#include <Be.h>

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

#ifndef _CAM_CONSTANTS_H
#include "CAM_Constants.h"
#endif

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectOther.h"
#include "InspectApplicationKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "utility.h"

extern const char * pTrue;
extern const char * pFalse;
extern const char * g_pIndentation;
extern const char * g_pFailedWithError;
extern const char * g_pNewline;

//the one and only instance of a ClueAreaManager, already defined in Clue.cpp
extern ClueAreaManager CAM;


/***************************************************************
***************************************************************/
void
ShowViewHeirerarchy
	(
	BString & strDetails
,	BView * inValue
,	int32 inIndent
,	int32 inIndex
	)
{
	BView * child (inValue->ChildAt (0));
	BString tabindent;

	int32 i (0);
	for (; i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	i = inValue->CountChildren ();
	strDetails << tabindent <<  "[" << inIndex << "] " << inValue->Name () <<
		" (ptr=" << hexbuf << ", has " << i << (1 == i ? " child)\n" : " children)\n");

	if (NULL != child)
	{
		++inIndent;

		int32 index (0);
		while (NULL != child)
		{
			ShowViewHeirerarchy (strDetails, child, inIndent, ++index);
			child = child->NextSibling ();
		}
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BWindow
	(
	BString & strDetails
,	BWindow * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BWindow object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		bool aBool (inValue->IsLocked ());
		if (aBool) //then we can continue
		{
			uint32 aUInt32 (0);
			float aFloat1 (0.0f), aFloat2 (0.0f), aFloat3 (0.0f), aFloat4 (0.0f);
			BRect aRect (inValue->Bounds ());
			strDetails << tabindent << "IsActive= " << (inValue->IsActive () ? pTrue : pFalse);
			Inspect_BRect (strDetails, &aRect, inIndent, "Bounds: ");
			aRect = inValue->Frame ();
			Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");
			strDetails << tabindent << "CountChildren= " << inValue->CountChildren () << g_pNewline;

			strDetails << tabindent << "Heirerarchy of BViews:\n";
			int32 index (0);
			BView * child (inValue->ChildAt (index));
			while (NULL != child)
			{
				ShowViewHeirerarchy (strDetails, child, inIndent + 1, ++index);
				child = child->NextSibling ();
			}

			strDetails << tabindent << "IsFront= " << (inValue->IsFront () ? pTrue : pFalse);
			strDetails << tabindent << "IsFloating= " << (inValue->IsFloating () ? pTrue : pFalse);
			strDetails << tabindent << "IsModal= " << (inValue->IsModal () ? pTrue : pFalse);
			strDetails << tabindent << "NeedsUpdate= " << (inValue->NeedsUpdate () ? pTrue : pFalse);

			window_feel aWindowFeel (inValue->Feel ());
			Inspect_Enum_window_feel (strDetails, aWindowFeel, inIndent, "Feel: ");

			aUInt32 = inValue->Flags ();
			strDetails << tabindent << "Flags= [" << (unsigned int) aUInt32 << "], ";

			if (B_NOT_MOVABLE & aUInt32)
				strDetails << "B_NOT_MOVABLE,";
			if (B_NOT_CLOSABLE & aUInt32)
				strDetails << "B_NOT_CLOSABLE,";
			if (B_NOT_ZOOMABLE & aUInt32)
				strDetails << "B_NOT_ZOOMABLE,";
			if (B_NOT_MINIMIZABLE & aUInt32)
				strDetails << "B_NOT_MINIMIZABLE,";
			if (B_NOT_RESIZABLE & aUInt32)
				strDetails << "B_NOT_RESIZABLE,";
			if (B_NOT_H_RESIZABLE & aUInt32)
				strDetails << "B_NOT_H_RESIZABLE,";
			if (B_NOT_V_RESIZABLE & aUInt32)
				strDetails << "B_NOT_V_RESIZABLE,";
			if (B_AVOID_FRONT & aUInt32)
				strDetails << "B_AVOID_FRONT,";
			if (B_AVOID_FOCUS & aUInt32)
				strDetails << "B_AVOID_FOCUS,";
			if (B_WILL_ACCEPT_FIRST_CLICK & aUInt32)
				strDetails << "B_WILL_ACCEPT_FIRST_CLICK,";
			if (B_OUTLINE_RESIZE & aUInt32)
				strDetails << "B_OUTLINE_RESIZE,";
			if (B_NO_WORKSPACE_ACTIVATION & aUInt32)
				strDetails << "B_NO_WORKSPACE_ACTIVATION,";
			if (B_NOT_ANCHORED_ON_ACTIVATE & aUInt32)
				strDetails << "B_NOT_ANCHORED_ON_ACTIVATE,";
			if (B_ASYNCHRONOUS_CONTROLS & aUInt32)
				strDetails << "B_ASYNCHRONOUS_CONTROLS,";
			if (B_QUIT_ON_WINDOW_CLOSE & aUInt32)
				strDetails << "B_QUIT_ON_WINDOW_CLOSE,";

			strDetails.RemoveLast (",");
			strDetails << g_pNewline;

			window_look aWindowLook (inValue->Look ());
			Inspect_Enum_window_look (strDetails, aWindowLook, inIndent, "Look: ");

			strDetails << tabindent << "PulseRate= " << inValue->PulseRate () << g_pNewline;
			inValue->GetSizeLimits (&aFloat1, &aFloat2, &aFloat3, &aFloat4);
			strDetails << tabindent << "SizeLimits: minWidth=" << aFloat1 << ", maxWidth=" << aFloat2 << ", minHeight=" << aFloat3 << ", maxHeight=" << aFloat4 << g_pNewline;
			strDetails << tabindent << "Title= " << inValue->Title () << g_pNewline;

			window_type aWindowType (inValue->Type ());
			Inspect_Enum_window_type (strDetails, aWindowType, inIndent, "Type: ");

			strDetails << tabindent << "Workspaces= " << inValue->Workspaces () << g_pNewline;
			strDetails << tabindent << "IsHidden= " << (inValue->IsHidden () ? pTrue : pFalse);
			strDetails << tabindent << "IsMinimized= " << (inValue->IsMinimized () ? pTrue : pFalse);

/*TODO
			if (DoBaseClasses)
			{
				strDetails << tabindent << g_pNewline;
				Inspect_BLooper (strDetails, (BLooper *) inValue, --inIndent, "  + BWindow baseclass ", true);
			}
*/
		}
		else
		{
			strDetails << tabindent << "you must lock the BLooper before Clue can continue!\n";
		}
	}
	else
	{
		strDetails << tabindent = "The BWindow was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BView
	(
	BString & strDetails
,	BView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BView object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		float aFloat (0.0f);
		float bFloat (0.0f);
		BFont aFont;
		rgb_color aRGB;
		BPoint aPoint (0.0f, 0.0f);
		BRect aRect (0.0f, 0.0f, 0.0f, 0.0f);

		uint32 ObjectMask (CAM.m_data->m_mask[INDEX_BVIEW]);

		if (ObjectMask & MASK_BVIEW_BOUNDS)
		{
			aRect = inValue->Bounds ();
			Inspect_BRect (strDetails, &aRect, inIndent, "Bounds: ");
		}

		if (ObjectMask & MASK_BVIEW_COUNTCHILDREN)
			strDetails << tabindent << "CountChildren= " << inValue->CountChildren () << g_pNewline;

		if (ObjectMask & MASK_BVIEW_HEIRARCHY)
		{
			strDetails << tabindent << "Heirerarchy of BViews:\n";
			ShowViewHeirerarchy (strDetails, inValue, inIndent + 1, 1);
		}

		if (ObjectMask & MASK_BVIEW_DRAWINGMODE)
		{
			drawing_mode aDrawingMode (inValue->DrawingMode ());
			Inspect_Enum_drawing_mode (strDetails, aDrawingMode, inIndent, "DrawingMode: ");
		}

		uint32 aUInt32 (0);
		if (ObjectMask & MASK_BVIEW_EVENTMASK)
		{
			aUInt32 = inValue->EventMask ();
			strDetails << tabindent << "EventMask= [" << aUInt32 << "], ";
			if (B_POINTER_EVENTS & aUInt32)
			{
				strDetails << "B_POINTER_EVENTS, ";
			}
			if (B_KEYBOARD_EVENTS & aUInt32)
			{
				strDetails << "B_KEYBOARD_EVENTS, ";
			}
			strDetails.RemoveLast (",");
			strDetails << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_FLAGS)
		{
			aUInt32 = inValue->Flags ();
			strDetails << tabindent << "Flags= [" << (unsigned int) aUInt32 << "], ";
			if (B_FULL_UPDATE_ON_RESIZE & aUInt32)
			{
				strDetails << "B_FULL_UPDATE_ON_RESIZE, ";
			}
			if (B_WILL_DRAW & aUInt32)
			{
				strDetails << "B_WILL_DRAW, ";
			}
			if (B_PULSE_NEEDED & aUInt32)
			{
				strDetails << "B_PULSE_NEEDED, ";
			}
			if (B_NAVIGABLE_JUMP & aUInt32)
			{
				strDetails << "B_NAVIGABLE_JUMP, ";
			}
			if (B_FRAME_EVENTS & aUInt32)
			{
				strDetails << "B_FRAME_EVENTS, ";
			}
			if (B_NAVIGABLE & aUInt32)
			{
				strDetails << "B_NAVIGABLE, ";
			}
			if (B_SUBPIXEL_PRECISE & aUInt32)
			{
				strDetails << "B_SUBPIXEL_PRECISE, ";
			}
			if (B_DRAW_ON_CHILDREN & aUInt32)
			{
				strDetails << "B_DRAW_ON_CHILDREN, ";
			}
			if (B_INPUT_METHOD_AWARE & aUInt32)
			{
				strDetails << "B_INPUT_METHOD_AWARE, ";
			}
			strDetails.RemoveLast (",");
			strDetails << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_FRAME)
		{
			aRect = inValue->Frame ();
			Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");
		}

		if (ObjectMask & MASK_BVIEW_GETFONT)
		{
			inValue->GetFont (&aFont);
			Inspect_BFont (strDetails, &aFont, inIndent, "GetFont: ");
		}

		if (ObjectMask & MASK_BVIEW_GETPREFERREDSIZE)
		{
			inValue->GetPreferredSize (&aFloat, &bFloat);
			strDetails << tabindent << "GetPreferredSize: width= " << aFloat << ", height= " << bFloat << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_HIGHCOLOR)
		{
			aRGB = inValue->HighColor ();
			Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "HighColor: ");
		}

		if (ObjectMask & MASK_BVIEW_LOWCOLOR)
		{
			aRGB = inValue->LowColor ();
			Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "LowColor: ");
		}

		if (ObjectMask & MASK_BVIEW_VIEWCOLOR)
		{
			aRGB = inValue->ViewColor ();
			Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "ViewColor: ");
		}

		if (ObjectMask & MASK_BVIEW_ISFOCUS)
			strDetails << tabindent << "IsFocus: " << (inValue->IsFocus () ? pTrue : pFalse);

		if (ObjectMask & MASK_BVIEW_ISHIDDEN)
			strDetails << tabindent << "IsHidden: " << (inValue->IsHidden () ? pTrue : pFalse);

		if (ObjectMask & MASK_BVIEW_ISPRINTING)
			strDetails << tabindent << "IsPrinting: " << (inValue->IsPrinting () ? pTrue : pFalse);

		if (ObjectMask & MASK_BVIEW_LINECAPMODE)
		{
			cap_mode aCapMode (inValue->LineCapMode ());
			Inspect_Enum_cap_mode (strDetails, aCapMode, inIndent, "LineCapMode: ");
		}

		if (ObjectMask & MASK_BVIEW_LINEJOINMODE)
		{
			join_mode aJoinMode (inValue->LineJoinMode ());
			Inspect_Enum_join_mode (strDetails, aJoinMode, inIndent, "LineJoinMode: ");
		}

		if (ObjectMask & MASK_BVIEW_LINEMITERLIMIT)
		{
			aFloat = inValue->LineMiterLimit ();
			strDetails << tabindent << "LineMiterLimit= " << aFloat;
			if (B_DEFAULT_MITER_LIMIT == aFloat)
				strDetails << ",  B_DEFAULT_MITER_LIMIT";
			strDetails << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_PARENT)
		{
			BView * pView (inValue->Parent ());
			strDetails << tabindent << "Parent= " << (pView ? pView->Name () : "NULL") << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_PENLOCATION)
		{
			aPoint = inValue->PenLocation ();
			Inspect_BPoint (strDetails, &aPoint, inIndent, "PenLocation: ");
		}

		if (ObjectMask & MASK_BVIEW_PENSIZE)
		{
			aFloat = inValue->PenSize ();
			strDetails << tabindent << "PenSize= " << aFloat << g_pNewline;
		}

		if (ObjectMask & MASK_BVIEW_ORIGIN)
		{
			aPoint = inValue->Origin ();
			Inspect_BPoint (strDetails, &aPoint, inIndent, "Origin: ");
		}

//		if (DoBaseClasses)
		if (ObjectMask & MASK_BVIEW_BASECLASSES)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BHandler (strDetails, (BHandler *) inValue, --inIndent, "  + BView baseclass ");
		}
	}
	else
	{
		strDetails = "The BView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPoint
	(
	BString & strDetails
,	BPoint * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPoint object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "X= " << inValue->x << g_pNewline;
		strDetails << tabindent << "Y= " << inValue->y << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BPoint was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BBitmap
	(
	BString & strDetails
,	BBitmap * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BBitmap object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		strDetails << tabindent << "BitsLength= " << inValue->BitsLength () << g_pNewline;
		BRect aRect (inValue->Bounds ());
		Inspect_BRect (strDetails, &aRect, inIndent, "Bounds: ");
		strDetails << tabindent << "BytesPerRow= " << inValue->BytesPerRow () << g_pNewline;
		strDetails << tabindent << "CountChildren= " << inValue->CountChildren () << g_pNewline;
		color_space acolor_space (inValue->ColorSpace ());
		Inspect_Enum_color_space (strDetails, acolor_space, inIndent, "ColorSpace: ");
		strDetails << tabindent << "IsValid: " << (inValue->IsValid () ? pTrue : pFalse);
		strDetails << tabindent << "IsLocked: " << (inValue->IsLocked () ? pTrue : pFalse);
	}
	else
	{
		strDetails << tabindent << "The BPoint was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BRect
	(
	BString & strDetails
,	BRect * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BRect object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "Left= " << inValue->left << g_pNewline;
		strDetails << tabindent << "Top= " << inValue->top << g_pNewline;
		strDetails << tabindent << "Right= " << inValue->right << g_pNewline;
		strDetails << tabindent << "Bottom= " << inValue->bottom << g_pNewline;
		strDetails << tabindent << "IsValid= " << (inValue->IsValid () ? pTrue : pFalse);
		strDetails << tabindent << "Width= " << inValue->Width () << g_pNewline;
		strDetails << tabindent << "IntegerWidth= " << inValue->IntegerWidth () << g_pNewline;
		strDetails << tabindent << "Height= " << inValue->Height () << g_pNewline;
		strDetails << tabindent << "IntegerHeight= " << inValue->IntegerHeight () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BRect was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BFont
	(
	BString & strDetails
,	BFont * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		font_family aFontFamily;
		font_style aFontStyle;
		font_height aFontHeight;
		uint32 aUInt32 (0);
		uint16 aUInt16 (0);
		uint8 aUInt8 (0);

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BFont object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		inValue->GetHeight (&aFontHeight);
		strDetails << tabindent << "ascent= " << aFontHeight.ascent << g_pNewline;
		strDetails << tabindent << "descent= " << aFontHeight.descent << g_pNewline;
		strDetails << tabindent << "leading= " << aFontHeight.leading << g_pNewline;

		unicode_block aUB (inValue->Blocks ());
		Inspect_Class_unicode_block (strDetails, &aUB, inIndent, "Blocks: ");

		BRect aRect (inValue->BoundingBox ());
		Inspect_BRect (strDetails, &aRect, inIndent, "BoundingBox: ");

		font_direction aFD (inValue->Direction ());
		Inspect_Enum_font_direction (strDetails, aFD, inIndent, "Direction: ");

		strDetails << tabindent << "IsFixed= " << ((inValue->IsFixed ()) ? pTrue : pFalse);
		strDetails << tabindent << "IsFullAndHalfFixed= " << ((inValue->IsFullAndHalfFixed ()) ? pTrue : pFalse);
		aUInt16 = inValue->Face ();
		strDetails << tabindent << "Face= [" << (unsigned int) aUInt16 << "], ";
		if (B_ITALIC_FACE & aUInt16)
		{
			strDetails << "B_ITALIC_FACE,";
		}
		if (B_UNDERSCORE_FACE & aUInt16)
		{
			strDetails << "B_UNDERSCORE_FACE,";
		}
		if (B_NEGATIVE_FACE & aUInt16)
		{
			strDetails << "B_NEGATIVE_FACE,";
		}
		if (B_OUTLINED_FACE & aUInt16)
		{
			strDetails << "B_OUTLINED_FACE,";
		}
		if (B_STRIKEOUT_FACE & aUInt16)
		{
			strDetails << "B_STRIKEOUT_FACE,";
		}
		if (B_BOLD_FACE & aUInt16)
		{
			strDetails << "B_BOLD_FACE,";
		}
		if (B_REGULAR_FACE & aUInt16)
		{
			strDetails << "B_REGULAR_FACE,";
		}

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		font_file_format aFFF (inValue->FileFormat ());
		Inspect_Enum_font_file_format (strDetails, aFFF, inIndent, "FileFormat: ");

// in R5.0.3, CountTuned seems to cause the program to halt.
//		strDetails << tabindent << "CountTuned= " << inValue->CountTuned () << g_pNewline;

		inValue->GetFamilyAndStyle (&aFontFamily, &aFontStyle);
		strDetails << tabindent << "Family= " << aFontFamily << g_pNewline;
		strDetails << tabindent << "Style= " << aFontStyle << g_pNewline;

		aUInt32 = inValue->Flags ();
		strDetails << tabindent << "Flags= [" << (unsigned int) aUInt32 << "], ";
		if (B_FORCE_ANTIALIASING & aUInt32)
		{
			strDetails << "B_FORCE_ANTIALIASING,";
		}
		if (B_DISABLE_ANTIALIASING & aUInt32)
		{
			strDetails << "B_DISABLE_ANTIALIASING,";
		}
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		strDetails << tabindent << "Rotation= " << inValue->Rotation () << g_pNewline;

		strDetails << tabindent << "Shear= " << inValue->Shear () << "°\n";

		strDetails << tabindent << "Size= " << inValue->Size () << g_pNewline;

		aUInt8 = inValue->Spacing ();
		strDetails << tabindent << "Spacing= [" << (unsigned int) aUInt8 << "], ";
		switch (aUInt8)
		{
			case B_CHAR_SPACING:
				strDetails << "B_CHAR_SPACING\n";
				break;
			case B_STRING_SPACING:
				strDetails << "B_STRING_SPACING\n";
				break;
			case B_BITMAP_SPACING:
				strDetails << "B_BITMAP_SPACING\n";
				break;
			case B_FIXED_SPACING:
				strDetails << "B_FIXED_SPACING\n";
				break;
			default:
				strDetails << "unknown\n";
				break;
		}

		aUInt8 = inValue->Encoding ();
		strDetails << tabindent << "Encoding= [" << (unsigned int) aUInt8 << "], ";
		switch (aUInt8)
		{
			case B_UNICODE_UTF8:
				strDetails << "B_UNICODE_UTF8 (UTF-8)\n";
				break;
			case B_ISO_8859_1:
				strDetails << "B_ISO_8859_1 (Latin 1)\n";
				break;
			case B_ISO_8859_2:
				strDetails << "B_ISO_8859_2 (Latin 2)\n";
				break;
			case B_ISO_8859_3:
				strDetails << "B_ISO_8859_3 (Latin 3)\n";
				break;
			case B_ISO_8859_4:
				strDetails << "B_ISO_8859_4 (Latin 4)\n";
				break;
			case B_ISO_8859_5:
				strDetails << "B_ISO_8859_5 (Latin/Cyrillic)\n";
				break;
			case B_ISO_8859_6:
				strDetails << "B_ISO_8859_6 (Latin/Arabic\n";
				break;
			case B_ISO_8859_7:
				strDetails << "B_ISO_8859_7 (Latin/Greek)\n";
				break;
			case B_ISO_8859_8:
				strDetails << "B_ISO_8859_8 (Latin/Hebrew)\n";
				break;
			case B_ISO_8859_9:
				strDetails << "B_ISO_8859_9 (Latin 5)\n";
				break;
			case B_ISO_8859_10:
				strDetails << "B_ISO_8859_10 (Latin 6)\n";
				break;
			case B_MACINTOSH_ROMAN:
				strDetails << "B_MACINTOSH_ROMAN\n";
				break;
			default:
				strDetails << "unknown\n";
				break;
		}
	}
	else
	{
		strDetails << tabindent << "The BFont was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BControl
	(
	BString & strDetails
,	BControl * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BControl object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "Label= " << inValue->Label () << g_pNewline;

		int32 aInt32 (inValue->Value ());
		strDetails << tabindent << "Value= " << aInt32;
		switch (aInt32)
		{
			case B_CONTROL_OFF:
				strDetails << " (B_CONTROL_OFF)";
				break;
			case B_CONTROL_ON:
				strDetails << " (B_CONTROL_ON)";
				break;
		}
		strDetails << g_pNewline;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BInvoker (strDetails, (BInvoker *) inValue, inIndent, "  + BControl baseclass ");
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, inIndent, "  + BControl baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BControl was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BTextView
	(
	BString & strDetails
,	BTextView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BTextView object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		int32 aInt32 (0), bInt32 (0);
		inValue->GetSelection (&aInt32, &bInt32);
		strDetails << tabindent << "GetSelection: start=" << aInt32 << ", finish=" << bInt32 << g_pNewline;
		strDetails << tabindent << "CountLines= " << inValue->CountLines () << g_pNewline;
		strDetails << tabindent << "CurrentLine= " << inValue->CurrentLine () << g_pNewline;
		strDetails << tabindent << "IsTypingHidden= " << (inValue->IsTypingHidden () ? pTrue : pFalse);
		strDetails << tabindent << "IsEditable= " << (inValue->IsEditable () ? pTrue : pFalse);
		strDetails << tabindent << "IsResizable= " << (inValue->IsResizable () ? pTrue : pFalse);
		strDetails << tabindent << "IsSelectable= " << (inValue->IsSelectable () ? pTrue : pFalse);

		alignment aAlignment (inValue->Alignment ());
		Inspect_Enum_alignment (strDetails, aAlignment, inIndent, "Alignment: ");

		strDetails << tabindent << "DoesAutoindent= " << (inValue->DoesAutoindent () ? pTrue : pFalse);
		color_space aColorSpace (inValue->ColorSpace ());
		Inspect_Enum_color_space (strDetails, aColorSpace, inIndent, "ColorSpace: ");
		strDetails << tabindent << "MaxBytes= " << inValue->MaxBytes () << g_pNewline;
		strDetails << tabindent << "IsStylable= " << (inValue->IsStylable () ? pTrue : pFalse);
		strDetails << tabindent << "TabWidth= " << inValue->TabWidth () << g_pNewline;
		BRect aRect (inValue->TextRect ());
		Inspect_BRect (strDetails, &aRect, inIndent, "TextRect:");
		strDetails << tabindent << "DoesWordWrap= " << (inValue->DoesWordWrap () ? pTrue : pFalse);
		strDetails << tabindent << "TextLength= " << inValue->TextLength () << g_pNewline;
		strDetails << tabindent << "DoesUndo= " << (inValue->DoesUndo () ? pTrue : pFalse);

		bool aBool (false);
		undo_state aUndoState (inValue->UndoState (&aBool));
		Inspect_Enum_undo_state (strDetails, aUndoState, inIndent, "UndoState: ");
		strDetails << tabindent << "UndoState: isRedo= " << (aBool ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BTextView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BTextView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BListView
	(
	BString & strDetails
,	BListView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BListView object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "CountItems= " << inValue->CountItems () << g_pNewline;
		strDetails << tabindent << "IsEmpty= " << (inValue->IsEmpty () ? pTrue : pFalse);
		BMessage * pMsg (inValue->InvocationMessage ());
		GetHexString (hexbuf, (intptr_t) pMsg);
		strDetails << tabindent << "InvocationMessage: [BMessage object, ptr=" << hexbuf << "]\n";
		Inspect_BMessage (strDetails, pMsg, inIndent + 1, B_EMPTY_STRING, 1, 1);
		list_view_type aListViewType (inValue->ListType ());
		strDetails << tabindent << "ListType= " << (B_MULTIPLE_SELECTION_LIST == aListViewType ? "B_MULTIPLE_SELECTION_LIST\n" : "B_SINGLE_SELECTION_LIST\n");
		pMsg = inValue->SelectionMessage ();
		GetHexString (hexbuf, (intptr_t) pMsg);
		strDetails << tabindent << "SelectionMessage: [BMessage object, ptr=" << hexbuf << "]\n";
		Inspect_BMessage (strDetails, pMsg, inIndent + 1, B_EMPTY_STRING, 1, 1);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BListView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BListView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMenu
	(
	BString & strDetails
,	BMenu * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BMenu object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "CountItems= " << inValue->CountItems () << g_pNewline;
		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "MaxContentWidth= " << inValue->MaxContentWidth () << g_pNewline;
		strDetails << tabindent << "IsRadioMode= " << (inValue->IsRadioMode () ? pTrue : pFalse);
		strDetails << tabindent << "AreTriggersEnabled= " << (inValue->AreTriggersEnabled () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, inIndent, "  + BMenu baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BMenu was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMenuBar
	(
	BString & strDetails
,	BMenuBar * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BMenuBar object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		menu_bar_border aMenuBarBorder (inValue->Border ());
		Inspect_Enum_menu_bar_border (strDetails, aMenuBarBorder, inIndent, "Border: ");

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BMenu (strDetails, (BMenu *) inValue, --inIndent, "  + BMenuBar baseclass", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BMenuBar was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMenuField
	(
	BString & strDetails
,	BMenuField * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BMenuField object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		alignment aAlignment (inValue->Alignment ());
		Inspect_Enum_alignment (strDetails, aAlignment, inIndent, "Alignment: ");

		strDetails << tabindent << "Divider= " << inValue->Divider () << g_pNewline;
		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "Label= " << inValue->Label () << g_pNewline;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, inIndent, "  + BMenuField baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BMenuField was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMenuItem
	(
	BString & strDetails
,	BMenuItem * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMenuItem object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		BRect aRect (inValue->Frame ());
		Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");
		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "Label= " << inValue->Label () << g_pNewline;
		strDetails << tabindent << "IsMarked= " << (inValue->IsMarked () ? pTrue : pFalse);
		uint32 aUInt32 (0);
		char aChar[2];
		aChar[1] = '\0';
		aChar[0] = inValue->Shortcut (&aUInt32);
		GetHexString (hexbuf, (intptr_t) aUInt32);
		strDetails << tabindent << "Shortcut= " << aChar << ", (modifiers = " << hexbuf << ")\n";
		aChar[0] = inValue->Trigger ();
		GetHexString (hexbuf, (intptr_t) aChar);
		strDetails << tabindent << "Trigger= " << aChar << g_pNewline;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BInvoker (strDetails, (BInvoker *) inValue, --inIndent, "  + BMenuItem baseclass ");
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BMenuItem was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPopUpMenu
	(
	BString & strDetails
,	BPopUpMenu * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPopUpMenu object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "AsyncAutoDestruct= " << (inValue->AsyncAutoDestruct () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BMenu (strDetails, (BMenu *) inValue, inIndent, "  + BPopUpMenu baseclass", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BPopUpMenu was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BBox
	(
	BString & strDetails
,	BBox * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BBox object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		border_style aBorderStyle (inValue->Border ());
		Inspect_Enum_border_style (strDetails, aBorderStyle, inIndent, "Border: ");

		strDetails << tabindent << "Label= ";
		const char * pChar (inValue->Label ());
		if (NULL != pChar)
		{
			strDetails << pChar;
		}
		else
		{
			strDetails << "NULL";
		}
		strDetails << g_pNewline;

		BView * pView (inValue->LabelView ());
		if (NULL != pView)
		{
			Inspect_BView (strDetails, pView, inIndent, "LabelView: ");
		}
		else
		{
			strDetails << tabindent << "LabelView= NULL\n";
		}

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BBox baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BBox was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BDragger
	(
	BString & strDetails
,	BDragger * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BDragger object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "AreDraggersDrawn= " << (BDragger::AreDraggersDrawn () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, inIndent, "  + BDragger baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BDragger was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BOutlineListView
	(
	BString & strDetails
,	BOutlineListView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BOutlineListView object, ptr=" << hexbuf << "]\n";

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BListView (strDetails, (BListView *) inValue, inIndent, "  + BOutlineListView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BOutlineListView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BButton
	(
	BString & strDetails
,	BButton * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BButton object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "IsDefault= " << (inValue->IsDefault () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, inIndent, "  + BButton baseclass", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BButton was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BCheckBox
	(
	BString & strDetails
,	BCheckBox * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BCheckBox object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, inIndent, "  + BCheckBox baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BCheckBox was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BColorControl
	(
	BString & strDetails
,	BColorControl * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BColorControl object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		strDetails << tabindent << "CellSize= " << inValue->CellSize () << g_pNewline;
		color_control_layout aCCL (inValue->Layout ());
		Inspect_Enum_color_control_layout (strDetails, aCCL, inIndent, "Layout: ");

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, --inIndent, "  + BColorControl baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BColorControl was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BListItem
	(
	BString & strDetails
,	BListItem * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BListItem object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "OutlineLevel= " << inValue->OutlineLevel () << g_pNewline;
		strDetails << tabindent << "IsSelected= " << (inValue->IsSelected () ? pTrue : pFalse);
		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "IsExpanded= " << (inValue->IsExpanded () ? pTrue : pFalse);
		strDetails << tabindent << "Height= " << inValue->Height () << g_pNewline;
		strDetails << tabindent << "Width= " << inValue->Width () << g_pNewline;
	}
	else
	{
		strDetails << tabindent = "The BListItem was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPolygon
	(
	BString & strDetails
,	BPolygon * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPolygon object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		strDetails << tabindent << "CountPoints= " << inValue->CountPoints () << g_pNewline;
		BRect aRect (inValue->Frame ());
		Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");
	}
	else
	{
		strDetails << tabindent = "The BListItem was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BRegion
	(
	BString & strDetails
,	BRegion * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BRegion object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		BRect aRect (inValue->Frame ());
		Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");
		int32 aInt32 (inValue->CountRects ());
		strDetails << tabindent << "CountRects= " << aInt32 << g_pNewline;
		strDetails << tabindent << "RectAt: Left,     Top,   Right,  Bottom\n";
		char buf[512];
		int32 index (0);
		while (index++ < aInt32)
		{
			aRect = inValue->RectAt (index - 1);
			sprintf (buf, "%7.2f, %7.2f, %7.2f, %7.2f\n", aRect.left, aRect.top, aRect.right, aRect.bottom);
			strDetails << tabindent << g_pIndentation << buf;
		}
	}
	else
	{
		strDetails << tabindent = "The BListItem was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPictureButton
	(
	BString & strDetails
,	BPictureButton * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPictureButton object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "Behavior= ";
		switch (inValue->Behavior ())
		{
			case B_ONE_STATE_BUTTON:
				strDetails << "B_ONE_STATE_BUTTON\n";
				break;
			case B_TWO_STATE_BUTTON:
				strDetails << "B_TWO_STATE_BUTTON\n";
				break;
			default:
				strDetails << tabindent << "unknown\n";
				break;
		}

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, inIndent, "  + BPictureButton baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BPictureButton was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BSlider
	(
	BString & strDetails
,	BSlider * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BSlider object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		BRect aRect (inValue->BarFrame ());
		Inspect_BRect (strDetails, &aRect, inIndent, "BarFrame: ");
		aRect = inValue->HashMarksFrame ();
		Inspect_BRect (strDetails, &aRect, inIndent, "HashMarksFrame: ");
		aRect = inValue->ThumbFrame ();
		Inspect_BRect (strDetails, &aRect, inIndent, "ThumbFrame: ");

		rgb_color aRGB;
		aRGB = inValue->BarColor ();
		Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "BarColor: ");
		strDetails << tabindent << "BarThickness= " << inValue->BarThickness () << g_pNewline;
		hash_mark_location aHML (inValue->HashMarks ());
		Inspect_Enum_hash_mark_location (strDetails, aHML, inIndent, "HashMarks: ");
		strDetails << tabindent << "HashMarkCount= " << inValue->HashMarkCount () << g_pNewline;
		strDetails << tabindent << "KeyIncrementValue= " << inValue->KeyIncrementValue () << g_pNewline;

		strDetails << tabindent << "MinLimitLabel= ";
		const char * pChar (inValue->MinLimitLabel ());
		if (NULL != pChar)
		{
			strDetails << pChar;
		}
		else
		{
			strDetails << "NULL";
		}
		strDetails << g_pNewline;

		strDetails << tabindent << "MaxLimitLabel= ";
		pChar = inValue->MaxLimitLabel ();
		if (NULL != pChar)
		{
			strDetails << pChar;
		}
		else
		{
			strDetails << "NULL";
		}
		strDetails << g_pNewline;

		BMessage * pMessage (inValue->ModificationMessage ());
		GetHexString (hexbuf, (intptr_t) pMessage);
		strDetails << tabindent << "ModificationMessage: [BMessage object, ptr=" << hexbuf << "]\n";
		Inspect_BMessage (strDetails, pMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);
		orientation aOrientation (inValue->Orientation ());
		Inspect_Enum_orientation (strDetails, aOrientation, inIndent, "Orientation: ");
		strDetails << tabindent << "Position= " << inValue->Position () << g_pNewline;
		strDetails << tabindent << "SnoozeAmount= " << inValue->SnoozeAmount () << g_pNewline;
		strDetails << tabindent << "Value= " << inValue->Value () << g_pNewline;

		strDetails << tabindent << "UpdateText= ";
		pChar = inValue->UpdateText ();
		if (NULL != pChar)
		{
			strDetails << pChar;
		}
		else
		{
			strDetails << "NULL";
		}
		strDetails << g_pNewline;

		strDetails << tabindent << "FillColor= " << (inValue->FillColor (&aRGB) ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, --inIndent, "  + BSlider baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BSlider was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BScrollView
	(
	BString & strDetails
,	BScrollView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BScrollView object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		BScrollBar * pScrollBar (inValue->ScrollBar (B_HORIZONTAL));
		Inspect_BScrollBar (strDetails, pScrollBar, inIndent, "ScrollBar(B_HORIZONTAL): ");
		pScrollBar = inValue->ScrollBar (B_VERTICAL);
		Inspect_BScrollBar (strDetails, pScrollBar, inIndent, "ScrollBar(B_VERTICAL): ");

		border_style aBorderStyle (inValue->Border ());
		Inspect_Enum_border_style (strDetails, aBorderStyle, inIndent, "Border: ");

		strDetails << tabindent << "IsBorderHighlighted= " << (inValue->IsBorderHighlighted () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BScrollView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent = "The BScrollView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BScrollBar
	(
	BString & strDetails
,	BScrollBar * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BScrollBar object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		orientation aOrientation (inValue->Orientation ());
		Inspect_Enum_orientation (strDetails, aOrientation, inIndent, "Orientation: ");
		strDetails << tabindent << "Proportion= " << inValue->Proportion () << g_pNewline;

		float aFloat (0.0f), bFloat (0.0f);
		inValue->GetRange (&aFloat, &bFloat);
		strDetails << tabindent << "GetRange: min=" << aFloat << ", max=" << bFloat << g_pNewline;

		inValue->GetSteps (&aFloat, &bFloat);
		strDetails << tabindent << "GetSteps: smallStep=" << aFloat << ", bigStep=" << bFloat << g_pNewline;

		BView * pView (inValue->Target ());
		strDetails << tabindent << "Target= " << (pView ? pView->Name () : "NULL") << g_pNewline;
		
		strDetails << tabindent << "Value= " << inValue->Value () << g_pNewline;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BScrollBar baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BScrollBar was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BScreen
	(
	BString & strDetails
,	BScreen * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BScreen object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		bool aBool (inValue->IsValid ());
		
		if (aBool)
		{
			strDetails << tabindent << "IsValid= True\n"; //we know this now!

			color_space aColorSpace (inValue->ColorSpace ());
			Inspect_Enum_color_space (strDetails, aColorSpace, inIndent, "ColorSpace: ");

			BRect aRect (inValue->Frame ());
			Inspect_BRect (strDetails, &aRect, inIndent, "Frame: ");

			accelerant_device_info aADI;
			status_t aStatusT (inValue->GetDeviceInfo (&aADI));
			if (B_OK == aStatusT)
			{
				Inspect_Struct_accelerant_device_info (strDetails, &aADI, inIndent, "GetDeviceInfo: ");
			}
			else
			{
				GetStatusTDescription (strDetails, aStatusT, inIndent, "GetDeviceInfo: failed, ");
			}

			display_mode aDM;
			aStatusT = inValue->GetMode (&aDM);
			if (B_OK == aStatusT)
			{
				Inspect_Struct_display_mode (strDetails, &aDM, inIndent, "GetMode: ");
			}
			else
			{
				GetStatusTDescription (strDetails, aStatusT, inIndent, "GetMode: failed, ");
			}

/* had trouble getting this function to work, so take out
			display_timing_constraints aDTC;
			if (B_OK == inValue->GetTimingConstraints (&aDTC))
			{
				Inspect_display_timing_constraints (strDetails, &aDTC, inIndent, "GetTimingConstraints: ");
			}
			else
			{
				strDetails << tabindent << "GetTimingConstraints: No constraints known.\n";
			}
*/
			screen_id aSC (inValue->ID ());
			strDetails << tabindent << "ID= " << aSC.id << g_pNewline;

			rgb_color aRGB (inValue->DesktopColor ());
			Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "DesktopColor: ");

			uint32 aUInt32 (inValue->DPMSState ());
			strDetails << tabindent << "DPMSState= (" << aUInt32 << "), ";
			switch (aUInt32)
			{
				case B_DPMS_ON:
					strDetails << "B_DPMS_ON";
					break;
				case B_DPMS_STAND_BY:
					strDetails << "B_DPMS_STAND_BY";
					break;
				case B_DPMS_SUSPEND:
					strDetails << "B_DPMS_SUSPEND";
					break;
				case B_DPMS_OFF:
					strDetails << "B_DPMS_OFF";
					break;
				default:
					break;
			}
			strDetails << g_pNewline;

			aUInt32 = inValue->DPMSCapabilites ();
			strDetails << tabindent << "DPMSCapabilites= (" << aUInt32 << "), ";
			if (B_DPMS_ON & aUInt32)
			{
				strDetails << "B_DPMS_ON, ";
			}
			if (B_DPMS_STAND_BY & aUInt32)
			{
				strDetails << "B_DPMS_STAND_BY, ";
			}
			if (B_DPMS_SUSPEND & aUInt32)
			{
				strDetails << "B_DPMS_SUSPEND, ";
			}
			if (B_DPMS_OFF & aUInt32)
			{
				strDetails << "B_DPMS_OFF, ";
			}

			strDetails.RemoveLast (",");
			strDetails << g_pNewline;
		}
		else
		{
			strDetails << tabindent << "IsValid: false.\n";
		}
	}
	else
	{
		strDetails << tabindent << "The BScreen was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BShelf
	(
	BString & strDetails
,	BShelf * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BShelf object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{

		strDetails << tabindent << "CountReplicants= " << inValue->CountReplicants () << g_pNewline;
		strDetails << tabindent << "IsDirty= " << (inValue->IsDirty () ? pTrue : pFalse);
		strDetails << tabindent << "AllowsDragging= " << (inValue->AllowsDragging () ? pTrue : pFalse);
		strDetails << tabindent << "AllowsZombies= " << (inValue->AllowsZombies () ? pTrue : pFalse);
		strDetails << tabindent << "DisplaysZombies= " << (inValue->DisplaysZombies () ? pTrue : pFalse);
		strDetails << tabindent << "IsTypeEnforced= " << (inValue->IsTypeEnforced () ? pTrue : pFalse);

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BHandler (strDetails, (BHandler *) inValue, inIndent, "  + BShelf baseclass ");
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BShelf was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BStatusBar
	(
	BString & strDetails
,	BStatusBar * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BStatusBar object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		const char * pChar (inValue->Label ());
		strDetails << tabindent << "Label= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

		pChar = inValue->TrailingLabel ();
		strDetails << tabindent << "TrailingLabel= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

		rgb_color aRGB;
		aRGB = inValue->BarColor ();
		Inspect_Struct_rgb_color (strDetails, &aRGB, inIndent, "BarColor: ");

		strDetails << tabindent << "BarHeight= " << inValue->BarHeight () << g_pNewline;
		strDetails << tabindent << "MaxValue= " << inValue->MaxValue () << g_pNewline;
		strDetails << tabindent << "CurrentValue= " << inValue->CurrentValue () << g_pNewline;

		pChar = inValue->Text ();
		strDetails << tabindent << "Text= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

		pChar = inValue->TrailingText ();
		strDetails << tabindent << "TrailingText= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BStatusBar baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BStatusBar was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BStringView
	(
	BString & strDetails
,	BStringView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BStringView object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "Alignment= ";
		alignment aAlignment (inValue->Alignment ());
		Inspect_Enum_alignment (strDetails, aAlignment, inIndent, "Alignment: ");

		const char * pChar (inValue->Text ());
		strDetails << tabindent << "Text= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

/*
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BStringView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BStringView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BTextControl
	(
	BString & strDetails
,	BTextControl * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTextControl object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		alignment aAlignment, bAlignment;
		inValue->GetAlignment (&aAlignment, &bAlignment);
		Inspect_Enum_alignment (strDetails, aAlignment, inIndent, "GetAlignment: forLabel ");
		Inspect_Enum_alignment (strDetails, bAlignment, inIndent, "GetAlignment: forText ");

		strDetails << tabindent << "Divider= " << inValue->Divider () << g_pNewline;

		BMessage * pMsg (inValue->ModificationMessage ());
		Inspect_BMessage (strDetails, pMsg, inIndent + 1, B_EMPTY_STRING, 1, 1);

		const char * pChar (inValue->Text ());
		strDetails << tabindent << "Text= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

		BTextView * pTextView (inValue->TextView ());
		Inspect_BTextView (strDetails, pTextView, inIndent, "TextView: ");

/*
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BControl (strDetails, (BControl *) inValue, --inIndent, "  + BTextControl baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BTextControl was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BTab
	(
	BString & strDetails
,	BTab * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTab object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "IsEnabled= " << (inValue->IsEnabled () ? pTrue : pFalse);
		strDetails << tabindent << "IsSelected= " << (inValue->IsSelected () ? pTrue : pFalse);

		const char * pChar (inValue->Label ());
		strDetails << tabindent << "Label= " << (NULL != pChar ? pChar : "NULL") << g_pNewline;

		strDetails << tabindent << "IsFocus= " << (inValue->IsFocus () ? pTrue : pFalse);

		BView * pView (inValue->View ());
		strDetails << tabindent << "View= " << (pView ? pView->Name () : "NULL") << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BTab was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BTabView
	(
	BString & strDetails
,	BTabView * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTabView object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "CountTabs= " << inValue->CountTabs () << g_pNewline;

		BView * pView (inValue->ContainerView ());
		strDetails << tabindent << "ContainerView= " << (pView ? pView->Name () : "NULL") << g_pNewline;

		strDetails << tabindent << "FocusTab= " << inValue->FocusTab () << g_pNewline;
		strDetails << tabindent << "Selection= " << inValue->Selection () << g_pNewline;
		strDetails << tabindent << "TabHeight= " << inValue->TabHeight () << g_pNewline;
		button_width aButtonWidth (inValue->TabWidth ());
		Inspect_Enum_button_width (strDetails, aButtonWidth, inIndent, "TabWidth: ");

/*
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BView (strDetails, (BView *) inValue, --inIndent, "  + BTabView baseclass ", true);
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BTabView was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPrintJob
	(
	BString & strDetails
,	BPrintJob * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BPrintJob object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BPrintJob was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPicture
	(
	BString & strDetails
,	BPicture * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BPicture object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BPicture was NULL\n";
	}
}

/***************************************************************
***************************************************************/
void
Inspect_BSeparatorItem
	(
	BString & strDetails
,	BSeparatorItem * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSeparatorItem object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BSeparatorItem was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BStringItem
	(
	BString & strDetails
,	BStringItem * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BStringItem object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BStringItem was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BInputDevice
	(
	BString & strDetails
,	BInputDevice * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BInputDevice object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BInputDevice was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_unicode_block
	(
	BString & strDetails
,	unicode_block * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[unicode_block object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The unicode_block was NULL\n";
	}
}

/***************************************************************
***************************************************************/
void
Inspect_BAlert
	(
	BString & strDetails
,	BAlert * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BAlert object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BAlert was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BShape
	(
	BString & strDetails
,	BShape * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BShape object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BShape was NULL\n";
	}
}





