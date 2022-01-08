#include <Be.h>

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectApplicationKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "InspectOther.h"
#include "utility.h"

extern const char* pTrue;
extern const char* pFalse;
extern const char* g_pIndentation;
extern const char* g_pFailedWithError;
extern const char* g_pNewline;
/***************************************************************
***************************************************************/
void
Inspect_BNodeInfo
(
	BString& strDetails
	,	BNodeInfo* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BNodeInfo object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		strDetails << tabindent << "InitCheck= ";
		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			strDetails << "B_OK\n";

			strDetails << tabindent << "GetAppHint: ";
			entry_ref aEntryRef;
			aStatusT = inValue->GetAppHint(&aEntryRef);
			if (B_OK == aStatusT)
				Inspect_Struct_entry_ref(strDetails, &aEntryRef, inIndent, B_EMPTY_STRING);
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			char aChar[B_MIME_TYPE_LENGTH + 1];
			aStatusT = inValue->GetPreferredApp(aChar);
			strDetails << tabindent << "GetPreferredApp= ";
			if (B_OK == aStatusT)
				strDetails << aChar << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			aStatusT = inValue->GetType(aChar);
			strDetails << tabindent << "GetType= ";
			if (B_OK == aStatusT)
				strDetails << aChar << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");
		} else
			GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");
	} else
		strDetails << "The BNodeInfo was NULL\n";
}
/***************************************************************
defined in storage/AppFileInfo.h
***************************************************************/
void
Inspect_BAppFileInfo
(
	BString& strDetails
	,	BAppFileInfo* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;

	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BAppFileInfo object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;
			++inIndent;

			strDetails << tabindent << "InitCheck= B_OK\n";
			uint32 aUInt32(0);
			inValue->GetAppFlags(&aUInt32);
			strDetails << tabindent << "GetAppFlags: (" << aUInt32 << ")";
			switch (B_LAUNCH_MASK & aUInt32) {
				case B_SINGLE_LAUNCH:
					strDetails << "B_SINGLE_LAUNCH,";
					break;
				case B_MULTIPLE_LAUNCH:
					strDetails << "B_MULTIPLE_LAUNCH,";
					break;
				case B_EXCLUSIVE_LAUNCH:
					strDetails << "B_EXCLUSIVE_LAUNCH,";
					break;
			}
			if (B_BACKGROUND_APP & aUInt32)
				strDetails << "B_BACKGROUND_APP,";
			if (B_ARGV_ONLY & aUInt32)
				strDetails << "B_ARGV_ONLY,";
			strDetails.RemoveLast(",");
			strDetails << g_pNewline;

			char aChar[B_MIME_TYPE_LENGTH + 1];
			aStatusT = inValue->GetSignature(aChar);
			strDetails << tabindent << "GetSignature= ";
			if (B_OK == aStatusT)
				strDetails << aChar << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			strDetails << tabindent << "GetSupportedTypes: ";
			BMessage msg;
			uint32 i(0);
			char* ptr(NULL);

			aStatusT = inValue->GetSupportedTypes(&msg);
			if (B_OK == aStatusT) {
				strDetails << g_pNewline;
				while (B_OK == msg.FindString("types", i++, (const char**) &ptr))
					strDetails << tabindent << "  |  Type=" << ptr << g_pNewline;
			} else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			version_info aVersionInfo;
			aStatusT = inValue->GetVersionInfo(&aVersionInfo, B_APP_VERSION_KIND);
			if (B_OK == aStatusT)
				Inspect_Struct_version_info(strDetails, &aVersionInfo, inIndent, "GetVersionInfo(B_APP_VERSION_KIND): ");
			else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetVersionInfo(B_APP_VERSION_KIND): failed, ");

			aStatusT = inValue->GetVersionInfo(&aVersionInfo, B_SYSTEM_VERSION_KIND);
			if (B_OK == aStatusT)
				Inspect_Struct_version_info(strDetails, &aVersionInfo, inIndent, "GetVersionInfo(B_SYSTEM_VERSION_KIND) ");
			else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetVersionInfo(B_SYSTEM_VERSION_KIND): failed, ");

			strDetails << tabindent << "IsUsingAttributes= " << (inValue->IsUsingAttributes() ? pTrue : pFalse);
			strDetails << tabindent << "IsUsingResources= " << (inValue->IsUsingResources() ? pTrue : pFalse);

			/*TODO
						if (DoBaseClasses)
						{
							strDetails << tabindent << g_pNewline;
							Inspect_BNodeInfo (strDetails, (BNodeInfo *) inValue, --inIndent, "  + BAppFileInfo baseclass ");
						}
			*/
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= failed, ");
	} else
		strDetails << "The BAppFileInfo was NULL\n";
}
/***************************************************************
***************************************************************/
void
Inspect_BStatable
(
	BString& strDetails
	,	BStatable* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BStatable object, ptr=" << hexbuf << "]\n";
//		strDetails << tabindent << "---- BStatable properties ----\n";
		tabindent << g_pIndentation;
		++inIndent;

		time_t aTimeT;
		status_t aStatusT(B_ERROR);
		aStatusT = inValue->GetCreationTime(&aTimeT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetCreationTime= " << aTimeT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetCreationTime: failed, ");

		aStatusT = inValue->GetModificationTime(&aTimeT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetModificationTime= " << aTimeT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetModificationTime: failed, ");

		aStatusT = inValue->GetAccessTime(&aTimeT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetAccessTime= " << aTimeT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetAccessTime: failed, ");

		uid_t aUidT(0);
		aStatusT = inValue->GetOwner(&aUidT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetOwner= " << aUidT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetOwner: failed, ");

		gid_t aGidT(0);
		aStatusT = inValue->GetGroup(&aGidT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetGroup= " << aGidT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetGroup: failed, ");

		mode_t aModeT(0);
		aStatusT = inValue->GetPermissions(&aModeT);
		if (B_OK == aStatusT)
			Inspect_Flags_mode_t (strDetails, aModeT, inIndent, "GetPermissions: ");
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetPermissions: failed, ");

		off_t aOffT(0);
		aStatusT = inValue->GetSize(&aOffT);
		if (B_OK == aStatusT)
			strDetails << tabindent << "GetSize= " << aOffT << g_pNewline;
		else
			GetStatusTDescription(strDetails, aStatusT, inIndent, "GetSize: failed, ");

		strDetails << tabindent << "IsFile= " << (inValue->IsFile() ? pTrue : pFalse);
		strDetails << tabindent << "IsDirectory= " << (inValue->IsDirectory() ? pTrue : pFalse);
		strDetails << tabindent << "IsSymLink= " << (inValue->IsSymLink() ? pTrue : pFalse);
	} else
		strDetails << "The BStatable was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BNode
(
	BString& strDetails
	,	BNode* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BNode object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;

			strDetails << tabindent << "InitCheck= B_OK\n";


			inValue->RewindAttrs();
			/* Print every attribute name. */
			char buf[B_ATTR_NAME_LENGTH];
			strDetails << tabindent << "GetNextAttrName list:\n";

			while (B_OK == inValue->GetNextAttrName(buf))
				strDetails << tabindent << "  |  name= " << buf << g_pNewline;

			/*TODO
						if (DoBaseClasses)
						{
							strDetails << tabindent << g_pNewline;
							Inspect_BStatable (strDetails, (BStatable *) inValue, inIndent, "  + BNode baseclass ");
						}
			*/
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= ");
	} else
		strDetails << "The BNode was NULL\n";
}


/***************************************************************
defined in storage/EntryList.h
***************************************************************/
void
Inspect_BEntryList
(
	BString& strDetails
	,	BEntryList* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BEntryList object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "CountEntries= " << inValue->CountEntries() << g_pNewline;
	} else
		strDetails << "The BEntryList was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BDirectory
(
	BString& strDetails
	,	BDirectory* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BDirectory object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;

			strDetails << tabindent << "InitCheck= B_OK\n";
			strDetails << tabindent << "CountEntries= " << inValue->CountEntries() << g_pNewline;
			strDetails << tabindent << "IsRootDirectory= " << (inValue->IsRootDirectory() ? pTrue : pFalse);

			/*TODO
						if (DoBaseClasses)
						{
							strDetails << tabindent << g_pNewline;
							Inspect_BNode (strDetails, (BNode *) inValue, inIndent, "  + BDirectory baseclass ", true);
							strDetails << tabindent << g_pNewline;
							Inspect_BEntryList (strDetails, (BEntryList *) inValue, inIndent, "  + BDirectory baseclass ");
						}
			*/
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= ");
	} else
		strDetails << "The BDirectory was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BEntry
(
	BString& strDetails
	,	BEntry* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BEntry object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;
			++inIndent;

			strDetails << tabindent << "InitCheck= B_OK\n";

			strDetails << tabindent << "Exists= " << (inValue->Exists() ? pTrue : pFalse);
			char name[B_FILE_NAME_LENGTH];
			char* pStr(name);
			strDetails << tabindent << "GetName= ";
			status_t aStatusT(inValue->GetName(name));
			if (B_OK == aStatusT)
				strDetails << (NULL != pStr ? name : "NULL\n");
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			BPath aPath;
			aStatusT = inValue->GetPath(&aPath);
			if (B_OK == aStatusT)
				Inspect_BPath(strDetails, &aPath, inIndent, "GetPath: ");
			else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetPath: failed, ");

			entry_ref aEntryRef;
			aStatusT = inValue->GetRef(&aEntryRef);
			if (B_OK == aStatusT)
				Inspect_Struct_entry_ref(strDetails, &aEntryRef, inIndent, "GetRef: ");
			else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetRef: failed, ");

			/*TODO
						if (DoBaseClasses)
						{
							strDetails << tabindent << g_pNewline;
							Inspect_BStatable (strDetails, (BStatable *) inValue, --inIndent, "  + BEntry baseclass ");
						}
			*/
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= ");
	} else
		strDetails << "The BEntry was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BPath
(
	BString& strDetails
	,	BPath* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {

		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPath object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "InitCheck= ";
		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			strDetails << "B_OK\n";

			const char* pChar(inValue->Leaf());
			strDetails << tabindent << "Leaf= " << (NULL != pChar ? pChar : "NULL");
			strDetails << g_pNewline;

			pChar = inValue->Path();
			strDetails << tabindent << "Path= " << (NULL != pChar ? pChar : "NULL");
			strDetails << g_pNewline;
		} else
			GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");
	} else
		strDetails << "The BPath was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BFile
(
	BString& strDetails
	,	BFile* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BFile object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;

			strDetails << tabindent << "InitCheck= B_OK\n";

			strDetails << tabindent << "IsReadable= " << (inValue->IsReadable() ? pTrue : pFalse);
			strDetails << tabindent << "IsWritable= " << (inValue->IsWritable() ? pTrue : pFalse);

			/*TODO
						if (DoBaseClasses)
						{
							strDetails << tabindent << g_pNewline;
							Inspect_BNode (strDetails, (BNode *) inValue, inIndent, "  + BFile baseclass ", true);
							strDetails << tabindent << g_pNewline;
							Inspect_BPositionIO (strDetails, (BPositionIO *) inValue, inIndent, "  + BFile baseclass ");
						}
			*/
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= failed, ");
	} else
		strDetails << "The BFile was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BPositionIO
(
	BString& strDetails
	,	BPositionIO* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BPositionIO object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		strDetails << tabindent << "Position= " << inValue->Position() << g_pNewline;
	} else
		strDetails << "The BPositionIO was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BFilePanel
(
	BString& strDetails
	,	BFilePanel* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {

		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BFilePanel object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

//		BWindow * aWindow (inValue->Window ());
//		if (NULL != aWindow)
//		{
//			if (aWindow->IsLocked ())
//			{
		file_panel_mode aFPM(inValue->PanelMode());
		Inspect_Enum_file_panel_mode(strDetails, aFPM, inIndent, "PanelMode: ");

		strDetails << tabindent << "HidesWhenDone= " << (inValue->HidesWhenDone() ? pTrue : pFalse);

		entry_ref aEntryRef;
		inValue->GetPanelDirectory(&aEntryRef);

		BRefFilter* aRefFilter(inValue->RefFilter());
		//do inspection here!!!

		BMessenger aMessenger(inValue->Messenger());
		Inspect_BMessenger(strDetails, &aMessenger, inIndent, "GetMessenger: ");

		strDetails << tabindent << "IsShowing= " << (inValue->IsShowing() ? pTrue : pFalse);
//			}
//			else
//			{
//				strDetails << tabindent << "The BLooper must be locked before Clue can continue!\n";
//			}
//		}
//		else
//		{
//			strDetails << "The BFilePanels BWindow was invalid.\n";
//		}
	} else
		strDetails << "The BFilePanel was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMimeType
(
	BString& strDetails
	,	BMimeType* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BMimeType object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;
		++inIndent;

		strDetails << tabindent << "InitCheck= ";
		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			strDetails << "B_OK\n";

			entry_ref aEntryRef;
			aStatusT = inValue->GetAppHint(&aEntryRef);
			if (B_OK == aStatusT)
				Inspect_Struct_entry_ref(strDetails, &aEntryRef, inIndent, "GetAppHint: ");
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "GetAppHint: failed, ");

			BMessage aMessage;
			aStatusT = inValue->GetAttrInfo(&aMessage);
			if (B_OK == aStatusT) {
				strDetails << tabindent << "GetAttrInfo: \n";
				Inspect_BMessage(strDetails, &aMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);
			} else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetAttrInfo: failed, ");

			aStatusT = inValue->GetFileExtensions(&aMessage);
			if (B_OK == aStatusT) {
				strDetails << tabindent << "GetFileExtensions: \n";
				Inspect_BMessage(strDetails, &aMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);
			} else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetFileExtensions: failed, ");

			strDetails << tabindent << "GetLongDescription: ";

			char aChar [B_MIME_TYPE_LENGTH + 1];
			char* pChar(aChar);
			aStatusT = inValue->GetLongDescription(aChar);
			if (B_OK == aStatusT)
				strDetails << (NULL != pChar ? pChar : "NULL\n");
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			strDetails << tabindent << "GetShortDescription: ";
			aStatusT = inValue->GetShortDescription(aChar);
			if (B_OK == aStatusT)
				strDetails << (NULL != pChar ? pChar : "NULL") << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			strDetails << tabindent << "GetPreferredApp= ";
			aStatusT = inValue->GetPreferredApp(aChar);
			if (B_OK == aStatusT)
				strDetails << (NULL != pChar ? pChar : "NULL") << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");

			aMessage.MakeEmpty();  //making sure it's cleared out before calling
			aStatusT = inValue->GetSupportingApps(&aMessage);
			if (B_OK == aStatusT) {
				int32 subs(0);
				int32 supers(0);

				strDetails << tabindent << "GetSupportingApps:\n";
				if ((B_OK == aMessage.FindInt32("be:sub", &subs)) && (B_OK == aMessage.FindInt32("be:super", &supers))) {
					int32 n(0);
					for (; n < subs; n++) {
						if (B_OK == aMessage.FindString("applications", n, (const char**) &pChar))
							strDetails << tabindent << g_pIndentation << "Full support: " << pChar << g_pNewline;
						else
							strDetails << tabindent << g_pIndentation << "bad BMessage format.\n";
					}
					int32 hold(n);
					for (n = 0; n < supers; n++) {
						if (B_OK == aMessage.FindString("applications", n + hold, (const char**) &pChar))
							strDetails << tabindent << g_pIndentation << "Supertype support: " << pChar << g_pNewline;
						else
							strDetails << tabindent << g_pIndentation << "bad BMessage format.\n";
					}
				} else
					strDetails << tabindent << g_pIndentation << "bad BMessage returned.\n";

			} else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetSupportingApps: failed, ");

			strDetails << tabindent << "IsInstalled= " << (inValue->IsInstalled() ? pTrue : pFalse);
			strDetails << tabindent << "IsValid= " << (inValue->IsValid() ? pTrue : pFalse);
			strDetails << tabindent << "IsSupertypeOnly= " << (inValue->IsSupertypeOnly() ? pTrue : pFalse);

			char const* pTypeChar(inValue->Type());
			strDetails << tabindent << "Type= " << (NULL != pTypeChar ? pTypeChar : "NULL") << g_pNewline;
		} else
			GetStatusTDescription(strDetails, aStatusT, 0, "failed, ");
	} else
		strDetails << "The BMimeType was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BVolume
(
	BString& strDetails
	,	BVolume* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	if (NULL != inValue) {
		char hexbuf[20];
		GetHexString(hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BVolume object, ptr=" << hexbuf << "]\n";

		status_t aStatusT(inValue->InitCheck());
		if (B_OK == aStatusT) {
			tabindent << g_pIndentation;
			++inIndent;

			strDetails << tabindent << "InitCheck= B_OK\n";

			strDetails << tabindent << "Capacity= " << inValue->Capacity() << g_pNewline;
			strDetails << tabindent << "FreeBytes= " << inValue->FreeBytes() << g_pNewline;
			strDetails << tabindent << "Device= " << inValue->Device() << g_pNewline;

			char aChar[B_FILE_NAME_LENGTH + 1];
			status_t aStatusT(inValue->GetName(aChar));
			if (B_OK == aStatusT)
				strDetails << tabindent << "GetName= " << (NULL != aChar ? aChar : "NULL") << g_pNewline;
			else
				GetStatusTDescription(strDetails, aStatusT, inIndent, "GetName= failed, ");

			BDirectory aDirectory;
			aStatusT = inValue->GetRootDirectory(&aDirectory);
			if (B_OK == aStatusT) {
				strDetails << tabindent << "GetRootDirectory:\n";
				Inspect_BDirectory(strDetails, &aDirectory, ++inIndent, B_EMPTY_STRING);
			} else
				GetStatusTDescription(strDetails, aStatusT, ++inIndent, "GetRootDirectory= failed, ");

			strDetails << tabindent << "IsPersistent= " << (inValue->IsPersistent() ? pTrue : pFalse);
			strDetails << tabindent << "IsRemovable= " << (inValue->IsRemovable() ? pTrue : pFalse);
			strDetails << tabindent << "IsReadOnly= " << (inValue->IsReadOnly() ? pTrue : pFalse);
			strDetails << tabindent << "IsShared= " << (inValue->IsShared() ? pTrue : pFalse);
			strDetails << tabindent << "KnowsAttr= " << (inValue->KnowsAttr() ? pTrue : pFalse);
			strDetails << tabindent << "KnowsMime= " << (inValue->KnowsMime() ? pTrue : pFalse);
			strDetails << tabindent << "KnowsQuery= " << (inValue->KnowsQuery() ? pTrue : pFalse);
		} else
			GetStatusTDescription(strDetails, aStatusT, ++inIndent, "InitCheck= ");
	} else
		strDetails << "The BVolume was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BVolumeRoster
(
	BString& strDetails
	,	BVolumeRoster* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BVolumeRoster object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BVolumeRoster was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSymLink
(
	BString& strDetails
	,	BSymLink* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSymLink object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSymLink was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BResources
(
	BString& strDetails
	,	BResources* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BResources object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BResources was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BResourceStrings
(
	BString& strDetails
	,	BResourceStrings* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BResourceStrings object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BResourceStrings was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BQuery
(
	BString& strDetails
	,	BQuery* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BQuery object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BQuery was NULL\n";
}
