#ifndef INSPECT_INTERFACE_KIT_OBJECTS_H
#define INSPECT_INTERFACE_KIT_OBJECTS_H


//function definitions
void Inspect_BAlert(BString&, BAlert*, int32, const char*);
void Inspect_BBitmap(BString&, BBitmap*, int32, const char*);
void Inspect_BBox(BString&, BBox*, int32, const char*);
void Inspect_BButton(BString&, BButton*, int32, const char*);
#ifdef CLUE_ON_ZETA_HACK
void Inspect_BChannelControl(BString&, BChannelControl*, int32, const char*);
void Inspect_BChannelSlider(BString&, BChannelSlider*, int32, const char*);
#endif
void Inspect_BCheckBox(BString&, BCheckBox*, int32, const char*);
void Inspect_BColorControl(BString&, BColorControl*, int32, const char*);
void Inspect_BControl(BString&, BControl*, int32, const char*);
void Inspect_BDragger(BString&, BDragger*, int32, const char*);
void Inspect_BFont(BString&, BFont*, int32, const char*);
void Inspect_BInputDevice(BString&, BInputDevice*, int32, const char*);
void Inspect_BListItem(BString&, BListItem*, int32, const char*);
void Inspect_BListView(BString&, BListView*, int32, const char*);
void Inspect_BMenu(BString&, BMenu*, int32, const char*);
void Inspect_BMenuBar(BString&, BMenuBar*, int32, const char*);
void Inspect_BMenuField(BString&, BMenuField*, int32, const char*);
void Inspect_BMenuItem(BString&, BMenuItem*, int32, const char*);
void Inspect_BOutlineListView(BString&, BOutlineListView*, int32, const char*);
void Inspect_BPicture(BString&, BPicture*, int32, const char*);
void Inspect_BPictureButton(BString&, BPictureButton*, int32, const char*);
void Inspect_BPoint(BString&, BPoint*, int32, const char*);
void Inspect_BPolygon(BString&, BPolygon*, int32, const char*);
void Inspect_BPopUpMenu(BString&, BPopUpMenu*, int32, const char*);
void Inspect_BPrintJob(BString&, BPrintJob*, int32, const char*);
void Inspect_BRect(BString&, BRect*, int32, const char*);
void Inspect_BRegion(BString&, BRegion*, int32, const char*);
void Inspect_BScreen(BString&, BScreen*, int32, const char*);
void Inspect_BScrollBar(BString&, BScrollBar*, int32, const char*);
void Inspect_BScrollView(BString&, BScrollView*, int32, const char*);
void Inspect_BSeparatorItem(BString&, BSeparatorItem*, int32, const char*);
void Inspect_BShape(BString&, BShape*, int32, const char*);
void Inspect_BShelf(BString&, BShelf*, int32, const char*);
void Inspect_BSlider(BString&, BSlider*, int32, const char*);
void Inspect_BStatusBar(BString&, BStatusBar*, int32, const char*);
void Inspect_BStringItem(BString&, BStringItem*, int32, const char*);
void Inspect_BStringView(BString&, BStringView*, int32, const char*);
void Inspect_BTab(BString&, BTab*, int32, const char*);
void Inspect_BTabView(BString&, BTabView*, int32, const char*);
void Inspect_BTextControl(BString&, BTextControl*, int32, const char*);
void Inspect_BTextView(BString&, BTextView*, int32, const char*);
void Inspect_unicode_block(BString&, unicode_block*, int32, const char*);
void Inspect_BView(BString&, BView*, int32, const char*);
void Inspect_BWindow(BString&, BWindow*, int32, const char*);

#endif //INSPECT_INTERFACE_KIT_OBJECTS_H


