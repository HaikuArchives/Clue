#ifndef _SPLASHVIEW_H
#define _SPLASHVIEW_H

#ifndef _VIEW_H
#include <View.h>
#endif

class CreditsView;
struct version_info;

class SplashView : public BView
{
	public:
						SplashView (BRect, bool);
		virtual			~SplashView (void);
		virtual void	Draw (BRect);
		virtual void	Pulse (void);
		virtual void	AttachedToWindow (void);
		virtual void	MessageReceived (BMessage *);
	private:
		SplashView (const SplashView &);
		SplashView & operator= (SplashView &);
	private:
		BBitmap *		m_bmpSplash;
		CreditsView *	m_pCreditsView;
		bool			m_AppStarting;
		BButton *		m_btnOK;
		version_info *	m_pVersionInfo;
		char			m_VIString[60];
};

#endif


