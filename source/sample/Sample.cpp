/*
	Jeff Braun
	web: http://www.tcinternet.net/users/brauns/
	emai1: yobkadon@hotmail.com
*/

/***************************************************************
include header files
***************************************************************/
#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BOX_H
#include <Box.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _CHECK_BOX_H
#include <CheckBox.h>
#endif

#ifndef _CLIPBOARD_H
#include <Clipboard.h>
#endif

#ifndef _DIRECTORY_H
#include <Directory.h>
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

#ifndef _MESSAGE_RUNNER_H
#include <MessageRunner.h>
#endif

#ifndef _NODE_INFO_H
#include <NodeInfo.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _POLYGON_H
#include <Polygon.h>
#endif

#ifndef _RADIO_BUTTON_H
#include <RadioButton.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCREEN_H
#include <Screen.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _VOLUME_H
#include <Volume.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#define CLUE //define this to allow sending of Clue messages
#include "Clue.h"

#include "Sample.h"

static const int32 MSG_TIMER			= 'timr';
static const int32 MSG_AUTOSEND			= 'auts';
static const int32 MSG_ALL_CLUE_ENTRIES	= 'mall';
static const int32 MSG_INSPECT_OBJECTS	= 'insp';

/***************************************************************
***************************************************************/
int
main
(
	int
	,	char**
)
{
	TRACE_METHOD((CC_APPLICATION, REPORT_METHOD, "everything starts here!"));
	new CApp;
	be_app->Run();
	delete be_app;

	return (0);
}


int* NonClassFunction(void)
{
	TRACE_SIMPLE((CC_SUPPORT, CR_INFO, "I can now put a trace in a non-class function!!!"));
	int i(0);
	return &i; //this may be bad form to return a ptr to a fn leve var, but we're not doing anything with it!!!
}


namespace ClueTestNameSpace {

class TestNameSpaces {
public:
	TestNameSpaces(void) {}
	~TestNameSpaces(void) {}
};

} //end namespace

class ClueTestNameSpace::TestNameSpaces* NameSpaceFuntion(void)
{
	TRACE_SIMPLE((CC_SUPPORT, CR_INFO, "testing non-class function using namespaces"));
	ClueTestNameSpace::TestNameSpaces* tns(new ClueTestNameSpace::TestNameSpaces());
	return tns;
}



/***************************************************************
***************************************************************/
CApp :: CApp
(
	void
)
	:	BApplication("application/x-vnd.JeffBraun-ClueTester")
{
	TRACE_METHOD((CC_APPLICATION, REPORT_METHOD, "application/x-vnd.JeffBraun-ClueTester"));
	new CWindow(BRect(50, 50, 300, 350));
	TRACE_SIMPLE((CC_APPLICATION, CR_INFO, "Hooray! We're on our way."));
	BRect rc(1.0f, 2.0f, 3.0f, 4.0f);
	TRACE_OBJECT((CC_APPLICATION, CR_OBJECT, &rc, "test BRect stuff"));

	BMessage msg('abcd');
	bool blnValue(true);
	bool blnValue2(false);
	msg.AddBool("a bool in msg", blnValue);
	msg.AddFloat("a float in msg", 3.14);
	BMessage msg2('efgh');
	msg2.AddBool("a bool in msg2", blnValue2);
	msg2.AddPoint("a BPoint in msg2", BPoint(1.0f, 2.0f));
	BMessage msg3('ijkl');
	bool blnValue3(false);
	msg3.AddBool("a bool in msg3", blnValue3);
	msg3.AddInt32("an Int32 in msg3", 1234);
	msg2.AddMessage("msg3 in msg2", &msg3);
	msg.AddMessage("msg2", &msg2);
	TRACE_OBJECT((CC_APPLICATION, CR_OBJECT, &msg, "Test the BMessage handling."));
}


/***************************************************************
***************************************************************/
void
CApp :: AppActivated
(
	bool active
)
{
	TRACE_SIMPLE((CC_APPLICATION, CR_INFO, "active = %i", active));
}


/***************************************************************
***************************************************************/
void
CApp :: DispatchMessage
(
	BMessage* message
	,	BHandler* handler
)
{
//  take out to add details messages
//	BString str ("send to: ");
//	str.Append (handler->Name ());
//	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, message, str.String ()));

	BApplication::DispatchMessage(message, handler);
}


/***************************************************************
***************************************************************/
void
CApp :: ReadyToRun
(
	void
)
{
	TRACE_SIMPLE((CC_APPLICATION, CR_INFO));
}


/***************************************************************
***************************************************************/
CWindow :: CWindow
(
	BRect frame
)
	:	BWindow(frame, "The Clue Tester Sample App", B_DOCUMENT_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	TRACE_METHOD((CC_INTERFACE, REPORT_METHOD, "frame: l=%0.f, t=%0.f, r=%0.f, b=%0.f",
				  frame.left, frame.top, frame.right, frame.bottom));
	m_pMenuBar = new BMenuBar(BRect(0, 0, 0, 0), "Sample Menu Bar");
	BuildEditMenu();
	m_pMenuBar->AddItem(m_pMenu);
	AddChild(m_pMenuBar);

	float menuHeight(m_pMenuBar->Bounds().Height());

	BRect rc(Bounds());
	rc.top = menuHeight;
	AddChild(new CView(rc));
	BView* pView(new BView(BRect(10, 10, 200, 200), "Just a dummy view", B_FOLLOW_NONE, 0));
	pView->Hide();  //hide it
	AddChild(pView);

//	SetPulseRate (100000); //Set pulse rate so TextViews cursor blinks!
	SetPulseRate(0);  //or not
	TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, this, "CWindow constructor 'this', but unlocked!"));

	Show();

	TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, this, "CWindow constructor 'this', but unlocked!"));
}


/***************************************************************
***************************************************************/
void
CWindow :: BuildEditMenu
(
	void
)
{
	m_pMenu = new BMenu("Edit");

	m_pMenuItem1 = new BMenuItem("Cut", new BMessage(B_CUT), 'x', B_COMMAND_KEY);
	m_pMenuItem1->SetTarget(NULL, this);
	m_pMenu->AddItem(m_pMenuItem1);

	m_pMenuItem2 = new BMenuItem("Copy", new BMessage(B_COPY), 'c', B_COMMAND_KEY);
	m_pMenuItem2->SetTarget(NULL, this);
	m_pMenu->AddItem(m_pMenuItem2);

	m_pMenu->AddSeparatorItem();

	m_pMenuItem3 = new BMenuItem("Select All", new BMessage(B_SELECT_ALL), 'a', B_COMMAND_KEY);
	m_pMenuItem3->SetTarget(NULL, this);
	m_pMenu->AddItem(m_pMenuItem3);
}



/***************************************************************
***************************************************************/
void
CWindow :: DispatchMessage
(
	BMessage* message
	,	BHandler* handler
)
{
//  take out for detailed messages
//	BString str ("send to: ");
//	str.Append (handler->Name ());
//	TRACE_OBJECT ((CC_INTERFACE, CR_OBJECT, message, str.String ()));

	BWindow::DispatchMessage(message, handler);
}


/***************************************************************
***************************************************************/
bool
CWindow :: QuitRequested
(
	void
)
{
	TRACE_METHOD((CC_INTERFACE, REPORT_METHOD));
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


/***************************************************************
***************************************************************/
CView :: CView
(
	BRect frame
)
	:	BView(frame, "The CView", B_FOLLOW_ALL_SIDES, B_PULSE_NEEDED)
	,	m_BCheckBox(NULL)
	,	m_BMessageRunner(NULL)
	,	m_BTextView(NULL)
	,	m_BScrollView(NULL)
	,	m_BBox(NULL)
	,	m_BRadioButton(NULL)
{
	TRACE_METHOD((CC_INTERFACE, REPORT_METHOD, "frame: l=%0.f, t=%0.f, r=%0.f, b=%0.f",
				  frame.left, frame.top, frame.right, frame.bottom));
	SetViewColor(255, 128, 128, 255);

	BRect rc(Bounds());
	rc.InsetBy(5.0f, 5.0f);
	m_BBox = new BBox(rc, "surrounding bbox", B_FOLLOW_ALL);
	m_BBox->SetLabel("Inspectable controls:");
	AddChild(m_BBox);

	m_BButtons[0] = new BButton(BRect(10, 30, 0, 0), "btnGenerate 101", "Generate all messages", new BMessage(MSG_ALL_CLUE_ENTRIES));
	m_BButtons[0]->ResizeToPreferred();
	m_BBox->AddChild(m_BButtons[0]);
	rc = m_BButtons[0]->Frame();
	m_BButtons[1] = new BButton(BRect(10, rc.bottom + 10.0, 0, 0), "btnInspect", "Inspect objects", new BMessage(MSG_INSPECT_OBJECTS));
	m_BButtons[1]->ResizeToPreferred();
	m_BBox->AddChild(m_BButtons[1]);
	rc = m_BButtons[1]->Frame();

	m_BCheckBox = new BCheckBox(BRect(rc.right + 10, rc.top, 200.0f, 100.0f), "chkTimer", "Timer", new BMessage(MSG_TIMER));
	m_BCheckBox->ResizeToPreferred();
	m_BBox->AddChild(m_BCheckBox);

	m_BRadioButton = new BRadioButton(BRect(10, rc.bottom + 10.0, 0, 0), "rdoButton", "Here's a radio button", NULL);
	m_BRadioButton->ResizeToPreferred();
	m_BBox->AddChild(m_BRadioButton);
	rc = m_BRadioButton->Frame();

	m_BTextView = new CTextView(BRect(10.0, rc.bottom + 10.0, 200, rc.bottom + 100), "txtEntry",
								BRect(2.0f, 2.0f, 198.0f - B_V_SCROLL_BAR_WIDTH, 98.0f), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_PULSE_NEEDED);
	m_BScrollView = new BScrollView("scroll view for txtEntry", m_BTextView, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true, B_FANCY_BORDER);
	m_BBox->AddChild(m_BScrollView);
}


/***************************************************************
***************************************************************/
void
CView :: AllAttached
(
	void
)
{
	TRACE_METHOD((CC_INTERFACE, REPORT_METHOD));

	m_BButtons[0]->SetTarget(this);
	m_BButtons[1]->SetTarget(this);

	m_BButtons[0]->MakeFocus(true);

	m_BCheckBox->SetTarget(this);

	TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, this, "the CView"));
}


/***************************************************************
***************************************************************/
void
CView :: MessageReceived
(
	BMessage* msg
)
{
	switch (msg->what) {
		case MSG_INSPECT_OBJECTS: {

				//no need to Lock looper as it's done implicitly for MessageReceived!!!
				CWindow* pWnd((CWindow*) this->Window());
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, (BHandler*) pWnd, "the CWindow handler"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, (BLooper*) pWnd, "the CWindow looper"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, pWnd, "the CWindow"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, pWnd->m_pMenu, "m_pMenu"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, pWnd->m_pMenuBar, "m_pMenuBar"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, pWnd->m_pMenuItem1, "m_pMenuItem1"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, (BHandler*) this, "the CView handler"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, this, "the CView"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BButtons[0], "m_buttons[0]"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, (BInvoker*) m_BCheckBox, "the m_BCheckBox invoker"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BCheckBox, "m_BCheckBox"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BTextView, "m_BTextView"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BScrollView, "m_BScrollView"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BBox, "m_BBox"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, m_BRadioButton, "m_BRadioButton"));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, msg, "MessageReceiveds message"));
				BFont font;
				GetFont(&font);
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &font, "the CViews font"));
				BPoint pt(3.0f, 2.0f);
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &pt, "a point"));
				BRect rect(Bounds());
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &rect, "a rect"));

				//FIXME TRACE_OBJECT for BApplication seems to be missing
				//be_app->Lock ();  //needs to be locked!!!
				//TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, be_app, "be_app"));
				//be_app->Unlock ();

				TRACE_OBJECT((CC_APPLICATION, CR_OBJECT, &be_app_messenger, "be_app_messenger"));

				be_clipboard->Lock();   //needs to be locked!!!
				TRACE_OBJECT((CC_GENERAL, CR_OBJECT, be_clipboard, "be_clipboard"));
				be_clipboard->Unlock();

				TRACE_OBJECT((CC_APPLICATION, CR_OBJECT, (BRoster*) be_roster, "be_roster"));   //get rid of const so compiles

				BRegion rgn;
				rgn.Include(BRect(1, 1, 2, 2));
				rgn.Include(BRect(4, -4, 4444, 4));
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &rgn, "a region"));

				BScreen screen;
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &screen, "a screen"));

				innerclass IC;
				IC.Debug2();
				IC.Debug3();
				IC.Debug4();

				NonClassFunction();
				//using ClueTestNameSpace;
				ClueTestNameSpace::TestNameSpaces* tns((ClueTestNameSpace::TestNameSpaces*) NameSpaceFuntion());
				delete tns;

				//BNode node ("/boot/beos/etc/Keymap/American");
				BNode node("/boot/beos/documentation/Read_Me_First.html");
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &node, "a node"));

				BNodeInfo info(&node);
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &info, "a nodeinfo"));

				BDirectory dir("/boot/home");
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &dir, "a directory"));

				BEntry entry("/boot/beos/documentation/Read_Me_First.html");
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &entry, "an entry"));
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, (BStatable*) &entry, "an casted entry to a statable"));

				BFile file("/boot/beos/documentation/Read_Me_First.html", B_READ_ONLY);
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &file, "a file"));

				BMimeType mime("application/x-vnd.Jeff-Clue");
//			BMimeType mime ("text/x-source-code");
				TRACE_OBJECT((CC_GENERAL, CR_OBJECT, &mime, "a mime type"));

				BVolume vol(4);
				TRACE_OBJECT((CC_STORAGE, CR_OBJECT, &vol, "a volume"));

				status_t retcode(B_TIMED_OUT);
				TRACE_OBJECT((CC_GENERAL, CR_OBJECT, retcode));

				retcode = B_ERROR;
				TRACE_OBJECT((CC_GENERAL, CR_OBJECT, retcode, "a return code B_ERROR"));

				retcode = B_OK;
				TRACE_OBJECT((CC_GENERAL, CR_OBJECT, retcode, "a return code B_OK"));

				//the code is somewhat forgiving, as it will check for NULL entries
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, (BView*) NULL, "a NULL BView object passed in!"));

				system_info si;
				get_system_info(&si);
				TRACE_OBJECT((CC_INTERFACE, CR_OBJECT, &si, "get_system_info"));
			}
			break;
		case MSG_TIMER:
			if (m_BMessageRunner) {
				delete m_BMessageRunner;
				m_BMessageRunner = NULL;
			} else {
				BMessage msg(MSG_AUTOSEND);
				m_BMessageRunner = new BMessageRunner(BMessenger(this), &msg, 50000);
			}
			break;
		case MSG_AUTOSEND:
			TRACE_SIMPLE((CC_GENERAL, CR_TIMER, "This is a timer message!"));
			break;
		case MSG_ALL_CLUE_ENTRIES: {
				TRACE_SIMPLE((REPORT_INFO, "Begin sending messages"));
				/*
								TRACE_SIMPLE ((REPORT_INFO, "  dump REPORT_INFO"));
								TRACE_SIMPLE ((REPORT_WARNING, "  dump REPORT_WARNING"));
								TRACE_SIMPLE ((REPORT_ERROR, "  dump REPORT_ERROR"));

								TRACE_SIMPLE ((CC_GENERAL, CR_OK, "  dump CC_GENERAL, CR_OK"));
								TRACE_SIMPLE ((CC_GENERAL, CR_INFO, "  dump CC_GENERAL, CR_INFO"));
								TRACE_SIMPLE ((CC_GENERAL, CR_WARNING, "  dump CC_GENERAL, CR_WARNING"));
								TRACE_SIMPLE ((CC_GENERAL, CR_ERROR, "  dump CC_GENERAL, CR_ERROR"));
								TRACE_SIMPLE ((CC_GENERAL, CR_SUCCEEDED, "  dump CC_GENERAL, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_GENERAL, CR_FAILED, "  dump CC_GENERAL, CR_FAILED"));
								TRACE_SIMPLE ((CC_GENERAL, CR_ENTER, "  dump CC_GENERAL, CR_ENTER"));
								TRACE_SIMPLE ((CC_GENERAL, CR_EXIT, "  dump CC_GENERAL, CR_EXIT"));
								TRACE_SIMPLE ((CC_GENERAL, CR_TIMER, "  dump CC_GENERAL, CR_TIMER"));
								TRACE_SIMPLE ((CC_GENERAL, CR_BIRTH, "  dump CC_GENERAL, CR_BIRTH"));
								TRACE_SIMPLE ((CC_GENERAL, CR_DEATH, "  dump CC_GENERAL, CR_DEATH"));
								TRACE_SIMPLE ((CC_GENERAL, CR_OBJECT, "  dump CC_GENERAL, CR_OBJECT"));

								TRACE_SIMPLE ((CC_APPLICATION, CR_OK, "  dump CC_APPLICATION, CR_OK"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "  dump CC_APPLICATION, CR_INFO"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_WARNING, "  dump CC_APPLICATION, CR_WARNING"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_ERROR, "  dump CC_APPLICATION, CR_ERROR"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_SUCCEEDED, "  dump CC_APPLICATION, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_FAILED, "  dump CC_APPLICATION, CR_FAILED"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_ENTER, "  dump CC_APPLICATION, CR_ENTER"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_EXIT, "  dump CC_APPLICATION, CR_EXIT"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_TIMER, "  dump CC_APPLICATION, CR_TIMER"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_BIRTH, "  dump CC_APPLICATION, CR_BIRTH"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_DEATH, "  dump CC_APPLICATION, CR_DEATH"));
								TRACE_SIMPLE ((CC_APPLICATION, CR_OBJECT, "  dump CC_APPLICATION, CR_OBJECT"));

								TRACE_SIMPLE ((CC_INTERFACE, CR_OK, "  dump CC_INTERFACE, CR_OK"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_INFO, "  dump CC_INTERFACE, CR_INFO"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_WARNING, "  dump CC_INTERFACE, CR_WARNING"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_ERROR, "  dump CC_INTERFACE, CR_ERROR"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_SUCCEEDED, "  dump CC_INTERFACE, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_FAILED, "  dump CC_INTERFACE, CR_FAILED"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_ENTER, "  dump CC_INTERFACE, CR_ENTER"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_EXIT, "  dump CC_INTERFACE, CR_EXIT"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_TIMER, "  dump CC_INTERFACE, CR_TIMER"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_BIRTH, "  dump CC_INTERFACE, CR_BIRTH"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_DEATH, "  dump CC_INTERFACE, CR_DEATH"));
								TRACE_SIMPLE ((CC_INTERFACE, CR_OBJECT, "  dump CC_INTERFACE, CR_OBJECT"));

								TRACE_SIMPLE ((CC_MEDIA, CR_OK, "  dump CC_MEDIA, CR_OK"));
								TRACE_SIMPLE ((CC_MEDIA, CR_INFO, "  dump CC_MEDIA, CR_INFO"));
								TRACE_SIMPLE ((CC_MEDIA, CR_WARNING, "  dump CC_MEDIA, CR_WARNING"));
								TRACE_SIMPLE ((CC_MEDIA, CR_ERROR, "  dump CC_MEDIA, CR_ERROR"));
								TRACE_SIMPLE ((CC_MEDIA, CR_SUCCEEDED, "  dump CC_MEDIA, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_MEDIA, CR_FAILED, "  dump CC_MEDIA, CR_FAILED"));
								TRACE_SIMPLE ((CC_MEDIA, CR_ENTER, "  dump CC_MEDIA, CR_ENTER"));
								TRACE_SIMPLE ((CC_MEDIA, CR_EXIT, "  dump CC_MEDIA, CR_EXIT"));
								TRACE_SIMPLE ((CC_MEDIA, CR_TIMER, "  dump CC_MEDIA, CR_TIMER"));
								TRACE_SIMPLE ((CC_MEDIA, CR_BIRTH, "  dump CC_MEDIA, CR_BIRTH"));
								TRACE_SIMPLE ((CC_MEDIA, CR_DEATH, "  dump CC_MEDIA, CR_DEATH"));
								TRACE_SIMPLE ((CC_MEDIA, CR_OBJECT, "  dump CC_MEDIA, CR_OBJECT"));

								TRACE_SIMPLE ((CC_STORAGE, CR_OK, "  dump CC_STORAGE, CR_OK"));
								TRACE_SIMPLE ((CC_STORAGE, CR_INFO, "  dump CC_STORAGE, CR_INFO"));
								TRACE_SIMPLE ((CC_STORAGE, CR_WARNING, "  dump CC_STORAGE, CR_WARNING"));
								TRACE_SIMPLE ((CC_STORAGE, CR_ERROR, "  dump CC_STORAGE, CR_ERROR"));
								TRACE_SIMPLE ((CC_STORAGE, CR_SUCCEEDED, "  dump CC_STORAGE, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_STORAGE, CR_FAILED, "  dump CC_STORAGE, CR_FAILED"));
								TRACE_SIMPLE ((CC_STORAGE, CR_ENTER, "  dump CC_STORAGE, CR_ENTER"));
								TRACE_SIMPLE ((CC_STORAGE, CR_EXIT, "  dump CC_STORAGE, CR_EXIT"));
								TRACE_SIMPLE ((CC_STORAGE, CR_TIMER, "  dump CC_STORAGE, CR_TIMER"));
								TRACE_SIMPLE ((CC_STORAGE, CR_BIRTH, "  dump CC_STORAGE, CR_BIRTH"));
								TRACE_SIMPLE ((CC_STORAGE, CR_DEATH, "  dump CC_STORAGE, CR_DEATH"));
								TRACE_SIMPLE ((CC_STORAGE, CR_OBJECT, "  dump CC_STORAGE, CR_OBJECT"));

								TRACE_SIMPLE ((CC_SUPPORT, CR_OK, "  dump CC_SUPPORT, CR_OK"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_INFO, "  dump CC_SUPPORT, CR_INFO"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_WARNING, "  dump CC_SUPPORT, CR_WARNING"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_ERROR, "  dump CC_SUPPORT, CR_ERROR"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_SUCCEEDED, "  dump CC_SUPPORT, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_FAILED, "  dump CC_SUPPORT, CR_FAILED"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_ENTER, "  dump CC_SUPPORT, CR_ENTER"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_EXIT, "  dump CC_SUPPORT, CR_EXIT"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_TIMER, "  dump CC_SUPPORT, CR_TIMER"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_BIRTH, "  dump CC_SUPPORT, CR_BIRTH"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_DEATH, "  dump CC_SUPPORT, CR_DEATH"));
								TRACE_SIMPLE ((CC_SUPPORT, CR_OBJECT, "  dump CC_SUPPORT, CR_OBJECT"));

								TRACE_SIMPLE ((CC_NETWORK, CR_OK, "  dump CC_NETWORK, CR_OK"));
								TRACE_SIMPLE ((CC_NETWORK, CR_INFO, "  dump CC_NETWORK, CR_INFO"));
								TRACE_SIMPLE ((CC_NETWORK, CR_WARNING, "  dump CC_NETWORK, CR_WARNING"));
								TRACE_SIMPLE ((CC_NETWORK, CR_ERROR, "  dump CC_NETWORK, CR_ERROR"));
								TRACE_SIMPLE ((CC_NETWORK, CR_SUCCEEDED, "  dump CC_NETWORK, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_NETWORK, CR_FAILED, "  dump CC_NETWORK, CR_FAILED"));
								TRACE_SIMPLE ((CC_NETWORK, CR_ENTER, "  dump CC_NETWORK, CR_ENTER"));
								TRACE_SIMPLE ((CC_NETWORK, CR_EXIT, "  dump CC_NETWORK, CR_EXIT"));
								TRACE_SIMPLE ((CC_NETWORK, CR_TIMER, "  dump CC_NETWORK, CR_TIMER"));
								TRACE_SIMPLE ((CC_NETWORK, CR_BIRTH, "  dump CC_NETWORK, CR_BIRTH"));
								TRACE_SIMPLE ((CC_NETWORK, CR_DEATH, "  dump CC_NETWORK, CR_DEATH"));
								TRACE_SIMPLE ((CC_NETWORK, CR_OBJECT, "  dump CC_NETWORK, CR_OBJECT"));

								TRACE_SIMPLE ((CC_MOUSE, CR_OK, "  dump CC_MOUSE, CR_OK"));
								TRACE_SIMPLE ((CC_MOUSE, CR_INFO, "  dump CC_MOUSE, CR_INFO"));
								TRACE_SIMPLE ((CC_MOUSE, CR_WARNING, "  dump CC_MOUSE, CR_WARNING"));
								TRACE_SIMPLE ((CC_MOUSE, CR_ERROR, "  dump CC_MOUSE, CR_ERROR"));
								TRACE_SIMPLE ((CC_MOUSE, CR_SUCCEEDED, "  dump CC_MOUSE, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_MOUSE, CR_FAILED, "  dump CC_MOUSE, CR_FAILED"));
								TRACE_SIMPLE ((CC_MOUSE, CR_ENTER, "  dump CC_MOUSE, CR_ENTER"));
								TRACE_SIMPLE ((CC_MOUSE, CR_EXIT, "  dump CC_MOUSE, CR_EXIT"));
								TRACE_SIMPLE ((CC_MOUSE, CR_TIMER, "  dump CC_MOUSE, CR_TIMER"));
								TRACE_SIMPLE ((CC_MOUSE, CR_BIRTH, "  dump CC_MOUSE, CR_BIRTH"));
								TRACE_SIMPLE ((CC_MOUSE, CR_DEATH, "  dump CC_MOUSE, CR_DEATH"));
								TRACE_SIMPLE ((CC_MOUSE, CR_OBJECT, "  dump CC_MOUSE, CR_OBJECT"));

								TRACE_SIMPLE ((CC_KEYBOARD, CR_OK, "  dump CC_KEYBOARD, CR_OK"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_INFO, "  dump CC_KEYBOARD, CR_INFO"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_WARNING, "  dump CC_KEYBOARD, CR_WARNING"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_ERROR, "  dump CC_KEYBOARD, CR_ERROR"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_SUCCEEDED, "  dump CC_KEYBOARD, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_FAILED, "  dump CC_KEYBOARD, CR_FAILED"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_ENTER, "  dump CC_KEYBOARD, CR_ENTER"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_EXIT, "  dump CC_KEYBOARD, CR_EXIT"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_TIMER, "  dump CC_KEYBOARD, CR_TIMER"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_BIRTH, "  dump CC_KEYBOARD, CR_BIRTH"));
								TRACE_SIMPLE ((CC_KEYBOARD, CR_DEATH, "  dump CC_KEYBOARD, CR_DEATH"));

								TRACE_SIMPLE ((CC_PRINTING, CR_OK, "  dump CC_PRINTING, CR_OK"));
								TRACE_SIMPLE ((CC_PRINTING, CR_INFO, "  dump CC_PRINTING, CR_INFO"));
								TRACE_SIMPLE ((CC_PRINTING, CR_WARNING, "  dump CC_PRINTING, CR_WARNING"));
								TRACE_SIMPLE ((CC_PRINTING, CR_ERROR, "  dump CC_PRINTING, CR_ERROR"));
								TRACE_SIMPLE ((CC_PRINTING, CR_SUCCEEDED, "  dump CC_PRINTING, CR_SUCCEEDED"));
								TRACE_SIMPLE ((CC_PRINTING, CR_FAILED, "  dump CC_PRINTING, CR_FAILED"));
								TRACE_SIMPLE ((CC_PRINTING, CR_ENTER, "  dump CC_PRINTING, CR_ENTER"));
								TRACE_SIMPLE ((CC_PRINTING, CR_EXIT, "  dump CC_PRINTING, CR_EXIT"));
								TRACE_SIMPLE ((CC_PRINTING, CR_TIMER, "  dump CC_PRINTING, CR_TIMER"));
								TRACE_SIMPLE ((CC_PRINTING, CR_BIRTH, "  dump CC_PRINTING, CR_BIRTH"));
								TRACE_SIMPLE ((CC_PRINTING, CR_DEATH, "  dump CC_PRINTING, CR_DEATH"));
								TRACE_SIMPLE ((CC_PRINTING, CR_OBJECT, "  dump CC_PRINTING, CR_OBJECT"));
				*/
				for (int i = 0; i < 1000; i++)
					TRACE_SIMPLE((CC_GENERAL, CR_INFO, "sending message %i", i));

				TRACE_SIMPLE((REPORT_INFO, "Done sending messages"));
			}
			break;
		default:
			BView::MessageReceived(msg);
	}
}


/***************************************************************
***************************************************************/
void CView :: MouseMoved
(
	BPoint point
	,	uint32 transit
	,	const BMessage* drag
)
{
	TRACE_METHOD((CC_MOUSE, REPORT_METHOD, "point: [%0.f, %0.f], transit = %i, drag = %08x",
				  point.x, point.y, transit, drag));
	TRACE_SIMPLE((CC_MOUSE, CR_INFO, "just for fun"));
}


/***************************************************************
***************************************************************/
CTextView ::CTextView
(
	BRect frame
	,	const char* name
	,	BRect textRect
	,	uint32 resizingMode
	,	uint32 flags
)
	:	BTextView(frame, name, textRect, resizingMode, flags)
{
	TRACE_METHOD((CC_INTERFACE, REPORT_METHOD, "name = %s", name));
}


/***************************************************************
***************************************************************/
void
CTextView :: Draw
(
	BRect uR //updateRect
)
{
	TRACE_SIMPLE((CC_INTERFACE, CR_OK, "frame: l=%0.f, t=%0.f, r=%0.f, b=%0.f", uR.left, uR.top, uR.right, uR.bottom));
	BTextView::Draw(uR);
}


/***************************************************************
***************************************************************/
void
CTextView :: KeyDown
(
	const char* bytes
	,	int32 numBytes
)
{
	int32 mods(modifiers());
	TRACE_SIMPLE((CC_KEYBOARD, CR_INFO, "numBytes = %lu; modifiers=%0x", numBytes, mods));
	if (B_MENU_KEY & mods)
		TRACE_SIMPLE((CC_KEYBOARD, CR_INFO, "B_MENU_KEY was down"));

	key_info KI;
	if (B_OK == get_key_info(&KI))
		TRACE_OBJECT((CC_KEYBOARD, CR_OBJECT, &KI, "the keyboard info struct"));

	BTextView::KeyDown(bytes, numBytes);
}

