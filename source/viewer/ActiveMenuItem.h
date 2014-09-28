/*	
	2000 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef ACTIVEMENUITEM_H
#define ACTIVEMENUITEM_H

#ifndef _MENU_ITEM_H
#include <MenuItem.h>
#endif

class ActiveMenuItem : public BMenuItem
{
	public:
						ActiveMenuItem (BWindow *, const char *, const char *, BMessage *,
							char shortcut = 0, uint32 modifiers = 0);
		virtual			~ActiveMenuItem (void);
		virtual status_t Invoke (BMessage * message = NULL);
	public:
		void			SetStatusBarMessage (const char *);
	private:
						ActiveMenuItem (const ActiveMenuItem &);
						ActiveMenuItem & operator= (ActiveMenuItem &);
	protected:
		virtual void	Highlight (bool);
	private:
		BWindow *		m_pWnd;
		char *			m_sbar_message;
};

#endif //ACTIVEMENUITEM_H
