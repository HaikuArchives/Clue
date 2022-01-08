/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include headers
***************************************************************/
//#define DEBUG 1

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef TEAMTAB_H
#include "TeamTab.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
globals
***************************************************************/
#define TOP_BUFFER_SPACE 3.0f
static bool g_bDrawLeft = true;

/***************************************************************
***************************************************************/
TeamTab :: TeamTab
(
	BBitmap* bitmap
	,	BView* tabView
)
	:	BTab(tabView)
	,	m_bitmap(bitmap)
{
}


/***************************************************************
***************************************************************/
void
TeamTab :: DrawTab
(
	BView* owner
	,	BRect frame
	,	tab_position position
	,	bool full
)
{
	rgb_color hi(owner->HighColor());
	rgb_color lo(owner->LowColor());

	PRINT(("\n\nTeamTab view owners name '%s'\n", owner->Name()));

	BRect orgframe(frame);
	if (B_TAB_ANY != position)
		g_bDrawLeft = true;

	if (B_TAB_FRONT != position) {
		owner->SetHighColor(CLR_BACKGROUND);
		BRect fr(frame.left, frame.top, frame.right + 2.0f, frame.bottom);
		if (g_bDrawLeft)
			fr.left -= 2.0f;
		else
			fr.left += 3.0f;
		owner->FillRect(fr);
	}

	float bumper(B_TAB_FRONT == position ? -2.0f : 3.0f);
	frame.left += bumper;
	frame.right -= bumper;
	frame.top += B_TAB_FRONT == position ? 0.0f : 2.0f;

	if (B_TAB_FRONT == position) {
		owner->SetHighColor(CLR_FOREGROUND);
		BRect fr(frame.left, frame.top, frame.right, frame.bottom + 1.0f);
		owner->FillRect(fr);
	}
	owner->SetHighColor(0, 0, 0, 150);
	owner->SetDrawingMode(B_OP_OVER);

	owner->DrawBitmapAsync(m_bitmap, BRect(frame.left + 4.0f, frame.top + 3.0f, frame.left + 19.0f, frame.top + 18.0f));

	owner->SetDrawingMode(B_OP_COPY);

	owner->SetHighColor(CLR_BLACK);
	owner->SetLowColor(CLR_FOREGROUND);

	// Start a line array to draw the tab
	owner->BeginLineArray(3);

	if (g_bDrawLeft) {
//		if (B_TAB_FRONT == position)
//		{
//			owner->AddLine (BPoint (frame.left, frame.bottom), BPoint (frame.left, frame.top), CLR_FOREGROUND_LITE);
//		}
//		else
//		{
//			owner->AddLine (BPoint (frame.left, frame.bottom), BPoint (frame.left, frame.top), CLR_BACKGROUND_LITE);
//		}
		owner->AddLine(BPoint(frame.left, frame.bottom), BPoint(frame.left, frame.top),
					   ((B_TAB_FRONT == position) ? CLR_FOREGROUND_LITE : CLR_BACKGROUND_LITE));
	} else
		g_bDrawLeft = true;

	// Top -- always drawn
	owner->AddLine(BPoint(frame.left, frame.top), BPoint(frame.right, frame.top),
				   (B_TAB_FRONT == position) ? CLR_FOREGROUND_LITE : CLR_BACKGROUND_LITE);
//	if (B_TAB_FRONT == position)
//	{
//		owner->AddLine (BPoint (frame.left, frame.top), BPoint (frame.right, frame.top), CLR_FOREGROUND_LITE);
//	}
//	else
//	{
//		owner->AddLine (BPoint (frame.left, frame.top), BPoint (frame.right, frame.top), CLR_BACKGROUND_LITE);
//	}

//	owner->AddLine (BPoint (frame.left, frame.top), BPoint (frame.right, frame.top), CLR_WHITE);

	// Right wall
	if (full) {
		owner->AddLine(BPoint(frame.right, frame.top + 1), BPoint(frame.right, frame.bottom + 5.0f),
					   B_TAB_FRONT == position ? CLR_FOREGROUND_DARK : CLR_BACKGROUND_DARK);
//		owner->AddLine (BPoint (frame.right, frame.top + 1), BPoint (frame.right, frame.bottom),
//			B_TAB_FRONT == position ? CLR_DARK_GREY : CLR_DARK_TOOLBAR_GREY);
	}

	owner->EndLineArray();

	if (B_TAB_FRONT == position)
		owner->SetLowColor(CLR_FOREGROUND);
	else
		owner->SetLowColor(CLR_BACKGROUND);

	DrawLabel(owner, frame);
	if (owner->Window()->IsActive())
		DrawFocusMark(owner, orgframe);

	owner->SetHighColor(hi);
	owner->SetLowColor(lo);

	if (B_TAB_FRONT == position)
		g_bDrawLeft = false;
};


/***************************************************************
***************************************************************/
void
TeamTab :: DrawLabel
(
	BView* owner
	,	BRect frame
)
{
	font_height height;
	owner->GetFontHeight(&height);
	owner->MovePenTo(frame.left + 22.0, height.leading + height.ascent + frame.top + TOP_BUFFER_SPACE);
	rgb_color hi(owner->HighColor());
	rgb_color lo(owner->LowColor());

	owner->SetHighColor(CLR_BLACK);
	//owner->SetFont (IsSelected () ? be_bold_font : be_plain_font);
	BFont font;
	owner->GetFont(&font);
	char strShortTitle[B_FILE_NAME_LENGTH + 3];
	const char* instr[1];
	instr[0] = Label();
	char* outstr[1];
	outstr[0] = strShortTitle;
	font.GetTruncatedStrings(instr, 1, B_TRUNCATE_END, frame.right - frame.left - 25, outstr);
	owner->DrawString(strShortTitle);

	owner->SetHighColor(hi);
	owner->SetLowColor(lo);
}


/***************************************************************
***************************************************************/
void
TeamTab :: DrawFocusMark
(
	BView* owner
	,	BRect frame
)
{
#ifdef DEBUG
	PRINT(("DrawFocusMark\n"));
	if (owner->IsFocus())
		PRINT((" owner FOCUSED\n"));
	else
		PRINT((" owner NOT focused\n"));
#endif

	float bumper(IsSelected()  ? -2.0f : 3.0f);
	float ceiling(TOP_BUFFER_SPACE + (IsSelected() ? 0.0f : 2.0f));
	if (BTab::IsFocus()) {
		PRINT(("   Focused\n"));
		owner->SetHighColor(keyboard_navigation_color());
	} else {
		PRINT(("   NOT Focused\n"));
		owner->SetHighColor(IsSelected() ? CLR_FOREGROUND : owner->ViewColor());
	}

#ifdef DEBUG
	if (BTab::IsSelected())
		PRINT(("   Selected\n"));
	else
		PRINT(("   NOT Selected\n"));
#endif

	font_height height;
	owner->GetFontHeight(&height);
	float totalheight(height.leading + height.ascent + height.descent + ceiling + 1.0f);
	owner->StrokeLine(BPoint(frame.left + 22.0f + bumper, totalheight), BPoint(frame.right - 2.0f - bumper, totalheight));
	PRINT(("  frame = [%0.f, %0.f]\n", frame.left, frame.right));
}


