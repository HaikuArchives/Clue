//
// Clue - Clue Fact - Tracks the data on an event.
// Copyright 1999-2006 Jeff Braun and Mathew Hounsell.
// All rights reserved. Distributed under the terms of the MIT License.
//

#if !defined(CLUE_EVENT_H_)
#include "ClueFact.h"
#endif

#include <Be.h>
#include <assert.h>
#include <string.h>

//==============================================================================
// Clue Fact Constants

int32 const								ClueFact::ARCHIVE_FORMAT = 1;

//==============================================================================
// Clue Fact Functions

bool
ClueFact::Check
(
	void
) const
{
	CLUE_CHECK_EXPR(NULL != m_File.value);
	CLUE_CHECK_EXPR(NULL != m_Method.value);
	CLUE_CHECK_EXPR(NULL != m_Class.value);
	CLUE_CHECK_EXPR(NULL != m_Description.value);
	CLUE_CHECK_EXPR(NULL != m_Detail.value);

	return (true);
}

//------------------------------------------------------------------------------
// Construction and Destructions
ClueFact::ClueFact
(
	FingerPrint const* const			pFP
	,	BString const* const				pFileName
	,	BString const* const				pMethodDefinition
	,	BString const* const				pDescription
	,	BString const* const				pDetails
	,	intptr_t const						nInst
)
	:
	m_CAT(CC_GENERAL)
	,	m_EVT(CE_OK)
	,	m_Time(0)
	,	m_ThreadID(0)
	,	m_TeamID(0)
	,	m_Line(0)
	,	m_Sequence(0)
	,	m_Inst(nInst)
{
	assert(NULL != pFP);
	assert(NULL != pFileName);
	assert(NULL != pMethodDefinition);
	assert(NULL != pDescription);
	assert(NULL != pDetails);

	m_CAT = pFP->Category;
	m_EVT = pFP->Event;
	m_Time = pFP->Time;
	m_ThreadID = pFP->ThreadID;
	m_TeamID = pFP->TeamID;
	m_Line = pFP->Line;
	m_Sequence = pFP->Sequence;

	//Build

	assert(CLUE_CHECK_CLUE_FACT(this));
}

ClueFact::~ClueFact
(
	void
)
{
	assert(CLUE_CHECK_CLUE_FACT(this));

	///
	///- String Destruction Handled by Helper Class
	///
}

//------------------------------------------------------------------------------
void
ClueFact::ClueFactString::Load
(
	BMessage const* const				pMessage
	,	char const* const					csName
)
{
	assert(B_EMPTY_STRING == value);

	char const* csOld(NULL);
	size_t cbLen(0);

	if (B_OK == pMessage->FindString(csName, &csOld)) {
		cbLen = strlen(csOld) + 1;

		char* csNew = new char[cbLen];  // @@ALLOCATION@@  @@EXCEPTION@@

		memcpy(csNew, csOld, cbLen);

		value = csNew;
	}
}

// Serialization
ClueFact::ClueFact
(
	BMessage const* const				pMessage
	,	int32 const							eArchiveFormat
)
	:
	m_CAT(CC_GENERAL)
	,	m_EVT(CE_OK)
	,	m_Time(0)
	,	m_ThreadID(0)
	,	m_TeamID(0)
	,	m_Line(0)
	,	m_Sequence(0)
	,	m_Inst(0)
{
	assert(NULL != pMessage);

	// If these finds fail then it will use the default set above
	// and in the default constructor.

	pMessage->FindInt32("m_CAT", (int32*) &m_CAT);
	pMessage->FindInt32("m_EVT", (int32*) &m_EVT);
	pMessage->FindInt32("m_Line", (int32*) &m_Line);
	pMessage->FindInt32("m_ThreadID", (int32*) &m_ThreadID);
	pMessage->FindInt32("m_Sequence", (int32*) &m_Sequence);
	pMessage->FindInt64("m_Time", (int64*) &m_Time);

	void* tmp_inst(NULL);
	pMessage->FindPointer("m_Inst_AsPointer", &tmp_inst);
	m_Inst = (intptr_t)tmp_inst;

	m_Method.Load(pMessage, "m_Method");
	m_Method.Load(pMessage, "m_Class");
	m_Method.Load(pMessage, "m_File");
	m_Method.Load(pMessage, "m_Detail");
	m_Method.Load(pMessage, "m_Description");

	assert(CLUE_CHECK_CLUE_FACT(*this));
}

status_t
ClueFact::Archive
(
	BMessage* const					pMessage
) const
{
	assert(NULL != pMessage);

	assert(CLUE_CHECK_CLUE_FACT(this));

	status_t 							result;

#define MESSAGE_STORE(how, name, value) \
	result = pMessage->how(name, (value)); \
	assert(B_OK == result || B_NO_MEMORY == result); \
	if (result != B_OK) return (result);

	MESSAGE_STORE(AddInt32, "m_CAT", m_CAT);
	MESSAGE_STORE(AddInt32, "m_EVT", m_EVT);
	MESSAGE_STORE(AddString, "m_Method", m_Method.value);
	MESSAGE_STORE(AddString, "m_Class", m_Class.value);
	MESSAGE_STORE(AddString, "m_File", m_File.value);
	MESSAGE_STORE(AddInt32, "m_Line", m_Line);
	MESSAGE_STORE(AddInt32, "m_ThreadID", m_ThreadID);
	MESSAGE_STORE(AddInt32, "m_Sequence", m_Sequence);
	MESSAGE_STORE(AddPointer, "m_Inst_AsPointer", (const void*)m_Inst);
	MESSAGE_STORE(AddInt64, "m_Time", m_Time);
	MESSAGE_STORE(AddString, "m_Detail", m_Detail.value);
	MESSAGE_STORE(AddString, "m_Description", m_Description.value);

#undef MESSAGE_STORE

	return (B_OK);
}

