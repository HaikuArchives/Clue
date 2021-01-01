#ifndef _CLUE_TAB_VIEW_H
#define _CLUE_TAB_VIEW_H

#ifndef _TAB_VIEW_H
#include <TabView.h>
#endif

class ClueTabView : public BTabView {
public:
	ClueTabView(BRect frame, const char*,
				button_width width = B_WIDTH_AS_USUAL,
				uint32 resizingMode = B_FOLLOW_ALL,
				uint32 flags = B_FULL_UPDATE_ON_RESIZE |
				B_WILL_DRAW | B_NAVIGABLE_JUMP |
				B_FRAME_EVENTS | B_NAVIGABLE);
	virtual			~ClueTabView();
	virtual void	MessageReceived(BMessage*);
	virtual void	AllAttached(void);
	virtual void	Draw(BRect);
	virtual void	AddTab(BView*, BTab* tab = NULL);
	virtual BTab* 	RemoveTab(int32);
	virtual BRect	DrawTabs();
	virtual void	DrawBox(BRect);
	virtual void	Select(int32 tab);
	virtual void	SetFocusTab(int32, bool);
private:
};


#endif //_CLUE_TAB_VIEW_H

