#ifndef _EDITCOLORVIEW_H
#define _EDITCOLORVIEW_H

#ifndef _EDITVIEW_H
#include "EditView.h"
#endif

class BColorControl;

class EditColorView : public EditView
{
	public:
							EditColorView (BRect, BMessage *);
		virtual				~EditColorView (void);
		virtual void		MessageReceived (BMessage *);
		virtual void		AllAttached (void);
		virtual void		AttachedToWindow (void);
		virtual void		DetachedFromWindow (void);
		virtual void		Draw (BRect);
	public:
		virtual bool		Save (void);
		static EditColorView *	Create (BRect, BMessage *);
	private:
		bool				PopulateData (BMessage *);
	private:
		EditColorView (const EditColorView &);
		EditColorView & operator= (EditColorView &);
	private:
		BColorControl *	m_ColorControl;
		BView *			m_view;
		rgb_color		m_color;
};

#endif




