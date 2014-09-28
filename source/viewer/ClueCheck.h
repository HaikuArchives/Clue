//
// Clue - Clue Check - Integrity Checking
// Copyright 1999-2006 Jeff Braun and Mathew Hounsell.
// All rights reserved. Distributed under the terms of the MIT License.
//

#if !defined(CLUE_CHECK_H_)
#define CLUE_CHECK_H_
//==============================================================================

#if !defined(_DEBUG_H)
#include <be/support/Debug.h>
#endif

//==============================================================================
// Clue Check Code

inline
bool
ClueCheckExpr
(
	bool								result
,	char const * const					expression
)
{
	if (! result)
		PRINT(("CLUE CHECK FAIL> %s", expression));

	return (result);
}

#if defined(CHECK_CLUE)
#define CLUE_CHECK_EXPR(expr) if (! ClueCheckExpr((expr), #expr) return (false)
#else
#define CLUE_CHECK_EXPR(expr) if (1) ; else if (expr) ;
#endif

template <typename T>
bool
ClueCheck
(
	T const &
)
{
	return (true);
}

//==============================================================================
//#endif ! defined (CLUE_CHECK_H_)
#endif
