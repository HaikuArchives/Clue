#ifndef INSPECT_APPLICATION_KIT_OBJECTS_H
#define INSPECT_APPLICATION_KIT_OBJECTS_H

void Inspect_BApplication(BString&, BApplication*, int32, const char*);
void Inspect_BClipboard(BString&, BClipboard*, int32, const char*);
void Inspect_BFlattenable(BString&, BFlattenable*, int32, const char*);
void Inspect_BHandler(BString&, BHandler*, int32, const char*);
void Inspect_BInvoker(BString&, BInvoker*, int32, const char*);
void Inspect_BLooper(BString&, BLooper*, int32, const char*);
void Inspect_BMessage(BString&, BMessage*, int32, const char*, int32, int32);
void Inspect_BMessageFilter(BString&, BMessageFilter*, int32, const char*);
void Inspect_BMessageQueue(BString&, BMessageQueue*, int32, const char*);
void Inspect_BMessageRunner(BString&, BMessageRunner*, int32, const char*);
void Inspect_BMessenger(BString&, BMessenger*, int32, const char*);
void Inspect_BPropertyInfo(BString&, BPropertyInfo*, int32, const char*);
void Inspect_BRoster(BString&, BRoster*, int32, const char*);

#endif //INSPECT_APPLICATION_KIT_OBJECTS_H


