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

#ifndef _SPLASH_H
#include "SplashWindow.h"
#endif

#ifndef _SPLASHVIEW_H
#include "SplashView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

static const BRect g_windowDefaultRect (0, 0, 400, 240);
static const BRect g_windowDefaultRectStartup (0, 0, 400, 200);


/***************************************************************
***************************************************************/
SplashWindow :: SplashWindow
	(
	SplashWindow ** ppOutside
,	bool IsAppStarting
	)
:	BWindow (g_windowDefaultRectStartup, STR_WINDOW_TITLE_ABOUT, B_BORDERED_WINDOW_LOOK, B_FLOATING_APP_WINDOW_FEEL, B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_NOT_RESIZABLE)
,	m_ppOutside (ppOutside)
{
	if (IsAppStarting)
	{
		ResizeTo (g_windowDefaultRectStartup.Width (), g_windowDefaultRectStartup.Height ());
		SetPulseRate (0);
	}
	else
	{
		ResizeTo (g_windowDefaultRect.Width (), g_windowDefaultRect.Height ());
		SetLook (B_TITLED_WINDOW_LOOK);
		SetPulseRate (10000);
	}
	BScreen screen (this);
	BRect rcScreen (screen.Frame ());
	BRect rcWnd (Bounds ());
	BPoint pt ((rcScreen.Width () / 2) - (rcWnd.Width () / 2), (rcScreen.Height () / 2) - (rcWnd.Height () / 2));
	MoveTo (pt.x, pt.y);

	SplashView * pSplashView (static_cast<SplashView *>(new SplashView (rcWnd, IsAppStarting)));
	AddChild (pSplashView);
	Show ();
}


/***************************************************************
***************************************************************/
SplashWindow :: ~SplashWindow
	(
	void
	)
{
	if (m_ppOutside)
	{
		*m_ppOutside = NULL;
	}
}


/***************************************************************
***************************************************************/
void
SplashWindow :: MessageReceived
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


/***************************************************************
***************************************************************/
void
SplashWindow :: BeginCountdown
	(
	void
	)
{
	SetPulseRate (1000000);
}

