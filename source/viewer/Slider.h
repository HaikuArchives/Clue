/*
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef SLIDER_H
#define SLIDER_H

/***************************************************************
include headers
***************************************************************/
#ifndef _SLIDER_H
#include <Slider.h>
#endif

/***************************************************************
class declaration
***************************************************************/
class Slider : public BSlider {
public:
	Slider(BRect, const char*, const char*, BMessage*,
		   int32, int32,
		   thumb_style thumbType = B_BLOCK_THUMB,
		   uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
		   uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	virtual			~Slider(void);
	virtual	void 	SetValue(int32);
private:
	Slider(const Slider&);
	Slider& operator= (Slider&);
protected:
	char* 			m_label;
};

#endif //SLIDER_H



