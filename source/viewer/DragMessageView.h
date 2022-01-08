/*

	DropView.h

*/
/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.
*/

#ifndef DROP_VIEW_H
#define DROP_VIEW_H

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

class BMessage;
class BRect;
class BPoint;
class ColumnListView;

class DragMessageView : public BStringView {
public:
	DragMessageView(BRect, const char*, ColumnListView*);
	~DragMessageView(void);
	virtual void 	MessageReceived(BMessage*);
	virtual void 	MouseMoved(BPoint, uint32, const BMessage*);
private:
	void			ProcessMessage(const BMessage*);
private:
	ColumnListView* 	m_ColumnListView;
	BMessage* 			m_message;
};

#endif //DROP_VIEW_H
