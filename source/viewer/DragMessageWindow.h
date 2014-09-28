/*
	
	DropWindow.h
	
*/
/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.
*/

#ifndef DROP_WINDOW_H
#define DROP_WINDOW_H

#ifndef _WINDOW_H
#include <Window.h>
#endif

// DropWindow class
class DragMessageWindow : public BWindow  
{
	public:
						DragMessageWindow (void);
						~DragMessageWindow (void);
		virtual	bool	QuitRequested (void);
		virtual void	MessageReceived (BMessage *);
	private:
		void			Register (void);
		void			UnRegister (void);
};

#endif
