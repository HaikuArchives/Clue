#ifndef _CREDITSVIEW_H
#define _CREDITSVIEW_H

class CreditsView : public BView
{
	public:
		CreditsView (void);
		virtual void Draw (BRect);
		virtual void GetPreferredSize (float *, float *);
		virtual void AttachedToWindow (void);
		virtual void Pulse (void);
	private:
		CreditsView (const CreditsView &);
		CreditsView & operator= (CreditsView &);
};

#endif


