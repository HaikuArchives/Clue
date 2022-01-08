/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/


/***************************************************************
include header files
***************************************************************/
#define DEBUG 1
#define CLUE_ON_ZETA_HACK
#include <Window.h>
#include <Menu.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include "constants.h"
#ifdef CLUE_ON_ZETA_HACK
#include "TeamItem.h"
#else
#include "CTeamItem.h"
#endif
#include "CTeamListView.h"

#ifdef CLUE_ON_ZETA_HACK
typedef TeamItem CTeamItem;
#endif

/***************************************************************
class implementation
***************************************************************/
CTeamListView :: CTeamListView
(
	BRect frame
	,	const char* name
	,	list_view_type type
	,	uint32 resizingMode
	,	uint32 flags
)
	:	BListView(frame, name, type, resizingMode, flags)
{
}



void
CTeamListView ::MouseDown
(
	BPoint point
)
{
	int32 buttons(0);
	Window()->CurrentMessage()->FindInt32("buttons", &buttons);
	if (B_SECONDARY_MOUSE_BUTTON & buttons) {
		//BPoint ptOrigin (Origin ());
		//point.y += ptOrigin.y;
		int32 index(IndexOf(point));
		if (index >= 0) {
			Select(index);
			CTeamItem* pTI((CTeamItem*) ItemAt(index));
			uint32 flags(pTI->Filter());
			BView* targetview(Window()->FindView("CBackView"));
			BPopUpMenu* popupmenu(new BPopUpMenu("TeamSelect"));
			BMenuItem* menuitem(new BMenuItem("Delete", new BMessage(MSG_TEAM_DELETE)));
			menuitem->SetTarget(targetview);
			popupmenu->AddItem(menuitem);
			BMenu* menu(new BMenu("FilterMenu"));

			menuitem = new BMenuItem("Class constructor", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Class destructor", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Method Entry", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Method Exit", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Info", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Warning", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			menuitem = new BMenuItem("Error", new BMessage(MSG_TEAM_PROPERTIES));
			menuitem->SetTarget(targetview);
			menu->AddItem(menuitem);

			popupmenu->AddItem(menu);
			//popupmenu->AddItem (menuitem);
			ConvertToScreen(&point);
			popupmenu->Go(point, true);
		}
	} else
		BListView::MouseDown(point);
}


