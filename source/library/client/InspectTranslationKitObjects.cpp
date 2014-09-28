#include <Be.h>

//#include "Inspect_Enums.h"
//#include "InspectOther.h"
#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "InspectOther.h"
#include "InspectTranslationKitObjects.h"
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
Inspect_BTranslator
	(
	BString & strDetails
,	BTranslator * inValue
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
	strDetails << tabindent << pDescription << "[BTranslator object, ptr=" << hexbuf << "]\n";
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
		strDetails << tabindent << "The BTranslator was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BTranslatorRoster
	(
	BString & strDetails
,	BTranslatorRoster * inValue
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
	strDetails << tabindent << pDescription << "[BTranslatorRoster object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "not coded in this release!" << g_pNewline;

		int32 aInt32A (0);
		int32 aInt32B (0);
		const char * pChar (inValue->Version (&aInt32A, &aInt32B));

		if (NULL != pChar)
			strDetails << tabindent << "Version= " << pChar << ", CurVersion= " << aInt32A << ", MinVersion= " << aInt32B << g_pNewline;
		else
			strDetails << tabindent << "Version= " << ", CurVersion= " << aInt32A << ", MinVersion= " << aInt32B << g_pNewline;

		translator_id * ids (NULL);
		int32 count (0);
		status_t aStatusT (inValue->GetAllTranslators (&ids, &count));
		if (B_OK == aStatusT)
		{
			strDetails << tabindent << "GetAllTranslators= " << "count= " << count << g_pNewline;
			for (int tix = 0; tix < count; tix++)
			{
				const translation_format * formats (NULL);
				int32 num_formats (0);
				aStatusT = inValue->GetInputFormats(ids[tix], &formats, &num_formats);
				if (B_OK == aStatusT)
				{
					strDetails << tabindent << "GetInputFormats[" << tix << "]= " << "num_formats= " << num_formats << g_pNewline;
					for (int iix = 0; iix < num_formats; iix++)
					{
						//strDetails << tabindent << g_pNewline;
//						Inspect_Struct_translation_format (strDetails, formats[iix], inIndent + 1, "  + GetInputFormats ");
						//if (formats[iix].type == from_type)
					}
				}
				else
				{
					BString tmp ("GetInputFormats[");
					tmp << tix << "]: failed, ";
					GetStatusTDescription (strDetails, aStatusT, inIndent, tmp.String ());
				}

			    aStatusT = inValue->GetOutputFormats (ids[tix], &formats, &num_formats);
			    if (aStatusT == B_OK)
			    {
					strDetails << tabindent << "GetOutputFormats[" << tix << "]= " << "num_formats= " << num_formats << g_pNewline;
					for (int oix = 0; oix < num_formats; oix++)
					{
//						Inspect_Struct_translation_format (strDetails, formats[oix], inIndent + 1, "  + GetOutputFormats ");
						//if (formats[oix].type != from_type)
					} 
				}
				else
				{
					BString tmp ("GetOutputFormats[");
					tmp << tix << "]: failed, ";
					GetStatusTDescription (strDetails, aStatusT, inIndent, tmp.String ());
				}
				
				const char * pCharName (NULL);
				const char * pCharInfo (NULL);
				int32 aInt32 (0);
				aStatusT = inValue->GetTranslatorInfo (ids[tix], &pCharName, &pCharInfo, &aInt32);
				if (B_OK == aStatusT)
				{
					strDetails << tabindent << "GetTranslatorInfo= " << pChar << ", CurVersion= " << aInt32A << ", MinVersion= " << aInt32B << g_pNewline;
				}
				else
				{
					BString tmp ("GetTranslatorInfo[");
					tmp << tix << "]: failed, ";
					GetStatusTDescription (strDetails, aStatusT, inIndent, tmp.String ());
				}
				
				BMessage aBMessage;
				aStatusT = inValue->GetConfigurationMessage (ids[tix], &aBMessage);
				if (B_OK == aStatusT)
				{
					Inspect_BMessage (strDetails, &aBMessage, inIndent + 1, "  + GetConfigurationMessage ", 1, 1);
				}
				else
				{
					BString tmp ("GetConfigurationMessage[");
					tmp << tix << "]: failed, ";
					GetStatusTDescription (strDetails, aStatusT, inIndent, tmp.String ());
				}
				
				delete[] ids;
			}
  		}
		else
		{
			GetStatusTDescription (strDetails, aStatusT, inIndent, "GetAllTranslators: failed, ");
		}

		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BTranslatorRoster was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BBitmapStream
	(
	BString & strDetails
,	BBitmapStream * inValue
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
	strDetails << tabindent << pDescription << "[BBitmapStream object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "Position= " << inValue->Position () << g_pNewline;
		strDetails << tabindent << "Size= " << inValue->Size () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BBitmapStream was NULL\n";
	}
}




