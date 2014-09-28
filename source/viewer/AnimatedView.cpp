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

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _MESSAGE_RUNNER_H
#include <MessageRunner.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef ANIMATEDVIEW_H
#include "AnimatedView.h"
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif

extern BBitmap * g_bmpEvents[];

/***************************************************************
globals
***************************************************************/
const uint32 MSG_SPRITE_TIMER = 'timr';


/***************************************************************
***************************************************************/
AnimatedView :: AnimatedView
	(
	BPoint pt
,	const char * name
	)
:	BView (BRect (pt.x, pt.y, pt.x + 31, pt.y + 36), name, B_FOLLOW_NONE, B_WILL_DRAW)
,	m_pMsgRunner (NULL)
,	m_fOffset (0.0)
,	m_pbmpStrip (NULL)
,	m_pbmpMagnify (NULL)
,	m_pbmpWorkBitmap (NULL)
,	m_pWorkView (NULL)
,	m_bRunning (false)
{
	BRect rc (0.0f, 0.0f, 15.0f, 12.0f * 16.0f - 1.0f);
	BBitmap * tempbmp (new BBitmap (rc, B_RGB32, true));
	BView * tempview (new BView (rc, "tempview", B_FOLLOW_NONE, 0));
	tempbmp->Lock ();
	tempbmp->AddChild (tempview);
//	for (int i = 0; i < 12; i++)
	for (int i (11), y (0); i >= 0; --i, ++y)
	{
		tempview->DrawBitmapAsync (g_bmpEvents[i], BPoint (0.0f, y * 16.0f));
	}
	tempview->Sync ();
	tempbmp->Unlock ();
	m_pbmpStrip = new BBitmap (tempbmp);
	delete tempbmp;
	//don't need to delete tempview as the BBitmaps BWindow should take care of that!

	BView::SetViewColor (B_TRANSPARENT_32_BIT);

	m_pbmpMagnify = RetrieveBitmap ("Magnify");
	TransparentSetBits (m_pbmpMagnify, 255, 128, 192);

	m_pbmpWorkBitmap = new BBitmap (Bounds (), B_RGB32, true);
	m_pWorkView = new BView (Bounds (), "WorkView", B_FOLLOW_NONE, 0);
	m_pWorkView->SetDrawingMode (B_OP_ALPHA);
	m_pWorkView->SetBlendingMode (B_CONSTANT_ALPHA, B_ALPHA_OVERLAY);
	m_pbmpWorkBitmap->Lock ();
	m_pbmpWorkBitmap->AddChild (m_pWorkView);
	m_pbmpWorkBitmap->Unlock ();
	m_fOffset = - (m_pbmpStrip->Bounds().bottom + 1.0);
}


/***************************************************************
***************************************************************/
AnimatedView :: ~AnimatedView
	(
	void
	)
{
	if (m_pMsgRunner)
	{
		delete m_pMsgRunner;
		m_pMsgRunner = NULL;
	}
	
	delete m_pbmpStrip;
	m_pbmpStrip = NULL;
	delete m_pbmpMagnify;
	m_pbmpMagnify = NULL;
	delete m_pbmpWorkBitmap;
	m_pbmpWorkBitmap = NULL;
}


/***************************************************************
***************************************************************/
void
AnimatedView :: Draw
	(
	BRect updateRect
	)
{
	DrawSprite ();
}


/***************************************************************
***************************************************************/
void
AnimatedView :: MessageReceived
	(
	BMessage * msg
	)
{
	if (MSG_SPRITE_TIMER == msg->what)
	{
		DrawSprite ();
		m_fOffset += 3;
		if (m_fOffset > Bounds().bottom)
		{
			m_fOffset = - (m_pbmpStrip->Bounds().bottom + 1.0);
		}
	}
	else
	{
		BView::MessageReceived (msg);
	}
/*
	switch (msg->what)
	{
		case MSG_SPRITE_TIMER:
			DrawSprite ();
			m_fOffset += 3;
			if (m_fOffset > Bounds().bottom)
			{
				m_fOffset = - (m_pbmpStrip->Bounds().bottom + 1.0);
			}
			break;
		default:
			BView::MessageReceived (msg);
			break;
	}
*/
}


/***************************************************************
***************************************************************/
void
AnimatedView :: AttachedToWindow
	(
	void
	)
{
	m_pbmpWorkBitmap->Lock ();
	m_pWorkView->SetHighColor (Parent()->ViewColor ());
	m_pbmpWorkBitmap->Unlock ();
}


/***************************************************************
***************************************************************/
void
AnimatedView :: SetViewColor
	(
	rgb_color color
	)
{
	m_pbmpWorkBitmap->Lock ();
	m_pWorkView->SetHighColor (color);
	m_pbmpWorkBitmap->Unlock ();
}


/***************************************************************
***************************************************************/
void
AnimatedView :: Enabled
	(
	bool newvalue
	)
{
	if (newvalue != m_bRunning)
	{
		m_bRunning = newvalue;
		if (m_bRunning)
		{
			if (!m_pMsgRunner)
			{
				BMessage msg (MSG_SPRITE_TIMER);
				m_pMsgRunner = reinterpret_cast<BMessageRunner *> (new BMessageRunner (BMessenger (this), &msg, 100000));
				if (B_OK != m_pMsgRunner->InitCheck ())
				{
					delete m_pMsgRunner;
					m_pMsgRunner = NULL;
				}
			}
		}
		else
		{
			if (m_pMsgRunner)
			{
				delete m_pMsgRunner;
				m_pMsgRunner = NULL;
			}
			Invalidate ();
			m_fOffset = - (m_pbmpStrip->Bounds().bottom + 1.0);
		}
	}
}


/***************************************************************
***************************************************************/
void
AnimatedView :: Pause
	(
	bool slowitdown
	)
{
	if (m_pMsgRunner)
	{
		if (slowitdown)
		{
			m_pMsgRunner->SetInterval (5000000);  //5 seconds
		}
		else
		{
			m_pMsgRunner->SetInterval (100000);  //1 10th of a second
		}
	}
}


/***************************************************************
***************************************************************/
void
AnimatedView :: DrawSprite
	(
	void
	)
{
	m_pbmpWorkBitmap->Lock ();
	m_pWorkView->FillRect (Bounds ());
	if (true == m_bRunning)
	{
		m_pWorkView->DrawBitmap (m_pbmpStrip, BPoint (3, m_fOffset));
	}
	m_pWorkView->MovePenTo (0.0, 2.0);
	m_pWorkView->DrawBitmap (m_pbmpMagnify);
	m_pWorkView->Sync ();
	m_pbmpWorkBitmap->Unlock ();
	DrawBitmapAsync (m_pbmpWorkBitmap);
}


