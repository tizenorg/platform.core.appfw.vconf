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

#define _GNU_SOURCE

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "vconf-internals.h"

extern __thread KDB *g_kdb_handle;

#ifndef API
#define API __attribute__ ((visibility("default")))
#endif

#define MAX_ERROR_LOOP_CNT 3
#define ERROR_LOOP_SLEEP_TIME 50000

/* #define ADDR_TRANS */

#ifdef VCONF_TIMECHECK
double correction, startT;

double set_start_time(void)
{
	struct timeval tv;
	double curtime;

	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
	return curtime;
}

double exec_time(double start)
{
	double end = set_start_time();
	return (end - start - correction);
}

int init_time(void)
{
	double temp_t;
	temp_t = set_start_time();
	correction = exec_time(temp_t);

	return 0;
}
#endif

static int keynode_set_keyname(keynode_t *keynode, const char *keyname)
{
	if (keynode->keyname)
		free(keynode->keyname);
	keynode->keyname = strndup(keyname, BUF_LEN);
	retvm_if(keynode->keyname == NULL, -1, "strndup Fails");
	return 0;
}

static inline void keynode_set_dir(keynode_t *keynode)
{
	keynode->type = VCONF_TYPE_DIR;
}

static inline void keynode_set_value_int(keynode_t *keynode, const int value)
{
	keynode->type = VCONF_TYPE_INT;
	keynode->value.i = value;
}

static inline void keynode_set_value_bool(keynode_t *keynode, const int value)
{
	keynode->type = VCONF_TYPE_BOOL;
	keynode->value.b = !!value;
}

static inline void keynode_set_value_dbl(keynode_t *keynode, const double value)
{
	keynode->type = VCONF_TYPE_DOUBLE;
	keynode->value.d = value;
}

static inline void keynode_set_value_str(keynode_t *keynode, const char *value)
{
	keynode->type = VCONF_TYPE_STRING;
	keynode->value.s = strndup(value, BUF_LEN);
}

static inline keynode_t *keynode_next(keynode_t *keynode)
{
	return keynode->next;
}

static inline void keynode_free(keynode_t *keynode)
{
	if (keynode->keyname)
		free(keynode->keyname);
	if (keynode->type == VCONF_TYPE_STRING && keynode->value.s)
		free(keynode->value.s);
	free(keynode);
}

static inline keynode_t *keylist_headnode(keylist_t *keylist)
{
	return keylist->head;
}

static keynode_t *keylist_lookup(keylist_t *keylist, const char *keyname,
				 keynode_t **before_keynode)
{
	keynode_t *found_node, *temp_node = NULL;

	found_node = keylist->head;
	while (found_node) {
		if (strlen(found_node->keyname) == strlen(keyname)) {
			if (!strncmp
			    (keyname, found_node->keyname, strlen(keyname))) {
				if (before_keynode)
					*before_keynode = temp_node;
				return found_node;
			}
		}
		temp_node = found_node;
		found_node = keynode_next(found_node);
	}
	return NULL;
}

static int trans_keyname(const char *keyname, char **trans_name)
{
#ifdef ADDR_TRANS
	char *_key;
#endif
	if (0 ==
	    strncmp(keyname, BACKEND_DB_PREFIX,
		    sizeof(BACKEND_DB_PREFIX) - 1)) {
		*trans_name = (char *)keyname;
		return VCONF_BACKEND_DB;
	} else if (0 ==
		   strncmp(keyname, BACKEND_FILE_PREFIX,
			   sizeof(BACKEND_FILE_PREFIX) - 1)) {
		*trans_name = (char *)keyname;
		return VCONF_BACKEND_FILE;
	} else if (0 ==
		   strncmp(keyname, BACKEND_MEMORY_PREFIX,
			   sizeof(BACKEND_MEMORY_PREFIX) - 1)) {
		*trans_name = (char *)keyname;
		return VCONF_BACKEND_MEMORY;
#ifdef ADDR_TRANS
	} else if (0 ==
		   strncmp(keyname, BACKEND_USER_PREFIX,
			   sizeof(BACKEND_USER_PREFIX) - 1)) {
		/*becasue string has additional character('\0') */
		_key = malloc(strlen(keyname));
		strcpy(_key, keyname + 2);
		memcpy(_key, "db", 2);
		*trans_name = _key;
		return VCONF_BACKEND_DB;
	} else if (0 ==
		   strncmp(keyname, BACKEND_SYSTEM_PREFIX,
			   sizeof(BACKEND_SYSTEM_PREFIX) - 1)) {
		_key = malloc(strlen(keyname));
		strcpy(_key, keyname + 2);
		memcpy(_key, "file", 4);
		*trans_name = _key;
		return VCONF_BACKEND_FILE;
#endif
	} else {
		ERR("Invalid argument: wrong prefix of key(%s)", keyname);
		return VCONF_BACKEND_NULL;
	}
}

static int check_connetion(int backend, void **gconf_handle)
{
	if (backend >= VCONF_BACKEND_DB) {
		KDB_OPEN_HANDLE;
		retvm_if(g_kdb_handle == NULL, -1, "kdbOpen() failed");
	}
	return 0;
}

static void _vconf_get_recursive(KeySet **ks, const char *key)
{
	KeySet *remove_ks = ksNew(0);
	Key *k, *parentKey;

	parentKey = keyNew(key, KEY_END);
	kdbGet(g_kdb_handle, remove_ks, parentKey, KDB_O_NORECURSIVE);
	keyDel(parentKey);
	ksRewind(remove_ks);
	while ((k = ksNext(remove_ks)) != 0)
		if (keyIsDir(k))
			_vconf_get_recursive(ks, keyName(k));

	ksAppend(*ks, remove_ks);
}

/*
 * This function get Key name of the keynode.
 * @param[in] keynode The Key
 * @return Key Name of the keynode
 */
API char *vconf_keynode_get_name(keynode_t *keynode)
{
	retvm_if(keynode == NULL, NULL, "Invalid argument: keynode is NULL");
	retvm_if(keynode->keyname == NULL, NULL, "The name of keynode is NULL");

	return keynode->keyname;
}

/*
 * This function get value type of the keynode.
 * @param[in] keynode The Key
 * @return Type of the keynode
 */
API int vconf_keynode_get_type(keynode_t *keynode)
{
	retvm_if(keynode == NULL, -1, "Invalid argument: keynode is NULL");

	return keynode->type;
}

API int vconf_keynode_get_int(keynode_t *keynode)
{
	retvm_if(keynode == NULL, -1, "Invalid argument: keynode is NULL");
	retvm_if(keynode->type != VCONF_TYPE_INT, -1,
		 "The type of keynode is not INT");

	return keynode->value.i;
}

API double vconf_keynode_get_dbl(keynode_t *keynode)
{
	retvm_if(keynode == NULL, -1.0, "Invalid argument: keynode is NULL");
	retvm_if(keynode->type != VCONF_TYPE_DOUBLE, -1.0,
		 "The type of keynode is not DBL");

	return keynode->value.d;
}

/*
 * This function get Boolean value of the keynode.
 * @param[in] keynode The Key
 * @return Boolean value, -1 on error
 */
API int vconf_keynode_get_bool(keynode_t *keynode)
{
	retvm_if(keynode == NULL, -1, "Invalid argument: keynode is NULL");
	retvm_if(keynode->type != VCONF_TYPE_BOOL, -1,
		 "The type of keynode is not BOOL");

	return !!(keynode->value.b);
}

/*
 * This function get String value of the keynode.
 * @param[in] keynode The Key
 * @return String value, NULL on error
 */
API char *vconf_keynode_get_str(keynode_t *keynode)
{
	retvm_if(keynode == NULL, NULL, "Invalid argument: keynode is NULL");
	retvm_if(keynode->type != VCONF_TYPE_STRING, NULL,
		 "The type of keynode is not STR");

	return keynode->value.s;
}

API char *vconf_keynode_steal_str(keynode_t *keynode)
{
	char *ret;
	retvm_if(keynode == NULL, NULL, "Invalid argument: keynode is NULL");
	retvm_if(keynode->type != VCONF_TYPE_STRING, NULL,
		 "The type of keynode is not STR");

	ret = keynode->value.s;
	keynode->value.s = NULL;
	return ret;
}

/*
 * Allocate, initialize and return a new Keylist object.
 * @return The pointer of New keylist, NULL on error
 */
API keylist_t *vconf_keylist_new(void)
{
	keylist_t *keylist;
	keylist = calloc(1, sizeof(keylist_t));

	return keylist;
}

/*
 * This function rewinds the KeyList internal cursor.
 * @param[in] keylist Key List
 * @return 0 on success, -1 on error
 */
API int vconf_keylist_rewind(keylist_t *keylist)
{
	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");

	keylist->cursor = NULL;

	return 0;
}

/*
 * A destructor for Keylist objects.
 * @param[in] keylist Key List
 * @return 0 on success, -1 on error
 */
API int vconf_keylist_free(keylist_t *keylist)
{
	keynode_t *keynode, *temp;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");

	if (keylist->num) {
		keynode = keylist_headnode(keylist);
		while (keynode) {
			temp = keynode_next(keynode);
			keynode_free(keynode);
			keynode = temp;
		}
	}
	free(keylist);
	return 0;
}

/*
 * This function look for a Keynode contained in keylist that matches keyname.
 * @param[in] keylist Key List
 * @param[in] keyname Key to find
 * @param[out] return_node pointer of keynode to set
 * @return Type of the found key
 */
API int
vconf_keylist_lookup(keylist_t *keylist,
		     const char *keyname, keynode_t **return_node)
{
	keynode_t *found_node;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");
	retvm_if(return_node == NULL, -1,
		 "Invalid argument: return_node is NULL");

	found_node = keylist_lookup(keylist, keyname, NULL);
	if (NULL == found_node)
		return 0;

	if (return_node)
		*return_node = found_node;
	return found_node->type;
}

/*
 * This function returns the next Key in a Keylist.
 * Next key is known by the keylist internal cursor.
 * @param[in] keylist Key List
 * @return The next Keynode, NULL on error
 */
API keynode_t *vconf_keylist_nextnode(keylist_t *keylist)
{
	retvm_if(keylist == NULL, NULL, "Invalid argument: keylist is NULL");

	if (keylist->cursor)
		keylist->cursor = keynode_next(keylist->cursor);
	else
		keylist->cursor = keylist->head;

	return keylist->cursor;
}

static int _vconf_keylist_add_dir(keylist_t *keylist, const char *keyname)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((keynode = keylist_lookup(keylist, keyname, NULL))) {
		keynode_set_dir(keynode);
		return keylist->num;
	}
	if ((keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		keynode_set_dir(addition);
		if (keylist->head && NULL != keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function appends a new Keynode included integer value to the keylist.
 * If same keyname exist, the keynode will change.
 * @param[in] keylist Key List
 * @param[in] keyname Key
 * @param[in] value The integer value
 * @return Number of keynode included in the keylist, -1 on error
 */
API int
vconf_keylist_add_int(keylist_t *keylist, const char *keyname, const int value)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((keynode = keylist_lookup(keylist, keyname, NULL))) {
		keynode_set_value_int(keynode, value);
		return keylist->num;
	}
	if ((keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		keynode_set_value_int(addition, value);
		if (keylist->head && NULL != keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function appends a new Keynode included boolean value to the keylist.
 * If same keyname exist, the keynode will change.
 * @param[in] keylist Key List
 * @param[in] keyname Key
 * @param[in] value The boolean value
 * @return Number of keynode included in the keylist, -1 on error
 */
API int
vconf_keylist_add_bool(keylist_t *keylist, const char *keyname, const int value)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((keynode = keylist_lookup(keylist, keyname, NULL))) {
		keynode_set_value_bool(keynode, value);
		return keylist->num;
	}
	if ((keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		keynode_set_value_bool(addition, value);
		if (keylist->head && NULL != keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function appends a new Keynode included double value to the keylist.
 * If same keyname exist, the keynode will change.
 * @param[in] keylist Key List
 * @param[in] keyname Key
 * @param[in] value The double value
 * @return Number of keynode included in the keylist, -1 on error
 */
API int
vconf_keylist_add_dbl(keylist_t *keylist,
		      const char *keyname, const double value)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((keynode = keylist_lookup(keylist, keyname, NULL))) {
		keynode_set_value_dbl(keynode, value);
		return keylist->num;
	}
	if ((keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		keynode_set_value_dbl(addition, value);
		if (keylist->head && NULL != keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function appends a new Keynode included string value to the keylist.
 * If same keyname exist, the keynode will change.
 * @param[in] keylist Key List
 * @param[in] keyname Key
 * @param[in] value The pointer of string value
 * @return Number of keynode included in the keylist, -1 on error
 */
API int
vconf_keylist_add_str(keylist_t *keylist,
		      const char *keyname, const char *value)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((keynode = keylist_lookup(keylist, keyname, NULL))) {
		if (VCONF_TYPE_STRING == keynode->type && keynode->value.s)
			free(keynode->value.s);
		keynode_set_value_str(keynode, value);
		return keylist->num;
	}
	if (NULL != (keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		keynode_set_value_str(addition, value);
		if (keylist->head && NULL != keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function Appends a new Keynode to the keylist without value.
 * Use on vconf_get()
 * @param[in] keylist Key List
 * @param[in] keyname Key
 * @return Number of keynode included in the keylist, -1 on error
 */
API int vconf_keylist_add_null(keylist_t *keylist, const char *keyname)
{
	keynode_t *keynode, *addition;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if (NULL != (keynode = keylist_lookup(keylist, keyname, NULL))) {
		keynode->type = 0;
		keynode->value.d = 0;
		return keylist->num;
	}
	if ((keynode = keylist_headnode(keylist)))
		while (keynode_next(keynode))
			keynode = keynode_next(keynode);

	addition = calloc(1, sizeof(keynode_t));
	if (!keynode_set_keyname(addition, keyname)) {
		if (keylist->head && keynode)
			keynode->next = addition;
		else
			keylist->head = addition;
		keylist->num += 1;
	} else
		ERR("(maybe)not enought memory");

	return keylist->num;
}

/*
 * This function remove the keynode that matches keyname.
 * @param[in] keylist the keylist included the keyname
 * @param[in] keyname key
 * @return 0 on success, -1(Invalid parameter), -2(Not exist keyname in keylist) on error
 */
API int vconf_keylist_del(keylist_t *keylist, const char *keyname)
{
	keynode_t *found_node, *before_node;

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	retvm_if(keyname == NULL, -1, "Invalid argument: keyname is NULL");

	if ((found_node = keylist_lookup(keylist, keyname, &before_node))) {
		before_node->next = found_node->next;
		keynode_free(found_node);
	} else
		return -2;

	return 0;
}

API int vconf_sync_key(const char *in_key)
{
	START_TIME_CHECK 

	int fd;
	char path[PATH_MAX];
	char *key;
	int backend_type;

	backend_type = trans_keyname(in_key, &key);

	retvm_if(backend_type != VCONF_BACKEND_FILE, -1,
		 "Invalid argument: file Backend is only valid");
	snprintf(path, PATH_MAX, "%s/%s", KDB_SYSTEM_DIR, key);

	fd = open(path, O_RDWR);
	fsync(fd);
	close(fd);

	return 0;
}

/*
 * This function set the value of given keys
 * @param[in] keylist the keylist which should contain changed keys
 * @return 0 on success, -1 on error
 */
API int vconf_set(keylist_t *keylist)
{
	START_TIME_CHECK 

	char buf[BUF_LEN] = { 0, };
	keynode_t *got_node;
	char *changedname;
	int backend_type;
	int error_loop_cnt = 0;
	KeySet *ks = ksNew(0);

	retex_if(keylist == NULL, "Invalid argument: keylist is NULL");

	INFO("(%d)START", keylist->num);

	got_node = keylist_headnode(keylist);
	while (got_node != NULL) {
		backend_type = trans_keyname(got_node->keyname, &changedname);
		if (VCONF_BACKEND_NULL == backend_type) {
			got_node = keynode_next(got_node);
			continue;
		}

		retex_if(-1 == check_connetion(backend_type, NULL),
			 "Connection Fail(%s)", got_node->keyname);

		switch (backend_type) {
		case VCONF_BACKEND_DB:
		case VCONF_BACKEND_FILE:
		case VCONF_BACKEND_MEMORY:
			switch (got_node->type) {
			case VCONF_TYPE_INT:
				snprintf(buf, BUF_LEN, "%d", got_node->value.i);
				ksAppendKey(ks,
					    keyNew(changedname, KEY_TYPE,
						   VCONF_TYPE_INT, KEY_VALUE,
						   buf, KEY_END));
				break;
			case VCONF_TYPE_DOUBLE:
				snprintf(buf, BUF_LEN, "%f", got_node->value.d);
				ksAppendKey(ks,
					    keyNew(changedname, KEY_TYPE,
						   VCONF_TYPE_DOUBLE, KEY_VALUE,
						   buf, KEY_END));
				break;
			case VCONF_TYPE_BOOL:
				snprintf(buf, BUF_LEN, "%d", got_node->value.b);
				ksAppendKey(ks,
					    keyNew(changedname, KEY_TYPE,
						   VCONF_TYPE_BOOL, KEY_VALUE,
						   buf, KEY_END));
				break;
			case VCONF_TYPE_STRING:
				ksAppendKey(ks,
					    keyNew(changedname, KEY_TYPE,
						   VCONF_TYPE_STRING, KEY_VALUE,
						   got_node->value.s, KEY_END));
				break;
			default:
				ERR("Key(%s) has Unknown Type",
				    got_node->keyname);
			}
#ifdef ADDR_TRANS
			if (got_node->keyname != changedname)
				free(changedname);
#endif
			break;
		default:
			ERR("Key(%s) has Unknown Backend", got_node->keyname);
		}

		got_node = keynode_next(got_node);
	}

	if (ksGetSize(ks)) {
		while (kdbSet(g_kdb_handle, ks, 0, 0)) {
			/* We got an error. Retry 5 times. */
			if (error_loop_cnt == MAX_ERROR_LOOP_CNT) {
				Key *problem;
				char keyname[300] = "";

				problem = ksCurrent(ks);
				if (problem)
					keyGetFullName(problem, keyname,
						       sizeof(keyname));
				ERR("kdbSet error: while saving %s", keyname);

				/* And try to set keys again starting 
				   from the next key, */
				/* unless we reached the end of KeySet */
				if (ksNext(ks) == 0)
					break;
			} else {
				usleep(ERROR_LOOP_SLEEP_TIME);
				error_loop_cnt++;
			}
		}
	}

	ksDel(ks);
	END_TIME_CHECK 
	return 0;

 CATCH:

	ksDel(ks);
	return -1;
}

static int _vconf_set_key(Key *k)
{
	int error_loop_cnt = 0;
	while (kdbSetKey(g_kdb_handle, k)) {
		ERR("kdbSetKey() failed");

		if (error_loop_cnt == MAX_ERROR_LOOP_CNT) {
			ERR("Retry %d times in error handler", error_loop_cnt);
			return -1;
		} else {
			usleep(ERROR_LOOP_SLEEP_TIME);
			error_loop_cnt++;
		}
	}

	return 0;
}

/*
 * This function set the integer value of given key
 * @param[in]	in_key	key
 * @param[in]	intval integer value to set
 * @return 0 on success, -1 on error
 */
API int vconf_set_int(const char *in_key, const int intval)
{
	START_TIME_CHECK

	char buf[BUF_LEN] = { 0, };
	char *key;
	int backend_type;
	Key *k;

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		snprintf(buf, BUF_LEN, "%d", intval);

		k = keyNew(key, KEY_TYPE, VCONF_TYPE_INT, KEY_VALUE, buf,
			   KEY_END);
		if (k == NULL) {
			ERR("kdbNew() failed");
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif

		if (_vconf_set_key(k) < 0) {
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	INFO("vconf_set_int(%d) : %s(%d) success", getpid(), in_key, intval);
	END_TIME_CHECK 
	return 0;
}

/*
* This function set the boolean value of given key
* @param[in]	in_key	key
* @param[in]	boolval boolean value to set 
		(Integer value 1 is 'True', and 0 is 'False')
* @return 0 on success, -1 on error
*/
API int vconf_set_bool(const char *in_key, const int boolval)
{
	START_TIME_CHECK

	char buf[BUF_LEN] = { 0, };
	char *key;
	int backend_type;
	Key *k;

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		snprintf(buf, BUF_LEN, "%d", !!boolval);

		k = keyNew(key, KEY_TYPE, VCONF_TYPE_BOOL, KEY_VALUE, buf,
			   KEY_END);
		if (k == NULL) {
			ERR("kdbNew() failed");
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif

		if (_vconf_set_key(k) < 0) {
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	INFO("vconf_set_bool(%d) : %s(%d) success", getpid(), in_key, boolval);
	END_TIME_CHECK 
	return 0;
}

/*
 * This function set the double value of given key
 * @param[in]	in_key	key
 * @param[in]	dblval double value to set
 * @return 0 on success, -1 on error
 */
API int vconf_set_dbl(const char *in_key, const double dblval)
{
	START_TIME_CHECK

	char buf[BUF_LEN] = { 0, };
	char *key;
	int backend_type;
	Key *k;

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		snprintf(buf, BUF_LEN, "%f", dblval);

		k = keyNew(key, KEY_TYPE, VCONF_TYPE_DOUBLE, KEY_VALUE, buf,
			   KEY_END);
		if (k == NULL) {
			ERR("kdbNew() failed");
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif

		if (_vconf_set_key(k) < 0) {
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	INFO("vconf_set_dbl(%d) : %s(%f) success", getpid(), in_key, dblval);
	END_TIME_CHECK 
	return 0;
}

/*
 * This function set the string value of given key
 * @param[in]	in_key	key
 * @param[in]	strval string value to set
 * @return 0 on success, -1 on error
 */
API int vconf_set_str(const char *in_key, const char *strval)
{
	START_TIME_CHECK 

	char *key;
	int backend_type;
	Key *k;

	retvm_if(strval == NULL, -1, "Invaild argument: strval is NULL");

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		k = keyNew(key, KEY_TYPE, VCONF_TYPE_STRING, KEY_VALUE, strval,
			   KEY_END);
		if (k == NULL) {
			ERR("kdbNew() failed");
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif

		if (_vconf_set_key(k) < 0) {
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	
	INFO("vconf_set_str(%d) : %s(%s) success", getpid(), in_key, strval);
	END_TIME_CHECK 
	return 0;
}

#if 1

/*
 * This function set the binary value of given key
 * @param[in]	in_key	key
 * @param[in]	binval binary value to set
 * @param[in]  size  the size for writing
 * @return 0 on success, -1 on error
 */
API int vconf_set_bytes(const char *in_key, const void *binval, int size)
{
	START_TIME_CHECK 

	char *key;
	int backend_type;
	Key *k;

	retvm_if(binval == NULL, -1, "Invaild argument: binval is NULL");
	retvm_if(size < 0, -1, "Invalid argument: size is not valid");

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		k = keyNew(key, KEY_TYPE, KEY_TYPE_BINARY, KEY_SIZE, size,
			   KEY_VALUE, binval, KEY_END);
		if (k == NULL) {
			ERR("kdbNew() failed");
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif

		if (_vconf_set_key(k) < 0) {
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	INFO("vconf_set_bytes(%d) : %s success", getpid(), in_key);
	END_TIME_CHECK 
	return 0;
}

/*
 * This function get the binary value of given key up to size bytes.
 * @param[in]	in_key	key
 * @param[out]	buf output buffer
 * @param[in]  size the size for reading
 * @return the number of bytes actually read on success, -1 on error
 */
API int vconf_get_bytes(const char *in_key, void *buf, int size)
{
	START_TIME_CHECK char *key;
	int backend_type, ret = 0;
	Key *k;

	retvm_if(buf == NULL, -1, "Invaild argument: buffer is NULL");
	retvm_if(size < 0, -1, "Invalid argument: size is not valid");

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		k = _vconf_kdb_get(key);
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		retvm_if(k == NULL, -1, "kdb get(%s) failed", in_key);

		if ((ret = keyGetBinary(k, buf, size)) < 0) {
			/* ERR("Invalid value"); */
			keyDel(k);
			return -1;
		}

		keyDel(k);
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}
	INFO("key(%s) has bytes data", in_key);
	END_TIME_CHECK 
	return ret;
}
#endif

static int _vconf_check_value_integrity(const void *value, type_t type)
{
	int i = 0;

	if ((type == VCONF_TYPE_STRING) && (value != NULL)) {
		return 0;
	}

	if ((value) && (strlen(value) > 0)) {
		if ((type == VCONF_TYPE_INT) || 
			(type == VCONF_TYPE_BOOL)|| 
			(type == VCONF_TYPE_DOUBLE)) {
			while (*(((char *)value) + i) != '\0') {
				if ( !isdigit(*(((char *)value) + i)) ) {
					if ((type != VCONF_TYPE_BOOL) && 
						(*(((char *)value) + i) != '-')) {
						if ((type == VCONF_TYPE_DOUBLE) && 
							(*(((char *)value) + i) != '.')) {
							ERR("ERROR : vconf value is not digit.");
							return -1;
						}	
					}
				}
				i++;
			}
		}

		return 0;
	} else {
		ERR("ERROR : vconf value is NULL.");
		return -2;
	}
}

/*
 * This function get the value of given keys
 * @param[in]	keylist	keylist
 * @param[in]	in_parentDIR parent DIRECTORY of needed keys
 * @param[in]	option VCONF_GET_KEY|VCONF_GET_DIR|VCONF_GET_ALL
 * @return 0 on success, -1 on error
 */
API int
vconf_get(keylist_t *keylist, const char *in_parentDIR, get_option_t option)
{
	START_TIME_CHECK char *parentDIR;
	keynode_t *temp_keynode;
	int backend_type;
	char orig_keyname[BUF_LEN];
	int is_getall = 0;
	KeySet *ks = NULL;
	Key *k, *parentKey;
	const void *get_value = NULL;
#ifdef ADDR_TRANS
	int changename_type = 0;
#endif

	retvm_if(keylist == NULL, -1, "Invalid argument: keylist is NULL");
	backend_type = trans_keyname(in_parentDIR, &parentDIR);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");

	if (backend_type >= VCONF_BACKEND_DB) {
		KDB_OPEN_HANDLE;
		retvm_if(g_kdb_handle == NULL, -1, "kdbOpen() failed");
#ifdef ADDR_TRANS
		if (in_parentDIR != parentDIR) {
			if (VCONF_BACKEND_DB == backend_type) {
				strncpy(orig_keyname, BACKEND_USER_PREFIX,
					sizeof(BACKEND_USER_PREFIX));
				changename_type = 4;
			} else if (VCONF_BACKEND_FILE == backend_type) {
				strncpy(orig_keyname, BACKEND_SYSTEM_PREFIX,
					sizeof(BACKEND_SYSTEM_PREFIX));
				changename_type = 6;
			}
		}
#endif
	}

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		{
			ks = ksNew(0);

			parentKey = keyNew(parentDIR, KEY_END);
			temp_keynode = keylist_headnode(keylist);

			if ((NULL != temp_keynode) && (VCONF_GET_KEY != option)) {
				ERR("Not support mode : Only VCONF_GET_KEY \
				option support To retrieve key with keylist");
				keyDel(parentKey);
				ksDel(ks);
				return -1;
			}

			while (temp_keynode != NULL) {
				if (temp_keynode->keyname) {
					/* if (0 == strncmp(temp_keynode->keyname, 
					   parentDIR, sizeof(parentDIR))) */
					/*kdbGet will handle */
					ksAppendKey(ks,
						    keyNew
						    (temp_keynode->keyname,
						     KEY_END));
				}
				temp_keynode = keynode_next(temp_keynode);
			}

			if (VCONF_GET_KEY == option)
				kdbGet(g_kdb_handle, ks, parentKey,
				       KDB_O_NODIR | KDB_O_NORECURSIVE);
			else if (VCONF_GET_ALL == option)
				kdbGet(g_kdb_handle, ks, parentKey,
				       KDB_O_NORECURSIVE);
			else
				kdbGet(g_kdb_handle, ks, parentKey,
				       KDB_O_DIRONLY | KDB_O_NORECURSIVE);

			keyDel(parentKey);
			ksRewind(ks);
			while (((k = ksNext(ks)) != 0)) {
				switch (keyGetType(k)) {
				case VCONF_TYPE_INT:
					get_value = keyValue(k);
					if (_vconf_check_value_integrity
					    (get_value, VCONF_TYPE_INT) < 0) {
						/* ERROR_HANDLING */
						ERR("_vconf_check_value \
						integrity (INT) Error");
						ksDel(ks);
						return -1;
					}
#ifdef ADDR_TRANS
					if (changename_type) {
						strncpy(orig_keyname +
							changename_type,
							keyName(k) +
							(changename_type - 2),
							BUF_LEN - 9);
						vconf_keylist_add_int(keylist,
								      orig_keyname,
								      atoi
								      (get_value));
					} else
#endif
						vconf_keylist_add_int(keylist,
								      keyName
								      (k),
								      atoi
								      (get_value));

					break;
				case VCONF_TYPE_DOUBLE:
					get_value = keyValue(k);
					if (_vconf_check_value_integrity
					    (get_value,
					     VCONF_TYPE_DOUBLE) < 0) {
						/* ERROR_HANDLING */
						ERR("_vconf_check_value \
						integrity (DBL) Error");
						ksDel(ks);
						return -1;
					}
#ifdef ADDR_TRANS
					if (changename_type) {
						strncpy(orig_keyname +
							changename_type,
							keyName(k) +
							(changename_type - 2),
							BUF_LEN - 9);
						vconf_keylist_add_dbl(keylist,
								      orig_keyname,
								      atof
								      (get_value));
					} else
#endif
						vconf_keylist_add_dbl(keylist,
								      keyName
								      (k),
								      atof
								      (get_value));
					break;
				case VCONF_TYPE_BOOL:
					get_value = keyValue(k);
					if (_vconf_check_value_integrity
					    (get_value, VCONF_TYPE_BOOL)
					    < 0) {
						/* ERROR_HANDLING */
						ERR("_vconf_check_value \
						integrity (BOOL) Error");
						ksDel(ks);
						return -1;
					}
#ifdef ADDR_TRANS
					if (changename_type) {
						strncpy(orig_keyname +
							changename_type,
							keyName(k) +
							(changename_type - 2),
							BUF_LEN - 9);
						vconf_keylist_add_bool(keylist,
								       orig_keyname,
								       atoi
								       (get_value));
					} else
#endif
						vconf_keylist_add_bool(keylist,
								       keyName
								       (k),
								       atoi
								       (get_value));
					break;
				case VCONF_TYPE_STRING:
					get_value = keyValue(k);
					if (_vconf_check_value_integrity
					    (get_value,
					     VCONF_TYPE_STRING) < 0) {
						/* ERROR_HANDLING */
						ERR("_vconf_check_value \
						integrity (STR) Error");
						ksDel(ks);
						return -1;
					}
#ifdef ADDR_TRANS
					if (changename_type) {
						strncpy(orig_keyname +
							changename_type,
							keyName(k) +
							(changename_type - 2),
							BUF_LEN - 9);
						vconf_keylist_add_str(keylist,
								      orig_keyname,
								      (char *)
								      get_value);
					} else
#endif
						vconf_keylist_add_str(keylist,
								      keyName
								      (k),
								      (char *)
								      get_value);
					break;
				default:
					if (keyIsDir(k)) {
#ifdef ADDR_TRANS
						if (changename_type) {
							strncpy(orig_keyname +
								changename_type,
								keyName(k) +
								(changename_type
								 - 2),
								BUF_LEN - 9);
							_vconf_keylist_add_dir
							    (keylist,
							     orig_keyname);
						} else
#endif
							_vconf_keylist_add_dir
							    (keylist,
							     keyName(k));
					}
					/* else ERR("key(%s) has a value of 
					   Unknown Type(%d)", 
					   keyName(k), keyGetType(k)); */
				}
			}
			ksDel(ks);
			break;
		}
	default:
		ERR("Key(%s) has Unknown Backend", in_parentDIR);
	}
	vconf_keylist_rewind(keylist);
	END_TIME_CHECK return 0;
}

static void *_vconf_get_key_value(char *key, type_t type, int backend_type)
{
	int error_loop_cnt = 0;
	Key *k;
	const void *get_value = NULL;

	char key_path[PATH_MAX] = {0,};
	void* return_value = NULL;
	int val_len = 0;

	if(key == NULL)
		return NULL;

 error_retry:
	error_loop_cnt++;
	if (error_loop_cnt == MAX_ERROR_LOOP_CNT + 1) {
		ERR("_vconf_get_key_value : Retry %d times in error handler", error_loop_cnt - 1);
		return NULL;
	} else if(error_loop_cnt > 2) {
		usleep(ERROR_LOOP_SLEEP_TIME);
	} else if (error_loop_cnt == 2) {
		switch(backend_type) {
			case VCONF_BACKEND_DB:
				snprintf(key_path, PATH_MAX, "%s/%s", KDB_USER_DIR, key);
				break;
			case VCONF_BACKEND_FILE:
				snprintf(key_path, PATH_MAX, "%s/%s", KDB_SYSTEM_DIR, key);
				break;
			case VCONF_BACKEND_MEMORY:
				snprintf(key_path, PATH_MAX, "%s/%s", KDB_MEMORY_DIR, key);
				break;
			default:
				ERR("_vconf_get_key_value : Invalid argument(wrong prefix(%d) of key)", type);
				return NULL;
		}

		if(access(key_path, F_OK) != 0) {
			if (errno == ENOENT) {
				ERR("_vconf_get_key_value : Key does not exist: %s", key);
				return NULL;
			}
		}

		usleep(ERROR_LOOP_SLEEP_TIME);
	}

	k = _vconf_kdb_get(key);
	if (k == NULL) {
		ERR("_vconf_get_key_value : kdb Get(%s) failed", key);
		goto error_retry;
	}

	if (keyGetType(k) == type) {
		if (type == VCONF_TYPE_STRING) {
			get_value = takeout_keyValue(k);
		} else {
			get_value = keyValue(k);
		}

		if (_vconf_check_value_integrity(get_value, type) < 0) {
			keyDel(k);
			get_value = NULL;
			goto error_retry;
		}

		return_value = NULL;

		if(strlen(get_value) == 0) {
			return_value = get_value;
		} else {
			val_len = strlen(get_value)+1;
			return_value = malloc(val_len);
			if(return_value != NULL) {
				memset(return_value, 0x00, val_len);
				memcpy(return_value, get_value, val_len-1);				
			} else {
				ERR("_vconf_get_key_value : malloc fail");
			}
		}

		keyDel(k);

		return return_value;
	} else {
		ERR("_vconf_get_key_value : vconf key type is not int.");
		keyDel(k);
		return NULL;
	}
}

/*
 * This function get the integer value of given key
 * @param[in]	in_key	key
 * @param[out]	intval output buffer
 * @return 0 on success, -1 on error
 */
API int vconf_get_int(const char *in_key, int *intval)
{
	START_TIME_CHECK char *key;
	int backend_type;
	void *value = NULL;

	retvm_if(intval == NULL, -1, "vconf_get_int : Invaild argument(%s) - intval is NULL", in_key);
	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "vconf_get_int : Invalid argument - Key(%s) Backend is not valid", in_key);
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "vconf_get_int : Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:

		value = _vconf_get_key_value(key, VCONF_TYPE_INT, backend_type);
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		if (value != NULL) {
			*intval = atoi(value);
			free(value);
		} else {
			ERR("vconf_get_int : _vconf_get_key_value(%s) fail", in_key);
			return -1;
		}

		break;
	default:
		ERR("vconf_get_int : Key(%s) has Unknown Backend", in_key);
		return -1;
	}

	END_TIME_CHECK return 0;
}

/*
 * This function get the boolean value of given key
 * @param[in]	in_key	key
 * @param[out]	boolval output buffer
 * @return 0 on success, -1 on error
 */
API int vconf_get_bool(const char *in_key, int *boolval)
{
	START_TIME_CHECK 
	char *key;
	int backend_type;
	void *value = NULL;

	retvm_if(boolval == NULL, -1, "vconf_get_bool : Invaild argument(%s) - boolval is NULL", in_key);
	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "vconf_get_bool : Invalid argument - Key(%s) Backend is not valid", in_key);
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "vconf_get_bool : Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:

		value = _vconf_get_key_value(key, VCONF_TYPE_BOOL, backend_type);
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		if (value != NULL) {
			*boolval = !!atoi(value);
			free(value);
		} else {
			ERR("vconf_get_bool : _vconf_get_key_value(%s) fail", in_key);
			return -1;
		}
		break;
	default:
		ERR("vconf_get_bool: Key(%s) has Unknown Backend", in_key);
	}

	END_TIME_CHECK
	return 0;
}

/*
 * This function get the double value of given key
 * @param[in]	in_key	key
 * @param[out]	dblval output buffer
 * @return 0 on success, -1 on error
 */
API int vconf_get_dbl(const char *in_key, double *dblval)
{
	START_TIME_CHECK char *key;
	int backend_type;
	void *value = NULL;

	retvm_if(dblval == NULL, -1, "vconf_get_dbl : Invaild argument(%s) - dblval is NULL)", in_key);
	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "vconf_get_dbl : Invalid argument - Key(%s) Backend is not valid", in_key);
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "vconf_get_dbl : Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:

		value = _vconf_get_key_value(key, VCONF_TYPE_DOUBLE, backend_type);
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		if (value != NULL) {
			*dblval = atof(value);
			free(value);
		} else {
			ERR("vconf_get_dbl : _vconf_get_key_value(%s) fail", in_key);
			return -1;
		}
		break;
	default:
		ERR("vconf_get_dbl : Key(%s) has Unknown Backend", in_key);
	}
	
	END_TIME_CHECK
	return 0;
}

/*
 * This function get the string value of given key
 * @param[in]	in_key	key
 * @return pointer of key value on success, NULL on error
 */
API char *vconf_get_str(const char *in_key)
{
	START_TIME_CHECK 
	char *key;
	int backend_type;
	void *value = NULL;
	char *strval = NULL;

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, NULL,
		 "vconf_get_str : Invalid argument - Key(%s) Backend is not valid", in_key);
	retvm_if(-1 == check_connetion(backend_type, NULL), NULL,
		 "vconf_get_str : Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		value = _vconf_get_key_value(key, VCONF_TYPE_STRING, backend_type);
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		if (value != NULL) {
			if(strlen(value) == 0) {
				INFO("vconf_get_str : _vconf_get_key_value(%s) is NULL string('')", in_key);
			}	
			strval = (char *)value;
		} else {
			ERR("vconf_get_str : _vconf_get_key_value(%s) is NULL", in_key);
			return NULL;
		}
		break;
	default:
		ERR("vconf_get_str : Key(%s) has Unknown Backend", in_key);
	}

	INFO("vconf_get_str : key(%s) is %s", in_key, strval);
	END_TIME_CHECK return strval;
}

/*
 * This function unset given key
 * @param[in]	in_key	key
 * @return 0 on success, -1 on error
 */
API int vconf_unset(const char *in_key)
{
	/* START_TIME_CHECK */
	char *key;
	int backend_type;
	int error_loop_cnt = 0;

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:

		while (kdbRemove(g_kdb_handle, key)) {
			if (error_loop_cnt == MAX_ERROR_LOOP_CNT) {
				ERR("Retry %d times in error handler",
				    error_loop_cnt);
#ifdef ADDR_TRANS
				if (key != in_key)
					free(key);
#endif
				return -1;
			} else {
				usleep(ERROR_LOOP_SLEEP_TIME);
				error_loop_cnt++;
			}
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}

	INFO("%s End", in_key);
	/* END_TIME_CHECK */
	return 0;
}

/*
 * This function unset given key recursively
 * @param[in]	in_dir	Directory name for removing
 * @return 0 on success, -1 on error
 */
API int vconf_unset_recursive(const char *in_dir)
{
	START_TIME_CHECK char *key;
	int backend_type;
	KeySet *ks;
	Key *k;
	int error_loop_cnt = 0;
	int ret = 0;

	backend_type = trans_keyname(in_dir, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: Backend is not valid");
	retvm_if(-1 == check_connetion(backend_type, NULL), -1,
		 "Connection Fail(%s)", in_dir);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		ks = ksNew(0);
		ksAppendKey(ks, keyNew(key, KEY_END));
		_vconf_get_recursive(&ks, key);

		if (ksGetSize(ks)) {
			ksRewind(ks);
			while (((k = ksNext(ks)) != 0)) {
				DBG("recursive unset (%s)", 
					keyName(k));
				keyRemove(k);
			}

			while (kdbSet(g_kdb_handle, ks, 0, 0)) {
				/* We got an error. Warn user. */
				Key *problem;
				char keyname[300] = "";

				problem = ksCurrent(ks);
				if (problem)
					keyGetFullName(problem, keyname, sizeof(keyname));

				DBG("kdbSet error: while removing %s. try %d times", 
					keyname, error_loop_cnt+1);

				/*
				retry to unset failed keys for error count times
				if unset key is failed for error count times 
				try to set keys from the next key
				unless we reached the end of KeySet
				*/	
				if (error_loop_cnt == MAX_ERROR_LOOP_CNT) {
					ERR("kdbSet error: while removing %s. error will be returned", 
						keyname);
					ret = -1;
					if (ksNext(ks) == 0)
						break;
				} else {
					usleep(ERROR_LOOP_SLEEP_TIME);
					error_loop_cnt++;
				}
			}
		} else {
			ERR("DIR(%s) has no keys or is not Unknown Directory name", 
				in_dir);
		}
		
		ksDel(ks);
#ifdef ADDR_TRANS
		if (key != in_dir)
			free(key);
#endif
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_dir);
	}

	DBG("unset recursive %s End", in_dir);
	
	END_TIME_CHECK 
	return ret;
}

API int vconf_notify_key_changed
	(const char *in_key, vconf_callback_fn cb, void *user_data) {
	/* START_TIME_CHECK */
	int backend_type;
	char *key;

	retvm_if(cb == NULL, -1, "Invalid argument: cb(%p)", cb);

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: (%s)Backend is not valid", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		if (_vconf_kdb_add_notify(backend_type, key, cb, user_data)) {
			ERR("vconf_notify_key_changed : key(%s) add notify fail",
			    in_key);
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		break;
	default:
		ERR("vconf_notify_key_changed : Key(%s) has Unknown Backend", in_key);
	}

	INFO("vconf_notify_key_changed : %s noti is added", in_key);

	/* END_TIME_CHECK */
	return 0;
}

API int vconf_ignore_key_changed(const char *in_key, vconf_callback_fn cb)
{
	/* START_TIME_CHECK */
	int backend_type;
	char *key;

	retvm_if(cb == NULL, -1, "Invalid argument: cb(%p)", cb);

	backend_type = trans_keyname(in_key, &key);
	retvm_if(backend_type == VCONF_BACKEND_NULL, -1,
		 "Invalid argument: (%s)Backend is not valid", in_key);

	switch (backend_type) {
	case VCONF_BACKEND_DB:
	case VCONF_BACKEND_FILE:
	case VCONF_BACKEND_MEMORY:
		if (_vconf_kdb_del_notify(backend_type, key, cb)) {
			ERR("vconf_ignore_key_changed() failed: key(%s)",
			    in_key);
#ifdef ADDR_TRANS
			if (key != in_key)
				free(key);
#endif
			return -1;
		}
#ifdef ADDR_TRANS
		if (key != in_key)
			free(key);
#endif
		break;
	default:
		ERR("Key(%s) has Unknown Backend", in_key);
	}

	INFO("vconf_ignore_key_changed : %s noti removed", in_key);
	/* END_TIME_CHECK */
	return 0;
}

