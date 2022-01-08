/*
	1999 Jeff Braun
	web: www.citylinq.com/brauns
	email1: yobkadon@hotmail.com
	email2: brauns@citylinq.com
*/

//#define DEBUG 1

#ifndef _DEBUG_H
#include <Debug.h>
#endif

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef _BITMAP_H
#include <Bitmap.h>
#endif

#ifndef _GRAPHICS_DEFS_H
#include <GraphicsDefs.h>
#endif

#ifndef _ROSTER_H
#include <Roster.h>
#endif

#ifndef RESOURCES_H
#include <Resources.h>
#endif

#ifndef UTILITY_H
#include "Utility.h"
#endif


const char*
GetResourceString
(
	int32 id
)
{
	app_info theInfo;
	status_t rv(B_ERROR);

	PRINT((" do GetRunningAppInfo\n"));
	rv = be_roster->GetRunningAppInfo(be_app->Team(), &theInfo);
	if (B_OK == rv) { //be_app->GetAppInfo (&theInfo)
		PRINT((" BFile\n"));
		BFile file(&theInfo.ref, B_READ_ONLY);

		rv = file.InitCheck();
		if (B_NO_ERROR == rv) {
			BResources rsrc(&file);
			size_t length(0);
			const char* pstr(NULL);

			pstr = (const char*) rsrc.LoadResource(B_STRING_TYPE, id, &length);
			PRINT((" the string was '%s'.\n", pstr));

			return (pstr);
		}
	}

	switch (rv) {
		case B_ERROR:
			PRINT(("GetResourceString B_ERROR\n"));
			break;
		case B_BAD_TEAM_ID:
			PRINT(("GetResourceString B_BAD_TEAM_ID\n"));
			break;
		default:
			PRINT(("GetResourceString error = %i.\n", rv));
	}

	return NULL;
}


/*
void
ThreeDRect
	(
	BView * view
,	BRect rc
,	rgb_color rgbLT
,	rgb_color rgbRB
	)
{
	BRegion region;
	view->GetClippingRegion (&region);
	view->ConstrainClippingRegion (NULL);
	view->SetHighColor (rgbLT);
	view->MovePenTo (rc.left, rc.bottom);
	view->StrokeLine (BPoint (rc.left, rc.top));
	view->StrokeLine (BPoint (rc.right, rc.top));
	view->SetHighColor (rgbRB);
	view->StrokeLine (BPoint (rc.right, rc.bottom));
	view->StrokeLine (BPoint (rc.left, rc.bottom));
	view->ConstrainClippingRegion (&region);
}
*/


status_t
TransparentSetBits
(
	BBitmap* inBMP
	,	uint8 Red
	,	uint8 Green
	,	uint8 Blue
)
{
	if (B_RGBA32 != inBMP->ColorSpace())
		return B_ERROR;
	int32 transparent(Red);
	transparent <<= 8;
	transparent |= Green;
	transparent <<= 8;
	transparent |= Blue;
	int32* pvoid = (int32*) inBMP->Bits();
	int32 bitlength = inBMP->BitsLength() / 4;
	for (int32 j = 0; j < bitlength; j++, ++pvoid) {
		if ((*pvoid & 0x00FFFFFF) == transparent)
			*pvoid = B_TRANSPARENT_MAGIC_RGBA32;
	}

	return B_OK;
}


/*
void
TransparentSetBits
	(
	BBitmap * inBMP
,	uint8 transparent
	)
{
	uint8 * pvoid = (uint8 *) inBMP->Bits ();
	int32 bitlength = inBMP->BitsLength ();
	for (int32 j = 0; j < bitlength; j++, ++pvoid)
	{
		if (*pvoid == transparent)
		{
			*pvoid = B_TRANSPARENT_MAGIC_CMAP8;
		}
	}
}


*/
BBitmap*
RetrieveBitmap
(
	const char* name
)
{
	app_info info;
	size_t length;
	int32 idFound;

	if (be_app->GetAppInfo(&info) != B_OK)
		return NULL;

	BFile* file(new BFile(&info.ref, B_READ_ONLY));

	if (file->InitCheck() != B_NO_ERROR) {
		delete file;
		return NULL;
	}

	BResources* res(new BResources(file));

	if (res->GetResourceInfo('BBMP', name, &idFound, &length)==false) {
		delete res;
		delete file;
		return NULL;
	}

	void* data(new char[length]);
	//data = malloc (length);

	if (res->ReadResource('BBMP', idFound, data, 0, length)==B_ERROR) {
		delete file;
		delete res;
		delete data;
		return NULL;
	}

	BMessage* mes(new BMessage());

	if (mes->Unflatten((const char*)data) != B_OK) {
		delete file;
		delete res;
		delete data;
		delete mes;
		return NULL;
	}

	BArchivable* unarchived(instantiate_object(mes));    //instantiate_object behind the scenese does a new?!

	if (unarchived) {
		BBitmap* bitmap(NULL);
		bitmap = dynamic_cast<BBitmap*>(unarchived);
		//bitmap = cast_as(unarchived, BBitmap);
		if (bitmap) {
			delete res;
			delete file;
			delete data;
			delete mes;
			return bitmap;
		}

		delete unarchived;
		delete res;
		delete file;
		delete data;
		delete mes;
		return NULL;
	}

	delete res;
	delete file;
	delete data;
	delete mes;
	return NULL;
}

