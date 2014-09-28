/*	
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
//#define DEBUG 1

#ifndef _MIME_H
#include <Mime.h>
#endif

#ifndef _BEEP_H
#include <Beep.h>
#endif

#ifndef _CLIPBOARD_H
#include <Clipboard.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif

#ifndef _TEAMCLV_H_
#include "TeamCLV.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif


/***************************************************************
**** ColumnListView CLASS IMPLEMENTATION
***************************************************************/
TeamCLV :: TeamCLV
	(
	BRect Frame
,	rgb_color CornerColor
,	BetterScrollView ** ContainerView
,	const char * Name
,	uint32 ResizingMode
,	uint32 flags
,	list_view_type Type
,	bool hierarchical
,	bool horizontal
,	bool vertical
,	border_style border
,	const BFont * LabelFont
	)
:	ColumnListView (Frame, CornerColor, ContainerView, Name, ResizingMode, flags, Type, hierarchical, horizontal, vertical, border, LabelFont)
,	m_popupmenu (NULL)
{
}


/***************************************************************
***************************************************************/
TeamCLV :: ~TeamCLV
	(
	void
	)
{
	if (m_popupmenu)
	{
		delete m_popupmenu;
		m_popupmenu = NULL;
	}
}


/***************************************************************
***************************************************************/
void
TeamCLV :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
		case B_COPY:
			CopyToClipboard ();
			break;
		default:
			ColumnListView::MessageReceived (message);
			break;
	}
}


/***************************************************************
***************************************************************/
void
TeamCLV :: MouseDown
	(
	BPoint point
	)
{
	int32 buttons (0);
	
	Window()->CurrentMessage()->FindInt32 ("buttons", &buttons);
	if (B_SECONDARY_MOUSE_BUTTON & buttons)
	{
		MakeFocus (true);

		int32 index (IndexOf (point));
		if (index >= 0)
		{
			Select (index);
			DoContextMenu (index, point, false);
		}
	}
	else
	{
		ColumnListView::MouseDown (point);
	}
}


/***************************************************************
***************************************************************/
void
TeamCLV :: KeyDown
	(
	const char * bytes
,	int32 numBytes
	)
{
	int32 mods (modifiers ());
	switch (bytes[0])
	{
		case B_ESCAPE:
			if (B_MENU_KEY & mods)
			{
				int32 index (CurrentSelection ());
				if (index >= 0)
				{
					DoContextMenu (index, BPoint (Bounds().right, ItemFrame(index).top), true);
				}
				else
				{
					beep ();
				}
			}
			else
			{
				ColumnListView::KeyDown (bytes, numBytes);
			}
			break;
		case B_DELETE:
			{
				if (0 <= CurrentSelection ())
				{
					BView * targetview (Window()->FindView ("BackView"));
					//msg = new BMessage (MSG_TEAM_DELETE);
					//msg->AddInt32 ("TeamID", pTI->m_TeamID);
					if (targetview)
					{
						BInvoker invkr (new BMessage (MSG_TEAM_DELETE), (BHandler *) targetview);
						invkr.Invoke ();
					}
				}
			}
			break;
		default:
			ColumnListView::KeyDown (bytes, numBytes);
			break;
	}
}


/***************************************************************
***************************************************************/
void
TeamCLV :: DoContextMenu
	(
	int32 index
,	BPoint point
,	bool openAnyway
	)
{
	TeamItem * pTI ((TeamItem *) ItemAt (index));
	BView * targetview (Window()->FindView ("BackView"));
	if (m_popupmenu)
	{
		delete m_popupmenu;
		m_popupmenu = NULL;
	}
	m_popupmenu = (BPopUpMenu *) new BPopUpMenu ("TeamSelect");

	BWindow * pWnd (Window ());
	BMessage * msg (new BMessage (MSG_CLEAR_CLUE_LIST));
	msg->AddInt32 ("TeamID", pTI->m_TeamID);
	ActiveMenuItem * pAMI (new ActiveMenuItem (pWnd, STR_POPUP_MENU_TEAM_CLEAR_CLUES, STR_STATUS_TEAMLIST_CLEAR_LIST, msg));
	pAMI->SetTarget (targetview);
	m_popupmenu->AddItem (pAMI);

	msg = new BMessage (MSG_TEAM_PROPERTIES);
	msg->AddInt32 ("TeamID", pTI->m_TeamID);
	pAMI = new ActiveMenuItem (pWnd, STR_POPUP_MENU_TEAM_EDIT_PROPERTIES, STR_STATUS_TEAMLIST_EDIT_PROPERTIES,  msg);
	pAMI->SetTarget (targetview);
	m_popupmenu->AddItem (pAMI);

	msg = new BMessage ('acti');
	msg->AddInt32 ("TeamID", pTI->m_TeamID);
	pAMI = new ActiveMenuItem (pWnd, STR_POPUP_MENU_TEAM_ACTIVATE, STR_STATUS_TEAMLIST_ACTIVATE,  msg);
	if (pTI->IsRunning ())
	{
		pAMI->SetTarget (targetview);
	}
	else
	{
		pAMI->SetEnabled (false);
	}
	m_popupmenu->AddItem (pAMI);

	m_popupmenu->AddSeparatorItem ();

	msg = new BMessage (MSG_TEAM_DELETE);
	msg->AddInt32 ("TeamID", pTI->m_TeamID);
	pAMI = new ActiveMenuItem (pWnd, STR_POPUP_MENU_TEAM_DELETE, STR_STATUS_TEAMLIST_DELETE, msg);
	pAMI->SetTarget (targetview);
	m_popupmenu->AddItem (pAMI);

	ConvertToScreen (&point);
	m_popupmenu->Go (point, true, openAnyway, true);
}


/***************************************************************
***************************************************************/
void
TeamCLV :: CopyToClipboard
	(
	void
	)
{
	int32 index (CurrentSelection ());
	if (index >= 0)
	{
		TeamItem * pTI ((TeamItem *) ItemAt (index));
		BString data;
		pTI->Copy (data, 0xFFFFFFFF);
		be_clipboard->Lock ();
		BMessage * pClipMsg (be_clipboard->Data ());
		if (pClipMsg)
		{
			pClipMsg->MakeEmpty ();
			pClipMsg->AddData ("text/plain", B_MIME_DATA, data.String (), data.Length ());
			//pClipMsg->AddData ("text/plain", B_MIME_TYPE, data.String (), data.Length ());
			//	add the actions
			pClipMsg->AddInt32("be:actions", B_COPY_TARGET);
			pClipMsg->AddString("be:clip_name", "Clue Team Entry");
			be_clipboard->Commit ();
		}
		be_clipboard->Unlock ();
	}
	else
	{
		beep ();
	}
}


/***************************************************************
***************************************************************/
bool
TeamCLV :: InitiateDrag
	(
	BPoint point
,	int32 index
,	bool wasSelected
	)
{
	if (wasSelected)
	{
/*
		BMessage dragmsg (B_SIMPLE_DATA);
		//	add the types
		dragmsg.AddString("be:types", "text/plain");
		//	add the actions
		dragmsg.AddInt32("be:actions", B_COPY_TARGET);
		dragmsg.AddString("be:clip_name", "Clue Team Entry");
		DragMessage (&dragmsg, BRect (point.x,point.y,point.x+60,point.y+60), this);
*/
		TeamItem * pTI ((TeamItem *) ItemAt (index));
		BString data;
		pTI->Copy (data, 0xFFFFFFFF);
		BMessage dragmsg (B_MIME_DATA);
		//	add the types
//		dragmsg.AddString("be:types", "text/plain");
//		dragmsg.AddData ("text/plain", B_MIME_DATA, "sample", 6);
		dragmsg.AddData ("text/plain", B_MIME_DATA, data.String (), data.Length ());
		//	add the actions
		dragmsg.AddInt32("be:actions", B_COPY_TARGET);
		dragmsg.AddString("be:clip_name", "Clue Team Entry");
		BRect dragrect (ItemFrame (index));
		DragMessage (&dragmsg, dragrect, this);

		return true;
	}
	else
	{
		return false;
	}
}

