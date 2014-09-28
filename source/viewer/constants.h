//--------------------------------------------------------------------
//	
//	constants.h
//
//	Written by: Owen Smith
//	
//	Copyright 1998 Be, Inc. All Rights Reserved.
//	
//--------------------------------------------------------------------

#ifndef _CLUE_CONSTANTS_H
#define _CLUE_CONSTANTS_H

#ifndef CLUE_BUILD_H
#include "ClueBuild.h"
#endif

#ifndef _GRAPHICS_DEFS_H
#include <GraphicsDefs.h>
#endif

extern const char * STR_SETTING_SCHEMA_VERSION;


//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP;
extern const char CMD_FILE_OPEN;
extern const char CMD_FILE_EXPORT;
extern const char CMD_FILE_PAGE_SETUP;
extern const char CMD_FILE_PRINT;
extern const char CMD_FILE_CLOSE;
extern const char CMD_FILE_HELP;
extern const char CMD_FILE_EDIT_CUT;
extern const char CMD_FILE_EDIT_COPY;
extern const char CMD_FILE_EDIT_SELECT_ALL;


//--------------------------------------------------------------------
//	Colors
extern rgb_color CLR_FOREGROUND;
extern rgb_color CLR_FOREGROUND_LITE;
extern rgb_color CLR_FOREGROUND_DARK;
extern rgb_color CLR_BACKGROUND;
extern rgb_color CLR_BACKGROUND_LITE;
extern rgb_color CLR_BACKGROUND_DARK;
extern rgb_color CLR_TEXT;
extern rgb_color CLR_LIST_BACKGROUND;
extern rgb_color CLR_LIST_TEXT;
extern rgb_color CLR_LIST_SELECTED_BACKGROUND;
extern rgb_color CLR_LIST_SELECTED_TEXT;

extern const rgb_color CLR_TOOLBAR_GREY;
extern const rgb_color CLR_DARK_TOOLBAR_GREY;
extern const rgb_color CLR_WHITE;
extern const rgb_color CLR_BLACK;
extern const rgb_color CLR_FASHIONABLE;
extern const rgb_color CLR_DARK_GREY;
extern const rgb_color CLR_BKG_GREY;
extern const rgb_color CLR_SHADOW_GREY;
extern const rgb_color CLR_RED;
extern const rgb_color CLR_LIST_SELECTED_GREY;

//--------------------------------------------------------------------
//	Message IDs
static const int32 MSG_CLOSE_ALL_ZOOM_WINDOWS		= 'cazw';
static const int32 MSG_GET_WINDOW_LIST				= 'mgwl';
static const int32 MSG_WIN_ADD_MENU					= 'oWAM';
static const int32 MSG_WIN_DELETE_MENU				= 'oWDM';
static const int32 MSG_VIEW_ADD_MENU				= 'oVAM';
static const int32 MSG_VIEW_DELETE_MENU				= 'oVDM';
static const int32 MSG_VIEW_ADD_ITEM				= 'oVAI';
static const int32 MSG_WIN_HIDE_USER_MENUS			= 'oWHU';
static const int32 MSG_WIN_LARGE_TEST_ICONS			= 'oWFM';
static const int32 MSG_MENU_OUTLINE_SEL				= 'oSMU';
static const int32 MSG_TEST_ITEM					= 'oWTM';
static const int32 MSG_USER_ITEM					= 'oWUM';
static const int32 MSG_LABEL_EDIT					= 'oLED';
static const int32 MSG_UPDATE_STATUS_UI				= 'sbud';
static const int32 MSG_MENU_FILE_START				= 'mFST';
static const int32 MSG_MENU_FILE_STOP				= 'mFSt';
static const int32 MSG_MENU_FILE_OPEN				= 'mFOP';
static const int32 MSG_MENU_FILE_EXPORT				= 'mFEP';
static const int32 MSG_MENU_EDIT_PREFERENCES		= 'mEDP';
static const int32 MSG_WINDOW_REGISTRY_ADD			= 'mWRA';
static const int32 MSG_WINDOW_REGISTRY_SUB			= 'mWRS';
static const int32 MSG_WINDOW_REGISTRY_ADDED		= 'mWRD';
static const int32 MSG_SPLITTER_START				= 'mSPS';
static const int32 MSG_SPLITTER_STOP				= 'mSST';
static const int32 MSG_PROCESS_CLUES				= 'pclu';
static const int32 MSG_QUIT_PORT_THREAD				= 'qprt';
static const int32 MSG_TEAM_DELETE					= 'mtmd';
static const int32 MSG_CLEAR_CLUE_LIST				= 'mccl';
static const int32 MSG_TEAM_PROPERTIES				= 'mtmp';
static const int32 MSG_FILTER_CLASS_BIRTH			= 'mfcb';
static const int32 MSG_FILTER_CLASS_DEATH			= 'mfcd';
static const int32 MSG_FILTER_METHOD_ENTER			= 'mfme';
static const int32 MSG_FILTER_METHOD_EXIT			= 'mfmx';
static const int32 MSG_FILTER_AUDIT_SUCCESS			= 'mfas';
static const int32 MSG_FILTER_AUDIT_FAILURE			= 'mfaf';
static const int32 MSG_FILTER_INFO					= 'mfin';
static const int32 MSG_FILTER_WARNING				= 'mfwr';
static const int32 MSG_FILTER_ERROR					= 'mfer';
static const int32 MSG_UPDATE_TEAM_PROPERTIES		= 'mutp';
static const int32 MSG_TOOL_TIP_START				= 'mttS';
static const int32 MSG_TOOL_TIP_STOP				= 'mtts';
static const int32 MSG_CATEGORY_CHANGED				= 'ccat';
static const int32 MSG_EVENT_MASK_CHANGED			= 'evtc';
static const int32 MSG_LIST_ITEM_SELECTED			= 'mlsc';
static const int32 MSG_LIST_ITEM_INVOCATED			= 'mlii';
static const int32 MSG_MENU_SEL_ALL_CAT_ALL_EVT		= 'sace';
static const int32 MSG_MENU_USEL_ALL_CAT_ALL_EVT	= 'uace';
static const int32 MSG_MENU_SEL_CUR_CAT_ALL_EVT		= 'scce';
static const int32 MSG_MENU_USEL_CUR_CAT_ALL_EVT	= 'ucce';
static const int32 MSG_LIST_CLUE_ITEM_INVOCATED		= 'mlci';
static const int32 MSG_LIST_CLUE_ITEM_SELECTED		= 'mcis';
static const int32 MSG_OK							= 'mokk';
static const int32 MSG_CANCEL						= 'cncl';
static const int32 MSG_APPLY						= 'aply';
static const int32 MSG_HELP							= 'help';
static const int32 MSG_SETTINGS_CHANGED				= 'schg';
static const int32 MSG_BROADCAST_SETTINGS_CHANGED	= 'bsch';
static const int32 MSG_PRINTER_PAGE_SETUP			= 'pgsu';
static const int32 MSG_PRINTER_PRINT				= 'prnt';


//--------------------------------------------------------------------
//	Strings
extern const char * STR_APP_SIG;
extern const char * STR_FILE_SIG;

// Simple localization scheme
#define LOCALE_USA
//#define LOCALE_GERMAN
//#define LOCALE_RUSSIAN
//#define LOCALE_PORTUGUESE
//#define LOCALE_FRENCH
//#define LOCALE_CZECH
//#define LOCALE_SWEDISH
//#define LOCALE_SPANISH
//#define LOCALE_TEST_STRINGS

extern const char * STR_STATUS_FILTER_CLASS_BIRTH;
extern const char * STR_STATUS_FILTER_CLASS_DEATH;
extern const char * STR_STATUS_FILTER_METHOD_ENTER;
extern const char * STR_STATUS_FILTER_METHOD_EXIT;
extern const char * STR_STATUS_FILTER_SUCCEEDED;
extern const char * STR_STATUS_FILTER_FAILED;
extern const char * STR_STATUS_FILTER_OK;
extern const char * STR_STATUS_FILTER_INFO;
extern const char * STR_STATUS_FILTER_WARNING;
extern const char * STR_STATUS_FILTER_ERROR;
extern const char * STR_STATUS_FILTER_TIMER;
extern const char * STR_STATUS_FILTER_OBJECT;
extern const char * STR_STATUS_MNU_FILE_OPEN;
extern const char * STR_STATUS_MNU_FILE_EXPORT;
extern const char * STR_STATUS_MNU_FILE_CLOSE;
extern const char * STR_STATUS_MNU_FILE_HELP;
extern const char * STR_STATUS_MNU_FILE_ABOUT;
extern const char * STR_STATUS_MNU_EDIT_PREFERENCES;
extern const char * STR_STATUS_MNU_EDIT_CUT;
extern const char * STR_STATUS_MNU_EDIT_COPY;
extern const char * STR_STATUS_MNU_EDIT_SELECT_ALL;
extern const char * STR_STATUS_START;
extern const char * STR_STATUS_STOP;
extern const char * STR_STATUS_PAGE_SETUP;
extern const char * STR_STATUS_PRINT;
extern const char * STR_STATUS_APPLICATION_CATEGORY;
extern const char * STR_STATUS_GENERAL_CATEGORY;
extern const char * STR_STATUS_INTERFACE_CATEGORY;
extern const char * STR_STATUS_KEYBOARD_CATEGORY;
extern const char * STR_STATUS_MEDIA_CATEGORY;
extern const char * STR_STATUS_MOUSE_CATEGORY;
extern const char * STR_STATUS_NETWORK_CATEGORY;
extern const char * STR_STATUS_PRINTING_CATEGORY;
extern const char * STR_STATUS_STORAGE_CATEGORY;
extern const char * STR_STATUS_SUPPORT_CATEGORY;
extern const char * STR_STATUS_TEAMLIST_CLEAR_LIST;
extern const char * STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
extern const char * STR_STATUS_TEAMLIST_ACTIVATE;
extern const char * STR_STATUS_TEAMLIST_DELETE;
extern const char * STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES;
extern const char * STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY;
extern const char * STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES;
extern const char * STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY;
extern const char * STR_OK;
extern const char * STR_CLOSE;
extern const char * STR_CANCEL;
extern const char * STR_WINDOW_TITLE_ABOUT;
extern const char * STR_WINDOW_TITLE_PROPERTIES;
extern const char * STR_WINDOW_TITLE_FILTER;
extern const char * STR_WINDOW_TITLE_ZOOM;
extern const char * STR_MNU_FILE;
extern const char * STR_MNU_FILE_START;
extern const char * STR_MNU_FILE_STOP;
extern const char * STR_MNU_FILE_OPEN;
extern const char * STR_MNU_FILE_EXPORT;
extern const char * STR_MNU_FILE_PAGE_SETUP;
extern const char * STR_MNU_FILE_PRINT;
extern const char * STR_MNU_FILE_HELP;
extern const char * STR_MNU_FILE_ABOUT;
extern const char * STR_MNU_FILE_CLOSE;
extern const char * STR_MNU_EDIT;
extern const char * STR_MNU_EDIT_CUT;
extern const char * STR_MNU_EDIT_COPY;
extern const char * STR_MNU_EDIT_SELECT_ALL;
extern const char * STR_MNU_EDIT_PREFERENCES;
extern const char * STR_MNU_WINDOW;
extern const char * STR_MNU_VIEW_LIVE;
extern const char * STR_MNU_EMPTY_ITEM;
extern const char * STR_LABEL_CTRL;
extern const char * STR_HIDE_USER_MENUS;
extern const char * STR_LARGE_TEST_ICONS;
extern const char * STR_ADD_MENU;
extern const char * STR_ADD_ITEM;
extern const char * STR_ADD_SEP;
extern const char * STR_DELETE_MENU;
extern const char * STR_STATUS_DEFAULT;
extern const char * STR_STATUS_TEST;
extern const char * STR_STATUS_USER;
extern const char * STR_STATUS_ADD_MENU;
extern const char * STR_STATUS_ADD_ITEM;
extern const char * STR_STATUS_ADD_SEPARATOR;
extern const char * STR_STATUS_DELETE_SEPARATOR;
extern const char * STR_STATUS_DELETE_MENU;
extern const char * STR_STATUS_DELETE_ITEM;
extern const char * STR_TEAM_COLUMN_VISIBLE;
extern const char * STR_TEAM_COLUMN_ICON;
extern const char * STR_TEAM_COLUMN_TEAM_ID;
extern const char * STR_TEAM_COLUMN_APP_NAME;
extern const char * STR_TEAM_COLUMN_QUEUE_LENGTH;
extern const char * STR_TEAM_COLUMN_VIEW_FILTER;
extern const char * STR_LABEL_TEAMS;
extern const char * STR_CLUE_COLUMN_CATEGORY;
extern const char * STR_CLUE_COLUMN_EVENT;
extern const char * STR_CLUE_COLUMN_METHOD;
extern const char * STR_CLUE_COLUMN_CLASS;
extern const char * STR_CLUE_COLUMN_FILE;
extern const char * STR_CLUE_COLUMN_LINE;
extern const char * STR_CLUE_COLUMN_THREAD_ID;
extern const char * STR_CLUE_COLUMN_SEQUENCE;
extern const char * STR_CLUE_COLUMN_DATE;
extern const char * STR_CLUE_COLUMN_TIME;
extern const char * STR_CLUE_COLUMN_DESCRIPTION;
extern const char * STR_CLUE_TAB_TITLE;
extern const char * STR_WINDOW_TITLE_LIVE;
extern const char * STR_GLOBAL_EVENT_SELECTION;
extern const char * STR_CT_CLASS_BIRTH_DESCRIPTION;
extern const char * STR_CT_CLASS_DEATH_DESCRIPTION;
extern const char * STR_CT_METHOD_ENTER_DESCRIPTION;
extern const char * STR_CT_METHOD_EXIT_DESCRIPTION;
extern const char * STR_CT_AUDIT_SUCCESS_DESCRIPTION;
extern const char * STR_CT_AUDIT_FAILURE_DESCRIPTION;
extern const char * STR_CT_OK_DESCRIPTION;
extern const char * STR_CT_INFO_DESCRIPTION;
extern const char * STR_CT_WARNING_DESCRIPTION;
extern const char * STR_CT_ERROR_DESCRIPTION;
extern const char * STR_CT_TIMER_DESCRIPTION;
extern const char * STR_CT_OBJECT_DESCRIPTION;
extern const char * STR_EVENT_QUEUE_LENGTH;
extern const char * STR_EVENT_QUEUE_LIMIT_LOW;
extern const char * STR_EVENT_QUEUE_LIMIT_HIGH;
extern const char * STR_TEAM_PROPERTY_COLUMN_VIEW;
extern const char * STR_TEAM_PROPERTY_COLUMN_EVENT;
extern const char * STR_TEAM_PROPERTY_COLUMN_DESCRIPTION;
extern const char * STR_TEAM_PROPERTY_COLUMN_VALUE;
extern const char * STR_ABOUT_VERSION;
extern const char * STR_POPUP_MENU_TEAM_DELETE;
extern const char * STR_POPUP_MENU_TEAM_CLEAR_CLUES;
extern const char * STR_POPUP_MENU_TEAM_EDIT_PROPERTIES;
extern const char * STR_POPUP_MENU_TEAM_ACTIVATE;
extern const char * STR_CATEGORIES;
extern const char * STR_CATEGORY_APPLICATION;
extern const char * STR_CATEGORY_GENERAL;
extern const char * STR_CATEGORY_INTERFACE;
extern const char * STR_CATEGORY_KEYBOARD;
extern const char * STR_CATEGORY_MEDIA;
extern const char * STR_CATEGORY_MOUSE;
extern const char * STR_CATEGORY_NETWORK;
extern const char * STR_CATEGORY_PRINTING;
extern const char * STR_CATEGORY_STORAGE;
extern const char * STR_CATEGORY_SUPPORT;
extern const char * STR_SEL_ALL_CAT_ALL_EVT;
extern const char * STR_USEL_ALL_CAT_ALL_EVT;
extern const char * STR_SEL_CUR_CAT_ALL_EVT;
extern const char * STR_USEL_CUR_CAT_ALL_EVT;
extern const char * STR_PREFERENCES_WINDOW_TITLE;
extern const char * STR_APPLY;
extern const char * STR_ITEMS;
extern const char * STR_CLR_FOREGROUND;
extern const char * STR_CLR_BACKGROUND;
extern const char * STR_CLR_LIST_BACKGROUND;
extern const char * STR_CLR_LIST_TEXT;
extern const char * STR_CLR_LIST_SELECTED_TEXT;
extern const char * STR_CLR_LIST_SELECTED_BACKGROUND;
extern const char * STR_ZOOM_CATEGORY;
extern const char * STR_ZOOM_EVENT;
extern const char * STR_ZOOM_DATETIME;
extern const char * STR_ZOOM_THREADID;
extern const char * STR_ZOOM_TEAMID;
extern const char * STR_ZOOM_LINE;
extern const char * STR_ZOOM_SEQUENCE;
extern const char * STR_ZOOM_FILE;
extern const char * STR_ZOOM_METHOD;
extern const char * STR_ZOOM_CLASS;
extern const char * STR_ZOOM_DESCRIPTION;
extern const char * STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS;
extern const char * STR_ENABLE_ALL_SUBITEMS;
extern const char * STR_DISABLE_ALL_SUBITEMS;

#endif // _CLUE_CONSTANTS_H



