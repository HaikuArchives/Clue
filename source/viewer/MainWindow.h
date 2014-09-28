/*	
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


/***************************************************************
include header files
***************************************************************/
#ifndef _ENTRY_H
#include <Entry.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

class BFilePanel;
class BMenuBar;
class BMenu;
class LiveView;
class BackView;
class StatusBarView;


/***************************************************************
class definition
***************************************************************/
class MainWindow
:	public BWindow 
{
	public:
						MainWindow (void);
						MainWindow (entry_ref *);
		virtual			~MainWindow (void);
		virtual void	MenusBeginning (void);
		virtual void	MessageReceived (BMessage *);
		virtual	bool	QuitRequested (void);
	private:
						MainWindow (const MainWindow &);
						MainWindow & operator= (MainWindow &);
	public:
		StatusBarView *	GetStatusBar (void) const;
	private:
		BMenu *			BuildFileMenu (void) const;
		BMenu *			BuildEditMenu (void) const;
		BMenu *			BuildWindowMenu (void) const;
		void			Export (BMessage *);
		void			Save (BMessage *);
		void			Register (void);
		void			UnRegister (void);
		void			SetFilePanelColors (void);
	private:
		BMenuBar *		m_pMenuBar;
		StatusBarView *	m_pStatusBar;
		LiveView *		m_LiveView;
		BackView *		m_backview;
		BFilePanel *	m_SavePanel;
		bool			m_running;
		const bool		m_IsLive;
};

#endif //MAINWINDOW_H

