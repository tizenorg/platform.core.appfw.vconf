/*
 * libslp-setting
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Hakjoo Ko <hakjoo.ko@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <sys/types.h>
#include <sys/inotify.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <linux/version.h>
#include <stdlib.h>
#include <pthread.h>
#include <glib.h>
#include "vconf-internals.h"

#include <glib.h>

#define INOTY_EVENT_MASK   (IN_CLOSE_WRITE | IN_DELETE_SELF)

__thread KDB *g_kdb_handle;

int _vconf_set_empty(const char *key)
{
	Key *k;

	retvm_if(key == NULL, -1, "Invalid argument: key is NULL");

	KDB_OPEN_HANDLE;
	retvm_if(g_kdb_handle == NULL, -1, "kdbOpen() failed");

	k = keyNew(key, KEY_MODE, 0666, KEY_END);
	if (k == NULL) {
		ERR("kdbNew() failed");
		return -1;
	}

	if (kdbSetKey(g_kdb_handle, k) == -1) {
		ERR("kdbSetKey() failed");
		keyDel(k);
		return -1;
	}

	keyDel(k);
	return 0;
}

Key *_vconf_kdb_get(const char *key)
{
	Key *k;
	int ret = 0;

	k = keyNew(key, KEY_END);
	if (k == NULL) {
		ERR("kdbNew() failed");
		return NULL;
	}

	if (ret = kdbGetKey(g_kdb_handle, k) < 0) {
		char err_buf[100] = { 0, };
		strerror_r(errno, err_buf, 100);
		ERR(" kdbGetKey(%s) failed(%s), %d", key, err_buf, ret);
		keyDel(k);
		return NULL;
	}
	return k;
}

/* inotify */

struct noti_node {
	int wd;
	int backend;
	char *keyname;
	vconf_callback_fn cb;
	void *cb_data;
	struct noti_node *next;
};
typedef struct noti_node notilist;
static GList *g_notilist;

static int inoti_comp_with_wd(gconstpointer a, gconstpointer b)
{
	int r;

	notilist *key1 = (notilist *) a;
	notilist *key2 = (notilist *) b;

	r = key1->wd - key2->wd;
	return r;
}

static int inoti_comp_with_wd_cb(gconstpointer a, gconstpointer b)
{
	int r;

	notilist *key1 = (notilist *) a;
	notilist *key2 = (notilist *) b;

	r = key1->wd - key2->wd;
	if (r != 0)
		return r;

	r = (int)(key1->cb - key2->cb);
	return r;
}

static int _kdb_inoti_fd;

static pthread_mutex_t _kdb_inoti_fd_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t _kdb_g_ns_mutex = PTHREAD_MUTEX_INITIALIZER;

static GSource *_kdb_handler;

static gboolean _kdb_gio_cb(GIOChannel *src, GIOCondition cond, gpointer data)
{
	int fd, r;
	struct inotify_event ie;

	DBG("_kdb_gio_cb function start");

	fd = g_io_channel_unix_get_fd(src);
	r = read(fd, &ie, sizeof(ie));

	while (r > 0) {

		INFO("read event from GIOChannel. pid : %d", getpid());
		
		if (g_notilist) {
			
			struct noti_node *t, *excuted_t = NULL;			
			keynode_t temp_node;
			Key *k;
			GList *noti_list;

			retvm_if(!(ie.mask & INOTY_EVENT_MASK),
				 TRUE, "Invalid argument: ie.mask(%d), ie.len(%d)",
				 ie.mask, ie.len);

			/* pthread_mutex_lock(&_kdb_g_ns_mutex); */

			noti_list = g_list_first(g_notilist);

			while (noti_list) {

				t = noti_list->data;

				if( (t) && (t->wd == ie.wd) ) {
					temp_node.keyname = t->keyname;
					k = NULL;

					if (!(ie.mask & IN_DELETE_SELF)) {
						KDB_OPEN_HANDLE;
						if (g_kdb_handle == NULL) {
							ERR("kdbOpen() failed");
							/* pthread_mutex_unlock
							    (&_kdb_g_ns_mutex); */
							return TRUE;
						}
						k = _vconf_kdb_get(t->keyname);
					}

					if (NULL == k)
						temp_node.type =
						    VCONF_TYPE_NONE;
					else
						temp_node.type =
						    keyGetType(k);
					
					switch (temp_node.type) {
					case VCONF_TYPE_INT:
						temp_node.value.i =
						    atoi(keyValue(k));
						INFO
						("Notify that key(%s) is %d / %d",
						     temp_node.keyname,
						     temp_node.value.i,
						     getpid());
						break;
					case VCONF_TYPE_DOUBLE:
						temp_node.value.d =
						    atof(keyValue(k));
						INFO
						("Notify that key(%s) is %f / %d",
						     temp_node.keyname,
						     temp_node.value.d,
						     getpid());
						break;
					case VCONF_TYPE_BOOL:
						temp_node.value.b =
						    !!atoi(keyValue(k));
						INFO
						("Notify that key(%s) is %d / %d",
						     temp_node.keyname,
						     temp_node.value.b,
						     getpid());
						break;
					case VCONF_TYPE_STRING:
						temp_node.value.s =
						    (char *)keyValue(k);
						INFO
						("Notify that key(%s) is %s / %d",
						     temp_node.keyname,
						     temp_node.value.s,
						     getpid());
						break;
					default:
						temp_node.value.s =
						    NULL;
						INFO
						("Notify that key(%s) is deleted",
						    temp_node.keyname);
					}
					t->cb(&temp_node, t->cb_data);
					excuted_t = t;
			    }
				
				noti_list = g_list_next(noti_list);
			}
			/* pthread_mutex_unlock(&_kdb_g_ns_mutex); */

			if ((ie.mask & IN_DELETE_SELF) && excuted_t)
				_vconf_kdb_del_notify(excuted_t->backend,
						      excuted_t->keyname, NULL);
		}

		if (ie.len > 0)
			/*read(fd, name, ie.len);*/
			lseek(fd, ie.len, SEEK_CUR);

		r = read(fd, &ie, sizeof(ie));
	}

	return TRUE;
}

#ifdef KER_VER_CHECK
#include <sys/utsname.h>
#define PROC_VERSION "/proc/version"

static int kern_ver;		/* Kernel version */

static int get_kernel_ver()
{
	struct utsname nm;
	int ret, fd;
	char buf[1024];
	int v1, v2, v3;

	retv_if(kern_ver != 0, kern_ver);

	ret = uname(&nm);
	if (ret == 0) {
		strcpy(buf, nm.release);

		ret = sscanf(buf, "%d.%d.%d", &v1, &v2, &v3);
	} else {
		fd = open(PROC_VERSION, O_RDONLY);
		retvm_if(fd == -1, -1, "File open error: %s", strerror(errno));

		memset(buf, 0x0, sizeof(buf));
		ret = read(fd, buf, sizeof(buf));
		close(fd);

		ret = sscanf(buf, "Linux version %d.%d.%d", &v1, &v2, &v3);
	}

	if (ret == 3) {
		kern_ver = KERNEL_VERSION(v1, v2, v3);
		return kern_ver;
	}

	return -1;
}
#endif

static int _vconf_kdb_noti_init(void)
{
	GIOChannel *gio;

	pthread_mutex_lock(&_kdb_inoti_fd_mutex);

	retex_if(0 < _kdb_inoti_fd, "Error : invalid _kdb_inoti_fd");

#ifdef KER_VER_CHECK
	if (get_kernel_ver() < KERNEL_VERSION(2, 6, 13)) {
		ERR("inotify requires kernel version >= 2.6.13 ");
		errno = EPERM;
		goto CATCH;
	}
#endif

	_kdb_inoti_fd = inotify_init();
	if (_kdb_inoti_fd == -1) {
		char err_buf[100] = { 0, };
		strerror_r(errno, err_buf, sizeof(err_buf));
		ERR("inotify init: %s", err_buf);
		goto CATCH;
	}

	fcntl(_kdb_inoti_fd, F_SETFD, FD_CLOEXEC);
	fcntl(_kdb_inoti_fd, F_SETFL, O_NONBLOCK);

	pthread_mutex_unlock(&_kdb_inoti_fd_mutex);

	gio = g_io_channel_unix_new(_kdb_inoti_fd);
	retvm_if(gio == NULL, -1, "Error: create a new GIOChannel");

	g_io_channel_set_flags(gio, G_IO_FLAG_NONBLOCK, NULL);

	_kdb_handler = g_io_create_watch(gio, G_IO_IN);
	g_source_set_callback(_kdb_handler, (GSourceFunc) _kdb_gio_cb, NULL,
			      NULL);
	g_source_attach(_kdb_handler, NULL);
	g_io_channel_unref(gio);
	g_source_unref(_kdb_handler);

	return 0;

 CATCH:

	pthread_mutex_unlock(&_kdb_inoti_fd_mutex);

	return -1;

}

int
_vconf_kdb_add_notify(int backend_type, const char *keyname,
		      vconf_callback_fn cb, void *data)
{
	char path[PATH_MAX];
	int wd, r;
	struct noti_node t, *n;
	char err_buf[100] = { 0, };
	int ret = 0;
	GList *list = NULL;

	retvm_if((keyname == NULL
		  || cb == NULL), -1, "_vconf_kdb_add_notify : Invalid argument - keyname(%s) cb(%p)",
		 keyname, cb);

	if (_kdb_inoti_fd <= 0)
		if (_vconf_kdb_noti_init())
			return -1;

	if (VCONF_BACKEND_DB == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_USER_DIR, keyname);
	else if (VCONF_BACKEND_FILE == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_SYSTEM_DIR, keyname);
	else if (VCONF_BACKEND_MEMORY == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_MEMORY_DIR, keyname);
	else {
		ERR("_vconf_kdb_add_notify : Invalid argument - wrong prefix(%d) of key", backend_type);
		return -1;
	}

	if (0 != access(path, F_OK)) {
		if (errno == ENOENT) {
			ERR("_vconf_kdb_add_notify : Key(%s) does not exist", keyname);
			return -1;
			/* No key creation on adding a callback */
			/*_vconf_set_empty(keyname);*/
		}
	}

	wd = inotify_add_watch(_kdb_inoti_fd, path, INOTY_EVENT_MASK);
	if (wd == -1) {
		strerror_r(errno, err_buf, sizeof(err_buf));
		ERR("_vconf_kdb_add_notify : add noti(%s)", err_buf);
		return -1;
	}

	t.wd = wd;
	t.cb = cb;

	pthread_mutex_lock(&_kdb_g_ns_mutex);
	
	list = g_list_find_custom(g_notilist, &t, (GCompareFunc)inoti_comp_with_wd_cb);
	if (list) {
		ERR("_vconf_kdb_add_notify : key(%s) has same callback(%p)", keyname, cb);
		errno = EALREADY;
		ret = -1;
		goto out_func;
	}

	n = calloc(1, sizeof(notilist));
	if (n == NULL) {
		memset(err_buf, 0x00, sizeof(err_buf));
		strerror_r(errno, err_buf, sizeof(err_buf));
		ERR("_vconf_kdb_add_notify : add noti(%s)", err_buf);
		ret = -1;
		goto out_func;
	}

	n->wd = wd;
	n->backend = backend_type;
	n->keyname = strndup(keyname, BUF_LEN);
	n->cb_data = data;
	n->cb = cb;

	g_notilist = g_list_append(g_notilist, n);
	if(!g_notilist) {
		ERR("g_list_append fail");
	}

	INFO("cb is added for %s. tot cb cnt : %d\n", n->keyname, g_list_length(g_notilist));

out_func:
	pthread_mutex_unlock(&_kdb_g_ns_mutex);

	return ret;
}

int
_vconf_kdb_del_notify(int backend_type, const char *keyname,
		      vconf_callback_fn cb)
{
	int wd = 0;
	int r = 0;
	struct noti_node *n = NULL;
	struct noti_node t;
	char path[PATH_MAX] = { 0, };
	int del = 0;
	int remain = 0;
	int ret = 0;
	GList *noti_list;

	retvm_if(keyname == NULL, -1, "Invalid argument: keyname(%s)", keyname);
	retvm_if(_kdb_inoti_fd == 0, -1,
		 "Invalid operation: not exist anything for inotify");

	if (VCONF_BACKEND_DB == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_USER_DIR, keyname);
	else if (VCONF_BACKEND_FILE == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_SYSTEM_DIR, keyname);
	else if (VCONF_BACKEND_MEMORY == backend_type)
		snprintf(path, PATH_MAX, "%s/%s", KDB_MEMORY_DIR, keyname);
	else {
		ERR("Invalid argument: wrong prefix of key");
		ret = -1;
		goto out_func;
	}

	/* get wd */
	wd = inotify_add_watch(_kdb_inoti_fd, path, INOTY_EVENT_MASK);
	if (wd == -1) {
		char err_buf[100] = { 0, };
		strerror_r(errno, err_buf, sizeof(err_buf));

		ERR("Error: inotify_add_watch() [%s]: %s", path, err_buf);
		ret = -1;
		goto out_func;
	}

	pthread_mutex_lock(&_kdb_g_ns_mutex);

	t.wd = wd;
	t.cb = cb;
	
	noti_list = g_list_find_custom(g_notilist, &t, (GCompareFunc)inoti_comp_with_wd_cb);
	if(noti_list) {
		del++;
		
		n = noti_list->data;
		g_notilist = g_list_remove(g_notilist, n);
		g_free(n->keyname);
		g_free(n);

		INFO("key(%s) cb is removed. remained noti list total length(%d)", 
			keyname, g_list_length(g_notilist));
	}

	noti_list = NULL;
	noti_list = g_list_find_custom(g_notilist, &t, (GCompareFunc)inoti_comp_with_wd);
	if(noti_list == NULL) {
		INFO("all noti for keyname(%s)/wd(%d) is removed", keyname, wd);

		r = inotify_rm_watch(_kdb_inoti_fd, wd);
		if(r == -1) {
			char err_buf[100] = {0,};
			strerror_r(errno, err_buf, sizeof(err_buf));
	  
			ERR("Error: inotify_rm_watch [%s]: %s", keyname, err_buf);
			ret = -1;
		}
	}

	if(g_list_length(g_notilist) == 0) {
		
		close(_kdb_inoti_fd);
		_kdb_inoti_fd = 0;

		g_source_destroy(_kdb_handler);
		_kdb_handler = NULL;

		g_list_free(g_notilist);
		g_notilist = NULL;

		INFO("all noti list is freed");		
	}	
	
	pthread_mutex_unlock(&_kdb_g_ns_mutex);

	if(del == 0) {
		ERR("Error: nothing deleted");
		errno = ENOENT;
		ret = -1;
	}

out_func:
	return ret;
}
