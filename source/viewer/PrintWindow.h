/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _WINDOW_H
#include <Window.h>
#endif


/***************************************************************
class definition
***************************************************************/
class PrintWindow
:	public BWindow 
{
	public:
						PrintWindow (void);
		virtual			~PrintWindow (void);
		virtual void	MenusBeginning (void);
		virtual	void	DispatchMessage (BMessage *, BHandler *);
		virtual void	MessageReceived (BMessage *);
		virtual	bool	QuitRequested (void);
	public:
		static PrintWindow * Create (void);
	private:
						PrintWindow (const PrintWindow &);
						PrintWindow & operator= (PrintWindow &);
	private:
		void			Register (void);
		void			UnRegister (void);
		static PrintWindow * m_PrintWindow;
};

#endif //PRINTWINDOW_H

