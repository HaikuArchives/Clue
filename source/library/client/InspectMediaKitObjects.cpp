#include <Be.h>
#include <MediaEncoder.h>

//#include "Inspect_Enums.h"
//#include "InspectOther.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "InspectMediaKitObjects.h"
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
Inspect_BMediaEncoder
(
	BString& strDetails
	,	BMediaEncoder* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaEncoder object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaEncoder was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMultiChannelControl
(
	BString& strDetails
	,	BMultiChannelControl* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMultiChannelControl object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMultiChannelControl was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BBuffer
(
	BString& strDetails
	,	BBuffer* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BBuffer object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BBuffer was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSmallBuffer
(
	BString& strDetails
	,	BSmallBuffer* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSmallBuffer object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSmallBuffer was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BBufferConsumer
(
	BString& strDetails
	,	BBufferConsumer* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BBufferConsumer object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BBufferConsumer was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BBufferGroup
(
	BString& strDetails
	,	BBufferGroup* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BBufferGroup object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BBufferGroup was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BBufferProducer
(
	BString& strDetails
	,	BBufferProducer* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BBufferProducer object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BBufferProducer was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BParameterWeb
(
	BString& strDetails
	,	BParameterWeb* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BParameterWeb object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BParameterWeb was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BParameterGroup
(
	BString& strDetails
	,	BParameterGroup* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BParameterGroup object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BParameterGroup was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BParameter
(
	BString& strDetails
	,	BParameter* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[v object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BParameter was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BContinuousParameter
(
	BString& strDetails
	,	BContinuousParameter* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BContinuousParameter object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BContinuousParameter was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BDiscreteParameter
(
	BString& strDetails
	,	BDiscreteParameter* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BDiscreteParameter object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BDiscreteParameter was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BNullParameter
(
	BString& strDetails
	,	BNullParameter* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BNullParameter object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BNullParameter was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BControllable
(
	BString& strDetails
	,	BControllable* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BControllable object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BControllable was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaTheme
(
	BString& strDetails
	,	BMediaTheme* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaTheme object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaTheme was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaAddOn
(
	BString& strDetails
	,	BMediaAddOn* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaAddOn object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaAddOn was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaDecoder
(
	BString& strDetails
	,	BMediaDecoder* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaDecoder object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaDecoder was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaEventLooper
(
	BString& strDetails
	,	BMediaEventLooper* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaEventLooper object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaEventLooper was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaFile
(
	BString& strDetails
	,	BMediaFile* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaFile object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaFile was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaFiles
(
	BString& strDetails
	,	BMediaFiles* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaFiles object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaFiles was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_media_node
(
	BString& strDetails
	,	media_node* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_node object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The media_node was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaNode
(
	BString& strDetails
	,	BMediaNode* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaNode object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaNode was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaRoster
(
	BString& strDetails
	,	BMediaRoster* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaRoster object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaRoster was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaTrack
(
	BString& strDetails
	,	BMediaTrack* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaTrack object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaTrack was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BMediaFormats
(
	BString& strDetails
	,	BMediaFormats* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMediaFormats object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BMediaFormats was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSound
(
	BString& strDetails
	,	BSound* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSound was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSoundFile
(
	BString& strDetails
	,	BSoundFile* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSoundFile object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSoundFile was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BSoundPlayer
(
	BString& strDetails
	,	BSoundPlayer* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BSoundPlayer object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BSoundPlayer was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BTimeCode
(
	BString& strDetails
	,	BTimeCode* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTimeCode object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BTimeCode was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BTimedEventQueue
(
	BString& strDetails
	,	BTimedEventQueue* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTimedEventQueue object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BTimedEventQueue was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BTimeSource
(
	BString& strDetails
	,	BTimeSource* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BTimeSource object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BTimeSource was NULL\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BFileInterface
(
	BString& strDetails
	,	BFileInterface* inValue
	,	int32 inIndent
	,	const char* pDescription
)
{
	BString tabindent;
	for (int32 i(0); i++ < inIndent;)
		tabindent << g_pIndentation;

	char hexbuf[20];
	GetHexString(hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BFileInterface object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue) {
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	} else
		strDetails << tabindent << "The BFileInterface was NULL\n";
}




