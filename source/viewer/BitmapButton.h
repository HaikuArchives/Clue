#ifndef _BITMAPBUTTON_H
#define _BITMAPBUTTON_H

#ifndef _CONTROL_H
#include <Control.h>
#endif
//#include <Button.h>

class BBitmap;
class BPoint;
class BMessage;

//class CBitmapButton : public BButton
class BitmapButton : public BControl
{
	public:
		BitmapButton (BPoint, const BBitmap *, BMessage *, const char *, const char *);
		virtual void MouseDown (BPoint);
		virtual void MouseMoved (BPoint, uint32, const BMessage *);
		virtual void KeyDown (const char *, int32);
		virtual void Draw (BRect);
		virtual void SetEnabled (bool);
	private:
		BitmapButton (const BitmapButton &);
		BitmapButton & operator= (BitmapButton &);
	private: //methods
		void DrawButtonFrame (void);
	private: //data
		const BBitmap * m_bmp;
		//int32			m_ResourceID;
		const char *	m_sbar_message;
		const char *	m_tooltip_message;
};

#endif //_BITMAPBUTTON_H



