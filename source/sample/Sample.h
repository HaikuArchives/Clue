/*	
	Jeff Braun
	web: http://www.tcinternet.net/users/brauns/
	emai1: yobkadon@hotmail.com
*/

/***************************************************************
class definitions
***************************************************************/
class CApp : public BApplication
{
	public:
		CApp (void);
				void DispatchMessage (BMessage *, BHandler *);
		virtual void AppActivated (bool);
		virtual void ReadyToRun (void);
	private:
		TRACE_CLASS (CC_APPLICATION);
};

class CWindow : public BWindow
{
	public:
		CWindow (BRect);
				void DispatchMessage (BMessage *, BHandler *);
		virtual bool QuitRequested ();
	public:
		BMenu *		m_pMenu;
		BMenuBar *	m_pMenuBar;
		BMenuItem * m_pMenuItem1;
		BMenuItem * m_pMenuItem2;
		BMenuItem * m_pMenuItem3;
	private:
		void		BuildEditMenu (void);
	private:
		TRACE_CLASS (CC_INTERFACE);
};

class CTextView : public BTextView
{
	public:
						CTextView (BRect, const char *, BRect, uint32, uint32);
		virtual void	Draw(BRect);
		virtual void	KeyDown (const char *, int32);
	private:
		TRACE_CLASS (CC_INTERFACE);
};

class CView : public BView
{
	public:
						CView (BRect);
		virtual void	AllAttached (void);
		virtual void	MessageReceived (BMessage *);
		virtual void	MouseMoved (BPoint, uint32, const BMessage *);
	private:
		class innerclass
		{
			public:
				innerclass (void)
				{
					TRACE_SIMPLE ((CC_SUPPORT, CR_INFO, "inner classe::constructor"));
				}
				void Debug2 (void)
				{
					TRACE_SIMPLE ((CC_SUPPORT, CR_INFO, "inner classe::Debug2"));
				}
				int Debug3 (void)
				{
					TRACE_SIMPLE ((CC_SUPPORT, CR_INFO, "inner classe::Debug3"));
					return 0;
				}
				int * Debug4 (void)
				{
					TRACE_SIMPLE ((CC_SUPPORT, CR_INFO, "inner classe::Debug4"));
					int i (-1);
					return &i;
				}
		};
	private:
		BButton *			m_BButtons[2];
		BCheckBox *			m_BCheckBox;
		BMessageRunner *	m_BMessageRunner;
		CTextView *			m_BTextView;
		BScrollView *		m_BScrollView;
		BBox *				m_BBox;
		BRadioButton *		m_BRadioButton;
	private:
		TRACE_CLASS (CC_INTERFACE);
};

