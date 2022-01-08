/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef REFFILTER_H_JLB
#define REFFILTER_H_JLB

/***************************************************************
include header files
***************************************************************/
#ifndef _FILE_PANEL_H
#include <FilePanel.h>
#endif

class RefFilter : public BRefFilter {
	bool Filter(const entry_ref*, BNode*, struct stat*, const char*);
};

#endif
