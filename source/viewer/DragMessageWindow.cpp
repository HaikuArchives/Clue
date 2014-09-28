/*

	DropWindow.cpp
	
*/
/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.
*/
//#define DEBUG 1

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FONT_H
#include <Font.h>
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

#ifndef DROP_WINDOW_H
#include "DragMessageWindow.h"
#endif

#ifndef DROP_VIEW_H
#include "DragMessageView.h"
#endif

#ifndef _BETTER_SCROLL_VIEW_H_
#include "BetterScrollView.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
***************************************************************/
DragMessageWindow :: DragMessageWindow
	(
	void
	)
:	BWindow (BRect (100.0f, 50.0f, 200.0f, 200.0f), "DragMessage Viewer", B_TITLED_WINDOW, B_NOT_ZOOMABLE)
{
	// menu bar
	BMenuBar * m_pMenuBar = new BMenuBar (BRect (0, 0, 0, 0), "Clue Menu Bar");
	//add a dummy item to help calculate height, will remove later below
	BMenu * pMenu (new BMenu (STR_MNU_FILE));
	pMenu->AddItem (new BMenuItem (STR_MNU_FILE_CLOSE, new BMessage (B_QUIT_REQUESTED), CMD_FILE_CLOSE));
	m_pMenuBar->AddItem (pMenu);

	// add child after menus are added so its initially calculated app_server bounds take added menus into account
	AddChild (m_pMenuBar);
	
	float menuHeight = m_pMenuBar->Bounds().Height();

	BRect rc (Bounds ());
	BetterScrollView *	m_BSV;
	rc.top = menuHeight + 31.0f;
	rc.bottom = 200.0f;
	rgb_color BotBackground;
	ColumnListView * m_ColumnListView = new ColumnListView (rc, BotBackground, &m_BSV, "ClueItemsList", B_FOLLOW_ALL,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_SINGLE_SELECTION_LIST, true, true, true, B_FANCY_BORDER);
	BFont font;
	m_ColumnListView->GetFont (&font);
	m_ColumnListView->AddColumn (new CLVColumn ("Entry", font.StringWidth ("entry")));
	m_ColumnListView->AddColumn (new CLVColumn ("Type", font.StringWidth ("type")));
	m_ColumnListView->AddColumn (new CLVColumn ("Count", font.StringWidth ("count")));
	m_ColumnListView->AddColumn (new CLVColumn ("Size", font.StringWidth ("Size")));
	m_ColumnListView->AddColumn (new CLVColumn ("Data", font.StringWidth ("Data")));

	rc.top = menuHeight + 1.0f;
	rc.bottom = rc.top + 30.0f;
	DragMessageView * dropView (new DragMessageView (rc, "myView", m_ColumnListView));
	
	// add view to window
	AddChild (dropView);
	AddChild (m_BSV);

	Register ();
}


/***************************************************************
***************************************************************/
DragMessageWindow :: ~DragMessageWindow
	(
	void
	)
{
	UnRegister ();
}


/***************************************************************
***************************************************************/
bool
DragMessageWindow :: QuitRequested
	(
	void
	)
{
	return (true);
}


/***************************************************************
***************************************************************/
void
DragMessageWindow :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
		case 'bltm':
			PRINT (("switch to this window.\n"));
			Activate ();
			break;
		default:
			BWindow::MessageReceived (message);
			break;
	}
}


/***************************************************************
***************************************************************/
void
DragMessageWindow :: Register
	(
	void
	)
{
	BMessenger messenger (be_app);
	BMessage message (MSG_WINDOW_REGISTRY_ADD);
	message.AddBool ("DragMessageViewer", true);
	message.AddString ("title", Title ());
	message.AddPointer ("window", this);
	messenger.SendMessage (&message, this);
}


/***************************************************************
***************************************************************/
void
DragMessageWindow :: UnRegister
	(
	void
	)
{
	BMessenger messenger (be_app);
	BMessage message (MSG_WINDOW_REGISTRY_SUB);
	message.AddPointer ("window", this);
	messenger.SendMessage (&message);
}

