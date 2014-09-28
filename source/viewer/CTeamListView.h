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
#include <ListView.h>
#include <Point.h>


/***************************************************************
class definition
***************************************************************/
class CTeamListView : public BListView
{
	public:
							CTeamListView (BRect, const char *,
								list_view_type type = B_SINGLE_SELECTION_LIST,
								uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								uint32 flags = B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);
		virtual void		MouseDown (BPoint);
};



