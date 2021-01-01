/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

class BWindow;
class BView;
class BMenuField;
class BPopUpMenu;
class TeamItem;
class BetterScrollView;
class ColumnListView;
class Slider;

class TeamPropertyView : public BView {
public:
	TeamPropertyView(BRect&, const BWindow*, const BView*, const TeamItem*);
	virtual				~TeamPropertyView(void);
	virtual void		AllAttached(void);
	virtual void		MessageReceived(BMessage*);
public:
	void				RefreshList(void);
private:
	TeamPropertyView(const TeamPropertyView&);
	TeamPropertyView& operator= (TeamPropertyView&);
private:
	void				CategoryChanged(BMessage*);
	void				SelectUnselect(bool, bool);
private:
	BWindow* 			m_targetwnd;
	BView* 				m_targetview;
	Slider* 			m_slider;
	BetterScrollView* 	m_bsv;
	ColumnListView* 	m_ColumnListView;
	TeamItem* 			m_TI;
	BButton* 			m_OK;
	uint32				m_CurCat;
	BMenuField* 		m_menufld;
	BPopUpMenu* 		m_popupmenu;
};

#endif



