//#define DEBUG 1
#include <Be.h>
#include <E-mail.h>
#include <MediaEncoder.h>

#ifndef B_ZETA_VERSION
#include <MultiChannelControl.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#define BUILD_CLUE_APPLICATION
#define CLUE
#include "Clue.h"

#ifndef _CLUE_AREA_MANAGER_H
#include "ClueAreaManager.h"
#endif

#ifndef _CAM_CONSTANTS_H
#include "CAM_Constants.h"
#endif
 
ClueAreaManager CAM; //create instance of a ClueAreaManager
static int32 Sequence (1); //Each program gets it's own Sequence
static const char * const PORT_NAME ("CluePort3");
#define MSG_OBJECT 'objt'


//#include "Inspect_Enums.h"
#include "InspectApplicationKitObjects.h"
#include "InspectDeviceKitObjects.h"
#include "InspectGameKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectMediaKitObjects.h"
#include "InspectMidiKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "InspectSupportKitObjects.h"
#include "InspectTranslationKitObjects.h"
#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectOther.h"
#include "utility.h"


/***************************************************************
***************************************************************/
void
GatherDataAndSend
	(
	FingerPrint *	pFP
,	const char *	pFileName
,	const char *	pMethodDefinition
,	const char *	pDescription
,	BString &		inDetail
,	const void *	inInst = NULL
	)
{
	BMessage msg;
	//I've used extremely short name string when Adding string to hopefully speed up the search for them later
	msg.AddData ("P", B_RAW_TYPE, pFP, sizeof (FingerPrint)); //the FINGERPRINT struct used 'P'
	msg.AddString ("F", (const char *) pFileName); //the File name uses 'F'
	msg.AddString ("M", (const char *) pMethodDefinition); //the ClassMethodDefinition uses 'M'
	if (pDescription)
	{
		msg.AddString ("D", (const char *) pDescription); //The Description used 'D'
	}
	else
	{
		msg.AddString ("D", (const char *) B_EMPTY_STRING); //The Description used 'D'
	}

	msg.AddString ("X", inDetail); //The Details used 'X'

	if (NULL != inInst)
		msg.AddPointer ("I", inInst);

	ssize_t msgsize (msg.FlattenedSize ());
	char * pflatmsg (new char[msgsize]);
	status_t rc (msg.Flatten (pflatmsg, msgsize));

	if (B_OK != rc)
	{
		debugger ("msg.Flatten failed!\n");
	}

	write_port_etc (CAM.m_data->m_port, MSG_OBJECT, pflatmsg, msgsize, B_TIMEOUT, 1);
	delete [] pflatmsg;
}



/***************************************************************
***************************************************************/
void
TraceSimple
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	const char *	inDescription
,	...
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT))
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BMessage msg;
		//I've used extremely short name string when Adding string to hopefully speed up the search for them later
		msg.AddData ("P", B_RAW_TYPE, &FP, sizeof (FingerPrint)); //the FINGERPRINT struct used 'P'
		msg.AddString ("F", (const char *) inFileName); //the File name uses 'F'
		msg.AddString ("M", (const char *) inMethodDefinition); //the ClassMethodDefinition uses 'A'

		char Detail[1024];
		Detail[0] = '\0'; //make it an empty string

		if (inDescription)
		{
			va_list marker;
			va_start (marker, inDescription);
			//va_end (marker)
			vsprintf (Detail, inDescription, marker);
		}

		Detail[1023] = '\0'; //make sure it is terminated!
		msg.AddString ("D", (const char *) Detail); //The Description used 'D'
		msg.AddString ("X", (const char *) B_EMPTY_STRING); //The Details used 'X'

		ssize_t msgsize (msg.FlattenedSize ());
		char * pflatmsg (new char[msgsize]);
		status_t rc (msg.Flatten (pflatmsg, msgsize));
		if (rc != B_OK)
		{
			debugger ("msg.Flatten failed!\n");
		}

		write_port_etc (CAM.m_data->m_port, MSG_OBJECT, pflatmsg, msgsize, B_TIMEOUT, 1);
		delete [] pflatmsg;
	}
}


/***************************************************************
***************************************************************/
void
TraceClass
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	const void *    inInst
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT))
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		char * pChar (strchr (inMethodDefinition, ':'));
		int32 length (pChar - inMethodDefinition + 1);
		pChar = (char *) new char[length];
		memcpy (pChar, inMethodDefinition, length);
		pChar[length - 1] = '\0';
		char MethodDefinition[100];
		sprintf (MethodDefinition, "%s:: (", pChar);
		delete [] pChar;

		BString strDetails;

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, B_EMPTY_STRING, strDetails, inInst);
	}
}


/***************************************************************
***************************************************************/
TraceMethod :: TraceMethod
	(
	ClueCategory	inCAT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	const char *	inDescription
,	...
	)
:	m_StartTime (real_time_clock_usecs ())
,	m_CAT (inCAT)
,	m_Line (inLineNumber)
,	m_CMDefinition (inMethodDefinition)
,	m_File (inFileName)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[m_CAT] & CE_ENTER))
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		struct FingerPrint FP = {m_CAT, CE_ENTER, TI.thread, TI.team, m_StartTime, m_Line, atomic_add (&Sequence, 1)};

		BMessage msg;
		//I've used extremely short name string when Adding string to hopefully speed up the search for them later
		msg.AddData ("P", B_RAW_TYPE, &FP, sizeof (FingerPrint)); //the FINGERPRINT struct used 'P'
		msg.AddString ("F", (const char *) inFileName); //the File name uses 'F'
		msg.AddString ("M", (const char *) inMethodDefinition); //the ClassMethodDefinition uses 'A'
		msg.AddString ("X", (const char *) B_EMPTY_STRING); //The Details used 'X'

		char Detail[1024];
		Detail[0] = '\0'; //make it an empty string

		if (inDescription)
		{
			va_list marker;
			va_start (marker, inDescription);
			//va_end (marker)
			vsprintf (Detail, inDescription, marker);
		}

		msg.AddString ("D", (const char *) Detail); //The Description used 'D'
		msg.PrintToStream ();

		ssize_t msgsize (msg.FlattenedSize ());
		char * pflatmsg (new char[msgsize]);
		status_t rc (msg.Flatten (pflatmsg, msgsize));

		if (rc != B_OK)
		{
			debugger ("msg.Flatten failed!\n");
		}

		write_port_etc (CAM.m_data->m_port, MSG_OBJECT, pflatmsg, msgsize, B_TIMEOUT, 1);
		delete [] pflatmsg;
	}
}


/***************************************************************
***************************************************************/
TraceMethod :: ~TraceMethod
	(
	void
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[m_CAT] & CE_EXIT))
	{
		bigtime_t StopTime (real_time_clock_usecs ());
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		struct FingerPrint FP = {m_CAT, CE_EXIT, TI.thread, TI.team, StopTime, m_Line, atomic_add (&Sequence, 1)};

		BString strDetails;
		bigtime_t diff (StopTime - m_StartTime);
		bigtime_t work (diff / 1000000);

		int32 hours (0), minutes (0), seconds (0), micro (0);
		hours = work / 3600;
		minutes = (work / 60) % 60;
		seconds = work % 60;
		micro = diff - (work * 1000000);
		char tmpstr[30];

		if (0 == hours)
		{
			if (0 == minutes)
			{
				if (0 == seconds)
				{
					sprintf (tmpstr, ".%06li", micro);
				}
				else
				{
					sprintf (tmpstr, "%li.%06li", seconds, micro);
				}
			}
			else
			{
				sprintf (tmpstr, "%li:%02li.%06li", minutes, seconds, micro);
			}
		}
		else
		{
			sprintf (tmpstr, "%li:%02li:%02li.%06li", hours, minutes, seconds, micro);
		}

		GatherDataAndSend (&FP, m_File, m_CMDefinition, tmpstr, strDetails);
	}
}


/*
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
*/


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaEncoder *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAENCODER] & MASK_BMEDIAENCODER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaEncoder:\n");
		Inspect_BMediaEncoder (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMultiChannelControl *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMULTICHANNELCONTROL] & MASK_BMULTICHANNELCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMultiChannelControl:\n");
		Inspect_BMultiChannelControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BAlert *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BALERT] & MASK_BALERT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BAlert:\n");
		Inspect_BAlert (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BAppFileInfo *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BAPPFILEINFO] & MASK_BAPPFILEINFO)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BAppFileInfo:\n");
		Inspect_BAppFileInfo (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BApplication *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BAPPLICATION] & MASK_BAPPLICATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BApplication:\n");
		Inspect_BApplication (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BAutolock * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BAUTOLOCK] & MASK_BAUTOLOCK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BAutolock:\n");
		Inspect_BAutolock (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BList * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BLIST] & MASK_BLIST)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BList:\n");
		Inspect_BList (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
#if !defined(CLUE_ON_ZETA_HACK) || defined(CLUE_FOR_ZETA_GL)
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BGLView *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BGLVIEW] & MASK_BGLVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BGLView:\n");
		Inspect_BGLView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBitmap *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBITMAP] & MASK_BBITMAP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBitmap:\n");
		Inspect_BBitmap (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBitmapStream *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBITMAPSTREAM] & MASK_BBITMAPSTREAM)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBitmapStream:\n");
		Inspect_BBitmapStream (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BString * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTRING] & MASK_BSTRING)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BString:\n");
		Inspect_BString (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBufferIO * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUFFERIO] & MASK_BBUFFERIO)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBufferIO:\n");
		Inspect_BBufferIO (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BGameSound *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BGAMESOUND] & MASK_BGAMESOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BGameSound:\n");
		Inspect_BGameSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBox *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBOX] & MASK_BBOX)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBox:\n");
		Inspect_BBox (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBuffer *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUFFER] & MASK_BBUFFER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBuffer:\n");
		Inspect_BBuffer (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSmallBuffer *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSMALLBUFFER] & MASK_BSMALLBUFFER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSmallBuffer:\n");
		Inspect_BSmallBuffer (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBufferConsumer *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUFFERCONSUMER] & MASK_BBUFFERCONSUMER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBufferConsumer:\n");
		Inspect_BBufferConsumer (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBufferGroup *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUFFERGROUP] & MASK_BBUFFERGROUP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBufferGroup:\n");
		Inspect_BBufferGroup (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BBufferProducer *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUFFERPRODUCER] & MASK_BBUFFERPRODUCER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BBufferProducer:\n");
		Inspect_BBufferProducer (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BButton *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BBUTTON] & MASK_BBUTTON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BButton:\n");
		Inspect_BButton (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BChannelControl *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCHANNELCONTROL] & MASK_BCHANNELCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BChannelControl:\n");
		Inspect_BChannelControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BChannelSlider *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCHANNELSLIDER] & MASK_BCHANNELSLIDER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BChannelSlider:\n");
		Inspect_BChannelSlider (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BCheckBox *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCHECKBOX] & MASK_BCHECKBOX)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BCheckBox:\n");
		Inspect_BCheckBox (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BClipboard *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCLIPBOARD] & MASK_BCLIPBOARD)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BClipboard:\n");
		Inspect_BClipboard (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BColorControl *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCOLORCONTROL] & MASK_BCOLORCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BColorControl:\n");
		Inspect_BColorControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BControl *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCONTROL] & MASK_BCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BControl:\n");
		Inspect_BControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BParameterWeb *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPARAMETERWEB] & MASK_BPARAMETERWEB)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BParameterWeb:\n");
		Inspect_BParameterWeb (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BParameterGroup *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPARAMETERGROUP] & MASK_BPARAMETERGROUP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BParameterGroup:\n");
		Inspect_BParameterGroup (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BParameter *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPARAMETER] & MASK_BPARAMETER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BParameter:\n");
		Inspect_BParameter (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BContinuousParameter *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCONTINUOUSPARAMETER] & MASK_BCONTINUOUSPARAMETER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BContinuousParameter:\n");
		Inspect_BContinuousParameter (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BDiscreteParameter *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BDISCRETEPARAMETER] & MASK_BDISCRETEPARAMETER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BDiscreteParameter:\n");
		Inspect_BDiscreteParameter (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BNullParameter *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BNULLPARAMETER] & MASK_BNULLPARAMETER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BNullParameter:\n");
		Inspect_BNullParameter (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BControllable *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BCONTROLLABLE] & MASK_BCONTROLLABLE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BControllable:\n");
		Inspect_BControllable (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaTheme *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIATHEME] & MASK_BMEDIATHEME)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaTheme:\n");
		Inspect_BMediaTheme (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BDirectory *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BDIRECTORY] & MASK_BDIRECTORY)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BDirectory:\n");
		Inspect_BDirectory (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BDirectWindow *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BDIRECTWINDOW] & MASK_BDIRECTWINDOW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BDirectWindow:\n");
		Inspect_BDirectWindow (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BDragger *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BDRAGGER] & MASK_BDRAGGER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BDragger:\n");
		Inspect_BDragger (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BEntry *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BENTRY] & MASK_BENTRY)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BEntry:\n");
		Inspect_BEntry (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BEntryList *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BENTRYLIST] & MASK_BENTRYLIST)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BEntryList:\n");
		Inspect_BEntryList (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFlattenable *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFLATTENABLE] & MASK_BFLATTENABLE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFlattenable:\n");
		Inspect_BFlattenable (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFile *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFILE] & MASK_BFILE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFile:\n");
		Inspect_BFile (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFileGameSound *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFILEGAMESOUND] & MASK_BFILEGAMESOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFileGameSound:\n");
		Inspect_BFileGameSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFilePanel *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFILEPANEL] & MASK_BFILEPANEL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFilePanel:\n");
		Inspect_BFilePanel (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFileInterface *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFILEINTERFACE] & MASK_BFILEINTERFACE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFileInterface:\n");
		Inspect_BFileInterface (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	unicode_block *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_UNICODE_BLOCK] & MASK_UNICODE_BLOCK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a unicode_block:\n");
		Inspect_unicode_block (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BFont *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BFONT] & MASK_BFONT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BFont:\n");
		Inspect_BFont (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BHandler *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BHANDLER] & MASK_BHANDLER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BHandler:\n");
		Inspect_BHandler (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BInvoker *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BINVOKER] & MASK_BINVOKER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BInvoker:\n");
		Inspect_BInvoker (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BInputDevice *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BINPUTDEVICE] & MASK_BINPUTDEVICE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BInputDevice:\n");
		Inspect_BInputDevice (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BJoystick *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BJOYSTICK] & MASK_BJOYSTICK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BJoystick:\n");
		Inspect_BJoystick (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BListItem *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BLISTITEM] & MASK_BLISTITEM)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BListItem:\n");
		Inspect_BListItem (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStringItem *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTRINGITEM] & MASK_BSTRINGITEM)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStringItem:\n");
		Inspect_BStringItem (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BListView *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BLISTVIEW] & MASK_BLISTVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BListView:\n");
		Inspect_BListView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BLocker * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BLOCKER] & MASK_BLOCKER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BLocker:\n");
		Inspect_BLocker (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BLooper *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BLOOPER] & MASK_BLOOPER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BLooper:\n");
		Inspect_BLooper (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaAddOn *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAADDON] & MASK_BMEDIAADDON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaAddOn:\n");
		Inspect_BMediaAddOn (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaDecoder *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIADECODER] & MASK_BMEDIADECODER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaDecoder:\n");
		Inspect_BMediaDecoder (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaEventLooper *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAEVENTLOOPER] & MASK_BMEDIAEVENTLOOPER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaEventLooper:\n");
		Inspect_BMediaEventLooper (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaFile *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAFILE] & MASK_BMEDIAFILE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaFile:\n");
		Inspect_BMediaFile (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaFiles *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAFILES] & MASK_BMEDIAFILES)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaFiles:\n");
		Inspect_BMediaFiles (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_node *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_MEDIA_NODE] & MASK_MEDIA_NODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_node:\n");
		Inspect_media_node (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaNode *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIANODE] & MASK_BMEDIANODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaNode:\n");
		Inspect_BMediaNode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaRoster *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAROSTER] & MASK_BMEDIAROSTER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaRoster:\n");
		Inspect_BMediaRoster (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaTrack *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIATRACK] & MASK_BMEDIATRACK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaTrack:\n");
		Inspect_BMediaTrack (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMediaFormats *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMEDIAFORMATS] & MASK_BMEDIAFORMATS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMediaFormats:\n");
		Inspect_BMediaFormats (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMenu *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMENU] & MASK_BMENU)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMenu:\n");
		Inspect_BMenu (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMenuBar *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMENUBAR] & MASK_BMENUBAR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMenuBar:\n");
		Inspect_BMenuBar (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMenuField *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMENUFIELD] & MASK_BMENUFIELD)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMenuField:\n");
		Inspect_BMenuField (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMenuItem *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMENUITEM] & MASK_BMENUITEM)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMenuItem:\n");
		Inspect_BMenuItem (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSeparatorItem *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSEPARATORITEM] & MASK_BSEPARATORITEM)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSeparatorItem:\n");
		Inspect_BSeparatorItem (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMessage *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMESSAGE] & MASK_BMESSAGE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMessage:\n\n");
		Inspect_BMessage (strDetails, inValue, 0, B_EMPTY_STRING, 1, 1);

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMessageFilter *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMESSAGEFILTER] & MASK_BMESSAGEFILTER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMessageFilter:\n");
		Inspect_BMessageFilter (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMessageQueue *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMESSAGEQUEUE] & MASK_BMESSAGEQUEUE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMessageQueue:\n");
		Inspect_BMessageQueue (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMessageRunner *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMESSAGERUNNER] & MASK_BMESSAGERUNNER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMessageRunner:\n");
		Inspect_BMessageRunner (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMessenger *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMESSENGER] & MASK_BMESSENGER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMessenger:\n");
		Inspect_BMessenger (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidi *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDI] & MASK_BMIDI)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidi:\n");
		Inspect_BMidi (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidiPort *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDIPORT] & MASK_BMIDIPORT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidiPort:\n");
		Inspect_BMidiPort (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidiStore *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDISTORE] & MASK_BMIDISTORE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidiStore:\n");
		Inspect_BMidiStore (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidiSynth *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDISYNTH] & MASK_BMIDISYNTH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidiSynth:\n");
		Inspect_BMidiSynth (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidiSynthFile *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDISYNTHFILE] & MASK_BMIDISYNTHFILE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidiSynthFile:\n");
		Inspect_BMidiSynthFile (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMidiText *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIDITEXT] & MASK_BMIDITEXT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMidiText:\n");
		Inspect_BMidiText (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BMimeType *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BMIMETYPE] & MASK_BMIMETYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BMimeType:\n");
		Inspect_BMimeType (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BNode *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BNODE] & MASK_BNODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BNode:\n");
		Inspect_BNode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BOptionControl *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BOPTIONCONTROL] & MASK_BOPTIONCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BOptionControl:\n");
		Inspect_BOptionControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BOptionPopUp *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BOPTIONPOPUP] & MASK_BOPTIONPOPUP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BOptionPopUp:\n");
		Inspect_BOptionPopUp (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BOutlineListView *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BOUTLINELISTVIEW] & MASK_BOUTLINELISTVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BOutlineListView:\n");
		Inspect_BOutlineListView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPath *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPATH] & MASK_BPATH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPath:\n");
		Inspect_BPath (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPicture *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPICTURE] & MASK_BPICTURE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPicture:\n");
		Inspect_BPicture (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPictureButton *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPICTUREBUTTON] & MASK_BPICTUREBUTTON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPictureButton:\n");
		Inspect_BPictureButton (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPoint *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPOINT] & MASK_BPOINT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPoint:\n");
		Inspect_BPoint (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPolygon *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPOLYGON] & MASK_BPOLYGON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPolygon:\n");
		Inspect_BPolygon (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPopUpMenu *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPOPUPMENU] & MASK_BPOPUPMENU)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPopUpMenu:\n");
		Inspect_BPopUpMenu (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPrintJob *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPRINTJOB] & MASK_BPRINTJOB)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPrintJob:\n");
		Inspect_BPrintJob (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPropertyInfo *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPROPERTYINFO] & MASK_BPROPERTYINFO)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPropertyInfo:\n");
		Inspect_BPropertyInfo (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BPushGameSound * inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BPUSHGAMESOUND] & MASK_BPUSHGAMESOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BPushGameSound:\n");
		Inspect_BPushGameSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BQuery * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BQUERY] & MASK_BQUERY)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BQuery:\n");
		Inspect_BQuery (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BRadioButton *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BRADIOBUTTON] & MASK_BRADIOBUTTON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BRadioButton:\n");
		Inspect_BControl (strDetails, (BControl *) inValue, 0, "\n");
		//don't have a function for BRadioButton as it really doesn't have any unique values BControl doesn't

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BRect *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BRECT] & MASK_BRECT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BRect:\n");
		Inspect_BRect (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BRegion *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BREGION] & MASK_BREGION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BRegion:\n");
		Inspect_BRegion (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BResourceStrings * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BRESOURCESTRINGS] & MASK_BRESOURCESTRINGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BResourceStrings:\n");
		Inspect_BResourceStrings (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BResources * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BRESOURCES] & MASK_BRESOURCES)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BResources:\n");
		Inspect_BResources (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BRoster *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BROSTER] & MASK_BROSTER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BRoster:\n");
		Inspect_BRoster (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSamples * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSAMPLES] & MASK_BSAMPLES)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSamples:\n");
		Inspect_BSamples (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BScreen *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSCREEN] & MASK_BSCREEN)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BScreen:\n");
		Inspect_BScreen (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BScrollBar *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSCROLLBAR] & MASK_BSCROLLBAR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BScrollBar:\n");
		Inspect_BScrollBar (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BScrollView *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSCROLLVIEW] & MASK_BSCROLLVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BScrollView:\n");
		Inspect_BScrollView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSerialPort * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSERIALPORT] & MASK_BSERIALPORT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSerialPort:\n");
		Inspect_BSerialPort (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BShape * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSHAPE] & MASK_BSHAPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BShape:\n");
		Inspect_BShape (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BShelf *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSHELF] & MASK_BSHELF)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BShelf:\n");
		Inspect_BShelf (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSimpleGameSound * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSIMPLEGAMESOUND] & MASK_BSIMPLEGAMESOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSimpleGameSound:\n");
		Inspect_BSimpleGameSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSlider *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSLIDER] & MASK_BSLIDER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSlider:\n");
		Inspect_BSlider (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSound * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSOUND] & MASK_BSOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSound:\n");
		Inspect_BSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSoundFile * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSOUNDFILE] & MASK_BSOUNDFILE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSoundFile:\n");
		Inspect_BSoundFile (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSoundPlayer * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSOUNDPLAYER] & MASK_BSOUNDPLAYER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSoundPlayer:\n");
		Inspect_BSoundPlayer (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStatable *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTATABLE] & MASK_BSTATABLE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStatable:\n");
		Inspect_BStatable (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStatusBar *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTATUSBAR] & MASK_BSTATUSBAR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStatusBar:\n");
		Inspect_BStatusBar (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStopWatch * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTOPWATCH] & MASK_BSTOPWATCH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStopWatch:\n");
		Inspect_BStopWatch (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStreamingGameSound * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTREAMINGGAMESOUND] & MASK_BSTREAMINGGAMESOUND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStreamingGameSound:\n");
		Inspect_BStreamingGameSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BStringView *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSTRINGVIEW] & MASK_BSTRINGVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BStringView:\n");
		Inspect_BStringView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSymLink * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSYMLINK] & MASK_BSYMLINK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSymLink:\n");
		Inspect_BSymLink (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTab *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTAB] & MASK_BTAB)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTab:\n");
		Inspect_BTab (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTabView *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTABVIEW] & MASK_BTABVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTabView:\n");
		Inspect_BTabView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTextControl *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTEXTCONTROL] & MASK_BTEXTCONTROL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTextControl:\n");
		Inspect_BTextControl (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTimeCode * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTIMECODE] & MASK_BTIMECODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTimeCode:\n");
		Inspect_BTimeCode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTimedEventQueue * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTIMEDEVENTQUEUE] & MASK_BTIMEDEVENTQUEUE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTimedEventQueue:\n");
		Inspect_BTimedEventQueue (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTimeSource * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTIMESOURCE] & MASK_BTIMESOURCE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTimeSource:\n");
		Inspect_BTimeSource (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTranslator * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTRANSLATOR] & MASK_BTRANSLATOR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTranslator:\n");
		Inspect_BTranslator (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTranslatorRoster * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTRANSLATORROSTER] & MASK_BTRANSLATORROSTER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTranslatorRoster:\n");
		Inspect_BTranslatorRoster (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BView *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BVIEW] & MASK_BVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BView:\n");
		Inspect_BView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BVolume *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BVOLUME] & MASK_BVOLUME)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BVolume:\n");
		Inspect_BVolume (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BVolumeRoster * inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BVOLUMEROSTER] & MASK_BVOLUMEROSTER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BVolumeRoster:\n");
		Inspect_BVolumeRoster (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}



/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BWindow *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BWINDOW] & MASK_BWINDOW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BWindow:\n");
		Inspect_BWindow (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}




/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BNodeInfo *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BNODEINFO] & MASK_BNODEINFO)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BNodeInfo:\n");
		Inspect_BNodeInfo (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BSynth * 		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BSYNTH] & MASK_BSYNTH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BSynth:\n");
		Inspect_BSynth (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	BTextView *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_BTEXTVIEW] & MASK_BTEXTVIEW)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a BTextView:\n");
		Inspect_BTextView (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}



//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	swap_action		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_SWAP_ACTION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a swap_action:\n");
		Inspect_Enum_swap_action (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	info_location	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_INFO_LOCATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a info_location:\n");
		Inspect_Enum_info_location (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	version_kind	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_VERSION_KIND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a version_kind:\n");
		Inspect_Enum_version_kind (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	color_control_layout	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_COLOR_CONTROL_LAYOUT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a color_control_layout:\n");
		Inspect_Enum_color_control_layout (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_parameter_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_MEDIA_PARAMETER_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_parameter_flags:\n");
		Inspect_Enum_media_parameter_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	direct_buffer_state	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_DIRECT_BUFFER_STATE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a direct_buffer_state:\n");
		Inspect_Enum_direct_buffer_state (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	direct_driver_state	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_DIRECT_DRIVER_STATE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a direct_driver_state:\n");
		Inspect_Enum_direct_driver_state (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	mail_flags		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_MAIL_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a mail_flags:\n");
		Inspect_Enum_mail_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	file_panel_mode	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_FILE_PANEL_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a file_panel_mode:\n");
		Inspect_Enum_file_panel_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	file_panel_button	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_FILE_PANEL_BUTTON)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a file_panel_button:\n");
		Inspect_Enum_file_panel_button (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	directory_which	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_DIRECTORY_WHICH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a directory_which:\n");
		Inspect_Enum_directory_which (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	font_direction	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_FONT_DIRECTION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a font_direction:\n");
		Inspect_Enum_font_direction (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	font_metric_mode	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_FONT_METRIC_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a font_metric_mode:\n");
		Inspect_Enum_font_metric_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	font_file_format	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_FONT_FILE_FORMAT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a font_file_format:\n");
		Inspect_Enum_font_file_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	gs_attributes	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_GS_ATTRIBUTES)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a gs_attributes:\n");
		Inspect_Enum_gs_attributes (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	color_space		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_COLOR_SPACE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a color_space:\n");
		Inspect_Enum_color_space (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	drawing_mode	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_DRAWING_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a drawing_mode:\n");
		Inspect_Enum_drawing_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	buffer_orientation	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_BUFFER_ORIENTATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a buffer_orientation:\n");
		Inspect_Enum_buffer_orientation (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	buffer_layout	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_BUFFER_LAYOUT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a buffer_layout:\n");
		Inspect_Enum_buffer_layout (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	source_alpha	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_SOURCE_ALPHA)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a source_alpha:\n");
		Inspect_Enum_source_alpha (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	alpha_function	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_ALPHA_FUNCTION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a alpha_function:\n");
		Inspect_Enum_alpha_function (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	image_type		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_IMAGE_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a image_type:\n");
		Inspect_Enum_image_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	input_method_op	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_INPUT_METHOD_OP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a input_method_op:\n");
		Inspect_Enum_input_method_op (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	input_device_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_INPUT_DEVICE_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a input_device_type:\n");
		Inspect_Enum_input_device_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	input_device_notification	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_INPUT_DEVICE_NOTIFICATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a input_device_notification:\n");
		Inspect_Enum_input_device_notification (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	alignment		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_ALIGNMENT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a alignment:\n");
		Inspect_Enum_alignment (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	join_mode		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_JOIN_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a join_mode:\n");
		Inspect_Enum_join_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	border_style	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_BORDER_STYLE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a border_style:\n");
		Inspect_Enum_border_style (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	button_width	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_BUTTON_WIDTH)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a button_width:\n");
		Inspect_Enum_button_width (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	cap_mode		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_CAP_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a cap_mode:\n");
		Inspect_Enum_cap_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	orientation		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_ORIENTATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a orientation:\n");
		Inspect_Enum_orientation (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	list_view_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP1] & MASK_ENUM_LIST_VIEW_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a list_view_type:\n");
		Inspect_Enum_list_view_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_type		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_type:\n");
		Inspect_Enum_media_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	node_kind		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_NODE_KIND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a node_kind:\n");
		Inspect_Enum_node_kind (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	video_orientation	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_VIDEO_ORIENTATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a video_orientation:\n");
		Inspect_Enum_video_orientation (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_flags		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_flags:\n");
		Inspect_Enum_media_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_producer_status	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_PRODUCER_STATUS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_producer_status:\n");
		Inspect_Enum_media_producer_status (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_realtime_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_REALTIME_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_realtime_flags:\n");
		Inspect_Enum_media_realtime_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_frame_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_FRAME_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_frame_flags:\n");
		Inspect_Enum_media_frame_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
#ifndef CLUE_ON_ZETA_HACK
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_multi_channels	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_MULTI_CHANNELS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_multi_channels:\n");
		Inspect_Enum_media_multi_channels (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
#endif

/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_multi_matrix	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_MULTI_MATRIX)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_multi_matrix:\n");
		Inspect_Enum_media_multi_matrix (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_display_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_DISPLAY_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_display_flags:\n");
		Inspect_Enum_media_display_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_format_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_FORMAT_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_format_flags:\n");
		Inspect_Enum_media_format_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_format_family	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_FORMAT_FAMILY)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_format_family:\n");
		Inspect_Enum_media_format_family (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_seek_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_SEEK_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_seek_type:\n");
		Inspect_Enum_media_seek_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_file_accept_format_flags	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MEDIA_FILE_ACCEPT_FORMAT_FLAGS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_file_accept_format_flags:\n");
		Inspect_Enum_media_file_accept_format_flags (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	mpeg_id			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MPEG_ID)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a mpeg_id:\n");
		Inspect_Enum_mpeg_id (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	menu_layout		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MENU_LAYOUT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a menu_layout:\n");
		Inspect_Enum_menu_layout (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	menu_bar_border	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MENU_BAR_BORDER)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a menu_bar_border:\n");
		Inspect_Enum_menu_bar_border (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	filter_result	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_FILTER_RESULT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a filter_result:\n");
		Inspect_Enum_filter_result (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	message_delivery	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MESSAGE_DELIVERY)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a message_delivery:\n");
		Inspect_Enum_message_delivery (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	message_source	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MESSAGE_SOURCE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a message_source:\n");
		Inspect_Enum_message_source (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	synth_mode		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_SYNTH_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a synth_mode:\n");
		Inspect_Enum_synth_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	midi_axe		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_MIDI_AXE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a midi_axe:\n");
		Inspect_Enum_midi_axe (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	icon_size		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_ICON_SIZE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a icon_size:\n");
		Inspect_Enum_icon_size (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	thread_state	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_THREAD_STATE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a thread_state:\n");
		Inspect_Enum_thread_state (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	cpu_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_CPU_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a cpu_type:\n");
		Inspect_Enum_cpu_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	platform_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_PLATFORM_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a platform_type:\n");
		Inspect_Enum_platform_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	value_kind	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_VALUE_KIND)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a value_kind:\n");
		Inspect_Enum_value_kind (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	query_op		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_QUERY_OP)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a query_op:\n");
		Inspect_Enum_query_op (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	data_rate		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_DATA_RATE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a data_rate:\n");
		Inspect_Enum_data_rate (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	data_bits		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_DATA_BITS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a data_bits:\n");
		Inspect_Enum_data_bits (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	stop_bits		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_STOP_BITS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a stop_bits:\n");
		Inspect_Enum_stop_bits (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	parity_mode		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_PARITY_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a parity_mode:\n");
		Inspect_Enum_parity_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	hash_mark_location	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP2] & MASK_ENUM_HASH_MARK_LOCATION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a hash_mark_location:\n");
		Inspect_Enum_hash_mark_location (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	thumb_style		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_THUMB_STYLE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a thumb_style:\n");
		Inspect_Enum_thumb_style (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	node_flavor		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_NODE_FLAVOR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a node_flavor:\n");
		Inspect_Enum_node_flavor (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	status_t		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_STATUS_T)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a status_t:\n");
		//Inspect_Enum_status_t (strDetails, inValue, 0, "\n");
		GetStatusTDescription (strDetails, inValue, 0, "status_t= ");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	interpolation_mode	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_INTERPOLATION_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a interpolation_mode:\n");
		Inspect_Enum_interpolation_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	reverb_mode		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_REVERB_MODE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a reverb_mode:\n");
		Inspect_Enum_reverb_mode (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	tab_position	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_TAB_POSITION)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a tab_position:\n");
		Inspect_Enum_tab_position (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	undo_state	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_UNDO_STATE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a undo_state:\n");
		Inspect_Enum_undo_state (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	timecode_type	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_TIMECODE_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a timecode_type:\n");
		Inspect_Enum_timecode_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	window_type		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_WINDOW_TYPE)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a window_type:\n");
		Inspect_Enum_window_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	window_look		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_WINDOW_LOOK)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a window_look:\n");
		Inspect_Enum_window_look (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	window_feel		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_WINDOW_FEEL)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a window_feel:\n");
		Inspect_Enum_window_feel (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	window_alignment	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_WINDOW_ALIGNMENT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a window_alignment:\n");
		Inspect_Enum_window_alignment (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	B_TRANSLATION_ERROR		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_B_TRANSLATION_ERROR)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a B_TRANSLATION_ERROR:\n");
		Inspect_Enum_B_TRANSLATION_ERROR (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorGroups	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT) && (CAM.m_data->m_mask[INDEX_ENUM_GROUP3] & MASK_ENUM_TRANSLATORGROUPS)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorGroups:\n");
		Inspect_Enum_TranslatorGroups (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	entry_ref *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a entry_ref:\n");
		Inspect_Struct_entry_ref (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	rgb_color *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a rgb_color:\n");
		Inspect_Struct_rgb_color (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	alert_type		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting an alert_type:\n");
		Inspect_Enum_alert_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	button_spacing	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a button_spacing:\n");
		Inspect_Enum_button_spacing (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	version_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a version_info:\n");
		Inspect_Struct_version_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	buffer_clone_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a buffer_clone_info:\n");
		Inspect_Struct_buffer_clone_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	clipping_rect *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a clipping_rect:\n");
		Inspect_Struct_clipping_rect (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	direct_buffer_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a direct_buffer_info:\n");
		Inspect_Struct_direct_buffer_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	mail_pop_account *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a mail_pop_account:\n");
		Inspect_Struct_mail_pop_account (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	mail_notification *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a mail_notification:\n");
		Inspect_Struct_mail_notification (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
/*
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	entry_ref *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a entry_ref:\n");
//		Inspect_Struct_entry_ref (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
*/


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	edge_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a edge_info:\n");
		Inspect_Struct_edge_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	font_height *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a font_height:\n");
		Inspect_Struct_font_height (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	escapement_delta *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a escapement_delta:\n");
		Inspect_Struct_escapement_delta (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	tuned_font_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a tuned_font_info:\n");
		Inspect_Struct_tuned_font_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	gs_audio_format *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a gs_audio_format:\n");
		Inspect_Struct_gs_audio_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	gs_attribute *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a gs_attribute:\n");
		Inspect_Struct_gs_attribute (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	gs_attribute_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a gs_attribute_info:\n");
		Inspect_Struct_gs_attribute_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	pattern *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a pattern:\n");
		Inspect_Struct_pattern (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
/*
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	rgb_color *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a rgb_color:\n");
//		Inspect_Struct_rgb_color (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
*/


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	color_map *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a color_map:\n");
		Inspect_Struct_color_map (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	overlay_rect_limits *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a overlay_rect_limits:\n");
		Inspect_Struct_overlay_rect_limits (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	overlay_restrictions *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a overlay_restrictions:\n");
		Inspect_Struct_overlay_restrictions (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	screen_id *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a screen_id:\n");
		Inspect_Struct_screen_id (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	image_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a image_info:\n");
		Inspect_Struct_image_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	key_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a key_info:\n");
		Inspect_Struct_key_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	key_map *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a key_map:\n");
		Inspect_Struct_key_map (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	mouse_map *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a mouse_map:\n");
		Inspect_Struct_mouse_map (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	scroll_bar_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a scroll_bar_info:\n");
		Inspect_Struct_scroll_bar_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	dormant_node_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a dormant_node_info:\n");
		Inspect_Struct_dormant_node_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	flavor_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a flavor_info:\n");
		Inspect_Struct_flavor_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	dormant_flavor_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a dormant_flavor_info:\n");
		Inspect_Struct_dormant_flavor_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_destination *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_destination:\n");
		Inspect_Struct_media_destination (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_source *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_source:\n");
		Inspect_Struct_media_source (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_raw_audio_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_raw_audio_format:\n");
		Inspect_Struct_media_raw_audio_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_audio_header *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_audio_header:\n");
		Inspect_Struct_media_audio_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_multi_audio_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_multi_audio_info:\n");
		Inspect_Struct_media_multi_audio_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_encoded_audio_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_encoded_audio_format:\n");
		Inspect_Struct_media_encoded_audio_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_encoded_audio_header *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_encoded_audio_header:\n");
		Inspect_Struct_media_encoded_audio_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_video_display_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_video_display_info:\n");
		Inspect_Struct_media_video_display_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_raw_video_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_raw_video_format:\n");
		Inspect_Struct_media_raw_video_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_video_header *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_video_header:\n");
		Inspect_Struct_media_video_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_encoded_video_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_encoded_video_format:\n");
		Inspect_Struct_media_encoded_video_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_encoded_video_header *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_encoded_video_header:\n");
		Inspect_Struct_media_encoded_video_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_multistream_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_multistream_format:\n");
		Inspect_Struct_media_multistream_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_multistream_header *	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_multistream_header:\n");
		Inspect_Struct_media_multistream_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_format:\n");
		Inspect_Struct_media_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_seek_tag *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_seek_tag:\n");
		Inspect_Struct_media_seek_tag (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_header_time_code *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_header_time_code:\n");
		Inspect_Struct_media_header_time_code (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_header *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_header:\n");
		Inspect_Struct_media_header (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_file_format_id *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_file_format_id:\n");
		Inspect_Struct_media_file_format_id (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_file_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_file_format:\n");
		Inspect_Struct_media_file_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_encode_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_encode_info:\n");
		Inspect_Struct_media_encode_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	encode_parameters *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a encode_parameters:\n");
		Inspect_Struct_encode_parameters (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_decode_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_decode_info:\n");
		Inspect_Struct_media_decode_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_input *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_input:\n");
		Inspect_Struct_media_input (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_output *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_output:\n");
		Inspect_Struct_media_output (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	live_node_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a live_node_info:\n");
		Inspect_Struct_live_node_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_request_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_request_info:\n");
		Inspect_Struct_media_request_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_node_attribute *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_node_attribute:\n");
		Inspect_Struct_media_node_attribute (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_codec_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_codec_info:\n");
		Inspect_Struct_media_codec_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	GUID *			inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a GUID:\n");
		Inspect_Struct_GUID (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_beos_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_beos_description:\n");
		Inspect_Struct_media_beos_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_quicktime_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_quicktime_description:\n");
		Inspect_Struct_media_quicktime_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_avi_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_avi_description:\n");
		Inspect_Struct_media_avi_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_avr_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_avr_description:\n");
		Inspect_Struct_media_avr_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_asf_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_asf_description:\n");
		Inspect_Struct_media_asf_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_mpeg_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_mpeg_description:\n");
		Inspect_Struct_media_mpeg_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_wav_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_wav_description:\n");
		Inspect_Struct_media_wav_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_aiff_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_aiff_description:\n");
		Inspect_Struct_media_aiff_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_misc_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_misc_description:\n");
		Inspect_Struct_media_misc_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_format_description *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_format_description:\n");
		Inspect_Struct_media_format_description (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	node_ref *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a node_ref:\n");
		Inspect_Struct_node_ref (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	compound_type *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a compound_type:\n");
		Inspect_Struct_compound_type (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	property_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a property_info:\n");
		Inspect_Struct_property_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	value_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a value_info:\n");
		Inspect_Struct_value_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	area_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a area_info:\n");
		Inspect_Struct_area_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	port_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a port_info:\n");
		Inspect_Struct_port_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	sem_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a sem_info:\n");
		Inspect_Struct_sem_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	thread_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a thread_info:\n");
		Inspect_Struct_thread_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	team_usage_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a team_usage_info:\n");
		Inspect_Struct_team_usage_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	team_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a team_info:\n");
		Inspect_Struct_team_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	cpu_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a cpu_info:\n");
		Inspect_Struct_cpu_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	system_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a system_info:\n");
		Inspect_Struct_system_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	media_timed_event *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a media_timed_event:\n");
		Inspect_Struct_media_timed_event (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
/*
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	clipping_rect *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a clipping_rect:\n");
//		Inspect_Struct_clipping_rect (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}
*/


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	app_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a app_info:\n");
		Inspect_Struct_app_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	text_run *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a text_run:\n");
		Inspect_Struct_text_run (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	text_run_array *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a text_run_array:\n");
		Inspect_Struct_text_run_array (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	timecode_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a timecode_info:\n");
		Inspect_Struct_timecode_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	translation_format *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a translation_format:\n");
		Inspect_Struct_translation_format (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	translator_info *		inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a translator_info:\n");
		Inspect_Struct_translator_info (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorBitmap * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorBitmap:\n");
		Inspect_Struct_TranslatorBitmap (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorSound * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorSound:\n");
		Inspect_Struct_TranslatorSound (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorStyledTextRecordHeader * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorStyledTextRecordHeader:\n");
		Inspect_Struct_TranslatorStyledTextRecordHeader (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorStyledTextStreamHeader * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorStyledTextStreamHeader:\n");
		Inspect_Struct_TranslatorStyledTextStreamHeader (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorStyledTextTextHeader * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorStyledTextTextHeader:\n");
		Inspect_Struct_TranslatorStyledTextTextHeader (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}


/***************************************************************
***************************************************************/
void
TraceObject
	(
	ClueCategory	inCAT
,	ClueEvent		inEVT
,	uint32			inLineNumber
,	const char *	inFileName
,	const char *	inMethodDefinition
,	TranslatorStyledTextStyleHeader * 	inValue
,	const char *	inDescription
	)
{
	if ((CAM.m_data->m_port >= B_OK) && (CAM.m_data->m_mask[inCAT] & inEVT)) //do we pass the filter?
	{
		thread_info TI;
		get_thread_info (find_thread (NULL), &TI);
		FingerPrint FP = {inCAT, inEVT, TI.thread, TI.team, real_time_clock_usecs (), inLineNumber, atomic_add (&Sequence, 1)};

		BString strDetails ("Inspecting a TranslatorStyledTextStyleHeader:\n");
		Inspect_Struct_TranslatorStyledTextStyleHeader (strDetails, inValue, 0, "\n");

		GatherDataAndSend (&FP, inFileName, inMethodDefinition, inDescription, strDetails);
	}
}



