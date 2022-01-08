/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef STATUSBARVIEW_H
#define STATUSBARVIEW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _VIEW_H
#include <View.h>
#endif


/***************************************************************
forward class declarations
***************************************************************/
class BMessageRunner;


/***************************************************************
class definition
***************************************************************/
class StatusBarView
	:	public BView {
public:
	StatusBarView(BRect);
	~StatusBarView(void);
	virtual void		AllAttached(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		Draw(BRect);
private:
	StatusBarView(const StatusBarView&);
	StatusBarView& operator= (StatusBarView&);
public:
	//void				SetPaneText (int32);
	void				SetPaneText(const char*);
private:
	char* 				m_text;
	BMessageRunner* 	m_runner;
};

#endif //STATUSBARVIEW_H

