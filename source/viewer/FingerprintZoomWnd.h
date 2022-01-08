#ifndef _FINGERPRINTZOOMWND_H
#define _FINGERPRINTZOOMWND_H

class BMessage;

class FingerprintZoomWnd : public BWindow {
public:
	FingerprintZoomWnd(ClueItem*);
	~FingerprintZoomWnd(void);
	virtual void	MessageReceived(BMessage*);
	//virtual void	DispatchMessage (BMessage *, BHandler *);
private:
	FingerprintZoomWnd(const FingerprintZoomWnd&);
	FingerprintZoomWnd& operator= (FingerprintZoomWnd&);
private:
};

#endif //_FINGERPRINTZOOMWND_H


