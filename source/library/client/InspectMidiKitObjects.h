#ifndef INSPECT_MIDI_KIT_OBJECTS_H
#define INSPECT_MIDI_KIT_OBJECTS_H

void Inspect_BMidi(BString&, BMidi*, int32, const char*);
void Inspect_BMidiPort(BString&, BMidiPort*, int32, const char*);
void Inspect_BMidiStore(BString&, BMidiStore*, int32, const char*);
void Inspect_BMidiSynth(BString&, BMidiSynth*, int32, const char*);
void Inspect_BMidiSynthFile(BString&, BMidiSynthFile*, int32, const char*);
void Inspect_BMidiText(BString&, BMidiText*, int32, const char*);
void Inspect_BSynth(BString&, BSynth*, int32, const char*);
void Inspect_BSamples(BString&, BSamples*, int32, const char*);

#endif //INSPECT_MIDI_KIT_OBJECTS_H


