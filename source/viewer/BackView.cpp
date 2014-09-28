/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
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

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _HANDLER_H
#include <Handler.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif

#ifndef _LIST_VIEW_H
#include <ListView.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
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

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

#ifndef _PRINTSESSION_H
#include <PrintJob.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCROLL_BAR_H
#include <ScrollBar.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef ANIMATEDVIEW_H
#include "AnimatedView.h"
#endif

#ifndef BACKVIEW_H
#include "BackView.h"
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef _CLUEITEM_H_
#include "ClueItem.h"
#endif

#ifndef SPLITTERVIEW_H
#include "SplitterView.h"
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif

#ifndef TEAMTAB_H
#include "TeamTab.h"
#endif

#ifndef _FINGERPRINTZOOMWND_H
#include "FingerprintZoomWnd.h"
#endif

#ifndef PROPERTYWINDOW_H
#include "TeamPropertyWindow.h"
#endif

#ifndef _BETTER_SCROLL_VIEW_H_
#include "BetterScrollView.h"
#endif

#ifndef _FINGERPRINTCLV_H_
#include "FingerprintCLV.h"
#endif

#ifndef _TEAMCLV_H_
#include "TeamCLV.h"
#endif

#ifndef _CLUE_TAB_VIEW_H
#include "ClueTabView.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

#ifndef PRINTWINDOW_H
#include "PrintWindow.h"
#endif

#ifndef _TEST_WINDOW_H
#include "TestWindow.h"
#endif

/***************************************************************
***************************************************************/
class DummyView : public BView
{
	public:
		DummyView (BRect frame, char * name, ColumnListView * pCLV)
		: BView (frame, name, B_FOLLOW_ALL, 0)
		,	m_pCLV (pCLV)
		{
			SetViewColor (B_TRANSPARENT_COLOR);
		}
		void AllAttached (void)
		{
			BRect rc (Parent()->Bounds ());
			ResizeTo (rc.Width (), rc.Height ());
			m_pCLV->SetTarget (Parent ());
			Show ();
		}
	private:
		ColumnListView * m_pCLV;
};

/***************************************************************
const declarations
***************************************************************/


/***************************************************************
application global declarations
***************************************************************/
BList				g_MainDataList;
BList				g_SecondaryDataList;
BList *				g_ReporterList (NULL);
volatile bool		g_UsingMainList (true);
volatile sem_id		g_semaphore;
const char *		g_PortName ("CluePort3");
extern BMessage g_Settings;
const uint32 MSG_CHECK_RUNNING_TEAMS = 'chrt';

/***************************************************************
file global declarations
***************************************************************/

/***************************************************************
This version is used by the Live! BWindow version of Clue
***************************************************************/
BackView :: BackView
	(
	BRect rcFrame
	)
:	BView (rcFrame, "BackView", B_FOLLOW_ALL, B_WILL_DRAW | B_FRAME_EVENTS)
,	m_mfView (NULL)
,	m_tvTabs (NULL)
,	m_lvTeams (NULL)
,	m_TIcached (NULL)
,	m_pSplitterView (NULL)
,	m_PortThreadID (0)
,	m_runner (NULL)
,	m_checkrosterrunner (NULL)
,	m_ColumnListView (NULL)
,	m_teamslabel (NULL)
,	m_BSV (NULL)
,	m_PrintSettings (NULL)
,	m_PrintJob (NULL)
,	m_maxLR (0.0, 0.0)
,	m_SplitPercentage (0.0)
,	m_splitting (false)
,	m_IsLive (true)
{
	PRINT (("CBackView :: CBackView (BRect)\n"));
	g_semaphore = create_sem (1, "ClueSemaphore");
	InitCommon ();
}


/*************************************************************************
*************************************************************************/
BackView :: BackView
	(
	BRect rcFrame
,	BMessage * archive
	)
:	BView (rcFrame, "CBackView", B_FOLLOW_ALL, B_WILL_DRAW | B_FRAME_EVENTS)
,	m_mfView (NULL)
,	m_tvTabs (NULL)
,	m_lvTeams (NULL)
,	m_TIcached (NULL)
,	m_pSplitterView (NULL)
,	m_PortThreadID (0)
,	m_runner (NULL)
,	m_checkrosterrunner (NULL)
,	m_ColumnListView (NULL)
,	m_teamslabel (NULL)
,	m_BSV (NULL)
,	m_PrintSettings (NULL)
,	m_PrintJob (NULL)
,	m_maxLR (0.0, 0.0)
,	m_SplitPercentage (0.0)
,	m_splitting (false)
,	m_IsLive (false)
{
	PRINT (("CBackView :: CBackView (BRect, BMessage *)\n"));
	InitCommon ();

	PRINT(("____________________________________\n"));
	int32 i (0);
	BMessage teamarchive;

	int32 teamarcfmt (0);

	archive->FindInt32 ("ARCHIVE_FORMAT", (int32 *) &teamarcfmt);  //this is the internal format of the Clue TEAMS!

	PRINT ((" begin extracting Teams...\n"));
	while (B_OK == archive->FindMessage ("Team Items", i++, &teamarchive))
	{
		CreateNewTeamItem (&teamarchive, teamarcfmt);
	}
}


/*************************************************************************
destructor
*************************************************************************/
BackView :: ~BackView
	(
	void
	)
{
	PRINT (("\n\nBackView::~BackView\n"));
	if (m_checkrosterrunner)
	{
	}

	BMessage tmpmsg ('temp');
	BMessage msgData ('pref');
	msgData.AddFloat ("Splitter", m_pSplitterView->Frame().left);

	if (B_OK == g_Settings.FindMessage ("VIEW:BackView", &tmpmsg))
	{
		g_Settings.ReplaceMessage ("VIEW:BackView", &msgData);
	}
	else
	{
		g_Settings.AddMessage ("VIEW:BackView", &msgData);
	}

	Listen (false);

	int32			index (m_ColumnListView->CountItems ());
	TeamItem *		ti (NULL);

	PRINT (("  there were %i TeamItems in the list\n", index));
	while (index--)
	{
		ti = (TeamItem *) m_ColumnListView->ItemAt (index);
		if (ti)
		{
			PRINT (("    Release the TeamItem\n"));
			ti->Release ();
		}
		else
		{
			PRINT (("   the TeamItem was invalid!\n"));
		}
	}
	
	if (m_PrintSettings)
	{
		
		delete m_PrintSettings;
		m_PrintSettings = NULL;
	}
}


/*************************************************************************
*************************************************************************/
void
BackView :: InitCommon
	(
	void
	)
{
	PRINT (("CBackView :: InitCommon\n"));

	float fSplitterPos (160.0f);
	BMessage msgData;

	if (B_OK == g_Settings.FindMessage ("VIEW:BackView", &msgData))
	{
		msgData.FindFloat ("Splitter", &fSplitterPos);
	}

	BRect rc (Bounds ());
	if (fSplitterPos > rc.right)
	{
		fSplitterPos = rc.right - 5.0f;
	}

	SetViewColor (CLR_BACKGROUND);

	m_pSplitterView = new SplitterView (BRect (fSplitterPos, 0.0, fSplitterPos + 4.0f, Bounds().bottom), "Splitter", B_FOLLOW_NONE, 0);
//	m_pSplitterView = new SplitterView (BRect (fSplitterPos, 0.0, fSplitterPos + 4.0f, Bounds().bottom - 5.0f), "Splitter", B_FOLLOW_NONE, 0);
	AddChild (m_pSplitterView);
	rc = m_pSplitterView->Frame ();

	m_SplitPercentage = rc.left / Bounds().right;

	BFont font;
	GetFont (&font);

	rc = Bounds ();
	rc.left = 7.0f;
	rc.top = 28.0f;
	rc.right = 100.0f;//m_pSplitterView->Frame().left - 5.0 - B_V_SCROLL_BAR_WIDTH;
	rc.bottom = rc.bottom - B_H_SCROLL_BAR_HEIGHT - 7.0f;
	m_ColumnListView = new TeamCLV (rc, CLR_BACKGROUND, &m_BSV, "TeamList", B_FOLLOW_LEFT | B_FOLLOW_TOP_BOTTOM,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_SINGLE_SELECTION_LIST, true, true, true, B_FANCY_BORDER);
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_COLUMN_VISIBLE, 20.0));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_COLUMN_ICON, 20.0));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_COLUMN_TEAM_ID, font.StringWidth ("000000") + 6.0, CLV_ALIGN_RIGHT));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_COLUMN_APP_NAME, font.StringWidth ("Some App") + 6.0));
	m_ColumnListView->AddColumn (new CLVColumn (STR_TEAM_COLUMN_QUEUE_LENGTH, font.StringWidth ("000000") + 6.0, CLV_ALIGN_RIGHT));
	m_ColumnListView->SetInvocationMessage (new BMessage (MSG_LIST_ITEM_INVOCATED));
	m_ColumnListView->SetSelectionMessage (new BMessage (MSG_LIST_ITEM_SELECTED));

	m_ColumnListView->SetViewColor (CLR_LIST_BACKGROUND);
	AddChild (m_BSV);

	BStringView * pSV ((BStringView *) m_ColumnListView->Parent()->FindView ("ListCountView"));
	if (pSV)
	{
		BString s;
		s << m_ColumnListView->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}

	rc = Bounds ();
	rc.InsetBy (5.0f, 5.0f);
	rc.top = 4.0f;
	rc.left = m_pSplitterView->Frame().right + 2.0f;
	m_tvTabs = new ClueTabView (rc, "tab_view");
	AddChild (m_tvTabs);

	m_teamslabel = new BStringView (BRect (10.0f, 40.0f, 100.0f, 45.0f), "svTeams:", STR_LABEL_TEAMS);
	AddChild (m_teamslabel);
	m_teamslabel->ResizeToPreferred ();
	m_teamslabel->MoveTo (10.0f, 26.0f - m_teamslabel->Bounds().Height() - 4.0f);
	m_teamslabel->ResizeTo (m_pSplitterView->Frame().left - 11.0f, m_teamslabel->Bounds().bottom);
}


/***************************************************************
***************************************************************/
void
BackView :: MessageReceived
	(
	BMessage * msg
	)
{
	//put in most-frequent to less-frequent order for that little extra speed we all want!
	switch (msg->what)
	{
		case MSG_PROCESS_CLUES:  //put this one first, as it's the most frequent
			ProcessIncomingData ();
			break;
		case MSG_CHECK_RUNNING_TEAMS:
			TeamsInRoster ();
			break;
		case 'acti':
			Activate ();
			break;
		case MSG_TEAM_DELETE:
			DeleteTeam ();
			break;
		case MSG_TEAM_PROPERTIES:
			TeamProperties ();
			break;
		case MSG_UPDATE_TEAM_PROPERTIES:
			UpdateTeamProperties (msg);
			break;
		case MSG_SPLITTER_START:
			SplitterStart ();
			break;
		case MSG_LIST_ITEM_INVOCATED:
			TeamInvocated (msg);
			break;
		case MSG_LIST_CLUE_ITEM_INVOCATED:
			{
			ColumnListView * pCLV (NULL);
			msg->FindPointer ("CIL", (void **) &pCLV);
			if (pCLV)
			{
				int32 selected (0);
				int32 i (0);
				int32 cnt (0);
				ClueItem * pCI (NULL);

				while ( (selected = pCLV->CurrentSelection (i++)) >= 0)
				{
					if (++cnt > 50)
					{
						BAlert* pAlert (new BAlert ("Clue", "Only opened the first 50 items.", STR_OK));
						pAlert->Go (NULL);
						break; //stop opening new windows
					}
					else
					{
						pCI = (ClueItem *) pCLV->ItemAt (selected);
						new FingerprintZoomWnd (pCI);
					}
				}
			}
			}
			break;
		case MSG_LIST_CLUE_ITEM_SELECTED:
			{
			PRINT (("msg = MSG_LIST_CLUE_ITEM_SELECTED\n"));
			BTextView * pText (NULL);
			msg->FindPointer ("DetailView", (void **) &pText);
			if (pText)
			{
				ColumnListView * pCLV (NULL);
				msg->FindPointer ("CIL", (void **) &pCLV);
				if (pCLV)
				{
					PRINT (("pCLV = %08x\n", pCLV));
					int32 index (pCLV->CurrentSelection (0));
					if (index >= 0)
					{
						ClueItem * ci ((ClueItem *)pCLV->ItemAt (index));
						if (ci)
						{
							ci->DisplayDetail (pText);
							BRect trect (0,0,0,0); 
							int n = pText->CountLines ();
							float filewidth (1.0f);
							float t (0.0f);

							for (int i (0); i < n; i++)
							{
								t = pText->LineWidth (i);
								if (t > filewidth)
								{
									filewidth = t;
								}
							}

							trect.right = filewidth;
							pText->SetTextRect (trect);
						}
						else
						{
							PRINT (("ci wasn't valid\n"));
							pText->SetText (NULL);
						}
					}
					else
					{
						pText->SetText (NULL);
					}
				}
				else
				{
					PRINT (("pCLV wasn't valid\n"));
					pText->SetText (NULL);
				}
			}
			else
			{
				PRINT (("pText wasn't valid\n"));
			}
			}
			break;
		case MSG_CLEAR_CLUE_LIST:
			ClearClueList (msg);
			break;
		case B_OBSERVER_NOTICE_CHANGE:
			{
			uint32 change (0);
			msg->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32 *) &change);
			switch (change)
			{
			case MSG_SETTINGS_CHANGED:
				{
					SetViewColor (CLR_BACKGROUND);
					SetLowColor (CLR_BACKGROUND);
					Invalidate ();
					m_teamslabel->SetViewColor (CLR_BACKGROUND);
					m_teamslabel->SetLowColor (CLR_BACKGROUND);
					m_teamslabel->Invalidate ();
					m_ColumnListView->SetViewColor (CLR_LIST_BACKGROUND);
					m_ColumnListView->SetLowColor (CLR_LIST_BACKGROUND);
					m_ColumnListView->Invalidate ();

					int32			index (m_ColumnListView->CountItems ());
					TeamItem *		ti (NULL);

					while (index--)
					{
						ti = (TeamItem *) m_ColumnListView->ItemAt (index);
						ti->m_view->SetViewColor (CLR_FOREGROUND);
						ti->m_view->Invalidate ();
						ti->m_CLV->SetViewColor (CLR_LIST_BACKGROUND);
						ti->m_CLV->Invalidate ();

						BView * pview (m_ColumnListView->Parent()->FindView ("BSCROLLVIEWCORNER"));
						if (pview)
						{
							pview->SetViewColor (CLR_BACKGROUND);
							pview->Invalidate ();
						}

						pview = ti->m_view->FindView ("BSCROLLVIEWCORNER");
						if (pview)
						{
							pview->SetViewColor (CLR_FOREGROUND);
							pview->Invalidate ();
						}

						pview = ti->m_view->FindView ("TVCorner");
						if (pview)
						{
							pview->SetViewColor (CLR_FOREGROUND);
							pview->Invalidate ();
						}
					}

					(m_tvTabs->ChildAt (0))->SetViewColor (CLR_FOREGROUND);
					(m_tvTabs->ChildAt (0))->SetLowColor (CLR_FOREGROUND);
					(m_tvTabs->ChildAt (0))->Invalidate ();
				}
				break;
			}
			}
			break;
		case 'prnt':
		{
//		PrintWindow * pPW (PrintWindow::Create ());
//		if (pPW)
//		{
//			BMessenger messenger (pPW);
//			BMessage message ('data');
//			messenger.SendMessage (&message);
//		}
			int32 index (m_ColumnListView->CurrentSelection (0));
			if (index >= 0)
			{
				//TestWindow * pTW (new TestWindow (Window (), this, m_PrintSettings));
				new TestWindow (Window (), this, m_PrintSettings);
			}
			else
			{
				BAlert* pAlert (new BAlert("Clue", "No Team selected to print.", "OK"));
				pAlert->Go (NULL);
			}
		}
			//OnPrint ();
			break;
		case 'dopr':
			if (B_OK == msg->FindPointer ("BPrintJob", (void **) &m_PrintJob))
			{
				//if (B_OK == msg->FindMessage ("Settings", m_PrintSettings))
				//{
					OnPrint ();
				//}
			}
			break;
		default:
			BView::MessageReceived (msg);
	}
}


/***************************************************************
***************************************************************/
void
BackView :: AllAttached
	(
	void
	)
{
	(m_tvTabs->ChildAt (0))->SetViewColor (CLR_FOREGROUND);

	//(m_tvTabs->ChildAt (0))->SetViewBitmap (g_Live);
	//m_tvTabs->SetViewColor (CLR_FASHIONABLE);
	m_ColumnListView->SetTarget (this);
	BStringView * sv ((BStringView *) FindView ("svTeams:"));
	sv->SetViewColor (CLR_BACKGROUND);
	//sv->SetViewColor (0,255,0,255);
	sv->SetLowColor (CLR_BACKGROUND);
	m_ColumnListView->MakeFocus ();
	BWindow * pwnd (Window ());
	if (pwnd)
	{
		((BHandler *)pwnd)->StartWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
//		if (B_OK != StartWatching ((BHandler *) pwnd, MSG_SETTINGS_CHANGED))
//		{
//			BAlert *myAlert = new BAlert("CBackView", "CBackView : AllAttached", STR_OK);
//			myAlert->Go (NULL);
//		}
	}

	m_BSV->ResizeTo (m_pSplitterView->Frame().left - 8.0, m_BSV->Bounds().bottom);

	if (m_IsLive)
	{
		BMessage msg (MSG_CHECK_RUNNING_TEAMS);
		m_checkrosterrunner = reinterpret_cast<BMessageRunner *> (new BMessageRunner (BMessenger (this), &msg, 500000));
#ifdef DEBUG
		if (m_checkrosterrunner->InitCheck ())
			PRINT (("rosterrunner is ok\n"));
		else
			PRINT (("rosterrunner had an error\n"));
#endif
	}
}


/***************************************************************
***************************************************************/

void
BackView :: FrameResized
	(
	float width
,	float height)
{
	BRect rc (m_pSplitterView->Frame ());
	BRect bnds (Bounds ());
	float x (bnds.right - rc.Width ());

	if (rc.left > x)
	{
		m_pSplitterView->MoveTo (x, 0.0);
		m_BSV->ResizeTo (x - 8.0, rc.bottom - 31.0);//rcBSV.bottom);
		m_teamslabel->ResizeTo (x - 14.0f, m_teamslabel->Bounds().bottom);
		m_tvTabs->MoveTo (x + 6.0, 4.0);
		m_tvTabs->ResizeTo (bnds.right - x - 11.0, rc.bottom - 9.0f);//rcTab.bottom);
	}
}



/*************************************************************************
*************************************************************************/
void
BackView :: MouseMoved (BPoint point, uint32 transit, const BMessage * message)
{
	PRINT (("BackView :: MouseMoved...\n"));
	BRect bnds (Bounds ());
	if (m_splitting)
	{
		PRINT ((" splitting\n"));
		point.x = min_c(m_maxLR.y, max_c(point.x, m_maxLR.x));
		m_BSV->ResizeTo (point.x - 11.0, m_cachedRects[0].bottom);
		m_teamslabel->ResizeTo (point.x - 16.0f, m_teamslabel->Bounds().bottom);
		m_pSplitterView->MoveTo (point.x - 3.0, 0.0);
		m_tvTabs->MoveTo (point.x + 3.0, 4.0);
		m_tvTabs->ResizeTo (bnds.right - point.x - 8.0, m_cachedRects[1].bottom);
		m_SplitPercentage = point.x / Bounds().right;
		PRINT (("Percentage = %f\n", m_SplitPercentage));
	}
	PRINT (("...MouseMoved done\n"));
}


/*************************************************************************
*************************************************************************/
void
BackView :: MouseUp
	(
	BPoint point
	)
{
	PRINT (("BackView :: MouseUp\n"));
	if (m_splitting)
	{
		SetEventMask (0, 0);
		m_splitting = false;
		BMessage msg (MSG_SPLITTER_STOP);
		m_pSplitterView->MessageReceived (&msg);
		m_SplitPercentage = point.x / Bounds().right;
	}
}


/*************************************************************************
*************************************************************************/
void
BackView :: ResizeBy
	(
	float horizontal
,	float vertical
	)
{
	BView::ResizeBy (horizontal, vertical);
	AdjustViews ();
}


/*************************************************************************
*************************************************************************/
void
BackView :: ResizeTo
	(
	float width
,	float height
	)
{
	BView::ResizeTo (width, height);
	AdjustViews ();
}


/*************************************************************************
*************************************************************************/
void
BackView :: AdjustViews
	(
	void
	)
{
	PRINT ((" AdjustViews\n"));

	BRect bnds (Bounds ());
	BRect rc (m_pSplitterView->Frame ());

//	if (rc.left > bnds.right)
//	{
		m_pSplitterView->MoveTo (bnds.right - rc.Width (), 0.0);
//	}
//	point.x = min_c(m_maxLR.y, max_c(point.x, m_maxLR.x));
//	m_BSV->ResizeTo (point.x - 11.0, m_cachedRects[0].bottom);
//	m_teamslabel->ResizeTo (point.x - 14.0f, m_teamslabel->Bounds().bottom);
//	m_pSplitterView->MoveTo (point.x - 3.0, 0.0);
//	m_tvTabs->MoveTo (point.x + 3.0, 4.0);
//	m_tvTabs->ResizeTo (bnds.right - point.x - 8.0, m_cachedRects[1].bottom);
//	m_SplitPercentage = point.x / Bounds().right;
}

/*************************************************************************
*************************************************************************/
void
BackView :: DeleteTeam
	(
	void
	)
{

	PRINT (("MSG_TEAM_DELETE\n"));
	int32 index (m_ColumnListView->CurrentSelection ());
	if (0 <= index)
	{
		TeamItem * ti ((TeamItem *) m_ColumnListView->RemoveItem (index));
		ASSERT (ti);
		if (ti == m_TIcached)
		{
			m_TIcached = NULL;  //must set back to NULL for ProcessIncomingData!
		}
		if (ti->m_TabVisible)
		{
			TeamTab * tab (NULL);
			int32 i (-1);
	
			do
			{
				tab = static_cast<TeamTab *>(m_tvTabs->TabAt (++i));
			}
			while (tab && (tab != ti->m_tab));
	
			if (tab)
			{
				tab = static_cast<TeamTab *>(m_tvTabs->RemoveTab (i));
				ti->m_TabVisible = false;
#ifdef DEBUG
				if (ti->m_view->RemoveSelf ())
				{
					PRINT (("RemoveSelf succeeded\n"));
				}
				else
				{
					PRINT (("RemoveSelf FAILED.\n"));
				}
#else
				ti->m_view->RemoveSelf ();
#endif
				delete tab;
			}
		}
		ti->Release ();
		//delete ti;
	
		//update count view
		BStringView * pSV ((BStringView *) m_ColumnListView->Parent()->FindView ("ListCountView"));
		if (pSV)
		{
			BString s;
			s << m_ColumnListView->CountItems () << STR_ITEMS;
			pSV->SetText (s.String ());
		}
	}
}


/*************************************************************************
*************************************************************************/
void
BackView :: UpdateTeamProperties
	(
	BMessage * msg
	)
{
	PRINT (("UpdateTeamProperties\n"));
	int32 index (m_ColumnListView->CurrentSelection ());
	TeamItem * ti ((TeamItem *) m_ColumnListView->ItemAt (index));
	PRINT (("queuelen was %i\n", ti->m_QueueLength));
	int32 newval (0);
	status_t rv (msg->FindInt32 ("QueueLength", (int32 *) &newval));
	if (B_OK != rv)
	{
		PRINT (("Couldn't find QueueLength in message!\n"));
		return;
	}
	int32 oldval (ti->m_QueueLength);
	ti->m_QueueLength = newval;
	if (ti->m_QueueLength < oldval)
	{
		ti->AdjustQueue ();
	}
	PRINT (("queuelen now %i\n", ti->m_QueueLength));
	char * pmask (NULL);
	rv = msg->FindPointer ("m_CategoryMask", (void **) &pmask);
	if (rv != B_OK)
	{
		PRINT (("couldn't find Mask in message!\n"));
		return;
	}
	//oldval = ti->m_ViewMask;
	memcpy (ti->m_CategoryMask, pmask, 10);
	delete [] pmask; //delete here as memory was allocated in CTeamPropertyView
	//PRINT (("queuelen now %0X\n", ti->m_ViewMask));
	//if (ti->m_ViewMask != oldval) //if hasn't changed, no reason to refresh list
	//{
		ti->RefreshList ();
	//}
	m_ColumnListView->InvalidateItem (index);
/*
	PRINT (("UpdateTeamProperties\n"));
	int32 index (m_ColumnListView->CurrentSelection ());
	TeamItem * ti ((TeamItem *) m_ColumnListView->ItemAt (index));
	PRINT (("queuelen was %i\n", ti->m_QueueLength));
	TeamItem * msgTI (NULL);
	//NOTE: we are now responsible for deletion of this TeamItem
	//when we're done with it
	status_t rv (msg->FindPointer ("TeamItem", (void **) &msgTI));
	if (B_OK != rv)
	{
		PRINT (("Couldn't find the TeamItem in message.\n"));
		return;
	}
	int32 oldval (ti->m_QueueLength);
	ti->m_QueueLength = msgTI->m_QueueLength;
	if (ti->m_QueueLength < oldval)
	{
		ti->AdjustQueue ();
	}
	PRINT (("queuelen now %i\n", ti->m_QueueLength));
	memcpy (ti->m_CategoryMask, msgTI->m_CategoryMask, 10 * sizeof(uint32));
	delete msgTI;
	ti->RefreshList ();
	m_ColumnListView->InvalidateItem (index);*/
}


/*************************************************************************
*************************************************************************/
void
BackView :: TeamInvocated
	(
	BMessage * msg
	)
{
	PRINT (("TeamInvocated\n"));
	int32 index (-1);
	status_t rv (msg->FindInt32 ("index", &index));
	if (B_OK != rv)
	{
		PRINT (("failed to find index\n"));
		return;
	}

	if (0 > index)
	{
		PRINT ((" invalid index\n"));
		return;  //invalid index
	}

	TeamItem * ti ((TeamItem *) m_ColumnListView->ItemAt (index));
	ti->m_TabVisible = !ti->m_TabVisible;

	Window()->DisableUpdates ();

	m_ColumnListView->InvalidateItem (index);
	TeamTab * tab (NULL);

	if (ti->m_TabVisible)
	{
		PRINT (("now visible\n"));
		tab = new TeamTab (ti->m_bitmap);
		ti->m_tab = tab;
		char tabname[30];
		sprintf (tabname, STR_CLUE_TAB_TITLE, ti->m_TeamID);
		tab->SetLabel (tabname);
		PRINT (("AddTab\n"));
		DummyView * tmpview (new DummyView (ti->m_view->Bounds (), tabname, ti->m_CLV));
#ifdef DEBUG
		ti->m_view->Bounds ().PrintToStream ();
#endif
		
		tmpview->AddChild (ti->m_view);
		PRINT (("Selection = %li\n", m_tvTabs->Selection ()));
		tmpview->Hide ();
		m_tvTabs->AddTab (tmpview, tab);
		m_tvTabs->Select (index);
	}
	else
	{
		PRINT (("now NOT visible!\n"));
		int32 i (-1);
		do
		{
			tab = static_cast<TeamTab *>(m_tvTabs->TabAt (++i));
		}
		while (tab && (tab != ti->m_tab));

		if (tab)
		{
			tab->View()->Hide ();
			tab->View()->ResizeTo (100.0f, 200.0f);
			tab = static_cast<TeamTab *>(m_tvTabs->RemoveTab (i));
#ifdef DEBUG
//			ti->m_view->ResizeTo (90.0f, 190.0f);
//			ti->m_view->ResizeTo (400.0f, 400.0f);
			if (ti->m_view->RemoveSelf ())
			{
				PRINT (("RemoveSelf succeeded\n"));
			}
			else
			{
				PRINT (("RemoveSelf FAILED.\n"));
			}
#else
//			ti->m_view->ResizeTo (90.0f, 190.0f);
			ti->m_view->RemoveSelf ();
#endif
			delete tab;
		}
	}

	Window()->EnableUpdates ();
}


/*************************************************************************
*************************************************************************/
void
BackView :: SplitterStart
	(
	void
	)
{
	PRINT (("SplitterStart\n"));
	m_cachedRects[0] = m_BSV->Bounds ();
	m_cachedRects[1] = m_tvTabs->Bounds ();
	BRect rc (Bounds ());
//	m_maxLR.x = rc.left + 105;
	m_maxLR.x = 3.0f;
	m_maxLR.y = rc.right - m_pSplitterView->Bounds().Width () + 3.0f;//50;
	m_splitting = true;
	SetEventMask (B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
}


/*************************************************************************
*************************************************************************/
void
BackView :: TeamProperties
	(
	void
	)
{
	PRINT (("TeamProperties\n"));
	new TeamPropertyWindow (Window (), this, (TeamItem *) m_ColumnListView->ItemAt (m_ColumnListView->CurrentSelection ()));
}


/*************************************************************************
*************************************************************************/
void
BackView :: ClearClueList
	(
	BMessage * msg
	)
{
	PRINT (("ClearClueList\n"));
	TeamItem * pTI ((TeamItem *) m_ColumnListView->ItemAt (m_ColumnListView->CurrentSelection ()));
	pTI->ClearList ();
	//update count view
	BStringView * pSV ((BStringView *) pTI->m_CLV->Parent()->FindView ("ListCountView"));
	if (pSV)
	{
		BString s;
		s << pTI->m_CLV->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}
}


/*************************************************************************
*************************************************************************/
void
BackView :: Export
	(
	BFile * file
	)
{
	PRINT (("CBackView :: Export\n"));
	BMessage archive;

	TeamItem * ti (NULL);
	int32 listcount (m_ColumnListView->CountItems ());
	int32 index (0);

	while (index < listcount)
	{
		PRINT ((" call ti-Archive\n"));
		ti = (TeamItem *) m_ColumnListView->ItemAt (index++);
		BMessage teamarchive;
		ti->Archive (&teamarchive);
		archive.AddInt32 ("ARCHIVE_FORMAT", TeamItem::ARCHIVE_FORMAT);  //this is the internal format of the Clue TEAMS!
		archive.AddMessage ("Team Items", &teamarchive);
	}

	PRINT ((" call mainarchive.Flatten (file)\n"));
	archive.Flatten (file);
}


/*************************************************************************
	PREREQUISITS: view should be attached before calling
*************************************************************************/
void
BackView :: Listen
	(
	bool listen
	)
{
	int32 Reporter (void * data);	//external function
	PRINT (("%s\n", listen ? "Start Listening" : "Stop listening"));

	if (listen)
	{
		g_ReporterList = &g_MainDataList;
		g_UsingMainList = true;
		if (!m_PortThreadID) //can't have already created a thread!
		{
			m_PortThreadID = spawn_thread (Reporter, "Reporter", B_URGENT_DISPLAY_PRIORITY, NULL); 
			resume_thread (m_PortThreadID);
		}
#ifdef DEBUG
		else
		{
			PRINT (("   ERROR: Thread was already running!\n"));
		}
#endif

		if (!m_runner)
		{
			BMessage msg (MSG_PROCESS_CLUES);
			m_runner = reinterpret_cast<BMessageRunner *> (new BMessageRunner (BMessenger (this), &msg, 100000));
			if (m_runner && (B_OK == m_runner->InitCheck ()))
				PRINT (("m_runner was successfully created!\n"));
			else
				PRINT (("ERROR: couldn't create m_runner object\n"));
		}
#ifdef DEBUG
		else
		{
			PRINT (("   ERROR: m_runner was already valid!\n"));
		}
#endif
	}
	else
	{
		if (m_PortThreadID) //thread has to exist
		{
			port_id PortID (find_port (g_PortName));
			if (B_NAME_NOT_FOUND != PortID)
			{
				write_port_etc (PortID, MSG_QUIT_PORT_THREAD, NULL, 0, B_TIMEOUT, 1);
			}
			status_t thread_rval (0);
			wait_for_thread (m_PortThreadID, &thread_rval);
			m_PortThreadID = 0;
		}

		if (m_runner)
		{
			delete m_runner;
			m_runner = NULL;
		}
		
		//clear out anything left in the primary and secondary BLists
		ProcessIncomingData ();
		ProcessIncomingData ();
	}
}


/***************************************************************
***************************************************************/
void
BackView :: ProcessIncomingData
	(
	void
	)
{
	//PRINT (("ProcessIncomingData\n"));

	if (B_NO_ERROR != acquire_sem (g_semaphore))
	{
		PRINT (("    ERROR: couldn't acquire the semaphore!\n"));
		return;
	}
	//switch which BList to use for new messages as we'll empty the other one
	g_UsingMainList = !g_UsingMainList;
	g_ReporterList = g_UsingMainList ? &g_MainDataList : &g_SecondaryDataList;
	release_sem (g_semaphore);

	//if the port thread is using the MainDataList now, we should empty
	//the SecondaryDataList so it's empty the next time around
	BList * const pCurrentDataList (g_UsingMainList ? &g_SecondaryDataList : &g_MainDataList);
	
	int32 countitems (pCurrentDataList->CountItems ());
	if (!countitems) //countitems was zero exit function
	{
		return;  //no need to continue!
	}

	PRINT (("if we have a runner, disable temporarily\n"));
	if (m_runner)
	{
		m_runner->SetInterval (5000000);
	}

	PRINT (("stop animation\n"));
	AnimatedView * pAV ((AnimatedView *) Window()->FindView ("Animate Events"));
	if (pAV)
	{
		pAV->Pause (true);
	}

	FingerPrint * ptrFP (NULL);
	FingerPrint FPData;
	ClueItem * ci (NULL);
	ssize_t msgsize (0);
	BMessage msg;
	char * pflatmsg (NULL);
	status_t rc (B_ERROR);

//	PRINT (("    INFO:  Find cached TeamItem!\n"));
	// assuming the vast majority of entries are from the same Team,
	// we'll cache the CTeamItem so we don't have to look it up
	// in FindTeamItem every time.  For several hundred messages,
	// I would think this would result in quite a bit of savings
	if (m_TIcached == NULL)
	{
		PRINT (("no cached TI\n"));
//		fp = reinterpret_cast<FingerPrint *> (pCurrentDataList->ItemAt (static_cast<int32> (0)));
		pflatmsg = (char *) pCurrentDataList->ItemAt (static_cast<int32> (0));
		if (pflatmsg)
		{
			PRINT (("pflatmsg was not NULL: %x\n", pflatmsg));

			if (msg.Unflatten ((const char *) pflatmsg) != B_OK)
			{
				PRINT (("call debugger, unflatten failed\n"));
				debugger ("msg.Unflatten failed\n");
			}
			//DO NOT DELETE pflatmsg!!!
#if DEBUG
			PRINT (("msg.unflatten worked, print contents:\n"));
			msg.PrintToStream ();
#endif
			msgsize = 0;
			if (msg.FindData ("P", B_RAW_TYPE, (const void **) &ptrFP, &msgsize) != B_OK)
			{
				PRINT (("call debugger, FindData failed\n"));
				debugger ("msg.FindData failed\n");
			}
			if (ptrFP)
			{
				PRINT (("memcpy data to FP\n"));
#if DEBUG
				if (sizeof(FingerPrint) != msgsize)
				{
					PRINT (("msgsize and FP size don't match!!!\n"));
				}
#endif
				PRINT (("ptrFP=%x, FPData=%x\n", ptrFP, &FPData));
				memcpy (&FPData, ptrFP, sizeof(FingerPrint));
			}
			else
			{
				PRINT (("call debugger as data was invalid\n"));
				debugger ("FingerPrint data was invalid");
			}
			m_TIcached = FindTeamItem (FPData.TeamID);
		}
		else
		{
			PRINT (("call debuger as flatmsg data was bad\n"));
			debugger ("pflatmsg data was invalid");
		}
	}

//	PRINT (("    INFO:  DisableUpdates.\n"));
	Window()->DisableUpdates ();
	//CTeamItem * perfTI ((CTeamItem *) m_ColumnListView->ItemAt (0));
	//BScrollBar * sbar (perfTI->m_CLV->ScrollBar (B_VERTICAL));
	//BView * sbarparent (sbar->Parent ());
	//sbar->RemoveSelf ();
	//BView * psbarview (sbar->Target ());
	//sbar->SetTarget ((BView *) NULL);
//	BString str;

	while (countitems--)
	{
		PRINT (("remove an item from list\n"));
		pflatmsg = (char *) pCurrentDataList->RemoveItem (static_cast<int32> (0));

		if (pflatmsg)
		{
			PRINT (("ptr to flatmsg was good: %x\n", pflatmsg));
			rc = msg.Unflatten ((const char *) pflatmsg);

			PRINT (("delete flatmsg\n"));
			delete [] pflatmsg;

			if (rc == B_OK)
			{
#if DEBUG
				PRINT (("msg.unflatten worked, print contents:\n"));
				msg.PrintToStream ();
#endif
				ptrFP = NULL;
				msgsize = 0;
				PRINT (("unflatten worked, FindData P\n"));
				rc = msg.FindData ("P", B_RAW_TYPE, (const void **) &ptrFP, &msgsize);
				if ((ptrFP != NULL) && (rc == B_OK))
				{
#if DEBUG
					if (sizeof(FingerPrint) != msgsize)
					{
						PRINT (("msgsize and FP size don't match!!!\n"));
					}
#endif
					PRINT (("ptrFP=%x, FPData=%x\n", ptrFP, &FPData));
					memcpy (&FPData, ptrFP, sizeof(FingerPrint));
				}
				else
				{
					PRINT (("call debugger as FP data was invalid\n"));
					debugger ("FingerPrint data was invalid");
				}
			}
			else
			{
				PRINT (("call debugger as Unflatten failed, rc=%i\n", rc));
				debugger ("msg.Unflatten failed!\n");
			}
		}
		else
		{
			PRINT (("call debugger as flatmsg was invalid\n"));
			debugger ("pflatmsg data was invalid");
		}

		BString FileName, MethodDefinition, Details, Description;
		msg.FindString ("F", &FileName); //the File name uses 'F'
		msg.FindString ("M", &MethodDefinition); //the ClassMethodDefinition uses 'A'
		msg.FindString ("D", &Description); //The Description used 'D'
		msg.FindString ("X", &Details); //The Details used 'X'

		void * tmp_inst (NULL);
		msg.FindPointer ("I", &tmp_inst); // The Instance uses 'I'
		if (NULL != tmp_inst) PRINT (("@@TIMELINE@@ Found an Instance Pointer In Message\n"));
		intptr_t Inst ((intptr_t)tmp_inst);

		if (m_TIcached->m_TeamID != FPData.TeamID)
		{
			PRINT ((" m_TIcached didn't match, call FindTeamItem.\n"));
			m_TIcached = FindTeamItem (FPData.TeamID);
		}

		PRINT (("new a ClueItem\n"));
		ci = new ClueItem (&FPData, &FileName, &MethodDefinition, &Description, &Details, Inst);
//		PRINT (("    INFO:  m_TIcached->AddClue (ci)\n"));
		PRINT (("AddClue\n"));
		m_TIcached->AddClue (ci);
//		PRINT (("    INFO:  m_TIcached->AddClue (ci)   finished\n"));
//		delete fp;
	}
	countitems =  m_ColumnListView->CountItems ();
//	PRINT ((" ProcessIncomingData : AddClues done, now AdjustQueue.\n"));

	TeamItem * ti (NULL);
	while (countitems--)
	{
		ti = (TeamItem *) m_ColumnListView->ItemAt (countitems);
#if DEBUG
		if (NULL == ti)
		{
			PRINT (("ti was NULL, but we are about to use it!!!\n"));
		}
#endif
		ti->AdjustQueue ();

		//update count view
		BStringView * pSV ((BStringView *) ti->m_CLV->Parent()->FindView ("ListCountView"));
		if (pSV)
		{
			BString s;
			PRINT (("update list count\n"));
			s << ti->m_CLV->CountItems () << STR_ITEMS;
			pSV->SetText (s.String ());
		}
	}

	//sbar->SetTarget (psbarview);
	//sbarparent->AddChild (sbar);
	Window()->EnableUpdates ();

	PRINT (("make the list empty\n"));
	pCurrentDataList->MakeEmpty ();  //the data has been transferred, clear the list for the port thread

//	if (pCLV->CurrentSelection (0) < 0)
//	{
//	}

	if (m_runner)
	{
		PRINT (("reset interval\n"));
		m_runner->SetInterval (100000);
	}

	if (pAV)
	{
		PRINT (("unpause ani\n\n\n"));
		pAV->Pause (false);
	}

/*
	FingerPrint * fp (NULL);
	ClueItem * ci (NULL);

	// assuming the vast majority of entries are from the same Team,
	// we'll cache the CTeamItem so we don't have to look it up
	// in FindTeamItem every time.  For several hundred messages,
	// I would think this would result in quite a bit of savings
	if (m_TIcached == NULL)
	{
		fp = reinterpret_cast<FingerPrint *> (pCurrentDataList->ItemAt (static_cast<int32> (0)));
		m_TIcached = FindTeamItem (fp->TeamID);
	}

	Window()->DisableUpdates ();
	//CTeamItem * perfTI ((CTeamItem *) m_ColumnListView->ItemAt (0));
	//BScrollBar * sbar (perfTI->m_CLV->ScrollBar (B_VERTICAL));
	//BView * sbarparent (sbar->Parent ());
	//sbar->RemoveSelf ();
	//BView * psbarview (sbar->Target ());
	//sbar->SetTarget ((BView *) NULL);

	PRINT ((" ProcessIncomingData : AddClues.\n"));
	while (countitems--)
	{
		fp = reinterpret_cast<FingerPrint *> (pCurrentDataList->RemoveItem (static_cast<int32> (0)));
		if (m_TIcached->m_TeamID != fp->TeamID)
		{
			m_TIcached = FindTeamItem (fp->TeamID);
			PRINT ((" m_TIcached didn't match, call FindTeamItem.\n"));
		}
		ci = new ClueItem (fp);
		m_TIcached->AddClue (ci);
		delete fp;
	}
	countitems =  m_ColumnListView->CountItems ();
	PRINT ((" ProcessIncomingData : AddClues done, now AdjustQueue.\n"));

	TeamItem * ti (NULL);
	while (countitems--)
	{
		ti = (TeamItem *) m_ColumnListView->ItemAt (countitems);
		ti->AdjustQueue ();
	}

	//sbar->SetTarget (psbarview);
	//sbarparent->AddChild (sbar);
	Window()->EnableUpdates ();

	pCurrentDataList->MakeEmpty ();  //the data has been transferred, clear the list for the port thread

	if (m_runner)
	{
		m_runner->SetInterval (100000);
	}
*/
}


/***************************************************************
start at end of list as most recently added items are there
and are probably more likely to have caused
***************************************************************/
TeamItem *
BackView :: FindTeamItem
	(
	team_id findthisteam
	)
{
	int32			index (m_ColumnListView->CountItems ());
	TeamItem *		ti (NULL);

	while (index--)
	{
		ti = (TeamItem *) m_ColumnListView->ItemAt (index);
		if (ti->m_TeamID == findthisteam)
		{
			return (ti);
		}
	}

	//if we got this far, we know it wasn't in the list
	return (CreateNewTeamItem (findthisteam));
}


class MyTextView : public BTextView
{
	public:
		MyTextView (BRect frame, const char * name, BRect textRect, uint32 resizeMask, uint32 flags = B_WILL_DRAW | B_PULSE_NEEDED)
		:	BTextView (frame, name, textRect, resizeMask, flags)
		,	m_Scroller (NULL)
		{
		}
		virtual void MakeFocus (bool focusState = true)
		{
			if (m_Scroller)
			{
				m_Scroller->SetBorderHighlighted (focusState);
			}
			BTextView::MakeFocus (focusState);
		}
		virtual void TargetedByScrollView (BScrollView *scroller)
		{
			m_Scroller = scroller;
			BView::TargetedByScrollView (scroller);
		}
		virtual void AttachedToWindow (void)
		{
			BView::AttachedToWindow ();
			//need to do the following because of draw bug:
			//if the scrollbar is > 0, the text is not scrolled in the TextView correctly.
			//instead, it's set at 0.  This fixes that problem until Be fixes the BTextView
			if (m_Scroller)
			{
				BScrollBar * pSB (m_Scroller->ScrollBar (B_VERTICAL));
				if (NULL != pSB)
				{
					float val (pSB->Value ());
					if (val > 0)
					{
						pSB->SetValue (val - 1);
						pSB->SetValue (val);
					}
				}
			}
		}
	private:
		BScrollView *	m_Scroller;
};


/***************************************************************
need to restructure this code!!!
***************************************************************/
TeamItem *
BackView :: CreateNewTeamItem
	(
	BMessage * archive
,	int32 teamarcfmt
	)
{
	PRINT (("CBackView :: CreateNewTeamItem\n"));
	BFont font;
	GetFont (&font);

	BRect trect (0.0f, 0.0f, 0.0f, 0.0f);
	BRect frame (7.0f, 103.0f, 93.0f - B_V_SCROLL_BAR_WIDTH, 193.0f - B_H_SCROLL_BAR_HEIGHT); 

	MyTextView * txtDetails (new MyTextView (frame, "DetailView", trect, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE));
	txtDetails->SetStylable (false);
	txtDetails->MakeEditable (false);
	txtDetails->SetWordWrap (false);
	txtDetails->SetFontAndColor (be_fixed_font);

	BView * tmpview (new BView (BRect (0.0f, 0.0f, 100.0f, 200.0f), "generic container", B_FOLLOW_ALL, 0));
	tmpview->SetViewColor (CLR_FOREGROUND);
	BetterScrollView * container (NULL);

	FingerprintCLV * pCLV (new FingerprintCLV (BRect (7.0f, 7.0f, 93.0f - B_V_SCROLL_BAR_WIDTH, 93.0f - B_H_SCROLL_BAR_HEIGHT),
		txtDetails, CLR_FOREGROUND, &container, "FingerprintCLV", B_FOLLOW_ALL_SIDES,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_MULTIPLE_SELECTION_LIST,
		true, true, true, B_FANCY_BORDER));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_CATEGORY, 30.0));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_EVENT, 30.0));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_METHOD, font.StringWidth ("AMethodName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_CLASS, font.StringWidth ("AClassName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_FILE, font.StringWidth ("AFileName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_LINE, font.StringWidth ("00000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_THREAD_ID, font.StringWidth ("000000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_SEQUENCE, font.StringWidth ("000000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_DATE, font.StringWidth ("00/00/0000") + 6.0f));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_TIME, font.StringWidth ("00:00:00.000000") + 6.0f));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_DESCRIPTION, 150.0f));

	pCLV->SetViewColor (CLR_LIST_BACKGROUND);

	//update count view
	BStringView * pSV ((BStringView *) container->FindView ("ListCountView"));
	if (pSV)
	{
		BString s;
		s << pCLV->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}

	BMessage * invokemsg (new BMessage (MSG_LIST_CLUE_ITEM_INVOCATED));
	invokemsg->AddPointer ("CIL", (const void *) pCLV);
	pCLV->SetInvocationMessage (invokemsg); //the ListView is responsible for releasing the new'd BMessage

	invokemsg = new BMessage (MSG_LIST_CLUE_ITEM_SELECTED);
	invokemsg->AddPointer ("CIL", (const void *) pCLV);
	invokemsg->AddPointer ("DetailView", (const void *) txtDetails);
	pCLV->SetSelectionMessage (invokemsg); //the ListView is responsible for releasing the new'd BMessage

	BRect rc (container->Bounds ());
	tmpview->AddChild (container);
	BScrollView * pBSV (new BScrollView("DetailViewScroll", txtDetails, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM, 0, true, true));
	rc = pBSV->Bounds ();

	BView * corner (new BView (BRect (rc.right - B_V_SCROLL_BAR_WIDTH, rc.bottom - B_H_SCROLL_BAR_HEIGHT, rc.right - 1.0f,
		rc.bottom - 1.0f), "TVCorner", B_FOLLOW_BOTTOM | B_FOLLOW_RIGHT, 0));
	corner->SetViewColor (CLR_FOREGROUND);
	pBSV->AddChild (corner);	
	tmpview->AddChild (pBSV);

	TeamItem *	ti (new TeamItem (archive, tmpview, pCLV, teamarcfmt));
	ASSERT (ti);
	ti->m_TabVisible = true;
	m_ColumnListView->AddItem (ti);

	//update count view
	pSV = (BStringView *) m_ColumnListView->Parent()->FindView ("ListCountView");
	if (pSV)
	{
		BString s;
		s << m_ColumnListView->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}

	//add the new Team's tab
	ti->m_tab = new TeamTab (ti->m_bitmap);
	char tabname[30];
	sprintf (tabname, STR_CLUE_TAB_TITLE, ti->m_TeamID);
	ti->m_tab->SetLabel (tabname);
	tmpview = new DummyView (ti->m_view->Bounds (), tabname, ti->m_CLV);
	tmpview->AddChild (ti->m_view);
	m_tvTabs->AddTab (tmpview, ti->m_tab);
//	m_tvTabs->Select (0);//index);

/*
	TeamItem *	ti (new TeamItem (msg, tmpview, pCLV));
	ASSERT (ti);
	ti->m_TabVisible = true;
	m_ColumnListView->AddItem (ti);

	//add the new Team's tab
	ti->m_tab = new TeamTab (ti->m_bitmap);
	char tabname[30];
	sprintf (tabname, STR_CLUE_TAB_TITLE, ti->m_TeamID);
	ti->m_tab->SetLabel (tabname);
	tmpview = new DummyView (ti->m_view->Bounds (), tabname, ti->m_CLV);
	tmpview->AddChild (ti->m_view);
	m_tvTabs->AddTab (tmpview, ti->m_tab);
	//m_tvTabs->Select (0);//index);
*/
	return (ti);
}


/***************************************************************
need to restructure this code!!!
***************************************************************/
TeamItem *
BackView :: CreateNewTeamItem
	(
	team_id TeamID
	)
{
	BFont font;
	GetFont (&font);

	BRect trect (0.0f, 0.0f, 0.0f, 0.0f);
	BRect frame (7.0f, 103.0f, 93.0f - B_V_SCROLL_BAR_WIDTH, 193.0f - B_H_SCROLL_BAR_HEIGHT); 

	MyTextView * txtDetails (new MyTextView (frame, "DetailView", trect, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE));
	txtDetails->SetStylable (false);
	txtDetails->MakeEditable (false);
	txtDetails->SetWordWrap (false);
	txtDetails->SetFontAndColor (be_fixed_font);

	BView * tmpview (new BView (BRect (0.0f, 0.0f, 100.0f, 200.0f), "generic container", B_FOLLOW_ALL, 0));
	tmpview->SetViewColor (CLR_FOREGROUND);
	BetterScrollView * container (NULL);

	FingerprintCLV * pCLV (new FingerprintCLV (BRect (7.0f, 7.0f, 93.0f - B_V_SCROLL_BAR_WIDTH, 93.0f - B_H_SCROLL_BAR_HEIGHT),
		txtDetails, CLR_FOREGROUND, &container, "FingerprintCLV", B_FOLLOW_ALL_SIDES,
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_MULTIPLE_SELECTION_LIST,
		true, true, true, B_FANCY_BORDER));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_CATEGORY, 30.0));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_EVENT, 30.0));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_METHOD, font.StringWidth ("AMethodName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_CLASS, font.StringWidth ("AClassName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_FILE, font.StringWidth ("AFileName")));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_LINE, font.StringWidth ("00000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_THREAD_ID, font.StringWidth ("000000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_SEQUENCE, font.StringWidth ("000000") + 6.0f, CLV_ALIGN_RIGHT));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_DATE, font.StringWidth ("00/00/0000") + 6.0f));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_TIME, font.StringWidth ("00:00:00.000000") + 6.0f));
	pCLV->AddColumn (new CLVColumn (STR_CLUE_COLUMN_DESCRIPTION, 150.0f));

	pCLV->SetViewColor (CLR_LIST_BACKGROUND);

	//update count view
	BStringView * pSV ((BStringView *) container->FindView ("ListCountView"));
	if (pSV)
	{
		BString s ("0");  //couldn't have anything in there yet, so it will always be zero (0)!!!
		s << STR_ITEMS;
//		s << pCLV->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}

	BMessage * msg (new BMessage (MSG_LIST_CLUE_ITEM_INVOCATED));
	msg->AddPointer ("CIL", (const void *) pCLV);
	pCLV->SetInvocationMessage (msg); //the ListView is responsible for releasing the new'd BMessage

	msg = new BMessage (MSG_LIST_CLUE_ITEM_SELECTED);
	msg->AddPointer ("CIL", (const void *) pCLV);
	msg->AddPointer ("DetailView", (const void *) txtDetails);
	pCLV->SetSelectionMessage (msg); //the ListView is responsible for releasing the new'd BMessage

	BRect rc (container->Bounds ());
	tmpview->AddChild (container);
	BScrollView * pBSV (new BScrollView("DetailViewScroll", txtDetails, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM, 0, true, true));
	rc = pBSV->Bounds ();

	BView * corner (new BView (BRect (rc.right - B_V_SCROLL_BAR_WIDTH, rc.bottom - B_H_SCROLL_BAR_HEIGHT, rc.right - 1.0f,
		rc.bottom - 1.0f), "TVCorner", B_FOLLOW_BOTTOM | B_FOLLOW_RIGHT, 0));
	corner->SetViewColor (CLR_FOREGROUND);
	pBSV->AddChild (corner);	
	tmpview->AddChild (pBSV);

	TeamItem *	ti (new TeamItem (TeamID, tmpview, pCLV));
	ti->SetRunning (true);
	ASSERT (ti);
	ti->m_TabVisible = true;
	m_ColumnListView->AddItem (ti);

	//update count view
	pSV = (BStringView *) m_ColumnListView->Parent()->FindView ("ListCountView");
	if (pSV)
	{
		BString s;
		s << m_ColumnListView->CountItems () << STR_ITEMS;
		pSV->SetText (s.String ());
	}

	//add the new Team's tab
	ti->m_tab = new TeamTab (ti->m_bitmap);
	char tabname[30];
	sprintf (tabname, STR_CLUE_TAB_TITLE, ti->m_TeamID);
	ti->m_tab->SetLabel (tabname);
	tmpview = new DummyView (ti->m_view->Bounds (), tabname, ti->m_CLV);
	tmpview->AddChild (ti->m_view);
	m_tvTabs->AddTab (tmpview, ti->m_tab);
	m_tvTabs->Select (0);//index);

	return (ti);
}


/***************************************************************
 BackView::OnPrint
 -----------------
 Handles the File>Print command.
***************************************************************/
void
BackView :: OnPrint
	(
	void
	)
{
/*
	// create the object which will manage the print process
	BPrintJob printJob ("Clue");
	
	if (! m_PrintSettings)
	{
		if (B_OK != OnPageSetup ())
		{
			return;  // Page Setup cancelled
		}
	}
	
	// update the print job with the document's current
	// Page Setup settings.
	printJob.SetSettings (new BMessage (*m_PrintSettings));
	
	// run the standard File>Print dialog to determine page range, # of copies, etc.
	if (B_OK != printJob.ConfigJob ())
	{
		return;
	}
*/
	// determine page range
	int32 nFirst = m_PrintJob->FirstPage ();
	int32 nLast = m_PrintJob->LastPage ();
	int32 nTotal = 5;
	
	if (nFirst < 1)
		nFirst = 1;
	if (nLast < 1)
		nLast = 1;
	if (nFirst >= nTotal)
		nFirst = nTotal;
	if (nLast >= nTotal)
		nLast = nTotal;

	nFirst = 1;
	int32 index (m_ColumnListView->CurrentSelection (0));
	TeamItem * ti ((TeamItem *) m_ColumnListView->ItemAt (index));
	nLast = ti->m_ItemList.CountItems ();

	
	// start the printing process
	bool bOk = true;
	m_PrintJob->BeginJob ();

	for (int32 i = nFirst; i <= nLast; i++)
	{
		bOk = PrintPage (i);
		if (! bOk)
		{
			break;
		}
	}
	
	if (bOk)
	{
		// no errors; complete the printing process
		m_PrintJob->CommitJob ();
	}
	else
	{
		// errors in printing; inform the user and bail
		BAlert* pAlert = new BAlert("print error",
			"There was an error printing the document.", "OK");
		pAlert->Go();
	}

	delete m_PrintJob;
	m_PrintJob = NULL;	
}

/***************************************************************
***************************************************************/
class PrintView : public BView
{
public:
	PrintView (BRect rc, const char * text, ClueItem * ci)
	:	BView (rc, "printview", B_FOLLOW_NONE, B_WILL_DRAW)
	,	m_CI (ci)
	,	m_text(text)
	{
		// .25 in. from top of view to the text
		m_fAboveText = 18;
		// .35 inches from bottom of text to ruler
		m_fBelowText = 26;
		// .25 inches from ruler to bottom of view
		m_fBelowLine = 18;
		// total height of text (also in points)
		font_height height;
		GetFontHeight (&height);
		m_fTextHeight = height.ascent + height.descent + height.leading;
	
		// resize view to the correct height and specified width
		//float totHeight = m_fAboveText + m_fTextHeight + m_fBelowText + m_fBelowLine;		
		//ResizeTo(width, totHeight);
	}
	virtual void Draw (BRect rc)
	{
		// draw string m_fAboveText units down
		float y (m_fAboveText);
		DrawString (m_text, BPoint (rc.left, y));
		// draw ruler m_fBelowText units below text
		y += m_fTextHeight + m_fBelowText;
		StrokeLine (BPoint (rc.left, y), BPoint (rc.right, y));

		y += m_fTextHeight + m_fBelowText;
		SetDrawingMode (B_OP_OVER);
		DrawBitmap (m_CI->m_CategoryBmp, BRect (rc.left + 4.0f, y, rc.left + 19.0f, y + 16.0f));
		DrawBitmap (m_CI->m_EventBmp, BRect (rc.left + 24.0f, y, rc.left + 39.0f, y + 16.0f));
		SetDrawingMode (B_OP_COPY);

		DrawString (m_CI->m_File, BPoint (rc.left + 35, y));

		y += m_fTextHeight + m_fBelowText;
		DrawString (m_CI->m_Method, BPoint (rc.left, y));

		y += m_fTextHeight + m_fBelowText;
		DrawString (m_CI->m_Class, BPoint (rc.left, y));

		y += m_fTextHeight + m_fBelowText;
		DrawString (m_CI->m_Description, BPoint (rc.left, y));

		y += m_fTextHeight + m_fBelowText;
		DrawString (m_CI->m_Detail, BPoint (rc.left, y));
	}
private:
	ClueItem * m_CI;
	float m_fTextHeight;
	float m_fAboveText;
	float m_fBelowText;
	float m_fBelowLine;
	const char* m_text;
};


/***************************************************************
 BackView::PrintPage
 -----------------
 Prints the specified page to the specified print job.
***************************************************************/
bool
BackView :: PrintPage
	(
	int32 nPage
	)
{
	BRect r = m_PrintJob->PrintableRect();	// relative to left top corner of paper
	BWindow * pWin (Window ());

	int32 index (m_ColumnListView->CurrentSelection (0));
	TeamItem * ti ((TeamItem *) m_ColumnListView->ItemAt (index));
	ClueItem * pCI ((ClueItem *) ti->m_ItemList.ItemAt (nPage - 1));

	// create a view which draws the header	
	PrintView * pPrintView (new PrintView (r, "Here is some text to print from Clue!", pCI));
	
	pPrintView->Hide ();	// so the view won't be seen on screen
	pWin->AddChild (pPrintView);  // view needs to be attached to a window to be drawn

	r.OffsetTo(0.0f, 0.0f);	// we draw relative to left top corner of printable area
	BPoint pt (r.LeftTop ());
	//pt.x += nPage * 10;
//	m_PrintJob->DrawView (ti->m_CLV, r, pt);
	m_PrintJob->DrawView (pPrintView, r, pt);
	
	// clean up
	pWin->RemoveChild (pPrintView);
	delete pPrintView;
			
	m_PrintJob->SpoolPage ();
	return (m_PrintJob->CanContinue ());
}


/***************************************************************
***************************************************************/
void
BackView :: TeamsInRoster
	(
	void
	)
{
	int32			index (m_ColumnListView->CountItems ());
	TeamItem *		ti (NULL);
	app_info		ai;

//	PRINT (("run TeamsInRoster, count=%i\n", index));
	while (index--)
	{
		ti = (TeamItem *) m_ColumnListView->ItemAt (index);
		if(ti->IsRunning ())
		{
			bool refreshteam (false);
			if (B_OK == be_roster->GetRunningAppInfo (ti->m_TeamID, &ai))
			{
				refreshteam = ti->SetRunning (true);
			}
			else
			{
				refreshteam = ti->SetRunning (false);
			}

			if (refreshteam)
			{
				m_ColumnListView->InvalidateItem (index);
				PRINT (("refresh #%i\n", index));
			}
		}
	}
}


/*************************************************************************
*************************************************************************/
void
BackView :: Activate
	(
	void
	)
{
	PRINT (("Activate\n"));
	TeamItem * pTI ((TeamItem *) m_ColumnListView->ItemAt (m_ColumnListView->CurrentSelection ()));
	be_roster->ActivateApp (pTI->m_TeamID);
}


