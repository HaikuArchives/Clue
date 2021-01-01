/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
//#define DEBUG 1

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _MESSAGE_RUNNER_H
#include <MessageRunner.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef RESOURCES_H
#include <Resources.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef STATUSBARVIEW_H
#include "StatusBarView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
***************************************************************/
StatusBarView :: StatusBarView
(
	BRect rcFrame
)
	:	BView(rcFrame, "StatusBarView", B_FOLLOW_BOTTOM | B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW)
	,	m_text(NULL)
	,	m_runner(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	m_text = (char*) new char[1];
	strcpy(m_text, "");

	SetFontSize(10.0);
}


/***************************************************************
***************************************************************/
StatusBarView :: ~StatusBarView
(
	void
)
{
	if (m_runner) {
		delete m_runner;
		m_runner = NULL;
	}
	delete [] m_text;
	m_text = NULL;
}

/***************************************************************
***************************************************************/
void
StatusBarView :: MessageReceived
(
	BMessage* msg
)
{
	switch (msg->what) {
		case 'cler': {
				if (m_runner) {
					delete m_runner;
					m_runner = NULL;
				}
				delete [] m_text;
				m_text = (char*) new char[1];
				strcpy(m_text, "");
				BRect rc(Bounds());
				rc.top = 1.0;
				Invalidate(rc);
			}
			break;
		default:
			BView::MessageReceived(msg);
	}
}


/***************************************************************
***************************************************************/
void
StatusBarView :: AllAttached
(
	void
)
{
}


/***************************************************************
***************************************************************/
void
StatusBarView :: Draw
(
	BRect updateRect
)
{
	//SetHighColor (ViewColor ());
	//FillRect (updateRect);
	SetHighColor(CLR_SHADOW_GREY);
	StrokeLine(BPoint(updateRect.left, 0), BPoint(updateRect.right, 0));
	BFont font;
	GetFont(&font);
	font_height fh;
	font.GetHeight(&fh);
	SetHighColor(CLR_BLACK);
	SetLowColor(ViewColor());
	DrawString(m_text, BPoint(5, fh.ascent + fh.leading));
}


/***************************************************************
***************************************************************/
void
StatusBarView :: SetPaneText
(
	const char* message)
{
	delete [] m_text;
	m_text = (char*) new char[strlen(message) + 1];
	strcpy(m_text, message);
	BRect rc(Bounds());
	rc.top = 1.0;
	Invalidate(rc);

	if (m_runner)
		delete m_runner;

	BMessage msg('cler');
	m_runner = reinterpret_cast<BMessageRunner*>(new BMessageRunner(BMessenger(this),
			&msg, 3000000, 1));
}

/***************************************************************
***************************************************************/
/*
void
CStatusBarView :: SetPaneText
	(
	int32 ResourceID
	)
{
	//To get app file info for be_app.
	app_info appInfo;
	BFile file;

	be_app->GetAppInfo (&appInfo);
	file.SetTo (&appInfo.ref, B_READ_ONLY);
	BResources resources (&file);
	size_t outSize (0);
	char * str ((char *) resources.LoadResource (B_STRING_TYPE, ResourceID, &outSize));

	if (str)
	{
		if (m_runner)
		{
			delete m_runner;
		}

		BMessage msg ('cler');
		m_runner = reinterpret_cast<BMessageRunner *> (new BMessageRunner (BMessenger (this),
														&msg, 3000000, 1));
		delete [] m_text;
		m_text = (char *) new char[strlen (str) + 1];
		strcpy (m_text, str);
		BRect rc (Bounds ());
		rc.top = 1.0;
		Invalidate (rc);
	}
}
*/
