#include "ClueBuild.h"
#include <Be.h>
#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

#ifndef _CAM_CONSTANTS_H
#include "CAM_Constants.h"
#endif

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectOther.h"
#include "InspectApplicationKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "utility.h"

extern const char * pTrue;
extern const char * pFalse;
extern const char * g_pIndentation;
extern const char * g_pFailedWithError;
extern const char * g_pNewline;

//the one and only instance of a ClueAreaManager, already defined in Clue.cpp
extern ClueAreaManager CAM;

/***************************************************************
***************************************************************/
void


Inspect_BApplication


	(


	BString & strDetails


,	BApplication * inValue


,	int32 inIndent


,	char * inDescription


	)


{


	BString tabindent;


	for (int32 i (0); i++ < inIndent;)


	{


		tabindent << "  |  ";


	}





	if (NULL != inValue)


	{


		Inspect_BLooper (strDetails, (BLooper *) inValue, inIndent, "\nBLooper properties\n-----------------\n");


		strDetails << tabindent << inDescription << "\n";


		app_info aAI;


		inValue->GetAppInfo (&aAI);


#ifndef CLUE_ON_ZETA_HACK
		Inspect_app_info (strDetails, &aAI, inIndent, "GetAppInfo: [app_info object]\n");
#endif

		strDetails << tabindent << "IsLaunching= " << (inValue->IsLaunching () ? pTrue : pFalse);


		strDetails << tabindent << "IsCursorHidden= " << (inValue->IsCursorHidden () ? pTrue : pFalse);


		strDetails << tabindent << "CountWindows= " << inValue->CountWindows () << "\n";


	}


	else


	{


		strDetails << "The BApplication was NULL\n";


	}


}


