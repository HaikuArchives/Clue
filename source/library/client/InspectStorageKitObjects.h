#ifndef INSPECT_STORAGE_KIT_OBJECTS_H
#define INSPECT_STORAGE_KIT_OBJECTS_H

void Inspect_BAppFileInfo(BString&, BAppFileInfo*, int32, const char*);
void Inspect_BDirectory(BString&, BDirectory*, int32, const char*);
void Inspect_BEntry(BString&, BEntry*, int32, const char*);
void Inspect_BEntryList(BString&, BEntryList*, int32, const char*);
void Inspect_BFile(BString&, BFile*, int32, const char*);
void Inspect_BFilePanel(BString&, BFilePanel*, int32, const char*);
void Inspect_BMimeType(BString&, BMimeType*, int32, const char*);
void Inspect_BNode(BString&, BNode*, int32, const char*);
void Inspect_BNodeInfo(BString&, BNodeInfo*, int32, const char*);
void Inspect_BPath(BString&, BPath*, int32, const char*);
void Inspect_BPositionIO(BString&, BPositionIO*, int32, const char*);
void Inspect_BStatable(BString&, BStatable*, int32, const char*);
void Inspect_BVolume(BString&, BVolume*, int32, const char*);
void Inspect_BVolumeRoster(BString&, BVolumeRoster*, int32, const char*);
void Inspect_BSymLink(BString&, BSymLink*, int32, const char*);
void Inspect_BResources(BString&, BResources*, int32, const char*);
void Inspect_BResourceStrings(BString&, BResourceStrings*, int32, const char*);
void Inspect_BQuery(BString&, BQuery*, int32, const char*);

#endif //INSPECT_STORAGE_KIT_OBJECTS_H

