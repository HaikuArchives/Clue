//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef _BEEP_H
#include <Beep.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _CLIPBOARD_H
#include <Clipboard.h>
#endif

#ifndef _BE_LIST_H
#include <List.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _CLUEITEM_H_
#include "ClueItem.h"
#endif

#ifndef _FINGERPRINTCLV_H_
#include "FingerprintCLV.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
**** ColumnListView CLASS IMPLEMENTATION
***************************************************************/
FingerprintCLV :: FingerprintCLV
	(
	BRect Frame
,	BTextView * pTextView
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
,	m_txtDetails (pTextView)
{
}


FingerprintCLV :: ~FingerprintCLV
	(
	void
	)
{
}


/***************************************************************
***************************************************************/
void
FingerprintCLV :: MessageReceived
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
FingerprintCLV :: CopyToClipboard
	(
	void
	)
{
	int32 i (CurrentSelection ());
	if (i >= 0)
	{
		ClueItem * pCI (NULL);
		BString data;

		int32 selected (0);
		i = 0;
		while ( (selected = CurrentSelection (i++)) >= 0)
		{
			pCI = (ClueItem *) ItemAt (selected);
			pCI->Copy (data, 0xFFFFFFFF, i);
		}

		be_clipboard->Lock ();
		BMessage * pClipMsg (be_clipboard->Data ());
		if (pClipMsg)
		{
			pClipMsg->MakeEmpty ();
			pClipMsg->AddData ("text/plain", B_MIME_DATA, data.String (), data.Length ());
			//pClipMsg->AddData ("text/plain", B_MIME_TYPE, data.String (), data.Length ());
			//	add the actions
			pClipMsg->AddInt32("be:actions", B_COPY_TARGET);
			pClipMsg->AddString("be:clip_name", "Clue Fingerprint");
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
FingerprintCLV :: InitiateDrag
	(
	BPoint point
,	int32 index
,	bool wasSelected
	)
{
	if (!wasSelected)
	{
		return false;
	}

	ClueItem * pCI ((ClueItem *) ItemAt (index));
	BString data;

	int32 selected (0);
	int32 i (0);
	while ( (selected = CurrentSelection (i++)) >= 0 )
	{
		pCI = (ClueItem *) ItemAt (selected);
		pCI->Copy (data, 0xFFFFFFFF, i);
	}

	BMessage dragmsg (B_MIME_DATA);
	//	add the types
	dragmsg.AddData ("text/plain", B_MIME_DATA, data.String (), data.Length ());
	//	add the actions
	dragmsg.AddInt32("be:actions", B_COPY_TARGET);
	dragmsg.AddString("be:clip_name", "Clue Fingerprint");
	BRect dragrect ((i > 2 ? Bounds () : ItemFrame (index)));
	DragMessage (&dragmsg, dragrect, this);

	return true;
}


class IntContainer
{
	public:
		IntContainer (int32 v) {m_int = v;}
		int32	Value(void) {return m_int;}
	private:
		int32	m_int;
};

/***************************************************************
***************************************************************/
void
FingerprintCLV :: KeyDown
	(
	const char * bytes
,	int32 numBytes
	)
{
//	int32 mods (modifiers ());
	switch (bytes[0])
	{
		case B_DELETE:
			m_txtDetails->SetText (NULL);
			{
			int32 selected (0);
			int32 i (0);
			BList listitems;
			int32 NextSelectedItem (CurrentSelection ());

			IntContainer * IC (NULL);
			while ( (selected = CurrentSelection (i++)) >= 0)
			{
				listitems.AddItem (new IntContainer (selected));
				//pCI = (ClueItem *) pCLV->ItemAt (selected);
				//listitems.AddItem (ItemAt (selected));
			}

			ClueItem * pCI (NULL);
			int32 cnt (listitems.CountItems ());
			if (cnt)
			{
				while (cnt > 0)
				{
					IC = reinterpret_cast<IntContainer *> (listitems.RemoveItem (--cnt));
					pCI = reinterpret_cast<ClueItem *> (RemoveItem (IC->Value ()));
					pCI->m_InList = false;
					//DO NOT DELETE THE ITEM AS IT'S BEING KEPT IN ANOTHER BLIST THE TEAMITEM OWNS!!!!
					delete IC;
				}


				BScrollView * pScrollView ((BScrollView *) Parent ());
				if (pScrollView)
				{
					BStringView * pBSV ((BStringView *) pScrollView->FindView ("ListCountView"));
					if (pBSV)
					{
						BString s;
						s << CountItems () << STR_ITEMS;
						pBSV->SetText (s.String ());
					}
					
				}
				if (NextSelectedItem < CountItems ())
				{
					Select (NextSelectedItem);
				}
			}
			}
			break;
/*
		case B_ESCAPE:
			if (B_MENU_KEY & mods)
			{
				DoContextMenu (0, BPoint (0.0f, 0.0f), true);
			}
			else
			{
				ColumnListView::KeyDown (bytes, numBytes);
			}
*/
		default:
			ColumnListView::KeyDown (bytes, numBytes);
			break;
	}
}


