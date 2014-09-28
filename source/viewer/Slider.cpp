/*	
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include headers
***************************************************************/
#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef SLIDER_H
#include "Slider.h"
#endif


/***************************************************************
globals
***************************************************************/

/***************************************************************
***************************************************************/
Slider :: Slider
	(
	BRect frame
,	const char * name
,	const char * label
,	BMessage * message
,	int32 minValue
,	int32 maxValue
,	thumb_style thumbType = B_BLOCK_THUMB
,	uint32 resizingMode
,	uint32 flags
	)
:	BSlider (frame, name, label, message, minValue, maxValue, thumbType, resizingMode, flags)
,	m_label (NULL)
{
	if (label)
	{
		m_label = new char[strlen (label) + 1];
		strcpy (m_label, label);
	}
}


/***************************************************************
***************************************************************/
Slider :: ~Slider
	(
	void
	)
{
	if (m_label)
	{
		delete [] m_label;
	}
}


/***************************************************************
***************************************************************/
void
Slider :: SetValue
	(
	int32 value
	)
{
	BSlider::SetValue (value);
	if (m_label)
	{
		char str[strlen (m_label) + 11]; //len of string + 1 for null + 10 for max int32 val of 2,147,483,648
		int32 val (Value ());
		sprintf (str, m_label, val);
		SetLabel (str);
	}
}
