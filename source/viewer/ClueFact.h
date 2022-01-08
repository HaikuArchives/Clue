//
// Clue - Clue Fact - Tracks the data on an event.
// Copyright 1999-2006 Jeff Braun and Mathew Hounsell.
// All rights reserved. Distributed under the terms of the MIT License.
//

#if !defined(CLUE_FACT_H_)
#define CLUE_FACT_H_
//==============================================================================

#if !defined(CLUE_H)
#define CLUE
#define BUILD_CLUE_APPLICATION
#include "Clue.h"
#endif

#if !defined(CLUE_CHECK_H_)
#include "ClueCheck.h"
#endif

#include <inttypes.h>

//------------------------------------------------------------------------------
class BMessage;
class BString;

//==============================================================================
// Clue Fact Code

#if defined(CHECK_CLUE)
#define CHECK_CLUE_FACT
#endif

#if defined(CHECK_CLUE_FACT)
#define CLUE_CHECK_CLUE_FACT(p_clue_fact) ((p_clue_event)->Check())
#else
#define CLUE_CHECK_CLUE_FACT(p_clue_fact) true
#endif

//-------------------------------------------------------------------------------
/// A Clue Fact tracks all the data for a single event sent to the server.
class ClueFact {
	// Construction & Destruction
public:
	bool
	Check
	(
		void
	) const;

	// Construction & Destruction
public:
	ClueFact
	(
		FingerPrint const* const
		,	BString const* const
		,	BString const* const
		,	BString const* const
		,	BString const* const
		,	intptr_t const
	);

	~ClueFact
	(
		void
	);

	// Copy and Assignment DISABLED
private:
	ClueFact
	(
		ClueFact const&
	); // Do NOT Implement

	ClueFact&
	operator=
	(
		ClueFact const&
	); // Do NOT Implement

	// Serialization
public:
	static int32 const				ARCHIVE_FORMAT;

	ClueFact
	(
		BMessage const* const
		,	int32 const
	);

	status_t
	Archive
	(
		BMessage* const
	) const;

	// Helpers
private:
	struct ClueFactString {
		char const* 				value;

		ClueFactString(void)
			:
			value((char*)B_EMPTY_STRING)
		{ }

		void Load(BMessage const* const, char const* const);

		~ClueFactString(void)
		{
			if (B_EMPTY_STRING != value)
				delete [] value;
			value = NULL;
		}

	private: ClueFactString(ClueFactString const&);  // Do NOT Implement
	private: ClueFactString& operator=(ClueFactString const&);   // Do NOT Implement
	};

	// Data
private:
	ClueCategory					m_CAT;
	ClueEvent						m_EVT;
	bigtime_t						m_Time;
	thread_id						m_ThreadID;
	team_id							m_TeamID;
	uint32							m_Line;
	uint32							m_Sequence;
	intptr_t						m_Inst;
	ClueFactString					m_File;
	ClueFactString					m_Method;
	ClueFactString					m_Class;
	ClueFactString					m_Description;
	ClueFactString					m_Detail;
};

//-------------------------------------------------------------------------------
template <>
bool
ClueCheck
<ClueFact>
(
	ClueFact const& 					rFact
)
{
	return (rFact.Check());
}

//==============================================================================
//#endif !defined(CLUE_FACT_H_)
#endif
