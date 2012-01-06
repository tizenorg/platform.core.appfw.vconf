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

#ifndef __VCONF_KEYS_H__
#define __VCONF_KEYS_H__

/**
 * This file defines keys and values.
 *
 * @file        vconf-keys.h
 * @defgroup    vconf_key Definitions of shared Keys
 * @ingroup     VCONF
 * @author      Wonguk Jeong (wonguk.jeong@samsung.com)
 * @author      Sangjung Woo (sangjung.woo@samsung.com)
 * @version     0.2
 * @brief       This file has the definitions of shared keys.
 *
 * add keys(key name) and values(enum) here for shared keys....
 *
 */

/* ========================== Mobex Engine Keys & Values ============================ */
/**
 * @defgroup vconf_key_modex Modex Engine Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_modex
 * @{
 * @brief Maintainer : sunbong.ha@samsung.com
 */
#define VCONFKEY_MOBEX_ENGINE_PREFIX "memory/mobex_engine"

/**
 * <!-- reg-control keynum=0, value=nt -->
 * @brief mobex engine status
 */
#define VCONFKEY_MOBEX_ENGINE_STATUS_INT VCONFKEY_MOBEX_ENGINE_PREFIX"/status"
/* check memo sync start/end for mobex-engine */
#define VCONFKEY_MOBEX_ENGINE_MEMO_SYNC_STATUS VCONFKEY_MOBEX_ENGINE_PREFIX"/memo_sync_status"
/**
 * @}
 */

/* ========================== Telephony Keys & Values ============================ */
/**
 * @defgroup vconf_key_Telephony Telephony Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Telephony
 * @{
 * @brief Maintainer : kyeongchul.kim@samsung.com, youngman.park@samsung.com
 */
#define VCONFKEY_TELEPHONY_PREFIX "memory/telephony"

/**
 * <!-- reg-control keynum=0, value=string -->
 * @brief current attached network name
 */
#define VCONFKEY_TELEPHONY_NWNAME   VCONFKEY_TELEPHONY_PREFIX"/nw_name"

/**
 * <!-- reg-control keynum=1, value=int -->
 * @brief it stands for current attached network PLMN value
 */
#define VCONFKEY_TELEPHONY_PLMN     VCONFKEY_TELEPHONY_PREFIX"/plmn"

/**
 * <!-- reg-control keynum=2, value=int -->
 * @brief it stands for current attached network LAC value
 */
#define VCONFKEY_TELEPHONY_LAC      VCONFKEY_TELEPHONY_PREFIX"/lac"

/**
 * <!-- reg-control keynum=3, value=int -->
 * @brief it stands for current attached network cell id value
 */
#define VCONFKEY_TELEPHONY_CELLID   VCONFKEY_TELEPHONY_PREFIX"/cell_id"

/**
 * <!-- reg-control keynum=4, value=enum -->
 * @brief it stands for current network type (3G, 2G, EDGE, Searching, Emergency, etc)
 */
#define VCONFKEY_TELEPHONY_SVCTYPE VCONFKEY_TELEPHONY_PREFIX"/svc_type"
enum {
	VCONFKEY_TELEPHONY_SVCTYPE_NONE,	/**< Network unknown */
	VCONFKEY_TELEPHONY_SVCTYPE_NOSVC,	/**< Network no service */
	VCONFKEY_TELEPHONY_SVCTYPE_EMERGENCY,	/**< Network emergency */
	VCONFKEY_TELEPHONY_SVCTYPE_SEARCH,	/**< Network search 1900 */
	VCONFKEY_TELEPHONY_SVCTYPE_2G,			/**< Network 2G */
	VCONFKEY_TELEPHONY_SVCTYPE_2_5G,		/**< Network 2.5G */
	VCONFKEY_TELEPHONY_SVCTYPE_2_5G_EDGE,	/**< Network EDGE */
	VCONFKEY_TELEPHONY_SVCTYPE_3G,			/**< Network UMTS */
	VCONFKEY_TELEPHONY_SVCTYPE_HSDPA	/**< Network HSDPA */
};

/**
 * <!-- reg-control keynum=5, value=enum -->
 * @brief it stands for current network circuit service availability
 */
#define VCONFKEY_TELEPHONY_SVC_CS VCONFKEY_TELEPHONY_PREFIX"/svc_cs"
enum {
	VCONFKEY_TELEPHONY_SVC_CS_UNKNOWN = 0x00,
	VCONFKEY_TELEPHONY_SVC_CS_OFF,
	VCONFKEY_TELEPHONY_SVC_CS_ON
};

/**
 * <!-- reg-control keynum=6, value=enum -->
 * @brief it stands for current network package service availability
 */
#define VCONFKEY_TELEPHONY_SVC_PS VCONFKEY_TELEPHONY_PREFIX"/svc_ps"
enum {
	VCONFKEY_TELEPHONY_SVC_PS_UNKNOWN = 0x00,
	VCONFKEY_TELEPHONY_SVC_PS_OFF,
	VCONFKEY_TELEPHONY_SVC_PS_ON
};

/**
 * <!-- reg-control keynum=7, value=enum -->
 * @brief it stands for current network zone is home zone or roaming zone
 */
#define VCONFKEY_TELEPHONY_SVC_ROAM VCONFKEY_TELEPHONY_PREFIX"/svc_roam"
enum {
	VCONFKEY_TELEPHONY_SVC_ROAM_OFF = 0x00,
	VCONFKEY_TELEPHONY_SVC_ROAM_ON
};

#define VCONFKEY_TELEPHONY_ZONE_TYPE VCONFKEY_TELEPHONY_PREFIX"/zone_type"
enum {
	VCONFKEY_TELEPHONY_ZONE_NONE = 0x00,
	VCONFKEY_TELEPHONY_ZONE_HOME,
	VCONFKEY_TELEPHONY_ZONE_CITY
};

/**
 * <!-- reg-control keynum=8, value=enum -->
 * @brief it stands for sim initialization status
 */
#define VCONFKEY_TELEPHONY_SIM_INIT VCONFKEY_TELEPHONY_PREFIX"/sim_init"
enum {
	VCONFKEY_TELEPHONY_SIM_INIT_NONE = 0x00,
	VCONFKEY_TELEPHONY_SIM_INIT_COMPLETED
};

/**
 * <!-- reg-control keynum=9, value=enum -->
 * @brief it stands for current sim is needed several lock verification or not
 */
#define VCONFKEY_TELEPHONY_SIM_CHV VCONFKEY_TELEPHONY_PREFIX"/sim_chv"
enum {
	VCONFKEY_TELEPHONY_SIM_CHV_NONE = 0x00,
	VCONFKEY_TELEPHONY_SIM_CHV_REQUIRED
};

/**
 * <!-- reg-control keynum=10, value=enum -->
 * @brief it stands for current device has SIM or not
 */
#define VCONFKEY_TELEPHONY_SIM_SLOT VCONFKEY_TELEPHONY_PREFIX"/sim_slot"
enum {
	VCONFKEY_TELEPHONY_SIM_UNKNOWN = 0x00,
	VCONFKEY_TELEPHONY_SIM_INSERTED,
	VCONFKEY_TELEPHONY_SIM_NOT_PRESENT,
	VCONFKEY_TELEPHONY_SIM_CARD_ERROR
};

/**
 * <!-- reg-control keynum=11, value=enum -->
 * @brief it stands for current telephony phonebook is ready to give valid value or not
 */
#define VCONFKEY_TELEPHONY_SIM_PB_INIT VCONFKEY_TELEPHONY_PREFIX"/pb_init"
enum {
	VCONFKEY_TELEPHONY_SIM_PB_INIT_NONE = 0x00,
	VCONFKEY_TELEPHONY_SIM_PB_INIT_COMPLETED
};

/**
 * <!-- reg-control keynum=12, value=enum -->
 * @brief it stands for current call status ( idle, connect, held )
 */
#define VCONFKEY_TELEPHONY_CALL_STATE VCONFKEY_TELEPHONY_PREFIX"/call_state"
enum {
	VCONFKEY_TELEPHONY_CALL_CONNECT_IDLE = 0x00,
	VCONFKEY_TELEPHONY_CALL_CONNECT_ACTIVE,
	VCONFKEY_TELEPHONY_CALL_CONNECT_HELD
};

#define VCONFKEY_TELEPHONY_CALL_FORWARD_STATE VCONFKEY_TELEPHONY_PREFIX"/call_forward_state"
enum {
	VCONFKEY_TELEPHONY_CALL_FORWARD_OFF = 0x00,
	VCONFKEY_TELEPHONY_CALL_FORWARD_ON = 0x01
};

/**
 * <!-- reg-control keynum=13, value=enum -->
 * @brief it stands for current telephony apis is ready to use or not
 */
#define VCONFKEY_TELEPHONY_TAPI_STATE VCONFKEY_TELEPHONY_PREFIX"/tapi_state"
enum {
	VCONFKEY_TELEPHONY_TAPI_STATE_NONE = 0x00,
	VCONFKEY_TELEPHONY_TAPI_STATE_READY
};

/**
 * <!-- reg-control keynum=14, value=enum -->
 * @brief it stands for display priority between SIM SPN and PLMN
 */
#define VCONFKEY_TELEPHONY_SPN_DISP_CONDITION VCONFKEY_TELEPHONY_PREFIX"/spn_disp_condition"
enum {
	VCONFKEY_TELEPHONY_DISP_INVALID = 0x00,
	VCONFKEY_TELEPHONY_DISP_SPN,
	VCONFKEY_TELEPHONY_DISP_PLMN,
	VCONFKEY_TELEPHONY_DISP_SPN_PLMN
};

/**
 * <!-- reg-control keynum=15, value=string -->
 * @brief it stands for SPN name which is stored in SIM card
 */
#define VCONFKEY_TELEPHONY_SPN_NAME VCONFKEY_TELEPHONY_PREFIX"/spn"

#define VCONFKEY_TELEPHONY_SAT_IDLE_SCREEN_EVENT VCONFKEY_TELEPHONY_PREFIX"/sat_idle"
enum {
	VCONFKEY_TELEPHONY_SAT_EVENT_DISABLED,
	VCONFKEY_TELEPHONY_SAT_EVENT_ENABLED
};

#define VCONFKEY_TELEPHONY_SAT_STATE VCONFKEY_TELEPHONY_PREFIX"/sat_state"
enum {
	VCONFKEY_TELEPHONY_SAT_NONE = 0x00,
	VCONFKEY_TELEPHONY_SAT_READY
};

#define VCONFKEY_TELEPHONY_SAT_SETUP_IDLE_TEXT VCONFKEY_TELEPHONY_PREFIX"/idle_text"

#define VCONFKEY_TELEPHONY_ZONE_ZUHAUSE VCONFKEY_TELEPHONY_PREFIX"/zuhause_zone"

/**
 * <!-- reg-control keynum=16, value=enum -->
 * @brief it stands for current network RSSI strength
 */
#define VCONFKEY_TELEPHONY_RSSI VCONFKEY_TELEPHONY_PREFIX"/rssi"
enum {
	VCONFKEY_TELEPHONY_RSSI_0 = 0x00,
	VCONFKEY_TELEPHONY_RSSI_1,
	VCONFKEY_TELEPHONY_RSSI_2,
	VCONFKEY_TELEPHONY_RSSI_3,
	VCONFKEY_TELEPHONY_RSSI_4,
	VCONFKEY_TELEPHONY_RSSI_5,
	VCONFKEY_TELEPHONY_RSSI_6
};

#define VCONFKEY_TELEPHONY_LOW_BATTERY VCONFKEY_TELEPHONY_PREFIX"/low_battery"
enum {
	VCONFKEY_TELEPHONY_BATT_POWER_OFF_LEVEL = 0x01,
	VCONFKEY_TELEPHONY_BATT_CRIT_LOW_LEVEL,
	VCONFKEY_TELEPHONY_BATT_LOW_LEVEL,
	VCONFKEY_TELEPHONY_BATT_NORMAL_LEVEL
};

#define VCONFKEY_TELEPHONY_IMEI VCONFKEY_TELEPHONY_PREFIX"/imei"

/**
 * <!-- reg-control keynum=17, value=string -->
 * @brief it stands for current inserted SIM number. This value is optional
 */
#define VCONFKEY_TELEPHONY_SUBSCRIBER_NUMBER VCONFKEY_TELEPHONY_PREFIX"/szSubscriberNumber"

/**
 * <!-- reg-control keynum=18, value=string -->
 * @brief it stands for current inserted SIM name. This value is optional
 */
#define VCONFKEY_TELEPHONY_SUBSCRIBER_NAME VCONFKEY_TELEPHONY_PREFIX"/szSubscriberAlpha"

#define VCONFKEY_TELEPHONY_IMEI_FACTORY_REBOOT VCONFKEY_TELEPHONY_PREFIX"/bFactoryProcess"	/* int 0:fail, 1:success */
enum {
	VCONFKEY_TELEPHONY_FACTORYMODE_OFF = 0x00,
	VCONFKEY_TELEPHONY_FACTORYMODE_ON = 0x01
};

#define VCONFKEY_TELEPHONY_SIM_FACTORY_MODE VCONFKEY_TELEPHONY_PREFIX"/bIMSIFactoryProcess"	/* int 0:normal, 1:factory sim */
enum {
	VCONFKEY_TELEPHONY_SIM_FACTORYMODE_OFF = 0x00,
	VCONFKEY_TELEPHONY_SIM_FACTORYMODE_ON = 0x01
};

#define VCONFKEY_TELEPHONY_SWVERSION VCONFKEY_TELEPHONY_PREFIX"/szSWVersion"	/* string */

#define VCONFKEY_TELEPHONY_HWVERSION VCONFKEY_TELEPHONY_PREFIX"/szHWVersion"	/* string */

#define VCONFKEY_TELEPHONY_CALDATE VCONFKEY_TELEPHONY_PREFIX"/szCalDate"	/* string */

#define VCONFKEY_TELEPHONY_PRODUCTCODE VCONFKEY_TELEPHONY_PREFIX"/productCode"	/* string */

/* Factory key string block, by Youngman Park <youngman.park@samsung.com> */
#define VCONFKEY_TELEPHONY_DB_PREFIX "db/telephony"
#define VCONFKEY_TELEPHONY_FACTORY_KSTRINGB VCONFKEY_TELEPHONY_DB_PREFIX"/bKeyStringBlock"
enum {
	VCONFKEY_TELEPHONY_FACTORY_KSTRINGB_OFF = 0x00,
	VCONFKEY_TELEPHONY_FACTORY_KSTRINGB_ON = 0x01
};

/**
 * @}
 */

/* ============================ SAT Keys & Values ============================*/
/**
 * @defgroup vconf_key_sat Sim Application Toolkit Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_sat SAT
 * @{
 * @brief Maintainer : sunghyuk.lee@samsung.com
 */
#define VCONFKEY_SAT_PREFIX "memory/sat"

 /**
 * <!-- reg-control keynum=0, value=string -->
 * @brief It contains a text string which is provided by SETUP IDLE MODE TEXT command from SATK
 */
#define VCONFKEY_SAT_IDLE_TEXT    VCONFKEY_SAT_PREFIX"/idle_text"

/**
 * @}
 */
/* ============================ Message Keys & Values ============================*/
/**
 * @defgroup vconf_key_Message Message Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Message
 * @{
 * @brief Maintainer : cw1218.kim@samsung.com
 */
/* [DO NOT UPDATE THIS] */
#define VCONFKEY_MSG_MEMORY_PREFIX			"memory/msg"
#define VCONFKEY_MSG_DB_PREFIX				"db/msg"
#define VCONFKEY_MSG_SERVER_READY			VCONFKEY_MSG_MEMORY_PREFIX"/ready"
#define VCONFKEY_MSG_STATUS_CHANGED_CONTACTID		VCONFKEY_MSG_MEMORY_PREFIX"/contact_id"

#define VCONFKEY_MESSAGE_RECV_SMS_STATE			VCONFKEY_MSG_DB_PREFIX"/recv_sms"
#define VCONFKEY_MESSAGE_RECV_MMS_STATE			VCONFKEY_MSG_DB_PREFIX"/recv_mms"
#define VCONFKEY_MESSAGE_RECV_DELREP_STATE		VCONFKEY_MSG_DB_PREFIX"/recv_delrep"
#define VCONFKEY_MESSAGE_RECV_READREP_STATE		VCONFKEY_MSG_DB_PREFIX"/recv_readrep"
#define VCONFKEY_MESSAGE_RECV_VOICEMAIL_STATE		VCONFKEY_MSG_DB_PREFIX"/recv_voicemail"
#define VCONFKEY_MESSAGE_RECV_MMS_NOTI_STATE		VCONFKEY_MSG_DB_PREFIX"/recv_mms_noti"
#define VCONFKEY_MESSAGE_NETWORK_MODE			VCONFKEY_MSG_DB_PREFIX"/network_mode"

enum {
	VCONFKEY_MESSAGE_NETWORK_PS_ONLY = 0x01,
	VCONFKEY_MESSAGE_NETWORK_CS_ONLY = 0x02,
	VCONFKEY_MESSAGE_NETWORK_PS_PREFER = 0x03,
	VCONFKEY_MESSAGE_NETWORK_CS_PREFER = 0x04
};

/**
 * @}
 */

/* ============================ Email Service Keys & Values ============================*/
/**
 * @defgroup vconf_key_EmailService Email service Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_EmailService
 * @{
 * @brief Maintainer : ch715.lee@samsung.com
 */

#define VCONFKEY_EMAIL_SERVICE_PREFIX	"db/email"

#define VCONFKEY_EMAIL_SERVICE_UNREAD	VCONFKEY_EMAIL_SERVICE_PREFIX"/unread"

/**
 * @}
 */

/* ============================ FileManager Service Keys & Values ============================*/
/**
 * @defgroup vconf_key_FileManagerService FileManager Service Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_FileManagerService
 * @{
 * @brief Maintainer : yy9875.kim@samsung.com
 */

#define VCONFKEY_FILEMANAGER_MMC_STATUS		"memory/filemanager/Mmc"
enum {
	VCONFKEY_FILEMANAGER_MMC_REMOVED = 0,
	VCONFKEY_FILEMANAGER_MMC_LOADING,
	VCONFKEY_FILEMANAGER_MMC_LOADED,
	VCONFKEY_FILEMANAGER_MMC_FULL
};

#define VCONFKEY_FILEMANAGER_DB_STATUS    "db/filemanager/dbupdate"
enum {
	VCONFKEY_FILEMANAGER_DB_UPDATING = 0,
	VCONFKEY_FILEMANAGER_DB_UPDATED
};

/**
 * @}
 */

/* ============================ Instant Message Keys & Values ============================*/
/**
 * @defgroup vconf_key_IM Instant Message Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_IM
 * @{
 * @brief Maintainer : nosweet7958@gmail.com
 */
#define VCONFKEY_IM_RECV_UNREAD    "db/im/recv_unread"
/**
 * @}
 */

/* ============================ Seven Email Keys & Values ============================*/
/**
 * @defgroup vconf_key_seven_email Seven Email Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_seven_email
 * @{
 * @brief Maintainer : nosweet7958@gmail.com
 */
#define VCONFKEY_SEVEN_EMAIL_RECV_UNREAD    "db/seven-email/recv_unread"
/**
 * @}
 */

/* =========================== QuickPanel Keys for indicator deamon ========================*/
/**
 * @defgroup vconf_key_QuickPanel QuickPanel Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_QuickPanel
 * @{
 * @brief Maintainer : hyunsil.park@samsung.com
 */
#define VCONFKEY_QUICKPANEL_WIFI					"memory/quickpanel/wifi"
#define VCONFKEY_QUICKPANEL_BLUETOOTH			"memory/quickpanel/bluetooth"
#define VCONFKEY_QUICKPANEL_GPS						"memory/quickpanel/gps"
#define VCONFKEY_QUICKPANEL_SILENTMODE		"memory/quickpanel/silentmode"

#define VCONFKEY_QUICKPANEL_MUSIC					"memory/quickpanel/music"
#define VCONFKEY_QUICKPANEL_RADIO					"memory/quickpanel/radio"
#define VCONFKEY_QUICKPANEL_VOICERECORDER	"memory/quickpanel/voicerecorder"
#define VCONFKEY_QUICKPANEL_NOTI					"memory/quickpanel/noti"

#define VCONFKEY_QUICKPANEL_REQ_NOTI_LIST	"memory/quickpanel/req_noti_list"

#define VCONFKEY_QUICKPANEL_SET_STATE					"memory/quickpanel/set_state"
#define VCONFKEY_QUICKPANEL_CUR_STATE					"memory/quickpanel/cur_state"

#define VCONFKEY_QUICKPANEL_SHOW_MISSED_CALL				"db/quickpanel/show_missed_call"
#define VCONFKEY_QUICKPANEL_SHOW_SMS								"db/quickpanel/show_sms"
#define VCONFKEY_QUICKPANEL_SHOW_MMS								"db/quickpanel/show_mms"
#define VCONFKEY_QUICKPANEL_SHOW_MMS_NOTI						"db/quickpanel/show_mms_noti"
#define VCONFKEY_QUICKPANEL_SHOW_VOICE_MAIL					"db/quickpanel/show_voice_mail"
#define VCONFKEY_QUICKPANEL_SHOW_DELIVERY_REPORT		"db/quickpanel/show_delivery_report"
#define VCONFKEY_QUICKPANEL_SHOW_READ_REPORT				"db/quickpanel/show_read_report"
#define VCONFKEY_QUICKPANEL_SHOW_IM									"db/quickpanel/show_im"
#define VCONFKEY_QUICKPANEL_SHOW_EMAIL							"db/quickpanel/show_email"
#define VCONFKEY_QUICKPANEL_SHOW_SEVEN_EMAIL				"db/quickpanel/show_seven_email"

#define VCONFKEY_QUICKPANEL_COMMUNITIES_UPLOAD_STATE "memory/quickpanel/communities_upload_state"
enum {
	VCONFKEY_QUICKPANEL_UPLOAD_START = 0x00,
	VCONFKEY_QUICKPANEL_UPLOAD_FAIL,
	VCONFKEY_QUICKPANEL_UPLOAD_FINISH
};

#define VCONFKEY_QUICKPANEL_COMMUNITIES_DOWNLOAD_STATE "memory/quickpanel/communities_download_state"
enum {
	VCONFKEY_QUICKPANEL_DOWNLOAD_START = 0x00,
	VCONFKEY_QUICKPANEL_DOWNLOAD_FAIL,
	VCONFKEY_QUICKPANEL_DOWNLOAD_FINISH
};

enum {
	VCONFKEY_QUICKPANEL_STATE_HIDE = 0x00,
	VCONFKEY_QUICKPANEL_STATE_SHOW,
	VCONFKEY_QUICKPANEL_STATE_MAX
};

enum {
	VCONFKEY_QUICKPANEL_DEFAULT_OFF = 0x00,
	VCONFKEY_QUICKPANEL_DEFAULT_ON,
	VCONFKEY_QUICKPANEL_DEFAULT_MAX
};

enum {
	VCONFKEY_QUICKPANEL_MUSIC_STATE = 0x00,
	VCONFKEY_QUICKPANEL_MUSIC_REW,
	VCONFKEY_QUICKPANEL_MUSIC_PAUSE,
	VCONFKEY_QUICKPANEL_MUSIC_PLAY,
	VCONFKEY_QUICKPANEL_MUSIC_FF,
	VCONFKEY_QUICKPANEL_MUSIC_IDLE,
	VCONFKEY_QUICKPANEL_MUSIC_MAX
};

enum {
	VCONFKEY_QUICKPANEL_RADIO_STATE = 0x00,
	VCONFKEY_QUICKPANEL_RADIO_REW,
	VCONFKEY_QUICKPANEL_RADIO_PAUSE,
	VCONFKEY_QUICKPANEL_RADIO_PLAY,
	VCONFKEY_QUICKPANEL_RADIO_FF,
	VCONFKEY_QUICKPANEL_RADIO_MAX
};

enum {
	VCONFKEY_QUICKPANEL_VOICERECORDER_STATE = 0x00,
	VCONFKEY_QUICKPANEL_VOICERECORDER_REC,
	VCONFKEY_QUICKPANEL_VOICERECORDER_PAUSE,
	VCONFKEY_QUICKPANEL_VOICERECORDER_SAVE,
	VCONFKEY_QUICKPANEL_VOICERECORDER_MAX
};

/* =========================== QuickPanel Keys for applications   ===========================*/
/* Maintainer : hyunsil.park@samsung.com */
#define VCONFKEY_QUICKPANEL_RADIO_STR				"memory/quickpanel/radio_str"
#define VCONFKEY_QUICKPANEL_RADIO_STATE			"memory/quickpanel/radio_state"
#define VCONFKEY_QUICKPANEL_MUSIC_STR				"memory/quickpanel/music_str"
#define VCONFKEY_QUICKPANEL_MUSIC_STATE			"memory/quickpanel/music_state"
#define VCONFKEY_QUICKPANEL_VISIBLE_STATE		"memory/quickpanel/visible_state"

enum {
	VCONFKEY_QUICKPANEL_VISIBLE_ON = 0x00,
	VCONFKEY_QUICKPANEL_VISIBLE_OFF,
	VCONFKEY_QUICKPANEL_VISIBLE_MAX
};
/**
 * @}
 */

/* ============================ Debug Level ============================*/
/**
 * @defgroup vconf_key_DebugLevel Debug Level Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_DebugLevel
 * @{
 * @brief Maintainer : yk.yun@samsung.com
 */
#define VCONFKEY_DEBUG_LEVEL     "db/debug/level"
enum {
	VCONFKEY_DEBUG_LEVEL_LOW = 0,
	VCONFKEY_DEBUG_LEVEL_MIDDLE,
	VCONFKEY_DEBUG_LEVEL_HIGH
};
/**
 * @}
 */

/* ============================ Testmode Keys ============================*/
/**
 * @defgroup vconf_key_Testmode Testmode Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Testmode
 * @{
 * @brief Maintainer : sena06.kim@samsung.com
 */
#define VCONFKEY_TESTMODE_PREFIX    "db/testmode"
enum {
	VCONFKEY_TESTMODE_OFF = 0,
	VCONFKEY_TESTMODE_ON
};

#define VCONFKEY_TESTMODE_AUTO_ANSWER		VCONFKEY_TESTMODE_PREFIX"/auto_answer"

#define VCONFKEY_TESTMODE_VT_CAM_SETTING	VCONFKEY_TESTMODE_PREFIX"/vt_cam_setting"
enum {
	VCONFKEY_TESTMODE_CAM_FRONT = 0,
	VCONFKEY_TESTMODE_CAM_EXTERNAL,
	VCONFKEY_TESTMODE_CAM_MAX
};

/**
 * @}
 */

/* ============================ Admin Keys & Values ============================*/
/**
 * @defgroup vconf_key_Launcher Launcher Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Launcher
 * @{
 * @brief Maintainer : jinny.yoon@samsung.com, sena06.kim@samsung.com
 */
#define VCONFKEY_ADMIN_THEME_SET	"file/launcher/theme-set"
enum {
	VCONFKEY_ADMIN_THEME_DEFAULT = 0,
	VCONFKEY_ADMIN_THEME_BLACK,
	VCONFKEY_ADMIN_THEME_MAX
};

#define VCONFKEY_ADMIN_PREFIX				"db/admin"

#define VCONFKEY_ADMIN_PRE_CONFIGURATION		VCONFKEY_ADMIN_PREFIX"/preconfiguration"
#define VCONFKEY_ADMIN_INTNL_JAVA_AUTOTEST_URL		VCONFKEY_ADMIN_PREFIX"/autotest_url"
#define VCONFKEY_ADMIN_UAGENT				VCONFKEY_ADMIN_PREFIX"/uagent"
#define VCONFKEY_ADMIN_UAPROF_URL_2G			VCONFKEY_ADMIN_PREFIX"/uaprof_url_2g"
#define VCONFKEY_ADMIN_UAPROF_URL_3G			VCONFKEY_ADMIN_PREFIX"/uaprof_url_3g"
#define VCONFKEY_ADMIN_GCF_TEST				VCONFKEY_ADMIN_PREFIX"/gcf_test"
enum {
	VCONFKEY_ADMIN_GCF_OFF = 0,
	VCONFKEY_ADMIN_GCF_ON
};
/**
 * @}
 */

/* =========================== Menu Screen Keys  ================================*/
/**
 * @defgroup vconf_key_menu_screen
 * @ingroup vconf_key
 * @addtogroup vconf_key_menu_screen
 * @{
 * @brief Maintainer : jinny.yoon@samsung.com
 */

/* Maintainer : jinny.yoon@samsung.com */
#define VCONFKEY_LAUNCH_EFFECT			"db/menu_widget/launch_effect"
#define VCONFKEY_BGSET				"db/menu_widget/bgset"
#define VCONFKEY_LANGSET			"db/menu_widget/language"
#define VCONFKEY_SIM_LOCK			"file/menu_widget/simlock"
#define VCONFKEY_PKGMGR_UPDATE			"file/menu_widget/pkgmgr"
#define VCONFKEY_VIEW_CHANGE			"file/menu_widget/view"
#define VCONFKEY_REGIONFORMAT			"db/menu_widget/regionformat"
#define VCONFKEY_REGIONFORMAT_TIME1224		"db/menu_widget/regionformat_time1224"
enum {
	VCONFKEY_TIME_FORMAT_12 = 1,
	VCONFKEY_TIME_FORMAT_24
};
/**
 * @}
 */

/* ============================ Idle screen (currently menu-screen) ============================*/
/**
 * @defgroup vconf_key_idle_screen
 * @ingroup vconf_key
 * @addtogroup vconf_key_idle_screen
 * @{
 * @brief Maintainer : jinny.yoon@samsung.com
 */
#define VCONFKEY_IDLE_SCREEN_TOP "memory/idle_screen/top"
enum {
	VCONFKEY_IDLE_SCREEN_TOP_FALSE = 0x00,
	VCONFKEY_IDLE_SCREEN_TOP_TRUE
};
/**
 * @}
 */

/* ============================ Media Transfer Protocol Keys & Values ============================*/
/**
 * @defgroup vconf_key_MTP MTP Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_MTP
 * @{
 * @brief Maintainer : daehyung.jo@samsung.com
 */
#define VCONFKEY_MTP_STATUS	"memory/mtp/working"
enum {
	VCONFKEY_MTP_OFF = 0,
	VCONFKEY_MTP_ON,
	VCONFKEY_MTP_MAX
};
/**
 * @}
 */

/* ========================== System Manager Notification ============================= */
/**
 * @defgroup vconf_key_SystemManager System Manager Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_SystemManager
 * @{
 * @brief Maintainer : wonil22.choi@samsung.com, jinkun.jang@samsung.com
 */

/**
 * <!-- reg-control keynum=19, value=int -->
 * @brief Remaining battery level. Value: 0(Min) ~ 5(Max)
 */
#define VCONFKEY_SYSMAN_BATTERY_LEVEL			"memory/Battery/Level"
enum {
	VCONFKEY_SYSMAN_BAT_LEVEL_MIN = 0,
	VCONFKEY_SYSMAN_BAT_LEVEL0 = 0,
	VCONFKEY_SYSMAN_BAT_LEVEL1,
	VCONFKEY_SYSMAN_BAT_LEVEL2,
	VCONFKEY_SYSMAN_BAT_LEVEL3,
	VCONFKEY_SYSMAN_BAT_LEVEL4,
	VCONFKEY_SYSMAN_BAT_LEVEL5,
	VCONFKEY_SYSMAN_BAT_LEVEL6,
	VCONFKEY_SYSMAN_BAT_LEVEL_MAX = 6
};

/**
 * <!-- reg-control keynum=20, value=int -->
 * @brief Charger status. Value: 1(charging) or 0(not)
 */
#define VCONFKEY_SYSMAN_BATTERY_CHARGE_NOW			"memory/Battery/Charger"

/**
 * <!-- reg-control keynum=21, value=enum -->
 * @brief It indicates current battery low status
 */
#define VCONFKEY_SYSMAN_BATTERY_STATUS_LOW		"memory/Battery/Status/Low"
enum {
	VCONFKEY_SYSMAN_BAT_POWER_OFF = 1,
	VCONFKEY_SYSMAN_BAT_CRITICAL_LOW,
	VCONFKEY_SYSMAN_BAT_WARNING_LOW,
	VCONFKEY_SYSMAN_BAT_NORMAL
};

#define VCONFKEY_SYSMAN_BATTERY_CAPACITY        "memory/Battery/Capacity"

/**
 * <!-- reg-control keynum=22, value=enum -->
 * @brief USB connection status
 */
#define VCONFKEY_SYSMAN_USB_STATUS				"memory/Connectivity/USB"
enum {
	VCONFKEY_SYSMAN_USB_DISCONNECTED = 0,
	VCONFKEY_SYSMAN_USB_CONNECTED,
	VCONFKEY_SYSMAN_USB_AVAILABLE
};

#define VCONFKEY_SYSMAN_USB_CONN_MODE			"memory/Connectivity/USB_mode"
enum {
	VCONFKEY_SYSMAN_USB_MODE_UMS_NONE = 0,
	VCONFKEY_SYSMAN_USB_MODE_UMS_PHONE,
	VCONFKEY_SYSMAN_USB_MODE_UMS_MMC
};

#define VCONFKEY_SYSMAN_USB_HOST_STATUS			"memory/Device/usbhost/status"
enum {
         VCONFKEY_SYSMEN_USB_HOST_DISCONNECTED = 0,
         VCONFKEY_SYSMEN_USB_HOST_CONNECTED
};

/**
 * <!-- reg-control keynum=23, value=enum -->
 * @brief It indicates MMC card
 */
#define VCONFKEY_SYSMAN_MMC_STATUS				"memory/Device/Mmc"
enum {
	VCONFKEY_SYSMAN_MMC_REMOVED = 0,
	VCONFKEY_SYSMAN_MMC_MOUNTED,
	VCONFKEY_SYSMAN_MMC_INSERTED_NOT_MOUNTED
};

#define VCONFKEY_SYSMAN_LCD_TIMEOUT_NORMAL		"db/MainLCD/Backlight/Normal"
#define VCONFKEY_SYSMAN_LCD_TIMEOUT_DIM			"db/MainLCD/Backlight/Dim"
#define VCONFKEY_SYSMAN_LCD_BRIGHTNESS			"db/Device/LCD/Brightness"

/**
 * <!-- reg-control keynum=24, value=enum -->
 * @brief Earjack connection status
 */
#define VCONFKEY_SYSMAN_EARJACK				"memory/Device/EarJack"
enum {
	VCONFKEY_SYSMAN_EARJACK_REMOVED = 0,
	VCONFKEY_SYSMAN_EARJACK_3WIRE = 0x1,
	VCONFKEY_SYSMAN_EARJACK_4WIRE = 0x3,
	VCONFKEY_SYSMAN_EARJACK_TVOUT = 0x10
};

#define VCONFKEY_SYSMAN_EARJACKKEY				"memory/Device/EarJackKey"

/**
 * <!-- reg-control keynum=25, value=enum -->
 * @brief Current low-memory status
 */
#define VCONFKEY_SYSMAN_LOW_MEMORY				"memory/sysman/low_memory"
enum {
	VCONFKEY_SYSMAN_LOW_MEMORY_NORMAL = 0x01,
	VCONFKEY_SYSMAN_LOW_MEMORY_SOFT_WARNING = 0x02,
	VCONFKEY_SYSMAN_LOW_MEMORY_HARD_WARNING = 0x04
};

#define VCONFKEY_SYSMAN_CRADLE_STATUS                  "memory/Device/Cradle/Status"

/* requested by dg0402.jang for USB-Host USB Storage Mount. 2011-07-21 */
#define VCONFKEY_SYSMAN_ADDED_USB_STORAGE              "memory/Device/usbhost/added_storage"
#define VCONFKEY_SYSMAN_REMOVED_USB_STORAGE            "memory/Device/usbhost/removed_storage"

/**
 * @}
 */

/* ========================== Power Manager Notification ============================= */
/**
 * @defgroup vconf_key_PowerManager Power Manager Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_PowerManager
 * @{
 * @brief Maintainer : wonil22.choi@samsung.com
 */

/**
 * <!-- reg-control keynum=26, value=enum -->
 * @brief It saves Phone's power managing state
 */
#define VCONFKEY_PM_STATE				"memory/pwrmgr/state"
enum {
	VCONFKEY_PM_STATE_NORMAL = 1,
	VCONFKEY_PM_STATE_LCDDIM,
	VCONFKEY_PM_STATE_LCDOFF,
	VCONFKEY_PM_STATE_SLEEP
};

/**
 * @}
 */

/* ========================== For Setting UI============================= */
/**
 * @defgroup vconf_key_SettingUI Setting application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_SettingUI
 * @{
 * @brief Maintainer : jy0214.kim@samsung.com
 */
#define VCONFKEY_SEL_USB_MODE	"db/setting/sel_usb"

#define VCONFKEY_SETAPPL_PREFIX  "db/setting"
#define VCONFKEY_SETAPPL_MEM_PREFIX  "memory/setting"

/* main setting*/
#define VCONFKEY_SETAPPL_FLIGHT_MODE_BOOL VCONFKEY_SETAPPL_PREFIX"/flight_mode"

/* rotate lock */
#define VCONFKEY_SETAPPL_ROTATE_LOCK_BOOL VCONFKEY_SETAPPL_PREFIX"/rotate_lock"

/* entry widget */
#define VCONFKEY_SETAPPL_AUTOCAPITAL_ALLOW_BOOL VCONFKEY_SETAPPL_PREFIX"/autocapital_allow"
#define VCONFKEY_SETAPPL_AUTOPERIOD_ALLOW_BOOL VCONFKEY_SETAPPL_PREFIX"/autoperiod_allow"

/*------------------------------------------> VCONF keys from here will be removed on 2nd week of Mar.*/
/* sound profile */
#define VCONFKEY_SETAPPL_CUR_PROFILE_INT		VCONFKEY_SETAPPL_PREFIX"/cur_profile"
#define VCONFKEY_SETAPPL_PREV_PROFILE_INT		VCONFKEY_SETAPPL_PREFIX"/prev_profile"

/*<------------------------------------------ VCONF keys to here will be removed on 2nd week of Mar.*/

/* setting > sound requested by hyejin0906.kim (20110608) */
#define VCONFKEY_SETAPPL_SOUND_LOCK_BOOL                VCONFKEY_SETAPPL_PREFIX"/sound/sound_lock"
#define VCONFKEY_SETAPPL_KEYPAD_STATUS_BOOL             VCONFKEY_SETAPPL_PREFIX"/sound/keypad_on"
#define VCONFKEY_SETAPPL_SOUND_EFFECT_BOOL              VCONFKEY_SETAPPL_PREFIX"/sound/sound_effect_on"

/* setting > sound requested by hyejin0906.kim (20010629) */
#define VCONFKEY_SETAPPL_MEDIA_SOUND_VOLUME_INT         VCONFKEY_SETAPPL_PREFIX"/sound/media/sound_volume"

/* Widget Theme	*/
#define VCONFKEY_SETAPPL_WIDGET_THEME_STR               VCONFKEY_SETAPPL_PREFIX"/widget_theme"

/* Brightness setting requested by mj2004.park */
#define VCONFKEY_SETAPPL_LCD_BRIGHTNESS			VCONFKEY_SETAPPL_PREFIX"/Brightness"

/* device name key requested by mj2004.park */
#define VCONFKEY_SETAPPL_DEVICE_NAME_STR		VCONFKEY_SETAPPL_PREFIX"/device_name"

/*------------------------------------------> VCONF keys from here will be removed on 2nd week of Mar.*/
enum {
	SETTING_PROFILE_NORMAL = 0,
	SETTING_PROFILE_SILENT,
	SETTING_PROFILE_DRIVING,
	SETTING_PROFILE_MEETING,
	SETTING_PROFILE_OUTDOOR,
	SETTING_PROFILE_FLIGHT,
	SETTING_PROFILE_MAX
};

/* normal profile */
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/normal/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/normal/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/normal/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/normal/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/normal/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/normal/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/normal/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/normal/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/normal/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/normal/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_NORMAL_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/normal/sys_volume"

/* silent profile */
#define VCONFKEY_SETAPPL_PROFILE_SILENT_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/silent/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/silent/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/silent/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/silent/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/silent/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/silent/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/silent/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/silent/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/silent/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/silent/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_SILENT_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/silent/sys_volume"

/*Driving Profile */
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/driving/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/driving/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/driving/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/driving/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/driving/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/driving/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/driving/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/driving/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/driving/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/driving/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_DRIVING_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/driving/sys_volume"

/* Meeting Profile */
#define VCONFKEY_SETAPPL_PROFILE_MEETING_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/meeting/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/meeting/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/meeting/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/meeting/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/meeting/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/meeting/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/meeting/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/meeting/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/meeting/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/meeting/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_MEETING_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/meeting/sys_volume"

/* Outdoor Profile */
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/outdoor/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/outdoor/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/outdoor/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/outdoor/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/outdoor/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/outdoor/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/outdoor/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/outdoor/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/outdoor/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/outdoor/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_OUTDOOR_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/outdoor/sys_volume"

/* Current Profile */
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_CALL_ALERT_TYPE_INT VCONFKEY_SETAPPL_PREFIX"/current/call_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_CALL_TONE_PATH_STR  VCONFKEY_SETAPPL_PREFIX"/current/call_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_CALL_ALERT_VIB_INT  VCONFKEY_SETAPPL_PREFIX"/current/call_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_CALL_VOLUME_INT     VCONFKEY_SETAPPL_PREFIX"/current/call_volume"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_MSG_ALERT_TYPE_INT  VCONFKEY_SETAPPL_PREFIX"/current/msg_alert_type"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_MSG_TONE_PATH_STR   VCONFKEY_SETAPPL_PREFIX"/current/msg_tone_path"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_MSG_ALERT_VIB_INT   VCONFKEY_SETAPPL_PREFIX"/current/msg_alert_vib"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_MSG_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/current/msg_volume"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_MSG_REPETITION_INT  VCONFKEY_SETAPPL_PREFIX"/current/msg_repetition"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_SYS_TOUCH_SOUND_INT VCONFKEY_SETAPPL_PREFIX"/current/sys_touch_sound"
#define VCONFKEY_SETAPPL_PROFILE_CURRENT_SYS_VOLUME_INT      VCONFKEY_SETAPPL_PREFIX"/current/sys_volume"
/*<------------------------------------------ VCONF keys to here will be removed on 2nd week of Mar.*/

/*------------------------------------------> New VCONF keys for sound setting.*/
enum {
	SETTING_SOUND_REP_ONCE = 0,
	SETTING_SOUND_REP_EVERY_2_MIN,
	SETTING_SOUND_REP_EVERY_5_MIN,
	SETTING_SOUND_REP_EVERY_10_MIN
};

#define VCONFKEY_SETAPPL_DEFAULT_CALL_RINGTONE_PATH_STR			VCONFKEY_SETAPPL_PREFIX"/sound/call/default_ringtone_path"
#define VCONFKEY_SETAPPL_DEFAULT_NOTI_MSG_RINGTONE_PATH_STR		VCONFKEY_SETAPPL_PREFIX"/sound/noti/default_msg_ringtone_path"
#define VCONFKEY_SETAPPL_DEFAULT_NOTI_EMAIL_RINGTONE_PATH_STR		VCONFKEY_SETAPPL_PREFIX"/sound/noti/default_email_ringtone_path"
#define VCONFKEY_SETAPPL_DEFAULT_NOTI_CALENDAR_RINGTONE_PATH_STR	VCONFKEY_SETAPPL_PREFIX"/sound/noti/default_calendar_ringtone_path"

#define VCONFKEY_SETAPPL_SOUND_STATUS_BOOL				VCONFKEY_SETAPPL_PREFIX"/sound/sound_on"
#define VCONFKEY_SETAPPL_VIBRATION_STATUS_BOOL				VCONFKEY_SETAPPL_PREFIX"/sound/vibration_on"
#define VCONFKEY_SETAPPL_USE_CALL_VOLUME_FOR_NOTI_BOOL			VCONFKEY_SETAPPL_PREFIX"/sound/use_call_volume_for_noti_on"
#define VCONFKEY_SETAPPL_CALL_RINGTONE_SOUND_VOLUME_INT			VCONFKEY_SETAPPL_PREFIX"/sound/call/ringtone_sound_volume"
#define VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR				VCONFKEY_SETAPPL_PREFIX"/sound/call/ringtone_path"
#define VCONFKEY_SETAPPL_CALL_VIBRATION_PATTERN_INT			VCONFKEY_SETAPPL_PREFIX"/sound/call/vibration_type"
#define VCONFKEY_SETAPPL_NOTI_SOUND_VOLUME_INT				VCONFKEY_SETAPPL_PREFIX"/sound/noti/sound_volume"
#define VCONFKEY_SETAPPL_NOTI_MSG_ALERT_REP_TYPE_INT			VCONFKEY_SETAPPL_PREFIX"/sound/noti/msg_alert_rep_type"
#define VCONFKEY_SETAPPL_NOTI_MSG_RINGTONE_PATH_STR			VCONFKEY_SETAPPL_PREFIX"/sound/noti/msg_ringtone_path"
#define VCONFKEY_SETAPPL_NOTI_EMAIL_ALERT_REP_TYPE_INT			VCONFKEY_SETAPPL_PREFIX"/sound/noti/email_alert_rep_type"
#define VCONFKEY_SETAPPL_NOTI_EMAIL_RINGTONE_PATH_STR			VCONFKEY_SETAPPL_PREFIX"/sound/noti/email_ringtone_path"
#define VCONFKEY_SETAPPL_NOTI_CALENDAR_ALERT_REP_TYPE_INT		VCONFKEY_SETAPPL_PREFIX"/sound/noti/calendar_alert_rep_type"
#define VCONFKEY_SETAPPL_NOTI_CALENDAR_RINGTONE_PATH_STR		VCONFKEY_SETAPPL_PREFIX"/sound/noti/calendar_ringtone_path"
#define VCONFKEY_SETAPPL_NOTI_VIBRATION_LEVEL_INT			VCONFKEY_SETAPPL_PREFIX"/sound/noti/vibration_level"
#define VCONFKEY_SETAPPL_TOUCH_FEEDBACK_SOUND_VOLUME_INT		VCONFKEY_SETAPPL_PREFIX"/sound/touch_feedback/sound_volume"
#define VCONFKEY_SETAPPL_TOUCH_FEEDBACK_VIBRATION_LEVEL_INT		VCONFKEY_SETAPPL_PREFIX"/sound/touch_feedback/vibration_level"
/*<------------------------------------------ New VCONF keys for sound setting.*/

/* USB-SETTING - ty317.kim */
#define VCONFKEY_SETAPPL_USB_IN_MODE_CHANGE         VCONFKEY_SETAPPL_MEM_PREFIX"/usb_in_mode_change"
#define VCONFKEY_SETAPPL_SELECT_POPUP_BTN_INT       VCONFKEY_SETAPPL_PREFIX"/select_popup_btn"

/* connectivity */
#define VCONFKEY_SETAPPL_USB_MODE_INT               VCONFKEY_SETAPPL_MEM_PREFIX"/usb_mode"
#define VCONFKEY_SETAPPL_USB_SEL_MODE_INT           VCONFKEY_SETAPPL_MEM_PREFIX"/usb_sel_mode"
#define VCONFKEY_SETAPPL_USB_DEBUG_MODE             VCONFKEY_SETAPPL_PREFIX"/usb_debugmode"
#define VCONFKEY_SETAPPL_SELECT_NETWORK_INT         VCONFKEY_SETAPPL_PREFIX"/select_network"
#define VCONFKEY_SETAPPL_NETWORK_MODE_INT           VCONFKEY_SETAPPL_PREFIX"/network_mode"
#define VCONFKEY_SETAPPL_ASK_ON_CONNECTION_BOOL     VCONFKEY_SETAPPL_PREFIX"/ask_on_con"
enum {
	SETTING_USB_NONE_MODE = -1,
	SETTING_USB_DEFAULT_MODE = 0,
	SETTING_USB_MASS_STORAGE,
	SETTING_USB_UNUSED_MODE,
	SETTING_USB_DEBUG_MODE,
};				/* connectivity - usb connection */

/* security */
#define VCONFKEY_SETAPPL_PHONE_PASSWD_STR			VCONFKEY_SETAPPL_PREFIX"/phone_passwd"
#define VCONFKEY_SETAPPL_PRIVACY_PASSWD_STR			VCONFKEY_SETAPPL_PREFIX"/privacy_passwd"
#define VCONFKEY_SETAPPL_PIN1_CODE_STR				VCONFKEY_SETAPPL_PREFIX"/pin1_code"
#define VCONFKEY_SETAPPL_PIN2_CODE_STR				VCONFKEY_SETAPPL_PREFIX"/pin2_code"
#define VCONFKEY_SETAPPL_SIM_ICCID_STR				VCONFKEY_SETAPPL_PREFIX"/sim_iccid"
#define VCONFKEY_SETAPPL_STATE_POWER_ON_LOCK_BOOL		VCONFKEY_SETAPPL_PREFIX"/power_on_lock"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_BOOL		VCONFKEY_SETAPPL_PREFIX"/privacy_lock_key"
#define VCONFKEY_SETAPPL_STATE_SIM_LOCK_BOOL			VCONFKEY_SETAPPL_PREFIX"/sim_lock"
#define VCONFKEY_SETAPPL_STATE_PIN_LOCK_BOOL			VCONFKEY_SETAPPL_PREFIX"/pin_lock"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_SELECT_ALL_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/select_all"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_MESSAGE_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/message"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_MY_FILES_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/my_files"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_CALL_LOG_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/call_log"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_CONTACT_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/contact"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_CALENDAR_BOOL	VCONFKEY_SETAPPL_PREFIX"/privacy_lock/calendar"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_MEMO_BOOL		VCONFKEY_SETAPPL_PREFIX"/privacy_lock/memo"
#define VCONFKEY_SETAPPL_STATE_PRIVACY_LOCK_EMAIL_BOOL		VCONFKEY_SETAPPL_PREFIX"/privacy_lock/email"
#define VCONFKEY_SETAPPL_STATE_FIXED_DIALING_MODE_BOOL		VCONFKEY_SETAPPL_PREFIX"/fixed_dialing_mode"
/* For security simple password menu by hyejin0906.kim */
#define VCONFKEY_SETAPPL_STATE_SIMPLE_PASSWORD_BOOL		VCONFKEY_SETAPPL_PREFIX"/simple_password"

/* Find my mobile by byonguk.lee */
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_SIM_CHANGE_ALERT_BOOL   VCONFKEY_SETAPPL_PREFIX"/fmm/sim_change_alert"
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_RECIPIENTS_STR          VCONFKEY_SETAPPL_PREFIX"/fmm/recipients"
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_SENDER_STR              VCONFKEY_SETAPPL_PREFIX"/fmm/sender"
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_MESSAGE_STR             VCONFKEY_SETAPPL_PREFIX"/fmm/alert_message"
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_REMOTE_CONTROL_BOOL     VCONFKEY_SETAPPL_PREFIX"/fmm/remote_control"
#define VCONFKEY_SETAPPL_FIND_MY_MOBILE_LOCATION_CONSENT_BOOL   VCONFKEY_SETAPPL_PREFIX"/fmm/location_consent"

/* mobile tracker */
#define VCONFKEY_SETAPPL_STATE_MOBILE_TRACKER_BOOL              VCONFKEY_SETAPPL_FIND_MY_MOBILE_SIM_CHANGE_ALERT_BOOL
#define VCONFKEY_SETAPPL_MOBILE_TRACKER_RECIPIENTS_STR          VCONFKEY_SETAPPL_FIND_MY_MOBILE_RECIPIENTS_STR
#define VCONFKEY_SETAPPL_MOBILE_TRACKER_SENDER_PHONE_STR        VCONFKEY_SETAPPL_FIND_MY_MOBILE_SENDER_STR
#define VCONFKEY_SETAPPL_MOBILE_TRACKER_MSG_STR                 VCONFKEY_SETAPPL_FIND_MY_MOBILE_MESSAGE_STR

#define VCONFKEY_SETAPPL_MOBILE_TRACKER_PHONE_LOCK_BOOL		VCONFKEY_SETAPPL_PREFIX"/mobile_tracker_phone_lock"
#define VCONFKEY_SETAPPL_MOBILE_TRACKER_HIDE_USER_DATA_BOOL	VCONFKEY_SETAPPL_PREFIX"/mobile_tracker_hide_user_data"

/* display and light */
#define VCONFKEY_SETAPPL_FONT_SIZE_INT				VCONFKEY_SETAPPL_PREFIX"/font_size"
#define VCONFKEY_SETAPPL_FONT_TYPE_INT				VCONFKEY_SETAPPL_PREFIX"/font_type"
#define VCONFKEY_SETAPPL_BRIGHTNESS_INT				VCONFKEY_SETAPPL_PREFIX"/brightness"
#define VCONFKEY_SETAPPL_BRIGHTNESS_AUTOMATIC_BOOL		VCONFKEY_SETAPPL_PREFIX"/brightness_automatic"
#define VCONFKEY_SETAPPL_BACKLIGHT_TIME_INT			VCONFKEY_SETAPPL_PREFIX"/backlight_time"

/* time and date */
#define VCONFKEY_SETAPPL_STATE_AUTOMATIC_TIME_UPDATE_BOOL	VCONFKEY_SETAPPL_PREFIX"/automatic_time_update"
#define VCONFKEY_SETAPPL_STATE_DST_BOOL				VCONFKEY_SETAPPL_PREFIX"/dst"
#define VCONFKEY_SETAPPL_TIME_FORMAT_INT			VCONFKEY_SETAPPL_PREFIX"/time_format"
#define VCONFKEY_SETAPPL_DATE_FORMAT_INT			VCONFKEY_SETAPPL_PREFIX"/date_format"
#define VCONFKEY_SETAPPL_TIMEZONE_ID				VCONFKEY_SETAPPL_PREFIX"/timezone_id"
#define VCONFKEY_SETAPPL_TIMEZONE_INT				VCONFKEY_SETAPPL_PREFIX"/timezone"
#define VCONFKEY_SETAPPL_CITYNAME_INDEX_INT			VCONFKEY_SETAPPL_PREFIX"/cityname_id"
#define VCONFKEY_SETAPPL_WEEKOFDAY_FORMAT_INT			VCONFKEY_SETAPPL_PREFIX"/weekofday_format"

/* phone */
#define VCONFKEY_SETAPPL_STATE_LANG_AUTOMATIC_BOOL VCONFKEY_SETAPPL_PREFIX"/lang_automatic"
#define VCONFKEY_SETAPPL_LANG_INT VCONFKEY_SETAPPL_PREFIX"/lang"

#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_DISPLAY_CONTENT_BOOL     VCONFKEY_SETAPPL_PREFIX"/ticker_noti/display_content"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_SMS_BOOL            VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_sms"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_MMS_NOTI_BOOL       VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_mms_noti"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_MMS_BOOL            VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_mms"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_VOICEMAIL_BOOL      VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_voicemail"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_EMAIL_BOOL          VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_email"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_RECV_SEVEN_EMAIL_BOOL    VCONFKEY_SETAPPL_PREFIX"/ticker_noti/recv_seven_email"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_MSG_DELIVERY_REPORT_BOOL VCONFKEY_SETAPPL_PREFIX"/ticker_noti/msg_delivery_report"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_MSG_READ_REPORT_BOOL     VCONFKEY_SETAPPL_PREFIX"/ticker_noti/msg_read_report"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_APP_DOWNLOADED_BOOL      VCONFKEY_SETAPPL_PREFIX"/ticker_noti/app_downloaded"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_FILE_DOWNLOADED_BOOL     VCONFKEY_SETAPPL_PREFIX"/ticker_noti/file_downloaded"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_IM_BOOL                  VCONFKEY_SETAPPL_PREFIX"/ticker_noti/im"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_FACE_BOOK_BOOL           VCONFKEY_SETAPPL_PREFIX"/ticker_noti/face_book"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_MY_SPACE_BOOL            VCONFKEY_SETAPPL_PREFIX"/ticker_noti/my_space"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_TWITTER_BOOL             VCONFKEY_SETAPPL_PREFIX"/ticker_noti/twitter"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_LBS_BOOL                 VCONFKEY_SETAPPL_PREFIX"/ticker_noti/lbs"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_MESSAGES_BOOL			VCONFKEY_SETAPPL_PREFIX"/ticker_noti/messages"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_VMAIL_BOOL				VCONFKEY_SETAPPL_PREFIX"/ticker_noti/vmail"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_EMAIL_BOOL				VCONFKEY_SETAPPL_PREFIX"/ticker_noti/email"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_SNS_BOOL					VCONFKEY_SETAPPL_PREFIX"/ticker_noti/sns"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_FILE_TRAN_BOOL			VCONFKEY_SETAPPL_PREFIX"/ticker_noti/file_tran"
#define VCONFKEY_SETAPPL_STATE_TICKER_NOTI_OSP_BOOL					VCONFKEY_SETAPPL_PREFIX"/ticker_noti/osp"

#define VCONFKEY_SETAPPL_STATE_DATA_ROAMING_BOOL	VCONFKEY_SETAPPL_PREFIX"/data_roaming"

#define VCONFKEY_SETAPPL_VIB_FEEDBACK_INT VCONFKEY_SETAPPL_PREFIX"/vib_feedback"

#define VCONFKEY_SETAPPL_STATE_TOUCH_PANEL_AUTOLOCK_BOOL VCONFKEY_SETAPPL_PREFIX"/touch_panel_autolock"
#define VCONFKEY_SETAPPL_STATE_TRANSACTION_TRACKING_BOOL VCONFKEY_SETAPPL_PREFIX"/transaction_tracking"
#define VCONFKEY_SETAPPL_STATE_EXPIRY_REMINDER_BOOL      VCONFKEY_SETAPPL_PREFIX"/expiry_reminder"
#define VCONFKEY_SETAPPL_ROAMING_NETWORK_INT VCONFKEY_SETAPPL_PREFIX"/roaming_network"

/* application */

/* menu widget */
#define VCONFKEY_SETAPPL_STATE_ADAPTIVE_MENU_ORDER_BOOL VCONFKEY_SETAPPL_PREFIX"/adaptive_menu_order"
#define VCONFKEY_SETAPPL_STATE_USE_NETWORK_BY_WIDGETS_BOOL VCONFKEY_SETAPPL_PREFIX"/use_network_by_widgets"

/* memory */
#define VCONFKEY_SETAPPL_DEFAULT_MEM_WAP_INT            VCONFKEY_SETAPPL_PREFIX"/default_memory/wap"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_BLUETOOTH_INT      VCONFKEY_SETAPPL_PREFIX"/default_memory/bluetooth"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_CAMERA_INT         VCONFKEY_SETAPPL_PREFIX"/default_memory/camera"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_VOICE_RECORDER_INT VCONFKEY_SETAPPL_PREFIX"/default_memory/voice_recorder"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_FM_RADIO_INT       VCONFKEY_SETAPPL_PREFIX"/default_memory/fm_radio"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_ALL_SHARE_INT          VCONFKEY_SETAPPL_PREFIX"/default_memory/all_share"
#define VCONFKEY_SETAPPL_DEFAULT_MEM_ADOBE_AIR_INT          VCONFKEY_SETAPPL_PREFIX"/default_memory/adobe_air"

/* reset */

/* TV out */
#define VCONFKEY_SETAPPL_TVOUT_AUTOFULL_SCREEN_BOOL		VCONFKEY_SETAPPL_PREFIX"/tvout/autofull_screen"
#define VCONFKEY_SETAPPL_TVOUT_TVSYSTEM_INT			VCONFKEY_SETAPPL_PREFIX"/tvout/tvsystem"
#define VCONFKEY_SETAPPL_TVOUT_RESOLUTION_INT			VCONFKEY_SETAPPL_PREFIX"/tvout/resolution"
#define VCONFKEY_SETAPPL_TVOUT_SCREENSIZE_INT			VCONFKEY_SETAPPL_PREFIX"/tvout/screensize"
#define VCONFKEY_SETAPPL_TVOUT_ROTATION_INT			VCONFKEY_SETAPPL_PREFIX"/tvout/rotation"

/* save Memory */

#define VCONFKEY_SETAPPL_MEM_CUR_PROFILE_INT				VCONFKEY_SETAPPL_MEM_PREFIX"/cur_profile"
#define VCONFKEY_SETAPPL_MEM_PROFILE_CURRENT_SYS_TOUCH_SOUND_INT	VCONFKEY_SETAPPL_MEM_PREFIX"/current/sys_touch_sound"
#define VCONFKEY_SETAPPL_MEM_PROFILE_CURRENT_SYS_VOLUME_INT		VCONFKEY_SETAPPL_MEM_PREFIX"/current/sys_volume"
#define VCONFKEY_SETAPPL_MEM_VIB_FEEDBACK_INT				VCONFKEY_SETAPPL_MEM_PREFIX"/vib_feedback"

/* setting - on,off status */
enum {
	SETTING_ON_OFF_BTN_OFF = 0,
	SETTING_ON_OFF_BTN_ON,
	SETTING_ON_OFF_BTN_MAX
};

/* profile - call alert type */
enum {
	SETTING_CALL_ALERT_TYPE_MELODY = 0,
	SETTING_CALL_ALERT_TYPE_RAISING_MELODY,
	SETTING_CALL_ALERT_TYPE_VIB,
	SETTING_CALL_ALERT_TYPE_VIB_THEN_MELODY,
	SETTING_CALL_ALERT_TYPE_VIB_AND_MELODY,
	SETTING_CALL_ALERT_TYPE_VIB_AND_RAISING_MELODY,
	SETTING_CALL_ALERT_TYPE_MUTE,
	SETTING_CALL_ALERT_TYPE_MAX
};

/* profile - call alert vib type */
enum {
	SETTING_CALL_ALERT_VIB_TYPE1 = 0,
	SETTING_CALL_ALERT_VIB_TYPE2,
	SETTING_CALL_ALERT_VIB_TYPE3,
	SETTING_CALL_ALERT_VIB_TYPE4,
	SETTING_CALL_ALERT_VIB_TYPE5,
	SETTING_CALL_ALERT_VIB_TYPE6,
	SETTING_CALL_ALERT_VIB_TYPE7,
	SETTING_CALL_ALERT_VIB_TYPE8,
	SETTING_CALL_ALERT_VIB_TYPE9,
	SETTING_CALL_ALERT_VIB_TYPE10,
	SETTING_CALL_ALERT_VIB_MAX
};

/* profile - msg alert type */
enum {
	SETTING_MSG_ALERT_TYPE_MELODY = 0,
	SETTING_MSG_ALERT_TYPE_VIB,
	SETTING_MSG_ALERT_TYPE_RAISING_MELODY,
	SETTING_MSG_ALERT_TYPE_VOICE,
	SETTING_MSG_ALERT_TYPE_VIB_THEN_MELODY,
	SETTING_MSG_ALERT_TYPE_VIB_AND_MELODY,
	SETTING_MSG_ALERT_TYPE_VIB_AND_RAISING_MELODY,
	SETTING_MSG_ALERT_TYPE_MUTE,
	SETTING_MSG_ALERT_TYPE_MAX
};

/* profile - msg alert vib type */
enum {
	SETTING_MSG_ALERT_VIB_TYPE1 = 0,
	SETTING_MSG_ALERT_VIB_TYPE2,
	SETTING_MSG_ALERT_VIB_TYPE3,
	SETTING_MSG_ALERT_VIB_TYPE4,
	SETTING_MSG_ALERT_VIB_TYPE5,
	SETTING_MSG_ALERT_VIB_MAX
};

/* profile - system touch sound */
enum {
	SETTING_SYS_TOUCH_SOUND_XYLOPHONE = 0,
	SETTING_SYS_TOUCH_SOUND_BEEP,
	SETTING_SYS_TOUCH_SOUND_GLOSSY,
	SETTING_SYS_TOUCH_SOUND_MUTE,
	SETTING_SYS_TOUCH_SOUND_MAX
};

/* network - select network */
enum {
	SETTING_SELECT_NETWORK_AUTOMATIC = 0,
	SETTING_SELECT_NETWORK_MANUAL,
	SETTING_SELECT_NETWORK_MAX
};

/* network - network mode */
enum {
	SETTING_NETWORK_MODE_AUTOMATIC = 0,
	SETTING_NETWORK_MODE_GSM_900_1800,
	SETTING_NETWORK_MODE_GSM_850_1900,
	SETTING_NETWORK_MODE_UTMS,
	SETTING_NETWORK_MODE_MAX
};

/* connectivity - tv out - tv system */
enum {
	SETTING_TVOUT_TV_SYSTEM_NTSC = 0,
	SETTING_TVOUT_TV_SYSTEM_PAL,
	SETTING_TVOUT_TV_SYSTEM_MAX
};

/* connectivity - tv out - screen size */
enum {
	SETTING_TVOUT_SCREEN_SIZE_NORMAL = 0,
	SETTING_TVOUT_SCREEN_SIZE_WIDE,
	SETTING_TVOUT_SCREEN_SIZE_MAX
};

/* display - font size */
enum {
	SETTING_FONT_SIZE_SMALL = 0,
	SETTING_FONT_SIZE_MIDDLE,
	SETTING_FONT_SIZE_LARGE,
	SETTING_FONT_SIZE_MAX
};

/* display - brightness */
enum {
	SETTING_BRIGHTNESS_LEVEL1 = 1,
	SETTING_BRIGHTNESS_LEVEL2,
	SETTING_BRIGHTNESS_LEVEL3,
	SETTING_BRIGHTNESS_LEVEL4,
	SETTING_BRIGHTNESS_LEVEL5,
	SETTING_BRIGHTNESS_LEVEL6,
	SETTING_BRIGHTNESS_LEVEL7,
	SETTING_BRIGHTNESS_LEVEL8,
	SETTING_BRIGHTNESS_LEVEL9,
	SETTING_BRIGHTNESS_LEVEL10
};

/* display - backlight time */
enum {
	SETTING_BACKLIGHT_TIME_8SEC = 8,
	SETTING_BACKLIGHT_TIME_15SEC = 15,
	SETTING_BACKLIGHT_TIME_30SEC = 30,
	SETTING_BACKLIGHT_TIME_1MIN = 60,
	SETTING_BACKLIGHT_TIME_3MIN = 180,
	SETTING_BACKLIGHT_TIME_10MIN = 600,
	SETTING_BACKLIGHT_TIME_MAX
};

/* time - time format */
enum {
	SETTING_TIME_FORMAT_12HOUR = 0,
	SETTING_TIME_FORMAT_24HOUR,
	SETTING_TIME_FORMAT_MAX
};

/* time - date format */
enum {
	SETTING_DATE_FORMAT_DD_MM_YYYY = 0,
	SETTING_DATE_FORMAT_MM_DD_YYYY,
	SETTING_DATE_FORMAT_YYYY_MM_DD,
	SETTING_DATE_FORMAT_YYYY_DD_MM,
	SETTING_DATE_FORMAT_MAX
};

/* time - week of day format */
enum {
	SETTING_WEEKOFDAY_FORMAT_SUNDAY = 0,
	SETTING_WEEKOFDAY_FORMAT_MONDAY,
	SETTING_WEEKOFDAY_FORMAT_TUESDAY,
	SETTING_WEEKOFDAY_FORMAT_WEDNESDAY,
	SETTING_WEEKOFDAY_FORMAT_THURSDAY,
	SETTING_WEEKOFDAY_FORMAT_FRIDAY,
	SETTING_WEEKOFDAY_FORMAT_SATURDAY,
	SETTING_WEEKOFDAY_FORMAT_MAX
};

/* phone - lnaguage */
enum {
	SETTING_LANG_AUTOMATIC = 0,
	SETTING_LANG_KOREA = 1,
	SETTING_LANG_ENGLISH,
	SETTING_LANG_CHINA,
	SETTING_LANG_CANTONESE,
	SETTING_LANG_TAIWAN,
	SETTING_LANG_GERMAN,
	SETTING_LANG_DUTCH,
	SETTING_LANG_SPAINISH,
	SETTING_LANG_PORTUGUESE,
	SETTING_LANG_GREEK,
	SETTING_LANG_ITALIAN,
	SETTING_LANG_FRENCH,
	SETTING_LANG_TURKISH,
	SETTING_LANG_JAPAN,
	SETTING_LANG_RUSSIAN,
	SETTING_LANG_MAX
};

/* phone - vibration feedback */
enum {
	SETTING_VIB_FEEDBACK_LEVEL0 = 0,
	SETTING_VIB_FEEDBACK_LEVEL1,
	SETTING_VIB_FEEDBACK_LEVEL2,
	SETTING_VIB_FEEDBACK_LEVEL3,
	SETTING_VIB_FEEDBACK_LEVEL4,
	SETTING_VIB_FEEDBACK_LEVEL5
};

/* memory - default memory */
enum {
	SETTING_DEF_MEMORY_PHONE = 0,
	SETTING_DEF_MEMORY_MMC,
	SETTING_DEF_MEMORY_MAX
};

/* phone - license setting */
enum {
	SETTING_ROAM_NET_AUTO_DOWNLOAD = 0,
	SETTING_ROAM_NET_MANUAL,
	SETTING_ROAM_NET_ALWAYS_REJECT,
	SETTING_ROAM_NET_MAX
};

/* Music player */
#define VCONFKEY_SETAPPL_MUSIC_MENU_ALBUMS_BOOL			VCONFKEY_SETAPPL_PREFIX"/music-player/albums"
#define VCONFKEY_SETAPPL_MUSIC_MENU_ARTISTS_BOOL		VCONFKEY_SETAPPL_PREFIX"/music-player/artists"
#define VCONFKEY_SETAPPL_MUSIC_MENU_GENRES_BOOL			VCONFKEY_SETAPPL_PREFIX"/music-player/genres"
#define VCONFKEY_SETAPPL_MUSIC_MENU_COMPOSERS_BOOL		VCONFKEY_SETAPPL_PREFIX"/music-player/composers"
#define VCONFKEY_SETAPPL_MUSIC_MENU_YEARS_BOOL			VCONFKEY_SETAPPL_PREFIX"/music-player/years"
#define VCONFKEY_SETAPPL_MUSIC_MENU_FOLDERS_BOOL		VCONFKEY_SETAPPL_PREFIX"/music-player/folders"

#define VCONFKEY_SETAPPL_MUSIC_MENU_VAL_INT VCONFKEY_SETAPPL_PREFIX"/music-player/menu"
enum {
	SETTING_MUSIC_MENU_ALBUM = 0x0001,
	SETTING_MUSIC_MENU_ARTIST = 0x0002,
	SETTING_MUSIC_MENU_GENRE = 0x0004,
	SETTING_MUSIC_MENU_COMPOSER = 0x0008,
	SETTING_MUSIC_MENU_YEAR = 0x0010,
	SETTING_MUSIC_MENU_FOLDER = 0x0020
};

#define VCONFKEY_SETAPPL_MUSIC_EQUALISER_VAL_INT		VCONFKEY_SETAPPL_PREFIX"/music-player/eq_val"
enum {
	SETTING_MUSIC_EQ_OFF = 0,
	SETTING_MUSIC_EQ_AUTO,
	SETTING_MUSIC_EQ_ROCK,
	SETTING_MUSIC_EQ_POP,
	SETTING_MUSIC_EQ_JAZZ,
	SETTING_MUSIC_EQ_CLASSIC,
	SETTING_MUSIC_EQ_DANCE,
	SETTING_MUSIC_EQ_LIVE,
	SETTING_MUSIC_EQ_NUMS
};

#define VCONFKEY_SETAPPL_MUSIC_EFFECT_VAL_INT			VCONFKEY_SETAPPL_PREFIX"/music-player/effect_val"
enum {
	SETTING_MUSIC_EFFECT_OFF = 0,
	SETTING_MUSIC_EFFECT_DYNAMIC,
	SETTING_MUSIC_EFFECT_WIDE,
	SETTING_MUSIC_EFFECT_EXTERNALIZATION,
	SETTING_MUSIC_EFFECT_MUSIC_CLARITY,
	SETTING_MUSIC_EFFECT_BASS_ENHANCEMENT,
	SETTING_MUSIC_EFFECT_CONCERT_HALL,
	SETTING_MUSIC_EFFECT_NUMS
};

#define VCONFKEY_SETAPPL_MUSIC_SURROUND_CH_STATE_BOOL		VCONFKEY_SETAPPL_PREFIX"/music-player/surround_ch_state"

#define VCONFKEY_SETAPPL_BATTERY_PERCENTAGE_BOOL		VCONFKEY_SETAPPL_PREFIX"/battery_percentage"

/* Accessibility setting */
#define VCONFKEY_SETAPPL_ACCESSIBILITY_ACCESSIBILITY		VCONFKEY_SETAPPL_PREFIX"/accessibility/accessibility"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_HIGH_CONTRAST		VCONFKEY_SETAPPL_PREFIX"/accessibility/high_contrast"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_SCREEN_ZOOM		VCONFKEY_SETAPPL_PREFIX"/accessibility/screen_zoom"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE		VCONFKEY_SETAPPL_PREFIX"/accessibility/font_size"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_STYLE		VCONFKEY_SETAPPL_PREFIX"/accessibility/font_style"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_TORCH_LIGHT		VCONFKEY_SETAPPL_PREFIX"/accessibility/torch_light"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_MONO_AUDIO		VCONFKEY_SETAPPL_PREFIX"/accessibility/mono_audio"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_ACCEPT_CALL		VCONFKEY_SETAPPL_PREFIX"/accessibility/accept_call"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_ENABLE_AUTO_ANSWER	VCONFKEY_SETAPPL_PREFIX"/accessibility/enable_auto_answer"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_AUTO_ANSWER		VCONFKEY_SETAPPL_PREFIX"/accessibility/auto_answer"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_POWERKEY_END_CALLS	VCONFKEY_SETAPPL_PREFIX"/accessibility/powerkey_end_calls"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_MOTION_TRIPLE_TAB	VCONFKEY_SETAPPL_PREFIX"/accessibility/motion_triple_tab"
#define VCONFKEY_SETAPPL_ACCESSIBILITY_POWER_KEY_HOLD           VCONFKEY_SETAPPL_PREFIX"/accessibility/power_key_hold"

/* Motion setting */
#define VCONFKEY_SETAPPL_MOTION_ACTIVATION                      VCONFKEY_SETAPPL_PREFIX"/motion_active"
#define VCONFKEY_SETAPPL_USE_TILT                               VCONFKEY_SETAPPL_PREFIX"/use_tilt"
#define VCONFKEY_SETAPPL_TILT_SENSITIVITY                       VCONFKEY_SETAPPL_PREFIX"/tilt_sensitivity"

#define VCONFKEY_SETAPPL_USE_PANNING                            VCONFKEY_SETAPPL_PREFIX"/use_panning"
#define VCONFKEY_SETAPPL_PANNING_SENSITIVITY                    VCONFKEY_SETAPPL_PREFIX"/panning_sensitivity"

#define VCONFKEY_SETAPPL_USE_DOUBLE_TAP                         VCONFKEY_SETAPPL_PREFIX"/use_double_tap"
#define VCONFKEY_SETAPPL_USE_TURN_OVER                          VCONFKEY_SETAPPL_PREFIX"/use_turn_over"

#define VCONFKEY_SETAPPL_USE_PICK_UP                            VCONFKEY_SETAPPL_PREFIX"/use_pick_up"
#define VCONFKEY_SETAPPL_USE_DOUBLE_TAP                         VCONFKEY_SETAPPL_PREFIX"/use_double_tap"

#define VCONFKEY_SETAPPL_APP_MOTION_INTERNET                    VCONFKEY_SETAPPL_PREFIX"/motion/app/internet"
#define VCONFKEY_SETAPPL_APP_MOTION_GALLERY                     VCONFKEY_SETAPPL_PREFIX"/motion/app/gallery"

/**
 * @}
 */

/* ========================== For CISS UI============================= */
/**
 * @defgroup vconf_key_CISS CISS Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_CISS
 * @{
 * @brief Maintainer : siwoo0.lee@samsung.com
 */
#define VCONFKEY_CISSAPPL_PREFIX  "db/ciss/"

#define VCONFKEY_CISSAPPL_SHOW_MY_NUMBER_INT             VCONFKEY_CISSAPPL_PREFIX"/show_my_number"
#define VCONFKEY_CISSAPPL_AUTO_REJECT_BOOL               VCONFKEY_CISSAPPL_PREFIX"/auto_reject"
#define VCONFKEY_CISSAPPL_AUTO_REJECT_UNKNOWN_BOOL       VCONFKEY_CISSAPPL_PREFIX"/auto_reject_unknown"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_BOOL               VCONFKEY_CISSAPPL_PREFIX"/prefix_dial"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_INT                VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_cnt"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_NUM1_STR           VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_num1"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_NUM2_STR           VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_num2"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_NUM3_STR           VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_num3"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_NUM4_STR           VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_num4"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_NUM5_STR           VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_num5"
#define VCONFKEY_CISSAPPL_REJECT_CALL_MSG_BOOL           VCONFKEY_CISSAPPL_PREFIX"/reject_call_message"
#define VCONFKEY_CISSAPPL_REJECT_CALL_MSG_INT            VCONFKEY_CISSAPPL_PREFIX"/reject_call_message_cnt"
#define VCONFKEY_CISSAPPL_USER_CREATE_MSG1_STR           VCONFKEY_CISSAPPL_PREFIX"/user_create_message1"
#define VCONFKEY_CISSAPPL_USER_CREATE_MSG2_STR           VCONFKEY_CISSAPPL_PREFIX"/user_create_message2"
#define VCONFKEY_CISSAPPL_USER_CREATE_MSG3_STR           VCONFKEY_CISSAPPL_PREFIX"/user_create_message3"
#define VCONFKEY_CISSAPPL_USER_CREATE_MSG4_STR           VCONFKEY_CISSAPPL_PREFIX"/user_create_message4"
#define VCONFKEY_CISSAPPL_USER_CREATE_MSG5_STR           VCONFKEY_CISSAPPL_PREFIX"/user_create_message5"
#define VCONFKEY_CISSAPPL_ANSWERING_MODE_INT             VCONFKEY_CISSAPPL_PREFIX"/answering_mode"
#define VCONFKEY_CISSAPPL_ANSWERING_MODE_TIME_INT        VCONFKEY_CISSAPPL_PREFIX"/answering_mode_time"
#define VCONFKEY_CISSAPPL_CALL_CONNECT_TONE_BOOL         VCONFKEY_CISSAPPL_PREFIX"/call_connect_tone"
#define VCONFKEY_CISSAPPL_MINUTE_MINDER_BOOL             VCONFKEY_CISSAPPL_PREFIX"/minute_minder"
#define VCONFKEY_CISSAPPL_CALL_END_TONE_BOOL             VCONFKEY_CISSAPPL_PREFIX"/call_end_tone"
#define VCONFKEY_CISSAPPL_ALERT_ON_CALL_INT              VCONFKEY_CISSAPPL_PREFIX"/alert_on_call"
#define VCONFKEY_CISSAPPL_VIDEO_IMAGE_PATH_STR           VCONFKEY_CISSAPPL_PREFIX"/video_image_path"
#define VCONFKEY_CISSAPPL_OWN_VIDEO_BOOL                 VCONFKEY_CISSAPPL_PREFIX"/own_video"
#define VCONFKEY_CISSAPPL_USE_CALL_FAIL_OPTIONS_BOOL     VCONFKEY_CISSAPPL_PREFIX"/use_call_fail_options"
#define VCONFKEY_CISSAPPL_VOICE_AUTO_REDIAL_BOOL         VCONFKEY_CISSAPPL_PREFIX"/voice_auto_redial"
#define VCONFKEY_CISSAPPL_VIDEO_AUTO_REDIAL_BOOL         VCONFKEY_CISSAPPL_PREFIX"/video_auto_redial"
#define VCONFKEY_CISSAPPL_PREFIX_DIAL_VALUE_INT          VCONFKEY_CISSAPPL_PREFIX"/prefix_dial_value"
#define VCONFKEY_CISSAPPL_REJECT_CALL_MSG_VALUE_INT      VCONFKEY_CISSAPPL_PREFIX"/reject_call_message_value"
#define VCONFKEY_CISSAPPL_CALL_DIVERTING_INDICATOR_BOOL  VCONFKEY_CISSAPPL_PREFIX"/call_diverting_indicator"
#define VCONFKEY_CISSAPPL_ANSWERING_KEY_BOOL             VCONFKEY_CISSAPPL_PREFIX"/call_answering_key"
#define VCONFKEY_CISSAPPL_POWER_KEY_ENDS_CALL_BOOL       VCONFKEY_CISSAPPL_PREFIX"/call_power_key_ends_call"

/**
 * @}
 */

/* =========================== Call app =================================== */
/**
 * @defgroup vconf_key_CallApp Call Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_CallApp
 * @{
 * @brief Maintainer : alpakook@samsung.com
 */
#define VCONFKEY_CALL_STATE "memory/call/state"
enum {
	VCONFKEY_CALL_OFF = 0x00,
	VCONFKEY_CALL_VOICE_CONNECTING,
	VCONFKEY_CALL_VOICE_ACTIVE,
	VCONFKEY_CALL_VIDEO_CONNECTING,
	VCONFKEY_CALL_VIDEO_ACTIVE,
	VCONFKEY_CALL_STATE_MAX
};

/**
 * @}
 */

/* =============================== Wifi ====================================== */
/**
 * @defgroup vconf_key_Wifi Wifi Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Wifi
 * @{
 * @brief Maintainer : shyeon.kim@samsung.com  sw0927.kim@samsung.com
 */
#define VCONFKEY_WIFI_STATE "memory/wifi/state"
enum {
	VCONFKEY_WIFI_OFF = 0x00,
	VCONFKEY_WIFI_UNCONNECTED,
	VCONFKEY_WIFI_CONNECTED,
	VCONFKEY_WIFI_TRANSFER,
	VCONFKEY_WIFI_STATE_MAX
};

#define VCONFKEY_WIFI_STRENGTH "memory/wifi/strength"
enum {
	VCONFKEY_WIFI_STRINGTH_MIN = 0,
	VCONFKEY_WIFI_STRINGTH_MAX = 4
};

#define VCONFKEY_WIFI_QS_EXIT "memory/wifi/wifi_qs_exit"
enum {
	VCONFKEY_WIFI_QS_CANCEL = 0x00,
	VCONFKEY_WIFI_QS_WIFI_CONNECTED,
	VCONFKEY_WIFI_QS_3G
};

#define VCONFKEY_WIFI_ENABLE_QS "db/wifi/enable_quick_start"
enum {
	VCONFKEY_WIFI_QS_DISABLE = 0x00,
	VCONFKEY_WIFI_QS_ENABLE = 0x01
};

/* Current connected ap's name : string
 * Added by Misun Kim <ms0123.kim@samsung.com>
 */
#define VCONFKEY_WIFI_CONNECTED_AP_NAME "db/wifi/connected_ap_name"

/* Current state of wifi UG */
#define VCONFKEY_WIFI_UG_RUN_STATE "memory/wifi/ug_run_state"
enum {
	VCONFKEY_WIFI_UG_RUN_STATE_NULL = 0x00,
	VCONFKEY_WIFI_UG_RUN_STATE_ON_FOREGROUND,
	VCONFKEY_WIFI_UG_RUN_STATE_ON_BACKGROUND,
	VCONFKEY_WIFI_UG_RUN_STATE_OFF,
	VCONFKEY_WIFI_UG_RUN_STATE_MAX
};

/**
 * @}
 */

/* ================================= BT =====================================*/
/**
 * @defgroup vconf_key_BT BT Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_BT
 * @{
 * @brief Maintainer : sw0312.kim@samsung.com, chanyeol.park@samsung.com
 */

/* Bluetooth Status : int (bit masking value) */
#define VCONFKEY_BT_STATUS "db/bluetooth/status"
enum {
	VCONFKEY_BT_STATUS_OFF = 0x0000,
	VCONFKEY_BT_STATUS_ON = 0x0001,
	VCONFKEY_BT_STATUS_BT_VISIBLE = 0x0002,
	VCONFKEY_BT_STATUS_TRANSFER = 0x0004
};

/* Local name */
#define VCONFKEY_BT_LOCAL_NAME "db/bluetooth/localname"

/* Bluetooth Connected Device : int (bit masking value) */
#define VCONFKEY_BT_DEVICE "memory/bluetooth/device"
enum {
	VCONFKEY_BT_DEVICE_NONE = 0x0000,
	VCONFKEY_BT_DEVICE_HEADSET_CONNECTED = 0x0004,
	VCONFKEY_BT_DEVICE_A2DP_HEADSET_CONNECTED = 0x0010,
	VCONFKEY_BT_DEVICE_SAP_CONNECTED = 0x0020,
	VCONFKEY_BT_DEVICE_PBAP_CONNECTED = 0x0040
};

/* Media sound path for BT */
enum {
	VCONFKEY_BT_PLAYER_SELECT_SPEAKER = 0x00,	/* Media Player Select Speaker */
	VCONFKEY_BT_PLAYER_SELECT_BLUETOOTH = 0x01,	/* Media Player Select Bluetooth */
	VCONFKEY_BT_APP_SELECT_SPEAKER = 0x02,	/* BT application Select Speaker */
	VCONFKEY_BT_APP_SELECT_BLUETOOTH = 0x04	/* BT application Select Bluetooth */
};

/* Bluetooth SCO Connection state : boolean */
#define VCONFKEY_BT_HEADSET_SCO "memory/bluetooth/btsco"
/* SCO connection state */
enum {
	VCONFKEY_BT_SCO_DISCONNECT = 0x00,	/* SCO Disconnected */
	VCONFKEY_BT_SCO_CONNECT = 0x01	/* SCO Connected */
};

/**
 * @}
 */

/* =========================== Alarm ================================*/
/**
 * @defgroup vconf_key_Alarm Alarm Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Alarm
 * @{
 * @brief Maintainer : jiwon11.lee@samsung.com
 */
#define VCONFKEY_ALARM_STATE	"db/alarm/state"
/**
 * @}
 */

/* =========================== Music app ================================*/
/**
 * @defgroup vconf_key_MusicApp Music Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_MusicApp
 * @{
 * @brief Maintainer : junhyuk7.lee@samsung.com
 */
#define VCONFKEY_MUSIC_STATE "memory/music/state"
enum {
	VCONFKEY_MUSIC_OFF = 0x00,
	VCONFKEY_MUSIC_PLAY,
	VCONFKEY_MUSIC_PAUSE,
	VCONFKEY_MUSIC_STOP,
	VCONFKEY_MUSIC_STATE_MAX
};

#define VCONFKEY_MUSIC_PROCESS_STATE "memory/music/process_state"
enum {
	VCONFKEY_MUSIC_PROCESS_OFF = 0x00,
	VCONFKEY_MUSIC_PROCESS_FOREGROUND,
	VCONFKEY_MUSIC_PROCESS_BACKGROUND,
	VCONFKEY_MUSIC_PROCESS_STATE_MAX
};

/**
 * @}
 */

/* ========================== Radio app ===============================*/
/**
 * @defgroup vconf_key_RadioApp Radio Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_RadioApp
 * @{
 * @brief Maintainer : hk57.kim@samsung.com
 */
#define VCONFKEY_RADIO_STATE "memory/radio/state"
enum {
	VCONFKEY_RADIO_OFF = 0x00,
	VCONFKEY_RADIO_PLAY,
	VCONFKEY_RADIO_STOP,
	VCONFKEY_RADIO_STATE_MAX
};

#define VCONFKEY_RADIO_TESTMODE    "db/radio/testmode"
enum {
	VCONFKEY_RADIO_TEST_OFF = 0,
	VCONFKEY_RADIO_TEST_ON
};

/**
 * @}
 */

/* =========================== Task Switcher app =================================== */
/**
 * @defgroup vconf_key_TaskSwitcherApp Task Switcher Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_TaskSwitcherApp
 * @{
 * @brief Maintainer : noha.park@samsung.com
 */
#define VCONFKEY_TASKSWITCHER_VIEWTYPE "db/taskswitcher/viewtype"
enum {
	VCONFKEY_TASKSWITCHER_VIEWTYPE_LIST = 0x00,
	VCONFKEY_TASKSWITCHER_VIEWTYPE_CARD,
	VCONFKEY_TASKSWITCHER_VIEWTYPE_MAX
};

/**
 * @}
 */

/* =========================== Menu Screen app =================================== */
/**
 * @defgroup vconf_key_MenuScreenApp Menu Screen Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_MenuScreenApp
 * @{
 * @brief Maintainer : nicesj.park@samsung.com
 */
#define VCONFKEY_MENUSCREEN_VIEWTYPE "db/menuscreen/viewtype"
enum {
	VCONFKEY_MENUSCREEN_VIEWTYPE_DEFAULT = 0x00,
	VCONFKEY_MENUSCREEN_VIEWTYPE_LIST,
	VCONFKEY_MENUSCREEN_VIEWTYPE_SPACE,
	VCONFKEY_MENUSCREEN_VIEWTYPE_MAX
};

/**
 * @}
 */

/* ========================== Sync ===============================*/
/**
 * @defgroup vconf_key_Sync Sync Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Sync
 * @{
 * @brief Maintainer : jyjeong@samsung.com
 */
#define VCONFKEY_SYNC_STATE "db/sync/state"
/**
 * @}
 */

/* ========================== Data Router Keys & Values ============================ */
/**
 * @defgroup vconf_key_DataRouter Data Router Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_DataRouter
 * @{
 * @brief Maintainer : injun.yang@samsung.com
 */
#define VCONF_DATAROUTER_PREFIX "memory/data_router"

/**
 * <!-- reg-control keynum=0, value=int -->
 * @brief data router connection method
 */
#define VCONFKEY_DR_CONNECTION_METHOD_INT	VCONF_DATAROUTER_PREFIX"/conn_method"
enum {
	VCONFKEY_DR_NONE = 0,
	VCONFKEY_DR_USB,
	VCONFKEY_DR_BLUETOOTH,
	VCONFKEY_DR_WIFI
};

#define VCONFKEY_DR_PW_STATUS_CHECK_BOOL	VCONF_DATAROUTER_PREFIX"/pw_status"
/* FOR CHECKING AUTH STATUS UNDER KIES CONNECTION / REQUESTED BY sunbong.ha / 2011-07-26 */
#define VCONFKEY_DR_AUTH_STATUS_CHECK_INT	VCONF_DATAROUTER_PREFIX"/auth_status"
/**
 * @}
 */

/* ========================== Dnet ===============================*/
/**
 * @defgroup vconf_key_dnet Data Network Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_dnet
 * @{
 * @brief Maintainer : donghoo.park@samsung.com
 */
#define VCONFKEY_3G_ENABLE "db/setting/3gEnabled"

#define VCONFKEY_DORMANT_SET "db/dnet/DormantSupport"

#define VCONFKEY_NETWORK_STATUS "memory/dnet/status"
enum {
	VCONFKEY_NETWORK_OFF = 0,
	VCONFKEY_NETWORK_CELLULAR,
	VCONFKEY_NETWORK_WIFI
};

#define VCONFKEY_NETWORK_CONFIGURATION_CHANGE_IND "memory/dnet/network_config"
#define VCONFKEY_NETWORK_IP "memory/dnet/ip"
#define VCONFKEY_NETWORK_PROXY "memory/dnet/proxy"

#define VCONFKEY_NETWORK_WIFI_STATE "memory/dnet/wifi"
enum {
	VCONFKEY_NETWORK_WIFI_OFF,
	VCONFKEY_NETWORK_WIFI_NOT_CONNECTED,
	VCONFKEY_NETWORK_WIFI_CONNECTED
};

#define VCONFKEY_NETWORK_CELLULAR_STATE "memory/dnet/cellular"
enum {
	VCONFKEY_NETWORK_CELLULAR_ON,
	VCONFKEY_NETWORK_CELLULAR_3G_OPTION_OFF,
	VCONFKEY_NETWORK_CELLULAR_ROAMING_OFF,
	VCONFKEY_NETWORK_CELLULAR_FLIGHT_MODE,
	VCONFKEY_NETWORK_CELLULAR_NO_SERVICE
};

#define VCONFKEY_DNET_STATE "memory/dnet/state"
enum {
	VCONFKEY_DNET_OFF = 0x00,
	VCONFKEY_DNET_NORMAL_CONNECTED,
	VCONFKEY_DNET_SECURE_CONNECTED,
	VCONFKEY_DNET_TRANSFER,
	VCONFKEY_DNET_STATE_MAX
};

#define VCONFKEY_DNET_INIT  "memory/dnet/init"
enum {
	VCONFKEY_DNET_SERVER_NOT_INITED = 0,
	VCONFKEY_DNET_SERVER_INITED
};

#define VCONFKEY_NETWORK_CELLULAR_PKT_TOTAL_RCV  "db/dnet/statistics/cellular/totalrcv"
#define VCONFKEY_NETWORK_CELLULAR_PKT_TOTAL_SNT  "db/dnet/statistics/cellular/totalsnt"
#define VCONFKEY_NETWORK_CELLULAR_PKT_LAST_RCV  "db/dnet/statistics/cellular/lastrcv"
#define VCONFKEY_NETWORK_CELLULAR_PKT_LAST_SNT  "db/dnet/statistics/cellular/lastsnt"
#define VCONFKEY_NETWORK_WIFI_PKT_TOTAL_RCV  "db/dnet/statistics/wifi/totalrcv"
#define VCONFKEY_NETWORK_WIFI_PKT_TOTAL_SNT  "db/dnet/statistics/wifi/totalsnt"
#define VCONFKEY_NETWORK_WIFI_PKT_LAST_RCV  "db/dnet/statistics/wifi/lastrcv"
#define VCONFKEY_NETWORK_WIFI_PKT_LAST_SNT  "db/dnet/statistics/wifi/lastsnt"

/**
 * @}
 */

/* ========================== GPS ===============================*/
/**
 * @defgroup vconf_key_GPS GPS Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_GPS
 * @{
 * @brief Maintainer : daejins.kim@samsung.com
 */
#define VCONFKEY_GPS_STATE "memory/gps/state"
enum {
	VCONFKEY_GPS_OFF = 0x00,
	VCONFKEY_GPS_SEARCHING,
	VCONFKEY_GPS_CONNECTED,
	VCONFKEY_GPS_STATE_MAX
};
/* setting location on/off value */
#define VCONFKEY_LOCATION_ENABLED "db/location/setting/GpsEnabled"
/**
 * @}
 */

/* ========================== SNS ===============================*/
/**
 * @defgroup vconf_key_SNS SNS Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_SNS
 * @{
 * @brief Maintainer : sukbong.lee@samsung.com
 */
#define VCONFKEY_SNS_FACEBOOK_STATE "db/sns/facebook/state"
#define VCONFKEY_SNS_MYSPACE_STATE "db/sns/myspace/state"
#define VCONFKEY_SNS_TWITTER_STATE "db/sns/twitter/state"
/**
 * @}
 */

/* ========================== Communities ===============================*/
/**
 * @defgroup vconf_key_Communities Communities Application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_Communities
 * @{
 * @brief Maintainer : karam.ko@samsung.com
 */
#define VCONFKEY_COMMUNITIES_FACEBOOK_STATE "db/communities/facebook/state"
#define VCONFKEY_COMMUNITIES_MYSPACE_STATE "db/communities/myspace/state"
#define VCONFKEY_COMMUNITIES_FLICKR_STATE "db/communities/flickr/state"
#define VCONFKEY_COMMUNITIES_PHOTOBUCKET_STATE "db/communities/photobucket/state"
#define VCONFKEY_COMMUNITIES_YOUTUBE_STATE "db/communities/youtube/state"
#define VCONFKEY_COMMUNITIES_PICASA_STATE "db/communities/picasa/state"
#define VCONFKEY_COMMUNITIES_FRIENDSTER_STATE "db/communities/friendster/state"
/**
 * @}
 */

/* =================== Input Service Framework Keys & Values ========================*/
/**
 * @defgroup vconf_key_InputServiceFramework service Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_InputServiceFramework
 * @{
 * @brief Maintainer : sehwan@samsung.com
 */
#define VCONFKEY_ISF_PREFIX				"db/isf"
#define VCONFKEY_ISF_INPUT_LANG_STR    VCONFKEY_ISF_PREFIX"/input_lang"	/* ex) "french" */
/**
 * @}
 */

/* ========================== For Logs UI============================= */
/**
 * @defgroup vconf_key_LogsUI LogsUI application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_LogsUI
 * @{
 * @brief Maintainer : sunghee46.kim@samsung.com
 */
/* This key is deleted following donghee.ye request at 2011-11-09 */
/* #define LOGS_UNSEEN_MISSED_CALL_COUNT "db/logs/unseen_missed_call_count" */

/**
 * @}
 */

/* =========================== IDLE lock =======================================*/
/**
 * @defgroup vconf_key_idleLock idleLock Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_idleLock
 * @{
 * @brief Maintainer : wonil22.choi@samsung.com hyoyoung.chang@samsung.com angelkim@samsung.com
 */

#define VCONFKEY_IDLE_LOCK_STATE "memory/idle_lock/state"
enum {
	VCONFKEY_IDLE_UNLOCK = 0x00,
	VCONFKEY_IDLE_LOCK
};

/**
 * @ingroup vconf_key
 * @addtogroup vconf_key_idleLock
 * @{
 * @brief Maintainer : jinny.yoon@samsung.com
 */
#define VCONFKEY_IDLE_LOCK_BGSET "db/idle_lock/bgset"

/**
 * @}
 */

/* =========================== pwlock =======================================*/
/**
 * @defgroup vconf_key_pwlock Lock application for password verification: phone, pin, sum, network, etc.
 * @ingroup vconf_key
 * @addtogroup vconf_key_pwlock
 * @{
 * @brief Maintainer : seungtaek.chung@samsung.com miju52.lee@samsung.com
 *        Used module : pwlock
 *
 */

#define VCONFKEY_PWLOCK_STATE "memory/pwlock/state"
enum {
	VCONFKEY_PWLOCK_BOOTING_UNLOCK = 0x00,
	VCONFKEY_PWLOCK_BOOTING_LOCK,
	VCONFKEY_PWLOCK_RUNNING_UNLOCK,
	VCONFKEY_PWLOCK_RUNNING_LOCK
};
/**
 * @}
 */

/* =========================== mobile hotspot =======================================*/
/**
 * @defgroup vconf_key_mobile_hotspot Mobile hotspot's vconf keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_mobile_hotspot
 * @{
 * @brief Maintainer : bh.shim@samsung.com, sy39.ju@samsung.com
 *        Used module : wifi-efl-ug, wifi-quick-app, setting, ug-kies-via-wifi, usb-setting-app, data-router, libmtp-0
 *
 */

#define VCONFKEY_MOBILE_AP_STATUS "memory/mobile_ap/mobile_ap_status"
enum {
	VCONFKEY_MOBILE_AP_STATUS_OFF = 0x00,
	VCONFKEY_MOBILE_AP_STATUS_ON
};

#define VCONFKEY_MOBILE_HOTSPOT_MODE "memory/mobile_hotspot/mode"
enum {
	VCONFKEY_MOBILE_HOTSPOT_MODE_NONE = 0x00,
	VCONFKEY_MOBILE_HOTSPOT_MODE_WIFI = 0x01,
	VCONFKEY_MOBILE_HOTSPOT_MODE_USB = 0x02,
	VCONFKEY_MOBILE_HOTSPOT_MODE_BT = 0x04
};

#define VCONFKEY_MOBILE_HOTSPOT_WIFI_KEY "db/mobile_hotspot/wifi_key"
/* This vconf key's value means the number of connected device to hotspot */
#define VCONFKEY_MOBILE_HOTSPOT_CONNECTED_DEVICE "memory/mobile_hotspot/connected_device"
/**
 * @}
 */

/* =========================== CAMERA apps =======================================*/
/**
 * @defgroup vconf_key_CameraApps camera Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_CameraApps
 * @{
 * @brief Maintainer :  milkelf.choi@samsung.com, jh1979.park@samsung.com, jm80.yang@samsung.com
 */

#define VCONFKEY_CAMERA_STATE "memory/camera/state"

enum {
	VCONFKEY_CAMERA_OFF = 0x00,
	VCONFKEY_CAMERA_ON,
	VCONFKEY_CAMERA_PREVIEW,
	VCONFKEY_CAMERA_PREVIEW_LOCK,
	VCONFKEY_CAMERA_CAPTURING,
	VCONFKEY_CAMERA_RECORDING,
	VCONFKEY_CAMERA_RECORDING_LOCK,
	VCONFKEY_CAMERA_REVIEW,
	VCONFKEY_CAMERA_STATE_MAX
};

/**
 * @}
 */

/* =========================== VoiceRecorder app =======================================*/
/**
 * @defgroup vconf_key_VoicerecorderApp Voice recorder app keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_VoicerecorderApp
 * @{
 * @brief Maintainer : quddls.oh@samsung.com
 */
#define VCONFKEY_VOICERECORDER_STATE "memory/voicerecorder/state"
enum {
	VCONFKEY_VOICERECORDER_OFF = 0x00,
	VCONFKEY_VOICERECORDER_READY,
	VCONFKEY_VOICERECORDER_RECORDING,
	VCONFKEY_VOICERECORDER_PAUSED,
	VCONFKEY_VOICERECORDER_STATE_MAX
};
/**
 * @}
 */

/* ========================== USB setting ====================================== */
/**
 * @defgroup vconf_key_usb_setting
 * @ingroup vconf_key
 * @addtogroup vconf_key_usb_setting
 * @{
 * @brief Maintainer : Jihye Lim <veronica.lim@samsung.com>
 */
#define VCONFKEY_USB_STORAGE_STATUS "memory/usb/mass_storage_status"
enum {
	VCONFKEY_USB_STORAGE_STATUS_OFF = 0x00,
	VCONFKEY_USB_STORAGE_STATUS_UMS_ON,
	VCONFKEY_USB_STORAGE_STATUS_UMS_MMC_ON
};
/**
 * @}
 */

/**
 * @defgroup vconf_key_ETC ETC Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_ETC
 * @{
 * @brief Maintainer :
 * Maybe it is not used.
 */

/* ============================ Calendar Keys & Values ============================*/
/* Maintainer :
#define VCONFKEY_CALENDAR_START_WDAY		"db/calendar/start_wday"
enum {
   VCONFKEY_CALENDAR_START_SUN = 0x00,
   VCONFKEY_CALENDAR_START_MON
};

#define VCONFKEY_CALENDAR_VIEW_BY		"db/calendar/start_wday"
enum {
   VCONFKEY_CALENDAR_VIEW_MONTH = 0x00,
   VCONFKEY_CALENDAR_VIEW_WEEK,
   VCONFKEY_CALENDAR_VIEW_DAY
};
*/

#if 0
/* ============================ Volume Keys & Values ============================*/
/* Maintainer :
 */
#define VCONFKEY_VOLUME_PCM    "db/volume/pcm"
/* No enum. Refer to src/apps/volume */
#define VCONFKEY_VOLUME_MODEM	"db/volume/modem"
enum {
	VCONFKEY_VOLUME_MUTE = 0x00,
	VCONFKEY_VOLUME_1,
	VCONFKEY_VOLUME_2,
	VCONFKEY_VOLUME_3,
	VCONFKEY_VOLUME_4,
	VCONFKEY_VOLUME_5,
	VCONFKEY_VOLUME_6,
	VCONFKEY_VOLUME_MAX
};
#endif

/* ============================ Lock Keys & Values ============================*/
/* Maintainer :
#define VCONFKEY_LOCK_STATE "db/lock/state"
#define VCONFKEY_LOCK_PIN1(LOCK_STATE) (LOCK_STATE & 0x01)
#define VCONFKEY_LOCK_PIN2(LOCK_STATE) ((LOCK_STATE >> 1) & 0x01)
#define VCONFKEY_LOCK_SIM(LOCK_STATE) ((LOCK_STATE >> 2) & 0x01)
#define VCONFKEY_LOCK_PHONE(LOCK_STATE) ((LOCK_STATE >> 3) & 0x01)
#define VCONFKEY_LOCK_PIN1_SET(LOCK_STATE) (LOCK_STATE | 0x01)
#define VCONFKEY_LOCK_PIN2_SET(LOCK_STATE) (LOCK_STATE | (0x01 << 1))
#define VCONFKEY_LOCK_SIM_SET(LOCK_STATE) (LOCK_STATE | (0x01 << 2))
#define VCONFKEY_LOCK_PHONE_SET(LOCK_STATE) (LOCK_STATE | (0x01 << 3))
#define VCONFKEY_LOCK_PIN1_UNSET(LOCK_STATE) (LOCK_STATE & ~0x01)
#define VCONFKEY_LOCK_PIN2_UNSET(LOCK_STATE) (LOCK_STATE & ~(0x01 << 1))
#define VCONFKEY_LOCK_SIM_UNSET(LOCK_STATE) (LOCK_STATE & ~(0x01 << 2))
#define VCONFKEY_LOCK_PHONE_UNSET(LOCK_STATE) (LOCK_STATE & ~(0x01 << 3))

#define VCONFKEY_LOCK_RETRY "db/lock/retry"
#define VCONFKEY_LOCK_RETRY_PIN1(LOCK_RETRY) (LOCK_RETRY & 0x0f)
#define VCONFKEY_LOCK_RETRY_PIN2(LOCK_RETRY) ((LOCK_RETRY >> 4) & 0x0f)
*/

/* ========================== System Keys & Values ============================ */
/* Maintainer :  */
/**
 * @defgroup vconf_key_system
 * @ingroup vconf_key
 * @addtogroup vconf_key_system
 * @{
 * @brief Maintainer : Jaeho Lee <jaeho81.lee@samsung.com>
 */
#define VCONFKEY_SYSTEM_TIMECHANGE "db/system/timechange"
/**
 * @}
 */

/* ========================== For Myfiles ============================= */
/**
 * @defgroup vconf_key_myfile myfiles application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_myfile
 * @{
 * @brief Maintainer : Jeunghoon Park <jh1979.park@samsung.com>
 */
#define VCONFKEY_MYFILE_LIST_BY "db/myfile/list_by"
/**
 * @}
 */

/* ============================ NFC ============================*/
/**
 * @defgroup vconf_key_NFC 
 * @ingroup vconf_key
 * @addtogroup vconf_key_NFC
 * @{
 * @brief Maintainer : wonkyu.kwon@samsung.com
 */

#define  VCONFKEY_NFC_STATE "db/nfc/enable"  /* status of NFC On/Off */

enum
{
    VCONFKEY_NFC_STATE_OFF = 0x00,
    VCONFKEY_NFC_STATE_ON,
    VCONFKEY_NFC_STATE_MAX
};

/**
 * @}
 */

/* ========================== Call ============================= */
/**
 * @defgroup vconf_key_call call application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_call
 * @{
 * @brief Maintainer : Sungjoon won <sungjoon.won@samsung.com>, js49.lee <jsj49.lee@samsung.com>
 */
#define VCONFKEY_CALL_VOLUME_LEVEL "db/call/vol_level"
/**
 * @}
 */

/* ========================== FLASH PLAYER ============================= */
/**
 * @defgroup vconf_key_call call application Keys
 * @ingroup vconf_key
 * @addtogroup vconf_key_call
 * @{
 * @brief Maintainer : Jeongsu Kim <jst.kim@samsung.com>
 */
#define VCONFKEY_FLASHPLAYER_FULLSCREEN "memory/flashplayer/fullscreen"
enum {
 VCONFKEY_FLASHPLAYER_FULLSCREEN_OFF = 0x00,
 VCONFKEY_FLASHPLAYER_FULLSCREEN_ON
};

/**
 * @}
 */

/* ========================== FACTORY ============================= */
/**
 * @defgroup vconf_key_factory
 * @ingroup vconf_key
 * @addtogroup vconf_key_factory
 * @{
 * @brief Maintainer : Jisung Ahn <jcastle.ahn@samsung.com>
 */
#define VCONFKEY_FACTORY_PREFIX "memory/factory"

/* when call connected at factory mode this flag set, write:call read:fta */
#define VCONFKEY_FACTORY_CALL_CONNECT_STATE VCONFKEY_FACTORY_PREFIX"/call_connected"
enum
{
 VCONFKEY_FACTORY_CALL_DISCONNECTED = 0x00,
 VCONFKEY_FACTORY_CALL_CONNECTED
};

/**
 * @}
 */

#endif				/* __VCONF_KEYS_H__ */

