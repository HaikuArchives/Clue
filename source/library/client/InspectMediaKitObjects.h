#ifndef INSPECT_MEDIA_KIT_OBJECTS_H
#define INSPECT_MEDIA_KIT_OBJECTS_H

class BMultiChannelControl;
class BMediaEncoder;

void Inspect_BMediaEncoder (BString &, BMediaEncoder *, int32, const char *);
void Inspect_BMultiChannelControl (BString &, BMultiChannelControl *, int32, const char *);
void Inspect_BBuffer (BString &, BBuffer *, int32, const char *);
void Inspect_BSmallBuffer (BString &, BSmallBuffer *, int32, const char *);
void Inspect_BBufferConsumer (BString &, BBufferConsumer *, int32, const char *);
void Inspect_BBufferGroup (BString &, BBufferGroup *, int32, const char *);
void Inspect_BBufferProducer (BString &, BBufferProducer *, int32, const char *);
void Inspect_BParameterWeb (BString &, BParameterWeb *, int32, const char *);
void Inspect_BParameterGroup (BString &, BParameterGroup *, int32, const char *);
void Inspect_BParameter (BString &, BParameter *, int32, const char *);
void Inspect_BContinuousParameter (BString &, BContinuousParameter *, int32, const char *);
void Inspect_BDiscreteParameter (BString &, BDiscreteParameter *, int32, const char *);
void Inspect_BNullParameter (BString &, BNullParameter *, int32, const char *);
void Inspect_BControllable (BString &, BControllable *, int32, const char *);
void Inspect_BMediaTheme (BString &, BMediaTheme *, int32, const char *);
void Inspect_BMediaAddOn (BString &, BMediaAddOn *, int32, const char *);
void Inspect_BMediaDecoder (BString &, BMediaDecoder *, int32, const char *);
void Inspect_BMediaEventLooper (BString &, BMediaEventLooper *, int32, const char *);
void Inspect_BMediaFile (BString &, BMediaFile *, int32, const char *);
void Inspect_BMediaFiles (BString &, BMediaFiles *, int32, const char *);
void Inspect_media_node (BString &, media_node *, int32, const char *);
void Inspect_BMediaNode (BString &, BMediaNode *, int32, const char *);
void Inspect_BMediaRoster (BString &, BMediaRoster *, int32, const char *);
void Inspect_BMediaTheme (BString &, BMediaTheme *, int32, const char *);
void Inspect_BMediaTrack (BString &, BMediaTrack *, int32, const char *);
void Inspect_BMediaFormats (BString &, BMediaFormats *, int32, const char *);
void Inspect_BSound (BString &, BSound *, int32, const char *);
void Inspect_BSoundFile (BString &, BSoundFile *, int32, const char *);
void Inspect_BSoundPlayer (BString &, BSoundPlayer *, int32, const char *);
void Inspect_BTimeCode (BString &, BTimeCode *, int32, const char *);
void Inspect_BTimedEventQueue (BString &, BTimedEventQueue *, int32, const char *);
void Inspect_BTimeSource (BString &, BTimeSource *, int32, const char *);
void Inspect_BFileInterface (BString &, BFileInterface *, int32, const char *);

#endif //INSPECT_MEDIA_KIT_OBJECTS_H


