#include <Be.h>

//#include "Inspect_Enums.h"
//#include "InspectOther.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "InspectDeviceKitObjects.h"
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
Inspect_BSerialPort
(
	BString& strDetails
	,	BSerialPort* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSerialPort object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSerialPort was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BJoystick
(
	BString& strDetails
	,	BJoystick* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BJoystick object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BJoystick was NULL\n";
}




