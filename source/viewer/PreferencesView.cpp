//#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _BUTTON_H
#include <Button.h>
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

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _OUTLINE_LIST_VIEW_H
#include <OutlineListView.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _TEXTVIEW_H
#include <TextView.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

#ifndef _EDITBOOLVIEW_H
#include "EditBoolView.h"
#endif

#ifndef _EDITCOLORVIEW_H
#include "EditColorView.h"
#endif

#ifndef _EDITTEAMVIEW_H
#include "EditTeamView.h"
#endif

#ifndef _PREFERENCESVIEW_H
#include "PreferencesView.h"
#endif

#ifndef _PREFERENCE_ITEM_H
#include "PreferenceItem.h"
#endif

#ifndef _CREDITSVIEW_H
#include "CreditsView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

extern volatile sem_id g_SettingsSemaphore;
extern BMessage g_Settings;


PreferencesView :: PreferencesView
(
	BRect frame
	,	BMessage* message
)
	:	BView(frame, "Preferences View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_PULSE_NEEDED)
	,	m_btnOK(NULL)
	,	m_btnCancel(NULL)
	,	m_btnApply(NULL)
	,	m_outline(NULL)
	,	m_text(NULL)
	,	m_EditView(NULL)
	,	m_IsDirty(false)
{
	SetViewColor(CLR_BACKGROUND);

	m_outline = new BOutlineListView(BRect(10.0f, 10.0f, 200.0f, 150.0f), "preference_list", B_SINGLE_SELECTION_LIST);
	CreateList(m_outline, NULL, message);

	m_outline->SetSelectionMessage(new BMessage('msel'));
	AddChild(new BScrollView("scroll_preference_items", m_outline, B_FOLLOW_LEFT | B_FOLLOW_TOP, 0, false, true));

	frame.left = 10;
	frame.top = 160;
	frame.right = 50;
	frame.bottom = 180;
	m_btnOK = static_cast<BButton*>(new BButton(frame, STR_OK, STR_OK, new BMessage(MSG_OK)));
	m_btnOK->MakeDefault(true);
	AddChild(m_btnOK);

	frame.left = 60;
	frame.right = 100;
	m_btnCancel = static_cast<BButton*>(new BButton(frame, STR_CANCEL, STR_CANCEL, new BMessage(MSG_CANCEL)));
	AddChild(m_btnCancel);

	frame.left = 110;
	frame.right = 160;
	m_btnApply = static_cast<BButton*>(new BButton(frame, STR_APPLY, STR_APPLY, new BMessage(MSG_APPLY)));
	m_btnApply->SetEnabled(false);
	AddChild(m_btnApply);
}


PreferencesView :: ~PreferencesView
(
	void
)
{
	PreferenceItem* pPI(NULL);

	for (int32 i(m_outline->CountItems() - 1); i >= 0 ; i--) {
		pPI = (PreferenceItem*) m_outline->RemoveItem(i);
		delete pPI;
	}
}


/***************************************************************
***************************************************************/
void
PreferencesView :: MessageReceived
(
	BMessage* msg
)
{
	//put in most-frequent to less-frequent order for that little extra speed we all want!
	switch (msg->what) {
		case 'msel': {
				BRect frame(Bounds());
				frame.left = 200.0f + B_V_SCROLL_BAR_WIDTH + 10.0f;

				if (m_EditView) {
					m_EditView->Save();
					PRINT(("EditView->Save\n"));
					m_EditView->RemoveSelf();
					delete m_EditView;
					m_EditView = NULL;
				}

				int32 index(m_outline->CurrentSelection(0));
				if (index >= 0) {
					PRINT(("ItemSelected: index = %i\n", index));
					PreferenceItem* pi((PreferenceItem*)m_outline->ItemAt(index));
					if (pi) {
						PRINT(("  pi was valid\n"));
						BMessage* pMsg(pi->GetMessage());
						if (pMsg) {
							PRINT(("  pMsg was valid\n"));
							switch (pMsg->what) {
								case B_BOOL_TYPE:
									PRINT(("B_BOOL_TYPE\n"));
									//m_text->SetText ("B_BOOL_TYPE");
									m_EditView = (EditView*) new EditBoolView(frame, pMsg);
									m_EditView->SetLabel("B_BOOL_TYPE");
									break;
								case 'team':
									PRINT(("team\n"));
									//m_text->SetText ("B_DOUBLE_TYPE");
									m_EditView = (EditView*) EditTeamView::Create(frame, pMsg);
									if (m_EditView) {
										PRINT(("\nm_EditView was valid\n\n"));
										m_EditView->SetLabel("team");
									} else
										PRINT(("\nm_EditView was INvalid\n\n"));
									break;
								case B_RGB_COLOR_TYPE:
									PRINT(("B_RGB_COLOR_TYPE\n"));
									m_EditView = (EditView*) EditColorView::Create(frame, pMsg);
									if (m_EditView) {
										PRINT(("\nm_EditView was valid\n\n"));
										m_EditView->SetLabel("B_RGB_COLOR_TYPE");
									} else
										PRINT(("\nm_EditView was INvalid\n\n"));
									break;
								case 'node':
									PRINT(("node\n"));
									//m_text->SetText ("a node");
									break;
								default:
									PRINT(("pMsg->what=%i\n", pMsg->what));
									//m_text->SetText ("testing");
									break;
							}
						} else
							DEBUGGER("pMsg was NULL");
//						m_text->SetText ("pMsg was NULL");
					} else
						DEBUGGER("PreferencesItem was NULL");
//					m_text->SetText ("PreferenceItem was NULL");
				}
			}

			if (m_EditView) {
				PRINT(("pEditView = %08x\n", m_EditView));
//				m_text->RemoveSelf ();
				AddChild(m_EditView);
			}
//			else
//			{
//				AddChild (m_text);
//			}
			break;
		case MSG_CANCEL:
			Window()->PostMessage(B_QUIT_REQUESTED, Window());
			break;
		case MSG_OK:
			Window()->PostMessage(B_QUIT_REQUESTED, Window());
			// don't break here, save the settings first!!!
			if (!m_IsDirty)
				break;
		case MSG_APPLY: {
				if (m_EditView)
					m_EditView->Save();
				BMessage retmsg(MSG_BROADCAST_SETTINGS_CHANGED);
				PRINT(("\n\nPrefView\n"));
				BMessage* pmsg(NULL);

				for (int32 j(0); j < m_outline->CountItems(); j++) {
					PreferenceItem* pPI((PreferenceItem*) m_outline->ItemAt(j));
					pmsg = pPI->GetMessage();
					retmsg.AddMessage(pPI->GetName(), (const BMessage*) pmsg);
//				ssize_t numBytes (0);
//				BMessage msgtmp;
//				rgb_color * pColor;

//				if (B_OK == pmsg->FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
//				{
//					PRINT (("PrefView color: red=%i, green=%i, blue=%i\n\n", pColor->red, pColor->green, pColor->blue));
//				}
				}
				BMessenger msngr(NULL, be_app);
				msngr.SendMessage(&retmsg);
				m_IsDirty = false;
				m_btnApply->SetEnabled(false);
			}
			break;
		case B_OBSERVER_NOTICE_CHANGE: {
				uint32 change(0);
				msg->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32*) &change);
				switch (change) {
					case MSG_SETTINGS_CHANGED: {
							SetViewColor(CLR_BACKGROUND);
							SetLowColor(CLR_BACKGROUND);
							Invalidate();

							m_btnOK->SetViewColor(CLR_BACKGROUND);
							m_btnOK->SetLowColor(CLR_BACKGROUND);
							m_btnOK->Invalidate();

							m_btnCancel->SetViewColor(CLR_BACKGROUND);
							m_btnCancel->SetLowColor(CLR_BACKGROUND);
							m_btnCancel->Invalidate();

							m_btnApply->SetViewColor(CLR_BACKGROUND);
							m_btnApply->SetLowColor(CLR_BACKGROUND);
							m_btnApply->Invalidate();

							m_outline->SetViewColor(CLR_LIST_BACKGROUND);
							m_outline->SetLowColor(CLR_LIST_BACKGROUND);
							m_outline->Invalidate();
						}
						break;
				}
			}
			break;
		default:
			BView::MessageReceived(msg);
	}
}



void
PreferencesView :: CreateList
(
	BOutlineListView* OLV
	,	BListItem* superitem
	,	BMessage* inMsg
)
{
#ifdef CLUE_ON_ZETA_HACK
	char const* name(NULL);
#else
	char* name(NULL);
#endif
	uint32 type(0);
	int32 count(0);
	BMessage valBMessage;
	PreferenceItem* subitem(NULL);
	BString str;

	acquire_sem(g_SettingsSemaphore);

	for (int32 i(0); inMsg->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; i++) {
		PRINT(("name=%s;  i=%i;  count=%i\n", name, i, count));

		switch (inMsg->FindString(name, &str)) {
			case B_OK:
				for (int32 j(0); j < count; j++) {
					PRINT(("j = %i\n", j));
					g_Settings.FindMessage(str.String(), &valBMessage);
					subitem = (PreferenceItem*) new PreferenceItem(str.String(), name);
					subitem->CopyMessage(&valBMessage);
					OLV->AddItem(subitem);
				}
//			subitem = (PreferenceItem *) new PreferenceItem (name);
//			subitem->CopyMessage (&valBMessage);
//			if (superitem) //if not NULL
//			{
//				OLV->AddUnder (subitem, superitem);
//			}
//			else
//			{
//				OLV->AddItem (subitem);
//			}
//			CreateList (OLV, subitem, &valBMessage);
				break;
			case B_BAD_INDEX:
				PRINT(("\nB_BAD_INDEX\n"));
				break;
			case B_BAD_TYPE:
				PRINT(("\nB_BAD_TYPE\n"));
				break;
			case B_NAME_NOT_FOUND:
				PRINT(("\nB_NAME_NOT_FOUND\n"));
				break;
			default:
				PRINT(("\nother error\n"));
				break;
		}
	}

	release_sem(g_SettingsSemaphore);
}


/***************************************************************
***************************************************************/
void
PreferencesView :: AllAttached
(
	void
)
{
	m_outline->SetTarget(this);
	m_outline->MakeFocus();
	m_btnOK->SetTarget(this);
	m_btnCancel->SetTarget(this);
	m_btnApply->SetTarget(this);
	BWindow* pwnd(Window());
	if (pwnd)
		((BHandler*)pwnd)->StartWatching((BHandler*) this, MSG_SETTINGS_CHANGED);
}


void
PreferencesView :: SetDirty
(
	void
)
{
	m_IsDirty = true;
	m_btnApply->SetEnabled(true);
}


//void
//PreferencesView :: AddSubItem
//	(
//	BOutlineListView * OLV
//,	BListItem * LI
//,	BMessage * message
//	)
//{
//}



//void
//PreferencesView :: Draw
//	(
//	BRect updateRect
//	)
//{
//}


//void
//CSplashView :: Pulse
//	(
//	void
//	)
//{
//	if (m_AppStarting)
//	{
//		Window()->PostMessage (B_QUIT_REQUESTED, Window ());
//	}
//}


//void
//CSplashView :: AttachedToWindow
//	(
//	void
//	)
//{
//	if (!m_AppStarting)
//	{
//		m_btnOK->MakeFocus (true);
//	}
//}

