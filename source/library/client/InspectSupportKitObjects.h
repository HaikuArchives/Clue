#ifndef INSPECT_SUPPORT_KIT_OBJECTS_H
#define INSPECT_SUPPORT_KIT_OBJECTS_H

void Inspect_BStopWatch (BString &, BStopWatch *, int32, const char *);
void Inspect_BLocker (BString &, BLocker *, int32, const char *);
void Inspect_BBufferIO (BString &, BBufferIO *, int32, const char *);
void Inspect_BString (BString &, BString *, int32, const char *);
void Inspect_BList (BString &, BList *, int32, const char *);
void Inspect_BAutolock (BString &, BAutolock *, int32, const char *);

#endif //INSPECT_SUPPORT_KIT_OBJECTS_H

