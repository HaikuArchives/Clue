//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
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


//====================================================================
int32 ToolTipWindow::m_VisCount = 0;


ToolTipWindow :: ToolTipWindow
(
	tool_tip_settings* settings
)
	:	BWindow(BRect(0, 0, 10, 10), "tool_tip", B_BORDERED_WINDOW_LOOK,
				B_FLOATING_ALL_WINDOW_FEEL, B_AVOID_FRONT | B_AVOID_FOCUS, B_ALL_WORKSPACES)
{
	// setup the tooltip view
	AddChild(fView = new ToolTipView(settings));
	// start the message loop thread
	float minw(0);
	float maxw(0);
	float minh(0);
	float maxh(0);
	GetSizeLimits(&minw, &maxw, &minh, &maxh);
	SetSizeLimits(minw, maxw, 0, maxh);
	Run();
	//Show ();
}


//--------------------------------------------------------------------
void
ToolTipWindow :: MessageReceived
(
	BMessage* msg
)
{
	switch (msg->what) {
		// forward interesting messages to the view
		case B_SOME_APP_ACTIVATED:
		case MSG_TOOL_TIP_START:
		case MSG_TOOL_TIP_STOP:
			PRINT(("Tooltip message received.\n"));
			PostMessage(msg, fView);
			break;
		default:
			BWindow::MessageReceived(msg);
	}
}


void
ToolTipWindow :: Show
(
	void
)
{
	BWindow::Show();
	m_fEffect.pWnd = static_cast<BWindow*>(this);
	m_fEffect.quit = false;
	// start window effect thread
	resume_thread(m_EffectThreadID = spawn_thread((status_t (*)(void*)) EffectThread,
				  "ToolTip Effect", B_DISPLAY_PRIORITY, &m_fEffect));
}


void
ToolTipWindow :: Hide
(
	void
)
{
	status_t retval(B_OK);

	m_fEffect.quit = true;
	wait_for_thread(m_EffectThreadID, &retval);
	BWindow::Hide();
}


void
ToolTipWindow :: SetDesiredHeight
(
	int32 inHeight
)
{
	m_fEffect.desiredheight = inHeight;
}


//--------------------------------------------------------------------
void
ToolTipWindow :: GetSettings
(
	tool_tip_settings* settings
)
{
	fView->GetSettings(settings);
}


//--------------------------------------------------------------------
void
ToolTipWindow :: SetSettings
(
	tool_tip_settings* settings
)
{
	fView->SetSettings(settings);
}


//--------------------------------------------------------------------
status_t
ToolTipWindow :: EffectThread
(
	Effect* pEffect
)
{
//FIX THIS LATER
//	GOSSIPMETHOD ((GSP_METHOD_STATIC(EffectThread,CToolTipWindow)));
	bool keeprunning(true);

	while (!pEffect->quit && keeprunning) {
		if (pEffect->pWnd->LockWithTimeout(0) == B_NO_ERROR) {
			BRect rcWnd(pEffect->pWnd->Frame());
			if (rcWnd.Height() >= pEffect->desiredheight) {
				keeprunning = false;
				pEffect->pWnd->Unlock();
				continue;
			}
			pEffect->pWnd->ResizeTo(rcWnd.Width(), rcWnd.Height() + 2);
			pEffect->pWnd->Unlock();
		}
		snooze(10000);
	}
	return B_NO_ERROR;
}


