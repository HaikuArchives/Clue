/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
#define DEBUG 1

#include <cassert>

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _DIRECTORY_H
#include <Directory.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _FILE_PANEL_H
#include <FilePanel.h>
#endif

#ifndef _FIND_DIRECTORY_H
#include <FindDirectory.h>
#endif

#ifndef _BE_LIST_H
#include <List.h>
#endif

#ifndef _MENU_H
#include <Menu.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _NODE_H
#include <Node.h>
#endif

#ifndef _NODE_INFO_H
#include <NodeInfo.h>
#endif

#ifndef _PATH_H
#include <Path.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef THEAPP_H
#include "TheApp.h"
#endif

#ifndef MAINWINDOW_H
#include "MainWindow.h"
#endif

#ifndef PRINTWINDOW_H
#include "PrintWindow.h"
#endif

#ifndef DROP_WINDOW_H
#include "DragMessageWindow.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef REFFILTER_H_JLB
#include "RefFilter.h"
#endif

#ifndef _SPLASH_H
#include "SplashWindow.h"
#endif

#ifndef _TOOLTIPWINDOW_H
#include "ToolTipWindow.h"
#endif

#ifndef _PREFERENCESWND_H
#include "PreferencesWnd.h"
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif


const char * g_pAppSettingsName = "Clue_settings";
const char * g_pAppSettingsName1 = "Clue_settings_1";

BBitmap * g_bmpCategories[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
BBitmap * g_bmpEvents[12] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
BBitmap * g_DefaultBMP (NULL);
BBitmap * g_OtherBmps[2] = {NULL, NULL};
volatile sem_id g_SettingsSemaphore;  //already defined in CBackView
BMessage g_Settings ('0000');

BWindow * pLive (NULL);
BWindow * pDragViewer (NULL);
BWindow * pPrinter (NULL);
BList pWindows;
bool bArgsSent (false);


const int32 TheApp::SETTINGS_FORMAT_VERSION = 1;


/*
class RefFilter : public BRefFilter
{
	bool Filter (const entry_ref *, BNode *, struct stat *, const char *);
};

bool RefFilter::Filter(const entry_ref *ref, BNode * node, struct stat * st, const char * filetype)
{
	if (S_ISDIR(st->st_mode))
	{
		return true;
	}
	else if (S_ISREG(st->st_mode))
	{
		if (strcmp (filetype, STR_FILE_SIG) == 0)
		{
			return true;
		}
	}
	else if (S_ISLNK(st->st_mode))
	{
		BEntry entry (ref, true);
		if (B_OK == entry.InitCheck ())
		{
			BNode node (&entry);
			if (B_OK == node.InitCheck ())
			{
				if (node.IsDirectory ())
				{
					return true;
				}
				else
				{
					BNodeInfo info (&node);
					if (B_OK == info.InitCheck ())
					{
						char filetype[B_MIME_TYPE_LENGTH];
						info.GetType (filetype);
						if (strcmp (filetype, STR_FILE_SIG) == 0)
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}
*/


/***************************************************************
***************************************************************/
TheApp :: TheApp
	(
	void
	)
:	BApplication (STR_APP_SIG)
,	m_pSplashWnd (NULL)
,	m_pPreferencesWnd (NULL)
,	m_window_count (0)
,	m_next_untitled_number (1)
,	m_OpenPanel (NULL)
,	m_RF (NULL)
{
#ifdef DEBUG
#define RETRIEVE_BITMAP_INTO(target, nameliteral) do{(target) = RetrieveBitmap(nameliteral); ASSERT_WITH_MESSAGE(NULL != (target), "Unable to Retrive Resource Bitmap " nameliteral);} while(0);
#else
#define RETRIEVE_BITMAP_INTO(target, nameliteral) do{(target) = RetrieveBitmap(nameliteral); if (NULL == (target)) abort();} while(0);
#endif
	
	g_SettingsSemaphore = create_sem (1, "SettingsSemaphore");
	GetSettings ();
	UpdateColors ();

	RETRIEVE_BITMAP_INTO(g_OtherBmps[0], "Selected");
	TransparentSetBits (g_OtherBmps[0],	255, 128, 192);
	RETRIEVE_BITMAP_INTO(g_OtherBmps[1], "FilterEnable");

	RETRIEVE_BITMAP_INTO(g_bmpEvents[0], "CE_BIRTH");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[1], "CE_DEATH");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[2], "CE_ENTER");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[3], "CE_EXIT");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[4], "CE_OK");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[5], "CE_INFO");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[6], "CE_WARNING");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[7], "CE_ERROR");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[8], "CE_SUCCEEDED");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[9], "CE_FAILED");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[10], "CE_TIMER");
	RETRIEVE_BITMAP_INTO(g_bmpEvents[11], "CE_OBJECT");

	TransparentSetBits (g_bmpEvents[0],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[1],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[2],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[3],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[4],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[5],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[6],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[7],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[8],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[9],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[10],	255, 128, 192);
	TransparentSetBits (g_bmpEvents[11],	255, 128, 192);

	RETRIEVE_BITMAP_INTO(g_DefaultBMP, "default");
	TransparentSetBits (g_DefaultBMP, 255, 128, 192);

	RETRIEVE_BITMAP_INTO(g_bmpCategories[0], "CC_GENERAL");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[1], "default");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[2], "CC_INTERFACE");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[3], "CC_MEDIA");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[4], "CC_STORAGE");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[5], "CC_SUPPORT");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[6], "CC_NETWORK");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[7], "CC_MOUSE");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[8], "CC_KEYBOARD");
	RETRIEVE_BITMAP_INTO(g_bmpCategories[9], "CC_PRINTING");

	TransparentSetBits (g_bmpCategories[0],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[1],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[2],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[3],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[4],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[5],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[6],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[7],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[8],	255, 128, 192);
	TransparentSetBits (g_bmpCategories[9],	255, 128, 192);

	m_pToolTip = new ToolTipWindow ();
	assert(NULL != m_pToolTip); // @TODO new() fail

	// instantiate a new window and show it
	m_pSplashWnd = new SplashWindow (&m_pSplashWnd, true);
	assert(NULL != m_pSplashWnd); // @TODO new() fail

#undef RETRIEVE_BITMAP
}


/***************************************************************
***************************************************************/
TheApp :: ~TheApp
	(
	void
	)
{
	//now delete the bitmaps in the array
	int bmpcount (0);
	BBitmap * pbmp (NULL);
	int i (0);


	if (g_DefaultBMP)
	{
		delete g_DefaultBMP;
		g_DefaultBMP = NULL;
	}
	
	if (m_OpenPanel)
	{
		RefFilter * pRF (dynamic_cast<RefFilter *>(m_OpenPanel->RefFilter ()));
		
		if (pRF)
		{
			delete pRF;
			pRF = NULL;
		}

		delete m_OpenPanel;
		m_OpenPanel = NULL;
	}
	
	if (m_RF)
	{
		delete m_RF;
		m_RF = NULL;
	}

	bmpcount = sizeof (g_bmpEvents) / sizeof(g_bmpEvents[0]);
	for (i = 0; i < bmpcount; i++)
	{
		pbmp = g_bmpEvents[i];
		if (pbmp)
		{
			delete pbmp;
			g_bmpEvents[i] = NULL;
		}
	}

	bmpcount = sizeof (g_bmpCategories) / sizeof(g_bmpCategories[0]);
	for (i = 0; i < bmpcount; i++)
	{
		pbmp = g_bmpCategories[i];
		if (pbmp)
		{
			delete pbmp;
			g_bmpCategories[i] = NULL;
		}
	}

	bmpcount = sizeof (g_OtherBmps) / sizeof(g_OtherBmps[0]);
	for (i = 0; i < bmpcount; i++)
	{
		pbmp = g_OtherBmps[i];
		if (pbmp)
		{
			delete pbmp;
			g_OtherBmps[i] = NULL;
		}
	}

	SaveSettings ();
}


/***************************************************************
***************************************************************/
void
TheApp :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
		case B_SOME_APP_ACTIVATED:
		case MSG_TOOL_TIP_START:
		case MSG_TOOL_TIP_STOP:
			PRINT (("Tooltip message.\n"));
			m_pToolTip->PostMessage (message);
			break;
		case 'bltm':
			PRINT (("switch to Clue - Live! window\n"));
			if (! pLive)
			{
				(reinterpret_cast<MainWindow *>(new MainWindow ()))->Show ();
			}
			break;
		case 'msgv':
			if (!pDragViewer)
			{
				(reinterpret_cast<DragMessageWindow *>(new DragMessageWindow ()))->Show ();
			}
			break;
		case 'prtr':
			pPrinter = reinterpret_cast<PrintWindow *>(new PrintWindow ());
			pPrinter->Show ();
			break;
		case 'bldm':
			{
//			BMenuItem * mi (NULL);
			BWindow * from (NULL);
			message->FindPointer ("from", (void **) &from);
			BMenu * menu (NULL);
			ActiveMenuItem * pAMI (NULL);

			message->FindPointer ("menu", (void **) &menu);
//			mi = new BMenuItem (STR_WINDOW_TITLE_LIVE, new BMessage ('bltm'));
			pAMI = new ActiveMenuItem (from, STR_WINDOW_TITLE_LIVE, "Switch to this window", new BMessage ('bltm'));
			if (pLive)
			{
				if (from == pLive)
				{
					pAMI->SetMarked (true);
				}
				pAMI->SetTarget (pLive);
			}
			else
			{
				pAMI->SetTarget (this);
			}
			menu->AddItem (pAMI);
/*
			mi = new BMenuItem ("DragMessageView", new BMessage ('msgv'));
			if (pDragViewer)
			{
				if (from == pDragViewer)
				{
					mi->SetMarked (true);
				}
				mi->SetTarget (pDragViewer);
			}
			else
			{
				mi->SetTarget (this);
			}
			menu->AddItem (mi);

			mi = new BMenuItem ("Printer", new BMessage ('prtr'));
			if (pPrinter)
			{
				if (from == pPrinter)
				{
					mi->SetMarked (true);
				}
				mi->SetTarget (pPrinter);
			}
			else
			{
				mi->SetTarget (this);
			}
			menu->AddItem (mi);
*/
			int32 count (pWindows.CountItems ());
			if (count)
			{
				menu->AddSeparatorItem ();
				BWindow * pwnd (NULL);
				BMessage * msg (NULL);

				while (count--)
				{
					msg = (BMessage *) pWindows.ItemAt (count);
					//pwnd = (BWindow *) pWindows.ItemAt (count);
					if (B_OK == msg->FindPointer ("window", (void **) &pwnd))
					{
						const char * pchar (NULL);
						if (B_OK == msg->FindString ("title", (const char **) &pchar))
						{
							pAMI = new ActiveMenuItem (from, pchar, "Switch to this window", new BMessage ('bltm'));
//							mi = new BMenuItem (pchar, new BMessage ('bltm'));
							if (from == pwnd)
							{
								pAMI->SetMarked (true);
							}
							pAMI->SetTarget (pwnd);
							menu->AddItem (pAMI);
						}
					}
				}
			}
			}
			break;
		case MSG_WINDOW_REGISTRY_ADD:
			PRINT (("MSG_WINDOW_REGISTRY_ADD\n"));
		{
			bool tmpbool (false);
			BWindow * pwindow (NULL);
			message->FindPointer ("window", (void **) &pwindow);
			if (B_OK == message->FindBool ("live", &tmpbool))
			{
				pLive = pwindow;
			}
			else if (B_OK == message->FindBool ("DragMessageViewer", &tmpbool))
			{
				pDragViewer = pwindow;
			}
			else if (B_OK == message->FindBool ("Printer", &tmpbool))
			{
				pPrinter = pwindow;
			}
			else
			{
				DetachCurrentMessage ();
				pWindows.AddItem (message, 0);
			}
			++m_window_count;
		}
			break;
		case MSG_WINDOW_REGISTRY_SUB:
			PRINT (("MSG_WINDOW_REGISTRY_SUB\n"));
		{
			BWindow * pwindow (NULL);

			if (B_OK == message->FindPointer ("window", (void **) &pwindow))
			{
				if (pLive == pwindow)
				{
					pLive = NULL;
				}
				else if (pDragViewer == pwindow)
				{
					pDragViewer = NULL;
				}
				else if (pPrinter == pwindow)
				{
					pPrinter = NULL;
				}
				else
				{
					int32 count (pWindows.CountItems ());
					BWindow * pwnd (NULL);
					BMessage * msg (NULL);
					while (count--)
					{
						msg = (BMessage *) pWindows.ItemAt (count);
						if (B_OK == msg->FindPointer ("window", (void **) &pwnd))
						{
							if (pwnd == pwindow)
							{
								msg = (BMessage *) pWindows.RemoveItem (count);
								delete msg;
								break;
							}
						}
					}
				}
			}

			--m_window_count;

			if (!m_window_count)
			{
				PRINT ((" m_window_count was zero, quit.\n"));
				PostMessage (B_QUIT_REQUESTED);
			}
		}
			break;
		case MSG_MENU_FILE_OPEN:
			PRINT (("MSG_MENU_FILE_IMPORT\n"));
			if (!m_OpenPanel)
			{
				m_OpenPanel = new BFilePanel (B_OPEN_PANEL, NULL, NULL, 0, true, NULL, new RefFilter);
				SetFilePanelColors ();

			}
			m_OpenPanel->Show ();		// Show the file panel
			break;
		case MSG_MENU_EDIT_PREFERENCES:
			if (NULL == m_pPreferencesWnd)
			{
				BMessage msg ('root');
				msg.AddString (STR_CLR_FOREGROUND, "CLR_FOREGROUND");
				msg.AddString (STR_CLR_BACKGROUND, "CLR_BACKGROUND");
				msg.AddString (STR_CLR_LIST_BACKGROUND, "CLR_LIST_BACKGROUND");
				msg.AddString (STR_CLR_LIST_TEXT, "CLR_LIST_TEXT");
				msg.AddString (STR_CLR_LIST_SELECTED_TEXT, "CLR_LIST_SELECTED_TEXT");
				msg.AddString (STR_CLR_LIST_SELECTED_BACKGROUND, "CLR_LIST_SELECTED_BACKGROUND");

				m_pPreferencesWnd = new PreferencesWnd (&m_pPreferencesWnd, &msg);
			}
			else
			{
				m_pPreferencesWnd->Lock ();
				m_pPreferencesWnd->Activate ();
				m_pPreferencesWnd->Unlock ();
			}
			break;
		case MSG_BROADCAST_SETTINGS_CHANGED:
			{
			BMessage msg ('0000');
#ifdef CLUE_ON_ZETA_HACK
			char const * name (NULL);
#else	
			char * name (NULL);
#endif
			uint32 type (0);
			int32 count (0);
			for (int32 i (0); message->GetInfo (B_MESSAGE_TYPE, i, &name, &type, &count) == B_OK; i++)
			{
				switch (message->FindMessage (name, &msg))
				{
				case B_OK:
					PRINT (("App\n"));
					for (int32 j (0); j < count; j++)
					{
						if (B_OK == g_Settings.ReplaceMessage (name, &msg))
						{
							PRINT (("successful replacement\n"));
						}
					}
				}
			}

			UpdateColors ();
			
			count = CountWindows ();
			BWindow * pwnd (NULL);

			while (count-- > 0)
			{
				pwnd = WindowAt (count);
				if (pwnd)
				{
					if (pwnd->Lock ())
					{
						pwnd->PostMessage (MSG_BROADCAST_SETTINGS_CHANGED);
						pwnd->Unlock ();
					}
				}
			}

			SetFilePanelColors ();

			}
			break;
		case MSG_HELP:
			OpenHelp ();
			break;
		case MSG_CLOSE_ALL_ZOOM_WINDOWS:
			PRINT (("BApp received MSG_CLOSE_ALL_ZOOM_WINDOWS message\n"));
			CloseZoomWindows ();
			break;
		default:
			BApplication::MessageReceived(message);
			break;
	}
}


/***************************************************************
***************************************************************/
void
TheApp :: AppActivated
	(
	bool active
	)
{
	PRINT (("AppActivated\n"));
}


/***************************************************************
***************************************************************/
void
TheApp :: ArgvReceived
	(
	int32 argc
,	char ** argv
	)
{
	PRINT (("ArgsReceived\n"));
	bArgsSent = true;
}


/***************************************************************
***************************************************************/
void
TheApp :: AboutRequested
	(
	void
	)
{
	if (NULL == m_pSplashWnd)
	{
		m_pSplashWnd = new SplashWindow (&m_pSplashWnd, false);
	}
	else
	{
		m_pSplashWnd->Lock ();
		m_pSplashWnd->Activate ();
		m_pSplashWnd->Unlock ();
	}
}


/***************************************************************
***************************************************************/
void
TheApp :: ReadyToRun
	(
	void
	)
{
	PRINT (("ReadyToRun\n"));
	if (! bArgsSent)
	{
		(reinterpret_cast<MainWindow *>(new MainWindow ()))->Show ();
	}
	if (m_pSplashWnd)
	{
		m_pSplashWnd->BeginCountdown ();
	}
}


/***************************************************************
***************************************************************/
void
TheApp :: RefsReceived
	(
	BMessage * message
	)
{
	PRINT (("RefsReceived\n"));
	status_t 	rc (B_ERROR);		// The error code
	int32		ref_num (0);	// The index into the ref list
	entry_ref 	ref;

	bArgsSent = true;
	// Loop through the ref list and open each one
	do
	{
		rc = message->FindRef ("refs", ref_num++, &ref);
		if (B_OK != rc)
		{
			return;
		}
		(reinterpret_cast<MainWindow *>(new MainWindow (&ref)))->Show ();
	}
	while (true);
}


/***************************************************************
***************************************************************/
void
TheApp :: GetSettings
	(
	void
	)
{
	acquire_sem (g_SettingsSemaphore);
	BPath SettingsPath;
	if (B_OK == find_directory (B_USER_SETTINGS_DIRECTORY, &SettingsPath))
	{
		SettingsPath.SetTo (SettingsPath.Path (), g_pAppSettingsName);
		BFile file (SettingsPath.Path (), B_READ_ONLY | B_CREATE_FILE);
		if (B_OK == file.InitCheck ())
		{
			if (B_OK == g_Settings.Unflatten (&file))
			{

				int32 schema (0);
				g_Settings.FindInt32 ("SETTINGS_FORMAT_VERSION", &schema);
				
				Migrate (schema);
			}
		}
	}
	
	VerifySettings ();

	release_sem (g_SettingsSemaphore);
}


/***************************************************************
***************************************************************/
void
TheApp :: VerifySettings
	(
	void
	)
{

		BMessage msgData (B_RGB_COLOR_TYPE);
		BMessage tmpmsg ('0000');
		if (B_OK != g_Settings.FindMessage ("CLR_FOREGROUND", &tmpmsg))
		{
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_FOREGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_FOREGROUND", &msgData);
		}

		if (B_OK != g_Settings.FindMessage ("CLR_BACKGROUND", &tmpmsg))
		{
			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_BACKGROUND", &msgData);
		}

		if (B_OK != g_Settings.FindMessage ("CLR_LIST_BACKGROUND", &tmpmsg))
		{
			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_BACKGROUND", &msgData);
		}

		if (B_OK != g_Settings.FindMessage ("CLR_LIST_TEXT", &tmpmsg))
		{
			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_TEXT, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_TEXT", &msgData);
		}

		if (B_OK != g_Settings.FindMessage ("CLR_LIST_SELECTED_TEXT", &tmpmsg))
		{
			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_SELECTED_TEXT, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_SELECTED_TEXT", &msgData);
		}

		if (B_OK != g_Settings.FindMessage ("CLR_LIST_SELECTED_BACKGROUND", &tmpmsg))
		{
			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_SELECTED_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_SELECTED_BACKGROUND", &msgData);
		}

		int32 val (0);
		if (B_OK != g_Settings.FindInt32 ("SETTINGS_FORMAT_VERSION", &val))
		{
			g_Settings.AddInt32 ("SETTINGS_FORMAT_VERSION", SETTINGS_FORMAT_VERSION);
		}
}


/***************************************************************
***************************************************************/
void
TheApp :: Migrate
	(
	int32 schema
	)
{
	BMessage tmpmsg (g_Settings);
	
	switch (schema)
	{
		case 0:
			{
			g_Settings.MakeEmpty ();

			float l (100), t (80), r (450), b (300);
			tmpmsg.FindFloat ("left", &l);
			tmpmsg.FindFloat ("top", &t);
			tmpmsg.FindFloat ("right", &r);
			tmpmsg.FindFloat ("bottom", &b);
			
			tmpmsg.MakeEmpty ();
			
			BRect rc (l, t, r, b);
			tmpmsg.AddRect ("Frame", rc);
			g_Settings.AddMessage ("WINDOW:Live!", &tmpmsg);

			tmpmsg.MakeEmpty ();
			tmpmsg.AddRect ("Frame", rc);
			g_Settings.AddMessage ("WINDOW:File", &tmpmsg);

			BMessage msgData (B_RGB_COLOR_TYPE);
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_FOREGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_FOREGROUND", &msgData);

			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_BACKGROUND", &msgData);

			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_BACKGROUND", &msgData);

			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_TEXT, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_TEXT", &msgData);

			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_SELECTED_TEXT, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_SELECTED_TEXT", &msgData);

			msgData.MakeEmpty ();
			msgData.AddData ("value", B_RGB_COLOR_TYPE, &CLR_LIST_SELECTED_BACKGROUND, sizeof(rgb_color));
			g_Settings.AddMessage ("CLR_LIST_SELECTED_BACKGROUND", &msgData);

			g_Settings.AddInt32 ("SETTINGS_FORMAT_VERSION", SETTINGS_FORMAT_VERSION);
			}
			break;
		case 1:
			break;
		default:
			break;
	}
}


void
TheApp :: SaveSettings
	(
	void
	)
{
	BPath SettingsPath;
	if (B_OK == find_directory (B_USER_SETTINGS_DIRECTORY, &SettingsPath))
	{
		SettingsPath.SetTo (SettingsPath.Path (), g_pAppSettingsName);
		BFile file (SettingsPath.Path (), B_WRITE_ONLY | B_CREATE_FILE | B_ERASE_FILE);
		if (B_OK == file.InitCheck ())
		{
			g_Settings.Flatten (static_cast<BDataIO *>(&file));
		}
	}
}


/***************************************************************
***************************************************************/
void
TheApp :: UpdateColors
	(
	void
	)
{
	ssize_t numBytes (0);
	BMessage msgtmp;
	rgb_color * pColor;

	if (B_OK == g_Settings.FindMessage ("CLR_FOREGROUND", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_FOREGROUND.red = pColor->red;
			CLR_FOREGROUND.green = pColor->green;
			CLR_FOREGROUND.blue = pColor->blue;
			CLR_FOREGROUND.alpha = 255;
		}
	}

	if (B_OK == g_Settings.FindMessage ("CLR_BACKGROUND", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_BACKGROUND.red = pColor->red;
			CLR_BACKGROUND.green = pColor->green;
			CLR_BACKGROUND.blue = pColor->blue;
			CLR_BACKGROUND.alpha = 255;
		}
	}

	if (B_OK == g_Settings.FindMessage ("CLR_LIST_BACKGROUND", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_LIST_BACKGROUND.red = pColor->red;
			CLR_LIST_BACKGROUND.green = pColor->green;
			CLR_LIST_BACKGROUND.blue = pColor->blue;
			CLR_LIST_BACKGROUND.alpha = 255;
		}
	}

	if (B_OK == g_Settings.FindMessage ("CLR_LIST_TEXT", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_LIST_TEXT.red = pColor->red;
			CLR_LIST_TEXT.green = pColor->green;
			CLR_LIST_TEXT.blue = pColor->blue;
			CLR_LIST_TEXT.alpha = 255;
		}
	}

	if (B_OK == g_Settings.FindMessage ("CLR_LIST_SELECTED_BACKGROUND", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_LIST_SELECTED_BACKGROUND.red = pColor->red;
			CLR_LIST_SELECTED_BACKGROUND.green = pColor->green;
			CLR_LIST_SELECTED_BACKGROUND.blue = pColor->blue;
			CLR_LIST_SELECTED_BACKGROUND.alpha = 255;
		}
	}

	if (B_OK == g_Settings.FindMessage ("CLR_LIST_SELECTED_TEXT", &msgtmp))
	{
		if (B_OK == msgtmp.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
		{
			CLR_LIST_SELECTED_TEXT.red = pColor->red;
			CLR_LIST_SELECTED_TEXT.green = pColor->green;
			CLR_LIST_SELECTED_TEXT.blue = pColor->blue;
			CLR_LIST_SELECTED_TEXT.alpha = 255;
		}
	}

	CLR_FOREGROUND_LITE = tint_color (CLR_FOREGROUND, B_LIGHTEN_2_TINT);
	CLR_FOREGROUND_DARK = tint_color (CLR_FOREGROUND, B_DARKEN_2_TINT);
	CLR_BACKGROUND_LITE = tint_color (CLR_BACKGROUND, B_LIGHTEN_2_TINT);
	CLR_BACKGROUND_DARK = tint_color (CLR_BACKGROUND, B_DARKEN_2_TINT);
}


/***************************************************************
***************************************************************/
void
TheApp :: SetFilePanelColors
	(
	void
	)
{
	if (m_OpenPanel)
	{
		if (B_OK == m_OpenPanel->Window()->LockWithTimeout (1000000))
		{
			BView * pView (m_OpenPanel->Window()->ChildAt(0));
			if (pView)
			{
				pView->SetViewColor (CLR_BACKGROUND);
				pView->SetLowColor (CLR_BACKGROUND);
				pView->Invalidate ();

				BView * pChild (pView->FindView ("DirMenuField"));
				if (pChild)
				{
					pChild->SetViewColor (CLR_BACKGROUND);
					pChild->SetLowColor (CLR_BACKGROUND);
					pChild->Invalidate ();
				}

				pChild = pView->FindView ("cancel button");
				if (pChild)
				{
					pChild->SetViewColor (CLR_BACKGROUND);
					pChild->SetLowColor (CLR_BACKGROUND);
					pChild->Invalidate ();
				}

				pChild = pView->FindView ("default button");
				if (pChild)
				{
					pChild->SetViewColor (CLR_BACKGROUND);
					pChild->SetLowColor (CLR_BACKGROUND);
					pChild->Invalidate ();
				}
			}
			m_OpenPanel->Window()->Unlock ();
		}
	}
}


void
TheApp :: OpenHelp
	(
	void
	)
{
	app_info ai;
	GetAppInfo (&ai);
	BEntry entry (&(ai.ref));
	status_t rc (entry.InitCheck ());
	if (B_OK == rc)
	{
		BPath path;
		entry.GetPath (&path);
		rc = path.InitCheck ();
		if (B_OK == rc)
		{
			rc = path.GetParent (&path);
			if (B_OK == rc)
			{
				BString URL ("file://");
				URL.Append (path.Path ());
				URL.Append ("/Documentation/index.html");
				char * pURL ((char *) URL.String ());
				be_roster->Launch ("text/html", 1, &pURL);
			}
		}
	}
}


void
TheApp :: CloseZoomWindows
	(
	void
	)
{
	int32 count (CountWindows ());
	BWindow * pwnd (NULL);

	while (count-- > 0)
	{
		status_t rc (B_ERROR);
		pwnd = WindowAt (count);
		if (pwnd)
		{
			rc = pwnd->LockWithTimeout (1000000);
			if (B_OK == rc)
			{
				PRINT (("Locked BWindow: %s\n", pwnd->Title ()));
				pwnd->PostMessage (MSG_CLOSE_ALL_ZOOM_WINDOWS);
				pwnd->Unlock ();
			}
		}
	}
}




