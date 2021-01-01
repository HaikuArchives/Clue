/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

#ifndef UTILITY_H
#define UTILITY_H

const char* GetResourceString(int32);
//void ThreeDRect (BView *, BRect, rgb_color, rgb_color);
status_t TransparentSetBits(BBitmap*, uint8 Red, uint8 Green, uint8 Blue);
//void TransparentSetBits (BBitmap *, uint8);
BBitmap* RetrieveBitmap(const char*);

#endif //UTILITY_H


