/*
	1999 Jeff Braun
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

#ifndef _DIRECTORY_H
#include <Directory.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FILE_PANEL_H
#include <FilePanel.h>
#endif

#ifndef _FIND_DIRECTORY_H
#include <FindDirectory.h>
#endif

#ifndef _MENU_H
#include <Menu.h>
#endif

#ifndef _MENU_BAR_H
#include <MenuBar.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _MESSAGE_FILTER_H
#include <MessageFilter.h>
#endif

#ifndef _NODE_H
#include <Node.h>
#endif

#ifndef _NODE_INFO_H
#include <NodeInfo.h>
#endif

#ifndef _PATH_H
#include <Path.h>
#endif

#ifndef _SCROLL_BAR_H
#include <ScrollBar.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif

#ifndef PRINTWINDOW_H
#include "PrintWindow.h"
#endif

#ifndef CLUE_PRINT_VIEW_H
#include "PrintView.h"
#endif


extern BMessage g_Settings;


PrintWindow* PrintWindow::m_PrintWindow(NULL);

class PrintRedirector : public BMessageFilter {
public:
	PrintRedirector(PrintViewa* pHandler)
		:	BMessageFilter(B_PROGRAMMED_DELIVERY, B_LOCAL_SOURCE, 'data')
		,	m_NewHandler(pHandler)
	{
	};

	virtual filter_result	Filter(BMessage* msg, BHandler** target)
	{
//			PrintViewa * pPV (NULL);
//			pPV = dynamic_cast<PrintViewa *>(m_NewHandler);
//			pPV->MessageReceived (msg);
//			return (B_SKIP_MESSAGE);

		*target = m_NewHandler;
		return B_DISPATCH_MESSAGE;
	};
private:
	PrintViewa* 	m_NewHandler;
};

/***************************************************************
const declarations
***************************************************************/


/***************************************************************
***************************************************************/
PrintWindow :: PrintWindow
(
	void
)
	:	BWindow(BRect(100, 80, 450, 300), "Clue Print Queue", B_DOCUMENT_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	PrintViewa* pPV(new PrintViewa(Bounds()));
	AddCommonFilter(new PrintRedirector(pPV));
	AddChild(pPV);
//	AddFilter (new PrintRedirector (pPV));
	Register();
}


/***************************************************************
***************************************************************/
PrintWindow :: ~PrintWindow
(
	void
)
{
	m_PrintWindow = NULL;
	UnRegister();
}


void
PrintWindow :: DispatchMessage
(
	BMessage* message
	,	BHandler* handler
)
{
	//const char * pStr (handler->Name ());
	BWindow::DispatchMessage(message, handler);
}

/***************************************************************
***************************************************************/
void
PrintWindow :: MessageReceived
(
	BMessage* message
)
{
	switch (message->what) {
		case 'data':
//			m_PV->MessageReceived ();
			PRINT(("request a print\n"));
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}


/***************************************************************
***************************************************************/
bool
PrintWindow :: QuitRequested
(
	void
)
{
	return (true);
}


/***************************************************************
***************************************************************/
void
PrintWindow :: MenusBeginning
(
	void
)
{
}


/***************************************************************
***************************************************************/
void
PrintWindow :: Register
(
	void
)
{
	BMessenger messenger(be_app);
	BMessage message(MSG_WINDOW_REGISTRY_ADD);
	message.AddBool("Printer", true);
	message.AddString("title", Title());
	message.AddPointer("window", this);
	messenger.SendMessage(&message, this);
}


/***************************************************************
HelloWindow::Unregister

 Unregisters a window.  This tells the application that
 one fewer windows are open.  The application will
 automatically quit if the count goes to zero because
 of this call.
***************************************************************/
void
PrintWindow :: UnRegister
(
	void
)
{
	BMessenger messenger(be_app);
	BMessage message(MSG_WINDOW_REGISTRY_SUB);
	message.AddPointer("window", this);
	messenger.SendMessage(&message);
}


/***************************************************************
***************************************************************/
PrintWindow*
PrintWindow :: Create
(
	void
)
{
	//need to put a lock here!
	if (NULL == m_PrintWindow) {
		m_PrintWindow = new PrintWindow();
		m_PrintWindow->Show();
	}
	//need to unlock here!
	return (m_PrintWindow);
}

