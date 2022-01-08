//#define DEBUG 1

#ifndef _ALERT_H
#include <Alert.h>
#endif

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _PRINTSESSION_H
#include <PrintJob.h>
#endif

#ifndef CLUE_PRINT_VIEW_H
#include "PrintView.h"
#endif


PrintViewa :: PrintViewa(BRect frame)
	:	BView(frame, "TestView", B_FOLLOW_ALL_SIDES, 0)
	,	m_pBLV(NULL)
{
	m_pBLV = new BListView(BRect(10, 10, 50, 50), "Numbers", B_SINGLE_SELECTION_LIST);
	AddChild(m_pBLV);
}

/***************************************************************
***************************************************************/
void
PrintViewa :: MessageReceived
(
	BMessage* message
)
{
	switch (message->what) {
		case 'data':
			m_pBLV->AddItem(new BStringItem("print request"));
			PRINT(("PrintViewa: request a print\n"));
			OnPrint();
			break;
		default:
			BView::MessageReceived(message);
			break;
	}
}



/***************************************************************
 BackView::OnPrint
 -----------------
 Handles the File>Print command.
***************************************************************/
void
PrintViewa :: OnPrint
(
	void
)
{
	// create the object which will manage the print process
	BPrintJob printJob("Clue");

	if (! m_PrintSettings) {
		if (B_OK != OnPageSetup()) {
			return;  // Page Setup cancelled
		}
	}

	// update the print job with the document's current
	// Page Setup settings.
	printJob.SetSettings(new BMessage(*m_PrintSettings));

	// run the standard File>Print dialog to determine page range, # of copies, etc.
	if (B_OK != printJob.ConfigJob())
		return;

	// determine page range
	int32 nFirst = printJob.FirstPage();
	int32 nLast = printJob.LastPage();
	int32 nTotal = 1000;

	if (nFirst < 1)
		nFirst = 1;
	if (nLast < 1)
		nLast = 1;
	if (nFirst >= nTotal)
		nFirst = nTotal;
	if (nLast >= nTotal)
		nLast = nTotal;

	// start the printing process
	bool bOk = true;
	printJob.BeginJob();

	for (int32 i = nFirst; i <= nLast; i++) {
		bOk = PrintPage(printJob, i);
		if (! bOk)
			break;
	}

	if (bOk) {
		// no errors; complete the printing process
		printJob.CommitJob();
	} else {
		// errors in printing; inform the user and bail
		BAlert* pAlert = new BAlert("print error",
									"There was an error printing the document.", "OK");
		pAlert->Go();
	}
}

class PrintView2 : public BView {
public:
	PrintView2(BRect rc, const char* text)
		:	BView(rc, "printview2", B_FOLLOW_NONE, B_WILL_DRAW)
		,	m_text(text)
	{
		// .25 in. from top of view to the text
		m_fAboveText = 18;
		// .35 inches from bottom of text to ruler
		m_fBelowText = 26;
		// .25 inches from ruler to bottom of view
		m_fBelowLine = 18;
		// total height of text (also in points)
		font_height height;
		GetFontHeight(&height);
		m_fTextHeight = height.ascent + height.descent + height.leading;

		// resize view to the correct height and specified width
		//float totHeight = m_fAboveText + m_fTextHeight + m_fBelowText + m_fBelowLine;
		//ResizeTo(width, totHeight);
	}
	virtual void Draw(BRect)
	{
		// draw string m_fAboveText units down
		float y(m_fAboveText);
		DrawString(m_text, BPoint(0, y));
		// draw ruler m_fBelowText units below text
		y += m_fTextHeight + m_fBelowText;
		StrokeLine(BPoint(0, y), BPoint(Bounds().Width(), y));
	}
private:
	float m_fTextHeight;
	float m_fAboveText;
	float m_fBelowText;
	float m_fBelowLine;
	const char* m_text;
};


/***************************************************************
 BackView::PrintPage
 -----------------
 Prints the specified page to the specified print job.
***************************************************************/
bool
PrintViewa :: PrintPage
(
	BPrintJob& printJob
	,	int32 nPage
)
{
	BRect r = printJob.PrintableRect();	// relative to left top corner of paper
	BWindow* pWin(Window());

	// create a view which draws the header
	PrintView2* pPrintView(new PrintView2(r, "Here is some text to print from Clue!"));

	pPrintView->Hide();	// so the view won't be seen on screen
	pWin->AddChild(pPrintView);   // view needs to be attached to a window to be drawn

	r.OffsetTo(0, 0);	// we draw relative to left top corner of printable area
	printJob.DrawView(pPrintView, r, r.LeftTop());

	// clean up
	pWin->RemoveChild(pPrintView);
	delete pPrintView;

	printJob.SpoolPage();
	return (printJob.CanContinue());
}


/***************************************************************
 BackView::OnPageSetup
 -----------------
 Runs the standard File>Page Setup dialog. Returns B_OK if successful.
***************************************************************/
status_t
PrintViewa :: OnPageSetup
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
