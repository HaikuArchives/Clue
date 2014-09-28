/*
	
	DropView.cpp
	
*/
/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.
*/

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#include <Message.h>
#include <Entry.h>

#ifndef CLUE_BUILD_H
#include "ClueBuild.h"
#endif

#ifndef DROP_VIEW_H
#include "DragMessageView.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef DRAGMESSAGEITEM_H_
#include "DragMessageItem.h"
#endif


/***************************************************************
***************************************************************/
DragMessageView :: DragMessageView
	(
	BRect rect
,	const char * name
,	ColumnListView * CLV
	)
:	BStringView (rect, name, "Drag over me!", B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW)
,	m_ColumnListView (CLV)
,	m_message (NULL)
{
	//Set up the font for the text
	SetFont (be_bold_font);
	SetFontSize (24);
}


DragMessageView :: ~DragMessageView
	(
	void
	)
{
	int32			index (m_ColumnListView->CountItems ());
	DragMessageItem *		dmi (NULL);

	while (index--)
	{
		dmi = (DragMessageItem *) m_ColumnListView->RemoveItem (index);
		if (dmi)
		{
			delete dmi;
		}
	}

	if (m_message)
	{
		delete m_message;
		m_message = NULL;
	}
}

/***************************************************************
***************************************************************/
void
DragMessageView :: MessageReceived
	(
	BMessage * message
	)
{
   	entry_ref ref;
 	switch ( message->what ){
   		case B_SIMPLE_DATA:
   			// Look for a ref in the message
   			if( message->FindRef("refs", &ref) == B_OK ){
				// Call SetText() to change the string in the view
   				SetText( ref.name );
   			}else{
   				// Call inherited if we didn't handle the message
   				BStringView::MessageReceived(message);
   			}
   			break;
   		default:
   			// Call inherited if we didn't handle the message
   			BStringView::MessageReceived(message);
   			break;
	}
}


/***************************************************************
***************************************************************/
void
DragMessageView :: MouseMoved
	(
	BPoint point
,	uint32 transit
,	const BMessage * message
	)
{
	if (B_ENTERED_VIEW == transit)
	{
		if (message)
		{
			SetText ("Found message.");
			ProcessMessage (message);
		}
		else
		{
			SetText ("No message found.");
		}
	}
	else if (B_EXITED_VIEW == transit)
	{
		SetText ("Drag over me!");
	}
}


/***************************************************************
***************************************************************/
void
DragMessageView :: ProcessMessage
	(
	const BMessage * message
	)
{
	int32				index (m_ColumnListView->CountItems ());
	DragMessageItem *	dmi (NULL);

	while (index--)
	{
		dmi = (DragMessageItem *) m_ColumnListView->RemoveItem (index);
		if (dmi)
		{
			delete dmi;
		}
	}

	if (m_message)
	{
		delete m_message;
	}

	m_message = new BMessage (*message);

//	index = m_message->CountNames (B_ANY_TYPE);
//	while (index--)
//	{
//		dmi = new DragMessageItem (m_message, index);
//		m_ColumnListView->AddItem (dmi);
//	}
#ifdef CLUE_ON_ZETA_HACK
	char const * name (NULL);
#else
	char * name (NULL);
#endif
	uint32 type (0);
	int32 count (0);
	
	for (int32 i (0); B_OK == m_message->GetInfo (B_ANY_TYPE, i, &name, &type, &count); i++)
	{
		dmi = new DragMessageItem (m_message, name, type, count);
		m_ColumnListView->AddItem (dmi);
	}
}

