//Column list view header file


#ifndef _CLV_COLUMN_LIST_VIEW_H_
#define _CLV_COLUMN_LIST_VIEW_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _LIST_VIEW_H
#include <ListView.h>
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
#ifndef _SGB_COLORS_H_
#include "Colors.h"
#endif

#ifndef _CLV_COLUMN_H_
#include "CLVColumn.h"
#endif

class CLVListItem;
class CLVColumnLabelView;
class CLVFillerView;
class BetterScrollView;
//class CLVContainerView;
//class BScrollView;
//#include "PrefilledBitmap.h"
//#include "BetterScrollView.h"


//******************************************************************************************************
//**** CONSTANTS AND TYPE DEFINITIONS
//******************************************************************************************************
typedef int (*CLVCompareFuncPtr)(const CLVListItem* item1, const CLVListItem* item2, int32 sort_key);


//******************************************************************************************************
//**** ColumnListView CLASS DECLARATION
//******************************************************************************************************
class ColumnListView : public BListView
{
	public:
		//Constructor and destructor
		ColumnListView (BRect,
						rgb_color,
						//Used to get back a pointer to the container
						BetterScrollView **,	//Used to get back a pointer to the container
															//view that will hold the ColumnListView, the
															//the CLVColumnLabelView, and the scrollbars.
															//If no scroll bars or border are asked for,
															//this will act like a plain BView container.
						const char * Name = NULL,
						uint32 ResizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
						uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE,
						list_view_type Type = B_SINGLE_SELECTION_LIST,
						bool hierarchical = false,
						bool horizontal = true,					//Which scroll bars should I add, if any
						bool vertical = true,
						//bool scroll_view_corner = true,
						border_style border = B_NO_BORDER,		//What type of border to add, if any
						const BFont* LabelFont = be_plain_font);
		virtual ~ColumnListView (void);

		//Archival stuff
			/*** Not implemented yet
		ColumnListView(BMessage* archive);
		static ColumnListView* Instantiate(BMessage* data);
		virtual	status_t Archive(BMessage* data, bool deep = true) const;
			***/

		//Column setup functions
		virtual bool AddColumn (CLVColumn *);			//Note that a column may only be added to
															//one ColumnListView at a time, and may not
															//be added more than once to the same
															//ColumnListView without removing it
															//inbetween
		virtual bool AddColumnList (BList *);
		virtual bool RemoveColumn (CLVColumn *);
		virtual bool RemoveColumns (CLVColumn *, int32);	//Finds Column in ColumnList
																	//and removes Count columns and
																	//their data from the view
																	//and its items
		int32 CountColumns () const;
		int32 IndexOfColumn (CLVColumn *) const;
		CLVColumn* ColumnAt (int32) const;
		virtual bool SetDisplayOrder (const int32 *);
			//Sets the display order: each int32 in the Order list specifies the column index of the
			//next column to display.  Note that this DOES NOT get called if the user drags a
			//column, so overriding it will not inform you of user changes.  If you need that info,
			//override DisplayOrderChanged instead.  Also note that SetDisplayOrder does call
			//DisplayOrderChanged(false).
		virtual void ColumnWidthChanged (int32, float);
		virtual void DisplayOrderChanged (const int32 *);
			//Override this if you want to find out when the display order changed.
		int32* DisplayOrder (void) const;	//Gets the display order in the same format as that used by
										//SetDisplayOrder.  The returned array belongs to the caller and
										//must be delete[]'d when done with it.
		virtual void SetSortKey (int32);
			//Set it to -1 to remove the sort key.
		virtual void AddSortKey (int32);
		void ReverseSortMode (int32);
		virtual void SetSortMode (int32, CLVSortMode);
			//Override this to filter the modes
		int32 Sorting (int32 *, CLVSortMode *) const;
			//Returns the number of used sort keys, and fills the provided arrays with the sort keys
			//by column index and sort modes, in priority order.  The pointers should point to an array 
			//int32 SortKeys[n], and an array CLVSortMode SortModes[n] where n is the number of sortable
			//columns in the ColumnListView.  Note: sorting will only occur if the key column is shown.
		void SetSorting (int32, int32 *, CLVSortMode *);
			//Sets the sorting parameters using the same format returned by Sorting
		virtual void SortingChanged (void);	//Override this to detect changes to the sorting keys or modes.

		//BView overrides
		virtual void FrameResized (float, float);
 		virtual void ScrollTo (BPoint);
 		//virtual void MouseDown (BPoint);
 
		//List functions
		//virtual bool AddUnder (BListItem *, BListItem *);
		//virtual bool AddItem (BListItem *, int32);
		//virtual bool AddItem (BListItem *);
		//virtual bool AddList (BList *);			//This must be a BList of CLVListItem*'s, NOT BListItem*'s
		//virtual bool AddList (BList *, int32);	//This must be a BList of CLVListItem*'s, NOT BListItem*'s
		//virtual bool RemoveItem (BListItem *);
		//virtual BListItem* RemoveItem (int32);			//Actually returns CLVListItem
		//virtual bool RemoveItems (int32, int32);
		virtual void MakeEmpty (void);
		CLVListItem* FullListItemAt (int32)  const;
		int32 FullListIndexOf (const CLVListItem *) const;
		int32 FullListIndexOf (BPoint) const;
		CLVListItem* FullListFirstItem (void) const;
		CLVListItem* FullListLastItem (void) const;
		bool FullListHasItem (const CLVListItem *) const;
		int32 FullListCountItems (void) const;
		bool FullListIsEmpty (void) const;
		int32 FullListCurrentSelection (int32 index = 0) const;
		void FullListDoForEach (bool (*func)(CLVListItem *));
		void FullListDoForEach (bool (*func)(CLVListItem*, void*), void* arg2);
		//CLVListItem* Superitem (const CLVListItem *) const;
		//int32 FullListNumberOfSubitems (const CLVListItem *) const;
		//virtual void Expand (CLVListItem *);
		//virtual void Collapse (CLVListItem *);
		//bool IsExpanded (int32) const;
		void SetSortFunction (CLVCompareFuncPtr);
		void SortItems (void);

	private:
		friend class CLVMainView;
		friend class CLVColumn;
		friend class CLVColumnLabelView;
		friend class CLVListItem;

		void UpdateColumnSizesDataRectSizeScrollBars (bool scrolling_allowed = true);
		void ColumnsChanged (void);
		void CreateContainer (bool, bool, border_style, uint32, uint32, rgb_color);
		void SortListArray (CLVListItem **, int32);
		void MakeEmptyPrivate (void);
		bool AddListPrivate (BList *, int32);
		bool AddItemPrivate (CLVListItem *, int32);
		void SortFullListSegment (int32, int32, BList *);
		BList* SortItemsInThisLevel (int32);
		static int PlainBListSortFunc (BListItem **, BListItem **);
		static int HierarchicalBListSortFunc (BListItem **, BListItem **);
		void AssertWindowLocked (void) const;

		CLVColumnLabelView *	fColumnLabelView;
		BetterScrollView *		fScrollView;
		//CLVContainerView* fScrollView;
		//BScrollView *			fScrollView;
		bool					fHierarchical;
		BList					fColumnList;
		BList					fColumnDisplayList;
		BList					fSortKeyList;		//List contains CLVColumn pointers
		BList					fFullItemList;
		BBitmap					fRightArrow;
		BBitmap					fDownArrow;
//		PrefilledBitmap			fRightArrow;
//		PrefilledBitmap			fDownArrow;
		int32					fExpanderColumn;
		CLVCompareFuncPtr		fCompare;
};


#endif


