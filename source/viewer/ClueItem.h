//******************************************************************************************************
//**** A Clue Item is the used to keep all the information on an event.
//******************************************************************************************************

#ifndef _CLUEITEM_H_
#define _CLUEITEM_H_

//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#include <inttypes.h>

//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
#ifndef CLUE_H
#define CLUE
#define BUILD_CLUE_APPLICATION
#include "Clue.h"
#endif

#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif

class BBitmap;
class BTab;
class BView;


//******************************************************************************************************
//**** CLVListItem CLASS DECLARATION
//******************************************************************************************************
class ClueItem : public CLVListItem {
public:
	//Constructor and destructor
	ClueItem(const FingerPrint*,	const BString*, const BString*, const BString*,	const BString*, const intptr_t);
//							ClueItem (const FingerPrint *);
	ClueItem(BMessage*, int32);
	virtual				~ClueItem(void);

	virtual void		DrawItemColumn(BView*, BRect, int32, bool);
	//column_index (0-N) is based on the order in which the columns were added
	//to the ColumnListView, not the display order.  An index of -1 indicates
	//that the program needs to draw a blank area beyond the last column.  The
	//main purpose is to allow the highlighting bar to continue all the way to
	//the end of the ColumnListView, even after the end of the last column.
	virtual void		Update(BView*, const BFont*);
public:
	//void				Switch (BView *);
	void				DisplayDetail(BTextView*);
	void				Copy(BString&, uint32, uint32);
	status_t			Archive(BMessage*) const;
//		int32				AddRef (void);
//		int32				Release (void);
private:
	ClueItem(const ClueItem&);
	ClueItem& operator= (ClueItem&);
public:
	ClueCategory	m_CAT;
	ClueEvent		m_EVT;
	bigtime_t		m_Time;
	thread_id		m_ThreadID;
	team_id			m_TeamID;
	uint32			m_Line;
	uint32			m_Sequence;
	//uint32			m_DetailLineCount;
	intptr_t		m_Inst;
	char* 			m_File;
	char* 			m_Method;
	char* 			m_Class;
	char* 			m_Description;
	char* 			m_Detail;
	BBitmap* 		m_CategoryBmp;
	BBitmap* 		m_EventBmp;
	//char			m_bmpIndexCAT; //Category
	//char			m_bmpIndexEVT; //Event
	bool			m_InList;
	//bool			m_Expanded;
//		int32			m_RefCount;
public:
	static const int32	ARCHIVE_FORMAT;
};

//******************************************************************************************************
#endif // _CLUEITEM_H_
