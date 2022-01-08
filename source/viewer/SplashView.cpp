//#define DEBUG 1

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

#ifndef _SPLASHVIEW_H
#include "SplashView.h"
#endif

#ifndef _CREDITSVIEW_H
#include "CreditsView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/******************************************************************************************************
*******************************************************************************************************/
SplashView :: SplashView
(
	BRect frame
	,	bool IsAppStarting
)
	:	BView(frame, "Splash View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_PULSE_NEEDED)
	,	m_bmpSplash(NULL)
	,	m_pCreditsView(NULL)
	,	m_AppStarting(IsAppStarting)
	,	m_btnOK(NULL)
	,	m_pVersionInfo(NULL)
{
	SetViewColor(tint_color(CLR_BACKGROUND, B_DARKEN_1_TINT));
	//SetViewColor (B_TRANSPARENT_COLOR);
//	m_bmpSplash = RetrieveBitmap ("Splash");

	/* To get app file info for be_app. */
	app_info		appInfo;
	BFile			file;
	be_app->GetAppInfo(&appInfo);
	file.SetTo(&appInfo.ref, B_READ_ONLY);
	BAppFileInfo appFileInfo(&file);
	m_pVersionInfo = new version_info;
	appFileInfo.GetVersionInfo(m_pVersionInfo, B_APP_VERSION_KIND);

	char* pVariety("");
	switch (m_pVersionInfo->variety) {
		case 0:
			pVariety = "development";
			break;
		case 1:
			pVariety = "alpha";
			break;
		case 2:
			pVariety = "beta";
			break;
		case 3:
			pVariety = "gamma";
			break;
		case 4:
			pVariety = "golden master";
			break;
		case 5:
			pVariety = "final";
			break;
	}
	sprintf(m_VIString, STR_ABOUT_VERSION, m_pVersionInfo->major, m_pVersionInfo->middle, m_pVersionInfo->minor, pVariety);
	/*
		if (0) //!m_AppStarting)
		{
			m_pCreditsView = static_cast<CCreditsView *>(new CCreditsView);
			BScrollView * pSV (new BScrollView ("credit_listing", m_pCreditsView, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true, B_NO_BORDER));
			pSV->ResizeTo (200, 100);
			pSV->MoveTo (70, frame.bottom - 105);
			AddChild (pSV);

			BRect rcWnd (Bounds ());
			rcWnd.left = rcWnd.right - 60;
			rcWnd.top = rcWnd.bottom - 50;
			rcWnd.right = rcWnd.left + 50;
			rcWnd.bottom = rcWnd.top + 40;
			m_btnOK = static_cast<BButton *>(new BButton (rcWnd, STR_OK, STR_OK, new BMessage (B_QUIT_REQUESTED)));
			m_btnOK->MakeDefault (true);
			AddChild (m_btnOK);
		}
	*/
	if (!m_AppStarting) {
		BRect bnds(Bounds());
		m_pCreditsView = static_cast<CreditsView*>(new CreditsView);
		BScrollView* pSV(new BScrollView("credit_listing", m_pCreditsView, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true, B_NO_BORDER));
//		pSV->SetViewColor (CLR_TOOLBAR_GREY);
		pSV->ResizeTo(250, 145);
		pSV->MoveTo(55, bnds.bottom - 150);
		AddChild(pSV);

		bnds.left = bnds.right - 60;
		bnds.top = bnds.bottom - 50;
		bnds.right = bnds.left + 50;
		bnds.bottom = bnds.top + 40;
		m_btnOK = static_cast<BButton*>(new BButton(bnds, STR_OK, STR_OK, new BMessage(B_QUIT_REQUESTED)));
		m_btnOK->MakeDefault(true);
		AddChild(m_btnOK);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
SplashView :: ~SplashView
(
	void
)
{
	delete m_bmpSplash;
	m_bmpSplash = NULL;
	if (m_pVersionInfo) {
		delete m_pVersionInfo;
		m_pVersionInfo = NULL;
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
SplashView :: Draw
(
	BRect updateRect
)
{
	BRect bnds(Bounds());

	SetHighColor(tint_color(CLR_BACKGROUND, B_HIGHLIGHT_BACKGROUND_TINT));
	FillRect(BRect(0, 0, 31, bnds.bottom));

	BRect rect(Bounds());
	float vals[6] = {1.7F, 1.6F, 1.5F, 1.4F, 1.3F, 1.2F};
	for (int i(5); i >= 0; i--) {
		SetHighColor(tint_color(CLR_BACKGROUND, vals[i]));
		for (int j(i), y(0); j >= 0; j--, y++) {
			bnds.left = rect.right - ((j + 1) * 15.0f);
			bnds.right = bnds.left + 15.0f;
			bnds.top = y * 15.0f;
			bnds.bottom = bnds.top + 15.0f;
			FillRect(bnds);
		}
	}

	SetHighColor(CLR_BLACK);
	//SetFontSize (50);
	BFont font;
	font_height fh;
	//PRINT (("fh.a %f, fh.d %f, fh.l %f.\n", fh.ascent, fh.descent, fh.leading));
	font.SetSize(50);
	font.GetHeight(&fh);
	SetFont(&font, B_FONT_SIZE);
	//GetFont (&font);

	escapement_delta deltas[1];
	const char* StringArray[1] = {static_cast<const char*>(m_pVersionInfo->short_info)};   //0};
	BRect RectArray[1];

	//StringArray[0] = static_cast<const char *>(m_pVersionInfo->short_info);
	deltas[0].nonspace = 0.0;
	deltas[0].space = 0.0;
	font.GetBoundingBoxesForStrings(StringArray, 1, B_SCREEN_METRIC, deltas, RectArray);
	//BPoint pt (RectArray[0].Width (), RectArray[0].Height ()); //(0, 0);
	//pt.x = RectArray[0].Width ();
	//pt.y = RectArray[0].Height ();
	//SetDrawingMode (B_OP_COPY);
	//Sync ();
	//PRINT (("fh.a %f, fh.d %f, fh.l %f.\n", fh.ascent, fh.descent, fh.leading));
	//PRINT (("width %f, %f.\n", pt.x, pt.y));
	//PRINT (("Rect %f, %f, %f, %f.\n", RectArray[0].left, RectArray[0].top, RectArray[0].right, RectArray[0].bottom));
	//StrokeRect (RectArray[0]);

	//MovePenTo (bnds.Width () / 2 - pt.x / 2, 40 + fh.ascent);

	MovePenTo(55, fh.ascent);
	SetDrawingMode(B_OP_OVER);
	DrawString(StringArray[0]);
	font.SetSize(20);
	SetFont(&font, B_FONT_SIZE);
	//MovePenTo (bnds.Width () / 2 - pt.x / 2, 60 + fh.ascent);
	MovePenTo(57, 35 + fh.ascent);
//	SetHighColor (CLR_BLACK);
	DrawString(m_VIString);

	/* To get app file info for be_app. */
	app_info appInfo;
	if (B_OK == be_app->GetAppInfo(&appInfo)) {
		BFile file(&appInfo.ref, B_READ_ONLY);
		BAppFileInfo appFileInfo(&file);
		BBitmap* bmpIcon(new BBitmap(BRect(0.0, 0.0, 31.0, 31.0), B_CMAP8));
		if (B_OK == appFileInfo.GetIcon(bmpIcon, B_LARGE_ICON)) {
			MovePenTo(16, 16);
			DrawBitmap(bmpIcon);
		}
		delete bmpIcon;
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
SplashView :: Pulse
(
	void
)
{
	if (m_AppStarting)
		Window()->PostMessage(B_QUIT_REQUESTED, Window());
}


/******************************************************************************************************
*******************************************************************************************************/
void
SplashView :: AttachedToWindow
(
	void
)
{
	if (!m_AppStarting)
		m_btnOK->MakeFocus(true);
	BWindow* pwnd(Window());
	if (pwnd)
		((BHandler*)pwnd)->StartWatching((BHandler*) this, MSG_SETTINGS_CHANGED);
}



/***************************************************************
***************************************************************/
void
SplashView :: MessageReceived
(
	BMessage* message
)
{
	switch (message->what) {
		case B_OBSERVER_NOTICE_CHANGE: {
				uint32 change(0);
				message->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32*) &change);
				switch (change) {
					case MSG_SETTINGS_CHANGED:
						SetViewColor(tint_color(CLR_BACKGROUND, B_DARKEN_1_TINT));
						SetLowColor(tint_color(CLR_BACKGROUND, B_DARKEN_1_TINT));
						Invalidate();
						m_pCreditsView->SetViewColor(tint_color(CLR_BACKGROUND, B_DARKEN_1_TINT));
						m_pCreditsView->SetLowColor(tint_color(CLR_BACKGROUND, B_DARKEN_1_TINT));
						m_pCreditsView->Invalidate();
						break;
				}
			}
			break;
		default:
			BView::MessageReceived(message);
			break;
	}
}


