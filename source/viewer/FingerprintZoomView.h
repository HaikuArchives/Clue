#ifndef _FINGERPRINTZOOMVIEW_H
#define _FINGERPRINTZOOMVIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

#include <TextControl.h>

class BOutlineListView;
class BListItem;
class BMessage;
class ClueItem;
class BString;

class FingerprintZoomView : public BView {
public:
	FingerprintZoomView(BRect, ClueItem*);
	virtual				~FingerprintZoomView(void);
	virtual void		MessageReceived(BMessage*);
	virtual void		AllAttached(void);
	virtual	void		Draw(BRect);
	virtual void		MouseDown(BPoint);
	virtual void		Pulse(void);
private:
	FingerprintZoomView(const FingerprintZoomView&);
	FingerprintZoomView& operator= (FingerprintZoomView&);
private:
	ClueCategory	m_CAT;
	ClueEvent		m_EVT;
	bigtime_t		m_Time;
	thread_id		m_ThreadID;
	team_id			m_TeamID;
	uint32			m_Line;
	uint32			m_Sequence;
	BString			m_File;
	BString			m_Method;
	BString			m_Class;
	BString			m_Description;
	BString			m_Detail;
	bool			m_IsDown;
	BTextView* 		m_TextView;
	BScrollView* 	m_ScrollView;
	BButton* 		m_Button;
	BTextControl* 	m_TextControl;
	float			m_maxW;
	float			m_fontheight;
};

#endif // _FINGERPRINTZOOMVIEW_H



