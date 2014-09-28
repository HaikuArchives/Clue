#ifndef _OBJECTFILTER_ITEM_H
#define _OBJECTFILTER_ITEM_H

#ifndef __BSTRING__
#include "String.h"
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

class ObjectFilterItem : public BListItem
{
	public:
						ObjectFilterItem(const char *, bool IsLeafNode = false, uint32 inIndex = 0, uint32 InMask = 0, bool ControlsSubItems = false, uint32 outlineLevel = 0, bool expanded = false);
						~ObjectFilterItem (void);
	public:
		void			DrawItem (BView *, BRect, bool complete = false);
	public:
		void			SetChecked (bool);
		bool			IsChecked (void);
		bool			ToggleChecked (void);
		bool			IsLeafNode (void);
		bool			ControlsSubItems (void);
		void			SetGrayed (bool);
	private:
						ObjectFilterItem (const ObjectFilterItem &);
						ObjectFilterItem & operator= (ObjectFilterItem &);
	private:
		uint32			m_Index;
		uint32			m_Mask;
//		bool			m_Checked; //will be replaced by the CAM value!!!
		BString			m_Text;
		bool			m_IsLeafNode;
		bool			m_GrayedOut;
		bool			m_ControlsSubItems;
};

#endif //_OBJECTFILTER_ITEM_H


