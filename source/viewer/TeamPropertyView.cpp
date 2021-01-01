/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/
//#define DEBUG 1

#ifndef _BUTTON_H
#include <Button.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _MENU_FIELD_H
#include <MenuField.h>
#endif

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
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

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION
#include "Clue.h"
#endif

#ifndef PROPERTYVIEW_H
#include "TeamPropertyView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef SLIDER_H
#include "Slider.h"
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif

#ifndef _BETTER_SCROLL_VIEW_H_
#include "BetterScrollView.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "ColumnListView.h"
#endif

#ifndef _CLV_COLUMN_LIST_VIEW_H_
#include "CLVColumn.h"
#endif

#ifndef _CLUE_PROPERTYITEM_H_
#include "PropertyItem.h"
#endif


/***************************************************************
***************************************************************/
TeamPropertyView :: TeamPropertyView
(
	BRect& frame
	,	const BWindow* wnd
	,	const BView* view
	,	const TeamItem* pTI
)
	:	BView(frame, "CTeamPropertyView", B_FOLLOW_ALL_SIDES, 0)
	,	m_targetwnd((BWindow*) wnd)
	,	m_targetview((BView*) view)
	,	m_slider(NULL)
	,	m_bsv(NULL)
	,	m_ColumnListView(NULL)
	,	m_TI(NULL)
	,	m_OK(NULL)
	,	m_CurCat(CC_GENERAL)
	,	m_menufld(NULL)
	,	m_popupmenu(NULL)
{
	m_TI = (TeamItem*) new TeamItem(*pTI);
	SetViewColor(CLR_BACKGROUND);
	m_slider = new Slider(BRect(5.0f, 5.0f, frame.right - 5.0f, 40.0f), "QueueLength", STR_EVENT_QUEUE_LENGTH, NULL, 1, 100000,
						  B_TRIANGLE_THUMB, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP);
	m_slider->SetValue(m_TI->m_QueueLength);
	rgb_color color = {255, 100, 100, 255};
	m_slider->UseFillColor(true, &color);
	color.red = 155;
	color.green = 155;
	color.blue = 255;
	color.alpha = 255;
	m_slider->SetBarColor(color);
	m_slider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	m_slider->SetHashMarkCount(11);
	m_slider->SetKeyIncrementValue(2000);
	m_slider->SetLimitLabels(STR_EVENT_QUEUE_LIMIT_LOW, STR_EVENT_QUEUE_LIMIT_HIGH);

	m_popupmenu = (BPopUpMenu*) new BPopUpMenu("category list");
	BMessage* msg(new BMessage(MSG_CATEGORY_CHANGED));
	msg->AddInt32("Category", CC_APPLICATION);
	m_popupmenu->AddItem(new BMenuItem("Application", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_GENERAL);
	BMenuItem* mi(new BMenuItem("General", msg));
	//BitmapMenuItem * mi (new BitmapMenuItem (NULL, "General", msg));
	mi->SetMarked(true);
	m_popupmenu->AddItem(mi);
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_INTERFACE);
	m_popupmenu->AddItem(new BMenuItem("Interface", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_KEYBOARD);
	m_popupmenu->AddItem(new BMenuItem("Keyboard", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_MEDIA);
	m_popupmenu->AddItem(new BMenuItem("Media", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_MOUSE);
	m_popupmenu->AddItem(new BMenuItem("Mouse", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_NETWORK);
	m_popupmenu->AddItem(new BMenuItem("Network", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_PRINTING);
	m_popupmenu->AddItem(new BMenuItem("Printing", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_STORAGE);
	m_popupmenu->AddItem(new BMenuItem("Storage", msg));
	msg = new BMessage(MSG_CATEGORY_CHANGED);
	msg->AddInt32("Category", CC_SUPPORT);
	m_popupmenu->AddItem(new BMenuItem("Support", msg));

	m_popupmenu->AddSeparatorItem();

	msg = new BMessage(MSG_MENU_SEL_ALL_CAT_ALL_EVT);
	m_popupmenu->AddItem(new BMenuItem(STR_SEL_ALL_CAT_ALL_EVT, msg));
	msg = new BMessage(MSG_MENU_USEL_ALL_CAT_ALL_EVT);
	m_popupmenu->AddItem(new BMenuItem(STR_USEL_ALL_CAT_ALL_EVT, msg));

	m_popupmenu->AddSeparatorItem();

	msg = new BMessage(MSG_MENU_SEL_CUR_CAT_ALL_EVT);
	m_popupmenu->AddItem(new BMenuItem(STR_SEL_CUR_CAT_ALL_EVT, msg));
	msg = new BMessage(MSG_MENU_USEL_CUR_CAT_ALL_EVT);
	m_popupmenu->AddItem(new BMenuItem(STR_USEL_CUR_CAT_ALL_EVT, msg));

	float width1(StringWidth(STR_CATEGORIES));
	BRect rc;
	rc.left = 5.0f;
	rc.top = m_slider->Frame().bottom + 7.0f;
	rc.right = rc.left + width1 + StringWidth("Application") + 24.0;
	m_menufld = (BMenuField*) new BMenuField(rc, STR_CATEGORIES, STR_CATEGORIES, m_popupmenu);
	m_menufld->SetDivider(width1);

	m_OK = new BButton(BRect(0.0f, 0.0f, 0.0f, 0.0f), STR_OK, STR_OK, new BMessage(MSG_OK), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM);
	m_OK->ResizeToPreferred();
	rc = m_OK->Bounds();
	m_OK->MoveTo(5.0f, Bounds().Height() - rc.Height() - 4.0f);
	rc = m_OK->Frame();
	BButton* btn(new BButton(BRect(rc.right + 4.0f, rc.top, 0.0f, 0.0f), STR_CANCEL, STR_CANCEL, new BMessage(B_QUIT_REQUESTED),
							 B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	btn->ResizeToPreferred();

	BFont font;
	GetFont(&font);

	rc.left = 7.0f;
	rc.right = frame.right - 7.0f - B_V_SCROLL_BAR_WIDTH;
	rc.bottom = rc.top - 5.0f - B_H_SCROLL_BAR_HEIGHT;
	//can't position top yet as the BMenuField doesn't get sized until Attached is called on it.
	//so we must defer sizing of the CLV until AllAttached is called!
	rc.top = m_slider->Frame().bottom + 7.0f;
	m_ColumnListView = new ColumnListView(rc, CLR_BACKGROUND, &m_bsv, "ClueItemsList", B_FOLLOW_ALL_SIDES,
										  B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE, B_SINGLE_SELECTION_LIST, true, true, true, B_FANCY_BORDER);
	m_ColumnListView->AddColumn(new CLVColumn(STR_TEAM_PROPERTY_COLUMN_VIEW, 20.0f, 0.0f));
	m_ColumnListView->AddColumn(new CLVColumn(STR_TEAM_PROPERTY_COLUMN_EVENT, 20.0f, 0.0f));
	m_ColumnListView->AddColumn(new CLVColumn(STR_TEAM_PROPERTY_COLUMN_DESCRIPTION, font.StringWidth(STR_CT_METHOD_ENTER_DESCRIPTION) + 6.0f, 0.0f));
	m_ColumnListView->AddColumn(new CLVColumn(STR_TEAM_PROPERTY_COLUMN_VALUE, font.StringWidth("CT_AUDIT_SUCCESS_INDEX") + 6.0f, 0.0f));
	m_ColumnListView->SetInvocationMessage(new BMessage(MSG_LIST_ITEM_INVOCATED));

	m_ColumnListView->AddItem(new PropertyItem(CT_CLASS_BIRTH_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_CLASS_DEATH_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_METHOD_ENTER_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_METHOD_EXIT_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_OK_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_INFO_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_WARNING_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_ERROR_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_AUDIT_SUCCESS_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_AUDIT_FAILURE_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_TIMER_INDEX));
	m_ColumnListView->AddItem(new PropertyItem(CT_OBJECT_INDEX));

	//put in tab order
	AddChild(m_slider);
	AddChild(m_menufld);
	AddChild(m_bsv);
	AddChild(m_OK);
	AddChild(btn);

	m_slider->MakeFocus();
	RefreshList();
}


/***************************************************************
***************************************************************/
TeamPropertyView :: ~TeamPropertyView
(
	void
)
{
	int32			index(m_ColumnListView->CountItems());
	PropertyItem* 	pi(NULL);

	while (index--) {
		pi = (PropertyItem*) m_ColumnListView->RemoveItem(index);
		delete pi;
	}

	delete m_TI;
	m_TI = NULL;
}


/***************************************************************
***************************************************************/
void
TeamPropertyView :: AllAttached
(
	void
)
{
	m_slider->SetTarget(this);
	m_ColumnListView->SetTarget(this);
	m_OK->SetTarget(this);
	m_slider->MakeFocus(true);
	m_popupmenu->SetTargetForItems(this);
	BPoint pt(5.0f, m_menufld->Frame().bottom + 7.0f);
	m_bsv->MoveTo(pt);
	m_bsv->ResizeBy(0.0f, -m_menufld->Bounds().Height() - 9.0f);

	BWindow* pwnd(Window());
	if (pwnd)
		((BHandler*)pwnd)->StartWatching((BHandler*) this, MSG_SETTINGS_CHANGED);
}


/***************************************************************
***************************************************************/
void
TeamPropertyView :: MessageReceived
(
	BMessage* msg
)
{
	switch (msg->what) {
		case MSG_CATEGORY_CHANGED:
			CategoryChanged(msg);
			break;
		case MSG_MENU_SEL_ALL_CAT_ALL_EVT:
			SelectUnselect(true, false);
			break;
		case MSG_MENU_USEL_ALL_CAT_ALL_EVT:
			SelectUnselect(false, false);
			break;
		case MSG_MENU_SEL_CUR_CAT_ALL_EVT:
			SelectUnselect(true, true);
			break;
		case MSG_MENU_USEL_CUR_CAT_ALL_EVT:
			SelectUnselect(false, true);
			break;
		case MSG_LIST_ITEM_INVOCATED: {
				int32 index(0);
				if (B_OK != msg->FindInt32("index", &index)) { //check for valid index!
					PRINT(("Couldn't find index\n"));
					break;
				}
				PRINT(("index = %i\n", index));

				PropertyItem* pi((PropertyItem*) m_ColumnListView->ItemAt(index));
				pi->m_selected = !pi->m_selected;

				PRINT((" Mask was = %08x.\n", m_TI->m_CategoryMask[m_CurCat]));
				if (pi->m_selected) {
					PRINT((" | it.\n"));
					m_TI->m_CategoryMask[m_CurCat] |= pi->m_Event;
				} else {
					PRINT((" & it.\n"));
					m_TI->m_CategoryMask[m_CurCat] &= ~pi->m_Event;
				}
				PRINT((" Mask now = %08x.\n", m_TI->m_CategoryMask[m_CurCat]));

				m_ColumnListView->InvalidateItem(index);
			}
			break;
		case MSG_OK: {
				BMessage msg(MSG_UPDATE_TEAM_PROPERTIES);
				m_TI->m_QueueLength = m_slider->Value();
				//NOTE: the receiver of this message is responsible for deleting the TeamItem ti!!!
				TeamItem* ti((TeamItem*) new TeamItem(*m_TI));
				msg.AddPointer("TeamItem", ti);
				m_targetwnd->PostMessage(&msg, m_targetview);
				Window()->PostMessage(B_QUIT_REQUESTED, Window());
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
						}
						break;
				}
			}
			break;
		default:
			BView::MessageReceived(msg);
	}
}


/***************************************************************
***************************************************************/
void
TeamPropertyView :: RefreshList
(
	void
)
{
	PRINT(("RefreshList\n"));
	PRINT((" TI mask[%i] is = %08x.\n", m_CurCat, m_TI->m_CategoryMask[m_CurCat]));
	((PropertyItem*)m_ColumnListView->ItemAt(0))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_BIRTH		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(1))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_DEATH		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(2))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_ENTER		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(3))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_EXIT		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(4))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_OK			? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(5))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_INFO		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(6))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_WARNING		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(7))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_ERROR		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(8))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_SUCCEEDED	? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(9))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_FAILED		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(10))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_TIMER		? true : false;
	((PropertyItem*)m_ColumnListView->ItemAt(11))->m_selected = m_TI->m_CategoryMask[m_CurCat] & CE_OBJECT		? true : false;

	m_ColumnListView->Invalidate();
}


/***************************************************************
***************************************************************/
void
TeamPropertyView :: CategoryChanged
(
	BMessage* msg
)
{
	ClueCategory cc(CC_GENERAL);
	if (B_OK == msg->FindInt32("Category", (int32*) &cc)) {
		m_CurCat = cc;
		RefreshList();
	}
}


/***************************************************************
***************************************************************/
void
TeamPropertyView :: SelectUnselect
(
	bool select
	,	bool CurrentCategoryOnly
)
{
	if (CurrentCategoryOnly)
		m_TI->m_CategoryMask[m_CurCat] = select ? 0xFFFFFFFF : 0x00000000;
	else {
		for (int i(0); i < 10; i++)
			m_TI->m_CategoryMask[i] = select ? 0xFFFFFFFF : 0x00000000;
	}

	//because the ClueCategory listing isn't in the same order as the menu, need this array for indexing
//	int CatArray[] = {1,0,2,4,8,9,6,5,3,7};
	int CatArray[] = {1, 0, 2, 8, 3, 7, 6, 9, 4, 5};
	BMenuItem* mi(m_popupmenu->ItemAt(CatArray[m_CurCat]));
	mi->SetMarked(true);
	RefreshList();
}


