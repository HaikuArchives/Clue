//CLVListItem header file


#ifndef _CLV_LIST_ITEM_H_
#define _CLV_LIST_ITEM_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _RECT_H
#include <Rect.h>
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
class ColumnListView;


//******************************************************************************************************
//**** CLVListItem CLASS DECLARATION
//******************************************************************************************************
class CLVListItem : public BListItem
{
	public:
		//Constructor and destructor
		CLVListItem (uint32 level = 0, bool expanded = true);
		virtual ~CLVListItem (void);
		
		virtual void DrawItemColumn (BView *, BRect, int32, bool) = 0;
								//column_index (0-N) is based on the order in which the columns were added
								//to the ColumnListView, not the display order.  An index of -1 indicates
								//that the program needs to draw a blank area beyond the last column.  The
								//main purpose is to allow the highlighting bar to continue all the way to
								//the end of the ColumnListView, even after the end of the last column.
		virtual void DrawItem (BView *, BRect, bool);
								//In general, you don't need or want to override DrawItem().
		BRect ItemColumnFrame (int32, ColumnListView *);
		virtual void Update (BView *, const BFont *);
		virtual void ColumnWidthChanged (int32, float, ColumnListView *);
		virtual void FrameChanged (int32, BRect, ColumnListView *);

	private:
						CLVListItem (const CLVListItem &);
						CLVListItem & operator= (CLVListItem &);
	public:
		friend class ColumnListView;

		BRect				fExpanderButtonRect;
		BRect				fExpanderColumnRect;
		BList *				fSortingContextBList;
		ColumnListView *	fSortingContextCLV;
		float				fTextOffset;
};


#endif


