/*	
	2000 Jeff Braun
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

#ifndef _BE_LIST_H
#include <List.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _STRING_H_
#include <string.h>
#endif

#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION = 1
#include "Clue.h"
#endif

#ifndef _CLUE_CONSTANTS_H
#include "constants.h"
#endif

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

//the one and only instance of a ClueAreaManager, already defined in LiveView
extern ClueAreaManager CAM;


/***************************************************************
globals
***************************************************************/
extern BList *				g_ReporterList;  //already defined in CBackView
//extern volatile bool		g_UsingMainList;  //already defined in CBackView
extern volatile sem_id		g_semaphore;  //already defined in CBackView
extern const char *			g_PortName;  //already defined in CBackView
//extern uint32				g_FilterMask;

/***************************************************************
***************************************************************/
int32
Reporter
	(
	void * data
	) 
{
	PRINT (("Reporter started\n"));
	bool keepgoing (true);
	port_id PortID (create_port (100, g_PortName));

	if (0 >= PortID)
	{
		PRINT (("  PortID was bad!\n"));
		return (PortID);
	}
	
	CAM.m_data->m_port = PortID;

//	FingerPrint *	pFP (NULL);
	ssize_t			size (0);
	int32			code (0);
	char *			pflatmsg (NULL);
	ssize_t			rc (0);

	while (keepgoing)
	{
		size = port_buffer_size (PortID);

		if (size) // possible quit message ? size would be 0 (zero)
		{
			//char * pflatmsg (new char[size]);
			pflatmsg = new char[size];
			if (pflatmsg == NULL)
			{
				debugger ("ERROR: pflatmsg in Reporter was invalid!!!");
			}
			PRINT (("Reporter: pflatmsg=%8x)\n", pflatmsg));

			rc = read_port (PortID, &code, static_cast<void *>(pflatmsg), size);

			if (rc != size)
			{
				PRINT (("ERROR: Reporter copied bytes (%i) didn't match size (%i)!\n", rc, size));
				debugger ("ERROR: Reporter copied bytes didn't match size!\n");
			}

			if (B_NO_ERROR != acquire_sem (g_semaphore))
			{
				delete [] pflatmsg;
				debugger ("ERROR: Reporter couldn't acquire the semaphore!");
				continue;
			}

			PRINT (("Reporter: g_ReporterList->AddItem (%8x)\n", pflatmsg));

			if (!g_ReporterList->AddItem (pflatmsg))
			{
				debugger ("ERROR: Reporter failed to AddItem to list!");
			}

			release_sem (g_semaphore);
		}
		else
		{
			read_port (PortID, &code, (void *) 0, 0);
			if (MSG_QUIT_PORT_THREAD == code)
			{
				CAM.m_data->m_port = B_ERROR;
				close_port (PortID);
				keepgoing = false;
			}
		}
	}

	int32 count (port_count (PortID));

	while (count)
	{
		size = port_buffer_size (PortID);

		char * pchar (new char[size]);
		read_port (PortID, &code, (void *) pchar, size);
		delete [] pchar;
		pchar = NULL;
		count = port_count (PortID);
	}

	delete_port (PortID);  //now delete the port

	PRINT (("exiting Reporter\n"));
	return (0);  //exit the thread
}
