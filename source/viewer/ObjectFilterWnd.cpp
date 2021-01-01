//#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _SCREEN_H
#include <Screen.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _OBJECTFILTERWND_H
#include "ObjectFilterWnd.h"
#endif

#ifndef _OBJECTFILTERVIEW_H
#include "ObjectFilterView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

static const BRect g_windowDefaultRectStartup(100.0f, 100.0f, 300.0f, 500.0f);
extern BMessage g_Settings;
static const char* strWOF = "Window:ObjectFilter";


ObjectFilterWnd :: ObjectFilterWnd
(
	ObjectFilterWnd** ppOutside
)
	:	BWindow(g_windowDefaultRectStartup, STR_WINDOW_TITLE_FILTER, B_DOCUMENT_WINDOW_LOOK,
				B_FLOATING_APP_WINDOW_FEEL, B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE)
	,	m_ppOutside(ppOutside)
{
	BMessage msgtmp;
	if (B_OK == g_Settings.FindMessage(strWOF, &msgtmp)) {
		PRINT(("\nConstructor found Window:ObjectFilter\n"));
		BRect rc(0.0f, 0.0f, 0.0f, 0.0f);
		if (B_OK == msgtmp.FindRect("WinRect", &rc)) {
			PRINT(("  Found BRect, moveto and resize\n"));
			MoveTo(rc.left, rc.top);
			ResizeTo(rc.right, rc.bottom);
		}
	}

	BRect rcWnd(Bounds());

	ObjectFilterView* pObjectFilterView(static_cast<ObjectFilterView*>(new ObjectFilterView(rcWnd)));
//	ObjectFilterView * pObjectFilterView (new ObjectFilterView (rcWnd, message));
	AddChild(pObjectFilterView);
	float minW(0.0f);
	float maxW(0.0f);
	float minH(0.0f);
	float maxH(0.0f);
	GetSizeLimits(&minW, &maxW, &minH, &maxH);
	SetSizeLimits(100.0f, maxW, 100.0f, maxH);
	Show();
}


ObjectFilterWnd :: ~ObjectFilterWnd
(
	void
)
{
	BRect rc(Frame());
	rc.right =  Bounds().Width();
	rc.bottom = Bounds().Height();
	BMessage msgtmp;

	if (B_OK == g_Settings.FindMessage(strWOF, &msgtmp)) {
		PRINT(("\nFound Window:ObjectFilter\n"));

		BMessage msgData(B_RECT_TYPE);
		msgData.AddRect("WinRect", rc);
		g_Settings.ReplaceMessage(strWOF, &msgData);
	} else {
		PRINT(("Window:ObjectFilter not found, Add a message\n"));
		BMessage msgData(B_RECT_TYPE);
		msgData.AddRect("WinRect", rc);
		g_Settings.AddMessage(strWOF, &msgData);
	}

	if (m_ppOutside)
		*m_ppOutside = NULL;
}


void
ObjectFilterWnd :: MessageReceived
(
	BMessage* message
)
{
	switch (message->what) {
		case MSG_BROADCAST_SETTINGS_CHANGED:
			SendNotices(MSG_SETTINGS_CHANGED);
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}
