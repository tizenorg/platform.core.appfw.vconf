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

#include <tet_api.h>
#include <vconf.h>
#include <string.h>

keylist_t* pKeyList = NULL;
static char* KEY_PARENT = NULL;
static char* KEY_01 = NULL;
static char* KEY_02 = NULL;
static char* KEY_03 = NULL;
static char* KEY_04 = NULL;

static int KEY_01_BOOL_VALUE;
static int KEY_02_INT_VALUE;
static double KEY_03_DOUBLE_VALUE;
static char* KEY_04_STRING_VALUE;


static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_ApplicationFW_vconf_keynode_get_str_func_01(void);
static void utc_ApplicationFW_vconf_keynode_get_str_func_02(void);
// static void utc_ApplicationFW_vconf_keynode_get_str_func_03(void);


enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_ApplicationFW_vconf_keynode_get_str_func_01, POSITIVE_TC_IDX },
	{ utc_ApplicationFW_vconf_keynode_get_str_func_02, NEGATIVE_TC_IDX },
//	{ utc_ApplicationFW_vconf_keynode_get_str_func_03, NEGATIVE_TC_IDX },
	{ NULL, 0 }
};

static void startup(void)
{
	KEY_PARENT = "db/tet";
	KEY_01="db/tet/key_1";
	KEY_02="db/tet/key_2";
	KEY_03="db/tet/key_3";
	KEY_04="db/tet/key_4";

	KEY_01_BOOL_VALUE = 1;
	KEY_02_INT_VALUE = 100;
	KEY_03_DOUBLE_VALUE = 25.458;
	KEY_04_STRING_VALUE = "TestMessage";
	
	if(pKeyList!=NULL)
	{
		vconf_keylist_free(pKeyList);
		pKeyList = NULL;
	}

	pKeyList = vconf_keylist_new();

	vconf_keylist_add_bool(pKeyList, KEY_01, KEY_01_BOOL_VALUE);
	vconf_keylist_add_int(pKeyList, KEY_02, KEY_02_INT_VALUE);
	vconf_keylist_add_dbl(pKeyList, KEY_03, KEY_03_DOUBLE_VALUE);
	vconf_keylist_add_str(pKeyList, KEY_04, KEY_04_STRING_VALUE);

	vconf_set(pKeyList);
	vconf_keylist_free(pKeyList);
	pKeyList = NULL;
}

static void cleanup(void)
{
	if(pKeyList!=NULL)
	{
		vconf_keylist_free(pKeyList);
		pKeyList = NULL;
	}
}

/**
 * @brief Positive test case of vconf_keylist_get_str()
 */
static void utc_ApplicationFW_vconf_keynode_get_str_func_01(void)
{
	int r = 0;	
	char* pszRet;
	keynode_t* pKeyNode = NULL;

	pKeyList = vconf_keylist_new();
	r = vconf_get(pKeyList, KEY_PARENT, VCONF_GET_KEY);	
	if (r) {
		tet_infoline("vconf_get() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}

	while((pKeyNode = vconf_keylist_nextnode(pKeyList))!=NULL)
	{
		switch(vconf_keynode_get_type(pKeyNode))
		{
			case VCONF_TYPE_STRING:
				pszRet = vconf_keynode_get_str(pKeyNode);
				if (strncmp(pszRet, KEY_04_STRING_VALUE, strlen(pszRet))) {
					tet_infoline("vconf_keynode_get_bool() failed in positive test case");
					tet_result(TET_FAIL);
					return;
				}
				break;
				
			default:
				break;
		}
	}

	vconf_keylist_free(pKeyList);
	pKeyList = NULL;
	
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of ug_init vconf_keylist_get_str()
 */
static void utc_ApplicationFW_vconf_keynode_get_str_func_02(void)
{
	char* pszRet = NULL;
	pszRet = vconf_keynode_get_str(NULL);
	if (pszRet != NULL) {
		tet_infoline("vconf_keynode_get_bool() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	
	tet_result(TET_PASS);
}

#if 0
static void utc_ApplicationFW_vconf_keynode_get_str_func_03(void)
{
	int r = 0;	
	char* pszRet;
	keynode_t* pKeyNode = NULL;

	pKeyList = vconf_keylist_new();
	r = vconf_get(pKeyList, KEY_PARENT, VCONF_GET_KEY);	
	if (r) {
		tet_infoline("vconf_get() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}

	while(pKeyNode = vconf_keylist_nextnode(pKeyList))
	{
		switch(vconf_keynode_get_type(pKeyNode))
		{
			case VCONF_TYPE_INT:
				pszRet = vconf_keynode_get_str(pKeyNode);
				if (pszRet!=NULL)
				{
					tet_infoline("vconf_keynode_get_bool() failed in positive test case");
					tet_result(TET_FAIL);
					return;
				}
				break;
				
			default:
				break;
		}
	}

	vconf_keylist_free(pKeyList);
	pKeyList = NULL;
}
#endif
