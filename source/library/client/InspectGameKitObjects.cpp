#include <Be.h>

//#include "Inspect_Enums.h"
//#include "InspectOther.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "InspectGameKitObjects.h"
#include "utility.h"


//char CodeUnknown[5] = "    ";
//char buf[200 + B_PATH_NAME_LENGTH] = "";
//char TypeCodeUnknown[20] = "";

extern const char* pTrue;
extern const char* pFalse;
extern const char* g_pIndentation;
extern const char* g_pFailedWithError;
extern const char* g_pNewline;


/***************************************************************
***************************************************************/
void
Inspect_BStreamingGameSound
(
	BString& strDetails
	,	BStreamingGameSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BStreamingGameSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BStreamingGameSound was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSimpleGameSound
(
	BString& strDetails
	,	BSimpleGameSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSimpleGameSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSimpleGameSound was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BPushGameSound
(
	BString& strDetails
	,	BPushGameSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BPushGameSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BPushGameSound was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BFileGameSound
(
	BString& strDetails
	,	BFileGameSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BFileGameSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BFileGameSound was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BDirectWindow
(
	BString& strDetails
	,	BDirectWindow* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BDirectWindow object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BDirectWindow was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BGameSound
(
	BString& strDetails
	,	BGameSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BGameSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BGameSound was NULL\n";
}




