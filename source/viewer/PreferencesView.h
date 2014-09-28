#ifndef _PREFERENCESVIEW_H
#define _PREFERENCESVIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

class BOutlineListView;
class BListItem;
class BMessage;
class EditView;

class PreferencesView : public BView
{
	public:
							PreferencesView (BRect, BMessage *);
		virtual				~PreferencesView (void);
		virtual void		MessageReceived (BMessage *);
		virtual void		AllAttached (void);
//		virtual void Draw (BRect);
//		virtual void Pulse (void);
	private:
		void				CreateList (BOutlineListView *, BListItem *, BMessage *);
//		void	AddSubItem (BOutlineListView *, BListItem *, BMessage *);
	public:
		void				SetDirty (void);
	private:
		PreferencesView (const PreferencesView &);
		PreferencesView & operator= (PreferencesView &);
	private:
		BButton *			m_btnOK;
		BButton *			m_btnCancel;
		BButton *			m_btnApply;
		BOutlineListView *	m_outline;
		BTextView *			m_text;
		EditView *			m_EditView;
		bool				m_IsDirty;
};

#endif




