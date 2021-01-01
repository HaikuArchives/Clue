#ifndef _PREFERENCESWND_H
#define _PREFERENCESWND_H

class BMessage;

class PreferencesWnd : public BWindow {
public:
	PreferencesWnd(PreferencesWnd**, BMessage*);
	~PreferencesWnd(void);
	virtual void	MessageReceived(BMessage*);
	//virtual void	DispatchMessage (BMessage *, BHandler *);
private:
	PreferencesWnd(const PreferencesWnd&);
	PreferencesWnd& operator= (PreferencesWnd&);
private:
	PreferencesWnd** 	m_ppOutside;
};

#endif //_PREFERENCESWND_H



