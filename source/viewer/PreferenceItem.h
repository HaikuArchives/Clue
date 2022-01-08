#ifndef _PREFERENCE_ITEM_H
#define _PREFERENCE_ITEM_H

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif

#ifndef __BSTRING__
#include <String.h>
#endif

class PreferenceItem : public BStringItem {
public:
	PreferenceItem(const char*, const char*, uint32 outlineLevel = 0, bool expanded = true);
	~PreferenceItem(void);
public:
	void			SetDirty(bool);
	bool			IsDirty(void);
	void			CopyMessage(BMessage*);
	BMessage* 		GetMessage(void);
	const char* 	GetName(void);
private:
	BMessage		m_Message;
	BString			m_Name;
	bool			m_Dirty;
};

#endif //_OBJECTFILTER_ITEM_H


