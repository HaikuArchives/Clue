/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef LIVEVIEW_H
#define LIVEVIEW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif


/***************************************************************
forward class declarations
***************************************************************/
class BButton;
class BitmapButton;
class BMenuField;
class BPopUpMenu;
class AnimatedView;
class ObjectFilterWnd;
class BWindow;


/***************************************************************
class definition
***************************************************************/
class LiveView
	:	public BView {
public:
	LiveView(BWindow*, BRect);
	virtual				~LiveView(void);
	virtual void		AllAttached(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		Draw(BRect);
	void				Listen(bool);
private:
	LiveView(const LiveView&);
	LiveView& operator= (LiveView&);
private:
	void CategoryChanged(BMessage*);
	void EventMaskChanged(BMessage*);
	void SelectUnselect(bool, bool);
	void RefreshButtons(void);
	void CreatePopupMenu(BWindow*);
	void CreateButtons(const BRect);
private:
	BMenuField* 		m_menufld;
	BPopUpMenu* 		m_popupmenu;
	AnimatedView* 		m_animation;
	BitmapButton* 		m_BmpButtons[12];
	BitmapButton* 		m_VCRButtons[2];
	BBitmap* 			m_VCRBitmaps[2];
	BButton* 			m_ObjectFilter;
	ObjectFilterWnd* 	m_pObjectFilterWnd;
	uint32				m_CurCat; //the currently selected category
};

#endif //LIVEVIEW_H

