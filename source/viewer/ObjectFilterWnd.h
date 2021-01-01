#ifndef _OBJECTFILTERWND_H
#define _OBJECTFILTERWND_H

class BMessage;

class ObjectFilterWnd : public BWindow {
public:
	ObjectFilterWnd(ObjectFilterWnd**);
	~ObjectFilterWnd(void);
	virtual void	MessageReceived(BMessage*);
	//virtual void	DispatchMessage (BMessage *, BHandler *);
private:
	ObjectFilterWnd(const ObjectFilterWnd&);
	ObjectFilterWnd& operator= (ObjectFilterWnd&);
private:
	ObjectFilterWnd** m_ppOutside;
};

#endif //_OBJECTFILTERWND_H


