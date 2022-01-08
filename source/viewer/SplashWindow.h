#ifndef _SPLASH_H
#define _SPLASH_H

class SplashWindow : public BWindow {
public:
	SplashWindow(SplashWindow**, bool);
	~SplashWindow(void);
	virtual void	MessageReceived(BMessage*);
public:
	void BeginCountdown(void);
private:
	SplashWindow(const SplashWindow&);
	SplashWindow& operator= (SplashWindow&);
private:
	SplashWindow** 	m_ppOutside;
};

#endif //_SPLASH_H



