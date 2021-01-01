
#include <Errors.h>
#include <posix/string.h>

#ifndef BGLVIEW_H
#include "GLView.h"
#endif

#ifndef _MEDIA_DEFS_H
#include <MediaDefs.h>
#endif

#ifndef _MIDI_H
#include <Midi.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _TRANSLATION_ERRORS_H
#include <TranslationErrors.h>
#endif

#ifndef UTILITY_H
#include "utility.h"
#endif


extern const char * g_pIndentation;
extern const char * g_pNewline;


/***************************************************************
status_t defined in SupportDefs.h as:
typedef int32					status_t;
***************************************************************/
void
GetStatusTDescription
	(
	BString & strDetails
,	status_t inStatus
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
	GetHexString (hexbuf, (intptr_t) inStatus);
	strDetails << tabindent << pDescription << "(" << inStatus << " or " << hexbuf << ") ";

	if (inStatus < B_OS_ERROR_BASE)  //General Error
	{
		switch (inStatus)
		{
			case B_NO_MEMORY:
				strDetails << "B_NO_MEMORY";
				break;
			case B_IO_ERROR:
				strDetails << "B_IO_ERROR";
				break;
			case B_PERMISSION_DENIED:
				strDetails << "B_PERMISSION_DENIED";
				break;
			case B_BAD_INDEX:
				strDetails << "B_BAD_INDEX";
				break;
			case B_BAD_TYPE:
				strDetails << "B_BAD_TYPE";
				break;
			case B_BAD_VALUE:
				strDetails << "B_BAD_VALUE";
				break;
			case B_MISMATCHED_VALUES:
				strDetails << "B_MISMATCHED_VALUES";
				break;
			case B_NAME_NOT_FOUND:
				strDetails << "B_NAME_NOT_FOUND";
				break;
			case B_NAME_IN_USE:
				strDetails << "B_NAME_IN_USE";
				break;
			case B_TIMED_OUT:
				strDetails << "B_TIMED_OUT";
				break;
		 	case B_INTERRUPTED:
				strDetails << "B_INTERRUPTED";
				break;
			case B_WOULD_BLOCK:
				strDetails << "B_WOULD_BLOCK";
				break;
		 	case B_CANCELED:
				strDetails << "B_CANCELED";
				break;
			case B_NO_INIT:
				strDetails << "B_NO_INIT";
				break;
			case B_BUSY:
				strDetails << "B_BUSY";
				break;
			case B_NOT_ALLOWED:
				strDetails << "B_NOT_ALLOWED";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_APP_ERROR_BASE) //OS Error
	{
		switch (inStatus)
		{
			case B_BAD_SEM_ID:
				strDetails << "B_BAD_SEM_ID";
				break;
			case B_NO_MORE_SEMS:
				strDetails << "B_NO_MORE_SEMS";
				break;
			case B_BAD_THREAD_ID:
				strDetails << "B_BAD_THREAD_ID";
				break;
			case B_NO_MORE_THREADS:
				strDetails << "B_NO_MORE_THREADS";
				break;
			case B_BAD_THREAD_STATE:
				strDetails << "B_BAD_THREAD_STATE";
				break;
			case B_BAD_TEAM_ID:
				strDetails << "B_BAD_TEAM_ID";
				break;
			case B_NO_MORE_TEAMS:
				strDetails << "B_NO_MORE_TEAMS";
				break;
			case B_BAD_PORT_ID:
				strDetails << "B_BAD_PORT_ID";
				break;
			case B_NO_MORE_PORTS:
				strDetails << "B_NO_MORE_PORTS";
				break;
			case B_BAD_IMAGE_ID:
				strDetails << "B_BAD_IMAGE_ID";
				break;
			case B_BAD_ADDRESS:
				strDetails << "B_BAD_ADDRESS";
				break;
			case B_NOT_AN_EXECUTABLE:
				strDetails << "B_NOT_AN_EXECUTABLE";
				break;
			case B_MISSING_LIBRARY:
				strDetails << "B_MISSING_LIBRARY";
				break;
			case B_MISSING_SYMBOL:
				strDetails << "B_MISSING_SYMBOL";
				break;
			case B_DEBUGGER_ALREADY_INSTALLED:
				strDetails << "B_DEBUGGER_ALREADY_INSTALLED";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_INTERFACE_ERROR_BASE) //App Error
	{
		switch (inStatus)
		{
			case B_BAD_REPLY:
				strDetails << "B_BAD_REPLY";
				break;
			case B_DUPLICATE_REPLY:
				strDetails << "B_DUPLICATE_REPLY";
				break;
			case B_MESSAGE_TO_SELF:
				strDetails << "B_MESSAGE_TO_SELF";
				break;
			case B_BAD_HANDLER:
				strDetails << "B_BAD_HANDLER";
				break;
			case B_ALREADY_RUNNING:
				strDetails << "B_ALREADY_RUNNING";
				break;
			case B_LAUNCH_FAILED:
				strDetails << "B_LAUNCH_FAILED";
				break;
			case B_AMBIGUOUS_APP_LAUNCH:
				strDetails << "B_AMBIGUOUS_APP_LAUNCH";
				break;
			case B_UNKNOWN_MIME_TYPE:
				strDetails << "B_UNKNOWN_MIME_TYPE";
				break;
			case B_BAD_SCRIPT_SYNTAX:
				strDetails << "B_BAD_SCRIPT_SYNTAX";
				break;
			case B_LAUNCH_FAILED_NO_RESOLVE_LINK:
				strDetails << "B_LAUNCH_FAILED_NO_RESOLVE_LINK";
				break;
			case B_LAUNCH_FAILED_EXECUTABLE:
				strDetails << "B_LAUNCH_FAILED_EXECUTABLE";
				break;
			case B_LAUNCH_FAILED_APP_NOT_FOUND:
				strDetails << "B_LAUNCH_FAILED_APP_NOT_FOUND";
				break;
			case B_LAUNCH_FAILED_APP_IN_TRASH:
				strDetails << "B_LAUNCH_FAILED_APP_IN_TRASH";
				break;
			case B_LAUNCH_FAILED_NO_PREFERRED_APP:
				strDetails << "B_LAUNCH_FAILED_NO_PREFERRED_APP";
				break;
			case B_LAUNCH_FAILED_FILES_APP_NOT_FOUND:
				strDetails << "B_LAUNCH_FAILED_FILES_APP_NOT_FOUND";
				break;
			case B_BAD_MIME_SNIFFER_RULE:
				strDetails << "B_BAD_MIME_SNIFFER_RULE";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_MEDIA_ERROR_BASE) //Interface Error
	{
		switch (inStatus)
		{
			default:
				break;
		}
	}
	else if (inStatus < B_TRANSLATION_ERROR_BASE) //Media Error
	{
		switch (inStatus)
		{
			case B_STREAM_NOT_FOUND:
				strDetails << "B_STREAM_NOT_FOUND";
				break;
			case B_SERVER_NOT_FOUND:
				strDetails << "B_SERVER_NOT_FOUND";
				break;
			case B_RESOURCE_NOT_FOUND:
				strDetails << "B_RESOURCE_NOT_FOUND";
				break;
			case B_RESOURCE_UNAVAILABLE:
				strDetails << "B_RESOURCE_UNAVAILABLE";
				break;
			case B_BAD_SUBSCRIBER:
				strDetails << "B_BAD_SUBSCRIBER";
				break;
			case B_SUBSCRIBER_NOT_ENTERED:
				strDetails << "B_SUBSCRIBER_NOT_ENTERED";
				break;
			case B_BUFFER_NOT_AVAILABLE:
				strDetails << "B_BUFFER_NOT_AVAILABLE";
				break;
			case B_LAST_BUFFER_ERROR:
				strDetails << "B_LAST_BUFFER_ERROR";
				break;
			case B_MEDIA_SYSTEM_FAILURE:
				strDetails << "B_MEDIA_SYSTEM_FAILURE";
				break;
			case B_MEDIA_BAD_NODE:
				strDetails << "B_MEDIA_BAD_NODE";
				break;
			case B_MEDIA_NODE_BUSY:
				strDetails << "B_MEDIA_NODE_BUSY";
				break;
			case B_MEDIA_BAD_FORMAT:
				strDetails << "B_MEDIA_BAD_FORMAT";
				break;
			case B_MEDIA_BAD_BUFFER:
				strDetails << "B_MEDIA_BAD_BUFFER";
				break;
			case B_MEDIA_TOO_MANY_NODES:
				strDetails << "B_MEDIA_TOO_MANY_NODES";
				break;
			case B_MEDIA_TOO_MANY_BUFFERS:
				strDetails << "B_MEDIA_TOO_MANY_BUFFERS";
				break;
			case B_MEDIA_NODE_ALREADY_EXISTS:
				strDetails << "B_MEDIA_NODE_ALREADY_EXISTS";
				break;
			case B_MEDIA_BUFFER_ALREADY_EXISTS:
				strDetails << "B_MEDIA_BUFFER_ALREADY_EXISTS";
				break;
			case B_MEDIA_CANNOT_SEEK:
				strDetails << "B_MEDIA_CANNOT_SEEK";
				break;
			case B_MEDIA_CANNOT_CHANGE_RUN_MODE:
				strDetails << "B_MEDIA_CANNOT_CHANGE_RUN_MODE";
				break;
			case B_MEDIA_APP_ALREADY_REGISTERED:
				strDetails << "B_MEDIA_APP_ALREADY_REGISTERED";
				break;
			case B_MEDIA_APP_NOT_REGISTERED:
				strDetails << "B_MEDIA_APP_NOT_REGISTERED";
				break;
			case B_MEDIA_CANNOT_RECLAIM_BUFFERS:
				strDetails << "B_MEDIA_CANNOT_RECLAIM_BUFFERS";
				break;
			case B_MEDIA_BUFFERS_NOT_RECLAIMED:
				strDetails << "B_MEDIA_BUFFERS_NOT_RECLAIMED";
				break;
			case B_MEDIA_TIME_SOURCE_STOPPED:
				strDetails << "B_MEDIA_TIME_SOURCE_STOPPED";
				break;
			case B_MEDIA_TIME_SOURCE_BUSY:
				strDetails << "B_MEDIA_TIME_SOURCE_BUSY";
				break;
			case B_MEDIA_BAD_SOURCE:
				strDetails << "B_MEDIA_BAD_SOURCE";
				break;
			case B_MEDIA_BAD_DESTINATION:
				strDetails << "B_MEDIA_BAD_DESTINATION";
				break;
			case B_MEDIA_ALREADY_CONNECTED:
				strDetails << "B_MEDIA_ALREADY_CONNECTED";
				break;
			case B_MEDIA_NOT_CONNECTED:
				strDetails << "B_MEDIA_NOT_CONNECTED";
				break;
			case B_MEDIA_BAD_CLIP_FORMAT:
				strDetails << "B_MEDIA_BAD_CLIP_FORMAT";
				break;
			case B_MEDIA_ADDON_FAILED:
				strDetails << "B_MEDIA_ADDON_FAILED";
				break;
			case B_MEDIA_ADDON_DISABLED:
				strDetails << "B_MEDIA_ADDON_DISABLED";
				break;
			case B_MEDIA_CHANGE_IN_PROGRESS:
				strDetails << "B_MEDIA_CHANGE_IN_PROGRESS";
				break;
			case B_MEDIA_STALE_CHANGE_COUNT:
				strDetails << "B_MEDIA_STALE_CHANGE_COUNT";
				break;
			case B_MEDIA_ADDON_RESTRICTED:
				strDetails << "B_MEDIA_ADDON_RESTRICTED";
				break;
			case B_MEDIA_NO_HANDLER: 
				strDetails << "B_MEDIA_NO_HANDLER";
				break;
			case B_MEDIA_DUPLICATE_FORMAT:
				strDetails << "B_MEDIA_DUPLICATE_FORMAT";
				break;
			case B_MEDIA_REALTIME_DISABLED:
				strDetails << "B_MEDIA_REALTIME_DISABLED";
				break;
			case B_MEDIA_REALTIME_UNAVAILABLE:
				strDetails << "B_MEDIA_REALTIME_UNAVAILABLE";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_MIDI_ERROR_BASE) //Translation Error
	{
		switch (inStatus)
		{
			case B_NO_TRANSLATOR:
				strDetails << "B_NO_TRANSLATOR";
				break;
			case B_ILLEGAL_DATA:
				strDetails << "B_ILLEGAL_DATA";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_STORAGE_ERROR_BASE) //Midi Error
	{
		switch (inStatus)
		{
			case B_BAD_INSTRUMENT:
				strDetails << "B_BAD_INSTRUMENT";
				break;
			case B_BAD_MIDI_DATA:
				strDetails << "B_BAD_MIDI_DATA";
				break;
			case B_ALREADY_PAUSED:
				strDetails << "B_ALREADY_PAUSED";
				break;
			case B_ALREADY_RESUMED:
				strDetails << "B_ALREADY_RESUMED";
				break;
			case B_NO_SONG_PLAYING:
				strDetails << "B_NO_SONG_PLAYING";
				break;
			case B_TOO_MANY_SONGS_PLAYING:
				strDetails << "B_TOO_MANY_SONGS_PLAYING";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_POSIX_ERROR_BASE) //Storage Error
	{
		switch (inStatus)
		{
			case B_FILE_ERROR:
				strDetails << "B_FILE_ERROR";
				break;
			case B_FILE_NOT_FOUND:
				strDetails << "B_FILE_NOT_FOUND";
				break;
			case B_FILE_EXISTS:
				strDetails << "B_FILE_EXISTS";
				break;
			case B_ENTRY_NOT_FOUND:
				strDetails << "B_ENTRY_NOT_FOUND";
				break;
			case B_NAME_TOO_LONG:
				strDetails << "B_NAME_TOO_LONG";
				break;
			case B_NOT_A_DIRECTORY:
				strDetails << "B_NOT_A_DIRECTORY";
				break;
			case B_DIRECTORY_NOT_EMPTY:
				strDetails << "B_DIRECTORY_NOT_EMPTY";
				break;
			case B_DEVICE_FULL:
				strDetails << "B_DEVICE_FULL";
				break;
			case B_READ_ONLY_DEVICE:
				strDetails << "B_READ_ONLY_DEVICE";
				break;
			case B_IS_A_DIRECTORY:
				strDetails << "B_IS_A_DIRECTORY";
				break;
			case B_NO_MORE_FDS:
				strDetails << "B_NO_MORE_FDS";
				break;
			case B_CROSS_DEVICE_LINK:
				strDetails << "B_CROSS_DEVICE_LINK";
				break;
			case B_LINK_LIMIT:
				strDetails << "B_LINK_LIMIT";
				break;
			case B_BUSTED_PIPE:
				strDetails << "B_BUSTED_PIPE";
				break;
			case B_UNSUPPORTED:
				strDetails << "B_UNSUPPORTED";
				break;
			case B_PARTITION_TOO_SMALL:
				strDetails << "B_PARTITION_TOO_SMALL";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_MAIL_ERROR_BASE) //Posix Error
	{
		switch (inStatus)
		{
			case E2BIG:
				strDetails << "E2BIG";
				break;
			case ECHILD:
				strDetails << "ECHILD";
				break;
			case EDEADLK:
				strDetails << "EDEADLK";
				break;
			case EFBIG:
				strDetails << "EFBIG";
				break;
			case EMLINK:
				strDetails << "EMLINK";
				break;
			case ENFILE:
				strDetails << "ENFILE";
				break;
			case ENODEV:
				strDetails << "ENODEV";
				break;
			case ENOLCK:
				strDetails << "ENOLCK";
				break;
			case ENOSYS:
				strDetails << "ENOSYS";
				break;
			case ENOTTY:
				strDetails << "ENOTTY";
				break;
			case ENXIO:
				strDetails << "ENXIO";
				break;
			case ESPIPE:
				strDetails << "ESPIPE";
				break;
			case ESRCH:
				strDetails << "ESRCH";
				break;
			case EFPOS:
				strDetails << "EFPOS";
				break;
			case ESIGPARM:
				strDetails << "ESIGPARM";
				break;
			case EDOM:
				strDetails << "EDOM";
				break;
			case ERANGE:
				strDetails << "ERANGE";
				break;
			case EPROTOTYPE:
				strDetails << "EPROTOTYPE";
				break;
			case EPROTONOSUPPORT:
				strDetails << "EPROTONOSUPPORT";
				break;
			case EPFNOSUPPORT:
				strDetails << "EPFNOSUPPORT";
				break;
			case EAFNOSUPPORT:
				strDetails << "EAFNOSUPPORT";
				break;
			case EADDRINUSE:
				strDetails << "EADDRINUSE";
				break;
			case EADDRNOTAVAIL:
				strDetails << "EADDRNOTAVAIL";
				break;
			case ENETDOWN:
				strDetails << "ENETDOWN";
				break;
			case ENETUNREACH:
				strDetails << "ENETUNREACH";
				break;
			case ENETRESET:
				strDetails << "ENETRESET";
				break;
			case ECONNABORTED:
				strDetails << "ECONNABORTED";
				break;
			case ECONNRESET:
				strDetails << "ECONNRESET";
				break;
			case EISCONN:
				strDetails << "EISCONN";
				break;
			case ENOTCONN:
				strDetails << "ENOTCONN";
				break;
			case ESHUTDOWN:
				strDetails << "ESHUTDOWN";
				break;
			case ECONNREFUSED:
				strDetails << "ECONNREFUSED";
				break;
			case EHOSTUNREACH:
				strDetails << "EHOSTUNREACH";
				break;
			case ENOPROTOOPT:
				strDetails << "ENOPROTOOPT";
				break;
			case ENOBUFS:
				strDetails << "ENOBUFS";
				break;
			case EINPROGRESS:
				strDetails << "EINPROGRESS";
				break;
			case EALREADY:
				strDetails << "EALREADY";
				break;
			case EILSEQ:
				strDetails << "EILSEQ";
				break;
			case ENOMSG:
				strDetails << "ENOMSG";
				break;
			case ESTALE:
				strDetails << "ESTALE";
				break;
			case EOVERFLOW:
				strDetails << "EOVERFLOW";
				break;
			case EMSGSIZE:
				strDetails << "EMSGSIZE";
				break;
			case EOPNOTSUPP:
				strDetails << "EOPNOTSUPP";
				break;
			case ENOTSOCK:
				strDetails << "ENOTSOCK";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_PRINT_ERROR_BASE) //Mail Error
	{
		switch (inStatus)
		{
			case B_MAIL_NO_DAEMON:
				strDetails << "B_MAIL_NO_DAEMON";
				break;
			case B_MAIL_UNKNOWN_USER:
				strDetails << "B_MAIL_UNKNOWN_USER";
				break;
			case B_MAIL_WRONG_PASSWORD:
				strDetails << "B_MAIL_WRONG_PASSWORD";
				break;
			case B_MAIL_UNKNOWN_HOST:
				strDetails << "B_MAIL_UNKNOWN_HOST";
				break;
			case B_MAIL_ACCESS_ERROR:
				strDetails << "B_MAIL_ACCESS_ERROR";
				break;
			case B_MAIL_UNKNOWN_FIELD:
				strDetails << "B_MAIL_UNKNOWN_FIELD";
				break;
			case B_MAIL_NO_RECIPIENT:
				strDetails << "B_MAIL_NO_RECIPIENT";
				break;
			case B_MAIL_INVALID_MAIL:
				strDetails << "B_MAIL_INVALID_MAIL";
				break;
			default:
				break;
		}
	}
	else if (inStatus < B_DEVICE_ERROR_BASE) //Print Error
	{
		switch (inStatus)
		{
			case B_NO_PRINT_SERVER:
				strDetails << "B_NO_PRINT_SERVER";
				break;
			default:
				break;
		}
	}
	else if (inStatus <= B_ERRORS_END)  //Device Error
	{
		switch (inStatus)
		{
			case B_DEV_INVALID_IOCTL:
				strDetails << "B_DEV_INVALID_IOCTL";
				break;
			case B_DEV_NO_MEMORY:
				strDetails << "B_DEV_NO_MEMORY";
				break;
			case B_DEV_BAD_DRIVE_NUM:
				strDetails << "B_DEV_BAD_DRIVE_NUM";
				break;
			case B_DEV_NO_MEDIA:
				strDetails << "B_DEV_NO_MEDIA";
				break;
			case B_DEV_UNREADABLE:
				strDetails << "B_DEV_UNREADABLE";
				break;
			case B_DEV_FORMAT_ERROR:
				strDetails << "B_DEV_FORMAT_ERROR";
				break;
			case B_DEV_TIMEOUT:
				strDetails << "B_DEV_TIMEOUT";
				break;
			case B_DEV_RECALIBRATE_ERROR:
				strDetails << "B_DEV_RECALIBRATE_ERROR";
				break;
			case B_DEV_SEEK_ERROR:
				strDetails << "B_DEV_SEEK_ERROR";
				break;
			case B_DEV_ID_ERROR:
				strDetails << "B_DEV_ID_ERROR";
				break;
			case B_DEV_READ_ERROR:
				strDetails << "B_DEV_READ_ERROR";
				break;
			case B_DEV_WRITE_ERROR:
				strDetails << "B_DEV_WRITE_ERROR";
				break;
			case B_DEV_NOT_READY:
				strDetails << "B_DEV_NOT_READY";
				break;
			case B_DEV_MEDIA_CHANGED:
				strDetails << "B_DEV_MEDIA_CHANGED";
				break;
			case B_DEV_MEDIA_CHANGE_REQUESTED:
				strDetails << "B_DEV_MEDIA_CHANGE_REQUESTED";
				break;
			case B_DEV_RESOURCE_CONFLICT:
				strDetails << "B_DEV_RESOURCE_CONFLICT";
				break;
			case B_DEV_CONFIGURATION_ERROR:
				strDetails << "B_DEV_CONFIGURATION_ERROR";
				break;
			case B_DEV_DISABLED_BY_USER:
				strDetails << "B_DEV_DISABLED_BY_USER";
				break;
			case B_DEV_DOOR_OPEN:
				strDetails << "B_DEV_DOOR_OPEN";
				break;
			default:
				break;
		}
	}
	else
	{
		switch (inStatus)
		{
			case B_ERROR:
				strDetails << "B_ERROR";
				break;
			case B_OK:
				strDetails << "B_OK";
				break;
			default:
				strDetails << "Developer-defined status code";
				break;
		}
	}

	char * pChar (strerror (inStatus));
	if (NULL != pChar)
	{
		strDetails << ", " << pChar;
	}

	strDetails << "\n";
}


/***************************************************************
***************************************************************/
void
Inspect_BGLView
	(
	BString & strDetails
,	BGLView * inValue
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
	strDetails << tabindent << pDescription << "[BGLView object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "not coded in this release!" << g_pNewline;
		//if (DoBaseClasses)
		//{
		//	strDetails << tabindent << g_pNewline;
		//	Inspect_BFlattenable (strDetails, (BFlattenable *) inValue, inIndent, "  + BPropertyInfo baseclass ");
		//}
	}
	else
	{
		strDetails << tabindent << "The BGLView was NULL\n";
	}
}


