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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <vconf.h>
#include <glib-object.h>
#include "vconf-log.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

enum {
	VCONFTOOL_TYPE_NO = 0x00,
	VCONFTOOL_TYPE_STRING,
	VCONFTOOL_TYPE_INT,
	VCONFTOOL_TYPE_DOUBLE,
	VCONFTOOL_TYPE_BOOL
};

#define BUFSIZE		1024

const int SHARED_PERM = 0664;
const int USER_PERM = 0644;

const char *BACKEND_DB_PREFIX = "db/";
const char *BACKEND_FILE_PREFIX = "file/";
const char *BACKEND_MEMORY_PREFIX = "memory/";

const char *DB_PREFIX = "/opt/var/kdb";
const char *FILE_PREFIX = "/opt/var/kdb";
const char *MEMORY_PREFIX = "/var/run";
const char *MEMORY_INIT = "/opt/var/kdb/memory_init";

static char *guid = NULL;
static char *uid = NULL;
static char *vconf_type = NULL;
static int is_recursive = FALSE;
static int is_initialization = FALSE;
static int is_forced = FALSE;
static int get_num = 0;

static GOptionEntry entries[] = {
	{"type", 't', 0, G_OPTION_ARG_STRING, &vconf_type, "type of value",
	 "int|bool|double|string"},
	{"recursive", 'r', 0, G_OPTION_ARG_NONE, &is_recursive,
	 "retrieve keys recursively", NULL},
	{"guid", 'g', 0, G_OPTION_ARG_STRING, &guid, "group permission", NULL},
	{"uid", 'u', 0, G_OPTION_ARG_STRING, &uid, "user permission", NULL},
	{"initialization", 'i', 0, G_OPTION_ARG_NONE, &is_initialization,
	 "memory backend initialization", NULL},
	{"force", 'f', 0, G_OPTION_ARG_NONE, &is_forced,
	 "overwrite vconf values by force", NULL},
	{NULL}
};

static void get_operation(char *input);
static void recursive_get(char *subDIR, int level);
static void print_keylist(keylist_t *keylist, keynode_t *temp_node, int level);

static void print_help(const char *cmd)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "[Set vconf value]\n");
	fprintf(stderr,
		"       %s set -t <TYPE> <KEY NAME> <VALUE> <OPTIONS>\n", cmd);
	fprintf(stderr, "                 <TYPE>=int|bool|double|string\n");
	fprintf(stderr, "\n");
	fprintf(stderr,
		"       Ex) %s set -t string db/testapp/key1 \"This is test\" \n",
		cmd);
	fprintf(stderr, "\n");
	fprintf(stderr, "       <OPTIONS>\n");
	fprintf(stderr,
		"          -g <GUID> : Set Effective group id. The key's permission will be set to 0664.\n");
	fprintf(stderr,
		"           Ex) %s set -t string db/testapp/key1 \"This is test\" -g 425\n",
		cmd);
	fprintf(stderr,
		"           NOTE: -g and -u cannot be userd together. -u ignores -g option.\n");
	fprintf(stderr, "\n");
	fprintf(stderr,
		"          -u <UID> : Set Effective user id. The key's permission will be set to 0644.\n");
	fprintf(stderr,
		"           Ex) %s set -t string db/testapp/key1 \"This is test\" -u 5000\n",
		cmd);
	fprintf(stderr,
		"           NOTE: -g and -u cannot be userd together. -u ignores -g option.\n");
	fprintf(stderr, "\n");
	fprintf(stderr,
		"          -i : Install memory backend key into flash space for backup.\n");
	fprintf(stderr,
		"           Ex) %s set -t string db/testapp/key1 \"This is test\" -i\n",
		cmd);
	fprintf(stderr, "\n");
	fprintf(stderr,
		"          -f : Overwrite values by force, even when vconf values are already exist.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "[Get vconf value]\n");
	fprintf(stderr, "       %s get <OPTIONS> <KEY NAME>\n", cmd);
	fprintf(stderr, "\n");
	fprintf(stderr, "       <OPTIONS>\n");
	fprintf(stderr,
		"          -r : retrieve all keys included in sub-directorys \n");
	fprintf(stderr, "       Ex) %s get db/testapp/key1\n", cmd);
	fprintf(stderr, "           %s get db/testapp/\n", cmd);
	fprintf(stderr, "\n");
	fprintf(stderr, "[Unset vconf value]\n");
	fprintf(stderr, "       %s unset <KEY NAME>\n", cmd);
	fprintf(stderr, "\n");
	fprintf(stderr, "       Ex) %s unset db/testapp/key1\n", cmd);
	fprintf(stderr, "\n");
}

static int check_type(void)
{
	if (vconf_type) {
		if (!strncasecmp(vconf_type, "int", 3))
			return VCONFTOOL_TYPE_INT;
		else if (!strncasecmp(vconf_type, "string", 6))
			return VCONFTOOL_TYPE_STRING;
		else if (!strncasecmp(vconf_type, "double", 6))
			return VCONFTOOL_TYPE_DOUBLE;
		else if (!strncasecmp(vconf_type, "bool", 4))
			return VCONFTOOL_TYPE_BOOL;
	}
	return VCONFTOOL_TYPE_NO;
}

static int copy_memory_key(char *pszKey, char *pszOrigin)
{
	char szCmd[BUFSIZE] = { 0, };
	char szPath[BUFSIZE] = { 0, };
	char szFileName[BUFSIZE] = { 0, };
	char *pCh = strrchr(pszKey, '/');
	int nLen = strlen(pszKey);

	/* Get directory path and file name */
	snprintf(szPath, BUFSIZE, "%s/", MEMORY_INIT);
	strncat(szPath, pszKey, pCh - pszKey);
	strncpy(szFileName, pszKey + (pCh - pszKey) + 1, nLen - (pCh - pszKey));

	/* Check directory & create it */
	if (0 != access(szPath, F_OK)) {
		snprintf(szCmd, BUFSIZE, "mkdir %s -p --mode=755", szPath);
		if (system(szCmd)) {
			printf("[%s:%d]Fail mkdir() szCmd=%s\n", __FILE__,
			       __LINE__, szCmd);
			return -1;
		}
	}
	/* copy */
	strncat(szPath, "/", 1);
	strncat(szPath, szFileName, strlen(szFileName));
	memset(szCmd, 0x00, BUFSIZE);
	snprintf(szCmd, BUFSIZE, "cp %s %s -r -p", pszOrigin, szPath);
	if (system(szCmd)) {
		printf("[%s:%d]Fail copy\n", __FILE__, __LINE__);
		return -1;
	}
	return 0;
}

static int make_file_path(char *pszKey, char *pszBuf)
{
	if (0 ==
	    strncmp(pszKey, BACKEND_DB_PREFIX, sizeof(BACKEND_DB_PREFIX) - 1)) {
		snprintf(pszBuf, BUFSIZE, "%s/%s", DB_PREFIX, pszKey);
		return 0;
	} else if (0 ==
		   strncmp(pszKey, BACKEND_FILE_PREFIX,
			   sizeof(BACKEND_FILE_PREFIX) - 1)) {
		snprintf(pszBuf, BUFSIZE, "%s/%s", FILE_PREFIX, pszKey);
		return 0;
	} else if (0 ==
		   strncmp(pszKey, BACKEND_MEMORY_PREFIX,
			   sizeof(BACKEND_MEMORY_PREFIX) - 1)) {
		snprintf(pszBuf, BUFSIZE, "%s/%s", MEMORY_PREFIX, pszKey);
		return 0;
	}
	return -1;
}

int main(int argc, char **argv)
{
	int set_type;
	char szFilePath[BUFSIZE] = { 0, };
	int fd;
	int group_id;
	int user_id;

	GError *error = NULL;
	GOptionContext *context;

	g_type_init();
	context = g_option_context_new("- vconf library tool");
	g_option_context_add_main_entries(context, entries, NULL);
	g_option_context_set_help_enabled(context, FALSE);
	g_option_context_set_ignore_unknown_options(context, TRUE);

	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		exit(1);
	}

	if (argc < 2) {
		print_help(argv[0]);
		return 1;
	}

	if (!strncmp(argv[1], "set", 3)) {
		set_type = check_type();
		if (argc < 4 || !set_type) {
			print_help(argv[0]);
			return 1;
		}
#ifdef VCONF_TIMECHECK
		struct timeval tv;

		gettimeofday(&tv, NULL);
		printf("\x1b[105;37m[VConftool]\x1b[0m %d.%6d\n",
		       (int)tv.tv_sec, (int)tv.tv_usec);
#endif

		/*  Start DAC  *************************************/
		if (guid || uid) {
			if (0 != getuid()) {
				fprintf(stderr,
					"Error!\t Only root user can use '-g or -u' option\n");
				return -1;
			}
			if (guid) {
				/* TODO; digit check */
				group_id = atoi(guid);
				vconf_set_permission(SHARED_PERM);
			}
			if (uid) {
				user_id = atoi(uid);
				vconf_set_permission(USER_PERM);
			}

		}
		if (make_file_path(argv[2], szFilePath)) {
			fprintf(stderr, "Error!\t Bad prefix\n");
			return -1;
		}

		/*  End DAC  ****************************************/

		switch (set_type) {
		case VCONFTOOL_TYPE_STRING:
			vconf_set_str(argv[2], argv[3]);
			break;
		case VCONFTOOL_TYPE_INT:
			vconf_set_int(argv[2], atoi(argv[3]));
			break;
		case VCONFTOOL_TYPE_DOUBLE:
			vconf_set_dbl(argv[2], atof(argv[3]));
			break;
		case VCONFTOOL_TYPE_BOOL:
			vconf_set_bool(argv[2], !!atoi(argv[3]));
			break;

		default:
			fprintf(stderr, "never reach");
			exit(1);
		}

		/*  Start DAC  ***************************************/
		if (uid) {
			fd = open(szFilePath, O_RDONLY);
			if (-1 == fchown(fd, user_id, user_id)) {
				fprintf(stderr, "Error!\t Fail to fchown()\n");
				return -1;
			}
			close(fd);
		} else if (guid) {
			fd = open(szFilePath, O_RDONLY);
			if (-1 == fchown(fd, 0, group_id)) {
				fprintf(stderr, "Error!\t Fail to fchown()\n");
				return -1;
			}
			close(fd);
		}
		/*  End DAC  *****************************************/

		/* Install memory backend key into flash space *******/
		if (is_initialization) {
			copy_memory_key(argv[2], szFilePath);
		}

		/* End memory backend key into flash space ***********/

	} else if (!strncmp(argv[1], "get", 3)) {
		if (argv[2])
			get_operation(argv[2]);
		else
			print_help(argv[0]);
	} else if (!strncmp(argv[1], "unset", 5)) {
		if (argv[2])
			vconf_unset(argv[2]);
		else
			print_help(argv[0]);
	} else
		fprintf(stderr, "%s is a invalid command\n", argv[1]);
	return 0;
}

static void get_operation(char *input)
{
	keylist_t *get_keylist;
	keynode_t *temp_node;
	char *test;

	get_keylist = vconf_keylist_new();
	/* ParentDIR parameter of gconf_client_all_entries 
	can not include the last slash. */
	if ('/' == input[strlen(input) - 1] && strlen(input) > 8)
		input[strlen(input) - 1] = '\0';
	VCONF_DEBUG("vconf_get(%p, %s)", get_keylist, input);

	vconf_get(get_keylist, input, VCONF_GET_ALL);
	if (!(temp_node = vconf_keylist_nextnode(get_keylist))) {
		test = strrchr(input, '/');
		if (NULL != test) {
			vconf_keylist_add_null(get_keylist, input);
			if (test - input < 7)
				*(test + 1) = '\0';
			else
				*test = '\0';
			VCONF_DEBUG("vconf_get(%p, %s)", get_keylist, input);
			vconf_get(get_keylist, input, VCONF_GET_KEY);
			temp_node = vconf_keylist_nextnode(get_keylist);
		} else {
			fprintf(stderr, "Include at least one slash\"/\"\n");
			vconf_keylist_free(get_keylist);
			return;
		}
	}
	get_num = 0;
	print_keylist(get_keylist, temp_node, 0);

	if (!get_num)
		printf("No data\n");
	vconf_keylist_free(get_keylist);
}

static void recursive_get(char *subDIR, int level)
{
	VCONF_DEBUG("%s", subDIR);

	keylist_t *get_keylist;
	keynode_t *first_node;

	get_keylist = vconf_keylist_new();
	vconf_get(get_keylist, subDIR, VCONF_GET_ALL);

	if ((first_node = vconf_keylist_nextnode(get_keylist))) {
		print_keylist(get_keylist, first_node, level);
	}
	vconf_keylist_free(get_keylist);
}

static void print_keylist(keylist_t *keylist, keynode_t *temp_node, int level)
{
	do {
		switch (vconf_keynode_get_type(temp_node)) {
		case VCONF_TYPE_INT:
			printf("%s, value = %d (int)\n",
			       vconf_keynode_get_name(temp_node),
			       vconf_keynode_get_int(temp_node));
			get_num++;
			break;
		case VCONF_TYPE_BOOL:
			printf("%s, value = %d (bool)\n",
			       vconf_keynode_get_name(temp_node),
			       vconf_keynode_get_bool(temp_node));
			get_num++;
			break;
		case VCONF_TYPE_DOUBLE:
			printf("%s, value = %f (double)\n",
			       vconf_keynode_get_name(temp_node),
			       vconf_keynode_get_dbl(temp_node));
			get_num++;
			break;
		case VCONF_TYPE_STRING:
			printf("%s, value = %s (string)\n",
			       vconf_keynode_get_name(temp_node),
			       vconf_keynode_get_str(temp_node));
			get_num++;
			break;
		case VCONF_TYPE_DIR:
			VCONF_DEBUG("%s(Directory)\n",
				    vconf_keynode_get_name(temp_node));
			if (is_recursive)
				recursive_get(vconf_keynode_get_name(temp_node),
					      level + 1);
			break;
		default:
			/* fprintf(stderr, "Unknown Type(%d)\n", 
			vconf_keynode_get_type(temp_node)); */
			break;
		}
	} while ((temp_node = vconf_keylist_nextnode(keylist)));
}
