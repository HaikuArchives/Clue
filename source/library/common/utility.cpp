#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif


/***************************************************************
***************************************************************/
void
GetHexString
	(
	char * inoutBuffer
,	intptr_t inValue
	)
{
	//TODO decrease width for 32 bit pointers
	sprintf (inoutBuffer, "%#018" PRIxPTR, inValue);
}


/***************************************************************
***************************************************************/
void
HexDump
	(
	const void * inBuffer
,	long inLength
,	BString & inStr
,	BString & indent
,	int32 BytesPerLine = 16
	)
{
	long length (inLength);
	long offset (0);
	unsigned char * buffer ((unsigned char *) inBuffer);
	char outbuf[80];
	int32 loops (0);

	for (offset = 0; ++loops < 20; offset += BytesPerLine, buffer += BytesPerLine)
	{
		long remain (length);
		int index (0);

		sprintf (outbuf, "      0x%06x: ", (int) offset);
		inStr << indent << outbuf;

		for (index = 0; index < BytesPerLine; index++)
		{

			if (remain-- > 0)
			{
				sprintf (outbuf, "%02x%c", buffer[index], remain > 0 ? ',' : ' ');
				inStr << outbuf;
			}
			else
			{
				inStr << "   ";
			}
		}

		remain = length;
		inStr << " |";

		for (index = 0; index < BytesPerLine; index++)
		{

			if (remain-- > 0)
			{
				sprintf (outbuf, "%c", buffer[index] > ' ' ? buffer[index] : '.');
				inStr << outbuf;
			}
			else
			{
				inStr << " ";
			}
		}

		inStr << "|\n";

		length -= BytesPerLine;
		if (length <= 0)
			break;
	}

	if (length > 0)
	{
		inStr << indent << "      [" << length << " bytes remaining of " << inLength << "]\n";
	}
}
