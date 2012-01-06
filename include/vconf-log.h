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

#ifndef __VCONF_LOG_H__
#define __VCONF_LOG_H__

#include <stdio.h>
#include <unistd.h>

#define VCONF_DLOG_OUT

/************** Error ***************/
#ifdef VCONF_SYSLOG_OUT
#include <syslog.h>
#define VCONF_SYS_LOGD(prio, fmt, arg...) \
	do { syslog(prio, "[%s:%d] "fmt"\n", __FILE__, __LINE__, ##arg); \
	} while (0)
#define VCONF_SYS_LOG(prio, fmt, arg...) \
	do { syslog(prio, fmt, ##arg); } while (0)
#define INFO(fmt, arg...) VCONF_SYS_LOG(LOG_INFO, fmt, ##arg)
#define ERR(fmt, arg...) VCONF_SYS_LOG(LOG_ERR, fmt, ##arg)
#elif defined(VCONF_DLOG_OUT)
#define LOG_TAG		"VCONF"
#include <dlog.h>
#define VCONF_DLOG(prio, fmt, arg...) \
	do { SLOG(prio, LOG_TAG, fmt, ##arg); } while (0)
#define INFO(fmt, arg...) SLOGI(fmt, ##arg)
#define ERR(fmt, arg...) SLOGE(fmt, ##arg)
#define VCONF_DBG(fmt, arg...) SLOGD(fmt, ##arg)
#else
#include <syslog.h>
#define VCONF_PRTD(prio, fmt, arg...) \
	do { fprintf((LOG_PRI(prio) == LOG_ERR ? stderr : stdout), \
		"[%s:%d] "fmt"\n", __FILE__, __LINE__, ##arg); \
	} while (0)
#define VCONF_PRT(prio, fmt, arg...) \
	do { fprintf((LOG_PRI(prio) == LOG_ERR ? stderr : stdout), fmt"\n", ##arg); } while (0)
#define INFO(fmt, arg...) VCONF_PRT(LOG_INFO, fmt, ##arg)
#define ERR(fmt, arg...) VCONF_PRT(LOG_ERR, fmt, ##arg)
#endif

#ifdef VCONF_DEBUGGING
#include <stdlib.h>

#define VCONF_DEBUG(fmt, arg...) \
	printf("\x1b[105;37m[%d]\x1b[0m(%s)" fmt "\n", getpid(), __FUNCTION__, ##arg)
#define DBG VCONF_DBG
#define warn_if(expr, fmt, arg...) do { \
		if (expr) { \
			DBG("(%s) -> "fmt, #expr, ##arg); \
		} \
	} while (0)
#define ret_if(expr) do { \
		if (expr) { \
			DBG("(%s) -> %s() return", #expr, __FUNCTION__); \
			return; \
		} \
	} while (0)
#define retv_if(expr, val) do { \
		if (expr) { \
			DBG("(%s) -> %s() return", #expr, __FUNCTION__); \
			return (val); \
		} \
	} while (0)
#define retm_if(expr, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			DBG("(%s) -> %s() return", #expr, __FUNCTION__); \
			return; \
		} \
	} while (0)
#define retvm_if(expr, val, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			DBG("(%s) -> %s() return", #expr, __FUNCTION__); \
			return (val); \
		} \
	} while (0)
#define retex_if(expr, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			DBG("(%s) -> %s() return", #expr, __FUNCTION__); \
			goto CATCH; \
		} \
	} while (0)

   /************** TimeCheck ***************/
#ifdef VCONF_TIMECHECK
#define START_TIME_CHECK \
	init_time();\
	startT = set_start_time();
#define END_TIME_CHECK \
	VCONF_DEBUG("time = %f ms\n", exec_time(startT));
#else
#define START_TIME_CHECK
#define END_TIME_CHECK
#endif
#else
#define DBG(...)
#define VCONF_DEBUG(...)

#define warn_if(expr, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
		} \
	} while (0)
#define ret_if(expr) do { \
		if (expr) { \
			return; \
		} \
	} while (0)
#define retv_if(expr, val) do { \
		if (expr) { \
			return (val); \
		} \
	} while (0)
#define retm_if(expr, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			return; \
		} \
	} while (0)
#define retvm_if(expr, val, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			return (val); \
		} \
	} while (0)
#define retex_if(expr, fmt, arg...) do { \
		if (expr) { \
			ERR(fmt, ##arg); \
			goto CATCH; \
		} \
	} while (0)

#define START_TIME_CHECK
#define END_TIME_CHECK

#endif

#endif				/* __VCONF_LOG_H__ */
