/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef BACKVIEW_H
#define BACKVIEW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif

/***************************************************************
forward class declarations
***************************************************************/
class BButton;
class BCheckBox;
class BFile;
class BListView;
class BMenuField;
class BMessageRunner;
class BPrintJob;
class BStringView;
class AnimatedView;
class BetterScrollView;
class SplitterView;
class ClueTabView;
class ColumnListView;
class TeamItem;

/***************************************************************
class definition
***************************************************************/
class BackView
:	public BView
{
	public:
							BackView (BRect);
							BackView (BRect, BMessage *);
		virtual				~BackView ();
		virtual void		AllAttached (void);
		virtual void		FrameResized (float, float);
		virtual void		MessageReceived (BMessage *);
		virtual	void		MouseMoved (BPoint, uint32, const BMessage *);
		virtual void		MouseUp (BPoint);
		void				ResizeBy (float, float);
		void				ResizeTo (float, float);
	public:
		void				Listen (bool);
		//void				Import (BMessage *);
		void				Export (BFile *);
	private:
							BackView (const BackView &);
							BackView & operator= (BackView &);
	private:
		void				InitCommon (void);
		TeamItem *			CreateNewTeamItem (team_id);
		TeamItem *			CreateNewTeamItem (BMessage *, int32);
		void				ProcessIncomingData (void);
		TeamItem *			FindTeamItem (team_id);
		void				DeleteTeam (void);
		void				UpdateTeamProperties (BMessage *);
		void				TeamInvocated (BMessage *);
		void				SplitterStart (void);
		void				TeamProperties (void);
		void				ClearClueList (BMessage *);
		void				OnPrint (void);
		bool				PrintPage (int32);
		void				TeamsInRoster (void);
		void				Activate (void);
		void				AdjustViews (void);
	private:
		BMenuField *		m_mfView;
		ClueTabView *		m_tvTabs;
		//BTabView *			m_tvTabs;
		BListView *			m_lvTeams;
		TeamItem *			m_TIcached; //used to speed up Processing
		SplitterView *		m_pSplitterView;
		thread_id			m_PortThreadID;
		BMessageRunner * 	m_runner;
		BMessageRunner * 	m_checkrosterrunner;
		ColumnListView *	m_ColumnListView;
		//uint32				m_GlobalFilterMask;
		BStringView *		m_teamslabel;
		BetterScrollView *	m_BSV;
		BMessage *			m_PrintSettings;
		BPrintJob *			m_PrintJob;
		BPoint				m_maxLR;	//x is left, y is right!!!
		BRect				m_cachedRects[3];
		float				m_SplitPercentage;
		bool				m_splitting;
		bool				m_IsLive;
};

#endif //BACKVIEW_H

