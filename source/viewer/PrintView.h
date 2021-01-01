#ifndef CLUE_PRINT_VIEW_H
#define CLUE_PRINT_VIEW_H

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif

#ifndef _LIST_VIEW_H
#include <ListView.h>
#endif

#ifndef _LIST_ITEM_H
#include <ListItem.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _RECT_H
#include <Rect.h>
#endif


class BPrintJob;


class PrintViewa : public BView {
public:
	PrintViewa(BRect);
	virtual void	MessageReceived(BMessage*);
	void				OnPrint(void);
	bool				PrintPage(BPrintJob&, int32);
	status_t			OnPageSetup(void);
private:
	BListView* 			m_pBLV;
	BMessage* 			m_PrintSettings;
};

#endif //CLUE_PRINT_VIEW_H

