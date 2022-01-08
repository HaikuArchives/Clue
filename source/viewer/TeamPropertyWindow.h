/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef PROPERTYWINDOW_H
#define PROPERTYWINDOW_H

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _TEAMITEM_H_
#include "TeamItem.h"
#endif


class TeamPropertyWindow : public BWindow {
public:
	TeamPropertyWindow(const BWindow*, const BView*, const TeamItem*);
private:
	TeamPropertyWindow(const TeamPropertyWindow&);
	TeamPropertyWindow& operator= (TeamPropertyWindow&);
};

#endif

