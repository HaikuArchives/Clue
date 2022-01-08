#ifndef _TOOLTIPWINDOW_H
#define _TOOLTIPWINDOW_H

#ifndef _TOOLTIPVIEW_H
#include "ToolTipView.h"
#endif

struct Effect {
	BWindow* 	pWnd;
	bool		quit;
	int32		desiredheight;
};

class ToolTipView;

//====================================================================

class ToolTipWindow : public BWindow {
public:
	ToolTipWindow(tool_tip_settings* settings = NULL);
	virtual void		MessageReceived(BMessage*);
	virtual void		Show(void);
	virtual void		Hide(void);
	void				SetDesiredHeight(int32);
	void				GetSettings(tool_tip_settings*);
	void				SetSettings(tool_tip_settings*);
private:
	ToolTipView* 		fView;
	thread_id			m_EffectThreadID;
	Effect				m_fEffect;
	static status_t		EffectThread(Effect*);
	static int32		m_VisCount;
};

#endif // _TOOLTIPWINDOW_H

