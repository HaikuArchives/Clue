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

#ifndef _OBJECTFILTERVIEW_H
#include "ObjectFilterView.h"
#endif

#ifndef _OBJECTFILTER_ITEM_H
#include "ObjectFilterItem.h"
#endif

#ifndef _CAM_CONSTANTS_H
#include "CAM_Constants.h"
#endif

#ifndef _CREDITSVIEW_H
#include "CreditsView.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

extern volatile sem_id g_SettingsSemaphore;
extern BMessage g_Settings;

BListItem * (*eachFunc) (BListItem *, void *);




ObjectFilterView :: ObjectFilterView
	(
	BRect frame
	)
:	BView (frame, "ObjectFilter View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_PULSE_NEEDED)
,	m_btnClose (NULL)
,	m_outline (NULL)
{
	SetViewColor (CLR_BACKGROUND);

	frame.bottom -= 60.0f;
	frame.right -= B_V_SCROLL_BAR_WIDTH;
	m_outline = new BOutlineListView (frame, "objectfilter_list", B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL_SIDES);
	CreateList (m_outline);

	m_outline->SetSelectionMessage (new BMessage ('msel'));
	m_outline->SetInvocationMessage (new BMessage ('invo'));
	AddChild (new BScrollView ("scroll_objectfilter_items", m_outline, B_FOLLOW_ALL_SIDES, 0, false, true));

	frame.left = 15.0f;
	frame.top = frame.bottom + 15.0f;
//	frame.right = 50;
//	frame.bottom = 180;
	m_btnClose = static_cast<BButton *>(new BButton (frame, STR_CLOSE, STR_CLOSE, new BMessage (MSG_OK), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnClose->MakeDefault (true);
	AddChild (m_btnClose);

	m_btnEnableAll = static_cast<BButton *>(new BButton (frame, STR_ENABLE_ALL_SUBITEMS, STR_ENABLE_ALL_SUBITEMS, new BMessage ('enab'), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnEnableAll->SetEnabled (false);
	AddChild (m_btnEnableAll);

	m_btnDisableAll = static_cast<BButton *>(new BButton (frame, STR_DISABLE_ALL_SUBITEMS, STR_DISABLE_ALL_SUBITEMS, new BMessage ('disa'), B_FOLLOW_LEFT | B_FOLLOW_BOTTOM));
	m_btnDisableAll->SetEnabled (false);
	AddChild (m_btnDisableAll);
}


ObjectFilterView :: ~ObjectFilterView
	(
	void
	)
{
	ObjectFilterItem * pOFI (NULL);

	for (int32 i (m_outline->CountItems () - 1); i >= 0 ; i--)
	{
		pOFI = (ObjectFilterItem *) m_outline->RemoveItem (i);
		delete pOFI;
	}
}


/***************************************************************
***************************************************************/
void
ObjectFilterView :: MessageReceived
	(
	BMessage * msg
	)
{
	//put in most-frequent to less-frequent order for that little extra speed we all want!
	switch (msg->what)
	{
/*
		case 'msel':
			{
			BRect frame (Bounds ());
			frame.left = 200.0f + B_V_SCROLL_BAR_WIDTH + 10.0f;
			
			if (m_EditView)
			{
				m_EditView->Save ();
				PRINT (("EditView->Save\n"));
				m_EditView->RemoveSelf ();
				delete m_EditView;
				m_EditView = NULL;
			}

			int32 index (m_outline->CurrentSelection (0));
			if (index >= 0)
			{
				PRINT (("ItemSelected: index = %i\n", index));
				PreferenceItem * pi ((PreferenceItem *)m_outline->ItemAt (index));
				if (pi)
				{
					PRINT (("  pi was valid\n"));
					BMessage * pMsg (pi->GetMessage ());
					if (pMsg)
					{
						PRINT (("  pMsg was valid\n"));
						switch (pMsg->what)
						{
							case B_BOOL_TYPE:
								PRINT (("B_BOOL_TYPE\n"));
								//m_text->SetText ("B_BOOL_TYPE");
								m_EditView = (EditView *) new EditBoolView (frame, pMsg);
								m_EditView->SetLabel ("B_BOOL_TYPE");
								break;
							case 'team':
								PRINT (("team\n"));
								//m_text->SetText ("B_DOUBLE_TYPE");
								m_EditView = (EditView *) EditTeamView::Create (frame, pMsg);
								if (m_EditView)
								{
									PRINT (("\nm_EditView was valid\n\n"));
									m_EditView->SetLabel ("team");
								}
								else
								{
									PRINT (("\nm_EditView was INvalid\n\n"));
								}
								break;
							case B_RGB_COLOR_TYPE:
								PRINT (("B_RGB_COLOR_TYPE\n"));
								m_EditView = (EditView *) EditColorView::Create (frame, pMsg);
								if (m_EditView)
								{
									PRINT (("\nm_EditView was valid\n\n"));
									m_EditView->SetLabel ("B_RGB_COLOR_TYPE");
								}
								else
								{
									PRINT (("\nm_EditView was INvalid\n\n"));
								}
								break;
							case 'node':
								PRINT (("node\n"));
								//m_text->SetText ("a node");
								break;
							default:
								PRINT (("pMsg->what=%i\n", pMsg->what));
								//m_text->SetText ("testing");
								break;
						}
					}
					else
						DEBUGGER ("pMsg was NULL");
//						m_text->SetText ("pMsg was NULL");
				}
				else
					DEBUGGER ("PreferencesItem was NULL");
//					m_text->SetText ("PreferenceItem was NULL");
			}
			}
			
			if (m_EditView)
			{
				PRINT (("pEditView = %08x\n", m_EditView));
//				m_text->RemoveSelf ();
				AddChild (m_EditView);
			}
//			else
//			{
//				AddChild (m_text);
//			}
			break;
*/
		case 'enab':
			{
			int32 Index (m_outline->CurrentSelection ());
			if (Index >= 0)
			{
				ObjectFilterItem * OFI ((ObjectFilterItem *) m_outline->ItemAt (Index));
				if (OFI)
				{
					if ( ! OFI->IsLeafNode ())
					{
						m_outline->EachItemUnder ((BListItem *) OFI, false, Enable, (void *) m_outline);
//						if (OFI->ControlsSubItems ())
//						{
//							m_outline->EachItemUnder ((BListItem *) OFI, true, UnGrayOut, (void *) NULL);
//						}
						m_outline->Invalidate ();
					}
				}
			}
			}
			break;
		case 'disa':
			{
			int32 Index (m_outline->CurrentSelection ());
			if (Index >= 0)
			{
				ObjectFilterItem * OFI ((ObjectFilterItem *) m_outline->ItemAt (Index));
				if (OFI)
				{
					if ( ! OFI->IsLeafNode ())
					{
						m_outline->EachItemUnder ((BListItem *) OFI, false, Disable, (void *) m_outline);
						m_outline->Invalidate ();
					}
				}
			}
			}
			break;
		case 'msel':
			{
			int32 Index (0);
			if (B_OK == msg->FindInt32 ("index", &Index))
			{
				ObjectFilterItem * OFI ((ObjectFilterItem *) m_outline->ItemAt (Index));
				if (OFI)
				{
					bool rc ( ! OFI->IsLeafNode ());
					m_btnEnableAll->SetEnabled (rc);
					m_btnDisableAll->SetEnabled (rc);
					//m_outline->InvalidateItem (Index);
				}
			}
			}
			break;
		case 'invo':
			{
			int32 Index (0);
			if (B_OK == msg->FindInt32 ("index", &Index))
			{
				ObjectFilterItem * OFI ((ObjectFilterItem *) m_outline->ItemAt (Index));
				if (OFI)
				{
					bool rc (OFI->ToggleChecked ());
					if (OFI->ControlsSubItems ())
					{
						if (rc)
							m_outline->EachItemUnder ((BListItem *) OFI, true, UnGrayOut, (void *) NULL);
						else
							m_outline->EachItemUnder ((BListItem *) OFI, true, GrayOut, (void *) NULL);

						m_outline->Invalidate ();
					}
					else
						m_outline->InvalidateItem (Index);
				}
			}
			}
			break;
		case MSG_OK:
			Window()->PostMessage (B_QUIT_REQUESTED, Window ());
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

					m_btnClose->SetViewColor (CLR_BACKGROUND);
					m_btnClose->SetLowColor (CLR_BACKGROUND);
					m_btnClose->Invalidate ();

					m_outline->SetViewColor (CLR_LIST_BACKGROUND);
					m_outline->SetLowColor (CLR_LIST_BACKGROUND);
					m_outline->Invalidate ();
				}
				break;
			}
			}
			break;
		default:
			BView::MessageReceived (msg);
	}
}



void
ObjectFilterView :: CreateList
	(
	BOutlineListView * OLV
	)
{
//	ObjectFilterItem * itmOF (NULL);
	
	BListItem * itmEnum (NULL);
	BListItem * itmClass (NULL);
	BListItem * itmStruct (NULL);
	BListItem * itmObject (NULL);

	OLV->AddItem (itmClass = new ObjectFilterItem ("Class Category", false, 0, 0, false, 0, true));
//	OLV->AddItem (itmClass = new BStringItem ("Classes", 0, true));

	OLV->AddUnder (itmObject = new ObjectFilterItem ("BWindow"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BVolumeRoster"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BVolume"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BView", false, INDEX_BVIEW, MASK_BVIEW, true), itmClass);
//		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("Inspect this class", true, INDEX_BVIEW, MASK_BVIEW), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("Inspect base classes", true, INDEX_BVIEW, MASK_BVIEW_BASECLASSES), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call Bounds()", true, INDEX_BVIEW, MASK_BVIEW_BOUNDS), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("calls Flags()", true, INDEX_BVIEW, MASK_BVIEW_FLAGS), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call Frame()", true, INDEX_BVIEW, MASK_BVIEW_FRAME), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call IsFocus()", true, INDEX_BVIEW, MASK_BVIEW_ISFOCUS), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call IsHidden()", true, INDEX_BVIEW, MASK_BVIEW_ISHIDDEN), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call IsPrinting()", true, INDEX_BVIEW, MASK_BVIEW_ISPRINTING), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call Origin()", true, INDEX_BVIEW, MASK_BVIEW_ORIGIN), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call GetPreferredSize()", true, INDEX_BVIEW, MASK_BVIEW_GETPREFERREDSIZE), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call LineCapMode()", true, INDEX_BVIEW, MASK_BVIEW_LINECAPMODE), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call LineJoinMode()", true, INDEX_BVIEW, MASK_BVIEW_LINEJOINMODE), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call LineMiterLimit()", true, INDEX_BVIEW, MASK_BVIEW_LINEMITERLIMIT), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call PenLocation()", true, INDEX_BVIEW, MASK_BVIEW_PENLOCATION), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call PenSize()", true, INDEX_BVIEW, MASK_BVIEW_PENSIZE), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call HighColor()", true, INDEX_BVIEW, MASK_BVIEW_HIGHCOLOR), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call LowColor()", true, INDEX_BVIEW, MASK_BVIEW_LOWCOLOR), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call ViewColor()", true, INDEX_BVIEW, MASK_BVIEW_VIEWCOLOR), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call DrawingMode()", true, INDEX_BVIEW, MASK_BVIEW_DRAWINGMODE), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call GetFont()", true, INDEX_BVIEW, MASK_BVIEW_GETFONT), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("show BView heirerarchy", true, INDEX_BVIEW, MASK_BVIEW_HEIRARCHY), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call CountChildren()", true, INDEX_BVIEW, MASK_BVIEW_COUNTCHILDREN), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call EventMask()", true, INDEX_BVIEW, MASK_BVIEW_EVENTMASK), itmObject);
		OLV->AddUnder ((BListItem *) new ObjectFilterItem ("call Parent()", true, INDEX_BVIEW, MASK_BVIEW_PARENT), itmObject);
		if (! ((ObjectFilterItem *) itmObject)->IsChecked ())
		{
			m_outline->EachItemUnder (itmObject, true, GrayOut, (void *) NULL);
		}
	OLV->AddUnder (itmObject = new ObjectFilterItem ("unicode_block"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTranslatorRoster"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTranslator"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTimeSource"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTimedEventQueue"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTimeCode"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTextView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTextControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTabView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BTab"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSynth"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSymLink"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStringView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStringItem"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BString"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStreamingGameSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStopWatch"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStatusBar"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BStatable"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSoundPlayer"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSoundFile"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSmallBuffer"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSlider"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSimpleGameSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BShelf"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BShape"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSerialPort"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BScrollView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BScrollBar"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BScreen"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSamples"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BRoster"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BResources"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BResourceStrings"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BRegion"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BRect"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BRadioButton"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BQuery"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPushGameSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPropertyInfo"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPrintJob"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPopUpMenu"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPolygon"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPoint"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPictureButton"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPicture"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BParameterWeb"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BParameterGroup"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BParameter"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BPath"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BOutlineListView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BOptionPopUp"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BOptionControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BNullParameter"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BNodeInfo"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BNode"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMultiChannelControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMimeType"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidiText"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidiSynthFile"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidiSynth"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidiStore"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidiPort"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMidi"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMessenger"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMessageRunner"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMessageQueue"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMessageFilter"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMessage"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BSeparatorItem"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMenuItem"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMenuField"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMenuBar"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMenu"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaFormats"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaTrack"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaTheme"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaRoster"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaNode"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("media_node"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaFiles"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaFile"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMenuField"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaEventLooper"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaEncoder"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaDecoder"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BMediaAddOn"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BLooper"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BLocker"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BListView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BListItem"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BList"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BJoystick"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BInputDevice"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BInvoker"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BHandler"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BGLView"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BGameSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFont"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFileInterface"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFilePanel"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFileGameSound"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFile"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BFlattenable"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BEntryList"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BEntry"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BDragger"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BDirectWindow"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BDirectory"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BControllable"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BDiscreteParameter"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BContinuousParameter"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BColorControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BClipboard"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BCheckBox"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BChannelSlider"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BChannelControl"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BButton"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBufferProducer"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBufferGroup"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBufferConsumer"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBuffer"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBox"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBufferIO"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBitmapStream"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BBitmap"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BAutolock"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BApplication"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BAppFileInfo"), itmClass);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("BAlert"), itmClass);





	OLV->AddItem (itmEnum = new ObjectFilterItem ("Enums", false, 0, 0, false, 0, true));
//	OLV->AddItem (itmEnum = new BStringItem ("Enums", 0, true));
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("info_location", true, INDEX_ENUM_GROUP1, MASK_ENUM_INFO_LOCATION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("version_kind", true, INDEX_ENUM_GROUP1, MASK_ENUM_VERSION_KIND), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("swap_action", true, INDEX_ENUM_GROUP1, MASK_ENUM_SWAP_ACTION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("color_control_layout", true, INDEX_ENUM_GROUP1, MASK_ENUM_COLOR_CONTROL_LAYOUT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_parameter_flags", true, INDEX_ENUM_GROUP1, MASK_ENUM_MEDIA_PARAMETER_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("direct_buffer_state", true, INDEX_ENUM_GROUP1, MASK_ENUM_DIRECT_BUFFER_STATE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("direct_driver_state", true, INDEX_ENUM_GROUP1, MASK_ENUM_DIRECT_DRIVER_STATE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("mail_flags", true, INDEX_ENUM_GROUP1, MASK_ENUM_MAIL_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("file_panel_mode", true, INDEX_ENUM_GROUP1, MASK_ENUM_FILE_PANEL_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("file_panel_button", true, INDEX_ENUM_GROUP1, MASK_ENUM_FILE_PANEL_BUTTON), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("directory_which", true, INDEX_ENUM_GROUP1, MASK_ENUM_DIRECTORY_WHICH), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("font_direction", true, INDEX_ENUM_GROUP1, MASK_ENUM_FONT_DIRECTION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("font_metric_mode", true, INDEX_ENUM_GROUP1, MASK_ENUM_FONT_METRIC_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("font_file_format", true, INDEX_ENUM_GROUP1, MASK_ENUM_FONT_FILE_FORMAT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("gs_attributes", true, INDEX_ENUM_GROUP1, MASK_ENUM_GS_ATTRIBUTES), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("color_space", true, INDEX_ENUM_GROUP1, MASK_ENUM_COLOR_SPACE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("drawing_mode", true, INDEX_ENUM_GROUP1, MASK_ENUM_DRAWING_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("buffer_orientation", true, INDEX_ENUM_GROUP1, MASK_ENUM_BUFFER_ORIENTATION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("buffer_layout", true, INDEX_ENUM_GROUP1, MASK_ENUM_BUFFER_LAYOUT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("source_alpha", true, INDEX_ENUM_GROUP1, MASK_ENUM_SOURCE_ALPHA), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("alpha_function", true, INDEX_ENUM_GROUP1, MASK_ENUM_ALPHA_FUNCTION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("image_type", true, INDEX_ENUM_GROUP1, MASK_ENUM_IMAGE_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("input_method_op", true, INDEX_ENUM_GROUP1, MASK_ENUM_INPUT_METHOD_OP), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("input_device_type", true, INDEX_ENUM_GROUP1, MASK_ENUM_INPUT_DEVICE_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("input_device_notification", true, INDEX_ENUM_GROUP1, MASK_ENUM_INPUT_DEVICE_NOTIFICATION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("alignment", true, INDEX_ENUM_GROUP1, MASK_ENUM_ALIGNMENT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("join_mode", true, INDEX_ENUM_GROUP1, MASK_ENUM_JOIN_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("border_style", true, INDEX_ENUM_GROUP1, MASK_ENUM_BORDER_STYLE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("button_width", true, INDEX_ENUM_GROUP1, MASK_ENUM_BUTTON_WIDTH), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("cap_mode", true, INDEX_ENUM_GROUP1, MASK_ENUM_CAP_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("orientation", true, INDEX_ENUM_GROUP1, MASK_ENUM_ORIENTATION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("list_view_type", true, INDEX_ENUM_GROUP1, MASK_ENUM_LIST_VIEW_TYPE), itmEnum);
	
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_type", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("node_kind", true, INDEX_ENUM_GROUP2, MASK_ENUM_NODE_KIND), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("video_orientation", true, INDEX_ENUM_GROUP2, MASK_ENUM_VIDEO_ORIENTATION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_producer_status", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_PRODUCER_STATUS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_realtime_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_REALTIME_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_frame_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_FRAME_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_multi_channels", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_MULTI_CHANNELS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_multi_matrix", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_MULTI_MATRIX), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_display_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_DISPLAY_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_format_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_FORMAT_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_format_family", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_FORMAT_FAMILY), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_seek_type", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_SEEK_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("media_file_accept_format_flags", true, INDEX_ENUM_GROUP2, MASK_ENUM_MEDIA_FILE_ACCEPT_FORMAT_FLAGS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("mpeg_id", true, INDEX_ENUM_GROUP2, MASK_ENUM_MPEG_ID), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("menu_layout", true, INDEX_ENUM_GROUP2, MASK_ENUM_MENU_LAYOUT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("menu_bar_border", true, INDEX_ENUM_GROUP2, MASK_ENUM_MENU_BAR_BORDER), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("filter_result", true, INDEX_ENUM_GROUP2, MASK_ENUM_FILTER_RESULT), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("message_delivery", true, INDEX_ENUM_GROUP2, MASK_ENUM_MESSAGE_DELIVERY), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("message_source", true, INDEX_ENUM_GROUP2, MASK_ENUM_MESSAGE_SOURCE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("synth_mode", true, INDEX_ENUM_GROUP2, MASK_ENUM_SYNTH_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("midi_axe", true, INDEX_ENUM_GROUP2, MASK_ENUM_MIDI_AXE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("icon_size", true, INDEX_ENUM_GROUP2, MASK_ENUM_ICON_SIZE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("thread_state", true, INDEX_ENUM_GROUP2, MASK_ENUM_THREAD_STATE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("cpu_type", true, INDEX_ENUM_GROUP2, MASK_ENUM_CPU_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("value_kind", true, INDEX_ENUM_GROUP2, MASK_ENUM_VALUE_KIND), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("query_op", true, INDEX_ENUM_GROUP2, MASK_ENUM_QUERY_OP), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("data_rate", true, INDEX_ENUM_GROUP2, MASK_ENUM_DATA_RATE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("data_bits", true, INDEX_ENUM_GROUP2, MASK_ENUM_DATA_BITS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("stop_bits", true, INDEX_ENUM_GROUP2, MASK_ENUM_STOP_BITS), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("parity_mode", true, INDEX_ENUM_GROUP2, MASK_ENUM_PARITY_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("hash_mark_location", true, INDEX_ENUM_GROUP2, MASK_ENUM_HASH_MARK_LOCATION), itmEnum);
	
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("thumb_style", true, INDEX_ENUM_GROUP3, MASK_ENUM_THUMB_STYLE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("node_flavor", true, INDEX_ENUM_GROUP3, MASK_ENUM_NODE_FLAVOR), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("status_t", true, INDEX_ENUM_GROUP3, MASK_ENUM_STATUS_T), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("interpolation_mode", true, INDEX_ENUM_GROUP3, MASK_ENUM_INTERPOLATION_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("reverb_mode", true, INDEX_ENUM_GROUP3, MASK_ENUM_REVERB_MODE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("tab_position", true, INDEX_ENUM_GROUP3, MASK_ENUM_TAB_POSITION), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("undo_state", true, INDEX_ENUM_GROUP3, MASK_ENUM_UNDO_STATE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("timecode_type", true, INDEX_ENUM_GROUP3, MASK_ENUM_TIMECODE_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("B_TRANSLATION_ERROR", true, INDEX_ENUM_GROUP3, MASK_ENUM_B_TRANSLATION_ERROR), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("window_type", true, INDEX_ENUM_GROUP3, MASK_ENUM_WINDOW_TYPE), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("window_look", true, INDEX_ENUM_GROUP3, MASK_ENUM_WINDOW_LOOK), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("window_feel", true, INDEX_ENUM_GROUP3, MASK_ENUM_WINDOW_FEEL), itmEnum);
	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("window_alignment", true, INDEX_ENUM_GROUP3, MASK_ENUM_WINDOW_ALIGNMENT), itmEnum);







	OLV->AddItem (itmStruct = new ObjectFilterItem ("Structs", false, 0, 0, false, 0, true));
//	OLV->AddItem (itmStruct = new BStringItem ("Structs", 0, true));
//	OLV->AddUnder ((BListItem *) new ObjectFilterItem ("whatstruct", 0, 0), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorStyledTextStyleHeader", true), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorStyledTextTextHeader", true), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorStyledTextStreamHeader", true), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorStyledTextRecordHeader", true), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorSound", true), itmStruct);
	OLV->AddUnder (itmObject = new ObjectFilterItem ("TranslatorBitmap", true), itmStruct);
/*
	acquire_sem (g_SettingsSemaphore);

	for (int32 i (0); inMsg->GetInfo (B_STRING_TYPE, i, &name, &type, &count) == B_OK; i++)
	{
		PRINT (("name=%s;  i=%i;  count=%i\n", name, i, count));

		switch (inMsg->FindString (name, &str))
		{
		case B_OK:
			for (int32 j (0); j < count; j++)
			{
				PRINT (("j = %i\n", j));
				g_Settings.FindMessage (str.String(), &valBMessage);
				subitem = (PreferenceItem *) new PreferenceItem (str.String(), name);
				subitem->CopyMessage (&valBMessage);
				OLV->AddItem (subitem);
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
			PRINT (("\nB_BAD_INDEX\n"));
			break;
		case B_BAD_TYPE:
			PRINT (("\nB_BAD_TYPE\n"));
			break;
		case B_NAME_NOT_FOUND:
			PRINT (("\nB_NAME_NOT_FOUND\n"));
			break;
		default:
			PRINT (("\nother error\n"));
			break;
		}
	}

	release_sem (g_SettingsSemaphore);
*/
}


/***************************************************************
***************************************************************/
void
ObjectFilterView :: AllAttached
	(
	void
	)
{
	m_btnClose->ResizeToPreferred ();
	m_btnClose->SetTarget (this);
	BRect rc (m_btnClose->Frame ());

	m_btnEnableAll->ResizeToPreferred ();
	m_btnEnableAll->SetTarget (this);
	m_btnEnableAll->MoveTo (BPoint (rc.right + 20.0f, rc.top + 3.0F));
	rc = m_btnEnableAll->Frame ();

	m_btnDisableAll->ResizeToPreferred ();
	m_btnDisableAll->SetTarget (this);
	m_btnDisableAll->MoveTo (BPoint (rc.right + 20.0f, rc.top));

	m_outline->SetTarget (this);
	m_outline->MakeFocus ();

	BWindow * pwnd (Window ());
	if (pwnd)
	{
		((BHandler *)pwnd)->StartWatching ((BHandler *) this, MSG_SETTINGS_CHANGED);
	}
}


//void
//ObjectFilterView :: AttachedToWindow
//	(
//	void
//	)
//{
//	if (!m_AppStarting)
//	{
//		m_btnOK->MakeFocus (true);
//	}
//}


BListItem *
ObjectFilterView :: Disable
	(
	BListItem * item
,	void * data
	)
{
//	((ObjectFilterItem *) item)->SetChecked (false);
	ObjectFilterItem * OFI ((ObjectFilterItem *) item);
	OFI->SetChecked (false);
	if (OFI->ControlsSubItems ())
	{
		((BOutlineListView *) data)->EachItemUnder ((BListItem *) OFI, true, GrayOut, (void *) NULL);
	}
	return NULL;
}


BListItem *
ObjectFilterView :: Enable
	(
	BListItem * item
,	void * data
	)
{
	ObjectFilterItem * OFI ((ObjectFilterItem *) item);
	OFI->SetChecked (true);
	if (OFI->ControlsSubItems ())
	{
		((BOutlineListView *) data)->EachItemUnder ((BListItem *) OFI, true, UnGrayOut, (void *) NULL);
	}
	return NULL;
}


BListItem *
ObjectFilterView :: GrayOut
	(
	BListItem * item
,	void * data
	)
{
	((ObjectFilterItem *) item)->SetGrayed (true);
	return NULL;
}


BListItem *
ObjectFilterView :: UnGrayOut
	(
	BListItem * item
,	void * data
	)
{
	((ObjectFilterItem *) item)->SetGrayed (false);
	return NULL;
}



