/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef THEAPP_H
#define THEAPP_H

/***************************************************************
include header files
***************************************************************/
#ifndef _APPLICATION_H
#include <Application.h>
#endif

class BFilePanel;
class SplashWindow;
class PreferencesWnd;
class ToolTipWindow;
class RefFilter;

/***************************************************************
class definition
***************************************************************/
class TheApp
	:	public BApplication {
public:
	TheApp(void);
	virtual			~TheApp(void);
	virtual void	AboutRequested(void);
	virtual void	AppActivated(bool);
	virtual void	ArgvReceived(int32, char**);
	virtual void	MessageReceived(BMessage*);
	virtual void	ReadyToRun(void);
	virtual void	RefsReceived(BMessage*);
private:
	void			GetSettings(void);
	void			SaveSettings(void);
	void			VerifySettings(void);
	void			UpdateColors(void);
	void			SetFilePanelColors(void);
	void			Migrate(int32);
	void			OpenHelp(void);
	void			CloseZoomWindows(void);
private:
	TheApp(const TheApp&);
	TheApp& operator= (TheApp&);
public:
	ToolTipWindow* 	m_pToolTip;
private:
	SplashWindow* 	m_pSplashWnd;
	PreferencesWnd* m_pPreferencesWnd;
	int32			m_window_count;
	int32			m_next_untitled_number;
	BFilePanel* 	m_OpenPanel;
	RefFilter* 		m_RF;
private:
	static const int32 SETTINGS_FORMAT_VERSION;
};

#endif //THEAPP_H
