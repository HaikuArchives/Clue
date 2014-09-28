/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

//#define DEBUG 1
/***************************************************************
include header files
***************************************************************/
#ifndef THEAPP_H
#include "TheApp.h"
#endif

#ifdef DEBUG
extern"C" void SetNewLeakChecking(bool);
extern"C" void SetMallocLeakChecking(bool);
#endif

/***************************************************************
***************************************************************/
int main
	(
	void
	)
{
#ifdef DEBUG
	SetNewLeakChecking (true);
	SetMallocLeakChecking (true);
#endif
	TheApp * pApplication (new TheApp);
	pApplication->Run ();
	delete pApplication;
	return (0);
}

