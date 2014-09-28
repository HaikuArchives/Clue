//#define DEBUG 1

#include "ClueBuild.h"

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _GRAPHICS_DEFS_H
#include <GraphicsDefs.h>
#endif

#ifndef _PREFERENCE_ITEM_H
#include "PreferenceItem.h"
#endif

PreferenceItem :: PreferenceItem
	(
	const char * Name
,	const char * Description
,	uint32 outlineLevel
,	bool expanded
	)
:	BStringItem (Description, outlineLevel, expanded)
,	m_Message ('0000')
,	m_Name (Name)
,	m_Dirty (false)
{
}

PreferenceItem :: ~PreferenceItem
	(
	void
	)
{
}

const char *
PreferenceItem :: GetName
	(
	void
	)
{
	return m_Name.String ();
}

void
PreferenceItem :: SetDirty
	(
	bool newVal
	)
{
	m_Dirty = newVal;
}

bool
PreferenceItem :: IsDirty
	(
	void
	)
{
	return m_Dirty;
}

void
PreferenceItem :: CopyMessage
	(
	BMessage * inMsg
	)
{
	m_Message.what = inMsg->what;

	bool valBool;
//	int8 valInt8;
//	int16 valInt16;
	int32 valInt32;
	int64 valInt64;
	float valFloat;
	double valDouble;
	BString valBString;
//	BPoint valBPoint;
//	BRect valBRect;
//	entry_ref valEntryRef;
//	BMessage valBMessage;
//	BMessenger valBMessenger;
//	void * valPointer;
//	BFlattenable * valBFlattenable;

#ifdef CLUE_ON_ZETA_HACK
	char const * name (NULL);
#else	
	char * name (NULL);
#endif
	uint32 type (0);
	int32 count (0);

	//for now, only copy things we know how to deal with!!!
	for (int32 i (0); inMsg->GetInfo (B_ANY_TYPE, i, &name, &type, &count) == B_OK; i++)
	{
		switch (type)
		{
			case B_BOOL_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_BOOL_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindBool (name, count, &valBool);
					m_Message.AddBool (name, valBool);
				}
				break;
			case B_DOUBLE_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_DOUBLE_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindDouble (name, count, &valDouble);
					m_Message.AddDouble (name, valDouble);
				}
				break;
			case B_FLOAT_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_FLOAT_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindFloat (name, count, &valFloat);
					m_Message.AddFloat (name, valFloat);
				}
				break;
			case B_INT64_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_INT64_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindInt64 (name, count, &valInt64);
					m_Message.AddInt64 (name, valInt64);
				}
				break;
			case B_INT32_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_INT32_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindInt32 (name, count, &valInt32);
					m_Message.AddInt32 (name, valInt32);
				}
				break;
			case B_STRING_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_STRING_TYPE\n"));
				while (count-- > 0)
				{
					inMsg->FindString (name, count, &valBString);
					m_Message.AddString (name, valBString);
				}
				break;
			case B_RGB_COLOR_TYPE:
				PRINT (("\nPreferenceItem::CopyMessage: B_RGB_COLOR_TYPE\n"));
				while (count-- > 0)
				{
					rgb_color * pColor (NULL);
					ssize_t numBytes (0);

					if (inMsg->FindData (name, B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes) == B_OK)
					{
						if (sizeof(rgb_color) == numBytes)
						{
							PRINT (("   AddData named'%s', color: red=%i, green=%i, blue=%i\n", name, pColor->red, pColor->green, pColor->blue));
							m_Message.AddData (name, B_RGB_COLOR_TYPE, pColor, sizeof(rgb_color));
#ifdef DEBUG
							if (B_OK == m_Message.FindData (name, B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
							{
								PRINT (("   after AddData: red=%i, green=%i, blue=%i\n\n", pColor->red, pColor->green, pColor->blue));
							}
#endif
						}
					}
				}
				break;
			default:
				break;
		}
	}
}


BMessage *
PreferenceItem :: GetMessage (void)
{
	ssize_t numBytes (0);
	rgb_color * pColor (NULL);

	if (B_OK == m_Message.FindData ("value", B_RGB_COLOR_TYPE, (const void **) &pColor, &numBytes))
	{
	PRINT (("PreferenceItem:: GetMessage: red=%i, green=%i, blue=%i\n", pColor->red, pColor->green, pColor->blue));
	}

	return &m_Message;
}


