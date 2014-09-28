//CLVListItem header file


#ifndef _TEAMITEM_H_
#define _TEAMITEM_H_


//******************************************************************************************************
//**** SYSTEM HEADER FILES
//******************************************************************************************************
#ifndef _BE_LIST_H
#include <List.h>
#endif

#ifndef _CLV_LIST_ITEM_H_
#include "CLVListItem.h"
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES AND CLASS NAME DECLARATIONS
//******************************************************************************************************
class BBitmap;
class BTab;
class BView;
class ClueItem;
class FingerprintCLV;


//******************************************************************************************************
//**** CLVListItem CLASS DECLARATION
//******************************************************************************************************
class TeamItem : public CLVListItem
{
	public:
		//Constructor and destructor
//							CTeamItem (uint32, uint32, team_id, char *, BView *, BBitmap *, char *, ColumnListView *);
							TeamItem (team_id, BView *, FingerprintCLV *);
							TeamItem (BMessage *, BView *, FingerprintCLV *, int32);
							TeamItem (const TeamItem &, bool = true);
		virtual				~TeamItem (void);

		virtual	status_t	Archive (BMessage *, bool deep = true) const;
		
		virtual void		DrawItemColumn (BView *, BRect, int32, bool);
								//column_index (0-N) is based on the order in which the columns were added
								//to the ColumnListView, not the display order.  An index of -1 indicates
								//that the program needs to draw a blank area beyond the last column.  The
								//main purpose is to allow the highlighting bar to continue all the way to
								//the end of the ColumnListView, even after the end of the last column.
		virtual void		Update (BView *, const BFont *);
	public:
		void				SetFilter (uint32 flags);
		uint32				Filter (void);
		void				Copy (BString &, uint32);
		void				RefreshList (void);
		void				ClearList (void);
		void				AddClue (ClueItem *);
		void				AdjustQueue (void);
		int32				AddRef (void);
		int32				Release (void);
		bool				SetRunning (bool);
		bool				IsRunning (void);
	private:
							TeamItem & operator= (TeamItem &);
	public:
		uint32				m_CategoryMask[10];
		int32				m_QueueLength;
		team_id				m_TeamID;
//		char *				m_TeamName;
		bool				m_TabVisible;
		BTab *				m_tab;
		BView *				m_view;
		BBitmap *			m_bitmap;
		char				m_title[B_FILE_NAME_LENGTH];
		FingerprintCLV *	m_CLV;
		BList				m_ItemList;
		int32				m_RefCount;
		bool				m_IsRunning;
	public:
		static const int32	ARCHIVE_FORMAT;
};


#endif // _TEAMITEM_H_
