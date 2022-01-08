//CLVListItem source file


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
#define DEBUG 1

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
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

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _TIME_H_
#include <time.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _CLUEITEM_H_
#include "ClueItem.h"
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

extern BBitmap* g_bmpCategories[];
extern BBitmap* g_bmpEvents[];

const int32	ClueItem::ARCHIVE_FORMAT = 1;

/******************************************************************************************************
CLVItem constructor
team_id, char *, BView *, BBitmap *, char *
*******************************************************************************************************/
ClueItem :: ClueItem
(
	const FingerPrint* pFP
	,	const BString* pFileName
	,	const BString* pMethodDefinition
	,	const BString* pDescription
	,	const BString* pDetails
	, 	const intptr_t pInst
)
	:	CLVListItem()
	,	m_CAT(pFP->Category)
	,	m_EVT(pFP->Event)
	,	m_Time(pFP->Time)
	,	m_ThreadID(pFP->ThreadID)
	,	m_TeamID(pFP->TeamID)
	,	m_Line(pFP->Line)
	,	m_Sequence(pFP->Sequence)
	,	m_Inst(pInst)
	,	m_File((char*) B_EMPTY_STRING)
	,	m_Method((char*) B_EMPTY_STRING)
	,	m_Class((char*) B_EMPTY_STRING)
	,	m_Description((char*) B_EMPTY_STRING)
	,	m_Detail((char*) B_EMPTY_STRING)
	,	m_CategoryBmp(g_bmpCategories[pFP->Category])
	,	m_EventBmp(g_bmpEvents[4])
	,	m_InList(false)
//,	m_RefCount (1)
{
	PRINT(("\n\nStart CClueItem processing\n"));
	size_t len(0);
	char* pchar(strrchr(pFileName->String(), '/'));
	PRINT(("  work the Filename\n"));
	if (pchar) {
		PRINT(("  move past last char '++pchar' = %x\n", pchar));
		++pchar; //move past the last '/'
		PRINT(("  get the length of the string\n"));
		len = strlen(pchar) + 1; //apath.Leaf ()) + 1;
		PRINT(("  allocate memory, len=%i\n", len));
		m_File = new char[len];
		PRINT(("  memcpy %x %x, %i\n", m_File, pchar, len));
		memcpy(m_File, pchar, len);
	} else {
		PRINT(("  ERROR: pchar was invalid\n"));
		m_File = new char[7];
		strcpy(m_File, "ERROR!");
	}

	PRINT(("process Method: %s\n", pMethodDefinition->String()));
	int32 breaks(0);
	const char* pIndex[5];
	const char* pBuf(pMethodDefinition->String());
	const char* pStartOfDefinition(pBuf);

	while (*pBuf != '(') {
		switch (*pBuf) {
			case ':':
				PRINT(("   found a break: %s\n", pBuf));
				++breaks;
				pIndex[breaks - 1] = pBuf;
				pBuf += 2; //increment past both ::'s
				break;
			case ' ':
				pStartOfDefinition = ++pBuf; //reset where the real defintion we want, starts
				breaks = 0;
				PRINT(("   found a blank, reset start to: %s; also reset breaks to %i\n", pBuf, breaks));
				break;
			default:
				PRINT(("   nothing interesting, move on\n"));
				++pBuf;
				break;
		}
	}

#ifdef DEBUG
	PRINT(("   pBuf (%u)= %s\n", pBuf, pBuf));
	PRINT(("   calc'd definition (%u): %s\n", pStartOfDefinition, pStartOfDefinition));
	PRINT(("   breaks= %u\n", breaks));

	for (int i(0); i < breaks; i++)
		PRINT(("   break at (%u): %s\n", i, pIndex[i]));
#endif

	if (breaks > 0) { //then we have an OOP class::method defintion, handle accordingly
		PRINT(("  OOP class method found\n   Method="));
		if ((CE_BIRTH | CE_DEATH) & m_EVT)
			breaks = 0;
		else
			--breaks;
		len = pIndex[breaks] - pStartOfDefinition;
		m_Class = (char*) new char[++len];
		PRINT(("memcpy: class=%x, source=%x, len=%x\n", m_Method, pIndex[breaks], len));
		memcpy(m_Class, pStartOfDefinition, len);
		m_Class[--len] = '\0'; //terminate the string
		PRINT(("%s, len=%u\n", m_Class, len));

		if (!((CE_BIRTH | CE_DEATH) & m_EVT)) {
			pIndex[breaks] += 2;
			len = pBuf - pIndex[breaks];
			m_Method = (char*) new char[++len];
			PRINT(("memcpy: method=%x, source=%x, len=%x\n", m_Method, pIndex[breaks], len));
			memcpy(m_Method, pIndex[breaks], len);
			m_Method[--len] = '\0'; //terminate the string
			PRINT(("%s, len=%u\n   Class= ", m_Method, len));
		}
	} else {
		PRINT(("  non-class method found: "));
		//leave m_Class as is, B_EMPTY_STRING, just fill in the non-class function
		len = pBuf - pStartOfDefinition;
		m_Method = (char*) new char[++len];
		PRINT(("memcpy: dest=%x, source=%x, len=%x\n", m_Method, pStartOfDefinition, len));
		memcpy(m_Method, pStartOfDefinition, len);
		m_Method[--len] = '\0'; //terminate the string
		PRINT(("%s, %i\n", m_Method, len));
	}

	//Copy the Description
	len = pDescription->Length() + 1;
	m_Description = new char[len];
	memcpy(m_Description, pDescription->String(), len);

	//copy the details
	len = pDetails->Length() + 1;
	m_Detail = new char[len];
	PRINT(("memcpy: detail=%x, source=%x, len=%x\n", m_Method, pDetails->String(), len));
	memcpy(m_Detail, pDetails->String(), len);

	//put in order of most frequent to less frequent for performance's sake
	switch (m_EVT) {
		case CE_OK:
			m_EventBmp = g_bmpEvents[4];
			break;
		case CE_INFO:
			m_EventBmp = g_bmpEvents[5];
			break;
		case CE_ENTER:
			m_EventBmp = g_bmpEvents[2];
			break;
		case CE_EXIT:
			m_EventBmp = g_bmpEvents[3];
			break;
		case CE_OBJECT:
			m_EventBmp = g_bmpEvents[11];
			break;
		case CE_WARNING:
			m_EventBmp = g_bmpEvents[6];
			break;
		case CE_ERROR:
			m_EventBmp = g_bmpEvents[7];
			break;
		case CE_BIRTH:
			m_EventBmp = g_bmpEvents[0];
			break;
		case CE_DEATH:
			m_EventBmp = g_bmpEvents[1];
			break;
		case CE_SUCCEEDED:
			m_EventBmp = g_bmpEvents[8];
			break;
		case CE_FAILED:
			m_EventBmp = g_bmpEvents[9];
			break;
		case CE_TIMER:
			m_EventBmp = g_bmpEvents[10];
			break;
		default:
			DEBUGGER("ClueItem::ClueItem, in default for icon selection");
			break;
	}
	//AddRef (); //already incremented the counter in constructor list
}


/******************************************************************************************************
*******************************************************************************************************/
ClueItem :: ClueItem
(
	BMessage* archive
	,	int32 ArchiveFormat
)
	:	CLVListItem()
	,	m_CAT(CC_GENERAL)
	,	m_EVT(CE_OK)
	,	m_Time(0)
	,	m_ThreadID(0)
	,	m_TeamID(0)
	,	m_Line(0)
	,	m_Sequence(0)
	,	m_Inst(0)
	,	m_File((char*) B_EMPTY_STRING)
	,	m_Method((char*) B_EMPTY_STRING)
	,	m_Class((char*) B_EMPTY_STRING)
	,	m_Description((char*) B_EMPTY_STRING)
	,	m_Detail((char*) B_EMPTY_STRING)
	,	m_CategoryBmp(g_bmpCategories[CC_GENERAL])
	,	m_EventBmp(g_bmpEvents[4])
	,	m_InList(false)
{
	char* strptr(NULL);
	size_t len(0);

	archive->FindInt32("m_CAT", (int32*) &m_CAT);
	archive->FindInt32("m_EVT", (int32*) &m_EVT);
	archive->FindInt32("m_Line", (int32*) &m_Line);
	archive->FindInt32("m_ThreadID", (int32*) &m_ThreadID);
	archive->FindInt32("m_Sequence", (int32*) &m_Sequence);
	archive->FindInt64("m_Time", (int64*) &m_Time);

	void* tmp_inst(NULL);
	archive->FindPointer("m_Inst_AsPointer", &tmp_inst);
	m_Inst = (intptr_t)tmp_inst;

	if (B_OK == archive->FindString("m_Method", (const char**) &strptr)) {
		len = strlen(strptr) + 1;
		m_Method = (char*) new char[len];
		strcpy(m_Method, strptr);
	}

	if (B_OK == archive->FindString("m_Class", (const char**) &strptr)) {
		len = strlen(strptr) + 1;
		m_Class = (char*) new char[len];
		strcpy(m_Class, strptr);
	}

	if (B_OK == archive->FindString("m_File", (const char**) &strptr)) {
		len = strlen(strptr) + 1;
		m_File = (char*) new char[len];
		strcpy(m_File, strptr);
	}
	if (B_OK == archive->FindString("m_Detail", (const char**) &strptr)) {
		len = strlen(strptr) + 1;
		m_Detail = (char*) new char[len];
		strcpy(m_Detail, strptr);
	}

	if (B_OK == archive->FindString("m_Description", (const char**) &strptr)) {
		len = strlen(strptr) + 1;
		m_Description = (char*) new char[len];
		strcpy(m_Description, strptr);
	}

	m_CategoryBmp = g_bmpCategories[m_CAT];

	switch (m_EVT) {
		case CE_OK:
			m_EventBmp = g_bmpEvents[4];
			break;
		case CE_INFO:
			m_EventBmp = g_bmpEvents[5];
			break;
		case CE_ENTER:
			m_EventBmp = g_bmpEvents[2];
			break;
		case CE_EXIT:
			m_EventBmp = g_bmpEvents[3];
			break;
		case CE_WARNING:
			m_EventBmp = g_bmpEvents[6];
			break;
		case CE_ERROR:
			m_EventBmp = g_bmpEvents[7];
			break;
		case CE_BIRTH:
			m_EventBmp = g_bmpEvents[0];
			break;
		case CE_DEATH:
			m_EventBmp = g_bmpEvents[1];
			break;
		case CE_SUCCEEDED:
			m_EventBmp = g_bmpEvents[8];
			break;
		case CE_FAILED:
			m_EventBmp = g_bmpEvents[9];
			break;
		case CE_TIMER:
			m_EventBmp = g_bmpEvents[10];
			break;
		case CE_OBJECT:
			m_EventBmp = g_bmpEvents[11];
			break;
		default:
			DEBUGGER("ClueItem::ClueItem, in default for icon selection");
//			m_EventBmp = e_ClueBitmaps[7];
			break;
	}
}


/******************************************************************************************************
CLVItem destructor
*******************************************************************************************************/
ClueItem :: ~ClueItem
(
	void
)
{
	if (B_EMPTY_STRING != m_File) {
		delete [] m_File;
		m_File = NULL;
	}
	if (B_EMPTY_STRING != m_Method) {
		delete [] m_Method;
		m_Method = NULL;
	}
	if (B_EMPTY_STRING != m_Class) {
		delete [] m_Class;
		m_Class = NULL;
	}
	if (B_EMPTY_STRING != m_Description) {
		delete [] m_Description;
		m_Description = NULL;
	}
	if (B_EMPTY_STRING != m_Detail) {
		delete [] m_Detail;
		m_Detail = NULL;
	}
}


/******************************************************************************************************
Here are the columns and their order:
	Type
	Method
	Class
	File
	Line
	Thread
	Sequence
	Time
	Details
	Visible
*******************************************************************************************************/
void
ClueItem :: DrawItemColumn
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

	//possible columns 0 - 9
	switch (column_index) {
		case 0: //Category
			owner->SetDrawingMode(B_OP_OVER);
			owner->DrawBitmapAsync(m_CategoryBmp, BRect(item_column_rect.left + 4.0, item_column_rect.top + 1.0,
								   item_column_rect.left + 19.0, item_column_rect.top + 16.0));
			owner->SetDrawingMode(B_OP_COPY);
			break;
		case 1: //Event
			owner->SetDrawingMode(B_OP_OVER);
			owner->DrawBitmapAsync(m_EventBmp, BRect(item_column_rect.left + 4.0, item_column_rect.top + 1.0,
								   item_column_rect.left + 19.0, item_column_rect.top + 16.0));
			owner->SetDrawingMode(B_OP_COPY);
			break;
		case 2: //Method
			owner->DrawString(m_Method, BPoint(item_column_rect.left + 4.0, item_column_rect.top + fTextOffset));
			break;
		case 3: //Class
			owner->DrawString(m_Class, BPoint(item_column_rect.left + 4.0, item_column_rect.top + fTextOffset));
			break;
		case 4: //File
			owner->DrawString(m_File, BPoint(item_column_rect.left + 4.0, item_column_rect.top + fTextOffset));
			break;
		case 5: //Line
			sprintf(tmpstr, "%lu", m_Line);
			w = owner->StringWidth(tmpstr) + 4.0f;
			owner->DrawString(tmpstr, BPoint(item_column_rect.right - w, item_column_rect.top + fTextOffset));
			break;
		case 6: //Thread
			sprintf(tmpstr, "%li", m_ThreadID);
			w = owner->StringWidth(tmpstr) + 4.0f;
			owner->DrawString(tmpstr, BPoint(item_column_rect.right - w, item_column_rect.top + fTextOffset));
			break;
		case 7: //Sequence
			sprintf(tmpstr, "%lu", m_Sequence);
			w = owner->StringWidth(tmpstr) + 4.0f;
			owner->DrawString(tmpstr, BPoint(item_column_rect.right - w, item_column_rect.top + fTextOffset));
			break;
		case 8: { //Date
				time_t mytime(m_Time / 1000000);
				struct tm* pTime(localtime(&mytime));
//#ifdef LOCALE_USA
//			strftime (tmpstr, 30, "%b %d, %Y", pTime);
//#endif
//#ifdef LOCALE_GERMAN
//			strftime (tmpstr, 30, "%d/%b/%Y", pTime);
//#endif
//#ifdef LOCALE_RUSSIAN
//			strftime (tmpstr, 30, "%d/%b/%Y", pTime);
//#endif
//#ifdef LOCALE_PORTUGUESE
				strftime(tmpstr, 30, "%d/%m/%Y", pTime);
//#endif
				//delete pTime;
				owner->DrawString(tmpstr, BPoint(item_column_rect.left + 4.0f, item_column_rect.top + fTextOffset));
			}
			break;
		case 9: { //Time
				time_t mytime(m_Time / 1000000);
				struct tm* pTime(localtime(&mytime));
				mytime = m_Time - (mytime * 1000000);
				sprintf(tmpstr, "%02i:%02i:%02i.%06li", pTime->tm_hour, pTime->tm_min, pTime->tm_sec, mytime);
				//delete pTime;
				owner->DrawString(tmpstr, BPoint(item_column_rect.left + 4.0f, item_column_rect.top + fTextOffset));
			}
			break;
		case 10: //Details
			owner->DrawString(m_Description, BPoint(item_column_rect.left + 2.0, item_column_rect.top + fTextOffset));
			break;
	}
	owner->ConstrainClippingRegion(NULL);
}


void
ClueItem :: Update
(
	BView* owner
	,	const BFont* font
)
{
	BListItem::Update(owner, font);
	float h(Height());

	if (h < 17.0) {
		//SetHeight ((m_Expanded ? m_DetailLineCount : 1) * 17.0f);
		SetHeight(17.0f);
	}
//	else
//	{
//		//SetHeight ((m_Expanded ? m_DetailLineCount : 1) * h);
//		SetHeight ((m_Expanded ? m_DetailLineCount : 1) * h);
//	}

	font_height FontAttributes;
	be_plain_font->GetHeight(&FontAttributes);
	//float FontHeight (ceil (FontAttributes.ascent) + ceil (FontAttributes.descent));
	fTextOffset = ceil(FontAttributes.ascent) + ceil(FontAttributes.descent);
//	fTextOffset = ceil (FontAttributes.ascent) + (Height () - FontHeight) / 2.0;
}


/******************************************************************************************************
*******************************************************************************************************/
/*
void
ClueItem :: Switch
	(
	BView * owner
	)
{
	PRINT (("running Switch\n"));

//	if (m_DetailLineCount > 1)
//	{
		PRINT (("modify m_Expanded\n"));
		m_Expanded = !m_Expanded;
		PRINT (("%s\n", ((m_Expanded) ? " expanded" : " collapsed")));
		BFont font;
		owner->GetFont (&font);
//		Update (owner, &font);
//	}
//	else
//	{
		PRINT ((".\n"));
//	}
	PRINT (("ending Switch\n"));
}
*/

/******************************************************************************************************
*******************************************************************************************************/
void
ClueItem :: DisplayDetail
(
	BTextView* textview
)
{
	textview->SetText(m_Detail);
}


/******************************************************************************************************
*******************************************************************************************************/
status_t
ClueItem :: Archive
(
	BMessage* archive
)
const
{
	archive->AddInt32("m_CAT", m_CAT);
	archive->AddInt32("m_EVT", m_EVT);
	archive->AddString("m_Method", m_Method);
	archive->AddString("m_Class", m_Class);
	archive->AddString("m_File", m_File);
	archive->AddInt32("m_Line", m_Line);
	archive->AddInt32("m_ThreadID", m_ThreadID);
	archive->AddInt32("m_Sequence", m_Sequence);
	archive->AddPointer("m_Inst_AsPointer", (const void*)m_Inst);
	archive->AddInt64("m_Time", m_Time);
	archive->AddString("m_Detail", m_Detail);
	archive->AddString("m_Description", m_Description);
	//don't archive m_InList, m_RefCount
	return B_OK;
}


/******************************************************************************************************
*******************************************************************************************************/
void
ClueItem :: Copy
(
	BString& outString
	,	uint32 inMask
	,	uint32 inNumber
)
{
	char tmpstr[30];
	time_t mytime(m_Time / 1000000);
	struct tm* pTime(localtime(&mytime));
	mytime = m_Time - (mytime * 1000000);

	outString << "\n\n[Begin Fingerprint #" << inNumber << "]\n" << (unsigned int) m_CAT << ", " <<
	(unsigned int) m_EVT << ", " << m_Method << ", " << m_Class << ", " << m_File << ", ";
	outString << m_Line << ", " << m_ThreadID << ", " << m_Sequence << ", ";
	strftime(tmpstr, 30, "%d/%m/%Y, ", pTime);
	outString << tmpstr;
	sprintf(tmpstr, "%02i:%02i:%02i.%06li", pTime->tm_hour, pTime->tm_min, pTime->tm_sec, mytime);
	outString << tmpstr << ", " << m_Description << ",\n" << m_Detail << "\n[End Fingerprint]\n";
}


/******************************************************************************************************
*******************************************************************************************************/
/*
int32
ClueItem :: AddRef
	(
	void
	)
{
	atomic_add (&m_RefCount, 1);
	return (m_RefCount);
}
*/


/******************************************************************************************************
*******************************************************************************************************/
/*
int32
ClueItem :: Release
	(
	void
	)
{
	atomic_add (&m_RefCount, -1);
	if (!m_RefCount)
	{
		delete this;
	}
	return m_RefCount;
}
*/

