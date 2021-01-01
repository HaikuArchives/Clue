/*******************************************************************************
/
/	File:			MenuItem.h
/
/   Description:    BMenuItem represents a single item in a BMenu.
/                   BSeparatorItem is a cosmetic menu item that demarcates
/                   groups of other items.
/
/	Copyright 1994-98, Be Incorporated, All Rights Reserved
/
*******************************************************************************/

#ifndef _BITMAP_MENU_ITEM_H
#define _BITMAP_MENU_ITEM_H

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
#endif

class BBitmap;
class BMessage;
class BWindow;

/*----------------------------------------------------------------*/
/*----- BMenuItem class ------------------------------------------*/

class BitmapMenuItem : public BMenuItem {
public:
	BitmapMenuItem(BWindow*, BBitmap*, const char*, const char*, BMessage*, char shortcut = 0, uint32 modifiers = 0);
	virtual			~BitmapMenuItem(void);
protected:

	virtual	void	GetContentSize(float*, float*);
	virtual	void	DrawContent(void);
	virtual	void	Highlight(bool);
	/*----- Private or reserved -----------------------------------------*/
private:
	BWindow* 		m_pWnd;
	char* 			m_sbar_message;
	BBitmap* 		m_bmp;
};

#endif /* _BITMAP_MENU_ITEM_H */
