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

/**
 *  @ingroup SLP_PG
 *  @defgroup VCONF_PG VConf
 *  @{

 <h1 class="pg">Introduction</h1>
 VConf is a virtual configuration system which provides three kinds of backend and notification. Internally, VConf uses a modified Elektra 0.7 and inotify of kernel.

 @image html SLP_Vconf_PG_image01.png

 <h2 class="pg">Properties</h2>
- Convenient API (read/write common data type : integer, double, boolean, string)
- Guarantee Transaction(db backend)
- Apply Key-List concept
- Changeable Backend (db, file, memory)
- Simple Notification based Inotify
- Header File : vconf.h 

<h1 class="pg">Programming Guide</h1>

<h2 class="pg">Backends</h1>
VConf has 3 kinds of backend.

<h3 class="pg">1.	db backend</h1>
We can use this backend by specifying the "db" prefix. <br>
E.g. db/test_app/key1 <br>
A key starting with ¡°db¡± is saved at a location which is mounted by libsqlfs. Therefore the key has characteristics of a database.(robustness, atomicity). But it is slower than the other backends. <br>
Developers can use this backend in order to synchronize immediately. <br>

@code
#include <stdio.h>
#include <vconf.h> 

const char *key1_name="db/test/key1";

int main(int argc, char **argv)
{
   int key1_value;

   if(vconf_set_int(key1_name,1))
      fprintf(stderr, "vconf_set_int FAIL\n");
   else
      printf("vconf_set_int OK\n");

   if(vconf_get_int(key1_name, &key1_value))
      fprintf(stderr, "vconf_get_int FAIL\n");
   else
      printf("vconf_get_int OK(key1 value is %d)\n", key1_value);

   return 0;
}
@endcode

<h3 class="pg">2.	memory backend</h1>
We can use this backend by specifying the "memory" prefix. <br>
E.g. memory/test_app/key1 <br>
A key starting with ¡°memory¡± is saved at a location which is mounted by tmpfs. Therefore the key has characteristics of memory. It has the highest speed. But if the target is turned off, the key is removed (volatile). <br>
Developers can use this backend for keys such as the power state of phone. <br>

@code
#include <stdio.h>
#include <vconf.h>

 const char *key1_name="memory/test/key1";

 int main(int argc, char **argv)
 {
   int key1_value;

   if(vconf_set_bool(key1_name, 1))
      fprintf(stderr, "vconf_set_bool FAIL\n");
   else
      printf("vconf_set_bool OK\n");

   if(vconf_get_bool(key1_name, &key1_value))
      fprintf(stderr, "vconf_get_bool FAIL\n");
   else
      printf("vconf_get_bool OK(key1 value is %d)\n", key1_value);

   return 0;
 }
@endcode

<h3 class="pg">3.	File backend</h1>
We can use this backend by specifying the "file" prefix. <br>
E.g. file/test_app/key1 <br>
A key starting with ¡°file¡± is saved at a location which is mounted by basic file system. Therefore the key has characteristics of file. If the target is turned off without synchronising, the key can lose data. <br>
Developers can use this backend for keys such as the sync state of something, where it is not vitally important for the key to hold the correct data. <br>

@code
#include <stdio.h>
#include <vconf.h> 

const char *key1_name="file/test/key1";

int main(int argc, char **argv)
{
   double key1_value;

   if(vconf_set_dbl(key1_name, 1.23))
      fprintf(stderr, "vconf_set_dbl FAIL\n");
   else {
      printf("vconf_set_dbl OK\n");
      vconf_sync_key(key1_name);
   }

   if(vconf_get_dbl(key1_name, &key1_value))
      fprintf(stderr, "vconf_get_dbl FAIL\n");
   else
      printf("vconf_get_dbl OK(key1 value is %f)\n", key1_value);

   return 0;
}
@endcode

<h2 class="pg">Notification</h1>
The notification of a changed key is handled in the g_main_loop of the default context. If you want to receive a notification, you should use g_main_loop of the default context. <br>
For g_main_loop, refer to glib manual. <br>

@code
#include <stdio.h>
#include <vconf.h>
#include <glib-object.h>
#include <glib.h>

const char *key1_name="file/test/key1";

void test_cb(keynode_t *key, void* data)
{
   switch(vconf_keynode_get_type(key))
   {
      case VCONF_TYPE_INT:
	printf("key = %s, value = %d(int)\n",
		vconf_keynode_get_name(key), vconf_keynode_get_int(key));
	break;
      case VCONF_TYPE_BOOL:
	printf("key = %s, value = %d(bool)\n",
		vconf_keynode_get_name(key), vconf_keynode_get_bool(key));
	break;
      case VCONF_TYPE_DOUBLE:
	printf("key = %s, value = %f(double)\n",
		vconf_keynode_get_name(key), vconf_keynode_get_dbl(key));
	break;
      case VCONF_TYPE_STRING:
	printf("key = %s, value = %s(string)\n",
		vconf_keynode_get_name(key), vconf_keynode_get_str(key));
	break;
      default:
	fprintf(stderr, "Unknown Type(%d)\n", vconf_keynode_get_type(key));
	break;
   }
   return;
}

int main()
{
   GMainLoop *event_loop;

   vconf_notify_key_changed(key1_name, test_cb, NULL);

   event_loop = g_main_loop_new(NULL, FALSE);
   g_main_loop_run(event_loop);

   vconf_ignore_key_changed(key1_name, test_cb);

   return 0;
}
@endcode
*/

/**
@}
*/
