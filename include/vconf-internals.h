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

/*
 * Internals of libslp-setting
 *
 * @file        setting-internals.h
 * @author      Sangjung Woo (sangjung.woo@samsung.com)
 * @version     0.2
 * @brief       This file is the header file of internal functions.
 */

#ifndef __VCONF_GCONF_H__
#define __VCONF_GCONF_H__

#include <kdb.h>
#include "vconf-log.h"

/* #define KER_VER_CHECK */
#define BACKEND_DB_PREFIX "db/"
#define BACKEND_FILE_PREFIX "file/"
#define BACKEND_MEMORY_PREFIX "memory/"
#define BACKEND_GCONF_LOCAL_PREFIX "gconf_l/"
#define BACKEND_GCONF_DAEMON_PREFIX "gconf_d/"

#define BUF_LEN (1024)
#define CALLBACK_MAX (64)

typedef struct _keynode_t {
	char *keyname;
	int type;
	union {
		int i;
		int b;
		double d;
		char *s;
	} value;
	struct _keynode_t *next;
} keynode_t;

typedef struct _keylist_t {
	int num;
	keynode_t *head;
	keynode_t *cursor;
} keylist_t;

/*This is a callback function pointer signature*/
typedef void (*cb_func) (void *user_data);

/*This is a callback function pointer signature for value return*/
typedef void (*vconf_callback_fn) (keynode_t *node, void *user_data);

typedef struct {
	char *key;
	vconf_callback_fn cb;
	void *cb_data;
	unsigned int extra_num;
} callback_node_t;

enum {
	VCONF_BACKEND_NULL = 0,
	VCONF_BACKEND_GCONF_D,
	VCONF_BACKEND_GCONF_L,
	VCONF_BACKEND_DB,
	VCONF_BACKEND_FILE,
	VCONF_BACKEND_MEMORY,
};

enum {
	VCONF_TYPE_NONE = 0,
	VCONF_TYPE_BINARY = 20,
	VCONF_TYPE_STRING = 40,	/*KEY_TYPE_STRING of KDB is 40 */
	VCONF_TYPE_INT = 41,
	VCONF_TYPE_DOUBLE = 42,
	VCONF_TYPE_BOOL = 43,
	VCONF_TYPE_DIR,
};

typedef int get_option_t;
enum {
	VCONF_GET_KEY = 0,
	VCONF_GET_ALL,
	VCONF_GET_DIR,
};

typedef int cb_handle_t;
enum {
	VCONF_GLIB_LOOP,
	VCONF_ECORE_LOOP
};

/* Error codes retunred by the configuration manager */
#if 0
typedef enum {
	/*Unknown Error */
	VCONF_ERROR_UNKNOWN = -1,
	VCONF_ERROR_SUCCESS = 0,
	/* Something didn't work, don't know why, probably unrecoverable
	   so there's no point having a more specific errno */
	VCONF_ERROR_FAILED = 1,
	/* Server can't be launched/contacted */
	VCONF_ERROR_NO_SERVER = 2,
	/* don't have permission for that */
	VCONF_ERROR_NO_PERMISSION = 3,
	/* Address couldn't be resolved */
	VCONF_ERROR_BAD_ADDRESS = 4,
	/* directory or key isn't valid 
	   (contains bad characters, or malformed slash arrangement) */
	VCONF_ERROR_BAD_KEY = 5,
	/* Syntax error when parsing */
	VCONF_ERROR_PARSE_ERROR = 6,
	/* Fatal error parsing/loading information inside the backend */
	VCONF_ERROR_CORRUPT = 7,
	/* Type requested doesn't match type found */
	VCONF_ERROR_TYPE_MISMATCH = 8,
	/* Requested key operation on a dir */
	VCONF_ERROR_IS_DIR = 9,
	/* Requested dir operation on a key */
	VCONF_ERROR_IS_KEY = 10,
	/* Read-only source at front of path has set the value */
	VCONF_ERROR_OVERRIDDEN = 11,
	/* liboaf error */
	VCONF_ERROR_OAF_ERROR = 12,
	/* Tried to use remote operations on a local engine */
	VCONF_ERROR_LOCAL_ENGINE = 13,
	/* Failed to get a lockfile */
	VCONF_ERROR_LOCK_FAILED = 14,
	/* nowhere to write a value */
	VCONF_ERROR_NO_WRITABLE_DATABASE = 15,
	/* server is shutting down */
	VCONF_ERROR_IN_SHUTDOWN = 16,
	/* no key */
	VCONF_NO_KEY = 17,
	/* connection failure */
	VCONF_CONF_CONNECTION_FAIL = 18,
	/* invalid parameter */
	VCONF_CONF_INVALID_PARAMETER = 19,
	/* unable to get kdb key new */
	VCONF_CONF_ERROR_GET_KDB_KEY_NEW = 20,
	/* kdb open failure */
	VCONF_CONF_ERROR_KDB_OPEN = 21,
	/* unable to set kdb key val */
	VCONF_CONF_ERROR_KDB_KEY_SET = 22,
	/* unable to get kdb key val */
	VCONF_CONF_ERROR_KDB_KEY_GET = 23,
	/* unable to register callback notification */
	VCONF_ERROR_NOTI_ADD_FILE_CB = 24,
	/* kdb remove failure */
	VCONF_CONF_ERROR_KDB_REMOVE = 25,
	/* unable to remove callback function registered */
	VCONF_ERROR_NOTI_DEL_FILE_CB = 26,
	/*Supplied keylist is empty/Non existing */
	VCONF_ERROR_NO_KEYLIST = 27,
	/*This functionality is not supported */
	VCONF_ERROR_NOT_SUPPORTED = 28,
	/*Callback could not be called/Failed */
	VCONF_ERROR_CALLBACK_FAILED = 29
} SLP_Setting_Error;
#endif

/*************** Elecktra ****************/
#define KDB_USER_DIR "/opt/var/kdb"
#define KDB_SYSTEM_DIR "/opt/var/kdb"
#define KDB_MEMORY_DIR "/var/run"

int _vconf_set_empty(const char *key);
Key *_vconf_kdb_get(const char *key);
int _vconf_kdb_add_notify
	(int backend_type, const char *keyname, vconf_callback_fn cb, void *data);
int _vconf_kdb_del_notify
	(int backend_type, const char *keyname, vconf_callback_fn cb);

#define KDB_OPEN_HANDLE \
	do {\
		if (g_kdb_handle == NULL)\
		g_kdb_handle = kdbOpen();\
	} while (0)

#endif
