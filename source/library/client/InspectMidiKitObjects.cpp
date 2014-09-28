#include <Be.h>

//#include "Inspect_Enums.h"
//#include "InspectOther.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
#include "InspectMidiKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "utility.h"


//char CodeUnknown[5] = "    ";
//char buf[200 + B_PATH_NAME_LENGTH] = "";
//char TypeCodeUnknown[20] = "";

extern const char * pTrue;
extern const char * pFalse;
extern const char * g_pIndentation;
extern const char * g_pFailedWithError;
extern const char * g_pNewline;


/***************************************************************
***************************************************************/
void
Inspect_BMidi
	(
	BString & strDetails
,	BMidi * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidi object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidi was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMidiPort
	(
	BString & strDetails
,	BMidiPort * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidiPort object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidiPort was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMidiStore
	(
	BString & strDetails
,	BMidiStore * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidiStore object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidiStore was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMidiSynth
	(
	BString & strDetails
,	BMidiSynth * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidiSynth object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidiSynth was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMidiSynthFile
	(
	BString & strDetails
,	BMidiSynthFile * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidiSynthFile object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidiSynthFile was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMidiText
	(
	BString & strDetails
,	BMidiText * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BMidiText object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BMidiText was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BSynth
	(
	BString & strDetails
,	BSynth * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BSynth object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BSynth was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BSamples
	(
	BString & strDetails
,	BSamples * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[12];
	GetHexString (hexbuf, (int32) inValue);
	strDetails << tabindent << pDescription << "[BSamples object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BSamples was NULL\n";
	}
}




