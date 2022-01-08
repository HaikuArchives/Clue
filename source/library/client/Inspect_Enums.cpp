#include "ClueBuild.h"
#include <Be.h>

/*
#ifndef _APP_FILE_INFO_H
#include <AppFileInfo.h>
#endif

#include <fs_attr.h>
#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _COLOR_CONTROL_H
#include <ColorControl.h>
#endif

#ifndef _MESSAGE_FILTER_H
#include <MessageFilter.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _COLOR_CONTROL_H
#include <ColorControl.h>
#endif
#include <GraphicsDef.h>
#ifndef _INTERFACE_DEFS_H
#include <InterfaceDefs.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif
#include <EntryList.h>

#include <stat.h>

#ifndef _SLIDER_H
#include <Slider.h>
#endif
*/

#include <UnicodeBlockObjects.h>

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectApplicationKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "utility.h"

const char* pTrue("True\n");
const char* pFalse("False\n");
const char* g_pIndentation("  |  ");
const char* g_pFailedWithError(" failed with error ");
const char* g_pNewline("\n");


/***************************************************************
defined in InterfaceDefs.h as:
enum button_width {
	B_WIDTH_AS_USUAL,
	B_WIDTH_FROM_WIDEST,
	B_WIDTH_FROM_LABEL
};
***************************************************************/
void
Inspect_Enum_button_width
(
	BString& strDetails
	,	button_width inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[button_width enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_WIDTH_AS_USUAL:
			strDetails << tabindent << "B_WIDTH_AS_USUAL\n";
			break;
		case B_WIDTH_FROM_WIDEST:
			strDetails << tabindent << "B_WIDTH_FROM_WIDEST\n";
			break;
		case B_WIDTH_FROM_LABEL:
			strDetails << tabindent << "B_WIDTH_FROM_LABEL\n";
			break;
		default:
			strDetails << tabindent << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The button_width was NULL.\n";
//	}
}


/***************************************************************
defined in FilePanel.h as:
enum file_panel_mode {
	B_OPEN_PANEL,
	B_SAVE_PANEL
};
***************************************************************/
void
Inspect_Enum_file_panel_mode
(
	BString& strDetails
	,	file_panel_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[file_panel_mode enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_OPEN_PANEL:
			strDetails << tabindent << "B_OPEN_PANEL\n";
			break;
		case B_SAVE_PANEL:
			strDetails << tabindent << "B_SAVE_PANEL\n";
			break;
		default:
			strDetails << tabindent << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The file_panel_mode was NULL.\n";
//	}
}


/***************************************************************
defined in FilePanel.h as:
enum file_panel_button {
	B_CANCEL_BUTTON,
	B_DEFAULT_BUTTON
};
***************************************************************/
void
Inspect_Enum_file_panel_button
(
	BString& strDetails
	,	file_panel_button inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[file_panel_button enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_CANCEL_BUTTON:
			strDetails << tabindent << "B_CANCEL_BUTTON\n";
			break;
		case B_DEFAULT_BUTTON:
			strDetails << tabindent << "B_DEFAULT_BUTTON\n";
			break;
		default:
			strDetails << tabindent << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The file_panel_button was NULL.\n";
//	}
}


/***************************************************************
defined in MenuBar.h as:
enum menu_bar_border {
	B_BORDER_FRAME,
	B_BORDER_CONTENTS,
	B_BORDER_EACH_ITEM
};
***************************************************************/
void
Inspect_Enum_menu_bar_border
(
	BString& strDetails
	,	menu_bar_border inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);

	strDetails << tabindent << pDescription << "[menu_bar_border enum, " << hexbuf << "] ";
//	strDetails << tabindent << pDescription << "[menu_bar_border object, ptr=" << hexbuf << "]\n";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
//		switch (*inValue)
	switch (inValue) {
		case B_BORDER_FRAME:
			strDetails << "B_BORDER_FRAME\n";
			break;
		case B_BORDER_CONTENTS:
			strDetails << "B_BORDER_CONTENTS\n";
			break;
		case B_BORDER_EACH_ITEM:
			strDetails << "B_BORDER_EACH_ITEM\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The menu_bar_border was NULL.\n";
//	}
}


/***************************************************************
defined in Window.h as:
enum window_feel {
	B_NORMAL_WINDOW_FEEL			= 0,
	B_MODAL_SUBSET_WINDOW_FEEL		= 2,
	B_MODAL_APP_WINDOW_FEEL			= 1,
	B_MODAL_ALL_WINDOW_FEEL			= 3,
	B_FLOATING_SUBSET_WINDOW_FEEL	= 5,
	B_FLOATING_APP_WINDOW_FEEL		= 4,
	B_FLOATING_ALL_WINDOW_FEEL		= 6
};
***************************************************************/
void
Inspect_Enum_window_feel
(
	BString& strDetails
	,	window_feel inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[window_feel enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_NORMAL_WINDOW_FEEL:
			strDetails << "B_NORMAL_WINDOW_FEEL\n";
			break;
		case B_MODAL_SUBSET_WINDOW_FEEL:
			strDetails << "B_MODAL_SUBSET_WINDOW_FEEL\n";
			break;
		case B_MODAL_APP_WINDOW_FEEL:
			strDetails << "B_MODAL_APP_WINDOW_FEEL\n";
			break;
		case B_MODAL_ALL_WINDOW_FEEL:
			strDetails << "B_MODAL_ALL_WINDOW_FEEL\n";
			break;
		case B_FLOATING_SUBSET_WINDOW_FEEL:
			strDetails << "B_FLOATING_SUBSET_WINDOW_FEEL\n";
			break;
		case B_FLOATING_APP_WINDOW_FEEL:
			strDetails << "B_FLOATING_APP_WINDOW_FEEL\n";
			break;
		case B_FLOATING_ALL_WINDOW_FEEL:
			strDetails << "B_FLOATING_ALL_WINDOW_FEEL\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The window_feel was NULL.\n";
//	}
}


/***************************************************************
defined in Window.h as:
enum window_look {
	B_BORDERED_WINDOW_LOOK	= 20,
	B_NO_BORDER_WINDOW_LOOK	= 19,
	B_TITLED_WINDOW_LOOK	= 1,
	B_DOCUMENT_WINDOW_LOOK	= 11,
	B_MODAL_WINDOW_LOOK		= 3,
	B_FLOATING_WINDOW_LOOK	= 7
};
***************************************************************/
void
Inspect_Enum_window_look
(
	BString& strDetails
	,	window_look inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[window_look enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_BORDERED_WINDOW_LOOK:
			strDetails << "B_BORDERED_WINDOW_LOOK\n";
			break;
		case B_NO_BORDER_WINDOW_LOOK:
			strDetails << "B_NO_BORDER_WINDOW_LOOK\n";
			break;
		case B_TITLED_WINDOW_LOOK:
			strDetails << "B_TITLED_WINDOW_LOOK\n";
			break;
		case B_DOCUMENT_WINDOW_LOOK:
			strDetails << "B_DOCUMENT_WINDOW_LOOK\n";
			break;
		case B_MODAL_WINDOW_LOOK:
			strDetails << "B_MODAL_WINDOW_LOOK\n";
			break;
		case B_FLOATING_WINDOW_LOOK:
			strDetails << "B_FLOATING_WINDOW_LOOK\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The window_look was NULL.\n";
//	}
}


/***************************************************************
defined in Window.h as:
enum window_type {
	B_UNTYPED_WINDOW	= 0,
	B_TITLED_WINDOW 	= 1,
	B_MODAL_WINDOW 		= 3,
	B_DOCUMENT_WINDOW	= 11,
	B_BORDERED_WINDOW	= 20,
	B_FLOATING_WINDOW	= 21
};
***************************************************************/
void
Inspect_Enum_window_type
(
	BString& strDetails
	,	window_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[window_type enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_UNTYPED_WINDOW:
			strDetails << "B_UNTYPED_WINDOW\n";
			break;
		case B_TITLED_WINDOW:
			strDetails << "B_TITLED_WINDOW\n";
			break;
		case B_MODAL_WINDOW:
			strDetails << "B_MODAL_WINDOW\n";
			break;
		case B_DOCUMENT_WINDOW:
			strDetails << "B_DOCUMENT_WINDOW\n";
			break;
		case B_BORDERED_WINDOW:
			strDetails << "B_BORDERED_WINDOW\n";
			break;
		case B_FLOATING_WINDOW:
			strDetails << "B_FLOATING_WINDOW\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The window_type was NULL.\n";
//	}
}


/***************************************************************
defined in InterfaceDefs.h as:
enum join_mode {
	B_ROUND_JOIN=0,
	B_MITER_JOIN,
	B_BEVEL_JOIN,
	B_BUTT_JOIN,
	B_SQUARE_JOIN
};
***************************************************************/
void
Inspect_Enum_join_mode
(
	BString& strDetails
	,	join_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[join_mode enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_ROUND_JOIN:
			strDetails << "B_ROUND_JOIN\n";
			break;
		case B_MITER_JOIN:
			strDetails << "B_MITER_JOIN\n";
			break;
		case B_BEVEL_JOIN:
			strDetails << "B_BEVEL_JOIN\n";
			break;
		case B_BUTT_JOIN:
			strDetails << "B_BUTT_JOIN\n";
			break;
		case B_SQUARE_JOIN:
			strDetails << "B_SQUARE_JOIN\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The join_mode was NULL.\n";
//	}
}


/***************************************************************
defined in InterfaceDefs.h as:
enum cap_mode {
	B_ROUND_CAP=B_ROUND_JOIN,
	B_BUTT_CAP=B_BUTT_JOIN,
	B_SQUARE_CAP=B_SQUARE_JOIN
};
***************************************************************/
void
Inspect_Enum_cap_mode
(
	BString& strDetails
	,	cap_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[cap_mode enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_ROUND_CAP:
			strDetails << "B_ROUND_CAP\n";
			break;
		case B_BUTT_CAP:
			strDetails << "B_BUTT_CAP\n";
			break;
		case B_SQUARE_CAP:
			strDetails << "B_SQUARE_CAP\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The cap_mode was NULL.\n";
//	}
}


/***************************************************************
defined in GraphicsDefs.h as:
enum drawing_mode {
	B_OP_COPY,
	B_OP_OVER,
	B_OP_ERASE,
	B_OP_INVERT,
	B_OP_ADD,
	B_OP_SUBTRACT,
	B_OP_BLEND,
	B_OP_MIN,
	B_OP_MAX,
	B_OP_SELECT,
	B_OP_ALPHA
};
***************************************************************/
void
Inspect_Enum_drawing_mode
(
	BString& strDetails
	,	drawing_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[drawing_mode enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_OP_COPY:
			strDetails << "B_OP_COPY\n";
			break;
		case B_OP_OVER:
			strDetails << "B_OP_OVER\n";
			break;
		case B_OP_ERASE:
			strDetails << "B_OP_ERASE\n";
			break;
		case B_OP_INVERT:
			strDetails << "B_OP_INVERT\n";
			break;
		case B_OP_SELECT:
			strDetails << "B_OP_SELECT\n";
			break;
		case B_OP_ALPHA:
			strDetails << "B_OP_ALPHA\n";
			break;
		case B_OP_MIN:
			strDetails << "B_OP_MIN\n";
			break;
		case B_OP_MAX:
			strDetails << "B_OP_ADD\n";
			break;
		case B_OP_SUBTRACT:
			strDetails << "B_OP_SUBTRACE\n";
			break;
		case B_OP_BLEND:
			strDetails << "B_OP_BLEND\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The drawing_mode was NULL.\n";
//	}
}


/***************************************************************
defined in TextView.h as:
enum undo_state {
	B_UNDO_UNAVAILABLE,
	B_UNDO_TYPING,
	B_UNDO_CUT,
	B_UNDO_PASTE,
	B_UNDO_CLEAR,
	B_UNDO_DROP
};
***************************************************************/
void
Inspect_Enum_undo_state
(
	BString& strDetails
	,	undo_state inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[undo_state enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_UNDO_UNAVAILABLE:
			strDetails << "B_UNDO_UNAVAILABLE\n";
			break;
		case B_UNDO_TYPING:
			strDetails << "B_UNDO_TYPING\n";
			break;
		case B_UNDO_CUT:
			strDetails << "B_UNDO_CUT\n";
			break;
		case B_UNDO_PASTE:
			strDetails << "B_UNDO_PASTE\n";
			break;
		case B_UNDO_CLEAR:
			strDetails << "B_UNDO_CLEAR\n";
			break;
		case B_UNDO_DROP:
			strDetails << "B_UNDO_DROP\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The undo_state was NULL.\n";
//	}
}


/***************************************************************
defined in InterfaceDefs.h as:
enum alignment {
	B_ALIGN_LEFT,
    B_ALIGN_RIGHT,
    B_ALIGN_CENTER
};
***************************************************************/
void
Inspect_Enum_alignment
(
	BString& strDetails
	,	alignment inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[alignment enum, " << hexbuf << "] ";

//	if (NULL != inValue)
//	{
//		++inIndent;
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_ALIGN_LEFT:
			strDetails << "B_ALIGN_LEFT\n";
			break;
		case B_ALIGN_RIGHT:
			strDetails << "B_ALIGN_RIGHT\n";
			break;
		case B_ALIGN_CENTER:
			strDetails << "B_ALIGN_CENTER\n";
			break;
		default:
			strDetails << tabindent << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << g_pIndentation << "The alignment was NULL.\n";
//	}
}


/***************************************************************
defined in Font.h
***************************************************************/
void
Inspect_Class_unicode_block
(
	BString& strDetails
	,	unicode_block* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[unicode_block object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		if (inValue->Includes(B_BASIC_LATIN_BLOCK))
			strDetails << tabindent << "B_BASIC_LATIN_BLOCK\n";
		if (inValue->Includes(B_LATIN1_SUPPLEMENT_BLOCK))
			strDetails << tabindent << "B_LATIN1_SUPPLEMENT_BLOCK\n";
		if (inValue->Includes(B_LATIN_EXTENDED_A_BLOCK))
			strDetails << tabindent << "B_LATIN_EXTENDED_A_BLOCK\n";
		if (inValue->Includes(B_LATIN_EXTENDED_B_BLOCK))
			strDetails << tabindent << "B_LATIN_EXTENDED_B_BLOCK\n";
		if (inValue->Includes(B_IPA_EXTENSIONS_BLOCK))
			strDetails << tabindent << "B_IPA_EXTENSIONS_BLOCK\n";
		if (inValue->Includes(B_SPACING_MODIFIER_LETTERS_BLOCK))
			strDetails << tabindent << "B_SPACING_MODIFIER_LETTERS_BLOCK\n";
		if (inValue->Includes(B_COMBINING_DIACRITICAL_MARKS_BLOCK))
			strDetails << tabindent << "B_COMBINING_DIACRITICAL_MARKS_BLOCK\n";
		if (inValue->Includes(B_BASIC_GREEK_BLOCK))
			strDetails << tabindent << "B_BASIC_GREEK_BLOCK\n";
		if (inValue->Includes(B_GREEK_SYMBOLS_AND_COPTIC_BLOCK))
			strDetails << tabindent << "B_GREEK_SYMBOLS_AND_COPTIC_BLOCK\n";
		if (inValue->Includes(B_CYRILLIC_BLOCK))
			strDetails << tabindent << "B_CYRILLIC_BLOCK\n";
		if (inValue->Includes(B_ARMENIAN_BLOCK))
			strDetails << tabindent << "B_ARMENIAN_BLOCK\n";
		if (inValue->Includes(B_BASIC_HEBREW_BLOCK))
			strDetails << tabindent << "B_BASIC_HEBREW_BLOCK\n";
		if (inValue->Includes(B_HEBREW_EXTENDED_BLOCK))
			strDetails << tabindent << "B_HEBREW_EXTENDED_BLOCK\n";
		if (inValue->Includes(B_BASIC_ARABIC_BLOCK))
			strDetails << tabindent << "B_BASIC_ARABIC_BLOCK\n";
		if (inValue->Includes(B_ARABIC_EXTENDED_BLOCK))
			strDetails << tabindent << "B_ARABIC_EXTENDED_BLOCK\n";
		if (inValue->Includes(B_DEVANAGARI_BLOCK))
			strDetails << tabindent << "B_DEVANAGARI_BLOCK\n";
		if (inValue->Includes(B_BENGALI_BLOCK))
			strDetails << tabindent << "B_BENGALI_BLOCK\n";
		if (inValue->Includes(B_GURMUKHI_BLOCK))
			strDetails << tabindent << "B_GURMUKHI_BLOCK\n";
		if (inValue->Includes(B_GUJARATI_BLOCK))
			strDetails << tabindent << "B_GUJARATI_BLOCK\n";
		if (inValue->Includes(B_ORIYA_BLOCK))
			strDetails << tabindent << "B_ORIYA_BLOCK\n";
		if (inValue->Includes(B_TAMIL_BLOCK))
			strDetails << tabindent << "B_TAMIL_BLOCK\n";
		if (inValue->Includes(B_TELUGU_BLOCK))
			strDetails << tabindent << "B_TELUGU_BLOCK\n";
		if (inValue->Includes(B_KANNADA_BLOCK))
			strDetails << tabindent << "B_KANNADA_BLOCK\n";
		if (inValue->Includes(B_MALAYALAM_BLOCK))
			strDetails << tabindent << "B_MALAYALAM_BLOCK\n";
		if (inValue->Includes(B_THAI_BLOCK))
			strDetails << tabindent << "B_THAI_BLOCK\n";
		if (inValue->Includes(B_LAO_BLOCK))
			strDetails << tabindent << "B_LAO_BLOCK\n";
		if (inValue->Includes(B_BASIC_GEORGIAN_BLOCK))
			strDetails << tabindent << "B_BASIC_GEORGIAN_BLOCK\n";
		if (inValue->Includes(B_GEORGIAN_EXTENDED_BLOCK))
			strDetails << tabindent << "B_GEORGIAN_EXTENDED_BLOCK\n";
		if (inValue->Includes(B_HANGUL_JAMO_BLOCK))
			strDetails << tabindent << "B_HANGUL_JAMO_BLOCK\n";
		if (inValue->Includes(B_LATIN_EXTENDED_ADDITIONAL_BLOCK))
			strDetails << tabindent << "B_LATIN_EXTENDED_ADDITIONAL_BLOCK\n";
		if (inValue->Includes(B_GREEK_EXTENDED_BLOCK))
			strDetails << tabindent << "B_GREEK_EXTENDED_BLOCK\n";
		if (inValue->Includes(B_GENERAL_PUNCTUATION_BLOCK))
			strDetails << tabindent << "B_GENERAL_PUNCTUATION_BLOCK\n";
		if (inValue->Includes(B_SUPERSCRIPTS_AND_SUBSCRIPTS_BLOCK))
			strDetails << tabindent << "B_SUPERSCRIPTS_AND_SUBSCRIPTS_BLOCK\n";
		if (inValue->Includes(B_CURRENCY_SYMBOLS_BLOCK))
			strDetails << tabindent << "B_CURRENCY_SYMBOLS_BLOCK\n";
		if (inValue->Includes(B_COMBINING_MARKS_FOR_SYMBOLS_BLOCK))
			strDetails << tabindent << "B_COMBINING_MARKS_FOR_SYMBOLS_BLOCK\n";
		if (inValue->Includes(B_LETTERLIKE_SYMBOLS_BLOCK))
			strDetails << tabindent << "B_LETTERLIKE_SYMBOLS_BLOCK\n";
		if (inValue->Includes(B_NUMBER_FORMS_BLOCK))
			strDetails << tabindent << "B_NUMBER_FORMS_BLOCK\n";
		if (inValue->Includes(B_ARROWS_BLOCK))
			strDetails << tabindent << "B_ARROWS_BLOCK\n";
		if (inValue->Includes(B_MATHEMATICAL_OPERATORS_BLOCK))
			strDetails << tabindent << "B_MATHEMATICAL_OPERATORS_BLOCK\n";
		if (inValue->Includes(B_MISCELLANEOUS_TECHNICAL_BLOCK))
			strDetails << tabindent << "B_MISCELLANEOUS_TECHNICAL_BLOCK\n";
		if (inValue->Includes(B_CONTROL_PICTURES_BLOCK))
			strDetails << tabindent << "B_CONTROL_PICTURES_BLOCK\n";
		if (inValue->Includes(B_OPTICAL_CHARACTER_RECOGNITION_BLOCK))
			strDetails << tabindent << "B_OPTICAL_CHARACTER_RECOGNITION_BLOCK\n";
		if (inValue->Includes(B_ENCLOSED_ALPHANUMERICS_BLOCK))
			strDetails << tabindent << "B_ENCLOSED_ALPHANUMERICS_BLOCK\n";
		if (inValue->Includes(B_BOX_DRAWING_BLOCK))
			strDetails << tabindent << "B_BOX_DRAWING_BLOCK\n";
		if (inValue->Includes(B_BLOCK_ELEMENTS_BLOCK))
			strDetails << tabindent << "B_BLOCK_ELEMENTS_BLOCK\n";
		if (inValue->Includes(B_GEOMETRIC_SHAPES_BLOCK))
			strDetails << tabindent << "B_GEOMETRIC_SHAPES_BLOCK\n";
		if (inValue->Includes(B_MISCELLANEOUS_SYMBOLS_BLOCK))
			strDetails << tabindent << "B_MISCELLANEOUS_SYMBOLS_BLOCK\n";
		if (inValue->Includes(B_DINGBATS_BLOCK))
			strDetails << tabindent << "B_DINGBATS_BLOCK\n";
		if (inValue->Includes(B_CJK_SYMBOLS_AND_PUNCTUATION_BLOCK))
			strDetails << tabindent << "B_CJK_SYMBOLS_AND_PUNCTUATION_BLOCK\n";
		if (inValue->Includes(B_HIRAGANA_BLOCK))
			strDetails << tabindent << "B_HIRAGANA_BLOCK\n";
		if (inValue->Includes(B_KATAKANA_BLOCK))
			strDetails << tabindent << "B_KATAKANA_BLOCK\n";
		if (inValue->Includes(B_BOPOMOFO_BLOCK))
			strDetails << tabindent << "B_BOPOMOFO_BLOCK\n";
		if (inValue->Includes(B_HANGUL_COMPATIBILITY_JAMO_BLOCK))
			strDetails << tabindent << "B_HANGUL_COMPATIBILITY_JAMO_BLOCK\n";
		if (inValue->Includes(B_CJK_MISCELLANEOUS_BLOCK))
			strDetails << tabindent << "B_CJK_MISCELLANEOUS_BLOCK\n";
		if (inValue->Includes(B_ENCLOSED_CJK_LETTERS_AND_MONTHS_BLOCK))
			strDetails << tabindent << "B_ENCLOSED_CJK_LETTERS_AND_MONTHS_BLOCK\n";
		if (inValue->Includes(B_CJK_COMPATIBILITY_BLOCK))
			strDetails << tabindent << "B_CJK_COMPATIBILITY_BLOCK\n";
		if (inValue->Includes(B_HANGUL_BLOCK))
			strDetails << tabindent << "B_HANGUL_BLOCK\n";
		if (inValue->Includes(B_HIGH_SURROGATES_BLOCK))
			strDetails << tabindent << "B_HIGH_SURROGATES_BLOCK\n";
		if (inValue->Includes(B_LOW_SURROGATES_BLOCK))
			strDetails << tabindent << "B_LOW_SURROGATES_BLOCK\n";
		if (inValue->Includes(B_CJK_UNIFIED_IDEOGRAPHS_BLOCK))
			strDetails << tabindent << "B_CJK_UNIFIED_IDEOGRAPHS_BLOCK\n";
		if (inValue->Includes(B_PRIVATE_USE_AREA_BLOCK))
			strDetails << tabindent << "B_PRIVATE_USE_AREA_BLOCK\n";
		if (inValue->Includes(B_CJK_COMPATIBILITY_IDEOGRAPHS_BLOCK))
			strDetails << tabindent << "B_CJK_COMPATIBILITY_IDEOGRAPHS_BLOCK\n";
		if (inValue->Includes(B_ALPHABETIC_PRESENTATION_FORMS_BLOCK))
			strDetails << tabindent << "B_ALPHABETIC_PRESENTATION_FORMS_BLOCK\n";
		if (inValue->Includes(B_ARABIC_PRESENTATION_FORMS_A_BLOCK))
			strDetails << tabindent << "B_ARABIC_PRESENTATION_FORMS_A_BLOCK\n";
		if (inValue->Includes(B_COMBINING_HALF_MARKS_BLOCK))
			strDetails << tabindent << "B_COMBINING_HALF_MARKS_BLOCK\n";
		if (inValue->Includes(B_CJK_COMPATIBILITY_FORMS_BLOCK))
			strDetails << tabindent << "B_CJK_COMPATIBILITY_FORMS_BLOCK\n";
		if (inValue->Includes(B_SMALL_FORM_VARIANTS_BLOCK))
			strDetails << tabindent << "B_SMALL_FORM_VARIANTS_BLOCK\n";
		if (inValue->Includes(B_ARABIC_PRESENTATION_FORMS_B_BLOCK))
			strDetails << tabindent << "B_ARABIC_PRESENTATION_FORMS_B_BLOCK\n";
		if (inValue->Includes(B_HALFWIDTH_AND_FULLWIDTH_FORMS_BLOCK))
			strDetails << tabindent << "B_HALFWIDTH_AND_FULLWIDTH_FORMS_BLOCK\n";
		if (inValue->Includes(B_SPECIALS_BLOCK))
			strDetails << tabindent << "B_SPECIALS_BLOCK\n";
		if (inValue->Includes(B_TIBETAN_BLOCK))
			strDetails << tabindent << "B_TIBETAN_BLOCK\n";
	} else
		strDetails << tabindent << "The unicode_block was NULL.\n";
}

/***************************************************************
defined in Font.h as:
enum font_direction {
	B_FONT_LEFT_TO_RIGHT = 0,
	B_FONT_RIGHT_TO_LEFT = 1
};
***************************************************************/
void
Inspect_Enum_font_direction
(
	BString& strDetails
	,	font_direction inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[font_direction enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_FONT_LEFT_TO_RIGHT:
			strDetails << "B_FONT_LEFT_TO_RIGHT\n";
			break;
		case B_FONT_RIGHT_TO_LEFT:
			strDetails << "B_FONT_RIGHT_TO_LEFT\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The font_direction was NULL.\n";
//	}
}


/***************************************************************
defined in Font.h as:
enum font_file_format {
	B_TRUETYPE_WINDOWS			= 0,
	B_POSTSCRIPT_TYPE1_WINDOWS	= 1
};
***************************************************************/
void
Inspect_Enum_font_file_format
(
	BString& strDetails
	,	font_file_format inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[font_file_format enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_TRUETYPE_WINDOWS:
			strDetails << "B_TRUETYPE_WINDOWS\n";
			break;
		case B_POSTSCRIPT_TYPE1_WINDOWS:
			strDetails << "B_POSTSCRIPT_TYPE1_WINDOWS\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The font_file_format was NULL.\n";
//	}
}

/***************************************************************
defined in MessageFilter.h as:
enum message_source {
	B_ANY_SOURCE,
	B_REMOTE_SOURCE,
	B_LOCAL_SOURCE
};
***************************************************************/
void
Inspect_Enum_message_source
(
	BString& strDetails
	,	message_source inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[message_source enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_ANY_SOURCE:
			strDetails << "B_ANY_SOURCE\n";
			break;
		case B_REMOTE_SOURCE:
			strDetails << "B_REMOTE_SOURCE\n";
			break;
		case B_LOCAL_SOURCE:
			strDetails << "B_LOCAL_SOURCE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The message_source was NULL.\n";
//	}
}


/***************************************************************
defined in MessageFilter.h as:
enum message_delivery {
	B_ANY_DELIVERY,
	B_DROPPED_DELIVERY,
	B_PROGRAMMED_DELIVERY
};
***************************************************************/
void
Inspect_Enum_message_delivery
(
	BString& strDetails
	,	message_delivery inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[message_delivery enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_ANY_DELIVERY:
			strDetails << "B_ANY_DELIVERY\n";
			break;
		case B_DROPPED_DELIVERY:
			strDetails << "B_DROPPED_DELIVERY\n";
			break;
		case B_PROGRAMMED_DELIVERY:
			strDetails << "B_PROGRAMMED_DELIVERY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The message_delivery was NULL.\n";
//	}
}



/***************************************************************
defined in posix/sys/type.h as
typedef unsigned int        mode_t;
***************************************************************/
void
Inspect_Flags_mode_t
(
	BString& strDetails
	,	mode_t inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mode_t flag, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "mask= [" << (unsigned int) *inValue << "], ";
	if (S_ISUID & inValue)       /* set user id on execution */
		strDetails << "S_ISUID, ";
	if (S_ISGID & inValue)       /* set group id on execution */
		strDetails << "S_ISGID, ";
	if (S_ISVTX & inValue)       /* save swapped text even after use */
		strDetails << "S_ISVTX, ";


//		if (S_IRWXU == (S_IRWXU & inValue)) /* read, write, execute: owner */
//		{
//			strDetails << "S_IRWXU (S_IRUSR + S_IWUSR + S_IXUSR), ";
//		}
//		else
//		{
	if (S_IRUSR & inValue) /* read permission: owner */
		strDetails << "S_IRUSR, ";
	if (S_IWUSR & inValue) /* write permission: owner */
		strDetails << "S_IWUSR, ";
	if (S_IXUSR & inValue) /* execute permission: owner */
		strDetails << "S_IXUSR, ";
//		}

//		if (S_IRWXG == (S_IRWXG & inValue)) /* read, write, execute: group */
//		{
//			strDetails << "S_IRWXG (S_IRGRP + S_IWGRP + S_IXGRP), ";
//		}
//		else
//		{
	if (S_IRGRP & inValue) /* read permission: group */
		strDetails << "S_IRGRP, ";
	if (S_IWGRP & inValue) /* write permission: group */
		strDetails << "S_IWGRP, ";
	if (S_IXGRP & inValue) /* execute permission: group */
		strDetails << "S_IXGRP, ";
//		}

//		if (S_IRWXO == (S_IRWXO & inValue)) /* read, write, execute: other */
//		{
//			strDetails << "S_IRWXO (S_IROTH+S_IWOTH+S_IXOTH), ";
//		}
//		else
//		{
	if (S_IROTH & inValue) /* read permission: other */
		strDetails << "S_IROTH, ";
	if (S_IWOTH & inValue) /* write permission: other */
		strDetails << "S_IWOTH, ";
	if (S_IXOTH & inValue) /* execute permission: other */
		strDetails << "S_IXOTH,";
//		}

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;
	/*
	strDetails << "value= " << inValue << g_pNewline;

	strDetails << "S_IRWXU= " << S_IRWXU << ",   & inValue= " << (S_IRWXU & inValue) << g_pNewline;
	strDetails << "S_IRUSR= " << S_IRUSR << ",   & inValue= " << (S_IRUSR & inValue) << g_pNewline;
	strDetails << "S_IWUSR= " << S_IWUSR << ",   & inValue= " << (S_IWUSR & inValue) << g_pNewline;
	strDetails << "S_IXUSR= " << S_IXUSR << ",   & inValue= " << (S_IXUSR & inValue) << g_pNewline;
	strDetails << "S_IRWXG= " << S_IRWXG << ",   & inValue= " << (S_IRWXG & inValue) << g_pNewline;
	strDetails << "S_IRGRP= " << S_IRGRP << ",   & inValue= " << (S_IRGRP & inValue) << g_pNewline;
	strDetails << "S_IWGRP= " << S_IWGRP << ",   & inValue= " << (S_IWGRP & inValue) << g_pNewline;
	strDetails << "S_IXGRP= " << S_IXGRP << ",   & inValue= " << (S_IXGRP & inValue) << g_pNewline;
	strDetails << "S_IRWXO= " << S_IRWXO << ",   & inValue= " << (S_IRWXO & inValue) << g_pNewline;
	strDetails << "S_IROTH= " << S_IROTH << ",   & inValue= " << (S_IROTH & inValue) << g_pNewline;
	strDetails << "S_IWOTH= " << S_IWOTH << ",   & inValue= " << (S_IWOTH & inValue) << g_pNewline;
	strDetails << "S_IXOTH= " << S_IXOTH << ",   & inValue= " << (S_IXOTH & inValue) << g_pNewline;
	*/
//	}
//	else
//	{
//		strDetails << tabindent << "The mode_t was NULL.\n";
//	}
}


/***************************************************************
defined in Slider.h as:
enum thumb_style {
	B_BLOCK_THUMB,
	B_TRIANGLE_THUMB
};
***************************************************************/
void
Inspect_Enum_thumb_style
(
	BString& strDetails
	,	thumb_style inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[thumb_style enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_BLOCK_THUMB:
			strDetails << "B_BLOCK_THUMB\n";
			break;
		case B_TRIANGLE_THUMB:
			strDetails << "B_TRIANGLE_THUMB\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The thumb_style was NULL.\n";
//	}
}


/***************************************************************
defined in InterfaceDefs.h as:
enum orientation {
	B_HORIZONTAL,
	B_VERTICAL
};
***************************************************************/
void
Inspect_Enum_orientation
(
	BString& strDetails
	,	orientation inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[orientation enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_HORIZONTAL:
			strDetails << "B_HORIZONTAL\n";
			break;
		case B_VERTICAL:
			strDetails << "B_VERTICAL\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The orientation was NULL.\n";
//	}
}


/***************************************************************
defined in Slider.h as:
enum hash_mark_location {
	B_HASH_MARKS_NONE = 0,
	B_HASH_MARKS_TOP = 1,
	B_HASH_MARKS_LEFT = 1,
	B_HASH_MARKS_BOTTOM = 2,
	B_HASH_MARKS_RIGHT = 2,
	B_HASH_MARKS_BOTH = 3
};
***************************************************************/
void
Inspect_Enum_hash_mark_location
(
	BString& strDetails
	,	hash_mark_location inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[hash_mark_location enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_HASH_MARKS_NONE:
			strDetails << "B_HASH_MARKS_NONE\n";
			break;
		case B_HASH_MARKS_LEFT: //same as B_HASH_MARKS_TOP
			strDetails << "B_HASH_MARKS_TOP or B_HASH_MARKS_LEFT\n";
			break;
		case B_HASH_MARKS_RIGHT: //same as B_HASH_MARKS_BOTTOM
			strDetails << "B_HASH_MARKS_BOTTOM or B_HASH_MARKS_RIGHT\n";
			break;
		case B_HASH_MARKS_BOTH:
			strDetails << "B_HASH_MARKS_BOTH\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The hash_mark_location was NULL.\n";
//	}
}



/***************************************************************
defined in ColorControl.h as:
enum color_control_layout {
	B_CELLS_4x64 = 4,
	B_CELLS_8x32 = 8,
	B_CELLS_16x16 = 16,
	B_CELLS_32x8 = 32,
	B_CELLS_64x4 = 64
};
***************************************************************/
void
Inspect_Enum_color_control_layout
(
	BString& strDetails
	,	color_control_layout inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[color_control_layout enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_CELLS_4x64:
			strDetails << "B_CELLS_4x64\n";
			break;
		case B_CELLS_8x32:
			strDetails << "B_CELLS_8x32\n";
			break;
		case B_CELLS_16x16:
			strDetails << "B_CELLS_16x16\n";
			break;
		case B_CELLS_32x8:
			strDetails << "B_CELLS_32x8\n";
			break;
		case B_CELLS_64x4:
			strDetails << "B_CELLS_64x4\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The color_control_layout was NULL.\n";
//	}
}


/***************************************************************
defined in InterfaceDefs.h as:
enum border_style {
	B_PLAIN_BORDER,
	B_FANCY_BORDER,
	B_NO_BORDER
};


***************************************************************/
void
Inspect_Enum_border_style
(
	BString& strDetails
	,	border_style inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[border_style enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_PLAIN_BORDER:
			strDetails << "B_PLAIN_BORDER\n";
			break;
		case B_FANCY_BORDER:
			strDetails << "B_FANCY_BORDER\n";
			break;
		case B_NO_BORDER:
			strDetails << "B_NO_BORDER\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The BPoint was NULL.\n";
//	}
}



/***************************************************************
defined in GraphicsDefs.h
see file for definition
***************************************************************/
void
Inspect_Enum_color_space
(
	BString& strDetails
	,	color_space inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	if (inIndent >= 0) {
		for (int32 i(0); i < inIndent; i++)
			tabindent << g_pIndentation;
	}

//	if (NULL != inValue)
//	{
	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[color_space enum, " << hexbuf << "] ";
//		tabindent << g_pIndentation;

//		strDetails << tabindent << "enum= [" << (unsigned int) *inValue << "], ";
	switch (inValue) {
		case B_NO_COLOR_SPACE:
			strDetails << "B_NO_COLOR_SPACE\n";
			break;
		case B_RGB32:
			strDetails << "B_RGB32\n";
			break;
		case B_RGBA32:
			strDetails << "B_RGBA32\n";
			break;
		case B_RGB24:
			strDetails << "B_RGB24\n";
			break;
		case B_RGB16:
			strDetails << "B_RGB16\n";
			break;
		case B_RGB15:
			strDetails << "B_RGB15\n";
			break;
		case B_RGBA15:
			strDetails << "B_RGBA15\n";
			break;
		case B_CMAP8:
			strDetails << "B_CMAP8\n";
			break;
		case B_GRAY8:
			strDetails << "B_GRAY8\n";
			break;
		case B_GRAY1:
			strDetails << "B_GRAY1\n";
			break;
		case B_RGB32_BIG:
			strDetails << "B_RGB32_BIG\n";
			break;
		case B_RGBA32_BIG:
			strDetails << "B_RGBA32_BIG\n";
			break;
		case B_RGB24_BIG:
			strDetails << "B_RGB24_BIG\n";
			break;
		case B_RGB16_BIG:
			strDetails << "B_RGB16_BIG\n";
			break;
		case B_RGB15_BIG:
			strDetails << "B_RGB15_BIG\n";
			break;
		case B_RGBA15_BIG:
			strDetails << "B_RGBA15_BIG\n";
			break;
		case B_YCbCr422:
			strDetails << "B_YCbCr422\n";
			break;
		case B_YCbCr411:
			strDetails << "B_YCbCr411\n";
			break;
		case B_YCbCr444:
			strDetails << "B_YCbCr444\n";
			break;
		case B_YCbCr420:
			strDetails << "B_YCbCr420\n";
			break;
		case B_YUV422:
			strDetails << "B_YUV422\n";
			break;
		case B_YUV411:
			strDetails << "B_YUV411\n";
			break;
		case B_YUV444:
			strDetails << "B_YUV444\n";
			break;
		case B_YUV420:
			strDetails << "B_YUV420\n";
			break;
		case B_YUV9:
			strDetails << "B_YUV9\n";
			break;
		case B_YUV12:
			strDetails << "B_YUV12\n";
			break;
		case B_UVL24:
			strDetails << "B_UVL24\n";
			break;
		case B_UVL32:
			strDetails << "B_UVL32\n";
			break;
		case B_UVLA32:
			strDetails << "B_UVLA32\n";
			break;
		case B_LAB24:
			strDetails << "B_LAB24\n";
			break;
		case B_LAB32:
			strDetails << "B_LAB32\n";
			break;
		case B_LABA32:
			strDetails << "B_LABA32\n";
			break;
		case B_HSI24:
			strDetails << "B_HSI24\n";
			break;
		case B_HSI32:
			strDetails << "B_HSI32\n";
			break;
		case B_HSIA32:
			strDetails << "B_HSIA32\n";
			break;
		case B_HSV24:
			strDetails << "B_HSV24\n";
			break;
		case B_HSV32:
			strDetails << "B_HSV32\n";
			break;
		case B_HSVA32:
			strDetails << "B_HSVA32\n";
			break;
		case B_HLS24:
			strDetails << "B_HLS24\n";
			break;
		case B_HLS32:
			strDetails << "B_HLS32\n";
			break;
		case B_HLSA32:
			strDetails << "B_HLSA32\n";
			break;
		case B_CMY24:
			strDetails << "B_CMY24\n";
			break;
		case B_CMY32:
			strDetails << "B_CMY32\n";
			break;
		case B_CMYA32:
			strDetails << "B_CMYA32\n";
			break;
		case B_CMYK32:
			strDetails << "B_CMYK32\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
//	}
//	else
//	{
//		strDetails << tabindent << "The color_space was NULL.\n";
//	}
}


/***************************************************************
defined in ByteOrder.h as:
typedef enum {
	B_SWAP_HOST_TO_LENDIAN,
	B_SWAP_HOST_TO_BENDIAN,
	B_SWAP_LENDIAN_TO_HOST,
	B_SWAP_BENDIAN_TO_HOST,
	B_SWAP_ALWAYS
} swap_action;

***************************************************************/
void
Inspect_Enum_swap_action
(
	BString& strDetails
	,	swap_action inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[swap_action enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_SWAP_HOST_TO_LENDIAN:
			strDetails << "B_SWAP_HOST_TO_LENDIAN\n";
			break;
		case B_SWAP_HOST_TO_BENDIAN:
			strDetails << "B_SWAP_HOST_TO_BENDIAN\n";
			break;
		case B_SWAP_LENDIAN_TO_HOST:
			strDetails << "B_SWAP_LENDIAN_TO_HOST\n";
			break;
		case B_SWAP_BENDIAN_TO_HOST:
			strDetails << "B_SWAP_BENDIAN_TO_HOST\n";
			break;
		case B_SWAP_ALWAYS:
			strDetails << "B_SWAP_ALWAYS\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in AppFileInfo. as:
enum info_location {
	B_USE_ATTRIBUTES = 0x1,
	B_USE_RESOURCES = 0x2,
	B_USE_BOTH_LOCATIONS = 0x3
};

***************************************************************/
void
Inspect_Enum_info_location
(
	BString& strDetails
	,	info_location inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[info_location enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_USE_ATTRIBUTES:
			strDetails << "B_USE_ATTRIBUTES\n";
			break;
		case B_USE_RESOURCES:
			strDetails << "B_USE_RESOURCES\n";
			break;
		case B_USE_BOTH_LOCATIONS:
			strDetails << "B_USE_BOTH_LOCATIONS\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in AppFileInfo.h as:
enum version_kind {
	B_APP_VERSION_KIND,
	B_SYSTEM_VERSION_KIND
};

***************************************************************/
void
Inspect_Enum_version_kind
(
	BString& strDetails
	,	version_kind inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[version_kind enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_APP_VERSION_KIND:
			strDetails << "B_APP_VERSION_KIND\n";
			break;
		case B_SYSTEM_VERSION_KIND:
			strDetails << "B_SYSTEM_VERSION_KIND\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in ParameterWeb.h as:
enum media_parameter_flags {
	B_HIDDEN_PARAMETER = 0x1,
	B_ADVANCED_PARAMETER = 0x2
};

***************************************************************/
void
Inspect_Enum_media_parameter_flags
(
	BString& strDetails
	,	media_parameter_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_parameter_flags enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_HIDDEN_PARAMETER:
			strDetails << "B_HIDDEN_PARAMETER\n";
			break;
		case B_ADVANCED_PARAMETER:
			strDetails << "B_ADVANCED_PARAMETER\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in DirectWindow.h as:
enum direct_buffer_state {
	B_DIRECT_MODE_MASK	= 15,

	B_DIRECT_START		= 0,
	B_DIRECT_STOP		= 1,
	B_DIRECT_MODIFY		= 2,

	B_CLIPPING_MODIFIED = 16,
	B_BUFFER_RESIZED 	= 32,
	B_BUFFER_MOVED 		= 64,
	B_BUFFER_RESET	 	= 128
};

***************************************************************/
void
Inspect_Enum_direct_buffer_state
(
	BString& strDetails
	,	direct_buffer_state inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[direct_buffer_state enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DIRECT_MODE_MASK:
			strDetails << "B_DIRECT_MODE_MASK\n";
			break;
		case B_DIRECT_START:
			strDetails << "B_DIRECT_START\n";
			break;
		case B_DIRECT_STOP:
			strDetails << "B_DIRECT_STOP\n";
			break;
		case B_DIRECT_MODIFY:
			strDetails << "B_DIRECT_MODIFY\n";
			break;
		case B_CLIPPING_MODIFIED:
			strDetails << "B_CLIPPING_MODIFIED\n";
			break;
		case B_BUFFER_RESIZED:
			strDetails << "B_BUFFER_RESIZED\n";
			break;
		case B_BUFFER_MOVED:
			strDetails << "B_BUFFER_MOVED\n";
			break;
		case B_BUFFER_RESET:
			strDetails << "B_BUFFER_RESET\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in DirectWindow.h as:
enum direct_driver_state {
	B_DRIVER_CHANGED	= 0x0001,
	B_MODE_CHANGED		= 0x0002
};

***************************************************************/
void
Inspect_Enum_direct_driver_state
(
	BString& strDetails
	,	direct_driver_state inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[direct_driver_state enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DRIVER_CHANGED:
			strDetails << "B_DRIVER_CHANGED\n";
			break;
		case B_MODE_CHANGED:
			strDetails << "B_MODE_CHANGED\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in E-mail.h as:
enum	mail_flags			{B_MAIL_PENDING	= 1,	// waiting to be sent
							 B_MAIL_SENT	= 2,	// has been sent
							 B_MAIL_SAVE	= 4};	// save mail after sending

***************************************************************/
void
Inspect_Enum_mail_flags
(
	BString& strDetails
	,	mail_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mail_flags enum, " << hexbuf << "], ";
	if (B_MAIL_PENDING & inValue)
		strDetails << "B_MAIL_PENDING, ";
	if (B_MAIL_SENT & inValue)
		strDetails << "B_MAIL_SENT, ";
	if (B_MAIL_SAVE & inValue)
		strDetails << "B_MAIL_SAVE, ";

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;
	/*
		switch (inValue)
		{
			case B_MAIL_PENDING:
				strDetails << "B_MAIL_PENDING\n";
				break;
			case B_MAIL_SENT:
				strDetails << "B_MAIL_SENT\n";
				break;
			case B_MAIL_SAVE:
				strDetails << "B_MAIL_SAVE\n";
				break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


// TODO: B_USER_...
void
Inspect_Enum_directory_which
(
	BString& strDetails
	,	directory_which inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[directory_which enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DESKTOP_DIRECTORY:
			strDetails << "B_DESKTOP_DIRECTORY\n";
			break;
		case B_TRASH_DIRECTORY:
			strDetails << "B_TRASH_DIRECTORY\n";
			break;
		case B_SYSTEM_DIRECTORY:
			strDetails << "B_SYSTEM_DIRECTORY\n";
			break;
		case B_SYSTEM_ADDONS_DIRECTORY:
			strDetails << "B_SYSTEM_ADDONS_DIRECTORY\n";
			break;
		case B_SYSTEM_BOOT_DIRECTORY:
			strDetails << "B_SYSTEM_BOOT_DIRECTORY\n";
			break;
		case B_SYSTEM_FONTS_DIRECTORY:
			strDetails << "B_SYSTEM_FONTS_DIRECTORY\n";
			break;
		case B_SYSTEM_LIB_DIRECTORY:
			strDetails << "B_SYSTEM_LIB_DIRECTORY\n";
			break;
		case B_SYSTEM_SERVERS_DIRECTORY:
			strDetails << "B_SYSTEM_SERVERS_DIRECTORY\n";
			break;
		case B_SYSTEM_APPS_DIRECTORY:
			strDetails << "B_SYSTEM_APPS_DIRECTORY\n";
			break;
		case B_SYSTEM_BIN_DIRECTORY:
			strDetails << "B_SYSTEM_BIN_DIRECTORY\n";
			break;
		case B_SYSTEM_ETC_DIRECTORY:
			strDetails << "B_SYSTEM_ETC_DIRECTORY\n";
			break;
		case B_SYSTEM_DOCUMENTATION_DIRECTORY:
			strDetails << "B_SYSTEM_DOCUMENTATION_DIRECTORY\n";
			break;
		case B_SYSTEM_PREFERENCES_DIRECTORY:
			strDetails << "B_SYSTEM_PREFERENCES_DIRECTORY\n";
			break;
		case B_SYSTEM_TRANSLATORS_DIRECTORY:
			strDetails << "B_SYSTEM_TRANSLATORS_DIRECTORY\n";
			break;
		case B_SYSTEM_MEDIA_NODES_DIRECTORY:
			strDetails << "B_SYSTEM_MEDIA_NODES_DIRECTORY\n";
			break;
		case B_SYSTEM_SOUNDS_DIRECTORY:
			strDetails << "B_SYSTEM_SOUNDS_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_ADDONS_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_ADDONS_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_FONTS_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_FONTS_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_LIB_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_LIB_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_BIN_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_BIN_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_DOCUMENTATION_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_DOCUMENTATION_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_DEVELOP_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_DEVELOP_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_TRANSLATORS_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_TRANSLATORS_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_MEDIA_NODES_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_MEDIA_NODES_DIRECTORY\n";
			break;
		case B_SYSTEM_NONPACKAGED_SOUNDS_DIRECTORY:
			strDetails << "B_SYSTEM_NONPACKAGED_SOUNDS_DIRECTORY\n";
			break;
		case B_USER_DIRECTORY:
			strDetails << "B_USER_DIRECTORY\n";
			break;
		case B_USER_CONFIG_DIRECTORY:
			strDetails << "B_USER_CONFIG_DIRECTORY\n";
			break;
		case B_USER_ADDONS_DIRECTORY:
			strDetails << "B_USER_ADDONS_DIRECTORY\n";
			break;
		case B_USER_BOOT_DIRECTORY:
			strDetails << "B_USER_BOOT_DIRECTORY\n";
			break;
		case B_USER_FONTS_DIRECTORY:
			strDetails << "B_USER_FONTS_DIRECTORY\n";
			break;
		case B_USER_LIB_DIRECTORY:
			strDetails << "B_USER_LIB_DIRECTORY\n";
			break;
		case B_USER_SETTINGS_DIRECTORY:
			strDetails << "B_USER_SETTINGS_DIRECTORY\n";
			break;
		case B_USER_DESKBAR_DIRECTORY:
			strDetails << "B_USER_DESKBAR_DIRECTORY\n";
			break;
		case B_USER_PRINTERS_DIRECTORY:
			strDetails << "B_USER_PRINTERS_DIRECTORY\n";
			break;
		case B_USER_TRANSLATORS_DIRECTORY:
			strDetails << "B_USER_TRANSLATORS_DIRECTORY\n";
			break;
		case B_USER_MEDIA_NODES_DIRECTORY:
			strDetails << "B_USER_MEDIA_NODES_DIRECTORY\n";
			break;
		case B_USER_SOUNDS_DIRECTORY:
			strDetails << "B_USER_SOUNDS_DIRECTORY\n";
			break;
		case B_APPS_DIRECTORY:
			strDetails << "B_APPS_DIRECTORY\n";
			break;
		case B_PREFERENCES_DIRECTORY:
			strDetails << "B_PREFERENCES_DIRECTORY\n";
			break;
		case B_UTILITIES_DIRECTORY:
			strDetails << "B_UTILITIES_DIRECTORY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Font.h as:
enum font_metric_mode {
	B_SCREEN_METRIC		= 0,
	B_PRINTING_METRIC	= 1
};

***************************************************************/
void
Inspect_Enum_font_metric_mode
(
	BString& strDetails
	,	font_metric_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[font_metric_mode enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_SCREEN_METRIC:
			strDetails << "B_SCREEN_METRIC\n";
			break;
		case B_PRINTING_METRIC:
			strDetails << "B_PRINTING_METRIC\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in GameSoundsDefs.h as:
enum gs_attributes
{
	B_GS_NO_ATTRIBUTE = 0,			//	when there is no attribute
	B_GS_MAIN_GAIN = 1,				//	0 == 0 dB, -6.0 == -6 dB (gs_id ignored)
	B_GS_CD_THROUGH_GAIN,			//	0 == 0 dB, -12.0 == -12 dB (gs_id ignored)
										//	but which CD?
	B_GS_GAIN = 128,				//	0 == 0 dB, -1.0 == -1 dB, +10.0 == +10 dB
	B_GS_PAN,						//	0 == middle, -1.0 == left, +1.0 == right
	B_GS_SAMPLING_RATE,				//	44100.0 == 44.1 kHz
	B_GS_LOOPING,					//	0 == no
	B_GS_FIRST_PRIVATE_ATTRIBUTE = 90000,
	B_GS_FIRST_USER_ATTRIBUTE = 100000
};

not sure I've done this one correctly!
***************************************************************/
void
Inspect_Enum_gs_attributes
(
	BString& strDetails
	,	gs_attributes inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[gs_attributes enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_GS_NO_ATTRIBUTE:
			strDetails << "B_GS_NO_ATTRIBUTE\n";
			break;
		case B_GS_MAIN_GAIN:
			strDetails << "B_GS_MAIN_GAIN\n";
			break;
		case B_GS_CD_THROUGH_GAIN:
			strDetails << "B_GS_CD_THROUGH_GAIN\n";
			break;
		case B_GS_GAIN:
			strDetails << "B_GS_GAIN\n";
			break;
		case B_GS_PAN:
			strDetails << "B_GS_PAN\n";
			break;
		case B_GS_SAMPLING_RATE:
			strDetails << "B_GS_SAMPLING_RATE\n";
			break;
		case B_GS_LOOPING:
			strDetails << "B_GS_LOOPING\n";
			break;
		case B_GS_FIRST_PRIVATE_ATTRIBUTE:
			strDetails << "B_GS_FIRST_PRIVATE_ATTRIBUTE\n";
			break;
		case B_GS_FIRST_USER_ATTRIBUTE:
			strDetails << "B_GS_FIRST_USER_ATTRIBUTE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
enum buffer_orientation {
	B_BUFFER_TOP_TO_BOTTOM,
	B_BUFFER_BOTTOM_TO_TOP
};

***************************************************************/
void
Inspect_Enum_buffer_orientation
(
	BString& strDetails
	,	buffer_orientation inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[buffer_orientation enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_BUFFER_TOP_TO_BOTTOM:
			strDetails << "B_BUFFER_TOP_TO_BOTTOM\n";
			break;
		case B_BUFFER_BOTTOM_TO_TOP:
			strDetails << "B_BUFFER_BOTTOM_TO_TOP\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
enum buffer_layout {
	B_BUFFER_NONINTERLEAVED = 1
};

***************************************************************/
void
Inspect_Enum_buffer_layout
(
	BString& strDetails
	,	buffer_layout inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[buffer_layout enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_BUFFER_NONINTERLEAVED:
			strDetails << "B_BUFFER_NONINTERLEAVED\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
enum source_alpha {
	B_PIXEL_ALPHA=0,
	B_CONSTANT_ALPHA
};

***************************************************************/
void
Inspect_Enum_source_alpha
(
	BString& strDetails
	,	source_alpha inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[source_alpha enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_PIXEL_ALPHA:
			strDetails << "B_PIXEL_ALPHA\n";
			break;
		case B_CONSTANT_ALPHA:
			strDetails << "B_CONSTANT_ALPHA\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
enum alpha_function {
	B_ALPHA_OVERLAY=0,
	B_ALPHA_COMPOSITE
};

***************************************************************/
void
Inspect_Enum_alpha_function
(
	BString& strDetails
	,	alpha_function inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[alpha_function enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_ALPHA_OVERLAY:
			strDetails << "B_ALPHA_OVERLAY\n";
			break;
		case B_ALPHA_COMPOSITE:
			strDetails << "B_ALPHA_COMPOSITE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in image.h as:
typedef enum {
	B_APP_IMAGE = 1,
	B_LIBRARY_IMAGE,
	B_ADD_ON_IMAGE,
	B_SYSTEM_IMAGE
} image_type;

***************************************************************/
void
Inspect_Enum_image_type
(
	BString& strDetails
	,	image_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[image_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_APP_IMAGE:
			strDetails << "B_APP_IMAGE\n";
			break;
		case B_LIBRARY_IMAGE:
			strDetails << "B_LIBRARY_IMAGE\n";
			break;
		case B_ADD_ON_IMAGE:
			strDetails << "B_ADD_ON_IMAGE\n";
			break;
		case B_SYSTEM_IMAGE:
			strDetails << "B_SYSTEM_IMAGE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Input.h as:
enum input_method_op {
	B_INPUT_METHOD_STARTED			= 0,
	B_INPUT_METHOD_STOPPED			= 1,
	B_INPUT_METHOD_CHANGED	 		= 2,
	B_INPUT_METHOD_LOCATION_REQUEST	= 3
};

***************************************************************/
void
Inspect_Enum_input_method_op
(
	BString& strDetails
	,	input_method_op inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[input_method_op enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_INPUT_METHOD_STARTED:
			strDetails << "B_INPUT_METHOD_STARTED\n";
			break;
		case B_INPUT_METHOD_STOPPED:
			strDetails << "B_INPUT_METHOD_STOPPED\n";
			break;
		case B_INPUT_METHOD_CHANGED:
			strDetails << "B_INPUT_METHOD_CHANGED\n";
			break;
		case B_INPUT_METHOD_LOCATION_REQUEST:
			strDetails << "B_INPUT_METHOD_LOCATION_REQUEST\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Input.h as:
enum input_device_type {
	B_POINTING_DEVICE	= 0,
	B_KEYBOARD_DEVICE	= 1,
	B_UNDEFINED_DEVICE	= 2
};

***************************************************************/
void
Inspect_Enum_input_device_type
(
	BString& strDetails
	,	input_device_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[input_device_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_POINTING_DEVICE:
			strDetails << "B_POINTING_DEVICE\n";
			break;
		case B_KEYBOARD_DEVICE:
			strDetails << "B_KEYBOARD_DEVICE\n";
			break;
		case B_UNDEFINED_DEVICE:
			strDetails << "B_UNDEFINED_DEVICE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Input.h as:
enum input_device_notification {
	B_INPUT_DEVICE_ADDED 	= 0x0001,
	B_INPUT_DEVICE_STARTED	= 0x0002,
	B_INPUT_DEVICE_STOPPED	= 0x0004,
	B_INPUT_DEVICE_REMOVED	= 0x0008
};

***************************************************************/
void
Inspect_Enum_input_device_notification
(
	BString& strDetails
	,	input_device_notification inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[input_device_notification enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_INPUT_DEVICE_ADDED:
			strDetails << "B_INPUT_DEVICE_ADDED\n";
			break;
		case B_INPUT_DEVICE_STARTED:
			strDetails << "B_INPUT_DEVICE_STARTED\n";
			break;
		case B_INPUT_DEVICE_STOPPED:
			strDetails << "B_INPUT_DEVICE_STOPPED\n";
			break;
		case B_INPUT_DEVICE_REMOVED:
			strDetails << "B_INPUT_DEVICE_REMOVED\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in ListView.h as:
enum list_view_type {
	B_SINGLE_SELECTION_LIST,
	B_MULTIPLE_SELECTION_LIST
};

***************************************************************/
void
Inspect_Enum_list_view_type
(
	BString& strDetails
	,	list_view_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[list_view_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_SINGLE_SELECTION_LIST:
			strDetails << "B_SINGLE_SELECTION_LIST\n";
			break;
		case B_MULTIPLE_SELECTION_LIST:
			strDetails << "B_MULTIPLE_SELECTION_LIST\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaDefs.h as:
enum media_type {
	B_MEDIA_NO_TYPE = -1,
	B_MEDIA_UNKNOWN_TYPE = 0,
	B_MEDIA_RAW_AUDIO = 1,			// uncompressed raw_audio -- linear relationship bytes <-> samples
	B_MEDIA_RAW_VIDEO,				// uncompressed raw_video -- linear relationship bytes <-> pixels
	B_MEDIA_VBL,					// raw data from VBL area, 1600/line
	B_MEDIA_TIMECODE,				/ data format TBD
	B_MEDIA_MIDI,
	B_MEDIA_TEXT,					// typically closed captioning
	B_MEDIA_HTML,
	B_MEDIA_MULTISTREAM,			// AVI, etc
	B_MEDIA_PARAMETERS,				// BControllable change data
	B_MEDIA_ENCODED_AUDIO,			// dts, AC3, ...
	B_MEDIA_ENCODED_VIDEO,			// Indeo, MPEG, ...
	B_MEDIA_PRIVATE = 90000,		// Don't touch!
	B_MEDIA_FIRST_USER_TYPE = 100000	// Use something bigger than this for
										// experimentation with your own media forms
};

***************************************************************/
void
Inspect_Enum_media_type
(
	BString& strDetails
	,	media_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_MEDIA_NO_TYPE:
			strDetails << "B_MEDIA_NO_TYPE\n";
			break;
		case B_MEDIA_UNKNOWN_TYPE:
			strDetails << "B_MEDIA_UNKNOWN_TYPE\n";
			break;
		case B_MEDIA_RAW_AUDIO:
			strDetails << "B_MEDIA_RAW_AUDIO\n";
			break;
		case B_MEDIA_RAW_VIDEO:
			strDetails << "B_MEDIA_RAW_VIDEO\n";
			break;
		case B_MEDIA_VBL:
			strDetails << "B_MEDIA_VBL\n";
			break;
		case B_MEDIA_TIMECODE:
			strDetails << "B_MEDIA_TIMECODE\n";
			break;
		case B_MEDIA_MIDI:
			strDetails << "B_MEDIA_MIDI\n";
			break;
		case B_MEDIA_TEXT:
			strDetails << "B_MEDIA_TEXT\n";
			break;
		case B_MEDIA_HTML:
			strDetails << "B_MEDIA_HTML\n";
			break;
		case B_MEDIA_MULTISTREAM:
			strDetails << "B_MEDIA_MULTISTREAM\n";
			break;
		case B_MEDIA_PARAMETERS:
			strDetails << "B_MEDIA_PARAMETERS\n";
			break;
		case B_MEDIA_ENCODED_AUDIO:
			strDetails << "B_MEDIA_ENCODED_AUDIO\n";
			break;
		case B_MEDIA_ENCODED_VIDEO:
			strDetails << "B_MEDIA_ENCODED_VIDEO\n";
			break;
		case B_MEDIA_PRIVATE:
			strDetails << "B_MEDIA_PRIVATE\n";
			break;
		case B_MEDIA_FIRST_USER_TYPE:
			strDetails << "B_MEDIA_FIRST_USER_TYPE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaDefs.h as:
enum node_kind {
	B_BUFFER_PRODUCER = 0x1,
	B_BUFFER_CONSUMER = 0x2,
	B_TIME_SOURCE = 0x4,
	B_CONTROLLABLE = 0x8,
	B_FILE_INTERFACE = 0x10,
	B_ENTITY_INTERFACE = 0x20,
	// Set these flags for nodes that are suitable as default entities
	B_PHYSICAL_INPUT = 0x10000,
	B_PHYSICAL_OUTPUT = 0x20000,
	B_SYSTEM_MIXER = 0x40000
};

***************************************************************/
void
Inspect_Enum_node_kind
(
	BString& strDetails
	,	node_kind inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[node_kind enum, " << hexbuf << "], ";
	if (B_BUFFER_PRODUCER & inValue)
		strDetails << "B_BUFFER_PRODUCER, ";
	if (B_BUFFER_CONSUMER & inValue)
		strDetails << "B_BUFFER_CONSUMER, ";
	if (B_TIME_SOURCE & inValue)
		strDetails << "B_TIME_SOURCE, ";
	if (B_CONTROLLABLE & inValue)
		strDetails << "B_CONTROLLABLE, ";
	if (B_FILE_INTERFACE & inValue)
		strDetails << "B_FILE_INTERFACE, ";
	if (B_ENTITY_INTERFACE & inValue)
		strDetails << "B_ENTITY_INTERFACE, ";
	if (B_PHYSICAL_INPUT & inValue)
		strDetails << "B_PHYSICAL_INPUT, ";
	if (B_PHYSICAL_OUTPUT & inValue)
		strDetails << "B_PHYSICAL_OUTPUT, ";
	if (B_SYSTEM_MIXER & inValue)
		strDetails << "B_SYSTEM_MIXER, ";

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;
	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
enum video_orientation {	// for orientation, which pixel is first and how do we scan each "line"?
	B_VIDEO_TOP_LEFT_RIGHT = 1,		// This is the typical progressive scan format
	B_VIDEO_BOTTOM_LEFT_RIGHT		// This is how BMP and TGA might scan
};

***************************************************************/
void
Inspect_Enum_video_orientation
(
	BString& strDetails
	,	video_orientation inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[video_orientation enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_VIDEO_TOP_LEFT_RIGHT:
			strDetails << "B_VIDEO_TOP_LEFT_RIGHT\n";
			break;
		case B_VIDEO_BOTTOM_LEFT_RIGHT:
			strDetails << "B_VIDEO_BOTTOM_LEFT_RIGHT\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaDefs.h as:
enum media_flags
{
	B_MEDIA_FLAGS_VERSION = 1,			// uint32, bigger for newer
	B_MEDIA_FLAGS_PRIVATE = 0x40000000	// private to Be
};

Don't know exactly how to handle this one
***************************************************************/
void
Inspect_Enum_media_flags
(
	BString& strDetails
	,	media_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_flags enum, " << hexbuf << "] ";
	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
enum media_producer_status {	// for producer status
	B_DATA_NOT_AVAILABLE = 1,
	B_DATA_AVAILABLE = 2,
	B_PRODUCER_STOPPED = 3
};

***************************************************************/
void
Inspect_Enum_media_producer_status
(
	BString& strDetails
	,	media_producer_status inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_producer_status enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DATA_NOT_AVAILABLE:
			strDetails << "B_DATA_NOT_AVAILABLE\n";
			break;
		case B_DATA_AVAILABLE:
			strDetails << "B_DATA_AVAILABLE\n";
			break;
		case B_PRODUCER_STOPPED:
			strDetails << "B_PRODUCER_STOPPED\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaDefs.h as:
enum media_realtime_flags {
	B_MEDIA_REALTIME_ALLOCATOR = 0x1,
	B_MEDIA_REALTIME_AUDIO = 0x2,
	B_MEDIA_REALTIME_VIDEO = 0x4,
	B_MEDIA_REALTIME_ANYKIND = 0xffff
};

***************************************************************/
void
Inspect_Enum_media_realtime_flags
(
	BString& strDetails
	,	media_realtime_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_realtime_flags enum, " << hexbuf << "], ";
	if (B_MEDIA_REALTIME_ANYKIND == inValue)
		strDetails << "B_MEDIA_REALTIME_ANYKIND, ";
	else {
		if (B_MEDIA_REALTIME_ALLOCATOR & inValue)
			strDetails << "B_MEDIA_REALTIME_ALLOCATOR, ";
		if (B_MEDIA_REALTIME_AUDIO & inValue)
			strDetails << "B_MEDIA_REALTIME_AUDIO, ";
		if (B_MEDIA_REALTIME_VIDEO & inValue)
			strDetails << "B_MEDIA_REALTIME_VIDEO, ";
	}

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;
	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
enum media_frame_flags {
	B_MEDIA_KEY_FRAME = 0x1
};

***************************************************************/
void
Inspect_Enum_media_frame_flags
(
	BString& strDetails
	,	media_frame_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_frame_flags enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_MEDIA_KEY_FRAME:
			strDetails << "B_MEDIA_KEY_FRAME\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaDefs.h as:
enum media_multi_channels {
	B_CHANNEL_LEFT = 0x1,
	B_CHANNEL_RIGHT = 0x2,
	B_CHANNEL_CENTER = 0x4,				// 5.1+ or fake surround
	B_CHANNEL_SUB = 0x8,				// 5.1+
	B_CHANNEL_REARLEFT = 0x10,			// quad surround or 5.1+
	B_CHANNEL_REARRIGHT = 0x20,			// quad surround or 5.1+
	B_CHANNEL_FRONT_LEFT_CENTER = 0x40,
	B_CHANNEL_FRONT_RIGHT_CENTER = 0x80,
	B_CHANNEL_BACK_CENTER = 0x100,		// 6.1 or fake surround
	B_CHANNEL_SIDE_LEFT = 0x200,
	B_CHANNEL_SIDE_RIGHT = 0x400,
	B_CHANNEL_TOP_CENTER = 0x800,
	B_CHANNEL_TOP_FRONT_LEFT = 0x1000,
	B_CHANNEL_TOP_FRONT_CENTER = 0x2000,
	B_CHANNEL_TOP_FRONT_RIGHT = 0x4000,
	B_CHANNEL_TOP_BACK_LEFT = 0x8000,
	B_CHANNEL_TOP_BACK_CENTER = 0x10000,
	B_CHANNEL_TOP_BACK_RIGHT = 0x20000
};

***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
Inspect_Enum_media_multi_channels
(
	BString& strDetails
	,	media_multi_channels inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_multi_channels enum, " << hexbuf << "], ";
	if (B_CHANNEL_LEFT & inValue)
		strDetails << "B_CHANNEL_LEFT, ";
	if (B_CHANNEL_RIGHT & inValue)
		strDetails << "B_CHANNEL_RIGHT, ";
	if (B_CHANNEL_CENTER & inValue)
		strDetails << "B_CHANNEL_CENTER, ";
	if (B_CHANNEL_SUB & inValue)
		strDetails << "B_CHANNEL_SUB, ";
	if (B_CHANNEL_REARLEFT & inValue)
		strDetails << "B_CHANNEL_REARLEFT, ";
	if (B_CHANNEL_REARRIGHT & inValue)
		strDetails << "B_CHANNEL_REARRIGHT, ";
	if (B_CHANNEL_FRONT_LEFT_CENTER & inValue)
		strDetails << "B_CHANNEL_FRONT_LEFT_CENTER, ";
	if (B_CHANNEL_FRONT_RIGHT_CENTER & inValue)
		strDetails << "B_CHANNEL_FRONT_RIGHT_CENTER, ";
	if (B_CHANNEL_BACK_CENTER & inValue)
		strDetails << "B_CHANNEL_BACK_CENTER, ";
	if (B_CHANNEL_SIDE_LEFT & inValue)
		strDetails << "B_CHANNEL_SIDE_LEFT, ";
	if (B_CHANNEL_SIDE_RIGHT & inValue)
		strDetails << "B_CHANNEL_SIDE_RIGHT, ";
	if (B_CHANNEL_TOP_CENTER & inValue)
		strDetails << "B_CHANNEL_TOP_CENTER, ";
	if (B_CHANNEL_TOP_FRONT_LEFT & inValue)
		strDetails << "B_CHANNEL_TOP_FRONT_LEFT, ";
	if (B_CHANNEL_TOP_FRONT_CENTER & inValue)
		strDetails << "B_CHANNEL_TOP_FRONT_CENTER, ";
	if (B_CHANNEL_TOP_FRONT_RIGHT & inValue)
		strDetails << "B_CHANNEL_TOP_FRONT_RIGHT, ";
	if (B_CHANNEL_TOP_BACK_LEFT & inValue)
		strDetails << "B_CHANNEL_TOP_BACK_LEFT, ";
	if (B_CHANNEL_TOP_BACK_CENTER & inValue)
		strDetails << "B_CHANNEL_TOP_BACK_CENTER, ";
	if (B_CHANNEL_TOP_BACK_RIGHT & inValue)
		strDetails << "B_CHANNEL_TOP_BACK_RIGHT, ";

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;

	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}
#endif


/***************************************************************
defined in MediaDefs.h as:
enum media_multi_matrix {
	B_MATRIX_PROLOGIC_LR = 0x1,
	B_MATRIX_AMBISONIC_WXYZ = 0x4
};

TODO: Don't know how to deal with this correctly!
***************************************************************/
void
Inspect_Enum_media_multi_matrix
(
	BString& strDetails
	,	media_multi_matrix inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_multi_matrix enum, " << hexbuf << "] ";
	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
enum media_display_flags {
	B_F1_DOMINANT = 0x1,		// The first buffer sent (temporally) will be an F1 field
	B_F2_DOMINANT = 0x2,		// The first buffer sent (temporally) will be an F2 field
	B_TOP_SCANLINE_F1 = 0x4,	// The topmost scanline of the output buffer belongs to F1
	B_TOP_SCANLINE_F2 = 0x8		// The topmost scanline of the output buffer belongs to F2
};

***************************************************************/
void
Inspect_Enum_media_display_flags
(
	BString& strDetails
	,	media_display_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_display_flags enum, " << hexbuf << "], ";
	if (B_F1_DOMINANT & inValue)
		strDetails << "B_F1_DOMINANT, ";
	if (B_F2_DOMINANT & inValue)
		strDetails << "B_F2_DOMINANT, ";
	if (B_TOP_SCANLINE_F1 & inValue)
		strDetails << "B_TOP_SCANLINE_F1, ";
	if (B_TOP_SCANLINE_F2 & inValue)
		strDetails << "B_TOP_SCANLINE_F2, ";

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;

	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
enum media_format_flags {
	B_MEDIA_RETAINED_DATA = 0x1,
	B_MEDIA_MULTIPLE_BUFFERS = 0x2,
	B_MEDIA_CONTIGUOUS_BUFFER = 0x4,
	B_MEDIA_LINEAR_UPDATES = 0x8,
	B_MEDIA_MAUI_UNDEFINED_FLAGS = ~0xf // always deny these
};

***************************************************************/
void
Inspect_Enum_media_format_flags
(
	BString& strDetails
	,	media_format_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_format_flags enum, " << hexbuf << "], ";
	if (B_MEDIA_MAUI_UNDEFINED_FLAGS & inValue)
		strDetails << "B_MEDIA_MAUI_UNDEFINED_FLAGS, ";
	else {
		if (B_MEDIA_RETAINED_DATA & inValue)
			strDetails << "B_MEDIA_RETAINED_DATA, ";
		if (B_MEDIA_MULTIPLE_BUFFERS & inValue)
			strDetails << "B_MEDIA_MULTIPLE_BUFFERS, ";
		if (B_MEDIA_CONTIGUOUS_BUFFER & inValue)
			strDetails << "B_MEDIA_CONTIGUOUS_BUFFER, ";
		if (B_MEDIA_LINEAR_UPDATES & inValue)
			strDetails << "B_MEDIA_LINEAR_UPDATES, ";
	}

	strDetails.RemoveLast(",");
	strDetails << g_pNewline;
	/*
		switch (inValue)
		{
	//		case XXXXXXXXXXXXXXXX:
	//			strDetails << "XXXXXXXXXXXXXXXX\n";
	//			break;
			default:
				strDetails << "unknown\n";
				break;
		}
	*/
}


/***************************************************************
defined in MediaDefs.h as:
typedef enum {
	B_ANY_FORMAT_FAMILY = 0,
	B_BEOS_FORMAT_FAMILY = 1,
	B_QUICKTIME_FORMAT_FAMILY = 2,	// QuickTime is a registered trademark of Apple Computer
	B_AVI_FORMAT_FAMILY = 3,
	B_ASF_FORMAT_FAMILY = 4,
	B_MPEG_FORMAT_FAMILY = 5,
	B_WAV_FORMAT_FAMILY = 6,
	B_AIFF_FORMAT_FAMILY = 7,
	B_AVR_FORMAT_FAMILY = 8,

	B_MISC_FORMAT_FAMILY = 99999
} media_format_family;

***************************************************************/
void
Inspect_Enum_media_format_family
(
	BString& strDetails
	,	media_format_family inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_format_family enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_ANY_FORMAT_FAMILY:
			strDetails << "B_ANY_FORMAT_FAMILY\n";
			break;
		case B_BEOS_FORMAT_FAMILY:
			strDetails << "B_BEOS_FORMAT_FAMILY\n";
			break;
		case B_QUICKTIME_FORMAT_FAMILY:
			strDetails << "B_QUICKTIME_FORMAT_FAMILY\n";
			break;
		case B_AVI_FORMAT_FAMILY:
			strDetails << "B_AVI_FORMAT_FAMILY\n";
			break;
		case B_ASF_FORMAT_FAMILY:
			strDetails << "B_ASF_FORMAT_FAMILY\n";
			break;
		case B_MPEG_FORMAT_FAMILY:
			strDetails << "B_MPEG_FORMAT_FAMILY\n";
			break;
		case B_WAV_FORMAT_FAMILY:
			strDetails << "B_WAV_FORMAT_FAMILY\n";
			break;
		case B_AIFF_FORMAT_FAMILY:
			strDetails << "B_AIFF_FORMAT_FAMILY\n";
			break;
		case B_AVR_FORMAT_FAMILY:
			strDetails << "B_AVR_FORMAT_FAMILY\n";
			break;
		case B_MISC_FORMAT_FAMILY:
			strDetails << "B_MISC_FORMAT_FAMILY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaTrack.h as:
enum media_seek_type {
	B_MEDIA_SEEK_CLOSEST_FORWARD = 1,
	B_MEDIA_SEEK_CLOSEST_BACKWARD = 2,
	B_MEDIA_SEEK_DIRECTION_MASK = 3
};

***************************************************************/
void
Inspect_Enum_media_seek_type
(
	BString& strDetails
	,	media_seek_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_seek_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_MEDIA_SEEK_CLOSEST_FORWARD:
			strDetails << "B_MEDIA_SEEK_CLOSEST_FORWARD\n";
			break;
		case B_MEDIA_SEEK_CLOSEST_BACKWARD:
			strDetails << "B_MEDIA_SEEK_CLOSEST_BACKWARD\n";
			break;
		case B_MEDIA_SEEK_DIRECTION_MASK:
			strDetails << "B_MEDIA_SEEK_DIRECTION_MASK\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaFormst.h as:
enum media_file_accept_format_flags {
	B_MEDIA_REJECT_WILDCARDS = 0x1
};

***************************************************************/
void
Inspect_Enum_media_file_accept_format_flags
(
	BString& strDetails
	,	media_file_accept_format_flags inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_file_accept_format_flags enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_MEDIA_REJECT_WILDCARDS:
			strDetails << "B_MEDIA_REJECT_WILDCARDS\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MediaFormats.h as:
enum mpeg_id {
	B_MPEG_ANY = 0,
	B_MPEG_1_AUDIO_LAYER_1 = 0x101,
	B_MPEG_1_AUDIO_LAYER_2 = 0x102,
	B_MPEG_1_AUDIO_LAYER_3 = 0x103,		//	"MP3"
	B_MPEG_1_VIDEO = 0x111
};

***************************************************************/
void
Inspect_Enum_mpeg_id
(
	BString& strDetails
	,	mpeg_id inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mpeg_id enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_MPEG_ANY:
			strDetails << "B_MPEG_ANY\n";
			break;
		case B_MPEG_1_AUDIO_LAYER_1:
			strDetails << "B_MPEG_1_AUDIO_LAYER_1\n";
			break;
		case B_MPEG_1_AUDIO_LAYER_2:
			strDetails << "B_MPEG_1_AUDIO_LAYER_2\n";
			break;
		case B_MPEG_1_AUDIO_LAYER_3:
			strDetails << "B_MPEG_1_AUDIO_LAYER_3, MP3\n";
			break;
		case B_MPEG_1_VIDEO:
			strDetails << "B_MPEG_1_VIDEO\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Menu.h as:
enum menu_layout {
	B_ITEMS_IN_ROW = 0,
	B_ITEMS_IN_COLUMN,
	B_ITEMS_IN_MATRIX
};

***************************************************************/
void
Inspect_Enum_menu_layout
(
	BString& strDetails
	,	menu_layout inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[menu_layout enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_ITEMS_IN_ROW:
			strDetails << "B_ITEMS_IN_ROW\n";
			break;
		case B_ITEMS_IN_COLUMN:
			strDetails << "B_ITEMS_IN_COLUMN\n";
			break;
		case B_ITEMS_IN_MATRIX:
			strDetails << "B_ITEMS_IN_MATRIX\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MessageFilter.h as:
enum filter_result {
	B_SKIP_MESSAGE,
	B_DISPATCH_MESSAGE
};

***************************************************************/
void
Inspect_Enum_filter_result
(
	BString& strDetails
	,	filter_result inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[filter_result enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_SKIP_MESSAGE:
			strDetails << "B_SKIP_MESSAGE\n";
			break;
		case B_DISPATCH_MESSAGE:
			strDetails << "B_DISPATCH_MESSAGE\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MidiDefs.h as:
typedef enum synth_mode {
	B_NO_SYNTH,
	B_BIG_SYNTH,
	B_LITTLE_SYNTH,
	B_DEFAULT_SYNTH,
	B_SAMPLES_ONLY
} synth_mode;

***************************************************************/
void
Inspect_Enum_synth_mode
(
	BString& strDetails
	,	synth_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[synth_mode enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_NO_SYNTH:
			strDetails << "B_NO_SYNTH\n";
			break;
		case B_BIG_SYNTH:
			strDetails << "B_BIG_SYNTH\n";
			break;
		case B_LITTLE_SYNTH:
			strDetails << "B_LITTLE_SYNTH\n";
			break;
		case B_DEFAULT_SYNTH:
			strDetails << "B_DEFAULT_SYNTH\n";
			break;
		case B_SAMPLES_ONLY:
			strDetails << "B_SAMPLES_ONLY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in MidiDefs.h as:
typedef enum midi_axe {

  // Pianos
  B_ACOUSTIC_GRAND=0,
  B_BRIGHT_GRAND,
  B_ELECTRIC_GRAND,
  B_HONKY_TONK,
  B_ELECTRIC_PIANO_1,
  B_ELECTRIC_PIANO_2,
  B_HARPSICHORD,
  B_CLAVICHORD,

  // Tuned Idiophones
  B_CELESTA,
  B_GLOCKENSPIEL,
  B_MUSIC_BOX,
  B_VIBRAPHONE,
  B_MARIMBA,
  B_XYLOPHONE,
  B_TUBULAR_BELLS,
  B_DULCIMER,

  // Organs
  B_DRAWBAR_ORGAN,
  B_PERCUSSIVE_ORGAN,
  B_ROCK_ORGAN,
  B_CHURCH_ORGAN,
  B_REED_ORGAN,
  B_ACCORDION,
  B_HARMONICA,
  B_TANGO_ACCORDION,

  // Guitars
  B_ACOUSTIC_GUITAR_NYLON,
  B_ACOUSTIC_GUITAR_STEEL,
  B_ELECTRIC_GUITAR_JAZZ,
  B_ELECTRIC_GUITAR_CLEAN,
  B_ELECTRIC_GUITAR_MUTED,
  B_OVERDRIVEN_GUITAR,
  B_DISTORTION_GUITAR,
  B_GUITAR_HARMONICS,

  // Basses
  B_ACOUSTIC_BASS,
  B_ELECTRIC_BASS_FINGER,
  B_ELECTRIC_BASS_PICK,
  B_FRETLESS_BASS,
  B_SLAP_BASS_1,
  B_SLAP_BASS_2,
  B_SYNTH_BASS_1,
  B_SYNTH_BASS_2,

  // Strings
  B_VIOLIN,
  B_VIOLA,
  B_CELLO,
  B_CONTRABASS,
  B_TREMOLO_STRINGS,
  B_PIZZICATO_STRINGS,
  B_ORCHESTRAL_STRINGS,
  B_TIMPANI,

  // Ensemble strings and voices
  B_STRING_ENSEMBLE_1,
  B_STRING_ENSEMBLE_2,
  B_SYNTH_STRINGS_1,
  B_SYNTH_STRINGS_2,
  B_VOICE_AAH,
  B_VOICE_OOH,
  B_SYNTH_VOICE,
  B_ORCHESTRA_HIT,

  // Brass
  B_TRUMPET,
  B_TROMBONE,
  B_TUBA,
  B_MUTED_TRUMPET,
  B_FRENCH_HORN,
  B_BRASS_SECTION,
  B_SYNTH_BRASS_1,
  B_SYNTH_BRASS_2,

  // Reeds
  B_SOPRANO_SAX,
  B_ALTO_SAX,
  B_TENOR_SAX,
  B_BARITONE_SAX,
  B_OBOE,
  B_ENGLISH_HORN,
  B_BASSOON,
  B_CLARINET,

  // Pipes
  B_PICCOLO,
  B_FLUTE,
  B_RECORDER,
  B_PAN_FLUTE,
  B_BLOWN_BOTTLE,
  B_SHAKUHACHI,
  B_WHISTLE,
  B_OCARINA,

  // Synth Leads
  B_LEAD_1,
  B_SQUARE_WAVE = B_LEAD_1,
  B_LEAD_2,
  B_SAWTOOTH_WAVE = B_LEAD_2,
  B_LEAD_3,
  B_CALLIOPE = B_LEAD_3,
  B_LEAD_4,
  B_CHIFF = B_LEAD_4,
  B_LEAD_5,
  B_CHARANG = B_LEAD_5,
  B_LEAD_6,
  B_VOICE = B_LEAD_6,
  B_LEAD_7,
  B_FIFTHS = B_LEAD_7,
  B_LEAD_8,
  B_BASS_LEAD = B_LEAD_8,

  // Synth Pads
  B_PAD_1,
  B_NEW_AGE = B_PAD_1,
  B_PAD_2,
  B_WARM = B_PAD_2,
  B_PAD_3,
  B_POLYSYNTH = B_PAD_3,
  B_PAD_4,
  B_CHOIR = B_PAD_4,
  B_PAD_5,
  B_BOWED = B_PAD_5,
  B_PAD_6,
  B_METALLIC = B_PAD_6,
  B_PAD_7,
  B_HALO = B_PAD_7,
  B_PAD_8,
  B_SWEEP = B_PAD_8,

  // Effects
  B_FX_1,
  B_FX_2,
  B_FX_3,
  B_FX_4,
  B_FX_5,
  B_FX_6,
  B_FX_7,
  B_FX_8,

  // Ethnic
  B_SITAR,
  B_BANJO,
  B_SHAMISEN,
  B_KOTO,
  B_KALIMBA,
  B_BAGPIPE,
  B_FIDDLE,
  B_SHANAI,

  // Percussion
  B_TINKLE_BELL,
  B_AGOGO,
  B_STEEL_DRUMS,
  B_WOODBLOCK,
  B_TAIKO_DRUMS,
  B_MELODIC_TOM,
  B_SYNTH_DRUM,
  B_REVERSE_CYMBAL,

  // Sound Effects
  B_FRET_NOISE,
  B_BREATH_NOISE,
  B_SEASHORE,
  B_BIRD_TWEET,
  B_TELEPHONE,
  B_HELICOPTER,
  B_APPLAUSE,
  B_GUNSHOT
} midi_axe;

***************************************************************/
void
Inspect_Enum_midi_axe
(
	BString& strDetails
	,	midi_axe inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[midi_axe enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_ACOUSTIC_GRAND:
			strDetails << "B_ACOUSTIC_GRAND\n";
			break;
		case B_BRIGHT_GRAND:
			strDetails << "B_BRIGHT_GRAND\n";
			break;
		case B_ELECTRIC_GRAND:
			strDetails << "B_ELECTRIC_GRAND\n";
			break;
		case B_HONKY_TONK:
			strDetails << "B_HONKY_TONK\n";
			break;
		case B_ELECTRIC_PIANO_1:
			strDetails << "B_ELECTRIC_PIANO_1\n";
			break;
		case B_ELECTRIC_PIANO_2:
			strDetails << "B_ELECTRIC_PIANO_2\n";
			break;
		case B_HARPSICHORD:
			strDetails << "B_HARPSICHORD\n";
			break;
		case B_CLAVICHORD:
			strDetails << "B_CLAVICHORD\n";
			break;
		case B_CELESTA:
			strDetails << "B_CELESTA\n";
			break;
		case B_GLOCKENSPIEL:
			strDetails << "B_GLOCKENSPIEL\n";
			break;
		case B_MUSIC_BOX:
			strDetails << "B_MUSIC_BOX\n";
			break;
		case B_VIBRAPHONE:
			strDetails << "B_VIBRAPHONE\n";
			break;
		case B_MARIMBA:
			strDetails << "B_MARIMBA\n";
			break;
		case B_XYLOPHONE:
			strDetails << "B_XYLOPHONE\n";
			break;
		case B_TUBULAR_BELLS:
			strDetails << "B_TUBULAR_BELLS\n";
			break;
		case B_DULCIMER:
			strDetails << "B_DULCIMER\n";
			break;
		case B_DRAWBAR_ORGAN:
			strDetails << "B_DRAWBAR_ORGAN\n";
			break;
		case B_PERCUSSIVE_ORGAN:
			strDetails << "B_PERCUSSIVE_ORGAN\n";
			break;
		case B_ROCK_ORGAN:
			strDetails << "B_ROCK_ORGAN\n";
			break;
		case B_CHURCH_ORGAN:
			strDetails << "B_CHURCH_ORGAN\n";
			break;
		case B_REED_ORGAN:
			strDetails << "B_REED_ORGAN\n";
			break;
		case B_ACCORDION:
			strDetails << "B_ACCORDION\n";
			break;
		case B_HARMONICA:
			strDetails << "B_HARMONICA\n";
			break;
		case B_TANGO_ACCORDION:
			strDetails << "B_TANGO_ACCORDION\n";
			break;
		case B_ACOUSTIC_GUITAR_NYLON:
			strDetails << "B_ACOUSTIC_GUITAR_NYLON\n";
			break;
		case B_ACOUSTIC_GUITAR_STEEL:
			strDetails << "B_ACOUSTIC_GUITAR_STEEL\n";
			break;
		case B_ELECTRIC_GUITAR_JAZZ:
			strDetails << "B_ELECTRIC_GUITAR_JAZZ\n";
			break;
		case B_ELECTRIC_GUITAR_CLEAN:
			strDetails << "B_ELECTRIC_GUITAR_CLEAN\n";
			break;
		case B_ELECTRIC_GUITAR_MUTED:
			strDetails << "B_ELECTRIC_GUITAR_MUTED\n";
			break;
		case B_OVERDRIVEN_GUITAR:
			strDetails << "B_OVERDRIVEN_GUITAR\n";
			break;
		case B_DISTORTION_GUITAR:
			strDetails << "B_DISTORTION_GUITAR\n";
			break;
		case B_GUITAR_HARMONICS:
			strDetails << "B_GUITAR_HARMONICS\n";
			break;
		case B_ACOUSTIC_BASS:
			strDetails << "B_ACOUSTIC_BASS\n";
			break;
		case B_ELECTRIC_BASS_FINGER:
			strDetails << "B_ELECTRIC_BASS_FINGER\n";
			break;
		case B_ELECTRIC_BASS_PICK:
			strDetails << "B_ELECTRIC_BASS_PICK\n";
			break;
		case B_FRETLESS_BASS:
			strDetails << "B_FRETLESS_BASS\n";
			break;
		case B_SLAP_BASS_1:
			strDetails << "B_SLAP_BASS_1\n";
			break;
		case B_SLAP_BASS_2:
			strDetails << "B_SLAP_BASS_2\n";
			break;
		case B_SYNTH_BASS_1:
			strDetails << "B_SYNTH_BASS_1\n";
			break;
		case B_SYNTH_BASS_2:
			strDetails << "B_SYNTH_BASS_2\n";
			break;
		case B_VIOLIN:
			strDetails << "B_VIOLIN\n";
			break;
		case B_VIOLA:
			strDetails << "B_VIOLA\n";
			break;
		case B_CELLO:
			strDetails << "B_CELLO\n";
			break;
		case B_CONTRABASS:
			strDetails << "B_CONTRABASS\n";
			break;
		case B_TREMOLO_STRINGS:
			strDetails << "B_TREMOLO_STRINGS\n";
			break;
		case B_PIZZICATO_STRINGS:
			strDetails << "B_PIZZICATO_STRINGS\n";
			break;
		case B_ORCHESTRAL_STRINGS:
			strDetails << "B_ORCHESTRAL_STRINGS\n";
			break;
		case B_TIMPANI:
			strDetails << "B_TIMPANI\n";
			break;
		case B_STRING_ENSEMBLE_1:
			strDetails << "B_STRING_ENSEMBLE_1\n";
			break;
		case B_STRING_ENSEMBLE_2:
			strDetails << "B_STRING_ENSEMBLE_2\n";
			break;
		case B_SYNTH_STRINGS_1:
			strDetails << "B_SYNTH_STRINGS_1\n";
			break;
		case B_SYNTH_STRINGS_2:
			strDetails << "B_SYNTH_STRINGS_2\n";
			break;
		case B_VOICE_AAH:
			strDetails << "B_VOICE_AAH\n";
			break;
		case B_VOICE_OOH:
			strDetails << "B_VOICE_OOH\n";
			break;
		case B_SYNTH_VOICE:
			strDetails << "B_SYNTH_VOICE\n";
			break;
		case B_ORCHESTRA_HIT:
			strDetails << "B_ORCHESTRA_HIT\n";
			break;
		case B_TRUMPET:
			strDetails << "B_TRUMPET\n";
			break;
		case B_TROMBONE:
			strDetails << "B_TROMBONE\n";
			break;
		case B_TUBA:
			strDetails << "B_TUBA\n";
			break;
		case B_MUTED_TRUMPET:
			strDetails << "B_MUTED_TRUMPET\n";
			break;
		case B_FRENCH_HORN:
			strDetails << "B_FRENCH_HORN\n";
			break;
		case B_BRASS_SECTION:
			strDetails << "B_BRASS_SECTION\n";
			break;
		case B_SYNTH_BRASS_1:
			strDetails << "B_SYNTH_BRASS_1\n";
			break;
		case B_SYNTH_BRASS_2:
			strDetails << "B_SYNTH_BRASS_2\n";
			break;
		case B_SOPRANO_SAX:
			strDetails << "B_SOPRANO_SAX\n";
			break;
		case B_ALTO_SAX:
			strDetails << "B_ALTO_SAX\n";
			break;
		case B_TENOR_SAX:
			strDetails << "B_TENOR_SAX\n";
			break;
		case B_BARITONE_SAX:
			strDetails << "B_BARITONE_SAX\n";
			break;
		case B_OBOE:
			strDetails << "B_OBOE\n";
			break;
		case B_ENGLISH_HORN:
			strDetails << "B_ENGLISH_HORN\n";
			break;
		case B_BASSOON:
			strDetails << "B_BASSOON\n";
			break;
		case B_CLARINET:
			strDetails << "B_CLARINET\n";
			break;
		case B_PICCOLO:
			strDetails << "B_PICCOLO\n";
			break;
		case B_FLUTE:
			strDetails << "B_FLUTE\n";
			break;
		case B_RECORDER:
			strDetails << "B_RECORDER\n";
			break;
		case B_PAN_FLUTE:
			strDetails << "B_PAN_FLUTE\n";
			break;
		case B_BLOWN_BOTTLE:
			strDetails << "B_BLOWN_BOTTLE\n";
			break;
		case B_SHAKUHACHI:
			strDetails << "B_SHAKUHACHI\n";
			break;
		case B_WHISTLE:
			strDetails << "B_WHISTLE\n";
			break;
		case B_OCARINA:
			strDetails << "B_OCARINA\n";
			break;
//		case B_LEAD_1:
		case B_SQUARE_WAVE:
			strDetails << "B_LEAD_1 or B_SQUARE_WAVE\n";
			break;
//		case B_LEAD_2:
		case B_SAWTOOTH_WAVE:
			strDetails << "B_LEAD_2 or B_SAWTOOTH_WAVE\n";
			break;
//		case B_LEAD_3:
		case B_CALLIOPE:
			strDetails << "B_LEAD_3 or B_CALLIOPE\n";
			break;
//		case B_LEAD_4:
		case B_CHIFF:
			strDetails << "B_LEAD_4 or B_CHIFF\n";
			break;
//		case B_LEAD_5:
		case B_CHARANG:
			strDetails << "B_LEAD_5 or B_CHARANG\n";
			break;
//		case B_LEAD_6:
		case B_VOICE:
			strDetails << "B_LEAD_6 or B_VOICE\n";
			break;
//		case B_LEAD_7:
		case B_FIFTHS:
			strDetails << "B_LEAD_7 or B_FIFTHS\n";
			break;
//		case B_LEAD_8:
		case B_BASS_LEAD:
			strDetails << "B_LEAD_8 or B_BASS_LEAD\n";
			break;
		case B_NEW_AGE:
			strDetails << "B_NEW_AGE\n";
			break;
		case B_WARM:
			strDetails << "B_WARM\n";
			break;
		case B_POLYSYNTH:
			strDetails << "B_POLYSYNTH\n";
			break;
		case B_CHOIR:
			strDetails << "B_CHOIR\n";
			break;
		case B_BOWED:
			strDetails << "B_BOWED\n";
			break;
		case B_METALLIC:
			strDetails << "B_METALLIC\n";
			break;
		case B_HALO:
			strDetails << "B_HALO\n";
			break;
		case B_SWEEP:
			strDetails << "B_SWEEP\n";
			break;
		case B_FX_1:
			strDetails << "B_FX_1\n";
			break;
		case B_FX_2:
			strDetails << "B_FX_2\n";
			break;
		case B_FX_3:
			strDetails << "B_FX_3\n";
			break;
		case B_FX_4:
			strDetails << "B_FX_4\n";
			break;
		case B_FX_5:
			strDetails << "B_FX_5\n";
			break;
		case B_FX_6:
			strDetails << "B_FX_6\n";
			break;
		case B_FX_7:
			strDetails << "B_FX_7\n";
			break;
		case B_FX_8:
			strDetails << "B_FX_8\n";
			break;
		case B_SITAR:
			strDetails << "B_SITAR\n";
			break;
		case B_BANJO:
			strDetails << "B_BANJO\n";
			break;
		case B_SHAMISEN:
			strDetails << "B_SHAMISEN\n";
			break;
		case B_KOTO:
			strDetails << "B_KOTO\n";
			break;
		case B_KALIMBA:
			strDetails << "B_KALIMBA\n";
			break;
		case B_BAGPIPE:
			strDetails << "B_BAGPIPE\n";
			break;
		case B_FIDDLE:
			strDetails << "B_FIDDLE\n";
			break;
		case B_SHANAI:
			strDetails << "B_SHANAI\n";
			break;
		case B_TINKLE_BELL:
			strDetails << "B_TINKLE_BELL\n";
			break;
		case B_AGOGO:
			strDetails << "B_AGOGO\n";
			break;
		case B_STEEL_DRUMS:
			strDetails << "B_STEEL_DRUMS\n";
			break;
		case B_WOODBLOCK:
			strDetails << "B_WOODBLOCK\n";
			break;
		case B_TAIKO_DRUMS:
			strDetails << "B_TAIKO_DRUMS\n";
			break;
		case B_MELODIC_TOM:
			strDetails << "B_MELODIC_TOM\n";
			break;
		case B_SYNTH_DRUM:
			strDetails << "B_SYNTH_DRUM\n";
			break;
		case B_REVERSE_CYMBAL:
			strDetails << "B_REVERSE_CYMBAL\n";
			break;
		case B_FRET_NOISE:
			strDetails << "B_FRET_NOISE\n";
			break;
		case B_BREATH_NOISE:
			strDetails << "B_BREATH_NOISE\n";
			break;
		case B_SEASHORE:
			strDetails << "B_SEASHORE\n";
			break;
		case B_BIRD_TWEET:
			strDetails << "B_BIRD_TWEET\n";
			break;
		case B_TELEPHONE:
			strDetails << "B_TELEPHONE\n";
			break;
		case B_HELICOPTER:
			strDetails << "B_HELICOPTER\n";
			break;
		case B_APPLAUSE:
			strDetails << "B_APPLAUSE\n";
			break;
		case B_GUNSHOT:
			strDetails << "B_GUNSHOT\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Mime.h as:
enum icon_size {
	B_LARGE_ICON = 32,
	B_MINI_ICON = 16
};

***************************************************************/
void
Inspect_Enum_icon_size
(
	BString& strDetails
	,	icon_size inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[icon_size enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_LARGE_ICON:
			strDetails << "B_LARGE_ICON\n";
			break;
		case B_MINI_ICON:
			strDetails << "B_MINI_ICON\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in OS.h as:
typedef enum {
	B_THREAD_RUNNING=1,
	B_THREAD_READY,
	B_THREAD_RECEIVING,
	B_THREAD_ASLEEP,
	B_THREAD_SUSPENDED,
	B_THREAD_WAITING
} thread_state;

***************************************************************/
void
Inspect_Enum_thread_state
(
	BString& strDetails
	,	thread_state inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[thread_state enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_THREAD_RUNNING:
			strDetails << "B_THREAD_RUNNING\n";
			break;
		case B_THREAD_READY:
			strDetails << "B_THREAD_READY\n";
			break;
		case B_THREAD_RECEIVING:
			strDetails << "B_THREAD_RECEIVING\n";
			break;
		case B_THREAD_ASLEEP:
			strDetails << "B_THREAD_ASLEEP\n";
			break;
		case B_THREAD_SUSPENDED:
			strDetails << "B_THREAD_SUSPENDED\n";
			break;
		case B_THREAD_WAITING:
			strDetails << "B_THREAD_WAITING\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}

/***************************************************************
defined in PropertyInfo.h as:
enum value_kind {
	B_COMMAND_KIND = 0,
	B_TYPE_CODE_KIND = 1
};

***************************************************************/
void
Inspect_Enum_value_kind
(
	BString& strDetails
	,	value_kind inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[value_kind enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_COMMAND_KIND:
			strDetails << "B_COMMAND_KIND\n";
			break;
		case B_TYPE_CODE_KIND:
			strDetails << "B_TYPE_CODE_KIND\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Query.h as:
typedef enum {
	B_INVALID_OP = 0,
	B_EQ,
	B_GT,
	B_GE,
	B_LT,
	B_LE,
	B_NE,
	B_CONTAINS,
	B_BEGINS_WITH,
	B_ENDS_WITH,
	B_AND = 0x101,
	B_OR,
	B_NOT,
	_B_RESERVED_OP_ = 0x100000
} query_op;

***************************************************************/
void
Inspect_Enum_query_op
(
	BString& strDetails
	,	query_op inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[query_op enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_INVALID_OP:
			strDetails << "B_INVALID_OP\n";
			break;
		case B_EQ:
			strDetails << "B_EQ\n";
			break;
		case B_GT:
			strDetails << "B_GT\n";
			break;
		case B_GE:
			strDetails << "B_GE\n";
			break;
		case B_LT:
			strDetails << "B_LT\n";
			break;
		case B_LE:
			strDetails << "B_LE\n";
			break;
		case B_NE:
			strDetails << "B_NE\n";
			break;
		case B_CONTAINS:
			strDetails << "B_CONTAINS\n";
			break;
		case B_BEGINS_WITH:
			strDetails << "B_BEGINS_WITH\n";
			break;
		case B_ENDS_WITH:
			strDetails << "B_ENDS_WITH\n";
			break;
		case B_AND:
			strDetails << "B_AND\n";
			break;
		case B_OR:
			strDetails << "B_OR\n";
			break;
		case B_NOT:
			strDetails << "B_NOT\n";
			break;
		case _B_RESERVED_OP_:
			strDetails << "_B_RESERVED_OP_\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in SerialPort.h as:
enum data_rate { B_0_BPS = 0, B_50_BPS, B_75_BPS, B_110_BPS, B_134_BPS,
				 B_150_BPS, B_200_BPS, B_300_BPS, B_600_BPS, B_1200_BPS,
				 B_1800_BPS, B_2400_BPS, B_4800_BPS, B_9600_BPS, B_19200_BPS,
				 B_38400_BPS, B_57600_BPS, B_115200_BPS,
				 B_230400_BPS, B_31250_BPS };

***************************************************************/
void
Inspect_Enum_data_rate
(
	BString& strDetails
	,	data_rate inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[data_rate enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_0_BPS:
			strDetails << "B_0_BPS\n";
			break;
		case B_50_BPS:
			strDetails << "B_50_BPS\n";
			break;
		case B_75_BPS:
			strDetails << "B_75_BPS\n";
			break;
		case B_110_BPS:
			strDetails << "B_110_BPS\n";
			break;
		case B_134_BPS:
			strDetails << "B_134_BPS\n";
			break;
		case B_150_BPS:
			strDetails << "B_150_BPS\n";
			break;
		case B_200_BPS:
			strDetails << "B_200_BPS\n";
			break;
		case B_300_BPS:
			strDetails << "B_300_BPS\n";
			break;
		case B_600_BPS:
			strDetails << "B_600_BPS\n";
			break;
		case B_1200_BPS:
			strDetails << "B_1200_BPS\n";
			break;
		case B_1800_BPS:
			strDetails << "B_1800_BPS\n";
			break;
		case B_2400_BPS:
			strDetails << "B_2400_BPS\n";
			break;
		case B_4800_BPS:
			strDetails << "B_4800_BPS\n";
			break;
		case B_9600_BPS:
			strDetails << "B_9600_BPS\n";
			break;
		case B_19200_BPS:
			strDetails << "B_19200_BPS\n";
			break;
		case B_38400_BPS:
			strDetails << "B_38400_BPS\n";
			break;
		case B_57600_BPS:
			strDetails << "B_57600_BPS\n";
			break;
		case B_115200_BPS:
			strDetails << "B_115200_BPS\n";
			break;
		case B_230400_BPS:
			strDetails << "B_230400_BPS\n";
			break;
		case B_31250_BPS:
			strDetails << "B_31250_BPS\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in SerialPort.h as:
enum data_bits { B_DATA_BITS_7, B_DATA_BITS_8 };

***************************************************************/
void
Inspect_Enum_data_bits
(
	BString& strDetails
	,	data_bits inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[data_bits enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DATA_BITS_7:
			strDetails << "B_DATA_BITS_7\n";
			break;
		case B_DATA_BITS_8:
			strDetails << "B_DATA_BITS_8\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in SerialPort.h as:
enum stop_bits { B_STOP_BITS_1, B_STOP_BITS_2 };

***************************************************************/
void
Inspect_Enum_stop_bits
(
	BString& strDetails
	,	stop_bits inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[stop_bits enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_STOP_BITS_1:
			strDetails << "B_STOP_BITS_1\n";
			break;
		case B_STOP_BITS_2:
			strDetails << "B_STOP_BITS_2\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in SerialPort.h as:
enum parity_mode { B_NO_PARITY, B_ODD_PARITY, B_EVEN_PARITY };

***************************************************************/
void
Inspect_Enum_parity_mode
(
	BString& strDetails
	,	parity_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[parity_mode enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_NO_PARITY:
			strDetails << "B_NO_PARITY\n";
			break;
		case B_ODD_PARITY:
			strDetails << "B_ODD_PARITY\n";
			break;
		case B_EVEN_PARITY:
			strDetails << "B_EVEN_PARITY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in StorageDefs.h as:
enum node_flavor {
  B_FILE_NODE=0x01,
  B_SYMLINK_NODE=0x02,
  B_DIRECTORY_NODE=0x04,
  B_ANY_NODE= 0x07
};

***************************************************************/
void
Inspect_Enum_node_flavor
(
	BString& strDetails
	,	node_flavor inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent(B_EMPTY_STRING);
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[node_flavor enum, " << hexbuf << "] ";

	if (B_ANY_NODE == inValue)
		strDetails << "B_ANY_NODE\n";
	else {
		if (B_FILE_NODE == (B_FILE_NODE & inValue))
			strDetails << "B_FILE_NODE \n";
		if (B_SYMLINK_NODE == (B_SYMLINK_NODE & inValue))
			strDetails << "B_SYMLINK_NODE \n";
		if (B_DIRECTORY_NODE == (B_DIRECTORY_NODE & inValue))
			strDetails << "B_DIRECTORY_NODE \n";
	}
}


/***************************************************************
defined in Synth.h as:
typedef enum interpolation_mode
{
    B_DROP_SAMPLE = 0,
    B_2_POINT_INTERPOLATION,
    B_LINEAR_INTERPOLATION
  } interpolation_mode;

***************************************************************/
void
Inspect_Enum_interpolation_mode
(
	BString& strDetails
	,	interpolation_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[interpolation_mode enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_DROP_SAMPLE:
			strDetails << "B_DROP_SAMPLE\n";
			break;
		case B_2_POINT_INTERPOLATION:
			strDetails << "B_2_POINT_INTERPOLATION\n";
			break;
		case B_LINEAR_INTERPOLATION:
			strDetails << "B_LINEAR_INTERPOLATION\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Synth.h as:
typedef enum reverb_mode
{
	B_REVERB_NONE = 1,
	B_REVERB_CLOSET,
	B_REVERB_GARAGE,
	B_REVERB_BALLROOM,
	B_REVERB_CAVERN,
	B_REVERB_DUNGEON
  } reverb_mode;

***************************************************************/
void
Inspect_Enum_reverb_mode
(
	BString& strDetails
	,	reverb_mode inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[reverb_mode enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_REVERB_NONE:
			strDetails << "B_REVERB_NONE\n";
			break;
		case B_REVERB_CLOSET:
			strDetails << "B_REVERB_CLOSET\n";
			break;
		case B_REVERB_GARAGE:
			strDetails << "B_REVERB_GARAGE\n";
			break;
		case B_REVERB_BALLROOM:
			strDetails << "B_REVERB_BALLROOM\n";
			break;
		case B_REVERB_CAVERN:
			strDetails << "B_REVERB_CAVERN\n";
			break;
		case B_REVERB_DUNGEON:
			strDetails << "B_REVERB_DUNGEON\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in TabView.h as:
enum tab_position {
	B_TAB_FIRST = 999,
	B_TAB_FRONT,
	B_TAB_ANY
};

***************************************************************/
void
Inspect_Enum_tab_position
(
	BString& strDetails
	,	tab_position inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[tab_position enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_TAB_FIRST:
			strDetails << "B_TAB_FIRST\n";
			break;
		case B_TAB_FRONT:
			strDetails << "B_TAB_FRONT\n";
			break;
		case B_TAB_ANY:
			strDetails << "B_TAB_ANY\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in TimeCode.h as:
// Time code is always in the form HH:MM:SS:FF, it's the definition of FF that varies
enum timecode_type {
	B_TIMECODE_DEFAULT,
	B_TIMECODE_100,
	B_TIMECODE_75,			// CD
	B_TIMECODE_30,			// MIDI
	B_TIMECODE_30_DROP_2,	// NTSC
	B_TIMECODE_30_DROP_4,	// Brazil
	B_TIMECODE_25,			// PAL
	B_TIMECODE_24,			// Film
	B_TIMECODE_18			// Super8
};

***************************************************************/
void
Inspect_Enum_timecode_type
(
	BString& strDetails
	,	timecode_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[timecode_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_TIMECODE_DEFAULT:
			strDetails << "B_TIMECODE_DEFAULT\n";
			break;
		case B_TIMECODE_100:
			strDetails << "B_TIMECODE_100\n";
			break;
		case B_TIMECODE_75:
			strDetails << "B_TIMECODE_75\n";
			break;
		case B_TIMECODE_30:
			strDetails << "B_TIMECODE_30\n";
			break;
		case B_TIMECODE_30_DROP_2:
			strDetails << "B_TIMECODE_30_DROP_2\n";
			break;
		case B_TIMECODE_30_DROP_4:
			strDetails << "B_TIMECODE_30_DROP_4\n";
			break;
		case B_TIMECODE_25:
			strDetails << "B_TIMECODE_25\n";
			break;
		case B_TIMECODE_24:
			strDetails << "B_TIMECODE_24\n";
			break;
		case B_TIMECODE_18:
			strDetails << "B_TIMECODE_18\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Window.h as:
enum window_alignment {
	B_BYTE_ALIGNMENT	= 0,
	B_PIXEL_ALIGNMENT	= 1
};

***************************************************************/
void
Inspect_Enum_window_alignment
(
	BString& strDetails
	,	window_alignment inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[window_alignment enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_BYTE_ALIGNMENT:
			strDetails << "B_BYTE_ALIGNMENT\n";
			break;
		case B_PIXEL_ALIGNMENT:
			strDetails << "B_PIXEL_ALIGNMENT\n";
			break;
		default:
			strDetails << "unknown\n";
			break;
	}
}


/***************************************************************
defined in Alert.h as:
enum alert_type {
	B_EMPTY_ALERT = 0,
	B_INFO_ALERT,
	B_IDEA_ALERT,
	B_WARNING_ALERT,
	B_STOP_ALERT
};
***************************************************************/
void
Inspect_Enum_alert_type
(
	BString& strDetails
	,	alert_type inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[alert_type enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_EMPTY_ALERT:
			strDetails << "B_EMPTY_ALERT\n";
			break;
		case B_INFO_ALERT:
			strDetails << "B_INFO_ALERT\n";
			break;
		case B_IDEA_ALERT:
			strDetails << "B_IDEA_ALERT\n";
			break;
		case B_WARNING_ALERT:
			strDetails << "B_WARNING_ALERT\n";
			break;
		case B_STOP_ALERT:
			strDetails << "B_STOP_ALERT\n";
			break;
		default:
			strDetails << "unknown\n";
	}
}


/***************************************************************
defined in Alert.h as:
enum button_spacing {
	B_EVEN_SPACING = 0,
	B_OFFSET_SPACING
};
***************************************************************/
void
Inspect_Enum_button_spacing
(
	BString& strDetails
	,	button_spacing inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[button_spacing enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_EVEN_SPACING:
			strDetails << "B_EVEN_SPACING\n";
			break;
		case B_OFFSET_SPACING:
			strDetails << "B_OFFSET_SPACING\n";
			break;
		default:
			strDetails << "unknown\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
enum TranslatorGroups {
	B_TRANSLATOR_BITMAP			=	'bits',		//	TranslatorBitmap
	B_TRANSLATOR_PICTURE		=	'pict',		//	BPicture data
	B_TRANSLATOR_TEXT			=	'TEXT',		//	B_ASCII_TYPE
	B_TRANSLATOR_SOUND			=	'nois',		//	TranslatorSound
	B_TRANSLATOR_MIDI			=	'midi',		//	standard MIDI
	B_TRANSLATOR_MEDIA			=	'mhi!',		//	a stream of stuff
	B_TRANSLATOR_NONE			=	'none',
	B_TRANSLATOR_ANY_TYPE		=	0
};
***************************************************************/
void
Inspect_Enum_TranslatorGroups
(
	BString& strDetails
	,	TranslatorGroups inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i < inIndent; i++)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorGroups enum, " << hexbuf << "] ";

	switch (inValue) {
		case B_TRANSLATOR_BITMAP:
			strDetails << "B_TRANSLATOR_BITMAP ('bits')\n";
			break;
		case B_TRANSLATOR_PICTURE:
			strDetails << "B_TRANSLATOR_PICTURE ('pict')\n";
			break;
		case B_TRANSLATOR_TEXT:
			strDetails << "B_TRANSLATOR_TEXT ('TEXT')\n";
			break;
		case B_TRANSLATOR_SOUND:
			strDetails << "B_TRANSLATOR_SOUND ('nois')\n";
			break;
		case B_TRANSLATOR_MIDI:
			strDetails << "B_TRANSLATOR_MIDI ('midi')\n";
			break;
		case B_TRANSLATOR_MEDIA:
			strDetails << "B_TRANSLATOR_MEDIA ('mhi!')\n";
			break;
		case B_TRANSLATOR_NONE:
			strDetails << "B_TRANSLATOR_NONE ('none')\n";
			break;
		case B_TRANSLATOR_ANY_TYPE:
			strDetails << "B_TRANSLATOR_ANY_TYPE\n";
			break;
		default:
			strDetails << "unknown\n";
	}
}




