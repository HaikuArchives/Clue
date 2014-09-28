#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _POINT_H
#include <Point.h>
#endif

#ifndef _LIST_COUNT_STRING_VIEW_H
#include "ListCountStringView.h"
#endif

ListCountStringView :: ListCountStringView
	(
	BRect bounds, 
	const char *name, 
	const char *text, 
	uint32 resizeFlags, 
	uint32 flags
	)
:	BStringView (bounds, name, text, resizeFlags, flags)
{
}

void
ListCountStringView :: Draw
	(
	BRect bounds
	)
{
	BStringView::Draw (bounds);
	BRect rc (Bounds ());
	rgb_color color = {255, 255, 255, 255};

	BeginLineArray (4);
	AddLine (BPoint (rc.left, rc.bottom - 1.0f), BPoint (rc.left, rc.top + 1.0f), color);
	AddLine (BPoint (rc.left, rc.top + 1.0f), BPoint (rc.right, rc.top + 1.0f), color);

	color.red = 156;
	color.green = 154;
	color.blue = 156;
	AddLine (BPoint (rc.left, rc.top), BPoint (rc.right, rc.top), color); //top
	AddLine (BPoint (rc.left, rc.bottom), BPoint (rc.right, rc.bottom), color); //bottom
	EndLineArray ();
/*
	SetHighColor (156, 154, 156, 255);
	StrokeLine (BPoint (rc.left, rc.top), BPoint (rc.right, rc.top)); //top
	StrokeLine (BPoint (rc.left, rc.bottom), BPoint (rc.right, rc.bottom)); //bottom

	SetHighColor (255, 255, 255, 255);
	StrokeLine (BPoint (rc.left, rc.bottom - 1.0f), BPoint (rc.left, rc.top + 1.0f));
	StrokeLine (BPoint (rc.right, rc.top + 1.0f));
*/
}


void
ListCountStringView :: AttachedToWindow
	(
	void
	)
{
	BStringView::AttachedToWindow ();
	SetViewColor (222, 219, 222, 255);
	SetLowColor (222, 219, 222, 255);
}