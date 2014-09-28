#ifndef _LIST_COUNT_STRING_VIEW_H
#define _LIST_COUNT_STRING_VIEW_H

#ifndef _STRING_VIEW_H
#include <StringView.h>
#endif

class ListCountStringView : public BStringView
{
	public:
		ListCountStringView (BRect bounds, 
			const char *name, 
			const char *text, 
			uint32 resizeFlags =  B_FOLLOW_LEFT | B_FOLLOW_TOP, 
			uint32 flags = B_WILL_DRAW);
		virtual void	Draw (BRect bounds);
		virtual void 	AttachedToWindow (void);
};

#endif //_LIST_COUNT_STRING_VIEW_H

