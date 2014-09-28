#include <Be.h>

#include "Inspect_Enums.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "InspectSupportKitObjects.h"
//#include "InspectOther.h"
#include "utility.h"

//extern const char * pTrue;
//extern const char * pFalse;
extern const char * g_pIndentation;
//extern const char * g_pFailedWithError;
extern const char * g_pNewline;


/***************************************************************
***************************************************************/
void
Inspect_BStopWatch
	(
	BString & strDetails
,	BStopWatch * inValue
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
	strDetails << tabindent << pDescription << "[BStopWatch object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "ElapsedTime= " << inValue->ElapsedTime () << g_pNewline;
		strDetails << tabindent << "Name= " << inValue->Name () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BStopWatch was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BLocker
	(
	BString & strDetails
,	BLocker * inValue
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
	strDetails << tabindent << pDescription << "[BLocker object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "not coded in this release!" << g_pNewline;

		int32 aInt32 (inValue->LockingThread ());
		if (B_ERROR != aInt32)
			strDetails << tabindent << "LockingThread= " << aInt32 << g_pNewline;
		else
			strDetails << tabindent << "LockingThread= B_ERROR\n";

		strDetails << tabindent << "IsLocked= " << (int) inValue->IsLocked () << g_pNewline;
		strDetails << tabindent << "CountLocks= " << inValue->CountLocks () << g_pNewline;
		strDetails << tabindent << "CountLockRequests= " << inValue->CountLockRequests () << g_pNewline;
		strDetails << tabindent << "Sem= " << inValue->Sem () << g_pNewline;

		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BLocker was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BBufferIO
	(
	BString & strDetails
,	BBufferIO * inValue
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
	strDetails << tabindent << pDescription << "[BBufferIO object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "Position= " << inValue->Position () << g_pNewline;
		strDetails << tabindent << "BufferSize= " << inValue->BufferSize () << g_pNewline;
		
		//OwndStream and SetOwnsStream seem to be missing in libBe.so for the BBufferIO class!!!
		//strDetails << tabindent << "OwnsStream= " << inValue->OwnsStream () << g_pNewline;
		//inValue->SetOwnsStream (true);  not that I would call this function from libClue, don't want to change object

		//baseclass BPositionIO is a pure virtual base class, can't inspect it.
	}
	else
	{
		strDetails << tabindent << "The BBufferIO was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BString
	(
	BString & strDetails
,	BString * inValue
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
	strDetails << tabindent << pDescription << "[BString object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "not coded in this release!" << g_pNewline;

		strDetails << tabindent << "CountChars= " << inValue->CountChars () << g_pNewline;
		strDetails << tabindent << "Length= " << inValue->Length () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BString was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BList
	(
	BString & strDetails
,	BList * inValue
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
	strDetails << tabindent << pDescription << "[BList object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "not coded in this release!" << g_pNewline;

//		int32 aInt32 (inValue->CountItems ());
		strDetails << tabindent << "CountItems= " << inValue->CountItems () << g_pNewline;

//		bool aBool (inValue->IsEmpty ());
		strDetails << tabindent << "IsEmpty= " << (int) inValue->IsEmpty () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BList was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BAutolock
	(
	BString & strDetails
,	BAutolock * inValue
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
	strDetails << tabindent << pDescription << "[BAutolock object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "not coded in this release!" << g_pNewline;

		strDetails << tabindent << "IsLocked= " << (int) inValue->IsLocked () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BAutolock was NULL\n";
	}
}




