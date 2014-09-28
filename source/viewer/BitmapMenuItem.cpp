//#define DEBUG 1
#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h> 
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef _BITMAP_MENU_ITEM_H
#include "BitmapMenuItem.h"
#endif


/*----------------------------------------------------------------*/
/*----- BMenuItem class ------------------------------------------*/

BitmapMenuItem :: BitmapMenuItem
	(
	BWindow * pWindow
,	BBitmap * bmp
,	const char * label
,	const char * sbar_message
,	BMessage * message
,	char shortcut
,	uint32 modifiers
	)
:	BMenuItem (label, message, shortcut, modifiers)
,	m_pWnd (pWindow)
,	m_sbar_message (NULL)
,	m_bmp (bmp)
{
	PRINT (("BitmapMenuItem::BitmapMenuItem\n"));
	if (NULL != sbar_message)
	{
		m_sbar_message = (char *) new char[strlen (sbar_message) + 1];
		strcpy (m_sbar_message, sbar_message);
	}
}


/***************************************************************
***************************************************************/
BitmapMenuItem :: ~BitmapMenuItem
	(
	void
	)
{
	if (NULL != m_sbar_message)
	{
		delete [] m_sbar_message;
		m_sbar_message = NULL;
	}
}


/***************************************************************
***************************************************************/
void
BitmapMenuItem :: GetContentSize
	(
	float * width
,	float *height
	)
{
	PRINT (("BitmapMenuItem::GetContentSize\n"));
	BMenuItem::GetContentSize (width, height);
	*width += 20.0f;
	PRINT (("  return width = %0.f, height = %0.f\n", *width, *height));
}


/***************************************************************
***************************************************************/
void
BitmapMenuItem :: DrawContent
	(
	void
	)
{
	PRINT (("BitmapMenuItem::DrawContent\n"));
	BMenuItem::DrawContent ();
	BPoint pt (ContentLocation ());
	BMenu * menu (Menu ());
	float w (menu->StringWidth (Label ()) + 5.0f);
	float buffy (Frame().Height());
	if (buffy > 15.0)
	{
		buffy = 15.0f;
	}
	menu->SetDrawingMode (B_OP_OVER);
	menu->DrawBitmap (m_bmp, BRect (pt.x + w, pt.y - 2.0f, pt.x + 15.0f + w, pt.y + buffy - 2.0f));
	menu->SetDrawingMode (B_OP_COPY);
}


/***************************************************************
***************************************************************/
void
BitmapMenuItem :: Highlight
	(
	bool on
)
{
	PRINT (("BitmapMenuItem::Highlight\n"));
	BMenuItem::Highlight (on);
	if (m_pWnd)
	{
		BMessage postMsg (MSG_UPDATE_STATUS_UI);
		postMsg.AddString ("string", m_sbar_message);
		m_pWnd->PostMessage (&postMsg);
	}
}

