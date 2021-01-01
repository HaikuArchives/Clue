#include <Be.h>

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
#include "InspectOther.h"
#include "InspectApplicationKitObjects.h"
#include "InspectInterfaceKitObjects.h"
#include "InspectStorageKitObjects.h"
#include "utility.h"


char CodeUnknown[5] = "    ";
char buf[200 + B_PATH_NAME_LENGTH] = "";
char TypeCodeUnknown[20] = "";

extern const char * pTrue;
extern const char * pFalse;
extern const char * g_pIndentation;
extern const char * g_pFailedWithError;
extern const char * g_pNewline;


/***************************************************************
***************************************************************/
void
getcode
	(
	type_code		code,
	char *			out  //char array should be about 17
	)
{
	char hex[] = "0123456789abcdef";
	*(out++) = '\'';

	for (int ix=0; ix<4; ix++) {
		unsigned char ch = (code >> 24);
		if ((ch < 32) || (ch == '\\') || (ch > 127)) {
			*(out++) = '\\';
			*(out++) = 'x';
			*(out++) = hex[(ch>>4)&0xf];
			*(out++) = hex[ch&0xf];
		} else {
			*(out++) = ch;
		}
		code <<= 8;
	}
	*(out++) = '\'';
	*(out++) = ',';
	*(out) = 0;
}


/***************************************************************
***************************************************************/
const char *
GetTypeCode
	(
	type_code tc
	)
{
	switch ((char) (tc >> 24))
	{
		case 'A':
			if (B_ANY_TYPE == tc)
				return "B_ANY_TYPE, ";
			else if (B_ATOM_TYPE == tc)
				return "B_ATOM_TYPE, ";
			else if (B_ATOMREF_TYPE == tc)
				return "B_ATOMREF_TYPE, ";

			break;
		case 'B':
			switch ((char) (tc >> 16))
			{
				case 'M':
					if (B_MEDIA_PARAMETER_TYPE == tc)
						return "B_MEDIA_PARAMETER_TYPE, BMCT";
					else if (B_MEDIA_PARAMETER_WEB_TYPE == tc)
						return "B_MEDIA_PARAMETER_WEB_TYPE, BMCW";
					else if (B_MEDIA_PARAMETER_GROUP_TYPE == tc)
						return "B_MEDIA_PARAMETER_GROUP_TYPE, BMCG";
							
					break;
				case 'O':
					if (B_BOOL_TYPE == tc)
						return "B_BOOL_TYPE,";
					break;
				case 'P':
					if (B_POINT_TYPE == tc)
						return "B_POINT_TYPE,";
					break;
				case 'Y':
					if (B_INT8_TYPE == tc)
						return "B_INT8_TYPE,";
			}

			break;
		case 'C':
			if (B_CHAR_TYPE == tc)
				return "B_CHAR_TYPE,";
			else if (B_COLOR_8_BIT_TYPE == tc)
				return "B_COLOR_8_BIT_TYPE,";
			else if (B_STRING_TYPE == tc)
				return "B_STRING_TYPE,";

			break;
		case 'D':
			if (B_DOUBLE_TYPE == tc)
				return "B_DOUBLE_TYPE,";

			break;
		case 'F':
			if (B_FLOAT_TYPE == tc)
				return "B_FLOAT_TYPE,";

			break;
		case 'G':
			if (B_GRAYSCALE_8_BIT_TYPE == tc)
				return "B_GRAYSCALE_8_BIT_TYPE,";

			break;
		case 'L':
			if (B_INT32_TYPE == tc)
				return "B_INT32_TYPE,";
			else if (tc == B_INT64_TYPE)
				return "B_INT64_TYPE,";

			break;
		case 'M':
			if (B_MIME_TYPE == tc)
				return "B_MIME_TYPE,";
			else if ('MIMS' == tc)
				return "B_MIME_STRING_TYPE,";
			else if (B_MESSAGE_TYPE == tc)
				return "B_MESSAGE_TYPE,";
			else if (B_MESSENGER_TYPE == tc)
				return "B_MESSENGER_TYPE,";
			else if (B_MONOCHROME_1_BIT_TYPE == tc)
				return "B_MONOCHROME_1_BIT_TYPE,";

			break;
		case 'O':
			if (B_OBJECT_TYPE == tc)
				return "B_OBJECT_TYPE,";
			else if (B_OFF_T_TYPE == tc)
				return "B_OFF_T_TYPE,";

			break;
		case 'P':
			if ( B_PATTERN_TYPE == tc)
				return " B_PATTERN_TYPE,";
			else if (B_POINTER_TYPE == tc)
				return "B_POINTER_TYPE,";

			break;
		case 'R':
			if (B_RECT_TYPE == tc)
				return "B_RECT_TYPE,";
			else if (B_REF_TYPE == tc)
				return "B_REF_TYPE,";
			else if (B_RGB_32_BIT_TYPE == tc)
				return "B_RGB_32_BIT_TYPE,";
			else if (B_RGB_COLOR_TYPE == tc)
				return "B_RGB_COLOR_TYPE,";
			else if (B_RAW_TYPE == tc)
				return "B_RAW_TYPE,";

			break;
		case 'S':
			if (B_INT16_TYPE == tc)
				return "B_INT16_TYPE,";
			else if (B_SIZE_T_TYPE == tc)
				return "B_SIZE_T_TYPE,";
			else if (B_SSIZE_T_TYPE == tc)
				return "B_SSIZE_T_TYPE,";
			else if (B_PROPERTY_INFO_TYPE == tc)
				return "B_PROPERTY_INFO_TYPE, ";

			break;
		case 'T':
			if (B_TIME_TYPE == tc)
				return "B_TIME_TYPE,";
			else if (B_ASCII_TYPE == tc)
				return "B_ASCII_TYPE,";

			break;
		case 'U':
			if (B_UINT8_TYPE == tc)
				return "B_UINT8_TYPE,";
			else if (B_UINT16_TYPE == tc)
				return "B_UINT16_TYPE,";
			else if (B_UINT32_TYPE == tc)
				return "B_UINT32_TYPE,";
			else if (B_UINT64_TYPE == tc)
				return "B_UINT64_TYPE";
	}

	getcode (tc, TypeCodeUnknown);
	return TypeCodeUnknown;
}


/***************************************************************
***************************************************************/
const char *
GetCommandCode
	(
	uint32 type
	)
{
	switch ((char) (type >> 24))
	{
		case '_':
			switch ((char) (type >> 16))
			{
				case 'A':
					if ('_ABR' == type)
						return "B_ABOUT_REQUESTED, _ABR";
					else if ('_ACT' == type)
						return "B_WINDOW_ACTIVATED, _ACT";
					else if ('_AMN' == type)
						return "_APP_MENU_, _AMN";
					else if ('_AOV' == type)
						return "B_ACQUIRE_OVERLAY_LOCK, _AOV";
					else if ('_ARG' == type)
						return "B_ARGV_RECEIVED, _ARG";

					break;
				case 'B':
					if ('_BRM' == type)
						return "_BROWSER_MENUS_, _BRM";

					break;
				case 'C':
					if ('_CNC' == type)
						return "B_CANCEL, _CNC";

					break;
				case 'D':
					if ('_DPD' == type)
						return "_DISPOSE_DRAG_, _DPD";

					break;
				case 'E':
					if ('_EVP' == type)
						return "_EVENTS_PENDING_, _EVP";

					break;
				case 'K':
					if ('_KYD' == type)
						return "B_KEY_DOWN, _KYD";
					else if ('_KYU' == type)
						return "B_KEY_UP, _KYU";

					break;
				case 'M':
					switch ((char) (type >> 8))
					{
						case 'C':
							if ('_MCH' == type)
								return "B_MODIFIERS_CHANGED, _MCH";

							break;
						case 'D':
							if ('_MDN' == type)
								return "B_MOUSE_DOWN, _MDN";
							else if ('_MDP' == type)
								return "_MESSAGE_DROPPED_, _MDP";

							break;
						case 'E':
							if ('_MEV' == type)
								return "_MENU_EVENT_, _MEV";
							else if ('_MEX' == type)
								return "B_MOUSE_ENTER_EXIT, _MEX";

							break;
						case 'M':
							if ('_MMV' == type)
									return "B_MOUSE_MOVED, _MMV";

							break;
						case 'N':
							if ('_MND' == type)
								return "_MENUS_DONE_, _MND";

							break;
						case 'U':
							if ('_MUP' == type)
								return "B_MOUSE_UP, _MUP";

							break;
						case 'W':
							if ('_MWC' == type)
								return "B_MOUSE_WHEEL_CHANGED, _MWC";
					}
					break;
				case 'N':
					if ('_NVL' == type)
						return "_VOLUME_MOUNTED_, _NVL";

					break;
				case 'O':
					if ('_OWS' == type)
						return "B_OPEN_IN_WORKSPACE, _OWS";

					break;
				case 'P':
					if ('_PUL' == type)
						return "B_PULSE, _PUL";
					else if ('_PBL' == type)
						return "_PING_, _PBL";
					else if ('_PCH' == type)
						return "B_PRINTER_CHANGED, _PCH";
					else if ('_PIN' == type)
						return "_PRINTER_INFO_, _PIN";
					else if ('_PSL' == type)
						return "_SELECT_PRINTER_, _PSL";

					break;
				case 'Q':
					if ('_QIT' == type)
						return "_QUIT_, _QIT";
					else if ('_QRQ' == type)
						return "B_QUIT_REQUESTED, _QRQ";

					break;
				case 'R':
					if ('_ROV' == type)
						return "B_RELEASE_OVERLAY_LOCK, _ROV";
					else if ('_RRC' == type)
						return "B_REFS_RECEIVED, _RRC";
					else if ('_RTR'== type)
						return "B_READY_TO_RUN, _RTR";

					break;
				case 'S':
					if ('_SCH' == type)
						return "B_SCREEN_CHANGED, _SCH";
					else if ('_SDH' == type)
						return "_SHOW_DRAG_HANDLES_, _SDH";
					else if ('_SUP' == type)
						return "_SETUP_PRINTER_, _SUP";

					break;
				case 'U':
					switch ((char) (type >> 8))
					{
						case 'K':
							if ('_UKD' == type)
								return "B_UNMAPPED_KEY_DOWN, _UKD";
							else if ('_UKU' == type)
								return "B_UNMAPPED_KEY_UP, _UKU";

							break;
						case 'P':
							if (type == '_UPD')
								return "_UPDATE_, _UPD";
							else if (type == '_UPN')
								return "_UPDATE_IF_NEEDED_, _UPN";
					}
					break;
				case 'V':
					if ('_VMV' == type)
						return "B_VIEW_MOVED, _VMV";
					else if ('_VRS' == type)
						return "B_VIEW_RESIZED, _VRS";
					else if ('_VCH' == type)
						return "B_VALUE_CHANGED, _VCH";
					else if ('_VRM' == type)
						return "_VOLUME_UNMOUNTED_, _VRM";

					break;
				case 'W':
					if ('_WMV' == type)
						return "B_WINDOW_MOVED, _WMV";
					else if ('_WRS' == type)
						return "B_WINDOW_RESIZED, _WRS";
					else if ('_WAC' == type)
						return "B_WORKSPACE_ACTIVATED, _WAC";
					else if ('_WCG' == type)
						return "B_WORKSPACES_CHANGED, _WCG";
					else if ('_WMN' == type)
						return "B_MINIMIZE, _WMN";
					else if ('_WZM' == type)
						return "B_ZOOM, _WZM";
			}
			break;
		case 'A':
			if ('ARCV' == type)
				return "B_ARCHIVED_OBJECT, ARCV";
			else if ('AREL' == type)
				return "B_SILENT_RELAUNCH, AREL";

			break;
		case 'B':
			if ('BRAQ' == type)
				return "B_SOME_APP_QUIT, BRAQ";
			else if ('BRAS' == type)
				return "B_SOME_APP_LAUNCHED, BRAS";
			else if ('BRAW' == type)
				return "B_SOME_APP_ACTIVATED, BRAW";

			break;
		case 'C':
			if ('CCUT' == type)
				return "B_CUT, CCUT";
			else if ('CIVK' == type)
				return "B_CONTROL_INVOKED, CIVK";
			else if ('CMOD' == type)
				return "B_CONTROL_MODIFIED, CMOD";
			else if ('COPY' == type)
				return "B_COPY, COPY";

			break;
		case 'D':
			switch ((char) (type >> 16))
			{
				case 'A':
					if ('DATA' == type)
						return "B_SIMPLE_DATA, DATA";

					break;
				case 'D':
					if ('DDCP' == type)
						return "B_COPY_TARGET, DDCP";
					else if ('DDMV' == type)
						return "B_MOVE_TARGET, DDMV";
					else if ('DDRM' == type)
						return "B_TRASH_TARGET, DDRM";
					else if ('DDLN' == type)
						return "B_LINK_TARGET, DDLN";
			}
			break;
		case 'E':
			if ('ENDO' == type)
				return "B_ENDORSABLE, ENDO";

			break;
		case 'I':
			if ('IDCH' == type)
				return "B_INPUT_DEVICES_CHANGED, IDCH";
			else if ('IMEV' == type)
				return "B_INPUT_METHOD_EVENT, IMEV";

			break;
		case 'M':
			if ('MIME' == type)
				return "B_MIME_DATA, MIME";
			else if ('MNOT' == type)
				return "B_MESSAGE_NOT_UNDERSTOOD, MNOT";

			break;
		case 'N':
			if ('NDMN' == type)
				return "B_NODE_MONITOR, NDMN";
			else if ('NONE' == type)
				return "B_NO_REPLY, NONE";
			else if ('NTCH' == type)
				return "B_OBSERVER_NOTICE_CHANGE, NTCH";

			break;
		case 'P':
			if ('PCNT' == type)
				return "B_COUNT_PROPERTIES, PCNT";
			else if ('PCRT' == type)
				return "B_CREATE_PROPERTY, PCRT";
			else if ('PDEL' == type)
				return "B_DELETE_PROPERTY, PDEL";
			else if ('PEXE' == type)
				return "B_EXECUTE_PROPERTY, PEXE";
			else if ('PGET' == type)
				return "B_GET_PROPERTY, PGET";
			else if ('PSET' == type)
				return "B_SET_PROPERTY, PSET";
			else if ('PSTE' == type)
				return "B_PASTE, PSTE";

			break;
		case 'Q':
			if ('QUPD' == type)
				return "B_QUERY_UPDATE, QUPD";

			break;
		case 'R':
			if ('RPLY' == type)
				return "B_REPLY, RPLY";

			break;
		case 'S':
			switch ((char) (type >> 16))
			{
				case 'A':
					if ('SALL' == type)
						return "B_SELECT_ALL, SALL";
					else if ('SAVE' == type)
						return "B_SAVE_REQUESTED, SAVE";

					break;
				case 'B':
					if ('SBUP' == type)
						return "B_UPDATE_STATUS_BAR, SBUP";
					else if ('SBRS' == type)
						return "B_RESET_STATUS_BAR, SBRS";

					break;
				case 'U':
					if ('SUIT' == type)
						return "B_GET_SUPPORTED_SUITES, SUIT";
			}
			break;
		case 'U':
			if ('UNDO' == type)
				return "B_UNDO, UNDO";

			break;
		case 'W':
			if ('WDMB' ==  type)
				return "B_WINDOW_MOVE_BY, WDMB";
			else if ('WDMT' == type)
				return "B_WINDOW_MOVE_TO, WDMT";
			break;
	}

	CodeUnknown[0] = (char) (type >> 24);
	CodeUnknown[1] = (char) (type >> 16);
	CodeUnknown[2] = (char) (type >> 8);
	CodeUnknown[3] = (char) type;
	CodeUnknown[4] = '\0';
	return (CodeUnknown);
}


					//            1         2         3         4         5         6         7
					//   12345678901234567890123456789012345678901234567890123456789012345678901
const char *spaces =	"              ";

int	sl (14);


/***************************************************************
***************************************************************/
void
Inspect_BMessage
	(
	BString & inDetails
,	BMessage * inMsg
,	int32 inIndent
,	const char * inName
,	int32 inIndex
,	int32 inRange
	)
{
	BString tabindent;
	int32 i (0);
	for (i = 0; i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inMsg)
	{
		BRect valBRect;
		entry_ref valEntryRef;
		BMessage valBMessage;

#ifdef CLUE_ON_ZETA_HACK
		char const * name (NULL);
#else
		char * name (NULL);
#endif
		uint32 type (0);
		ssize_t numBytes (0);
		void * pvoid (NULL);
		char header[1000] = "";

		int32 offset (0);
		int32 count (0);
		status_t rc (B_ERROR);

		offset = strlen (inName);
		if (offset > sl)
		{
			offset = sl;
		}

		sprintf (buf, "%-18s (%s),%s [%li of %li], what=%s\n", 
			"B_MESSAGE_TYPE,", inName, spaces + offset, inIndex, inRange, GetCommandCode (inMsg->what));

		inDetails << tabindent << buf;

		tabindent << g_pIndentation;

		for (i = 0; inMsg->GetInfo (B_ANY_TYPE, i, &name, &type, &inRange) == B_OK; i++)
		{
			offset = strlen (name);
			if (offset > sl)
			{
				offset = sl;
			}
//			count = inRange;
			count = 0;

			const char * ptc (GetTypeCode (type));
			sprintf (header, "%-18s (%s),%s ", ptc, name, spaces + offset);

			switch (type)
			{
				case B_BOOL_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_BOOL_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (bool) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%s (%hi)\n",
									count, inRange, numBytes, *((bool *) pvoid) ? "True" : "False",
									*((bool *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE SIZE OF %li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes, sizeof (bool));

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (bool));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_INT8_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_INT8_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (int8) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#hx (%hi)\n",
									count, inRange, numBytes, *((int8 *) pvoid), *((int8 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE SIZE OF %li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes, sizeof (int8));

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (int8));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_UINT8_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_UINT8_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (uint8) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#hx (%hu)\n",
									count, inRange, numBytes, *((uint8 *) pvoid), *((uint8 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE SIZE OF %li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes, sizeof (uint8));

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (uint8));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_INT16_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_INT16_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (int16) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#hx (%hi)\n",
									count, inRange, numBytes, *((int16 *) pvoid), *((int16 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE SIZE OF %li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes, sizeof (int16));

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (int16));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_UINT16_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_UINT16_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (uint16) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#hx (%hu)\n",
									count, inRange, numBytes, *((uint16 *) pvoid), *((uint16 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE SIZE OF %li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes, sizeof (uint16));

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (uint16));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_INT32_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_INT32_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (int32) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#x (%li)\n",
									count, inRange, numBytes, *((int32 *) pvoid), *((int32 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (int32));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_UINT32_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_INT32_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (uint32) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#x (%lu)\n",
									count, inRange, numBytes, *((uint32 *) pvoid), *((uint32 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (uint32));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_INT64_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_INT64_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (int64) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=0x%#Lx (%Li)\n",
									count, inRange, numBytes, *((int64 *) pvoid), *((int64 *) pvoid));
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (int64));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_UINT64_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_UINT64_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (uint64) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=0x%#Lx (%Lu)\n",
									count, inRange, numBytes, *((int64 *) pvoid), *((uint64 *) pvoid));
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (uint64));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_FLOAT_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_FLOAT_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (float) == numBytes) //makes sure the data fits
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%.4Lf\n",
									count, inRange, numBytes, *((float *) pvoid));
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (float));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_DOUBLE_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_DOUBLE_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof(double) == numBytes) //makes sure the data fits
							{
								sprintf (buf, "%s[%li of %li], size=%2li, value=%.8Lf\n",
									header, count, inRange, numBytes, *((double *) pvoid));
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (double));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_RECT_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_RECT_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof(BRect) == numBytes) //makes sure the data fits
							{
								valBRect = *((BRect *) pvoid);
								sprintf (buf, "[%li of %li], size=%2li, L=%.4f, T=%.4f, R=%.4f, B=%.4f\n",
									count, inRange, numBytes,
									valBRect.left, valBRect.top, valBRect.right, valBRect.bottom);
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (BRect));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_MESSAGE_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindMessage (name, count - 1, &valBMessage);
						if (B_OK == rc)
						{
							if (inIndent < 10)
							{
								Inspect_BMessage (inDetails, &valBMessage, inIndent + 1, name, count, inRange);
							}
							else
							{
								sprintf (buf, "[%li of %li], MAX NUMBER OF NESTED LEVELS OF BMESSAGES ARE PRINTED\n",
									count, inRange);
								inDetails << tabindent << header << buf;
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_POINT_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_POINT_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof(BPoint) == numBytes) //makes sure the data fits
							{
								sprintf (buf, "[%li of %li], size=%2li, X=%f, Y=%f\n",
									count, inRange, numBytes, ((BPoint *) pvoid)->x, ((BPoint *) pvoid)->y);
								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (BPoint));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_STRING_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_STRING_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (numBytes < 2000) //don't copy a REALLY LONG string, use HexDump instead
							{
								sprintf (buf, "[%li of %li], size=%2li, ",
									count, inRange, numBytes);
								inDetails << tabindent << header << buf << (char *) pvoid << g_pNewline;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, DISPLAY HEX DUMP:\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent);
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_REF_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindRef (name, count - 1, &valEntryRef);
						if (B_OK == rc)
						{
							// Find the path...
							BEntry bentry (&valEntryRef);
							BPath path;
							if (B_OK == bentry.InitCheck ())
							{
								bentry.GetPath (&path);
							}

							sprintf (buf, "[%li of %li], device=%li, directory=%Li, name='%s'\n",
								count, inRange, valEntryRef.device, valEntryRef.directory, valEntryRef.name);
							inDetails << tabindent << header << buf;
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
				case B_POINTER_TYPE:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, B_POINTER_TYPE, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							if (sizeof (int32) == numBytes)
							{
								sprintf (buf, "[%li of %li], size=%2li, value=%#x\n",
									count, inRange, numBytes, *((int32 *) pvoid));

								inDetails << tabindent << header << buf;
							}
							else
							{
								sprintf (buf, "[%li of %li], size=%2li, SIZE DIDN'T MATCH DATA TYPE, DISPLAY HEX DUMP\n",
									count, inRange, numBytes);

								inDetails << tabindent << header << buf;
								HexDump (pvoid, numBytes, inDetails, tabindent, sizeof (int32));
							}
						}
						else
						{
							sprintf (buf, "[%li of %li], INTERNAL DATA FORMAT WAS BAD, FINDDATA RETURNED %li, %2li\n",
								count - 1, inRange, rc, numBytes);

							inDetails << tabindent << header << buf;
						}
					}
					break;
/*
			case B_MESSENGER_TYPE:
				*inStr << tabindent << "B_MESSENGER_TYPE\n";
				break;
			case B_MIME_TYPE:
				*inStr << tabindent << "B_MIME_TYPE\n";
				break;
			case B_MONOCHROME_1_BIT_TYPE:
				*inStr << tabindent << "B_MONOCHROME_1_BIT_TYPE\n";
				break;
			case B_OBJECT_TYPE:
				*inStr << tabindent << "B_OBJECT_TYPE\n";
				break;
			case B_OFF_T_TYPE:
				*inStr << tabindent << "B_OFF_T_TYPE\n";
				break;
			case B_PATTERN_TYPE:
				*inStr << tabindent << "B_PATTERN_TYPE\n";
				break;
			case B_RAW_TYPE:
				*inStr << tabindent << "B_RAW_TYPE\n";
				break;
			case B_RGB_32_BIT_TYPE:
				*inStr << tabindent << "B_RGB_32_BIT_TYPE\n";
				break;
			case B_RGB_COLOR_TYPE:
				*inStr << tabindent << "B_RGB_COLOR_TYPE\n";
				break;
			case B_SIZE_T_TYPE:
				*inStr << tabindent << "B_SIZE_T_TYPE\n";
				break;
			case B_SSIZE_T_TYPE:
				*inStr << tabindent << "B_SSIZE_T_TYPE\n";
				break;
			case B_TIME_TYPE:
				*inStr << tabindent << "B_TIME_TYPE\n";
				break;
			case B_UINT64_TYPE:
				*inStr << tabindent << "B_UINT64_TYPE\n";
				break;
			case B_MEDIA_PARAMETER_TYPE:
				*inStr << tabindent << "B_MEDIA_PARAMETER_TYPE\n";
				break;
			case B_MEDIA_PARAMETER_WEB_TYPE:
				*inStr << tabindent << "B_MEDIA_PARAMETER_WEB_TYPE\n";
				break;
			case B_MEDIA_PARAMETER_GROUP_TYPE:
				*inStr << tabindent << "B_MEDIA_PARAMETER_GROUP_TYPE\n";
				break;
			case B_ATOM_TYPE:
				*inStr << tabindent << "B_ATOM_TYPE\n";
				break;
			case B_ATOMREF_TYPE:
				*inStr << tabindent << "B_ATOMREF_TYPE\n";
				break;
			case B_ASCII_TYPE:
				*inStr << tabindent << "B_ASCII_TYPE\n";
				break;
			case B_CHAR_TYPE:
				while (count-- > 0)
				{
					inMsg->FindFloat (name, count, &valFloat);
					*inStr << tabindent << "B_CHAR_TYPE (" << name << ") [" << count + 1 <<" of " << inRange << "]\tvalue=" << valFloat << g_pNewline;
				}
				*inStr << tabindent << "B_CHAR_TYPE\n";
				break;
			case B_COLOR_8_BIT_TYPE:
				*inStr << tabindent << "B_COLOR_8_BIT_TYPE\n";
				break;
			case B_GRAYSCALE_8_BIT_TYPE:
				*inStr << tabindent << "B_GRAYSCALE_8_BIT_TYPE\n";
				break;
*/
				default:
					while (count++ < inRange)
					{
						rc = inMsg->FindData (name, type, count - 1, (const void **) &pvoid, &numBytes);
						if (B_OK == rc)
						{
							sprintf (buf, "%s[%li of %li], size=%2li\n",
								header, count, inRange, numBytes);

							inDetails << tabindent << buf;
							HexDump (pvoid, numBytes, inDetails, tabindent);
						}
						else
						{
							inDetails << tabindent << "type was invalid[" << rc << "] for name '" << name << "' and index " << count - 1 << g_pNewline;
						}
					}
					break;
			}
		}
	}
	else
	{
		inDetails << tabindent << "The BMessage was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BHandler
	(
	BString & strDetails
,	BHandler * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}


	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BHandler object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "Name= " << inValue->Name () << g_pNewline;
		BMessage msg;
		status_t aStatusT (inValue->GetSupportedSuites (&msg));
		if (B_OK == aStatusT)
		{
			GetHexString (hexbuf, (intptr_t) &msg);
			strDetails << tabindent << "GetSupportedSuites: [BMessage object, ptr=" << hexbuf << "]\n";
			Inspect_BMessage (strDetails, &msg, inIndent + 1, B_EMPTY_STRING, 1, 1);
		}
		else
		{
			GetStatusTDescription (strDetails, aStatusT, inIndent, "GetSupportedSuites: failed, ");
		}
	}
	else
	{
		strDetails << tabindent << "The BHandler was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BInvoker
	(
	BString & strDetails
,	BInvoker * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	if (NULL != inValue)
	{
		++inIndent;

		char hexbuf[20];
		GetHexString (hexbuf, (intptr_t) inValue);
		strDetails << tabindent << pDescription << "[BInvoker object, ptr=" << hexbuf << "]\n";
		tabindent << g_pIndentation;

		BMessage * pMsg (inValue->Message ());
		if (NULL == pMsg)
		{
			strDetails << tabindent << "Message= NULL\n";
		}
		else
		{
			GetHexString (hexbuf, (intptr_t) pMsg);
			strDetails << tabindent << "Message: [BMessage object, ptr=" << hexbuf << "]\n";
			Inspect_BMessage (strDetails, pMsg, inIndent + 1, B_EMPTY_STRING, 1, 1);
		}
		strDetails << tabindent << "Command= " << inValue->Command () << g_pNewline;
		strDetails << tabindent << "IsTargetLocal= " << (inValue->IsTargetLocal () ? pTrue : pFalse);
		bigtime_t aBigtime (inValue->Timeout ());
		strDetails << tabindent << "Timeout= (" << aBigtime << ")" << (B_INFINITE_TIMEOUT == aBigtime ? ", B_INFINITE_TIMEOUT\n" : g_pNewline);
	}
	else
	{
		strDetails << tabindent = "The BInvoker was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BLooper
	(
	BString & strDetails
,	BLooper * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BLooper object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		bool aBool (inValue->IsLocked ());
		if (aBool) //then we can continue
		{
			strDetails << tabindent << "CountHandlers= " << inValue->CountHandlers () << g_pNewline;
			strDetails << tabindent << "CountLocks= " << inValue->CountLocks () << g_pNewline;
			strDetails << tabindent << "CountLockRequests= " << inValue->CountLockRequests () << g_pNewline;
			strDetails << tabindent << "IsLocked= " << pTrue;
			strDetails << tabindent << "Team= " << inValue->Team () << g_pNewline;
			strDetails << tabindent << "Thread= " << inValue->Thread () << g_pNewline;

/*TODO
			if (DoBaseClasses)
			{
				strDetails << tabindent << g_pNewline;
				Inspect_BHandler (strDetails, (BHandler *) inValue, inIndent, "  + BLooper baseclass ");
			}
*/
		}
		else
		{
			strDetails << tabindent << "The BLooper must be locked before Clue can continue!\n";
		}
	}
	else
	{
		strDetails << tabindent << "The BLooper was NULL.\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BApplication
	(
	BString & strDetails
,	BApplication * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BApplication object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		bool aBool (inValue->IsLocked ());
		if (aBool) //then we can continue
		{
			app_info aAI;
			status_t aStatusT (inValue->GetAppInfo (&aAI));
			if (B_OK == aStatusT)
			{
				Inspect_Struct_app_info (strDetails, &aAI, inIndent, "GetAppInfo: ");
			}
			else
			{
				GetStatusTDescription (strDetails, aStatusT, inIndent, "GetAppInfo: failed, ");
			}
			strDetails << tabindent << "IsLaunching= " << (inValue->IsLaunching () ? pTrue : pFalse);
			strDetails << tabindent << "IsCursorHidden= " << (inValue->IsCursorHidden () ? pTrue : pFalse);
			strDetails << tabindent << "CountWindows= " << inValue->CountWindows () << g_pNewline;

/*TODO
			if (DoBaseClasses)
			{
				strDetails << tabindent << g_pNewline;
				Inspect_BLooper (strDetails, (BLooper *) inValue, --inIndent, "  + BApplication baseclass ", true);
			}
*/
		}
		else
		{
			strDetails << tabindent << "The BLooper must be locked before Clue can continue!\n";
		}
	}
	else
	{
		strDetails << tabindent << "The BApplication was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BClipboard
	(
	BString & strDetails
,	BClipboard * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BClipboard object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		bool aBool (inValue->IsLocked ());
		if (aBool)
		{
			BMessage * pMessage (inValue->Data ());
			GetHexString (hexbuf, (intptr_t) pMessage);
			strDetails << tabindent << "Data: [BMessage object, ptr=" << hexbuf << "]\n";
			Inspect_BMessage (strDetails, pMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);
			strDetails << tabindent << "LocalCount= " << inValue->LocalCount () << g_pNewline;
			strDetails << tabindent << "SystemCount= " << inValue->SystemCount () << g_pNewline;
			strDetails << tabindent << "IsLocked= " << (aBool ? pTrue : pFalse);
			strDetails << tabindent << "Name= " << inValue->Name () << g_pNewline;
		}
		else
		{
			strDetails << tabindent << "The BClipboard must be locked before Clue can continue!\n";
		}
	}
	else
	{
		strDetails << tabindent << "The BClipboard was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMessageFilter
	(
	BString & strDetails
,	BMessageFilter * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMessageFilter object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "Command= " << inValue->Command () << g_pNewline;
		strDetails << tabindent << "FiltersAnyCommand= " << (inValue->FiltersAnyCommand () ? pTrue : pFalse);
		BLooper * pLooper (inValue->Looper ());
		//is this safe to do?  Could the BLooper be a different thread?
		strDetails << tabindent << "Looper: Name= " << (pLooper ? pLooper->Name () : "NULL") << g_pNewline;

		message_delivery aMD (inValue->MessageDelivery ());
		Inspect_Enum_message_delivery (strDetails, aMD, inIndent, "MessageDelivery: ");
		message_source aMS (inValue->MessageSource ());
		Inspect_Enum_message_source (strDetails, aMS, inIndent, "MessageSource: ");
	}
	else
	{
		strDetails << tabindent << "The BMessageFilter was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMessageQueue
	(
	BString & strDetails
,	BMessageQueue * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMessageQueue object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "CountMessages= " << inValue->CountMessages () << g_pNewline;
		strDetails << tabindent << "IsEmpty= " << (int) inValue->IsEmpty () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BMessageQueue was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMessageRunner
	(
	BString & strDetails
,	BMessageRunner * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMessageRunner object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "InitCheck= ";
		status_t aStatusT (inValue->InitCheck ());
		if (B_OK == aStatusT)
		{
			strDetails << "B_OK\n" << tabindent << "GetInfo: ";
			bigtime_t aBigtime (0);
			int32 aInt32 (0);
			aStatusT = inValue->GetInfo (&aBigtime, &aInt32);
			if (B_OK == aStatusT)
			{
				strDetails << "interval= " << aBigtime << ", count= " << aInt32 << g_pNewline;
			}
			else
			{
				GetStatusTDescription (strDetails, aStatusT, 0, "failed, ");
			}
		}
		else
		{
			GetStatusTDescription (strDetails, aStatusT, 0, "failed, ");
		}
	}
	else
	{
		strDetails << tabindent << "The BMessageRunner was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BMessenger
	(
	BString & strDetails
,	BMessenger * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BMessenger object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "IsValid= " << (inValue->IsValid () ? pTrue : pFalse);
		BLooper * pLooper (NULL);
		BHandler * pHandler (inValue->Target (&pLooper));
		strDetails << tabindent << "Target: BHandler= " << (NULL != pHandler ? pHandler->Name () : "NULL") << 
			", BLooper= " << (NULL != pLooper ? pLooper->Name () : "NULL") << g_pNewline;
		strDetails << tabindent << "IsTargetLocal= " << (inValue->IsTargetLocal () ? pTrue : pFalse);
		strDetails << tabindent << "Team= " << inValue->Team () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BMessenger was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BFlattenable
	(
	BString & strDetails
,	BFlattenable * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BFlattenable object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "FlattenedSize= " << inValue->FlattenedSize () << g_pNewline;
		strDetails << tabindent << "IsFixedSize= " << (int) inValue->IsFixedSize () << g_pNewline;
		strDetails << tabindent << "TypeCode= " << inValue->TypeCode () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The BFlattenable was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BPropertyInfo
	(
	BString & strDetails
,	BPropertyInfo * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BPropertyInfo object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{

/*TODO
		if (DoBaseClasses)
		{
			strDetails << tabindent << g_pNewline;
			Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		}
*/
	}
	else
	{
		strDetails << tabindent << "The BPropertyInfo was NULL\n";
	}
}


/***************************************************************
***************************************************************/
void
Inspect_BRoster
	(
	BString & strDetails
,	BRoster * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i++ < inIndent;)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[BRoster object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		app_info aAppInfo;
		status_t aStatusT (inValue->GetActiveAppInfo (&aAppInfo));
		if (B_OK == aStatusT)
		{
			Inspect_Struct_app_info (strDetails, &aAppInfo, inIndent, "GetActiveAppInfo: ");
		}
		else
		{
			GetStatusTDescription (strDetails, aStatusT, inIndent, "GetActivateAppInfo: failed, ");
		}

		BMessage aMessage;
		GetHexString (hexbuf, (intptr_t) &aMessage);
		strDetails << tabindent << "GetRecentDocuments: [BMessage object, ptr=" << hexbuf << "]\n";
		inValue->GetRecentDocuments (&aMessage, 10);
		Inspect_BMessage (strDetails, &aMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);

		GetHexString (hexbuf, (intptr_t) &aMessage);
		strDetails << tabindent << "GetRecentFolders: [BMessage object, ptr=" << hexbuf << "]\n";
		inValue->GetRecentFolders (&aMessage, 10);
		Inspect_BMessage (strDetails, &aMessage, inIndent + 1, B_EMPTY_STRING, 1, 1);
	}
	else
	{
		strDetails << tabindent << "The BRoster was NULL\n";
	}
}


