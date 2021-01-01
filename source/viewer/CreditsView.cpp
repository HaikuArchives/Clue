//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _REGION_H
#include <Region.h>
#endif

#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif

#ifndef _SCROLL_BAR_H
#include <ScrollBar.h>
#endif

#ifndef _CREDITSVIEW_H
#include "CreditsView.h"
#endif

const int32 CREDIT_ENTRIES = 21;

char Credits[CREDIT_ENTRIES][45] = {
	//123456789012345678901234567890123456789012345
	"Clue",
	"brought to you by these wonderful people:",
	"----------------------------------------",
	"Star Programmer:",
	"    Jeff Braun",
	"    yobkadon@hotmail.com",
	"    brauns.dyndns.org",
	"",
	"Programmer:",
	"    Mathew Hounsell",
	"    mat_geek@yahoo.com.au",
	"",
	"Additional icons:",
	"    erik (www.cubelab.de)",
	"",
	"Language translations:",
	"    Sergei Dolgov (Russian)",
	"    Bruno G. Albuquerque (Portuguese)",
	"    Adi Sieker (German)",
	"    Sylvain Tertois (French)",
	"    Jan Polzer (Czech)"
};


/******************************************************************************************************
*******************************************************************************************************/
CreditsView :: CreditsView
(
	void
)
	:	BView(BRect(0, 0, 250, 150), "Credits View", B_FOLLOW_NONE, B_WILL_DRAW | B_PULSE_NEEDED)
{
}


/******************************************************************************************************
*******************************************************************************************************/
void
CreditsView :: Draw
(
	BRect updateRect
)
{
	float tfh(0);  //total font height
//	BFont font;
	//float parheight (Parent()->Bounds().Height());
	font_height fh;
	GetFontHeight(&fh);
	tfh = fh.ascent + fh.descent + fh.leading;
	/*
		PRINT (("updaterect: %f, %f.\n",updateRect.top, updateRect.bottom));
		BRect ptOrg (Frame ());
		PRINT (("Frame = %f, %f.\n", ptOrg.top, ptOrg.bottom));
	 	BScrollBar * psbar = ((BScrollView *)Parent())->ScrollBar (B_VERTICAL);
		if (psbar)
		{
			float min, max;
			psbar->GetRange (&min, &max);
			PRINT (("sbar value = %f, min=%f,  max=%f\n", psbar->Value (), min, max));
		}
		else
			PRINT (("couldn't get scrollbar.\n"));
	*/
	for (int32 i(0); i < CREDIT_ENTRIES; i++) {
		MovePenTo(0, 150 + i * tfh);
		DrawString(Credits[i]);
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
CreditsView :: GetPreferredSize
(
	float* width
	,	float* height
)
{
	//PRINT (("\n\nGetPrefSize.\n\n\n"));
	BScrollView* pSV(dynamic_cast<BScrollView*>(Parent()));
	if (pSV) {
		BRect rcParent(pSV->Bounds());
		float parheight(rcParent.Height());
		font_height fh;
		GetFontHeight(&fh);
		float tfh(fh.ascent + fh.descent + fh.leading);
		*height = tfh* CREDIT_ENTRIES + parheight;
		*width = 250;
	} else {
		*height = 10;
		*width = 10;
	}
}


/******************************************************************************************************
*******************************************************************************************************/
void
CreditsView :: AttachedToWindow
(
	void
)
{
	PRINT(("CCreditsView :: AttachedToWindow\n"));
	rgb_color parview(Parent()->Parent()->ViewColor());
	SetViewColor(parview);
	SetLowColor(parview); //ViewColor ());
	ResizeToPreferred();
}


/******************************************************************************************************
*******************************************************************************************************/
void
CreditsView :: Pulse
(
	void
)
{
	float currheight(Bounds().Height());
	BScrollBar* psbar(dynamic_cast<BScrollView*>(Parent())->ScrollBar(B_VERTICAL));
	if (psbar->Value() >= currheight)
		ScrollTo(0, 0);
	else
		ScrollBy(0, 2);
}

