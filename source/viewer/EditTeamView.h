#ifndef _EDITTEAMVIEW_H
#define _EDITTEAMVIEW_H

#ifndef _EDITVIEW_H
#include "EditView.h"
#endif

class BWindow;
class BView;
class BMenuField;
class BPopUpMenu;
class TeamItem;
class BetterScrollView;
class ColumnListView;
class Slider;

class EditTeamView : public EditView
{
	public:
							EditTeamView (BRect, BMessage *);
		virtual				~EditTeamView (void);
		virtual void		MessageReceived (BMessage *);
		virtual void		AllAttached (void);
		virtual void		AttachedToWindow (void);
		virtual void		DetachedFromWindow (void);
		virtual void		Draw (BRect);
	public:
		virtual bool		Save (void);
		static EditTeamView *	Create (BRect, BMessage *);
	private:
		bool				PopulateData (BMessage *);
	private:
		EditTeamView (const EditTeamView &);
		EditTeamView & operator= (EditTeamView &);
	private:
		//BWindow *			m_targetwnd;
		//BView *				m_targetview;
		Slider *			m_slider;
		BetterScrollView *	m_bsv;
		ColumnListView *	m_ColumnListView;
		uint32				m_CategoryMask[10];
		int32				m_QueueLength;
		//TeamItem *			m_TI;
		BButton *			m_OK;
		uint32				m_CurCat;
		BMenuField *		m_menufld;
		BPopUpMenu *		m_popupmenu;
		//int32				m_Value;
		//int32				m_minValue;
		//int32				m_maxValue;
};

#endif



