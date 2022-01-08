/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef TEAMTAB_H
#define TEAMTAB_H

/***************************************************************
include headers
***************************************************************/
#ifndef _TAB_VIEW_H
#include <TabView.h>
#endif

class BBitmap;

/***************************************************************
class declaration
***************************************************************/
class TeamTab : public BTab {
public:
	TeamTab(BBitmap*, BView* tabView = NULL);
	virtual void	DrawTab(BView*, BRect, tab_position, bool full = true);
	virtual void	DrawLabel(BView*, BRect);
	virtual void	DrawFocusMark(BView*, BRect);
private:
	TeamTab(const TeamTab&);
	TeamTab& operator= (TeamTab&);
protected:
	BBitmap* 		m_bitmap;
};

#endif //TEAMTAB_H



