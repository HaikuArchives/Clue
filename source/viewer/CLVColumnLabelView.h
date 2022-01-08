//CLVColumnLabelView class header file


#ifndef _CLV_COLUMN_LABEL_VIEW_H_
#define _CLV_COLUMN_LABEL_VIEW_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _BE_LIST_H
#include <List.h>
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
class ColumnListView;
class CLVColumn;


//******************************************************************************************************
//**** CLASS AND STRUCTURE DECLARATIONS, ASSOCIATED CONSTANTS AND STATIC FUNCTIONS
//******************************************************************************************************
struct CLVDragGroup {
	int32 GroupStartDispListIndex;		//Indices in the column display list where this group starts
	int32 GroupStopDispListIndex;		//and finishes
	float GroupBegin, GroupEnd;			//-1.0 if whole group is hidden
	CLVColumn* LastColumnShown;
	bool AllLockBeginning;
	bool AllLockEnd;
	bool Shown;							//False if none of the columns in this group are shown
	uint32 Flags;						//Uses CLV_NOT_MOVABLE, CLV_LOCK_AT_BEGINNING, CLV_LOCK_AT_END
};


class CLVColumnLabelView : public BView {
public:
	//Constructor and destructor
	CLVColumnLabelView(BRect, ColumnListView*, const BFont*);
	virtual ~CLVColumnLabelView();

	//BView overrides
	virtual void Draw(BRect);
	virtual void MouseDown(BPoint);
	virtual void MouseMoved(BPoint, uint32, const BMessage*);
	virtual void MouseUp(BPoint);
	virtual void MessageReceived(BMessage*);

private:
	friend class ColumnListView;
	friend class CLVColumn;

	float fFontAscent;
	BList* fDisplayList;

	//Column select and drag stuff
	CLVColumn* fColumnClicked;
	BPoint fPreviousMousePos;
	BPoint fMouseClickedPos;
	bool fColumnDragging;
	bool fColumnResizing;
	BList fDragGroups;					//Groups of CLVColumns that must drag together
	int32 fDragGroup;					//Index into DragGroups of the group being dragged by user
	CLVDragGroup* fTheDragGroup;
	CLVDragGroup* fTheShownGroupBefore;
	CLVDragGroup* fTheShownGroupAfter;
	int32 fSnapGroupBefore;  //Index into DragGroups of TheShownGroupBefore and
	int32 fSnapGroupAfter;				//TheShownGroupAfter, if the group the user is dragging is
	//allowed to snap there, otherwise -1
	float fDragBoxMouseHoldOffset;
	float fResizeMouseHoldOffset;
	float fDragBoxWidth;				//Can include multiple columns; depends on CLV_LOCK_WITH_RIGHT
	float fPrevDragOutlineLeft;
	float fPrevDragOutlineRight;
	float fSnapMin;
	float fSnapMax;			//-1.0 indicates the column can't snap in the given direction
	ColumnListView* fParent;
	bool m_WatchMouse;

	//Private functions
	void ShiftDragGroup(int32);
	void UpdateDragGroups(void);
	void SetSnapMinMax(void);
};


#endif
