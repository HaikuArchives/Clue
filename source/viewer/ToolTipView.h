#ifndef _TOOLTIPVIEW_H
#define _TOOLTIPVIEW_H

#ifndef _FONT_H
#include <Font.h>
#endif

#ifndef _WINDOW_H
#include <Window.h>
#endif

#ifndef _VIEW_H
#include <View.h>
#endif


// ui settings
struct tool_tip_settings {
	bool				enabled;		// flag whether tips are enables or not
	bool				one_time_only;	// flag to only display the tip once per time in view
	bigtime_t			delay;			// delay before tip is shown in microseconds
	bigtime_t			hold;			// amount of time tip is displayed in microseconds
	BFont				font;			// font tip is drawn in
};

// internal settings
struct tool_tip {
	bool				app_active;
	bool				quit;
	bool				stop;
	bool				stopped;
	bool				reset;
	bool				shown;
	bool				showing;
	bool				tip_timed_out;
	BPoint				start;
	BRect				bounds;
	class ToolTipView*	tool_tip_view;
	BWindow*				tool_tip_window;
	bigtime_t			start_time;
	bigtime_t			expire_time;
	tool_tip_settings	settings;
};


//====================================================================
class ToolTipView : public BView {
public:
	ToolTipView(tool_tip_settings* settings = NULL);
	~ToolTipView(void);
	virtual void		AllAttached(void);
	virtual void		Draw(BRect);
	virtual void		MessageReceived(BMessage*);

	void				GetSettings(tool_tip_settings*);
	void				SetSettings(tool_tip_settings*);
private:
	void				AdjustWindow();
	static status_t		ToolTipThread(tool_tip*);
private: //properties
	char* 				fString;
	thread_id			fThread;
	tool_tip			fTip;
};

#endif //_TOOLTIP_H
