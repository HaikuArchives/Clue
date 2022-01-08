#ifndef _EDITBOOLVIEW_H
#define _EDITBOOLVIEW_H

#ifndef _EDITVIEW_H
#include "EditView.h"
#endif

class EditBoolView : public EditView {
public:
	EditBoolView(BRect, BMessage*);
	virtual				~EditBoolView(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		AllAttached(void);
public:
	virtual bool		Save(void);
private:
	EditBoolView(const EditBoolView&);
	EditBoolView& operator= (EditBoolView&);
};

#endif //_EDITBOOLVIEW_H

