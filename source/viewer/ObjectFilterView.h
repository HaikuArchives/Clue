#ifndef _OBJECTFILTERVIEW_H
#define _OBJECTFILTERVIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

class BOutlineListView;
class BListItem;
class BMessage;

class ObjectFilterView : public BView {
public:
	ObjectFilterView(BRect);
	virtual				~ObjectFilterView(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		AllAttached(void);
private:
	void				CreateList(BOutlineListView*);
//		void	AddSubItem (BOutlineListView *, BListItem *, BMessage *);
	static BListItem* 	Disable(BListItem*, void*);
	static BListItem* 	Enable(BListItem*, void*);
	static BListItem* 	GrayOut(BListItem*, void*);
	static BListItem* 	UnGrayOut(BListItem*, void*);
public:
	void				SetDirty(void);
private:
	ObjectFilterView(const ObjectFilterView&);
	ObjectFilterView& operator= (ObjectFilterView&);
private:
	BButton* 			m_btnClose;
	BButton* 			m_btnEnableAll;
	BButton* 			m_btnDisableAll;
	BOutlineListView* 	m_outline;
};

#endif



