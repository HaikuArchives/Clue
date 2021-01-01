#ifndef _BETTER_SCROLL_VIEW_H_
#define _BETTER_SCROLL_VIEW_H_


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
#ifndef _SCROLL_VIEW_H
#include <ScrollView.h>
#endif


//******************************************************************************************************
//**** PROJECT HEADER FILES
//******************************************************************************************************
//#include "ScrollViewCorner.h"


//******************************************************************************************************
//**** CLASS DECLARATIONS
//******************************************************************************************************
class BetterScrollView : public BScrollView {
public:
	BetterScrollView(const char*,
					 rgb_color, BView*, uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
					 uint32 flags = B_FRAME_EVENTS | B_WILL_DRAW, bool horizontal = true,
					 bool vertical = true, border_style border = B_FANCY_BORDER);
	virtual			~BetterScrollView(void);
	virtual void	SetDataRect(BRect, bool scrolling_allowed = true);
	BRect			GetDataRect(void);
	virtual	void	FrameResized(float, float);
	void			UpdateScrollBars(bool);
	void			SetCornerColor(rgb_color);
private:
	BetterScrollView(const BetterScrollView&);
	BetterScrollView& operator= (BetterScrollView&);
private:
	BRect			m_data_rect;
	BScrollBar* 	m_h_scrollbar;
	BScrollBar* 	m_v_scrollbar;
	BView* 			m_target;
public:
	bool			m_IsBeingDestroyed;
	BView* 			m_scroll_view_corner;
	//ScrollViewCorner* m_scroll_view_corner;
};


#endif



