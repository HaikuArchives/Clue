/*	
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef PROPERTYWINDOW_H
#include "TeamPropertyWindow.h"
#endif

#ifndef PROPERTYVIEW_H
#include "TeamPropertyView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


TeamPropertyWindow :: TeamPropertyWindow
	(
	const BWindow * wnd
,	const BView * view
,	const TeamItem * pTI
	)
:	BWindow (BRect (100, 100, 400, 400), "Properties", B_DOCUMENT_WINDOW_LOOK, B_MODAL_SUBSET_WINDOW_FEEL,
		B_NOT_ZOOMABLE | B_NOT_MINIMIZABLE | B_ASYNCHRONOUS_CONTROLS)
{
	BRect rc (Bounds ());
	AddChild (new TeamPropertyView (rc, wnd, view, pTI));
	rc = wnd->Frame ();
	BRect myrc (Bounds ());
	myrc.left = (myrc.right - myrc.left) / 2.0;
	myrc.top = (myrc.bottom - myrc.top) / 2.0;
	rc.left += (rc.right - rc.left) / 2.0 - myrc.left;
	rc.top += (rc.bottom - rc.top) / 2.0 - myrc.top;
	MoveTo (rc.left, rc.top);
	char title[50];
	sprintf (title, STR_WINDOW_TITLE_PROPERTIES, pTI->m_title);
	SetTitle (title);
	AddToSubset ((BWindow *) wnd);
	Show ();
}

