//CLVListItem header file


#ifndef _CLUE_PROPERTYITEM_H_
#define _CLUE_PROPERTYITEM_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif

const uint32 CT_CLASS_BIRTH_INDEX	= 0;
const uint32 CT_CLASS_DEATH_INDEX	= 1;
const uint32 CT_METHOD_ENTER_INDEX	= 2;
const uint32 CT_METHOD_EXIT_INDEX	= 3;
const uint32 CT_OK_INDEX			= 4;
const uint32 CT_INFO_INDEX			= 5;
const uint32 CT_WARNING_INDEX		= 6;
const uint32 CT_ERROR_INDEX			= 7;
const uint32 CT_AUDIT_SUCCESS_INDEX	= 8;
const uint32 CT_AUDIT_FAILURE_INDEX	= 9;
const uint32 CT_TIMER_INDEX			= 10;
const uint32 CT_OBJECT_INDEX		= 11;


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
class BBitmap;
class BTab;
class BView;


//******************************************************************************************************
//**** CLVListItem CLASS DECLARATION
//******************************************************************************************************
class PropertyItem : public CLVListItem {
public:
	//Constructor and destructor
	PropertyItem(uint32);

	virtual void		DrawItemColumn(BView*, BRect, int32, bool);
	//column_index (0-N) is based on the order in which the columns were added
	//to the ColumnListView, not the display order.  An index of -1 indicates
	//that the program needs to draw a blank area beyond the last column.  The
	//main purpose is to allow the highlighting bar to continue all the way to
	//the end of the ColumnListView, even after the end of the last column.
	virtual void		Update(BView*, const BFont*);

public:
	void				SetFilter(uint32 flags);
	uint32				Filter(void);
private:
	PropertyItem(const PropertyItem&);
	PropertyItem& operator= (PropertyItem&);
public:
	uint32				m_ClueInfoIndex;
	ClueEvent			m_Event;
	bool				m_selected;
};


#endif // _CLUE_PROPERTYITEM_H_
