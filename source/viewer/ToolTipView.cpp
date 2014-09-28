//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCREEN_H
#include <Screen.h>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef _TOOLTIPVIEW_H
#include "ToolTipView.h"
#endif

#ifndef _TOOLTIPWINDOW_H
#include "ToolTipWindow.h"
#endif


#define kHOR_MARGIN					  3//4		// hor. gap between frame and tip
#define kVER_MARGIN					  0//3		// ver. gap between frame and tip
#define kTIP_HOR_OFFSET				 10		// tip position right of cursor
#define kTIP_VER_OFFSET				 16		// tip position below cursor
#define kSLOP						  4		// mouse slop before tip hides

#define kTOOL_TIP_DELAY_TIME	 500000		// default delay time before tip shows (.5 secs.)
#define kTOOL_TIP_HOLD_TIME		3000000		// default hold time of time (3 secs.)

//const uint32 MSG_TIMER			= 'timr';

//#define kDRAW_WINDOW_FRAME

const rgb_color kVIEW_COLOR	= {255, 255, 225};//{255, 203, 0, 255};	// view background color (light yellow)
//const rgb_color kLIGHT_VIEW_COLOR = {255, 255, 80, 255}; // top left frame highlight
//const rgb_color kDARK_VIEW_COLOR = {175, 123, 0, 255}; // bottom right frame highlight


//====================================================================
ToolTipView :: ToolTipView
	(
	tool_tip_settings * settings
	)
:	BView (BRect (0.0f, 0.0f, 10.0f, 10.0f), "CToolTipView", B_FOLLOW_ALL, B_WILL_DRAW)
,	fString (NULL)
,	fThread (0)
{
	// initialize the tip
	fTip.app_active = true;
	fTip.quit = false;
	fTip.stopped = true;
	fTip.stop = true;
	fTip.reset = true;
	fTip.shown = false;
	fTip.showing = false;
	fTip.tip_timed_out = false;
	fTip.start = BPoint (0.0f, 0.0f);
	fTip.bounds = BRect (0.0f, 0.0f, 0.0f, 0.0f);
	fTip.tool_tip_view = NULL;
	fTip.tool_tip_window = NULL;
	fTip.start_time = 0L;
	fTip.expire_time = 0L;

	// initialize tooltip settings
	if (settings)
	{
		// we should probably sanity-check user defined settings (but we won't)
		fTip.settings = *settings;
	}
	else
	{
		// use defaults if no settings are passed
		fTip.settings.enabled = true;
		fTip.settings.one_time_only = false;
		fTip.settings.delay = kTOOL_TIP_DELAY_TIME;
		fTip.settings.hold = kTOOL_TIP_HOLD_TIME;
		fTip.settings.font = be_plain_font;
	}

	fString = static_cast<char *>(new char[1]);
	fString[0] = 0;

	// initialize the view
	SetFont (&fTip.settings.font);
	SetViewColor (kVIEW_COLOR);
}


//--------------------------------------------------------------------
ToolTipView :: ~ToolTipView
	(
	void
	)
{
	status_t	status;

	// kill tool_tip thread
	fTip.quit = true;
	wait_for_thread (fThread, &status);

	// delete tip
	delete [] fString;
}


//--------------------------------------------------------------------
void
ToolTipView :: AllAttached
	(
	void
	)
{
	// initialize internal settings
	fTip.tool_tip_view = this;
	fTip.tool_tip_window = Window ();

	// start tool_tip thread
	resume_thread (fThread = spawn_thread ((status_t (*)(void *)) ToolTipThread,
				"tip_thread", B_DISPLAY_PRIORITY, &fTip));
}


//--------------------------------------------------------------------
void
ToolTipView :: Draw
	(
	BRect /* where */)
{
	char *		src_strings[1];
	char *		tmp_string;
	char *		truncated_strings[1];
	BFont		font;
	font_height	finfo;

	// set pen position
	GetFont (&font);
	font.GetHeight (&finfo);
	MovePenTo (kHOR_MARGIN + 1, kVER_MARGIN + finfo.ascent);

	// truncate string if needed
	src_strings[0] = fString;
	tmp_string = static_cast<char *>(new char[strlen (fString) + 16]);
	truncated_strings[0] = tmp_string;
	font.GetTruncatedStrings ((const char **)src_strings, 1, B_TRUNCATE_END,
		Bounds ().Width () - (2 * kHOR_MARGIN) + 1, truncated_strings);

	// draw string
	SetLowColor (kVIEW_COLOR);
	SetHighColor (0, 0, 0, 255);
	DrawString(tmp_string);
	delete [] tmp_string;
}


//--------------------------------------------------------------------
void
ToolTipView :: MessageReceived
	(
	BMessage * message
	)
{
	switch (message->what)
	{
		case B_SOME_APP_ACTIVATED:
			PRINT (("tooltip view: B_SOME_APP_ACTIVATED\n"));
			message->FindBool ("active", &fTip.app_active);
			break;

		case MSG_TOOL_TIP_START:
			PRINT (("tooltip view: MSG_TOOL_TIP_START\n"));
			{
				const char * str (NULL);

				// extract parameters
				message->FindPoint ("start", &fTip.start);
				message->FindRect ("bounds", &fTip.bounds);
				message->FindString ("string", &str);
				delete [] fString;
				fString = static_cast<char *>(new char[strlen (str) + 1]);
				strcpy (fString, str);

				// force window to fit new parameters
				AdjustWindow ();

				// flag thread to reset
				fTip.reset = true;
			}
			break;

		case MSG_TOOL_TIP_STOP:
			PRINT (("tooltip view: MSG_TOOL_TIP_STOP\n"));
			// flag thread to stop
			fTip.stop = true;
			break;
		default:
			BView::MessageReceived (message);
	}
}


//--------------------------------------------------------------------
void
ToolTipView :: GetSettings
	(
	tool_tip_settings * settings
	)
{
	// return current settings
	*settings = fTip.settings;
}


//--------------------------------------------------------------------
void
ToolTipView :: SetSettings
	(
	tool_tip_settings * settings
	)
{
	bool	invalidate = fTip.settings.font != settings->font;

	// we should probably sanity-check user defined settings (but we won't)
	fTip.settings = *settings;

	// if the font changed, adjust window to fit
	if (invalidate)
	{
		Window()->Lock();
		SetFont (&fTip.settings.font);
		AdjustWindow ();
		Window()->Unlock();
	}
}


//--------------------------------------------------------------------
void
ToolTipView :: AdjustWindow
	(
	void
	)
{
	float			width (0);
	float			height (0);
	float			x (0);
	float			y (0);
	BScreen			s (B_MAIN_SCREEN_ID);
	BRect			screen (s.Frame ());
	ToolTipWindow *	TTWnd (dynamic_cast<ToolTipWindow *>(Window ()));
	font_height		finfo;

	screen.InsetBy (2, 2);	// we want a 2-pixel clearance
	fTip.settings.font.GetHeight (&finfo);
	width = fTip.settings.font.StringWidth (fString) + (kHOR_MARGIN * 2);  // string width
	height = (finfo.ascent + finfo.descent + finfo.leading) + (kVER_MARGIN * 2);  // string height

	// calculate new position and size of window
	x = fTip.start.x + kTIP_HOR_OFFSET;
	if ((x + width) > screen.right)
	{
		x = screen.right - width;
	}
	
	y = fTip.start.y + kTIP_VER_OFFSET;
	if ((y + height) > screen.bottom)
	{
		y = screen.bottom - height;
		if ((fTip.start.y >= (y - kSLOP)) && (fTip.start.y <= (y + height)))
		{
			y = fTip.start.y - kTIP_VER_OFFSET - height;
		}
	}
	if (x < screen.left)
	{
		width -= screen.left - x;
		x = screen.left;
	}
	if (y < screen.top)
	{
		height -= screen.top - y;
		y = screen.top;
	}

	TTWnd->MoveTo (static_cast<int>(x), static_cast<int>(y));
	TTWnd->ResizeTo (static_cast<int>(width), 0);//(int) height);
	TTWnd->SetDesiredHeight (static_cast<int>(height));

	// force an update
	Invalidate (Bounds ());
}


//--------------------------------------------------------------------
status_t
ToolTipView :: ToolTipThread
	(
	tool_tip * tip
	)
{
	uint32	buttons;
	BPoint	where;
	BScreen	s (B_MAIN_SCREEN_ID);
	BRect	screen = s.Frame ();

	screen.InsetBy (2, 2);
	while (!tip->quit)
	{
		if (tip->tool_tip_window->LockWithTimeout (0) == B_NO_ERROR)
		{
			tip->tool_tip_view->GetMouse (&where, &buttons);
			tip->tool_tip_view->ConvertToScreen (&where);

			tip->stopped = tip->stop;
			if (tip->reset)
			{
				PRINT (("tip->reset\n"));
				if (tip->showing)
				{
					tip->tool_tip_window->Hide();
				}
				tip->stop = false;
				tip->stopped = false;
				tip->reset = false;
				tip->shown = false;
				tip->showing = false;
				tip->start_time = system_time () + tip->settings.delay;
			}
			else if (tip->showing)
			{
				PRINT (("tip->showing\n"));
				if ((tip->stop) ||
					(!tip->settings.enabled) ||
					(!tip->app_active) ||
					(!tip->bounds.Contains (where)) ||
					(tip->expire_time < system_time ()) ||
					(abs (static_cast<int>(tip->start.x) - static_cast<int>(where.x)) > kSLOP) ||
					(abs (static_cast<int>(tip->start.y) - static_cast<int>(where.y)) > kSLOP) ||
					(buttons))
				{
					PRINT (("tooltip->Hide\n"));
					tip->tool_tip_window->Hide ();
					tip->shown = tip->settings.one_time_only;
					tip->showing = false;
					tip->tip_timed_out = (tip->expire_time < system_time ());
					tip->start_time = system_time () + tip->settings.delay;
				}
			}
			else if ((tip->settings.enabled) &&
					 (!tip->stopped) &&
					 (tip->app_active) &&
					 (!tip->shown) &&
					 (!tip->tip_timed_out) &&
					 (!buttons) &&
					 (tip->bounds.Contains (where)) &&
					 (tip->start_time < system_time ()))
			{
				PRINT (("tooltip->show\n"));
				tip->start = where;
				tip->tool_tip_view->AdjustWindow ();
				tip->tool_tip_window->Show ();
				tip->tool_tip_window->Activate (false);
				tip->showing = true;
				tip->expire_time = system_time () + tip->settings.hold;
				tip->start = where;
			}
			else if ((abs(static_cast<int>(tip->start.x) - static_cast<int>(where.x)) > kSLOP) ||
					 (abs(static_cast<int>(tip->start.y) - static_cast<int>(where.y)) > kSLOP))
			{
				tip->start = where;
				tip->start_time = system_time () + tip->settings.delay;
				tip->tip_timed_out = false;
			}

			if (buttons)
			{
				tip->start_time = system_time () + tip->settings.delay;
			}

			tip->tool_tip_window->Unlock ();
		}
		snooze (50000);
	}
	return B_NO_ERROR;
}

