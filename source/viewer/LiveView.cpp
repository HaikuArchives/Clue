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

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
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

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _ENTRY_H
#include <Entry.h>
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

#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif

#ifndef _LIST_ITEM_H
#include <ListView.h>
#endif

#ifndef _MENU_BAR_H
#include <MenuBar.h>
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

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _POP_UP_MENU_H
#include <PopUpMenu.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _TAB_VIEW_H
#include <TabView.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef ANIMATEDVIEW_H
#include "AnimatedView.h"
#endif

#ifndef _BITMAP_MENU_ITEM_H
#include "BitmapMenuItem.h"
#endif

#ifndef LIVEVIEW_H
#include "LiveView.h"
#endif

#ifndef _OBJECTFILTERWND_H
#include "ObjectFilterWnd.h"
#endif

#ifndef _BITMAPBUTTON_H
#include "BitmapButton.h"
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

#ifndef _CAM_CONSTANTS_H
#include "CAM_Constants.h"
#endif

#ifndef ACTIVEMENUITEM_H
#include "ActiveMenuItem.h"
#endif


//create instance of a ClueAreaManager
ClueAreaManager CAM;

extern BBitmap * g_bmpCategories[];
extern BBitmap * g_bmpEvents[];
extern BBitmap * g_Live;
//uint32 g_FilterMask = CT_CLASS_BIRTH | CT_CLASS_DEATH | CT_METHOD_ENTER | CT_METHOD_EXIT | CT_INFO | CT_WARNING | CT_ERROR;
extern rgb_color CLR_GENERAL_FOREGROUND;
extern BMessage g_Settings;

/***************************************************************
const declarations
***************************************************************/
static const int32 MSG_MENU_LIVE		= 'menu';
static const rgb_color kLight 			= {0, 215, 255, 255};
BPopUpMenu * menu						(NULL);

/***************************************************************
***************************************************************/
LiveView :: LiveView
	(
	BWindow * pWnd
,	BRect rcFrame
	)
:	BView (rcFrame, "LiveView", B_FOLLOW_TOP | B_FOLLOW_LEFT_RIGHT, B_FRAME_EVENTS | B_WILL_DRAW)
,	m_menufld (NULL)
,	m_popupmenu (NULL)
,	m_animation (NULL)
,	m_pObjectFilterWnd (NULL)
,	m_CurCat (CC_GENERAL)
{
	memset (CAM.m_data->m_mask, 0xffffffff, sizeof(uint32) * 100);

	BMessage tmpmsg;
	if (B_OK == g_Settings.FindMessage ("VIEW:LiveView", &tmpmsg))
	{
		tmpmsg.FindInt32 ("CC_GENERAL", (int32 *) &(CAM.m_data->m_mask[CC_GENERAL]));
		tmpmsg.FindInt32 ("CC_APPLICATION", (int32 *) &(CAM.m_data->m_mask[CC_APPLICATION]));
		tmpmsg.FindInt32 ("CC_INTERFACE", (int32 *) &(CAM.m_data->m_mask[CC_INTERFACE]));
		tmpmsg.FindInt32 ("CC_MEDIA", (int32 *) &(CAM.m_data->m_mask[CC_MEDIA]));
		tmpmsg.FindInt32 ("CC_STORAGE", (int32 *) &(CAM.m_data->m_mask[CC_STORAGE]));
		tmpmsg.FindInt32 ("CC_SUPPORT", (int32 *) &(CAM.m_data->m_mask[CC_SUPPORT]));
		tmpmsg.FindInt32 ("CC_NETWORK", (int32 *) &(CAM.m_data->m_mask[CC_NETWORK]));
		tmpmsg.FindInt32 ("CC_MOUSE", (int32 *) &(CAM.m_data->m_mask[CC_MOUSE]));
		tmpmsg.FindInt32 ("CC_KEYBOARD", (int32 *) &(CAM.m_data->m_mask[CC_KEYBOARD]));
		tmpmsg.FindInt32 ("CC_PRINTING", (int32 *) &(CAM.m_data->m_mask[CC_PRINTING]));
		tmpmsg.FindInt32 ("Selected Category", (int32 *) &m_CurCat);
	}

	BRect rc (Bounds ());

	SetViewColor (CLR_FOREGROUND);
	
	m_animation = new AnimatedView (BPoint (5.0f, 5.0f), "Animate Events");
	AddChild (m_animation);
	rc = m_animation->Frame ();

	m_VCRBitmaps[0] = RetrieveBitmap ("Go");
	m_VCRBitmaps[1] = RetrieveBitmap ("Stop");
	TransparentSetBits (m_VCRBitmaps[0], 255, 128, 192);
	TransparentSetBits (m_VCRBitmaps[1], 255, 128, 192);

	m_VCRButtons[0] = new BitmapButton (BPoint (rc.right + 15.0f, 5.0f), m_VCRBitmaps[0],
		new BMessage (MSG_MENU_FILE_START), STR_STATUS_START, STR_MNU_FILE_START);
	m_VCRButtons[0]->SetValue (B_CONTROL_OFF);
	AddChild (m_VCRButtons[0]);
	rc = m_VCRButtons[0]->Frame ();

	m_VCRButtons[1] = new BitmapButton (BPoint (rc.Width() + rc.left + 5.0f, 5.0f), m_VCRBitmaps[1],
		new BMessage (MSG_MENU_FILE_STOP), STR_STATUS_STOP, STR_MNU_FILE_STOP);
	m_VCRButtons[1]->SetValue (B_CONTROL_ON);
	m_VCRButtons[1]->SetEnabled (false);
	AddChild (m_VCRButtons[1]);
	rc = m_VCRButtons[1]->Frame ();

	CreatePopupMenu (pWnd);

	float width1 (StringWidth (STR_CATEGORIES) + 4.0f);
	rc.left = rc.right + 15.0f;
	rc.top = 5.0f;
	rc.right = rc.left + width1 + StringWidth (STR_CATEGORY_APPLICATION) + 24.0;
	m_menufld = (BMenuField *) new BMenuField (rc, STR_CATEGORIES, STR_CATEGORIES, m_popupmenu);
	AddChild (m_menufld);
	m_menufld->SetDivider (width1);

	CreateButtons (rc);
	
	rc = m_BmpButtons[11]->Frame();
	rc.left += rc.Width() + 14.0f;
	rc.right += 28.0f;
	m_ObjectFilter = new BButton (rc,"object_filter", "TRACE_OBJECT Filter ...", new BMessage ('obfl'));
	AddChild (m_ObjectFilter);










/*
	BMenuItem * mi (NULL);
	BMenu * BMenum (NULL);
	BMenu * BMclass (NULL);
	BMenu * BMstruct (NULL);
	BMessage * MenuMsg (NULL);

	BPopUpMenu * PMenu = (BPopUpMenu *) new BPopUpMenu (STR_CATEGORIES);

	BMenum = new BMenu ("Enums");

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("abc", MenuMsg);
	BMenum->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("jkl", MenuMsg);
	BMenum->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("xyz", MenuMsg);
	BMenum->AddItem (mi);

	mi = new BMenuItem (BMenum);
	PMenu->AddItem (mi);


	BMclass = new BMenu ("Classes");

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("abc", MenuMsg);
	BMclass->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("jkl", MenuMsg);
	BMclass->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("xyz", MenuMsg);
	BMclass->AddItem (mi);

	mi = new BMenuItem (BMclass);
	PMenu->AddItem (mi);


	BMstruct = new BMenu ("Structs");

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("abc", MenuMsg);
	BMstruct->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("jkl", MenuMsg);
	BMstruct->AddItem (mi);

	MenuMsg = new BMessage (MSG_CATEGORY_CHANGED);
	mi = new BMenuItem ("xyz", MenuMsg);
	BMstruct->AddItem (mi);

	mi = new BMenuItem (BMstruct);
	PMenu->AddItem (mi);



	rc = m_ObjectFilter->Frame();
	rc.left += rc.Width() + 14.0f;
	rc.right = rc.left + 100.0f;
	BMenuField * menufld = (BMenuField *) new BMenuField (rc, STR_CATEGORIES, STR_CATEGORIES, PMenu);
	AddChild (menufld);
*/








	rc = m_animation->Frame ();
	ResizeTo (rcFrame.right, rc.bottom + 5.0f);
	RefreshButtons ();
}


void
LiveView :: CreatePopupMenu
	(
	BWindow * pWnd
	)
{
	BMenuItem * mi (NULL);
	BMessage * msg (NULL);

	m_popupmenu = (BPopUpMenu *) new BPopUpMenu (STR_CATEGORIES);
	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_APPLICATION);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[1], STR_CATEGORY_APPLICATION, STR_STATUS_APPLICATION_CATEGORY, msg);
	if (CC_APPLICATION == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_GENERAL);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[0], STR_CATEGORY_GENERAL, STR_STATUS_GENERAL_CATEGORY, msg);
	if (CC_GENERAL == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_INTERFACE);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[2], STR_CATEGORY_INTERFACE, STR_STATUS_INTERFACE_CATEGORY, msg);
	if (CC_INTERFACE == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_KEYBOARD);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[8], STR_CATEGORY_KEYBOARD, STR_STATUS_KEYBOARD_CATEGORY, msg);
	if (CC_KEYBOARD == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_MEDIA);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[3], STR_CATEGORY_MEDIA, STR_STATUS_MEDIA_CATEGORY, msg);
	if (CC_MEDIA == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_MOUSE);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[7], STR_CATEGORY_MOUSE, STR_STATUS_MOUSE_CATEGORY, msg);
	if (CC_MOUSE == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_NETWORK);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[6], STR_CATEGORY_NETWORK, STR_STATUS_NETWORK_CATEGORY, msg);
	if (CC_NETWORK == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_PRINTING);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[9], STR_CATEGORY_PRINTING, STR_STATUS_PRINTING_CATEGORY, msg);
	if (CC_PRINTING == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_STORAGE);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[4], STR_CATEGORY_STORAGE, STR_STATUS_STORAGE_CATEGORY, msg);
	if (CC_STORAGE == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	msg = new BMessage (MSG_CATEGORY_CHANGED);
	msg->AddInt32 ("Category", CC_SUPPORT);
	mi = new BitmapMenuItem (pWnd, g_bmpCategories[5], STR_CATEGORY_SUPPORT, STR_STATUS_SUPPORT_CATEGORY, msg);
	if (CC_SUPPORT == m_CurCat)
	{
		mi->SetMarked (true);
	}
	m_popupmenu->AddItem (mi);

	m_popupmenu->AddSeparatorItem ();

	ActiveMenuItem * pAMI (NULL);
	pAMI = new ActiveMenuItem (pWnd, STR_SEL_ALL_CAT_ALL_EVT, STR_STATUS_SELECT_ALL_EVENTS_ALL_CATEGORIES,
		new BMessage (MSG_MENU_SEL_ALL_CAT_ALL_EVT));
	m_popupmenu->AddItem (pAMI);

	pAMI = new ActiveMenuItem (pWnd, STR_SEL_CUR_CAT_ALL_EVT, STR_STATUS_SELECT_ALL_EVENTS_CUR_CATEGORY,
		new BMessage (MSG_MENU_SEL_CUR_CAT_ALL_EVT));
	m_popupmenu->AddItem (pAMI);

	m_popupmenu->AddSeparatorItem ();

	pAMI = new ActiveMenuItem (pWnd, STR_USEL_ALL_CAT_ALL_EVT, STR_STATUS_UNSELECT_ALL_EVENTS_ALL_CATEGORIES,
		new BMessage (MSG_MENU_USEL_ALL_CAT_ALL_EVT));
	m_popupmenu->AddItem (pAMI);

	pAMI = new ActiveMenuItem (pWnd, STR_USEL_CUR_CAT_ALL_EVT, STR_STATUS_UNSELECT_ALL_EVENTS_CUR_CATEGORY,
		new BMessage (MSG_MENU_USEL_CUR_CAT_ALL_EVT));
	m_popupmenu->AddItem (pAMI);
}


void
LiveView :: CreateButtons
	(
	BRect rc
	)
{
	BMessage * msg (NULL);

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event",  CE_BIRTH);
	msg->AddInt32 ("ButtonID", 0);
	m_BmpButtons[0] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[0], msg, STR_STATUS_FILTER_CLASS_BIRTH, "CE_BIRTH");
	AddChild (m_BmpButtons[0]);
	rc = m_BmpButtons[0]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_DEATH);
	msg->AddInt32 ("ButtonID", 1);
	m_BmpButtons[1] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[1], msg, STR_STATUS_FILTER_CLASS_DEATH, "CE_DEATH");
	AddChild (m_BmpButtons[1]);
	rc = m_BmpButtons[1]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_ENTER);
	msg->AddInt32 ("ButtonID", 2);
	m_BmpButtons[2] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[2], msg, STR_STATUS_FILTER_METHOD_ENTER, "CE_ENTER");
	AddChild (m_BmpButtons[2]);
	rc = m_BmpButtons[2]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_EXIT);
	msg->AddInt32 ("ButtonID", 3);
	m_BmpButtons[3] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[3], msg, STR_STATUS_FILTER_METHOD_EXIT, "CE_EXIT");
	AddChild (m_BmpButtons[3]);
	rc = m_BmpButtons[3]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_OK);
	msg->AddInt32 ("ButtonID", 4);
	m_BmpButtons[4] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[4], msg, STR_STATUS_FILTER_OK, "CE_OK");
	AddChild (m_BmpButtons[4]);
	rc = m_BmpButtons[4]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_INFO);
	msg->AddInt32 ("ButtonID", 5);
	m_BmpButtons[5] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[5], msg, STR_STATUS_FILTER_INFO, "CE_INFO");
	AddChild (m_BmpButtons[5]);
	rc = m_BmpButtons[5]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_WARNING);
	msg->AddInt32 ("ButtonID", 6);
	m_BmpButtons[6] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[6], msg, STR_STATUS_FILTER_WARNING, "CE_WARNING");
	AddChild (m_BmpButtons[6]);
	rc = m_BmpButtons[6]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_ERROR);
	msg->AddInt32 ("ButtonID", 7);
	m_BmpButtons[7] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[7], msg, STR_STATUS_FILTER_ERROR, "CE_ERROR");
	AddChild (m_BmpButtons[7]);
	rc = m_BmpButtons[7]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_SUCCEEDED);
	msg->AddInt32 ("ButtonID", 8);
	m_BmpButtons[8] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[8], msg, STR_STATUS_FILTER_SUCCEEDED, "CE_SUCCEEDED");
	AddChild (m_BmpButtons[8]);
	rc = m_BmpButtons[8]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_FAILED);
	msg->AddInt32 ("ButtonID", 9);
	m_BmpButtons[9] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[9], msg, STR_STATUS_FILTER_FAILED, "CE_FAILED");
	AddChild (m_BmpButtons[9]);
	rc = m_BmpButtons[9]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_TIMER);
	msg->AddInt32 ("ButtonID", 10);
	m_BmpButtons[10] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[10], msg, STR_STATUS_FILTER_TIMER, "CE_TIMER");
	AddChild (m_BmpButtons[10]);
	rc = m_BmpButtons[10]->Frame ();

	msg = new BMessage (MSG_EVENT_MASK_CHANGED);
	msg->AddInt32 ("Event", CE_OBJECT);
	msg->AddInt32 ("ButtonID", 11);
	m_BmpButtons[11] = new BitmapButton (BPoint (rc.Width () + rc.left + 5.0f, 5.0f),
		g_bmpEvents[11], msg, STR_STATUS_FILTER_OBJECT, "CE_OBJECT");
	AddChild (m_BmpButtons[11]);
}


/***************************************************************
***************************************************************/
LiveView :: ~LiveView
	(
	void
	)
{
	BMessage msgNewData ('mask');
	msgNewData.AddInt32 ("CC_GENERAL", CAM.m_data->m_mask[CC_GENERAL]);
	msgNewData.AddInt32 ("CC_APPLICATION", CAM.m_data->m_mask[CC_APPLICATION]);
	msgNewData.AddInt32 ("CC_INTERFACE", CAM.m_data->m_mask[CC_INTERFACE]);
	msgNewData.AddInt32 ("CC_MEDIA", CAM.m_data->m_mask[CC_MEDIA]);
	msgNewData.AddInt32 ("CC_STORAGE", CAM.m_data->m_mask[CC_STORAGE]);
	msgNewData.AddInt32 ("CC_SUPPORT", CAM.m_data->m_mask[CC_SUPPORT]);
	msgNewData.AddInt32 ("CC_NETWORK", CAM.m_data->m_mask[CC_NETWORK]);
	msgNewData.AddInt32 ("CC_MOUSE", CAM.m_data->m_mask[CC_MOUSE]);
	msgNewData.AddInt32 ("CC_KEYBOARD", CAM.m_data->m_mask[CC_KEYBOARD]);
	msgNewData.AddInt32 ("CC_PRINTING", CAM.m_data->m_mask[CC_PRINTING]);
	msgNewData.AddInt32 ("Selected Category", m_CurCat);

	BMessage msgtmp ('mask');
	if (B_OK == g_Settings.FindMessage ("VIEW:LiveView", &msgtmp))
	{
		g_Settings.ReplaceMessage ("VIEW:LiveView", &msgNewData);
	}
	else
	{
		g_Settings.AddMessage ("VIEW:LiveView", &msgNewData);
	}

	Listen (false);
	delete m_VCRBitmaps[0];
	delete m_VCRBitmaps[1];
}


/***************************************************************
***************************************************************/
void
LiveView :: MessageReceived
	(
	BMessage * msg
	)
{
	switch (msg->what)
	{
		case MSG_CATEGORY_CHANGED:
			CategoryChanged (msg);
			break;
		case MSG_EVENT_MASK_CHANGED:
			EventMaskChanged (msg);
			break;
		case MSG_MENU_SEL_ALL_CAT_ALL_EVT:
			SelectUnselect (true, false);
			break;
		case MSG_MENU_USEL_ALL_CAT_ALL_EVT:
			SelectUnselect (false, false);
			break;
		case MSG_MENU_SEL_CUR_CAT_ALL_EVT:
			SelectUnselect (true, true);
			break;
		case MSG_MENU_USEL_CUR_CAT_ALL_EVT:
			SelectUnselect (false, true);
			break;
case 'obfl':
	{
//	BAlert *myAlert = new BAlert("Some Information message", "Object Filter button was clicked", 
//		"OK", NULL, NULL, B_WIDTH_AS_USUAL, B_INFO_ALERT);
//	myAlert->Go (NULL);
			if (NULL == m_pObjectFilterWnd)
			{
				m_pObjectFilterWnd = new ObjectFilterWnd (&m_pObjectFilterWnd);
			}
			else
			{
				m_pObjectFilterWnd->Lock ();
				m_pObjectFilterWnd->Activate ();
				m_pObjectFilterWnd->Unlock ();
			}
			break;
	}
		case B_OBSERVER_NOTICE_CHANGE:
			{
			uint32 change (0);
			msg->FindInt32(B_OBSERVE_WHAT_CHANGE, (int32 *) &change);
			switch (change)
			{
			case MSG_SETTINGS_CHANGED:
				{
					SetViewColor (CLR_FOREGROUND);
					SetLowColor (CLR_FOREGROUND);
					Invalidate ();

					m_animation->SetViewColor (CLR_FOREGROUND);
					m_animation->SetLowColor (CLR_FOREGROUND);
					m_animation->Invalidate ();

					for (int i (0); i < 12; i++)
					{
						m_BmpButtons[i]->SetViewColor (CLR_FOREGROUND);
						m_BmpButtons[i]->SetLowColor (CLR_FOREGROUND);
						m_BmpButtons[i]->Invalidate ();
					}

					m_VCRButtons[0]->SetViewColor (CLR_FOREGROUND);
					m_VCRButtons[0]->SetLowColor (CLR_FOREGROUND);
					m_VCRButtons[0]->Invalidate ();

					m_VCRButtons[1]->SetViewColor (CLR_FOREGROUND);
					m_VCRButtons[1]->SetLowColor (CLR_FOREGROUND);
					m_VCRButtons[1]->Invalidate ();

					m_menufld->SetViewColor (CLR_FOREGROUND);
					m_menufld->SetLowColor (CLR_FOREGROUND);
					m_menufld->Invalidate ();
				}
				break;
			}
			}
			break;
		default:
			BView::MessageReceived (msg);
	}
}


/***************************************************************
***************************************************************/
void
LiveView :: SelectUnselect
	(
	bool select
,	bool CurrentCategoryOnly
	)
{
	if (CurrentCategoryOnly)
	{
		CAM.m_data->m_mask[m_CurCat] = select ? 0xFFFFFFFF : 0x00000000;
	}
	else //all categories, all events are Selected or Unselected
	{
		for (int i (0); i < 10; i++)
		{
			CAM.m_data->m_mask[i] = select ? 0xFFFFFFFF : 0x00000000;
		}
	}

	//because the ClueCategory listing isn't in the same order as the menu, need this array for indexing
	int CatArray[] = {1,0,2,4,8,9,6,5,3,7};
	BMenuItem * mi (m_popupmenu->ItemAt (CatArray[m_CurCat]));
	mi->SetMarked (true);
	RefreshButtons ();
}


/***************************************************************
***************************************************************/
void
LiveView :: AllAttached
	(
	void
	)
{
	PRINT (("AllAttached\n"));
	for (int i = 0; i < 12; m_BmpButtons[i++]->SetTarget (this));
	m_popupmenu->SetTargetForItems (this);
	((BHandler *)Window ())->StartWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
//	menu->SetTargetForItems (this);
	//float w (0.0f);
	//float h (0.0f);
	m_ObjectFilter->ResizeToPreferred ();
	m_ObjectFilter->SetTarget (this);
	m_ObjectFilter->SetViewColor (CLR_FOREGROUND);
	m_ObjectFilter->SetLowColor (CLR_FOREGROUND);
}



/***************************************************************
***************************************************************/
void
LiveView :: Draw
	(
	BRect updateRect
	)
{
	BRect rc (Bounds ());
	float L (rc.left);
	float T (rc.top);
	float R (rc.right);
	float B (rc.bottom);
	
	//draw the border at the bottom of the view
	SetHighColor (CLR_FOREGROUND_DARK);
	StrokeLine (BPoint (L, B - 1.0), BPoint (R, B - 1.0));
//	StrokeLine (BPoint (updateRect.left, rc.bottom - 1.0), BPoint (updateRect.right, rc.bottom - 1.0));
	SetHighColor (CLR_BACKGROUND_LITE);
	StrokeLine (BPoint (L, B), BPoint (R, B));
//	StrokeLine (BPoint (updateRect.left, rc.bottom), BPoint (updateRect.right, rc.bottom));

	//draw first vertical separator line
	R = m_animation->Frame ().right;
//	rc.right = m_animation->Frame ().right;
	SetHighColor (CLR_FOREGROUND_DARK);
	StrokeLine (BPoint (R + 7.0f, B - 1.0f), BPoint (R + 7.0f, T));
//	StrokeLine (BPoint (rc.right + 7.0f, rc.bottom - 1.0f), BPoint (rc.right + 7.0f, rc.top));
	SetHighColor (CLR_FOREGROUND_LITE);
	StrokeLine (BPoint (R + 8.0f, B - 1.0f), BPoint (R + 8.0f, T));
//	StrokeLine (BPoint (rc.right + 8.0f, rc.bottom - 1.0f), BPoint (rc.right + 8.0f, rc.top));

	//draw second vertical separator line
	R = m_VCRButtons[1]->Frame ().right;
//	rc.right = m_VCRButtons[1]->Frame ().right;
	SetHighColor (CLR_FOREGROUND_DARK);
	StrokeLine (BPoint (R + 7.0f, B - 1.0f), BPoint (R + 7.0f, T));
//	StrokeLine (BPoint (rc.right + 7.0f, rc.bottom - 1.0f), BPoint (rc.right + 7.0f, rc.top));
	SetHighColor (CLR_FOREGROUND_LITE);
	StrokeLine (BPoint (R + 8.0f, B - 1.0f), BPoint (R + 8.0f, T));
//	StrokeLine (BPoint (rc.right + 8.0f, rc.bottom - 1.0f), BPoint (rc.right + 8.0f, rc.top));

	//draw third vertical separator line
	R = m_BmpButtons[11]->Frame().right;
//	rc.right = m_VCRButtons[1]->Frame ().right;
	SetHighColor (CLR_FOREGROUND_DARK);
	StrokeLine (BPoint (R + 7.0f, B - 1.0f), BPoint (R + 7.0f, T));
//	StrokeLine (BPoint (rc.right + 7.0f, rc.bottom - 1.0f), BPoint (rc.right + 7.0f, rc.top));
	SetHighColor (CLR_FOREGROUND_LITE);
	StrokeLine (BPoint (R + 8.0f, B - 1.0f), BPoint (R + 8.0f, T));
//	StrokeLine (BPoint (rc.right + 8.0f, rc.bottom - 1.0f), BPoint (rc.right + 8.0f, rc.top));
}


/*************************************************************************
	PREREQUISITS: view should be attached before calling
*************************************************************************/
void
LiveView :: Listen
	(
	bool listen
	)
{
	m_animation->Enabled (listen);
	if (listen)
	{
		m_VCRButtons[0]->SetEnabled (false);
		m_VCRButtons[0]->SetValue (B_CONTROL_ON);
		m_VCRButtons[1]->SetEnabled (true);
		m_VCRButtons[1]->SetValue (B_CONTROL_OFF);

CAM.m_data->m_mask[INDEX_BVIEW] = MASK_BVIEW | MASK_BVIEW_BOUNDS | MASK_BVIEW_FLAGS |
	MASK_BVIEW_FRAME | MASK_BVIEW_ISFOCUS | MASK_BVIEW_ISHIDDEN | MASK_BVIEW_ISPRINTING | 
	MASK_BVIEW_ORIGIN | MASK_BVIEW_GETPREFERREDSIZE | MASK_BVIEW_LINECAPMODE | 
	MASK_BVIEW_LINEJOINMODE | MASK_BVIEW_LINEMITERLIMIT | MASK_BVIEW_PENLOCATION | 
	MASK_BVIEW_PENSIZE | MASK_BVIEW_HIGHCOLOR | MASK_BVIEW_LOWCOLOR | MASK_BVIEW_VIEWCOLOR | 
	MASK_BVIEW_DRAWINGMODE | MASK_BVIEW_GETFONT | MASK_BVIEW_HEIRARCHY | MASK_BVIEW_COUNTCHILDREN | 
	MASK_BVIEW_EVENTMASK | MASK_BVIEW_PARENT | MASK_BVIEW_BASECLASSES;
	}
	else
	{
		m_VCRButtons[0]->SetEnabled (true);
		m_VCRButtons[0]->SetValue (B_CONTROL_OFF);
		m_VCRButtons[1]->SetEnabled (false);
		m_VCRButtons[1]->SetValue (B_CONTROL_ON);
	}
}


/***************************************************************
***************************************************************/
void
LiveView :: RefreshButtons
	(
	void
	)
{
	m_BmpButtons[0]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_BIRTH		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[1]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_DEATH		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[2]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_ENTER		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[3]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_EXIT		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[4]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_OK			? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[5]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_INFO		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[6]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_WARNING	? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[7]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_ERROR		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[8]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_SUCCEEDED	? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[9]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_FAILED		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[10]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_TIMER		? B_CONTROL_ON : B_CONTROL_OFF);
	m_BmpButtons[11]->SetValue (CAM.m_data->m_mask[m_CurCat] & CE_OBJECT	? B_CONTROL_ON : B_CONTROL_OFF);
}


/***************************************************************
***************************************************************/
void
LiveView :: CategoryChanged
	(
	BMessage * msg
	)
{
	ClueCategory cc (CC_GENERAL);
	if (B_OK == msg->FindInt32 ("Category", (int32 *) &cc))
	{
		m_CurCat = cc;
		RefreshButtons ();
	}
}


/***************************************************************
***************************************************************/
void
LiveView :: EventMaskChanged
	(
	BMessage * msg
	)
{
	int32 index (0);
	ClueEvent ce (CE_OK);
	if ((B_OK == msg->FindInt32 ("Event", (int32 *) &ce)) && (B_OK == msg->FindInt32 ("ButtonID", (int32 *) &index)))
	{
		int32 mousebtn (B_PRIMARY_MOUSE_BUTTON);
		msg->FindInt32 ("buttons", (int32 *) &mousebtn);
		
		if (B_PRIMARY_MOUSE_BUTTON == mousebtn)
		{
			if (B_CONTROL_ON == m_BmpButtons[index]->Value ())
			{
				CAM.m_data->m_mask[m_CurCat] = CAM.m_data->m_mask[m_CurCat] | ce;
			}
			else
			{
				CAM.m_data->m_mask[m_CurCat] = CAM.m_data->m_mask[m_CurCat] & ~ce;
			}
			PRINT (("CAM.m_data->mask = %x\n", CAM.m_data->m_mask[m_CurCat]));
		}
		else
		{
			if (B_CONTROL_ON == m_BmpButtons[index]->Value ())
			{
				CAM.m_data->m_mask[0] = CAM.m_data->m_mask[0] | ce;
				CAM.m_data->m_mask[1] = CAM.m_data->m_mask[1] | ce;
				CAM.m_data->m_mask[2] = CAM.m_data->m_mask[2] | ce;
				CAM.m_data->m_mask[3] = CAM.m_data->m_mask[3] | ce;
				CAM.m_data->m_mask[4] = CAM.m_data->m_mask[4] | ce;
				CAM.m_data->m_mask[5] = CAM.m_data->m_mask[5] | ce;
				CAM.m_data->m_mask[6] = CAM.m_data->m_mask[6] | ce;
				CAM.m_data->m_mask[7] = CAM.m_data->m_mask[7] | ce;
				CAM.m_data->m_mask[8] = CAM.m_data->m_mask[8] | ce;
				CAM.m_data->m_mask[9] = CAM.m_data->m_mask[9] | ce;
				CAM.m_data->m_mask[10] = CAM.m_data->m_mask[10] | ce;
				CAM.m_data->m_mask[11] = CAM.m_data->m_mask[11] | ce;
			}
			else
			{
				CAM.m_data->m_mask[0] = CAM.m_data->m_mask[0] & ~ce;
				CAM.m_data->m_mask[1] = CAM.m_data->m_mask[1] & ~ce;
				CAM.m_data->m_mask[2] = CAM.m_data->m_mask[2] & ~ce;
				CAM.m_data->m_mask[3] = CAM.m_data->m_mask[3] & ~ce;
				CAM.m_data->m_mask[4] = CAM.m_data->m_mask[4] & ~ce;
				CAM.m_data->m_mask[5] = CAM.m_data->m_mask[5] & ~ce;
				CAM.m_data->m_mask[6] = CAM.m_data->m_mask[6] & ~ce;
				CAM.m_data->m_mask[7] = CAM.m_data->m_mask[7] & ~ce;
				CAM.m_data->m_mask[8] = CAM.m_data->m_mask[8] & ~ce;
				CAM.m_data->m_mask[9] = CAM.m_data->m_mask[9] & ~ce;
				CAM.m_data->m_mask[10] = CAM.m_data->m_mask[10] & ~ce;
				CAM.m_data->m_mask[11] = CAM.m_data->m_mask[11] & ~ce;
			}
		}
	}
}

