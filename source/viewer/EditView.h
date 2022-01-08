#ifndef _EDITVIEW_H
#define _EDITVIEW_H

#ifndef _BOX_H
#include <Box.h>
#endif

class BMessage;

class EditView : public BBox {
public:
	EditView(BRect, BMessage*, const char* name = NULL,
			 uint32 resizeFlags = B_FOLLOW_LEFT | B_FOLLOW_TOP,
			 uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP,
			 border_style border = B_FANCY_BORDER);
	virtual				~EditView(void);
public:
	virtual bool		Save(void) = 0;
protected:
	BMessage* 		m_Message;
};

#endif



