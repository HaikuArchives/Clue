/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
//#define DEBUG 1

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _DIRECTORY_H
#include <Directory.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FILE_PANEL_H
#include <FilePanel.h>
#endif

#ifndef _FIND_DIRECTORY_H
#include <FindDirectory.h>
#endif

#ifndef _MENU_H
#include <Menu.h>
#endif

#ifndef _MENU_BAR_H
#include <MenuBar.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
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

#ifndef _SCROLL_BAR_H
#include <ScrollBar.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif

#ifndef LIVEVIEW_H
#include "LiveView.h"
#endif

#ifndef BACKVIEW_H
#include "BackView.h"
#endif

#ifndef MAINWINDOW_H
#include "MainWindow.h"
#endif

#ifndef STATUSBARVIEW_H
#include "StatusBarView.h"
#endif

extern BMessage g_Settings;

/***************************************************************
const declarations
***************************************************************/
static const char * const g_pAppSettingsName ("Clue_settings");


/***************************************************************
***************************************************************/
MainWindow :: MainWindow
	(
	void
	)
:	BWindow(BRect (100, 80, 450, 300), STR_WINDOW_TITLE_LIVE, B_DOCUMENT_WINDOW, B_ASYNCHRONOUS_CONTROLS)
,	m_pMenuBar (NULL)
,	m_pStatusBar (NULL)
,	m_LiveView (NULL)
,	m_backview (NULL)
,	m_SavePanel (NULL)
,	m_running (true)
,	m_IsLive (true)
{
	Register ();
/*
	float minWidth (0.0);
	float maxWidth (0.0);
	float minHeight (0.0);
	float maxHeight (0.0);
	GetSizeLimits (&minWidth, &maxWidth, &minHeight, &maxHeight);
	SetSizeLimits (250, maxWidth, 150, maxHeight);
*/
	BMessage msgData;

	if (B_OK == g_Settings.FindMessage ("WINDOW:Live!", &msgData))
	{
		BRect rc (0.0f, 0.0f, 0.0f, 0.0f);
		if (B_OK == msgData.FindRect ("Frame", &rc))
		{
			BPoint pt (rc.LeftTop ());
			MoveTo (pt.x, pt.y);
			pt = rc.RightBottom ();
			ResizeTo (pt.x, pt.y);
		}

		bool bVal (false);

		if (B_OK == msgData.FindBool ("Running", &bVal))
		{
			m_running = bVal;
		}
	}

	// menu bar
	m_pMenuBar = new BMenuBar (BRect (0, 0, 0, 0), "Clue Menu Bar");
	//add a dummy item to help calculate height, will remove later below
	m_pMenuBar->AddItem (new BMenuItem ("", new BMessage ('1234')));

	// add child after menus are added so its initially
	// calculated app_server bounds take added menus into account
	AddChild (m_pMenuBar);
	
	float menuHeight = m_pMenuBar->Bounds().Height();

	BRect rc (Bounds ());
	rc.top = menuHeight + 1.0;
	rc.bottom = 75.0;
	m_LiveView = new LiveView ((BWindow *) this, rc);
	AddChild (m_LiveView);
	rc = Bounds ();
	rc.top = m_LiveView->Frame().bottom + 1.0;
	rc.bottom -= B_H_SCROLL_BAR_HEIGHT;
	m_backview = new BackView (rc);
	AddChild (m_backview);
	rc.top = rc.bottom + 1;
	rc.bottom = rc.top + B_H_SCROLL_BAR_HEIGHT - 1;
	rc.right -= B_V_SCROLL_BAR_WIDTH;
	m_pStatusBar = new StatusBarView (rc);
	AddChild (m_pStatusBar);

	//remove dummy item from above that was used to calc height
	BMenuItem * pMenuItem (m_pMenuBar->RemoveItem ((int32) 0));
	delete pMenuItem;

	// File menu
	BMenu * pMenu = BuildFileMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}
	// Edit menu
	pMenu = BuildEditMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}
	// Window menu
	pMenu = BuildWindowMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}

	if (m_running)
	{
		BMessage msg (MSG_MENU_FILE_START);
		MessageReceived (&msg);
	}
}


/***************************************************************
***************************************************************/
MainWindow :: MainWindow
	(
	entry_ref * ref
	)
:	BWindow(BRect (100, 80, 450, 300), STR_WINDOW_TITLE_LIVE, B_DOCUMENT_WINDOW, B_ASYNCHRONOUS_CONTROLS)
,	m_pMenuBar (NULL)
,	m_pStatusBar (NULL)
,	m_LiveView (NULL)
,	m_backview (NULL)
,	m_SavePanel (NULL)
,	m_running (false)
,	m_IsLive (false)
{
	char name[B_FILE_NAME_LENGTH];
	char title[6 + B_FILE_NAME_LENGTH];
	BEntry entry (ref);
	entry.GetName (name);
	sprintf (title, "Clue - %s", name);
	SetTitle (title);
	Register ();

	BMessage msgData;
	if (B_OK == g_Settings.FindMessage ("WINDOW:File", &msgData))
	{
		BRect rc (0.0f, 0.0f, 0.0f, 0.0f);
		if (B_OK == msgData.FindRect ("Frame", &rc))
		{
			BPoint pt (rc.LeftTop ());
			MoveTo (pt.x, pt.y);
			pt = rc.RightBottom ();
			ResizeTo (pt.x, pt.y);
		}
		msgData.FindBool ("Running", &m_running);
	}

	BMessage archive;
	BFile file (ref, B_READ_WRITE);

	if (B_OK == file.InitCheck ())
	{
		archive.Unflatten (&file);
	}

	// menu bar
	m_pMenuBar = new BMenuBar (BRect (0, 0, 0, 0), "Clue Menu Bar");
	//add a dummy item to help calculate height, will remove later below
	m_pMenuBar->AddItem (new BMenuItem ("", new BMessage ('1234')));

	// add child after menus are added so its initially
	// calculated app_server bounds take added menus into account
	AddChild (m_pMenuBar);
	
	float menuHeight = m_pMenuBar->Bounds().Height();

	BRect rc (Bounds ());
	rc.top = menuHeight + 1;
	rc.bottom -= B_H_SCROLL_BAR_HEIGHT;
	m_backview = new BackView (rc, &archive);
	AddChild (m_backview);
	rc.top = rc.bottom + 1;
	rc.bottom = rc.top + B_H_SCROLL_BAR_HEIGHT - 1;
	rc.right -= B_V_SCROLL_BAR_WIDTH;
	m_pStatusBar = new StatusBarView (rc);
	AddChild (m_pStatusBar);

	//remove dummy item from above that was used to calc height
	BMenuItem * pMenuItem (m_pMenuBar->RemoveItem ((int32) 0));
	delete pMenuItem;

	// File menu
	BMenu * pMenu = BuildFileMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}
	// Edit menu
	pMenu = BuildEditMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}
	// Window menu
	pMenu = BuildWindowMenu ();
	if (pMenu)
	{
		m_pMenuBar->AddItem (pMenu);
	}
}


/***************************************************************
***************************************************************/
MainWindow :: ~MainWindow
	(
	void
	)
{
	BMessage tmpmsg ('temp');
	BMessage msgData ('mask');
	BRect size (Frame ());
	size.right = Bounds().Width ();
	size.bottom = Bounds().Height ();
	msgData.AddRect ("Frame", size);
	msgData.AddBool ("Running", m_running);
	PRINT (("SAVING msgData: Running = %i\n", m_running));

	if (B_OK == g_Settings.FindMessage (m_IsLive ? "WINDOW:Live!" : "WINDOW:File", &tmpmsg))
	{
		g_Settings.ReplaceMessage (m_IsLive ? "WINDOW:Live!" : "WINDOW:File", &msgData);
	}
	else
	{
		g_Settings.AddMessage (m_IsLive ? "WINDOW:Live!" : "WINDOW:File", &msgData);
	}

	if (m_SavePanel)
	{
		delete m_SavePanel;
		m_SavePanel = NULL;
	}

	UnRegister ();
}


/***************************************************************
***************************************************************/
void
MainWindow :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
		case B_COPY_TARGET:
			message->PrintToStream ();
			break;
		case MSG_BROADCAST_SETTINGS_CHANGED:
			SendNotices (MSG_SETTINGS_CHANGED);
			SetFilePanelColors ();
			break;
		case 'bltm':
			PRINT (("switch to this window.\n"));
			if (! IsActive ())
			{
				//Show ();
				Activate ();
			}
			break;
		case MSG_UPDATE_STATUS_UI:
			{
			PRINT (("BWindow :: MSG_UPDATE_STATUS_UI\n"));
			const char * pMessage (NULL);
			if (B_OK == message->FindString ("string", &pMessage))
			{
				m_pStatusBar->SetPaneText (pMessage);
			}
			}
			break;
		case MSG_MENU_FILE_START:
			PRINT (("MSG_MENU_FILE_START\n"));
			m_running = true;
			m_backview->Listen (m_running);
			m_LiveView->Listen (m_running);
			PRINT (("Start UP Messenger\n"));
			break;
		case MSG_MENU_FILE_STOP:
			PRINT (("MSG_MENU_FILE_STOP\n"));
			m_running = false;
			m_backview->Listen (m_running);
			m_LiveView->Listen (m_running);
			PRINT (("Stop messenger\n"));
			break;
		case MSG_MENU_FILE_EXPORT:
			Export (message);
			break;
		case B_SAVE_REQUESTED:
			Save (message);
			break;
		default:
			BWindow::MessageReceived (message);
			break;
	}
}


/***************************************************************
***************************************************************/
bool
MainWindow :: QuitRequested
	(
	void
	)
{
	return (true);
}


/***************************************************************
***************************************************************/
void
MainWindow :: MenusBeginning
	(
	void
	)
{
	if (m_IsLive)
	{
		BMenu * menu (m_pMenuBar->SubmenuAt (0));
		if (menu)
		{
			ActiveMenuItem * mi ((ActiveMenuItem *) menu->ItemAt (0));
			if (mi)
			{
				if (m_running)
				{
					mi->SetLabel (STR_MNU_FILE_STOP);
					mi->SetMessage (new BMessage (MSG_MENU_FILE_STOP));
					mi->SetStatusBarMessage (STR_STATUS_STOP);
				}
				else
				{
					mi->SetLabel (STR_MNU_FILE_START);
					mi->SetMessage (new BMessage (MSG_MENU_FILE_START));
					mi->SetStatusBarMessage (STR_STATUS_START);
				}
			}
		}
	}


	BMenu * menu (m_pMenuBar->SubmenuAt (2));
	if (menu)
	{
		//first, remove all existing items
		BMenuItem * mi (menu->RemoveItem ((int32)0));
		while (mi)
		{
			delete mi;
			mi = menu->RemoveItem ((int32)0);
		}
			
		BMessenger messenger (be_app);
		BMessage message ('bldm');
		message.AddPointer ("from", this);
		message.AddPointer ("menu", menu);
		messenger.SendMessage (&message, this);
	}
}

/***************************************************************
***************************************************************/
BMenu *
MainWindow :: BuildFileMenu
	(
	void
	)
	const
{
	BMenu * pMenu (new BMenu (STR_MNU_FILE));
	
	ActiveMenuItem * pAMI (NULL);
	if (m_IsLive)
	{
		pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_START, m_running ? STR_STATUS_STOP : STR_STATUS_START,
			new BMessage (m_running ? MSG_MENU_FILE_STOP : MSG_MENU_FILE_START), CMD_FILE_START_STOP);
		pAMI->SetTarget (this, this);
		pMenu->AddItem (pAMI);
		pMenu->AddSeparatorItem ();
	}
	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_OPEN, STR_STATUS_MNU_FILE_OPEN, new BMessage (MSG_MENU_FILE_OPEN), CMD_FILE_OPEN);
	pAMI->SetTarget (NULL, be_app);
//pAMI->SetEnabled (false);
	pMenu->AddItem (pAMI);
//	if (m_IsLive)
//	{
		pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_EXPORT, STR_STATUS_MNU_FILE_EXPORT, new BMessage (MSG_MENU_FILE_EXPORT), CMD_FILE_EXPORT);
		pAMI->SetTarget (this, this);
//pAMI->SetEnabled (false);
		pMenu->AddItem (pAMI);
		pMenu->AddSeparatorItem ();
//	}
	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_PAGE_SETUP, STR_STATUS_PAGE_SETUP, new BMessage (MSG_PRINTER_PAGE_SETUP), CMD_FILE_PAGE_SETUP, B_SHIFT_KEY);
	pAMI->SetTarget (m_backview, this);
pAMI->SetEnabled (false);
	pMenu->AddItem (pAMI);

	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_PRINT, STR_STATUS_PRINT, new BMessage (MSG_PRINTER_PRINT), CMD_FILE_PRINT);
	pAMI->SetTarget (m_backview, this);
pAMI->SetEnabled (false);
	pMenu->AddItem (pAMI);
	pMenu->AddSeparatorItem ();
	
//	BMenuItem * pAboutItem (new CActiveMenuItem (STR_MNU_FILE_ABOUT, STR_STATUS_MNU_FILE_ABOUT,
//		new BMessage (B_ABOUT_REQUESTED)));

	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_HELP, STR_STATUS_MNU_FILE_HELP, new BMessage (MSG_HELP), CMD_FILE_HELP);
	pAMI->SetTarget (NULL, be_app);
	pMenu->AddItem (pAMI);
	
	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_ABOUT, STR_STATUS_MNU_FILE_ABOUT, new BMessage (B_ABOUT_REQUESTED));
	pAMI->SetTarget (NULL, be_app);
	pMenu->AddItem (pAMI);
	
	pMenu->AddSeparatorItem ();
	
	pMenu->AddItem (new ActiveMenuItem ((BWindow *) this, STR_MNU_FILE_CLOSE, STR_STATUS_MNU_FILE_CLOSE,
		new BMessage (B_QUIT_REQUESTED), CMD_FILE_CLOSE));
		
	return pMenu;
}


/***************************************************************
***************************************************************/
BMenu *
MainWindow :: BuildEditMenu
	(
	void
	)
	const
{
	BMenu * pMenu (new BMenu (STR_MNU_EDIT));
	ActiveMenuItem * pAMI (NULL);

	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_EDIT_COPY, STR_STATUS_MNU_EDIT_COPY, new BMessage (B_COPY), CMD_FILE_EDIT_COPY);
	pAMI->SetTarget (NULL, this);
//pAMI->SetEnabled (false);
	pMenu->AddItem (pAMI);

	pMenu->AddSeparatorItem ();

	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_EDIT_SELECT_ALL, STR_STATUS_MNU_EDIT_SELECT_ALL, new BMessage (B_SELECT_ALL), CMD_FILE_EDIT_SELECT_ALL);
	pAMI->SetTarget (NULL, this);
//pAMI->SetEnabled (false);
	pMenu->AddItem (pAMI);

	pMenu->AddSeparatorItem ();

	pAMI = new ActiveMenuItem ((BWindow *) this, STR_MNU_EDIT_PREFERENCES, STR_STATUS_MNU_EDIT_PREFERENCES, new BMessage (MSG_MENU_EDIT_PREFERENCES));
	pAMI->SetTarget (NULL, be_app);
	pMenu->AddItem (pAMI);
		
	return pMenu;
}


/***************************************************************
***************************************************************/
BMenu *
MainWindow :: BuildWindowMenu
	(
	void
	)
	const
{
	PRINT (("BuildWindowMenu\n"));
	BMenu * pMenu = new BMenu (STR_MNU_WINDOW);
	//BMessenger (be_app);
	
	//pMenu->AddItem (new CActiveMenuItem (STR_MNU_VIEW_LIVE, MSG_UPDATE_STATUS_UI, new BMessage (B_ABOUT_REQUESTED)));
		
	return pMenu;
}


/***************************************************************
***************************************************************/
StatusBarView *
MainWindow :: GetStatusBar
	(
	void
	)
	const
{
	return m_pStatusBar;
}


/***************************************************************
***************************************************************/
void
MainWindow :: Export
	(
	BMessage * message
	)
{
	PRINT (("ClueWindow :: Export\n"));
	// Create the save filepanel for this window
	if (! m_SavePanel)
	{
		PRINT ((" m_SavePanel was NULL, create it\n"));
		BMessenger msgr (this); //the BFP will make a copy of the messenger for its use
		m_SavePanel = new BFilePanel (B_SAVE_PANEL, &msgr, NULL, B_FILE_NODE, false);
		SetFilePanelColors ();
	}

	PRINT ((" m_SavePanel->Show\n"));
	m_SavePanel->Show();
	PRINT (("ClueWindow :: Export finished\n"));
}


/***************************************************************
***************************************************************/
void
MainWindow :: Save
	(
	BMessage * message
	)
{
	PRINT ((" Save.\n"));
	entry_ref ref;		// For the directory to save into
	const char *name;	// For the filename

	// Peel the entry_ref and name of the directory and file out of the message.
	if (message->FindRef ("directory", &ref) != B_OK) {
		PRINT (("Error dir\n"));
		return;
	}
	if (message->FindString ("name", &name) != B_OK) {
		PRINT (("error name\n"));
		return;
	}
	
	BDirectory dir (&ref);
	BEntry entry (&dir, name);
	entry.GetRef (&ref);

	// open the file for writing
	BFile file (&ref, B_WRITE_ONLY | B_ERASE_FILE | B_CREATE_FILE);
	if (file.InitCheck() != B_OK)
	{
		PRINT (("error InitCheck\n"));
		return;
	}

	m_backview->Export (&file);

	// set the file's MIME type
	BNodeInfo ni (&file);
	ni.SetType (STR_FILE_SIG);
	PRINT (("Save finished\n"));
}


/***************************************************************
***************************************************************/
void
MainWindow :: Register
	(
	void
	)
{
	BMessenger messenger (be_app);
	BMessage message (MSG_WINDOW_REGISTRY_ADD);
	if (m_IsLive)
	{
		message.AddBool ("live", m_IsLive);
	}
	message.AddString ("title", Title ());
	message.AddPointer ("window", this);
	messenger.SendMessage (&message, this);
}


/***************************************************************
HelloWindow::Unregister

 Unregisters a window.  This tells the application that
 one fewer windows are open.  The application will
 automatically quit if the count goes to zero because
 of this call.
***************************************************************/
void
MainWindow :: UnRegister
	(
	void
	)
{
	BMessenger messenger (be_app);
	BMessage message (MSG_WINDOW_REGISTRY_SUB);
	message.AddPointer ("window", this);
	messenger.SendMessage (&message);
}


void
MainWindow :: SetFilePanelColors
	(
	void
	)
{
	if (m_SavePanel)
	{
		if (B_OK == m_SavePanel->Window()->LockWithTimeout (1000000))
		{
			BView * pView (m_SavePanel->Window()->ChildAt(0));
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

				pChild = pView->FindView ("text view");
				if (pChild)
				{
					pChild->SetViewColor (CLR_BACKGROUND);
					pChild->SetLowColor (CLR_BACKGROUND);
					pChild->Invalidate ();
				}
			}
			m_SavePanel->Window()->Unlock ();
		}
	}
}
