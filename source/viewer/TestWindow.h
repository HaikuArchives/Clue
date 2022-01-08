#ifndef _TEST_WINDOW_H
#define _TEST_WINDOW_H

//#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif
#include <Debug.h>
#include <Window.h>
#ifndef _PRINTSESSION_H
#include <PrintJob.h>
#endif

class TestWindow : public BWindow {
public:
	TestWindow(BWindow* pOwner, BHandler* pReplyHandler, BMessage* PrintSettings)
		:	BWindow(BRect(500, 500, 0, 0), "Invisible Print Setup Window",
					B_FLOATING_WINDOW_LOOK, B_FLOATING_SUBSET_WINDOW_FEEL, B_ASYNCHRONOUS_CONTROLS)
		,	m_ReplyWindow(pOwner)
		,	m_ReplyHandler(pReplyHandler)
		,	m_PrintSettings(PrintSettings)
	{
		AddToSubset(pOwner);
		Run();
		//Show ();
		PostMessage('onpr');
	};
	virtual void	MessageReceived(BMessage* message)
	{
		switch (message->what) {
			case 'onpr':
				OnPrint();
				break;
			default:
				BWindow::MessageReceived(message);
		}
	}
private:
	TestWindow(const TestWindow&);
	TestWindow& operator= (TestWindow&);
private:
	BWindow* 		m_ReplyWindow;
	BHandler* 		m_ReplyHandler;
	BMessage* 		m_PrintSettings;
	void OnPrint(void)
	{
		// create the object which will manage the print process
		if (! m_PrintSettings) {
			if (B_OK != OnPageSetup()) {
				PRINT(("OnPageSetup was canceled\n"));
				PostMessage(B_QUIT_REQUESTED);
				return;  // Page Setup cancelled
			}
		}

		// update the print job with the document's current
		// Page Setup settings.
		BPrintJob* printJob(new BPrintJob("Clue"));

		printJob->SetSettings(new BMessage(*m_PrintSettings));

		// run the standard File>Print dialog to determine page range, # of copies, etc.
		if (B_OK != printJob->ConfigJob()) {
			PRINT(("ConfigJob was canceled\n"));
			PostMessage(B_QUIT_REQUESTED);
			delete printJob;
			return;
		}

		//BAlert* pAlert = new BAlert("PrintJob", "Successfully configured the BPrintJob!", "OK");
		//pAlert->Go();

		PostMessage(B_QUIT_REQUESTED);

		BMessenger messenger(m_ReplyHandler, m_ReplyWindow);
		BMessage message('dopr');
		message.AddPointer("BPrintJob", printJob);
		message.AddMessage("Settings", m_PrintSettings);
		messenger.SendMessage(&message);
	}

	/***************************************************************
	 BackView::OnPageSetup
	 -----------------
	 Runs the standard File>Page Setup dialog. Returns B_OK if successful.
	***************************************************************/
	status_t OnPageSetup
	(
		void
	)
	{
		BPrintJob printJob("Clue");

		// MFC NOTE: The print settings are stored in a message, in an
		// undocumented format. BPrintJob is in charge of reading and
		// writing these settings, and we are in charge of storing them.
		//BMessage* printSettings = m_pDocument->PrintSettings();
		if (m_PrintSettings) {
			// we transfer ownership of the print settings to the print job
			printJob.SetSettings(new BMessage(*m_PrintSettings));
		}

		// ConfigPage launches the File>Page Setup dialog.
		status_t result(printJob.ConfigPage());

		if (result == B_OK) {
			// Page Setup was successful; store the new settings.
			// Once we call printJob.Settings(), we own the pointer that it returns.
			m_PrintSettings = printJob.Settings();
		}

		return result;
	}

};

#endif //_TEST_WINDOW_H

