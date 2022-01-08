//CLVListItem header file


#ifndef DRAGMESSAGEITEM_H_
#define DRAGMESSAGEITEM_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _BE_LIST_H
#include <List.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
class BMessage;

//******************************************************************************************************
//**** CLVListItem CLASS DECLARATION
//******************************************************************************************************
class DragMessageItem : public CLVListItem {
public:
	//Constructor and destructor
//							CTeamItem (uint32, uint32, team_id, char *, BView *, BBitmap *, char *, ColumnListView *);
	DragMessageItem(const BMessage*, const char*, type_code, int32);
	virtual				~DragMessageItem(void);
	virtual void		DrawItemColumn(BView*, BRect, int32, bool);
	//column_index (0-N) is based on the order in which the columns were added
	//to the ColumnListView, not the display order.  An index of -1 indicates
	//that the program needs to draw a blank area beyond the last column.  The
	//main purpose is to allow the highlighting bar to continue all the way to
	//the end of the ColumnListView, even after the end of the last column.
	virtual void		Update(BView*, const BFont*);
private:
	DragMessageItem& operator= (DragMessageItem&);
	DragMessageItem(const DragMessageItem&);
private:
	BString				m_name;
	type_code			m_type;
	int32				m_count;
	const BMessage* 	m_message;
};


#endif // DRAGMESSAGEITEM_H_
