//CLVListItem source file


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
//#define DEBUG 1

#define ADD_IN_FRONT_OF_LIST 1

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _PATH_H
#include <Path.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _CLUEITEM_H_
#include "ClueItem.h"
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif

#ifndef _FINGERPRINTCLV_H_
#include "FingerprintCLV.h"
#endif

#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


extern BBitmap* g_DefaultBMP;
extern BBitmap* e_ClueBitmaps[];
extern BBitmap* g_OtherBmps[];

const int32	TeamItem::ARCHIVE_FORMAT = 1;


/******************************************************************************************************
CTeamItem constructor
*******************************************************************************************************/
TeamItem :: TeamItem
(
	team_id TeamID
	,	BView* view
	,	FingerprintCLV* pCLV
)
	:	CLVListItem()
	,	m_QueueLength(5000)
	,	m_TeamID(TeamID)
	,	m_TabVisible(false)
	,	m_tab(NULL)
	,	m_view(view)
	,	m_bitmap(NULL)
	,	m_CLV(pCLV)
	,	m_RefCount(1)
	,	m_IsRunning(false)
{
	memset(m_CategoryMask, 0xffffffff, sizeof(uint32) * 10);
	m_title[0] = '\0';

	app_info		appInfo;
	status_t		retval(B_ERROR);

	retval = be_roster->GetRunningAppInfo(TeamID, &appInfo);
	if (B_OK == retval) {
		BFile file;
		retval = file.SetTo(&appInfo.ref, B_READ_WRITE);
		if (B_OK == retval) {
			BAppFileInfo appFileInfo;
			retval = appFileInfo.SetTo(&file);
			if (B_OK == retval) {
				BEntry entry;
				retval = entry.SetTo(&(appInfo.ref));
				if (B_OK == retval) {
					entry.GetName(m_title);
					m_bitmap = new BBitmap(BRect(0, 0, 15, 15), B_CMAP8);
					retval = appFileInfo.GetIcon(m_bitmap, B_MINI_ICON);
					if (B_OK != retval) {
						delete m_bitmap;
						m_bitmap = NULL;
					}
				}
			}
		}
	}

	if (!m_bitmap) {
		//use the default one
		m_bitmap = new BBitmap(g_DefaultBMP);
	}
}


/******************************************************************************************************
TeamItem constructor
*******************************************************************************************************/
TeamItem :: TeamItem
(
	BMessage* archive
	,	BView* view
	,	FingerprintCLV* pCLV
	,	int32 arcfmt
)
	:	CLVListItem()
	,	m_QueueLength(5000)
	,	m_TeamID(0)
	,	m_TabVisible(false)
	,	m_tab(NULL)
	,	m_view(view)
	,	m_bitmap(NULL)
	,	m_CLV(pCLV)
	,	m_RefCount(1)
	,	m_IsRunning(false)
{
	memset(m_CategoryMask, 0xffffffff, sizeof(uint32) * 10);
	PRINT(("CTeamItem :: CTeamItem\n"));
	m_title[0] = '\0';
	char* strptr(NULL);
	archive->FindString("m_title", (const char**) &strptr);
	strcpy(m_title, strptr);

	int32 itemarcfmt(0);

	archive->FindInt32("ARCHIVE_FORMAT", (int32*) &itemarcfmt);    //this is the internal format of the Clue ITEMS!
	archive->FindInt32("C_GENERAL", (int32*) &m_CategoryMask[CC_GENERAL]);
	archive->FindInt32("C_APPLICATION", (int32*) &m_CategoryMask[CC_APPLICATION]);
	archive->FindInt32("C_INTERFACE", (int32*) &m_CategoryMask[CC_INTERFACE]);
	archive->FindInt32("C_MEDIA", (int32*) &m_CategoryMask[CC_MEDIA]);
	archive->FindInt32("C_STORAGE", (int32*) &m_CategoryMask[CC_STORAGE]);
	archive->FindInt32("C_SUPPORT", (int32*) &m_CategoryMask[CC_SUPPORT]);
	archive->FindInt32("C_NETWORK", (int32*) &m_CategoryMask[CC_NETWORK]);
	archive->FindInt32("C_MOUSE", (int32*) &m_CategoryMask[CC_MOUSE]);
	archive->FindInt32("C_KEYBOARD", (int32*) &m_CategoryMask[CC_KEYBOARD]);
	archive->FindInt32("C_PRINTING", (int32*) &m_CategoryMask[CC_PRINTING]);
	archive->FindInt32("m_QueueLength", (int32*) &m_QueueLength);
	archive->FindInt32("m_TeamID", &m_TeamID);
	archive->FindBool("m_TabVisible", &m_TabVisible);

	BMessage msgIcon('MICN');
	if (B_OK == archive->FindMessage("B_MINI_ICON", &msgIcon)) {
		BArchivable* obj(instantiate_object(&msgIcon));
		m_bitmap = dynamic_cast<BBitmap*>(obj);
	}

	if (NULL == m_bitmap)
		m_bitmap = new BBitmap(g_DefaultBMP);

	int32 i(0);
	BMessage cluearchive;
	ClueItem* ci(NULL);

	while (B_OK == archive->FindMessage("Clue Items", i++, &cluearchive)) {
		ci = new ClueItem(&cluearchive, itemarcfmt);
		AddClue(ci);
		//m_ItemList.AddItem (ci);
	}

	BStringView* pSV((BStringView*) m_CLV->Parent()->FindView("ListCountView"));
	if (pSV) {
		BString s;
		s << m_CLV->CountItems() << " items";
		pSV->SetText(s.String());
	}

	PRINT((" done CTeamItem constructor\n"));
}


/******************************************************************************************************
CLVItem destructor
*******************************************************************************************************/
TeamItem :: TeamItem
(
	const TeamItem& TI
	,	bool minimal
)
	:	CLVListItem()
	,	m_QueueLength(TI.m_QueueLength)
	,	m_TeamID(TI.m_TeamID)
	,	m_TabVisible(TI.m_TabVisible)
	,	m_tab(NULL)
	,	m_view(NULL)
	,	m_bitmap(NULL)
	,	m_CLV(NULL)
	,	m_RefCount(1)
	,	m_IsRunning(false)
{
	memcpy(m_CategoryMask, TI.m_CategoryMask, sizeof(uint32) * 10);

	//we don't handle the createall possibility right now
	if (minimal) {
	}
}


/******************************************************************************************************
CLVItem destructor
*******************************************************************************************************/
TeamItem :: ~TeamItem
(
	void
)
{
	if (!m_TabVisible) { //BViews aren't Attached to a window, so we must destroy items manually!
		delete m_view;
		m_view = NULL;
	}

	if (m_bitmap) {
		delete m_bitmap;
		m_bitmap = NULL;
	}

	int32 countitems(m_ItemList.CountItems());
	ClueItem* ci(NULL);
	PRINT(("\nTeamItem has %i ClueItems in it.\n", countitems));
	while (countitems--) {
		ci = reinterpret_cast<ClueItem*>(m_ItemList.RemoveItem(static_cast<int32>(0)));
		if (ci) {
			PRINT(("  release ClueItem\n"));
			delete ci;
			//ci->Release ();
			//delete ci;
		} else
			PRINT(("  ClueItem was invalid!\n"));
	}
}


/******************************************************************************************************
*******************************************************************************************************/
status_t
TeamItem :: Archive
(
	BMessage* archive
	,	bool deep
)
const
{
	PRINT(("CTeamItem :: Archive\n"));
	PRINT(("  AddString %s\n", m_title));
	PRINT((" AddString (m_title) = '%s'.\n", m_title));
	archive->AddString("m_title", m_title);
	char tmpstr[B_FILE_NAME_LENGTH];
	archive->FindString("m_title", (const char**) & (tmpstr[0]));
	PRINT((" tmpstr = '%s'.\n", tmpstr));
	archive->AddInt32("ARCHIVE_FORMAT", ClueItem::ARCHIVE_FORMAT);   //this is the internal format of the Clue ITEMS!
	archive->AddInt32("C_GENERAL", m_CategoryMask[CC_GENERAL]);
	archive->AddInt32("C_APPLICATION", m_CategoryMask[CC_APPLICATION]);
	archive->AddInt32("C_INTERFACE", m_CategoryMask[CC_INTERFACE]);
	archive->AddInt32("C_MEDIA", m_CategoryMask[CC_MEDIA]);
	archive->AddInt32("C_STORAGE", m_CategoryMask[CC_STORAGE]);
	archive->AddInt32("C_SUPPORT", m_CategoryMask[CC_SUPPORT]);
	archive->AddInt32("C_NETWORK", m_CategoryMask[CC_NETWORK]);
	archive->AddInt32("C_MOUSE", m_CategoryMask[CC_MOUSE]);
	archive->AddInt32("C_KEYBOARD", m_CategoryMask[CC_KEYBOARD]);
	archive->AddInt32("C_PRINTING", m_CategoryMask[CC_PRINTING]);
	archive->AddInt32("m_QueueLength", m_QueueLength);
	archive->AddInt32("m_TeamID", m_TeamID);
	archive->AddBool("m_TabVisible", m_TabVisible);
	BMessage msgIcon('MICN');
	m_bitmap->Archive(&msgIcon);
	archive->AddMessage("B_MINI_ICON", &msgIcon);

	ClueItem* ci(NULL);
	int32 index(m_ItemList.CountItems() - 1);   //0);
	PRINT(("  listcount = %i\n", index));

	while (index >= 0) {
		ci = (ClueItem*) m_ItemList.ItemAt(index--);
		BMessage cluearchive;
		PRINT((" ci->Archive\n"));
		ci->Archive(&cluearchive);
		archive->AddMessage("Clue Items", &cluearchive);
	}

	PRINT(("  return B_OK\n"));
	return B_OK;
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: DrawItemColumn
(
	BView* owner
	,	BRect item_column_rect
	,	int32 column_index
	,	bool complete
)
{
	rgb_color color;
	rgb_color textcolor;
	bool selected(IsSelected());
	if (selected) {
		textcolor = CLR_LIST_SELECTED_TEXT;
		color = CLR_LIST_SELECTED_BACKGROUND;
//		color = CLR_LIST_SELECTED_GREY;
	} else {
		textcolor = CLR_LIST_TEXT;
		color = CLR_LIST_BACKGROUND;
//		color = CLR_WHITE;
	}
	owner->SetLowColor(color);
	owner->SetDrawingMode(B_OP_COPY);
	if (selected || complete) {
		owner->SetHighColor(color);
		owner->FillRect(item_column_rect);
	}
	BRegion Region;
	Region.Include(item_column_rect);
	owner->ConstrainClippingRegion(&Region);
	owner->SetHighColor(textcolor);

	char tmpstr[30];
	float w(0.0f);
	float y(0.0f);

	//possible columns 0 - 4
	switch (column_index) {
		case 0: //Visible
			if (m_TabVisible) {
				BPoint pt(item_column_rect.left + 4.0f, (item_column_rect.bottom - item_column_rect.top) / 2.0f - 3.0f + item_column_rect.top);
				owner->SetDrawingMode(B_OP_OVER);
				owner->DrawBitmap(g_OtherBmps[1], pt);
				owner->SetDrawingMode(B_OP_COPY);
			}
			break;
		case 1: //small icon
			if (m_bitmap) {
				item_column_rect.left += 4.0;
				item_column_rect.right = item_column_rect.left + 15.0;
				item_column_rect.top += 1.0;
				if (Height() > 20.0)
					item_column_rect.top += ceil((Height() - 20.0) / 2.0);
				item_column_rect.bottom = item_column_rect.top + 15.0;
				owner->SetDrawingMode(B_OP_OVER);
				owner->DrawBitmapAsync(m_bitmap, BRect(0.0f, 0.0f, 15.0f, 15.0f), item_column_rect);
				owner->SetDrawingMode(B_OP_COPY);
			}
			break;
		case 2: //Team ID
			sprintf(tmpstr, "%lu", m_TeamID);
			w = owner->StringWidth(tmpstr) + 4.0f;
			y = item_column_rect.top + fTextOffset;
			owner->DrawString(tmpstr, BPoint(item_column_rect.right - w, y));
			if (m_IsRunning) {
				y += 2;
				owner->SetPenSize(2.0f);
				owner->StrokeLine(BPoint(item_column_rect.right - w, y),
								  BPoint(item_column_rect.right - 6, y));
//				BRect rc (pt.x, pt.y, pt.x + 6.0f, pt.y + 6.0f);
//				rc.InsetBy (-1, -1);
				//owner->SetHighColor (0, 255, 0, 255);
				//owner->StrokeRect (rc);
			}
			break;
		case 3: //Caption
			owner->DrawString(m_title, BPoint(item_column_rect.left + 4.0, item_column_rect.top + fTextOffset));
			break;
		case 4: //Queue Length
			sprintf(tmpstr, "%lu", m_QueueLength);
			w = owner->StringWidth(tmpstr) + 4.0f;
			owner->DrawString(tmpstr, BPoint(item_column_rect.right - w, item_column_rect.top + fTextOffset));
			break;
	}
	owner->ConstrainClippingRegion(NULL);
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: Update
(
	BView* owner
	,	const BFont* font
)
{
	BListItem::Update(owner, font);
	if (Height() < 17.0)
		SetHeight(17.0);
	font_height FontAttributes;
	be_plain_font->GetHeight(&FontAttributes);
	float FontHeight = ceil(FontAttributes.ascent) + ceil(FontAttributes.descent);
	fTextOffset = ceil(FontAttributes.ascent) + (Height() - FontHeight) / 2.0;
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: SetFilter
(
	uint32 flags
)
{
}


/******************************************************************************************************
*******************************************************************************************************/
uint32
TeamItem :: Filter
(
	void
)
{
	return (0);
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: Copy
(
	BString& outString
	,	uint32 inMask
)
{
	ClueItem* ci(NULL);
	int32 count(m_ItemList.CountItems());

	outString << "[Team Entry]\nTitle= " << m_title;
	outString << "\nVisible= " << (m_TabVisible ? "True" : "False");
	outString << "\nTeam ID= " << m_TeamID;
	outString << "\nQueue Length= " << m_QueueLength;
	outString << "\n----==== Begin " << count << " Fingerprints ====----\n";

	for (int index(0); index < count;) {
		ci = (ClueItem*) m_ItemList.ItemAt(index);
//		if (m_CategoryMask[ci->m_CAT] & ci->m_EVT)
//		{

		ci->Copy(outString, inMask, ++index);
//		}
//		else
//		{
//			ci->m_InList = false;
//		}
	}
	outString << "----==== End Fingerprints ====----\n";
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: RefreshList
(
	void
)
{
	m_CLV->MakeEmpty();
	ClueItem* ci(NULL);
	int32 count(m_ItemList.CountItems());

	for (int index(0); index < count; ++index) {
		ci = (ClueItem*) m_ItemList.ItemAt(index);
		if (m_CategoryMask[ci->m_CAT] & ci->m_EVT) {
			ci->m_InList = true;
			m_CLV->AddItem(ci);
		} else
			ci->m_InList = false;
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: ClearList
(
	void
)
{
	m_CLV->MakeEmpty();

	int32 countitems(m_ItemList.CountItems());
	ClueItem* ci(NULL);
	while (countitems--) {
		ci = reinterpret_cast<ClueItem*>(m_ItemList.RemoveItem(static_cast<int32>(0)));
		if (ci != NULL) {
			delete ci;
			ci = NULL;
		}
		//ci->Release ();
		//delete ci;  user Release instead, for reference counting!
	}
	BView* pView(m_view->FindView("DetailView"));
	if (pView)
		((BTextView*) pView)->SetText(NULL);
}


/******************************************************************************************************
*******************************************************************************************************/
int32
TeamItem :: AddRef
(
	void
)
{
	atomic_add(&m_RefCount, 1);
	return (m_RefCount);
}


/******************************************************************************************************
*******************************************************************************************************/
int32
TeamItem :: Release
(
	void
)
{
	atomic_add(&m_RefCount, -1);
	PRINT(("  TeamItem RefCount was %i.\n", m_RefCount));

	if (m_RefCount <= 0) {
		delete this;
		PRINT(("delete this TeamItem\n"));
	} else
		PRINT(("RefCount was > 0\n"));
	return (m_RefCount);
}

/******************************************************************************************************
*******************************************************************************************************/
bool
TeamItem :: SetRunning
(
	bool newval
)
{
	PRINT(("TeamItem::SetRunning= %i, oldval=%i\n", newval, m_IsRunning));
	if (m_IsRunning != newval) {
		m_IsRunning = newval;
		PRINT(("  return true\n"));
		return true;
	}

	PRINT(("  return false\n"));
	return false;
}

/******************************************************************************************************
*******************************************************************************************************/
bool
TeamItem :: IsRunning
(
	void
)
{
	return m_IsRunning;
}



/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: AddClue
(
	ClueItem* pClueItem
)
{
#ifdef ADD_IN_FRONT_OF_LIST
	//put items at front of list
	m_ItemList.AddItem(pClueItem, 0);
	if (m_CategoryMask[pClueItem->m_CAT] & pClueItem->m_EVT) {
		pClueItem->m_InList = true;
		m_CLV->AddItem(pClueItem, 0);
	}
#else
	//put items at end of list
	m_ItemList.AddItem(pClueItem);
	if (m_CategoryMask[pClueItem->m_CAT] & pClueItem->m_EVT) {
		pClueItem->m_InList = true;
		m_CLV->AddItem(pClueItem);
	}
#endif
}


/******************************************************************************************************
*******************************************************************************************************/
void
TeamItem :: AdjustQueue
(
	void
)
{
	PRINT(("CTeamItem :: AdjustQueue\n"));
#ifdef ADD_IN_FRONT_OF_LIST
	int32 listcount(m_ItemList.CountItems() - 1);

	if (listcount >= m_QueueLength)
#else
	int32 listcount(m_ItemList.CountItems());

	if (listcount > m_QueueLength)
#endif
	{
		//need to trim entries
		//int32 trimcount (listcount - m_QueueLength); //this is the number of ClueItems we must trim from the list
		int32 itemsvisible(0);
		ClueItem* ci(NULL);
		BList deletelist;

#ifdef ADD_IN_FRONT_OF_LIST
		while (listcount >= m_QueueLength) {
			ci = reinterpret_cast<ClueItem*>(m_ItemList.RemoveItem(static_cast<int32>(listcount--)));
#else
		listcount -= m_QueueLength;
		while (listcount--) {
			ci = reinterpret_cast<ClueItem*>(m_ItemList.RemoveItem(static_cast<int32>(0)));
#endif
			if (ci->m_InList)
				++itemsvisible;
			deletelist.AddItem(ci);
		}
		PRINT((" itemsvisible = %i\n", itemsvisible));

		if (itemsvisible) {
#ifdef ADD_IN_FRONT_OF_LIST
			listcount = m_CLV->CountItems();
			PRINT((" m_CLV->CountItems = %i\n", listcount));
			int32 start(listcount - itemsvisible);
			PRINT((" start = %i, call RemoveItems (%i, %i)\n", start, start, itemsvisible));
			m_CLV->RemoveItems(start, itemsvisible);
#else
			PRINT((" call RemoveItems (0, %i)\n", itemsvisible));
			m_CLV->RemoveItems(0, itemsvisible);
#endif
			PRINT((" RemoveItems returned\n"));
		}

		listcount = deletelist.CountItems();
		PRINT((" deletelist.CountItems = %i.\n", listcount));
		while (listcount--) {
			ci = reinterpret_cast<ClueItem*>(deletelist.RemoveItem((int32) 0));
			delete ci;
		}

		PRINT((" deletelist count = %i\n", deletelist.CountItems()));
		PRINT((" finished\n"));
	}
}
