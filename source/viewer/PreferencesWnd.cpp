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

#ifndef _PREFERENCESWND_H
#include "PreferencesWnd.h"
#endif

#ifndef _PREFERENCESVIEW_H
#include "PreferencesView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

static const BRect g_windowDefaultRectStartup (100.0f, 100.0f, 610.0f, 300.0f);
extern BMessage g_Settings;


PreferencesWnd :: PreferencesWnd
	(
	PreferencesWnd ** ppOutside
,	BMessage * message
	)
:	BWindow (g_windowDefaultRectStartup, STR_PREFERENCES_WINDOW_TITLE, B_TITLED_WINDOW_LOOK, 
		B_FLOATING_APP_WINDOW_FEEL, B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE)
,	m_ppOutside (ppOutside)
{
	BMessage msgtmp;
	if (B_OK == g_Settings.FindMessage ("Window:Preferences", &msgtmp))
	{
		PRINT (("\nConstructor found Window:Preferences\n"));
		BRect rc (0.0f, 0.0f, 0.0f, 0.0f);
		if (B_OK == msgtmp.FindRect ("WinRect", &rc))
		{
			PRINT (("  Found BRect, moveto and resize\n"));
			MoveTo (rc.left, rc.top);
			ResizeTo (rc.right, rc.bottom);
		}
	}

//	BScreen screen (this);
//	BRect rcScreen (screen.Frame ());
	BRect rcWnd (Bounds ());
//	BPoint pt ((rcScreen.Width () / 2) - (rcWnd.Width () / 2), (rcScreen.Height () / 2) - (rcWnd.Height () / 2));
//	MoveTo (pt.x, pt.y);

	PreferencesView * pPreferencesView (static_cast<PreferencesView *>(new PreferencesView (rcWnd, message)));
	AddChild (pPreferencesView);
	Show ();
}


PreferencesWnd :: ~PreferencesWnd
	(
	void
	)
{
	BRect rc (Frame ());
	rc.right =  Bounds().Width ();
	rc.bottom = Bounds().Height ();
	BMessage msgtmp;

	if (B_OK == g_Settings.FindMessage ("Window:Preferences", &msgtmp))
	{
		PRINT (("\nFound Window:Preferences\n"));

		BMessage msgData (B_RECT_TYPE);
		msgData.AddRect ("WinRect", rc);
		g_Settings.ReplaceMessage ("Window:Preferences", &msgData);
	}
	else
	{
		PRINT (("Window:Preferences not found, Add a message\n"));
		BMessage msgData (B_RECT_TYPE);
		msgData.AddRect ("WinRect", rc);
		g_Settings.AddMessage ("Window:Preferences", &msgData);
	}

	if (m_ppOutside)
	{
		*m_ppOutside = NULL;
	}
}


void
PreferencesWnd :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
	case MSG_BROADCAST_SETTINGS_CHANGED:
		SendNotices (MSG_SETTINGS_CHANGED);
		break;
	default:
		BWindow::MessageReceived (message);
		break;
	}
}
