/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef	ANIMATEDVIEW_H
#define	ANIMATEDVIEW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _VIEW_H
#include <View.h>
#endif

#ifdef CLUE_ON_ZETA_HACK
#ifndef _MESSAGE_RUNNER_H
#include <MessageRunner.h>
#endif
#endif


/***************************************************************
class definition
***************************************************************/
class AnimatedView
	:	public BView {
public:
	AnimatedView(BPoint, const char*);
	virtual				~AnimatedView(void);
	virtual	void		Draw(BRect);
	virtual	void		AttachedToWindow(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		SetViewColor(rgb_color);
public:
	void				Enabled(bool);
	void				Pause(bool);
private:
	void				DrawSprite(void);
private:
	AnimatedView(const AnimatedView&);
	AnimatedView& operator= (AnimatedView&);
private:
	BMessageRunner* 	m_pMsgRunner;
	float				m_fOffset;
	BBitmap* 			m_pbmpStrip;
	BBitmap* 			m_pbmpMagnify;
	BBitmap* 			m_pbmpWorkBitmap;
	BView* 				m_pWorkView;
	bool				m_bRunning;
};

#endif //ANIMATEDVIEW_H

