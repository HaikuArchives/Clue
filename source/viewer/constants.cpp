//--------------------------------------------------------------------
//
//	constants.cpp
//
//	Written by: Owen Smith
//
//	Copyright 1998 Be, Inc. All Rights Reserved.
//
//--------------------------------------------------------------------
#include <InterfaceDefs.h>
#include "constants.h"

//--------------------------------------------------------------------
//	Colors
rgb_color CLR_FOREGROUND				= { 218, 218, 218, 255 };
rgb_color CLR_FOREGROUND_LITE			= {   0,   0,   0, 255 };
rgb_color CLR_FOREGROUND_DARK			= {   0,   0,   0, 255 };
rgb_color CLR_BACKGROUND				= { 222, 219, 222, 255 };
rgb_color CLR_BACKGROUND_LITE			= {   0,   0,   0, 255 };
rgb_color CLR_BACKGROUND_DARK			= {   0,   0,   0, 255 };
rgb_color CLR_TEXT						= {   0,   0,   0, 255 };
rgb_color CLR_LIST_BACKGROUND			= { 255, 255, 255, 255 };
rgb_color CLR_LIST_TEXT					= {   0,   0,   0, 255 };
rgb_color CLR_LIST_SELECTED_BACKGROUND	= { 255, 186, 200, 255 };
rgb_color CLR_LIST_SELECTED_TEXT		= {   0,   0,   0, 255 };

extern const rgb_color CLR_TOOLBAR_GREY			= { 200, 200, 200, 255 };
extern const rgb_color CLR_DARK_TOOLBAR_GREY	= { 160, 160, 160, 255 };
extern const rgb_color CLR_WHITE				= { 255, 255, 255, 255 };
extern const rgb_color CLR_BLACK				= {   0,   0,   0, 255 };
extern const rgb_color CLR_FASHIONABLE			= { 193, 201,   0, 255 };
extern const rgb_color CLR_DARK_GREY			= {  96,  96,  96, 255 };
extern const rgb_color CLR_BKG_GREY				= { 216, 216, 216, 255 };
extern const rgb_color CLR_SHADOW_GREY			= { 127, 127, 127, 255 };
extern const rgb_color CLR_RED					= { 255,   0,   0, 255 };
extern const rgb_color CLR_LIST_SELECTED_GREY	= { 178, 178, 178, 255 };

extern const char* STR_APP_SIG
= "application/x-vnd.Jeff-Clue";

extern const char* STR_FILE_SIG
= "application/x-vnd.Jeff.Clue-Document";

//extern const char * STR_SETTING_SCHEMA_VERSION
//	= "SCHEMA_VERSION:";


#if defined(LOCALE_USA)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	American English Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
= "Open an existing Clue document" B_UTF8_ELLIPSIS;

//extern const char * STR_STATUS_MNU_FILE_IMPORT
//	= "Open an existing file";

extern const char* STR_STATUS_MNU_FILE_EXPORT
= "Export the current data to a file";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Displays the Help file in a browser.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
= "Close this window";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
= "when selected, allows CE_BIRTH events through";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
= "when selected, allows CE_DEATH events through";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
= "when selected, allows CE_ENTER events through";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
= "when selected, allows CE_EXIT events through";

extern const char* STR_STATUS_FILTER_SUCCEEDED
= "when selected, allows CE_SUCCEEDED events through";

extern const char* STR_STATUS_FILTER_FAILED
= "when selected, allows CE_FAILED events through";

extern const char* STR_STATUS_FILTER_OK
= "when selected, allows CE_OK events through";

extern const char* STR_STATUS_FILTER_INFO
= "when selected, allows CE_INFO events through";

extern const char* STR_STATUS_FILTER_WARNING
= "when selected, allows CE_WARNING events through";

extern const char* STR_STATUS_FILTER_ERROR
= "when selected, allows CE_ERROR events through";

extern const char* STR_STATUS_FILTER_TIMER
= "when selected, allows CE_TIMER events through";

extern const char* STR_STATUS_FILTER_OBJECT
= "when selected, allows CE_OBJECT events through";

extern const char* STR_STATUS_MNU_FILE_ABOUT
= "show information about this program";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "View Prerferences Panel";

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Cut selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Copy selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Select All items";

extern const char* STR_STATUS_START
= "Start retrieving Clues";

extern const char* STR_STATUS_STOP
= "Stop retrieving Clues";

extern const char* STR_STATUS_PAGE_SETUP
= "Changes the page layout.";

extern const char* STR_STATUS_PRINT
= "Prints the selected Team's Clue entries and sets printing options.";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "OK";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Cancel";

extern const char* STR_APPLY
= "Apply";

extern const char* STR_WINDOW_TITLE_ABOUT
= "About Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Properties: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "File";

extern const char* STR_MNU_FILE_START
= "Start";

extern const char* STR_MNU_FILE_STOP
= "Stop";

extern const char* STR_MNU_FILE_OPEN
= "Open";

extern const char* STR_MNU_FILE_EXPORT
= "Export Clues" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Page Setup" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PRINT
= "Print" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Help" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "About" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Close";

extern const char* STR_MNU_EDIT
= "Edit";

extern const char* STR_MNU_EDIT_CUT
= "Cut";

extern const char* STR_MNU_EDIT_COPY
= "Copy";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Select All";

extern const char* STR_MNU_WINDOW
= "Window";

extern const char* STR_MNU_HELP
= "Help";

extern const char* STR_MNU_VIEW_LIVE
= "Live Updates";

extern const char* STR_MNU_EMPTY_ITEM
= "(Empty menu)";

extern const char* STR_LABEL_CTRL
= "Label:";

extern const char* STR_HIDE_USER_MENUS
= "Hide User Menus";

extern const char* STR_LARGE_TEST_ICONS
= "Large Test Icons";

extern const char* STR_ADD_MENU
= "Add Menu";

extern const char* STR_ADD_ITEM
= "Add Item";

extern const char* STR_ADD_SEP
= "Add Separator";

extern const char* STR_DELETE_MENU
= "Delete";

extern const char* STR_STATUS_DEFAULT
= "";

extern const char* STR_STATUS_TEST
= "Test item selected: ";

extern const char* STR_STATUS_USER
= "Menu item selected: ";

extern const char* STR_STATUS_ADD_MENU
= "Added menu: ";

extern const char* STR_STATUS_ADD_ITEM
= "Added menu item: ";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Added separator menu item";

extern const char* STR_STATUS_DELETE_MENU
= "Deleted menu: ";

extern const char* STR_STATUS_DELETE_ITEM
= "Deleted menu item: ";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Deleted separator menu item";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Visible";

extern const char* STR_TEAM_COLUMN_ICON
= "Icon";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "Team ID";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Name";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Queue Length";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "View Filter";

extern const char* STR_LABEL_TEAMS
= "Teams:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Category";

extern const char* STR_CLUE_COLUMN_EVENT
= "Event";

extern const char* STR_CLUE_COLUMN_METHOD
= "Method";

extern const char* STR_CLUE_COLUMN_CLASS
= "Class";

extern const char* STR_CLUE_COLUMN_FILE
= "File";

extern const char* STR_CLUE_COLUMN_LINE
= "Line";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "Thread ID";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Sequence";

extern const char* STR_CLUE_COLUMN_DATE
= "Date";

extern const char* STR_CLUE_COLUMN_TIME
= "Time";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Description";

extern const char* STR_CLUE_TAB_TITLE
= "Team: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Live!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Global Event Selection :";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Class Constructor";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Class Destructor";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Class Method enter";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Class Method exit";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Audit success";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Audit failure";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_INFO_DESCRIPTION
= "Information";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Warning";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Error";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Timer";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Object";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Event Queue Length (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100,000";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "View";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Event";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Description";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Value";

extern const char* STR_ABOUT_VERSION
= "version: %lu.%lu.%lu %s (English)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Delete this entry";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Clear clue list";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Edit Properties" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "Categories :";

extern const char* STR_CATEGORY_APPLICATION
= "Application";

extern const char* STR_CATEGORY_GENERAL
= "General";

extern const char* STR_CATEGORY_INTERFACE
= "Interface";

extern const char* STR_CATEGORY_KEYBOARD
= "Keyboard";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Mouse";

extern const char* STR_CATEGORY_NETWORK
= "Network";

extern const char* STR_CATEGORY_PRINTING
= "Printing";

extern const char* STR_CATEGORY_STORAGE
= "Storage";

extern const char* STR_CATEGORY_SUPPORT
= "Support";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Preferences";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Preferences" B_UTF8_ELLIPSIS;

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Select All Events All Categories";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Unselect All Events All Categories";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Select All Events Current Category";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Unselect All Events Current Category";

extern const char* STR_ITEMS
= " items";

extern const char* STR_CLR_FOREGROUND
= "Highlight Color";

extern const char* STR_CLR_BACKGROUND
= "Background Color";

extern const char* STR_CLR_LIST_BACKGROUND
= "List Background Color";

extern const char* STR_CLR_LIST_TEXT
= "List Text Color";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "List Selected Text Color";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "List Selected Background Color";

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif /* LOCALE_USA */





















#if defined(LOCALE_GERMAN)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	German Strings
extern const char* FileStartStop
="Anfangen oder Beenden des Einlesens";

extern const char* STR_STATUS_MNU_FILE_OPEN
="Importieren einer Datei";

extern const char* STR_STATUS_MNU_FILE_IMPORT
= "Open an existing file";

extern const char* STR_STATUS_MNU_FILE_EXPORT
="Aktuelle Ansicht in Datei exportieren";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Displays the Help file in a browser.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
="Dieses Fenster schliessen";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
="falls angewählt, werden E_BIRTH Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
="falls angewählt, werden E_DEATH Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
="falls angewählt, werden E_ENTER Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
="falls angewählt, werden E_EXIT Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_SUCCEEDED
="falls angewählt, werden E_SUCCEEDED Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_FAILED
="falls angewählt, werden E_FAILED Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_OK
="falls angewählt, werden E_OK Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_INFO
="falls angewählt, werden E_INFO Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_WARNING
="falls angewählt, werden E_WARNING Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_ERROR
="falls angewählt, werden E_ERROR Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_TIMER
="falls angewählt, werden E_TIMER Ereignisse angezeigt.";

extern const char* STR_STATUS_FILTER_OBJECT
= "when selected, allows CE_OBJECT events through";

extern const char* STR_STATUS_MNU_FILE_ABOUT
="Information über dieses Program anzeigen.";

extern const char* STR_STATUS_START
="Anfangen Hinweise einzulesen";

extern const char* STR_STATUS_STOP
="Beenden Hinweise einzulesen";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "OK";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Abbrechen";

extern const char* STR_WINDOW_TITLE_ABOUT
= "über Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Eigenschaften: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "Datei";

extern const char* STR_MNU_FILE_START
= "Start";

extern const char* STR_MNU_FILE_STOP
= "Stop";

extern const char* STR_MNU_FILE_IMPORT
= "Ansicht Importieren" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_EXPORT
= "Ansicht Exportieren" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "über" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Schließen";

extern const char* STR_MNU_WINDOW
= "Fenster";

extern const char* STR_MNU_VIEW_LIVE
= "Live Updates";

extern const char* STR_MNU_EMPTY_ITEM
= "(leeres Menü)";

extern const char* STR_LABEL_CTRL
= "Etikett:";

extern const char* STR_HIDE_USER_MENUS
= "Benutzer Menüs ausblenden";

extern const char* STR_LARGE_TEST_ICONS
= "Große Test Symbole";

extern const char* STR_ADD_MENU
= "Menü hinzufügen";

extern const char* STR_ADD_ITEM
= "Menüpunkt hinzufügen";

extern const char* STR_ADD_SEP
= "Spearator hinzufügen";

extern const char* STR_DELETE_MENU
= "Löschen";

extern const char* STR_STATUS_TEST
= "Test Menüpunkt selektiert: ";

extern const char* STR_STATUS_USER
= "Menüpunkt selektiert: ";

extern const char* STR_STATUS_ADD_MENU
= "Menü hinzugefügt: ";

extern const char* STR_STATUS_ADD_ITEM
= "Menüpunkt hinzugefügt: ";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Separator Menüpunkt angelegt";

extern const char* STR_STATUS_DELETE_MENU
= "Menü gelöscht: ";

extern const char* STR_STATUS_DELETE_ITEM
= "Menüpunkt gelöscht: ";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Separator Menüpunkt gelöscht";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Sichtbar";

extern const char* STR_TEAM_COLUMN_ICON
= "Symbol";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "Team ID";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Name";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Schlangenlänge";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "Filter anzeigen";

extern const char* STR_LABEL_TEAMS
= "Teams:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Category";

extern const char* STR_CLUE_COLUMN_EVENT
= "Typ";

extern const char* STR_CLUE_COLUMN_METHOD
= "Methode";

extern const char* STR_CLUE_COLUMN_CLASS
= "Klasse";

extern const char* STR_CLUE_COLUMN_FILE
= "Datei";

extern const char* STR_CLUE_COLUMN_LINE
= "Zeile";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "Thread ID";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Sequenz";

extern const char* STR_CLUE_COLUMN_DATE
= "Datum";

extern const char* STR_CLUE_COLUMN_TIME
= "Zeit";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Description";

extern const char* STR_CLUE_TAB_TITLE
= "Team: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Live!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Globale Ereignis Auswahl :";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Klassen Constructor";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Klassen Destructor";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Klassen Methoden Anfang";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Klassen Methoden Ende";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Prüfung erfolgreich";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Prüfung fehlgeschlagen";

extern const char* STR_CT_INFO_DESCRIPTION
= "Information";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Warnung";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Fehler";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Länge der Ereignisschlange (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100.000";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "Ansicht";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Event";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Beschreibung";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Wert";

extern const char* STR_ABOUT_VERSION
= "Version: %lu.%lu.%lu %s (German)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Delete this entry";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Clear clue list";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Edit Properties" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "Ereignisschlange :";

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Select All Events All Categories";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Unselect All Events All Categories";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Select All Events Current Category";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Unselect All Events Current Category";

extern const char* STR_ITEMS
= " items";

extern const char* STR_CLR_FOREGROUND
= "Highlight Color";

extern const char* STR_CLR_BACKGROUND
= "Background Color";

extern const char* STR_CLR_LIST_BACKGROUND
= "List Background Color";

extern const char* STR_CLR_LIST_TEXT
= "List Text Color";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "List Selected Text Color";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "List Selected Background Color";

extern const char* STR_CATEGORY_APPLICATION
= "Application";

extern const char* STR_CATEGORY_GENERAL
= "General";

extern const char* STR_CATEGORY_INTERFACE
= "Interface";

extern const char* STR_CATEGORY_KEYBOARD
= "Keyboard";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Mouse";

extern const char* STR_CATEGORY_NETWORK
= "Network";

extern const char* STR_CATEGORY_PRINTING
= "Printing";

extern const char* STR_CATEGORY_STORAGE
= "Storage";

extern const char* STR_CATEGORY_SUPPORT
= "Support";

extern const char* STR_STATUS_PAGE_SETUP
= "Changes the page layout.";

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Page Setup" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Cut selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Copy selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Select All items";

extern const char* STR_APPLY
= "Apply";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Timer";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Object";

extern const char* STR_STATUS_PRINT
= "Prints the selected Team's Clue entries and sets printing options.";

extern const char* STR_MNU_FILE_PRINT
= "Print" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Help" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_EDIT
= "Edit";

extern const char* STR_MNU_EDIT_CUT
= "Cut";

extern const char* STR_MNU_EDIT_COPY
= "Copy";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Select All";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Preferences";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "View Prerferences Panel";

extern const char* STR_MNU_FILE_OPEN
= "Open";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Preferences" B_UTF8_ELLIPSIS;

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif /* LOCALE_GERMAN */

















#if defined(LOCALE_PORTUGUESE)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	Portuguese Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
="Importa um arquivo no Clue" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_FILE_EXPORT
="Exporta a visualiza��o atual para um arquivo";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Displays the Help file in a browser.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
="Fecha esta janela";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
="quando selecionada, permite eventos E_BIRTH";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
="quando selecionada, permite eventos E_DEATH";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
="quando selecionada, permite eventos E_ENTER";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
="quando selecionada, permite eventos E_EXIT";

extern const char* STR_STATUS_FILTER_SUCCEEDED
="quando selecionada, permite eventos E_SUCCEEDED";

extern const char* STR_STATUS_FILTER_FAILED
="quando selecionada, permite eventos E_FAILED";

extern const char* STR_STATUS_FILTER_OK
="quando selecionada, permite eventos E_OK";

extern const char* STR_STATUS_FILTER_INFO
="quando selecionada, permite eventos E_INFO";

extern const char* STR_STATUS_FILTER_WARNING
="quando selecionada, permite eventos E_WARNING";

extern const char* STR_STATUS_FILTER_ERROR
="quando selecionada, permite eventos E_ERROR";

extern const char* STR_STATUS_FILTER_TIMER
="quando selecionada, permite eventos E_TIMER";

extern const char* STR_STATUS_FILTER_OBJECT
= "when selected, allows CE_OBJECT events through";

extern const char* STR_STATUS_MNU_FILE_ABOUT
="mostra informa��es sobre este programa";

extern const char* STR_STATUS_START
="Inicia Clues";

extern const char* STR_STATUS_STOP
="Para Clues";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "OK";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Cancelar";

extern const char* STR_WINDOW_TITLE_ABOUT
= "Sobre Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Propriedades";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "Arquivo";

extern const char* STR_MNU_FILE_START
= "Iniciar";

extern const char* STR_MNU_FILE_STOP
= "Parar";

extern const char* STR_MNU_FILE_IMPORT
= "Importar Visualização" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_EXPORT
= "Exportar Visualização" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "Sobre" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Fechar";

extern const char* STR_MNU_WINDOW
= "Janela";

extern const char* STR_MNU_VIEW_LIVE
= "Atualizações Instantâneas";

extern const char* STR_MNU_EMPTY_ITEM
= "(Menu vazio)";

extern const char* STR_LABEL_CTRL
= "Etiqueta";

extern const char* STR_HIDE_USER_MENUS
= "Esconder Menus de Usuário";

extern const char* STR_LARGE_TEST_ICONS
= "Ícones de Teste Grandes";

extern const char* STR_ADD_MENU
= "Adicionar Menu";

extern const char* STR_ADD_ITEM
= "Adicionar Item";

extern const char* STR_ADD_SEP
= "Adicionar Separador";

extern const char* STR_DELETE_MENU
= "Apagar";

extern const char* STR_STATUS_TEST
= "Testar item selecionado: ";

extern const char* STR_STATUS_USER
= "Item de menu selecionado: ";

extern const char* STR_STATUS_ADD_MENU
= "Menu adicionado: ";

extern const char* STR_STATUS_ADD_ITEM
= "Item de menu adicionado: ";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Separador de item de menu adicionado";

extern const char* STR_STATUS_DELETE_MENU
= "Menu apagado: ";

extern const char* STR_STATUS_DELETE_ITEM
= "Item de menu apagado: ";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Separador de item de menu apagado";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Visivel";

extern const char* STR_TEAM_COLUMN_ICON
= "Icone";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "ID de Team";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Nome";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Tamanho da Fila";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "Filtro de Visualização";

extern const char* STR_LABEL_TEAMS
= "Teams:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Category";

extern const char* STR_CLUE_COLUMN_EVENT
= "Tipo";

extern const char* STR_CLUE_COLUMN_METHOD
= "Método";

extern const char* STR_CLUE_COLUMN_CLASS
= "Classe";

extern const char* STR_CLUE_COLUMN_FILE
= "Arquivo";

extern const char* STR_CLUE_COLUMN_LINE
= "Linha";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "ID de Thread";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Sequencia";

extern const char* STR_CLUE_COLUMN_DATE
= "Data";

extern const char* STR_CLUE_COLUMN_TIME
= "Hora";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Detalhes";

extern const char* STR_CLUE_TAB_TITLE
= "Team: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Ao Vivo!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Seleção Global de Eventos";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Construtor de Classe";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Destrutor de Classe";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Entrada de Método de Classe";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Saida de Método de Classe";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Sucesso na auditoria";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Falha na auditoria";

extern const char* STR_CT_INFO_DESCRIPTION
= "Informação";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Aviso";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Erro";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Tamanho da Fila de Evento (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100.000";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "Vizualização";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Tipo";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Descrição";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Valor";

extern const char* STR_ABOUT_VERSION
= "versão: %lu.%lu.%lu %s (Portuguese)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Delete this entry";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Clear clue list";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Edit Properties" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "Vizualização :";

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Select All Events All Categories";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Unselect All Events All Categories";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Select All Events Current Category";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Unselect All Events Current Category";

extern const char* STR_ITEMS
= " items";

extern const char* STR_CLR_FOREGROUND
= "Highlight Color";

extern const char* STR_CLR_BACKGROUND
= "Background Color";

extern const char* STR_CLR_LIST_BACKGROUND
= "List Background Color";

extern const char* STR_CLR_LIST_TEXT
= "List Text Color";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "List Selected Text Color";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "List Selected Background Color";

extern const char* STR_CATEGORY_APPLICATION
= "Application";

extern const char* STR_CATEGORY_GENERAL
= "General";

extern const char* STR_CATEGORY_INTERFACE
= "Interface";

extern const char* STR_CATEGORY_KEYBOARD
= "Keyboard";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Mouse";

extern const char* STR_CATEGORY_NETWORK
= "Network";

extern const char* STR_CATEGORY_PRINTING
= "Printing";

extern const char* STR_CATEGORY_STORAGE
= "Storage";

extern const char* STR_CATEGORY_SUPPORT
= "Support";

extern const char* STR_STATUS_PAGE_SETUP
= "Changes the page layout.";

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Page Setup" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Cut selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Copy selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Select All items";

extern const char* STR_APPLY
= "Apply";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Timer";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Object";

extern const char* STR_STATUS_PRINT
= "Prints the selected Team's Clue entries and sets printing options.";

extern const char* STR_MNU_FILE_PRINT
= "Print" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Help" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_EDIT
= "Edit";

extern const char* STR_MNU_EDIT_CUT
= "Cut";

extern const char* STR_MNU_EDIT_COPY
= "Copy";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Select All";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Preferences";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "View Prerferences Panel";

extern const char* STR_MNU_FILE_OPEN
= "Open";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Preferences" B_UTF8_ELLIPSIS;

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif



















#if defined(LOCALE_RUSSIAN)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	Russian Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
="Импорт файла в Clue" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_FILE_EXPORT
="Экспорт вида в файл";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Displays the Help file in a browser.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
="Закрыть окно";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
="если выбрано, разрешено прохождение события E_BIRTH";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
="если выбрано, разрешено прохождение события E_DEATH";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
="если выбрано, разрешено прохождение события E_ENTER";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
="если выбрано, разрешено прохождение события E_EXIT";

extern const char* STR_STATUS_FILTER_SUCCEEDED
="если выбрано, разрешено прохождение события E_SUCCEEDED";

extern const char* STR_STATUS_FILTER_FAILED
="если выбрано, разрешено прохождение события E_FAILED";

extern const char* STR_STATUS_FILTER_OK
="если выбрано, разрешено прохождение события E_OK";

extern const char* STR_STATUS_FILTER_INFO
="если выбрано, разрешено прохождение события E_INFO";

extern const char* STR_STATUS_FILTER_WARNING
="если выбрано, разрешено прохождение события E_WARNING";

extern const char* STR_STATUS_FILTER_ERROR
="если выбрано, разрешено прохождение события E_ERROR";

extern const char* STR_STATUS_FILTER_TIMER
="если выбрано, разрешено прохождение события E_TIMER";

extern const char* STR_STATUS_FILTER_OBJECT
= "when selected, allows CE_OBJECT events through";

extern const char* STR_STATUS_MNU_FILE_ABOUT
="Показать сведения об этой программе";

extern const char* STR_STATUS_START
="Запустить извлечение";

extern const char* STR_STATUS_STOP
="Остановить извлечение";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "Да";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Нет";

extern const char* STR_WINDOW_TITLE_ABOUT
= "О Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Свойства: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "Файл";

extern const char* STR_MNU_FILE_START
= "Старт";

extern const char* STR_MNU_FILE_STOP
= "Стоп";

extern const char* STR_MNU_FILE_IMPORT
= "Импорт вида" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_EXPORT
= "Экспорт вида" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "O" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Закрыть";

extern const char* STR_MNU_WINDOW
= "Окно";

extern const char* STR_MNU_VIEW_LIVE
= "Обновления";

extern const char* STR_MNU_EMPTY_ITEM
= "Пустое меню)";

extern const char* STR_LABEL_CTRL
= "Метка:";

extern const char* STR_HIDE_USER_MENUS
= "Спрятать меню пользователя";

extern const char* STR_LARGE_TEST_ICONS
= "Большие тестовые иконки";

extern const char* STR_ADD_MENU
= "Добавить Меню";

extern const char* STR_ADD_ITEM
= "Добавить пункт";

extern const char* STR_ADD_SEP
= "Добавить разделитель";

extern const char* STR_DELETE_MENU
= "Удалить";

extern const char* STR_STATUS_TEST
= "Тестовый пункт выбран";

extern const char* STR_STATUS_USER
= "Пункт меню выбран";

extern const char* STR_STATUS_ADD_MENU
= "Добавленное меню";

extern const char* STR_STATUS_ADD_ITEM
= "Добавленный пункт меню";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Добавленный разделитель меню";

extern const char* STR_STATUS_DELETE_MENU
= "Удалённое меню";

extern const char* STR_STATUS_DELETE_ITEM
= "Удалённый пункт меню";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Удаленный разделитель меню";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Видимый";

extern const char* STR_TEAM_COLUMN_ICON
= "Иконка";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "ID группы";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Имя";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Длина очереди";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "Фильтр видов";

extern const char* STR_LABEL_TEAMS
= "Пучки:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Category";

extern const char* STR_CLUE_COLUMN_EVENT
= "Тип";

extern const char* STR_CLUE_COLUMN_METHOD
= "Метод";

extern const char* STR_CLUE_COLUMN_CLASS
= "Класс";

extern const char* STR_CLUE_COLUMN_FILE
= "Файл";

extern const char* STR_CLUE_COLUMN_LINE
= "Строка";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "ID нити";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Последовательность";

extern const char* STR_CLUE_COLUMN_DATE
= "Дата";

extern const char* STR_CLUE_COLUMN_TIME
= "Время";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Детали";

extern const char* STR_CLUE_TAB_TITLE
= "Пучок: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Live!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Выбор глобального события";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Конструктор класса";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Деструктор класса";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Вход метода класса";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Выход метода класса";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Успех проверки";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Провал проверки";

extern const char* STR_CT_INFO_DESCRIPTION
= "Информация";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Предупреждение";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Ошибка";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Длина очереди событий (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100000";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "Вид";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Тип";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Описание";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Значение";

extern const char* STR_ABOUT_VERSION
= "версия: %lu.%lu.%lu %s (Russian)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Delete this entry";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Clear clue list";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Edit Properties" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "ðÏËÁÚÁÔØ :";

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Select All Events All Categories";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Unselect All Events All Categories";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Select All Events Current Category";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Unselect All Events Current Category";

extern const char* STR_ITEMS
= " items";

extern const char* STR_CLR_FOREGROUND
= "Highlight Color";

extern const char* STR_CLR_BACKGROUND
= "Background Color";

extern const char* STR_CLR_LIST_BACKGROUND
= "List Background Color";

extern const char* STR_CLR_LIST_TEXT
= "List Text Color";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "List Selected Text Color";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "List Selected Background Color";

extern const char* STR_CATEGORY_APPLICATION
= "Application";

extern const char* STR_CATEGORY_GENERAL
= "General";

extern const char* STR_CATEGORY_INTERFACE
= "Interface";

extern const char* STR_CATEGORY_KEYBOARD
= "Keyboard";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Mouse";

extern const char* STR_CATEGORY_NETWORK
= "Network";

extern const char* STR_CATEGORY_PRINTING
= "Printing";

extern const char* STR_CATEGORY_STORAGE
= "Storage";

extern const char* STR_CATEGORY_SUPPORT
= "Support";

extern const char* STR_STATUS_PAGE_SETUP
= "Changes the page layout.";

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Page Setup" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Cut selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Copy selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Select All items";

extern const char* STR_APPLY
= "Apply";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Timer";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Object";

extern const char* STR_STATUS_PRINT
= "Prints the selected Team's Clue entries and sets printing options.";

extern const char* STR_MNU_FILE_PRINT
= "Print" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Help" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_EDIT
= "Edit";

extern const char* STR_MNU_EDIT_CUT
= "Cut";

extern const char* STR_MNU_EDIT_COPY
= "Copy";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Select All";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Preferences";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "View Prerferences Panel";

extern const char* STR_MNU_FILE_OPEN
= "Open";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Preferences" B_UTF8_ELLIPSIS;

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif //LOCALE_RUSSIAN














#if defined(LOCALE_FRENCH)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	French Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
= "Importe un fichier dans Clue";

extern const char* STR_STATUS_MNU_FILE_IMPORT
= "Open an existing file";

extern const char* STR_STATUS_MNU_FILE_EXPORT
= "Exporte la vue courante dans un fichier";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Displays the Help file in a browser.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
= "Ferme cette fenêtre";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
= "si sélectionné, affiche les événements E_BIRTH";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
= "si sélectionné, affiche les événements E_DEATH";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
= "si sélectionné, affiche les événements E_ENTER";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
= "si sélectionné, affiche les événements E_EXIT";

extern const char* STR_STATUS_FILTER_SUCCEEDED
= "si sélectionné, affiche les événements E_SUCCEEDED";

extern const char* STR_STATUS_FILTER_FAILED
= "si sélectionné, affiche les événements E_FAILED";

extern const char* STR_STATUS_FILTER_OK
= "si sélectionné, affiche les événements E_OK";

extern const char* STR_STATUS_FILTER_INFO
= "si sélectionné, affiche les événements E_INFO";

extern const char* STR_STATUS_FILTER_WARNING
= "si sélectionné, affiche les événements E_WARNING";

extern const char* STR_STATUS_FILTER_ERROR
= "si sélectionné, affiche les événements E_ERROR";

extern const char* STR_STATUS_FILTER_TIMER
= "si sélectionné, affiche les événements E_TIMER";

extern const char* STR_STATUS_FILTER_OBJECT
= "when selected, allows CE_OBJECT events through";

extern const char* STR_STATUS_MNU_FILE_ABOUT
= "Montre des informations sur Clue";

extern const char* STR_STATUS_START
= "Commence la réception d'événements Clue";

extern const char* STR_STATUS_STOP
= "Arrête la réception d'événements Clue";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "OK";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Annuler";

extern const char* STR_WINDOW_TITLE_ABOUT
= "A propos de Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Propriétés: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "Fichier";

extern const char* STR_MNU_FILE_START
= "Démarrer";

extern const char* STR_MNU_FILE_STOP
= "Arrêter";

extern const char* STR_MNU_FILE_IMPORT
= "Importer la vue" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_EXPORT
= "Exporter la vue" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "A propos" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Fermer";

extern const char* STR_MNU_WINDOW
= "Fenêtre";

extern const char* STR_MNU_VIEW_LIVE
= "Mises à jour Live";

extern const char* STR_MNU_EMPTY_ITEM
= "(menu vide)";

extern const char* STR_LABEL_CTRL
= "Etiquette:";

extern const char* STR_HIDE_USER_MENUS
= "Cache les menus utilisateur";

extern const char* STR_LARGE_TEST_ICONS
= "Grandes icônes de test";

extern const char* STR_ADD_MENU
= "Ajouter un menu";

extern const char* STR_ADD_ITEM
= "Ajouter une commande";

extern const char* STR_ADD_SEP
= "Ajouter un séparateur";

extern const char* STR_DELETE_MENU
= "Effacer";

extern const char* STR_STATUS_TEST
= "Commande de test sélectionée";

extern const char* STR_STATUS_USER
= "Commande sélectionnée";

extern const char* STR_STATUS_ADD_MENU
= "Menu ajouté";

extern const char* STR_STATUS_ADD_ITEM
= "Commande ajoutée";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Séparateur ajouté";

extern const char* STR_STATUS_DELETE_MENU
= "Menu effacé:";

extern const char* STR_STATUS_DELETE_ITEM
= "Commande effacée";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Séparateur effacé";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Visible";

extern const char* STR_TEAM_COLUMN_ICON
= "Icône";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "numéro d'application";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Nom";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Longueur de la file d'attente";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "Voir le filtre";

extern const char* STR_LABEL_TEAMS
= "Applications:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Categorie";

extern const char* STR_CLUE_COLUMN_EVENT
= "Event";

extern const char* STR_CLUE_COLUMN_METHOD
= "Méthode";

extern const char* STR_CLUE_COLUMN_CLASS
= "Classe";

extern const char* STR_CLUE_COLUMN_FILE
= "Fichier";

extern const char* STR_CLUE_COLUMN_LINE
= "Ligne";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "numéro de thread";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Séquence";

extern const char* STR_CLUE_COLUMN_DATE
= "Date";

extern const char* STR_CLUE_COLUMN_TIME
= "Heure";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Détails";

extern const char* STR_CLUE_TAB_TITLE
= "Appl: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Live!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Sélection globales des événements";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Constructeur de classe";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Destructeur de classe";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Entré dans la méthode";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Sorti de la méthode";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Audit réussi";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Audit manqué";

extern const char* STR_CT_INFO_DESCRIPTION
= "Information";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Alerte";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Erreur";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Taille de la file d'événements (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100 000";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "Visible";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Event";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Description";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Valeur";

extern const char* STR_ABOUT_VERSION
= "version: %lu.%lu.%lu %s (French)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Supprimer cette application";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Vider la liste Clue";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Modifier les Propriétés" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "Categories :";

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Select All Events All Categories";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Unselect All Events All Categories";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Select All Events Current Category";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Unselect All Events Current Category";

extern const char* STR_ITEMS
= " items";

extern const char* STR_CLR_FOREGROUND
= "Highlight Color";

extern const char* STR_CLR_BACKGROUND
= "Background Color";

extern const char* STR_CLR_LIST_BACKGROUND
= "List Background Color";

extern const char* STR_CLR_LIST_TEXT
= "List Text Color";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "List Selected Text Color";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "List Selected Background Color";

extern const char* STR_CATEGORY_APPLICATION
= "Application";

extern const char* STR_CATEGORY_GENERAL
= "General";

extern const char* STR_CATEGORY_INTERFACE
= "Interface";

extern const char* STR_CATEGORY_KEYBOARD
= "Keyboard";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Mouse";

extern const char* STR_CATEGORY_NETWORK
= "Network";

extern const char* STR_CATEGORY_PRINTING
= "Printing";

extern const char* STR_CATEGORY_STORAGE
= "Storage";

extern const char* STR_CATEGORY_SUPPORT
= "Support";

extern const char* STR_STATUS_PAGE_SETUP
= "Changes the page layout.";

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Page Setup" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Cut selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Copy selection to clipboard";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Select All items";

extern const char* STR_APPLY
= "Apply";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Timer";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Object";

extern const char* STR_STATUS_PRINT
= "Prints the selected Team's Clue entries and sets printing options.";

extern const char* STR_MNU_FILE_PRINT
= "Print" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Help" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_EDIT
= "Edit";

extern const char* STR_MNU_EDIT_CUT
= "Cut";

extern const char* STR_MNU_EDIT_COPY
= "Copy";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Select All";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Preferences";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "View Prerferences Panel";

extern const char* STR_MNU_FILE_OPEN
= "Open";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Preferences" B_UTF8_ELLIPSIS;

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif //LOCALE_FRENCH




















#if defined(LOCALE_CZECH)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'T';

extern const char CMD_FILE_OPEN
= 'O';

extern const char CMD_FILE_EXPORT
= 'S';

extern const char CMD_FILE_CLOSE
= 'W';

extern const char CMD_FILE_PAGE_SETUP
= 'P';

extern const char CMD_FILE_PRINT
= 'P';

extern const char CMD_FILE_HELP
= 'H';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'C';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'A';

//--------------------------------------------------------------------
//	American English Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
= "Otevřít existující Clue dokument" B_UTF8_ELLIPSIS;

//extern const char * STR_STATUS_MNU_FILE_IMPORT
//	= "Otevřít existující soubor";

extern const char* STR_STATUS_MNU_FILE_EXPORT
= "Exportovat stávající data do souboru";

extern const char* STR_STATUS_MNU_FILE_HELP
= "Zobrazí nápovědu v okně browseru.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
= "Zavřít toto okno";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
= "pokud je vybráno, povolí CE_BIRTH události";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
= "pokud je vybráno, povolí CE_DEATH události";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
= "pokud je vybráno, povolí CE_ENTER události";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
= "pokud je vybráno, povolí CE_EXIT události";

extern const char* STR_STATUS_FILTER_SUCCEEDED
= "pokud je vybráno, povolí CE_SUCCEEDED události";

extern const char* STR_STATUS_FILTER_FAILED
= "pokud je vybráno, povolí CE_FAILED události";

extern const char* STR_STATUS_FILTER_OK
= "pokud je vybráno, povolí CE_OK události";

extern const char* STR_STATUS_FILTER_INFO
= "pokud je vybráno, povolí CE_INFO události";

extern const char* STR_STATUS_FILTER_WARNING
= "pokud je vybráno, povolí CE_WARNING události";

extern const char* STR_STATUS_FILTER_ERROR
= "pokud je vybráno, povolí CE_ERROR události";

extern const char* STR_STATUS_FILTER_TIMER
= "pokud je vybráno, povolí CE_TIMER události";

extern const char* STR_STATUS_FILTER_OBJECT
= "pokud je vybráno, povolí CE_OBJECT události";

extern const char* STR_STATUS_MNU_FILE_ABOUT
= "zobrazí informace o tomto programu";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "Zobrazit panel Nastavení";

extern const char* STR_STATUS_MNU_EDIT_CUT
= "Vyjmout označené do schránky";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "Kopírovat označené do schránky";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "Vybrat všechny položky";

extern const char* STR_STATUS_START
= "Spustit získávání hodnot";

extern const char* STR_STATUS_STOP
= "Zastavit získávání hodnot";

extern const char* STR_STATUS_PRINT
= "Vytisknout záznamy označené skupiny hodnot a nastavit možnosti tisku.";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "Things related to BApplication objects (CC_APPLICATION)";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "Things that might not fall under any other Category (CC_GENERAL)";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "Things related to BWindow, BVIew, GUI type objects (CC_INTERFACE)";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "Keyboard related Events (CC_KEYBOARD)";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "Things related to processing multi-media (CC_MEDIA)";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "Things related to processing mouse handling (CC_MOUSE)";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "Network programming messages (CC_NETWORK)";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "Things related to printing and its setup (CC_PRINTING)";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "Things related to working with files/documents on a disk (CC_STORAGE)";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "Things related to the BeOS Support kit objects (CC_SUPPORT)";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "Delete all of the Fingerprints for this team";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "Edit the properties for this team";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "Bring this team to the front of all windows";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "Remove this team from the list, deletes all of its data";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "Allows Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "Allows Fingerprints for all available Events for this category";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "Blocks Fingerprints for all available Events and all available categories";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "Blocks Fingerprints for all available Events for this category";

extern const char* STR_OK
= "OK";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "Storno";

extern const char* STR_APPLY
= "Použít";

extern const char* STR_WINDOW_TITLE_ABOUT
= "O Clue";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "Možnosti: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "TRACE_OBJECT Filter";

extern const char* STR_WINDOW_TITLE_ZOOM
= "Fingerprint Zoom";

extern const char* STR_MNU_FILE
= "Soubor";

extern const char* STR_MNU_FILE_START
= "Start";

extern const char* STR_MNU_FILE_STOP
= "Stop";

extern const char* STR_MNU_FILE_OPEN
= "Otevřít";

extern const char* STR_MNU_FILE_EXPORT
= "Exportovat hodnoty" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PAGE_SETUP
= "Nastavení strany" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PRINT
= "Tisk" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "Nápověda" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "O" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "Zavřít";

extern const char* STR_MNU_EDIT
= "Upravit";

extern const char* STR_MNU_EDIT_CUT
= "Vyjmout";

extern const char* STR_MNU_EDIT_COPY
= "Kopírovat";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "Vybrat vše";

extern const char* STR_MNU_WINDOW
= "Okno";

extern const char* STR_MNU_HELP
= "Nápověda";

extern const char* STR_MNU_VIEW_LIVE
= "Obnovení - update";

extern const char* STR_MNU_EMPTY_ITEM
= "(prázdná nabídka)";

extern const char* STR_LABEL_CTRL
= "Popisek:";

extern const char* STR_HIDE_USER_MENUS
= "Skrýt uživatelské nabídky";

extern const char* STR_LARGE_TEST_ICONS
= "Velké testovací ikony";

extern const char* STR_ADD_MENU
= "Přidat nabídku";

extern const char* STR_ADD_ITEM
= "Přidat položku";

extern const char* STR_ADD_SEP
= "Přidat oddělovač";

extern const char* STR_DELETE_MENU
= "Smazat";

extern const char* STR_STATUS_DEFAULT
= "";

extern const char* STR_STATUS_TEST
= "Testovacích položek vybráno: ";

extern const char* STR_STATUS_USER
= "Položek nabídky vybráno: ";

extern const char* STR_STATUS_ADD_MENU
= "Přidaná nabídka: ";

extern const char* STR_STATUS_ADD_ITEM
= "Přidané položky nabídky: ";

extern const char* STR_STATUS_ADD_SEPARATOR
= "Přidané oddělovače položek nabídky";

extern const char* STR_STATUS_DELETE_MENU
= "Smazané nabídky: ";

extern const char* STR_STATUS_DELETE_ITEM
= "Smazané položky nabídky: ";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "Smazané oddělovače položek nabídky";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "Viditelné";

extern const char* STR_TEAM_COLUMN_ICON
= "Ikona";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "Team ID";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "Jméno";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "Délka fronty";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "Zobrazit filtr";

extern const char* STR_LABEL_TEAMS
= "Teamy:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "Kategorie";

extern const char* STR_CLUE_COLUMN_EVENT
= "Typ";

extern const char* STR_CLUE_COLUMN_METHOD
= "Metoda";

extern const char* STR_CLUE_COLUMN_CLASS
= "Třída";

extern const char* STR_CLUE_COLUMN_FILE
= "Soubor";

extern const char* STR_CLUE_COLUMN_LINE
= "Linka";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "ID vlákna";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "Sekvence";

extern const char* STR_CLUE_COLUMN_DATE
= "Datum";

extern const char* STR_CLUE_COLUMN_TIME
= "Čas";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "Popis";

extern const char* STR_CLUE_TAB_TITLE
= "Team: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - žije!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "Globální výběr událostí :";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "Class Constructor";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "Class Destructor";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "Class Method vstup";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "Class Method konec";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "Audit úspěšný";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "Audit selhal";

extern const char* STR_CT_OK_DESCRIPTION
= "OK";

extern const char* STR_CT_INFO_DESCRIPTION
= "Informace";

extern const char* STR_CT_WARNING_DESCRIPTION
= "Varování";

extern const char* STR_CT_ERROR_DESCRIPTION
= "Chyba";

extern const char* STR_CT_TIMER_DESCRIPTION
= "Časovač";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "Objekt";

extern const char* STR_EVENT_QUEUE_LENGTH
= "Délka fronty události (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100,000";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "Zobrazit";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "Event";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "Popis";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "Hodnota";

extern const char* STR_ABOUT_VERSION
= "verze: %lu.%lu.%lu %s (Česky)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "Smazat tuto položku";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "Vyčistit clue seznam";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "Upravit nastavení" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "Activate";

extern const char* STR_CATEGORIES
= "Kategorie :";

extern const char* STR_CATEGORY_APPLICATION
= "Aplikace";

extern const char* STR_CATEGORY_GENERAL
= "Obecné";

extern const char* STR_CATEGORY_INTERFACE
= "Rozhraní";

extern const char* STR_CATEGORY_KEYBOARD
= "Klávesnice";

extern const char* STR_CATEGORY_MEDIA
= "Media";

extern const char* STR_CATEGORY_MOUSE
= "Myš";

extern const char* STR_CATEGORY_NETWORK
= "Síť";

extern const char* STR_CATEGORY_PRINTING
= "Tisk";

extern const char* STR_CATEGORY_STORAGE
= "Uložení";

extern const char* STR_CATEGORY_SUPPORT
= "Podpora";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "Nastavení";

extern const char* STR_MNU_EDIT_PREFERENCES
= "Nastavení" B_UTF8_ELLIPSIS;

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "Vybrat všechny události ve všech kategoriích";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "Odznačit všechny události všech kategoríí";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "Vybrat všechny události stávající kategorie";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "Odznačit všechny události stávající kategorie";

extern const char* STR_ITEMS
= " položek";

extern const char* STR_CLR_FOREGROUND
= "Barva zvýraznění";

extern const char* STR_CLR_BACKGROUND
= "Barva pozadí";

extern const char* STR_CLR_LIST_BACKGROUND
= "Barva pozadí seznamu";

extern const char* STR_CLR_LIST_TEXT
= "Barva textu seznamu";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "Barva označeného textu v seznamu";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "Barva pozadí označeného seznamu";

extern const char* STR_STATUS_PAGE_SETUP
= "Změna rozvržení stran.";

extern const char* STR_ZOOM_CATEGORY
= "Category:";

extern const char* STR_ZOOM_EVENT
= "Event";

extern const char* STR_ZOOM_DATETIME
= "Date/Time:";

extern const char* STR_ZOOM_THREADID
= "ThreadID:";

extern const char* STR_ZOOM_TEAMID
= "TeamID:";

extern const char* STR_ZOOM_LINE
= "Line:";

extern const char* STR_ZOOM_SEQUENCE
= "Sequence:";

extern const char* STR_ZOOM_FILE
= "File:";

extern const char* STR_ZOOM_METHOD
= "Method:";

extern const char* STR_ZOOM_CLASS
= "Class:";

extern const char* STR_ZOOM_DESCRIPTION
= "Description:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "Close All Zoom Windows";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "Enabled All Subitems";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "Disable All Subitems";

#endif /* LOCALE_CZECH */




















#if defined(LOCALE_TEST_STRINGS)

//--------------------------------------------------------------------
//	Shortcuts
extern const char CMD_FILE_START_STOP
= 'X';

extern const char CMD_FILE_OPEN
= 'X';

extern const char CMD_FILE_EXPORT
= 'X';

extern const char CMD_FILE_CLOSE
= 'X';

extern const char CMD_FILE_PAGE_SETUP
= 'X';

extern const char CMD_FILE_PRINT
= 'X';

extern const char CMD_FILE_HELP
= 'X';

extern const char CMD_FILE_EDIT_CUT
= 'X';

extern const char CMD_FILE_EDIT_COPY
= 'X';

extern const char CMD_FILE_EDIT_SELECT_ALL
= 'X';

//--------------------------------------------------------------------
//	American English Strings
extern const char* STR_STATUS_MNU_FILE_OPEN
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_STATUS_MNU_FILE_EXPORT
= "XXX";

extern const char* STR_STATUS_MNU_FILE_HELP
= "XXX.";

extern const char* STR_STATUS_MNU_FILE_CLOSE
= "XXX";

extern const char* STR_STATUS_FILTER_CLASS_BIRTH
= "XXX";

extern const char* STR_STATUS_FILTER_CLASS_DEATH
= "XXX";

extern const char* STR_STATUS_FILTER_METHOD_ENTER
= "XXX";

extern const char* STR_STATUS_FILTER_METHOD_EXIT
= "XXX";

extern const char* STR_STATUS_FILTER_SUCCEEDED
= "XXX";

extern const char* STR_STATUS_FILTER_FAILED
= "XXX";

extern const char* STR_STATUS_FILTER_OK
= "XXX";

extern const char* STR_STATUS_FILTER_INFO
= "XXX";

extern const char* STR_STATUS_FILTER_WARNING
= "XXX";

extern const char* STR_STATUS_FILTER_ERROR
= "XXX";

extern const char* STR_STATUS_FILTER_TIMER
= "XXX";

extern const char* STR_STATUS_FILTER_OBJECT
= "XXX";

extern const char* STR_STATUS_MNU_FILE_ABOUT
= "XXX";

extern const char* STR_STATUS_MNU_EDIT_PREFERENCES
= "XXX";

extern const char* STR_STATUS_MNU_EDIT_CUT
= "XXX";

extern const char* STR_STATUS_MNU_EDIT_COPY
= "XXX";

extern const char* STR_STATUS_MNU_EDIT_SELECT_ALL
= "XXX";

extern const char* STR_STATUS_START
= "XXX";

extern const char* STR_STATUS_STOP
= "XXX";

extern const char* STR_STATUS_PAGE_SETUP
= "XXX.";

extern const char* STR_STATUS_PRINT
= "XXX.";

extern const char* STR_STATUS_APPLICATION_CATEGORY
= "XXX";

extern const char* STR_STATUS_GENERAL_CATEGORY
= "XXX";

extern const char* STR_STATUS_INTERFACE_CATEGORY
= "XXX";

extern const char* STR_STATUS_KEYBOARD_CATEGORY
= "XXX";

extern const char* STR_STATUS_MEDIA_CATEGORY
= "XXX";

extern const char* STR_STATUS_MOUSE_CATEGORY
= "XXX";

extern const char* STR_STATUS_NETWORK_CATEGORY
= "XXX";

extern const char* STR_STATUS_PRINTING_CATEGORY
= "XXX";

extern const char* STR_STATUS_STORAGE_CATEGORY
= "XXX";

extern const char* STR_STATUS_SUPPORT_CATEGORY
= "XXX";

extern const char* STR_STATUS_TEAMLIST_CLEAR_LIST;
= "XXX";

extern const char* STR_STATUS_TEAMLIST_EDIT_PROPERTIES;
= "XXX";

extern const char* STR_STATUS_TEAMLIST_ACTIVATE;
= "XXX";

extern const char* STR_STATUS_TEAMLIST_DELETE
= "XXX";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES
= "XXX";

extern const char* STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY
= "XXX";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES
= "XXX";

extern const char* STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY
= "XXX";

extern const char* STR_OK
= "XXX";

extern const char* STR_CLOSE
= "Close";

extern const char* STR_CANCEL
= "XXX";

extern const char* STR_APPLY
= "XXX";

extern const char* STR_WINDOW_TITLE_ABOUT
= "XXX";

extern const char* STR_WINDOW_TITLE_PROPERTIES
= "XXX: '%s'";

extern const char* STR_WINDOW_TITLE_FILTER
= "XXX";

extern const char* STR_WINDOW_TITLE_ZOOM
= "XXX";

extern const char* STR_MNU_FILE
= "XXX";

extern const char* STR_MNU_FILE_START
= "XXX";

extern const char* STR_MNU_FILE_STOP
= "XXX";

extern const char* STR_MNU_FILE_OPEN
= "XXX";

extern const char* STR_MNU_FILE_EXPORT
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PAGE_SETUP
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_PRINT
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_HELP
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_ABOUT
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_MNU_FILE_CLOSE
= "XXX";

extern const char* STR_MNU_EDIT
= "XXX";

extern const char* STR_MNU_EDIT_CUT
= "XXX";

extern const char* STR_MNU_EDIT_COPY
= "XXX";

extern const char* STR_MNU_EDIT_SELECT_ALL
= "XXX";

extern const char* STR_MNU_WINDOW
= "XXX";

extern const char* STR_MNU_HELP
= "XXX";

extern const char* STR_MNU_VIEW_LIVE
= "XXX";

extern const char* STR_MNU_EMPTY_ITEM
= "(XXX)";

extern const char* STR_LABEL_CTRL
= "XXX:";

extern const char* STR_HIDE_USER_MENUS
= "XXX";

extern const char* STR_LARGE_TEST_ICONS
= "XXX";

extern const char* STR_ADD_MENU
= "XXX";

extern const char* STR_ADD_ITEM
= "XXX";

extern const char* STR_ADD_SEP
= "XXX";

extern const char* STR_DELETE_MENU
= "XXX";

extern const char* STR_STATUS_DEFAULT
= "";

extern const char* STR_STATUS_TEST
= "XXX: ";

extern const char* STR_STATUS_USER
= "XXX: ";

extern const char* STR_STATUS_ADD_MENU
= "XXX: ";

extern const char* STR_STATUS_ADD_ITEM
= "XXX: ";

extern const char* STR_STATUS_ADD_SEPARATOR
= "XXX";

extern const char* STR_STATUS_DELETE_MENU
= "XXX: ";

extern const char* STR_STATUS_DELETE_ITEM
= "XXX: ";

extern const char* STR_STATUS_DELETE_SEPARATOR
= "XXX";

extern const char* STR_TEAM_COLUMN_VISIBLE
= "XXX";

extern const char* STR_TEAM_COLUMN_ICON
= "XXX";

extern const char* STR_TEAM_COLUMN_TEAM_ID
= "XXX";

extern const char* STR_TEAM_COLUMN_APP_NAME
= "XXX";

extern const char* STR_TEAM_COLUMN_QUEUE_LENGTH
= "XXX";

extern const char* STR_TEAM_COLUMN_VIEW_FILTER
= "XXX";

extern const char* STR_LABEL_TEAMS
= "XXX:";

extern const char* STR_CLUE_COLUMN_CATEGORY
= "XXX";

extern const char* STR_CLUE_COLUMN_EVENT
= "XXX";

extern const char* STR_CLUE_COLUMN_METHOD
= "XXX";

extern const char* STR_CLUE_COLUMN_CLASS
= "XXX";

extern const char* STR_CLUE_COLUMN_FILE
= "XXX";

extern const char* STR_CLUE_COLUMN_LINE
= "XXX";

extern const char* STR_CLUE_COLUMN_THREAD_ID
= "XXX";

extern const char* STR_CLUE_COLUMN_SEQUENCE
= "XXX";

extern const char* STR_CLUE_COLUMN_DATE
= "XXX";

extern const char* STR_CLUE_COLUMN_TIME
= "XXX";

extern const char* STR_CLUE_COLUMN_DESCRIPTION
= "XXX";

extern const char* STR_CLUE_TAB_TITLE
= "XXX: %li";

extern const char* STR_WINDOW_TITLE_LIVE
= "Clue - Live!";

extern const char* STR_GLOBAL_EVENT_SELECTION
= "XXX :";

extern const char* STR_CT_CLASS_BIRTH_DESCRIPTION
= "XXX";

extern const char* STR_CT_CLASS_DEATH_DESCRIPTION
= "XXX";

extern const char* STR_CT_METHOD_ENTER_DESCRIPTION
= "XXX";

extern const char* STR_CT_METHOD_EXIT_DESCRIPTION
= "XXX";

extern const char* STR_CT_AUDIT_SUCCESS_DESCRIPTION
= "XXX";

extern const char* STR_CT_AUDIT_FAILURE_DESCRIPTION
= "XXX";

extern const char* STR_CT_OK_DESCRIPTION
= "XXX";

extern const char* STR_CT_INFO_DESCRIPTION
= "XXX";

extern const char* STR_CT_WARNING_DESCRIPTION
= "XXX";

extern const char* STR_CT_ERROR_DESCRIPTION
= "XXX";

extern const char* STR_CT_TIMER_DESCRIPTION
= "XXX";

extern const char* STR_CT_OBJECT_DESCRIPTION
= "XXX";

extern const char* STR_EVENT_QUEUE_LENGTH
= "XXX (%li)";

extern const char* STR_EVENT_QUEUE_LIMIT_LOW
= "1";

extern const char* STR_EVENT_QUEUE_LIMIT_HIGH
= "100,000";

extern const char* STR_TEAM_PROPERTY_COLUMN_VIEW
= "XXX";

extern const char* STR_TEAM_PROPERTY_COLUMN_EVENT
= "XXX";

extern const char* STR_TEAM_PROPERTY_COLUMN_DESCRIPTION
= "XXX";

extern const char* STR_TEAM_PROPERTY_COLUMN_VALUE
= "XXX";

extern const char* STR_ABOUT_VERSION
= "XXX: %lu.%lu.%lu %s (Test)";

extern const char* STR_POPUP_MENU_TEAM_DELETE
= "XXX";

extern const char* STR_POPUP_MENU_TEAM_CLEAR_CLUES
= "XXX";

extern const char* STR_POPUP_MENU_TEAM_EDIT_PROPERTIES
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_POPUP_MENU_TEAM_ACTIVATE
= "XXX";

extern const char* STR_CATEGORIES
= "XXX :";

extern const char* STR_CATEGORY_APPLICATION
= "XXX";

extern const char* STR_CATEGORY_GENERAL
= "XXX";

extern const char* STR_CATEGORY_INTERFACE
= "XXX";

extern const char* STR_CATEGORY_KEYBOARD
= "XXX";

extern const char* STR_CATEGORY_MEDIA
= "XXX";

extern const char* STR_CATEGORY_MOUSE
= "XXX";

extern const char* STR_CATEGORY_NETWORK
= "XXX";

extern const char* STR_CATEGORY_PRINTING
= "XXX";

extern const char* STR_CATEGORY_STORAGE
= "XXX";

extern const char* STR_CATEGORY_SUPPORT
= "XXX";

extern const char* STR_PREFERENCES_WINDOW_TITLE
= "XXX";

extern const char* STR_MNU_EDIT_PREFERENCES
= "XXX" B_UTF8_ELLIPSIS;

extern const char* STR_SEL_ALL_CAT_ALL_EVT
= "XXX";

extern const char* STR_USEL_ALL_CAT_ALL_EVT
= "XXX";

extern const char* STR_SEL_CUR_CAT_ALL_EVT
= "XXX";

extern const char* STR_USEL_CUR_CAT_ALL_EVT
= "XXX";

extern const char* STR_ITEMS
= " XXX";

extern const char* STR_CLR_FOREGROUND
= "XXX";

extern const char* STR_CLR_BACKGROUND
= "XXX";

extern const char* STR_CLR_LIST_BACKGROUND
= "XXX";

extern const char* STR_CLR_LIST_TEXT
= "XXX";

extern const char* STR_CLR_LIST_SELECTED_TEXT
= "XXX";

extern const char* STR_CLR_LIST_SELECTED_BACKGROUND
= "XXX";

extern const char* STR_ZOOM_CATEGORY
= "XXX:";

extern const char* STR_ZOOM_EVENT
= "XXX";

extern const char* STR_ZOOM_DATETIME
= "XXX:";

extern const char* STR_ZOOM_THREADID
= "XXX:";

extern const char* STR_ZOOM_TEAMID
= "XXX:";

extern const char* STR_ZOOM_LINE
= "XXX:";

extern const char* STR_ZOOM_SEQUENCE
= "XXX:";

extern const char* STR_ZOOM_FILE
= "XXX:";

extern const char* STR_ZOOM_METHOD
= "XXX:";

extern const char* STR_ZOOM_CLASS
= "XXX:";

extern const char* STR_ZOOM_DESCRIPTION
= "XXX:";

extern const char* STR_CLOSE_ALL_OPEN_ZOOM_WINDOWS
= "XXX";

extern const char* STR_ENABLE_ALL_SUBITEMS
= "XXX";

extern const char* STR_DISABLE_ALL_SUBITEMS
= "XXX";

#endif /* LOCALE_TEST_STRINGS */


