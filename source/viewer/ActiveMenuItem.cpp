/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif

//====================================================================
//	BitmapMenuItem Implementation



//--------------------------------------------------------------------
//	BitmapMenuItem constructors, destructors, operators

ActiveMenuItem :: ActiveMenuItem
(
	BWindow* pWindow
	,	const char* label
	,	const char* sbar_message
	,	BMessage* message
	,	char shortcut
	,	uint32 modifiers
)
	:	BMenuItem(label, message, shortcut, modifiers)
	,	m_pWnd(pWindow)
	,	m_sbar_message(NULL)
{
	PRINT(("ActiveMenuItem: %s\n", label));
	if (NULL != sbar_message) {
		m_sbar_message = (char*) new char[strlen(sbar_message) + 1];
		strcpy(m_sbar_message, sbar_message);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
ActiveMenuItem :: ~ActiveMenuItem
(
	void
)
{
	if (NULL != m_sbar_message) {
		delete [] m_sbar_message;
		m_sbar_message = NULL;
	}
}


/******************************************************************************************************
*******************************************************************************************************/
status_t
ActiveMenuItem :: Invoke
(
	BMessage* message
)
{
	PRINT(("Menu Invoked\n"));
	return (BMenuItem::Invoke(message));
}


/******************************************************************************************************
*******************************************************************************************************/
void
ActiveMenuItem :: Highlight
(
	bool flag
)
{
	PRINT(("ActiveMenuItem::Highlight.\n"));
	BMenuItem::Highlight(flag);

	if (m_pWnd) {
		//newMsg.AddInt32 ("ResourceID", m_ResourceID);
		//newMsg.AddString("Menu Name", menuName);
//	BWindow* pWin (Menu()->Supermenu()->Window());
		BMessage postMsg(MSG_UPDATE_STATUS_UI);
		postMsg.AddString("string", m_sbar_message);
		m_pWnd->PostMessage(&postMsg);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
ActiveMenuItem :: SetStatusBarMessage
(
	const char* sbar_message
)
{
	delete [] m_sbar_message;
	m_sbar_message = (char*) new char[strlen(sbar_message) + 1];
	strcpy(m_sbar_message, sbar_message);
}
