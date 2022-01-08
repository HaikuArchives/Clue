#ifndef SPLITTERVIEW_H
#define SPLITTERVIEW_H

/***************************************************************
include header files
***************************************************************/
#ifndef _VIEW_H
#include <View.h>
#endif

/***************************************************************
class definition
***************************************************************/
class SplitterView
	:	public BView {
public:
	SplitterView(BRect, char*, uint32, uint32);
	virtual void	Draw(BRect);
//		virtual void	AllAttached (void);
	virtual void	MessageReceived(BMessage*);
	virtual void	MouseDown(BPoint);
	virtual void	MouseMoved(BPoint, uint32, const BMessage*);
	virtual void	MouseUp(BPoint);
	virtual void	AttachedToWindow(void);
private:
	SplitterView(const SplitterView&);
	SplitterView& operator= (SplitterView&);
private:
	bool			m_tracking;
	bool			inview;
};

#endif	//SPLITTERVIEW_H

