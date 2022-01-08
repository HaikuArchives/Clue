/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

/***************************************************************
include header files
***************************************************************/
//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif
#ifndef _ENTRY_H
#include <Entry.h>
#endif
#ifndef _NODE_H
#include <Node.h>
#endif
#ifndef _NODE_INFO_H
#include <NodeInfo.h>
#endif
#ifndef _TRANSLATION_UTILS_H
#include <TranslationUtils.h>
#endif

#ifndef REFFILTER_H_JLB
#include "RefFilter.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif


/***************************************************************
***************************************************************/
bool
RefFilter :: Filter
(
	const entry_ref* ref
	,	BNode* node
	,	struct stat* st
	,	const char* filetype
)
{
	if (S_ISDIR(st->st_mode))
		return true;
	else if (S_ISREG(st->st_mode)) {
		if (strcmp(filetype, STR_FILE_SIG) == 0)
			return true;
	} else if (S_ISLNK(st->st_mode)) {
		BEntry entry(ref, true);
		if (B_OK == entry.InitCheck()) {
			BNode node(&entry);
			if (B_OK == node.InitCheck()) {
				if (node.IsDirectory())
					return true;
				else {
					BNodeInfo info(&node);
					if (B_OK == info.InitCheck()) {
						char filetype[B_MIME_TYPE_LENGTH];
						info.GetType(filetype);
						if (strcmp(filetype, STR_FILE_SIG) == 0)
							return true;
					}
				}
			}
		}
	}

	return false;
}
