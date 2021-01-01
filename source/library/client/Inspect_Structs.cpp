#include "ClueBuild.h"
#include <Be.h>

#include <MediaDefs.h>

#include <UnicodeBlockObjects.h>

#include "Inspect_Enums.h"
#include "Inspect_Structs.h"
//#include "InspectApplicationKitObjects.h"
//#include "InspectInterfaceKitObjects.h"
//#include "InspectStorageKitObjects.h"
#include "utility.h"

//defined in Inspect_Enums.cpp
extern const char * pTrue;
extern const char * pFalse;
extern const char * g_pIndentation;
//extern const char * g_pFailedWithError;
extern const char * g_pNewline;




/***************************************************************
defined in Buffer.h as:
struct buffer_clone_info {
	buffer_clone_info();
	~buffer_clone_info();
	media_buffer_id	buffer;
	area_id		area;
	size_t		offset;
	size_t		size;
	int32		flags;
private:
	uint32 _reserved_[4];
};
***************************************************************/
void
Inspect_Struct_buffer_clone_info
	(
	BString & strDetails
,	buffer_clone_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[buffer_clone_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "buffer= " << inValue->buffer << g_pNewline;
		strDetails << tabindent << "area= " << inValue->area << g_pNewline;
		strDetails << tabindent << "offset= " << inValue->offset << g_pNewline;
		strDetails << tabindent << "size= " << inValue->size << g_pNewline;
		GetHexString (hexbuf, (intptr_t) inValue->flags);
		strDetails << tabindent << "flags= (" << hexbuf << "), " << inValue->flags << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The buffer_clone_info was NULL.\n";
	}
}


/***************************************************************
defined in DirectWindow.h as:
typedef struct {
	direct_buffer_state	buffer_state;
	direct_driver_state	driver_state;
	void				*bits;
	void				*pci_bits;
	int32				bytes_per_row;
	uint32				bits_per_pixel;
	color_space			pixel_format;
	buffer_layout		layout;
	buffer_orientation	orientation;
	uint32				_reserved[9];
	uint32				_dd_type_;
	uint32				_dd_token_;
	uint32				clip_list_count;
	clipping_rect		window_bounds;
	clipping_rect		clip_bounds;
	clipping_rect		clip_list[1];
} direct_buffer_info;
***************************************************************/
void
Inspect_Struct_direct_buffer_info
	(
	BString & strDetails
,	direct_buffer_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[direct_buffer_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The direct_buffer_info was NULL.\n";
	}
}


/***************************************************************
defined in E-mail.h as:
typedef struct {
	char		pop_name[B_MAX_USER_NAME_LENGTH];
	char		pop_password[B_MAX_USER_NAME_LENGTH];
	char		pop_host[B_MAX_HOST_NAME_LENGTH];
	char		real_name[128];
	char		reply_to[128];
	int32		days;			//see flags above
	int32		interval;		// in seconds
	int32		begin_time;		// in seconds
	int32		end_time;		// in seconds
} mail_pop_account;
***************************************************************/
void
Inspect_Struct_mail_pop_account
	(
	BString & strDetails
,	mail_pop_account * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mail_pop_account object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		BString str (inValue->pop_name, B_MAX_USER_NAME_LENGTH);
		strDetails << tabindent << "pop_name= " << str.String () << g_pNewline;
		str.SetTo (inValue->pop_password, B_MAX_USER_NAME_LENGTH);
		strDetails << tabindent << "pop_passwrod= " << str.String () << g_pNewline;
		str.SetTo (inValue->pop_host, B_MAX_HOST_NAME_LENGTH);
		strDetails << tabindent << "pop_host= " << str.String () << g_pNewline;
		str.SetTo (inValue->real_name, 128);
		strDetails << tabindent << "real_name= " << str.String () << g_pNewline;
		str.SetTo (inValue->reply_to, 128);
		strDetails << tabindent << "reply_to= " << str.String () << g_pNewline;
		strDetails << tabindent << "days= " << inValue->days;
		switch (inValue->days)
		{
			case B_CHECK_NEVER:
				strDetails << ", B_CHECK_NEVER";
				break;
			case B_CHECK_WEEKDAYS:
				strDetails << ", B_CHECK_WEEKDAYS";
				break;
			case B_CHECK_DAILY:
				strDetails << ", B_CHECK_DAILY";
				break;
			case B_CHECK_CONTINUOUSLY:
				strDetails << ", B_CHECK_CONTINUOUSLY";
				break;
		}
		strDetails << g_pNewline;
		strDetails << tabindent << "interval= " << inValue->interval << " seconds" << g_pNewline;
		strDetails << tabindent << "begin_time= " << inValue->begin_time << " seconds" << g_pNewline;
		strDetails << tabindent << "end_time= " << inValue->end_time << "seconds" << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The mail_pop_account was NULL.\n";
	}
}


/***************************************************************
defined in E-mail.h as:
typedef struct {
	bool		alert;
	bool		beep;
} mail_notification;
***************************************************************/
void
Inspect_Struct_mail_notification
	(
	BString & strDetails
,	mail_notification * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mail_notification object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "alert= " << inValue->alert << g_pNewline;
		strDetails << tabindent << "beep= " << inValue->beep << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The mail_notification was NULL.\n";
	}
}


/***************************************************************
defined in Entry.h
struct entry_ref {
						entry_ref();
  						entry_ref(dev_t dev, ino_t dir, const char *name);
						entry_ref(const entry_ref &ref);
						~entry_ref();
	
  	status_t 			set_name(const char *name);

	bool				operator==(const entry_ref &ref) const;
	bool				operator!=(const entry_ref &ref) const;
	entry_ref &			operator=(const entry_ref &ref);

	dev_t				device;
	ino_t				directory;
	char				*name;
};
***************************************************************/
void
Inspect_Struct_entry_ref
	(
	BString & strDetails
,	entry_ref * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[entry_ref struct, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "device= " << inValue->device << g_pNewline;
		strDetails << tabindent << "directory= " << inValue->directory << g_pNewline;
		strDetails << tabindent << "name= " << inValue->name << g_pNewline;

	}
	else
	{
		strDetails << tabindent << "The entry_ref was NULL.\n";
	}
}


/***************************************************************
defined in Font.h as:
struct edge_info {
	float	left;
	float	right;
};
***************************************************************/
void
Inspect_Struct_edge_info
	(
	BString & strDetails
,	edge_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[edge_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "left= " << inValue->left << g_pNewline;
		strDetails << tabindent << "right= " << inValue->right << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The edge_info was NULL.\n";
	}
}


/***************************************************************
defined in Font.h as:
struct font_height {
	float	ascent;
	float	descent;
	float	leading;
};
***************************************************************/
void
Inspect_Struct_font_height
	(
	BString & strDetails
,	font_height * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[font_height object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "ascent= " << inValue->ascent << g_pNewline;
		strDetails << tabindent << "descent= " << inValue->descent << g_pNewline;
		strDetails << tabindent << "leading= " << inValue->leading << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The font_height was NULL.\n";
	}
}


/***************************************************************
defined in Font.h as:
struct escapement_delta {
	float	nonspace;
	float	space;
};
***************************************************************/
void
Inspect_Struct_escapement_delta
	(
	BString & strDetails
,	escapement_delta * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[escapement_delta object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "nonspace= " << inValue->nonspace << g_pNewline;
		strDetails << tabindent << "space= " << inValue->space << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The escapement_delta was NULL.\n";
	}
}


/***************************************************************
defined in Font.h as:
struct tuned_font_info {
	float    size;
	float    shear; 
	float    rotation;
	uint32   flags;
	uint16   face;
};
***************************************************************/
void
Inspect_Struct_tuned_font_info
	(
	BString & strDetails
,	tuned_font_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[tuned_font_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "size= " << inValue->size << g_pNewline;
		strDetails << tabindent << "shear= " << inValue->shear << g_pNewline;
		strDetails << tabindent << "rotation= " << inValue->rotation << g_pNewline;
		strDetails << tabindent << "flags= " << inValue->flags << g_pNewline;
		strDetails << tabindent << "face= " << inValue->face << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The tuned_font_info was NULL.\n";
	}
}


/***************************************************************
defined in XXXXXXXXXXXX.h as:
struct gs_audio_format
{		// same as media_raw_audio_format
	enum format {	// for "format"
		B_GS_U8 = 0x11,			// 128 == mid, 1 == bottom, 255 == top
		B_GS_S16 = 0x2,			// 0 == mid, -32767 == bottom, +32767 == top
		B_GS_F = 0x24,			// 0 == mid, -1.0 == bottom, 1.0 == top
		B_GS_S32 = 0x4			// 0 == mid, 0x80000001 == bottom, 0x7fffffff == top
	};
	float		frame_rate;
	uint32		channel_count;		// 1 or 2, mostly
	uint32		format;				// for compressed formats, go to media_encoded_audio_format
	uint32		byte_order;			// 2 for little endian, 1 for big endian
	size_t		buffer_size;		// size of each buffer -- NOT GUARANTEED
};
***************************************************************/
void
Inspect_Struct_gs_audio_format
	(
	BString & strDetails
,	gs_audio_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[gs_audio_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "frame_rate= " << inValue->frame_rate << g_pNewline;
		strDetails << tabindent << "channel_count= " << inValue->channel_count << g_pNewline;
		strDetails << tabindent << "format= " << inValue->format << g_pNewline;
		strDetails << tabindent << "byte_order= " << inValue->byte_order << g_pNewline;
		strDetails << tabindent << "buffer_size= " << inValue->buffer_size << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The gs_audio_format was NULL.\n";
	}
}


/***************************************************************
defined in GameSoundDefs.h as:
struct gs_attribute
{
		int32		attribute;		//	which attribute
		bigtime_t	duration;		//	how long of time to ramp over for the change
		float		value;			//	where the value stops changing
		uint32		flags;			//	whatever flags are for the attribute
};
***************************************************************/
void
Inspect_Struct_gs_attribute
	(
	BString & strDetails
,	gs_attribute * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[gs_attribute object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "attribute= " << inValue->attribute;
		switch (inValue->attribute)
		{
			case B_GS_NO_ATTRIBUTE:
				strDetails << ", B_GS_NO_ATTRIBUTE\n";
				break;
			case B_GS_MAIN_GAIN:
				strDetails << ", B_GS_MAIN_GAIN\n";
				break;
			case B_GS_CD_THROUGH_GAIN:
				strDetails << ", B_GS_CD_THROUGH_GAIN\n";
				break;
			case B_GS_GAIN:
				strDetails << ", B_GS_GAIN\n";
				break;
			case B_GS_PAN:
				strDetails << ", B_GS_PAN\n";
				break;
			case B_GS_SAMPLING_RATE:
				strDetails << ", B_GS_SAMPLING_RATE\n";
				break;
			case B_GS_LOOPING:
				strDetails << ", B_GS_LOOPING\n";
				break;
			default:
				strDetails << g_pNewline;
		}

		strDetails << tabindent << "duration= " << inValue->duration << g_pNewline;
		strDetails << tabindent << "value= " << inValue->value << g_pNewline;
		strDetails << tabindent << "flags= " << inValue->flags << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The gs_attribute was NULL.\n";
	}
}


/***************************************************************
defined in GameSoundDefs.h as:
struct gs_attribute_info
{
		int32		attribute;
		float		granularity;
		float		minimum;
		float		maximum;
};
***************************************************************/
void
Inspect_Struct_gs_attribute_info
	(
	BString & strDetails
,	gs_attribute_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[gs_attribute_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "attribute= " << inValue->attribute;
		switch (inValue->attribute)
		{
			case B_GS_NO_ATTRIBUTE:
				strDetails << ", B_GS_NO_ATTRIBUTE\n";
				break;
			case B_GS_MAIN_GAIN:
				strDetails << ", B_GS_MAIN_GAIN\n";
				break;
			case B_GS_CD_THROUGH_GAIN:
				strDetails << ", B_GS_CD_THROUGH_GAIN\n";
				break;
			case B_GS_GAIN:
				strDetails << ", B_GS_GAIN\n";
				break;
			case B_GS_PAN:
				strDetails << ", B_GS_PAN\n";
				break;
			case B_GS_SAMPLING_RATE:
				strDetails << ", B_GS_SAMPLING_RATE\n";
				break;
			case B_GS_LOOPING:
				strDetails << ", B_GS_LOOPING\n";
				break;
			default:
				strDetails << g_pNewline;
		}

		strDetails << tabindent << "granularity= " << inValue->granularity << g_pNewline;
		strDetails << tabindent << "minimum= " << inValue->minimum << g_pNewline;
		strDetails << tabindent << "maximum= " << inValue->maximum << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The gs_attribute_info was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
typedef struct pattern {
		uint8		data[8];
} pattern;
***************************************************************/
void
Inspect_Struct_pattern
	(
	BString & strDetails
,	pattern * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[pattern object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		for (int i(0); i < 8; ++i)
		{
			strDetails << (inValue->data[i] & (0x80) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x40) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x20) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x10) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x08) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x04) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x02) ? "1" : "0");
			strDetails << (inValue->data[i] & (0x01) ? "1\n" : "0\n");
		}
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The pattern was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h
typedef struct rgb_color {
	uint8		red;
	uint8		green;
	uint8		blue;
	uint8		alpha;
} rgb_color;
***************************************************************/
void
Inspect_Struct_rgb_color
	(
	BString & strDetails
,	rgb_color * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	if (inIndent >= 0)
	{
		for (int32 i (0); i < inIndent; i++)
		{
			tabindent << g_pIndentation;
		}
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[rgb_color struct, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "red= " << (unsigned int) inValue->red << g_pNewline;
		strDetails << tabindent << "green= " << (unsigned int) inValue->green << g_pNewline;
		strDetails << tabindent << "blue= " << (unsigned int) inValue->blue << g_pNewline;
		strDetails << tabindent << "alpha= " << (unsigned int) inValue->alpha << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The rgb_color was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
typedef struct color_map {
	int32				id;
	rgb_color			color_list[256];
	uint8				inversion_map[256];
	uint8				index_map[32768];
} color_map;
***************************************************************/
void
Inspect_Struct_color_map
	(
	BString & strDetails
,	color_map * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[color_map object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "id= " << inValue->id << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The color_map was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
typedef struct overlay_rect_limits {
	uint16				horizontal_alignment;
	uint16				vertical_alignment;
	uint16				width_alignment;
	uint16				height_alignment;
	uint16				min_width;
	uint16				max_width;
	uint16				min_height;
	uint16				max_height;
	uint32				reserved[8];
} overlay_rect_limits;
***************************************************************/
void
Inspect_Struct_overlay_rect_limits
	(
	BString & strDetails
,	overlay_rect_limits * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[overlay_rect_limits object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "horizontal_alignment= " << inValue->horizontal_alignment << g_pNewline;
		strDetails << tabindent << "vertical_alignment= " << inValue->vertical_alignment << g_pNewline;
		strDetails << tabindent << "width_alignment= " << inValue->width_alignment << g_pNewline;
		strDetails << tabindent << "height_alignment= " << inValue->height_alignment << g_pNewline;
		strDetails << tabindent << "min_width= " << inValue->min_width << g_pNewline;
		strDetails << tabindent << "max_width= " << inValue->max_width << g_pNewline;
		strDetails << tabindent << "min_height= " << inValue->min_height << g_pNewline;
		strDetails << tabindent << "max_height= " << inValue->max_height << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The overlay_rect_limits was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
typedef struct overlay_restrictions {
	overlay_rect_limits	source;
	overlay_rect_limits	destination;
	float				min_width_scale;
	float				max_width_scale;
	float				min_height_scale;
	float				max_height_scale;
	uint32				reserved[8];
} overlay_restrictions;
***************************************************************/
void
Inspect_Struct_overlay_restrictions
	(
	BString & strDetails
,	overlay_restrictions * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[overlay_restrictions object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		Inspect_Struct_overlay_rect_limits (strDetails, &(inValue->source), inIndent, "source: ");
		Inspect_Struct_overlay_rect_limits (strDetails, &(inValue->destination), inIndent, "destination: ");
		strDetails << tabindent << "min_width_scale= " << inValue->min_width_scale << g_pNewline;
		strDetails << tabindent << "max_width_scale= " << inValue->max_width_scale << g_pNewline;
		strDetails << tabindent << "min_height_scale= " << inValue->min_height_scale << g_pNewline;
		strDetails << tabindent << "max_height_scale= " << inValue->max_height_scale << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The overlay_restrictions was NULL.\n";
	}
}


/***************************************************************
defined in GraphicsDefs.h as:
struct screen_id { int32 id; };
***************************************************************/
void
Inspect_Struct_screen_id
	(
	BString & strDetails
,	screen_id * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[screen_id object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "id= " << inValue->id;
		if (B_MAIN_SCREEN_ID.id == inValue->id)
			strDetails << ", B_MAIN_SCREEN_ID";
		
		strDetails << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The screen_id was NULL.\n";
	}
}


/***************************************************************
defined in image.h as:
typedef struct {
	image_id	id;					
	image_type	type;				
	int32		sequence;			
	int32		init_order;			
	void		(*init_routine)();
	void		(*term_routine)();
	dev_t		device;				
	ino_t		node;
	char        name[MAXPATHLEN];  
	void		*text;	
	void		*data;
	int32		text_size;	
	int32		data_size;	
} image_info;
***************************************************************/
void
Inspect_Struct_image_info
	(
	BString & strDetails
,	image_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[image_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "id= " << inValue->id << g_pNewline;
		Inspect_Enum_image_type (strDetails, inValue->type, inIndent, "type: ");
		strDetails << tabindent << "sequence= " << inValue->sequence << g_pNewline;
		strDetails << tabindent << "init_order= " << inValue->init_order << g_pNewline;
		strDetails << tabindent << "device= " << inValue->device << g_pNewline;
		strDetails << tabindent << "node= " << inValue->node << g_pNewline;
		BString str (inValue->name, MAXPATHLEN);
		strDetails << tabindent << "name= " << str.String () << g_pNewline;
		strDetails << tabindent << "text_size= " << inValue->text_size << g_pNewline;
		strDetails << tabindent << "data_size= " << inValue->data_size << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The image_info was NULL.\n";
	}
}


/***************************************************************
defined in InterfaceDefs.h as:
struct key_info {
	uint32	modifiers;
	uint8	key_states[16];
};
***************************************************************/
void
Inspect_Struct_key_info
	(
	BString & strDetails
,	key_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[key_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;
	if (NULL != inValue)
	{
		GetHexString (hexbuf, inValue->modifiers);
		strDetails << tabindent << "modifiers= (" << hexbuf << "), ";

		if (inValue->modifiers & B_SHIFT_KEY)
			strDetails << "B_SHIFT_KEY, ";

		if (inValue->modifiers & B_COMMAND_KEY)
			strDetails << "B_COMMAND_KEY, ";

		if (inValue->modifiers & B_CONTROL_KEY)
			strDetails << "B_CONTROL_KEY, ";

		if (inValue->modifiers & B_CAPS_LOCK)
			strDetails << "B_CAPS_LOCK, ";

		if (inValue->modifiers & B_SCROLL_LOCK)
			strDetails << "B_SCROLL_LOCK, ";

		if (inValue->modifiers & B_NUM_LOCK)
			strDetails << "B_NUM_LOCK, ";

		if (inValue->modifiers & B_OPTION_KEY)
			strDetails << "B_OPTION_KEY, ";

		if (inValue->modifiers & B_MENU_KEY)
			strDetails << "B_MENU_KEY, ";

		if (inValue->modifiers & B_LEFT_SHIFT_KEY)
			strDetails << "B_LEFT_SHIFT_KEY, ";

		if (inValue->modifiers & B_RIGHT_SHIFT_KEY)
			strDetails << "B_RIGHT_SHIFT_KEY, ";

		if (inValue->modifiers & B_LEFT_COMMAND_KEY)
			strDetails << "B_LEFT_COMMAND_KEY, ";

		if (inValue->modifiers & B_RIGHT_COMMAND_KEY)
			strDetails << "B_RIGHT_COMMAND_KEY, ";

		if (inValue->modifiers & B_LEFT_CONTROL_KEY)
			strDetails << "B_LEFT_CONTROL_KEY, ";

		if (inValue->modifiers & B_RIGHT_CONTROL_KEY)
			strDetails << "B_RIGHT_CONTROL_KEY, ";

		if (inValue->modifiers & B_LEFT_OPTION_KEY)
			strDetails << "B_LEFT_OPTION_KEY, ";

		if (inValue->modifiers & B_RIGHT_OPTION_KEY)
			strDetails << "B_RIGHT_OPTION_KEY, ";
		
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;


//TODO
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The key_info was NULL.\n";
	}
}


/***************************************************************
defined in InterfaceDefs.h as:
struct key_map {
		uint32	version;
		uint32	caps_key;
		uint32	scroll_key;
		uint32	num_key;
		uint32	left_shift_key;
		uint32	right_shift_key;
		uint32	left_command_key;
		uint32	right_command_key;
		uint32	left_control_key;
		uint32	right_control_key;
		uint32	left_option_key;
		uint32	right_option_key;
		uint32	menu_key;
		uint32	lock_settings;
		int32	control_map[128];
		int32	option_caps_shift_map[128];
		int32	option_caps_map[128];
		int32	option_shift_map[128];
		int32	option_map[128];
		int32	caps_shift_map[128];
		int32	caps_map[128];
		int32	shift_map[128];
		int32	normal_map[128];
		int32	acute_dead_key[32];
		int32	grave_dead_key[32];
		int32	circumflex_dead_key[32];
		int32	dieresis_dead_key[32];
		int32	tilde_dead_key[32];
		uint32	acute_tables;
		uint32	grave_tables;
		uint32	circumflex_tables;
		uint32	dieresis_tables;
		uint32	tilde_tables;
};
***************************************************************/
void
Inspect_Struct_key_map
	(
	BString & strDetails
,	key_map * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[key_map object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "version= " << inValue->version << g_pNewline;
		strDetails << tabindent << "caps_key= " << inValue->caps_key << g_pNewline;
		strDetails << tabindent << "scroll_key= " << inValue->scroll_key << g_pNewline;
		strDetails << tabindent << "num_key= " << inValue->num_key << g_pNewline;
		strDetails << tabindent << "left_shift_key= " << inValue->left_shift_key << g_pNewline;
		strDetails << tabindent << "right_shift_key= " << inValue->right_shift_key << g_pNewline;
		strDetails << tabindent << "left_command_key= " << inValue->left_command_key << g_pNewline;
		strDetails << tabindent << "right_command_key= " << inValue->right_command_key << g_pNewline;
		strDetails << tabindent << "left_control_key= " << inValue->left_control_key << g_pNewline;
		strDetails << tabindent << "right_control_key= " << inValue->right_control_key << g_pNewline;
		strDetails << tabindent << "left_option_key= " << inValue->left_option_key << g_pNewline;
		strDetails << tabindent << "right_option_key= " << inValue->right_option_key << g_pNewline;
		strDetails << tabindent << "menu_key= " << inValue->menu_key << g_pNewline;
		strDetails << tabindent << "lock_settings= " << inValue->lock_settings << g_pNewline;
		strDetails << tabindent << "control_map= not implemented in this release\n";
		strDetails << tabindent << "option_caps_shift_map= not implemented in this release\n";
		strDetails << tabindent << "option_caps_map= not implemented in this release\n";
		strDetails << tabindent << "option_shift_map= not implemented in this release\n";
		strDetails << tabindent << "option_map= not implemented in this release\n";
		strDetails << tabindent << "caps_shift_map= not implemented in this release\n";
		strDetails << tabindent << "caps_map= not implemented in this release\n";
		strDetails << tabindent << "shift_map= not implemented in this release\n";
		strDetails << tabindent << "normal_map= not implemented in this release\n";
		strDetails << tabindent << "acute_dead_key= not implemented in this release\n";
		strDetails << tabindent << "grave_dead_key= not implemented in this release\n";
		strDetails << tabindent << "circumflex_dead_key= not implemented in this release\n";
		strDetails << tabindent << "dieresis_dead_key= not implemented in this release\n";
		strDetails << tabindent << "tilde_dead_key= not implemented in this release\n";
		strDetails << tabindent << "acute_tables= " << inValue->acute_tables << g_pNewline;
		strDetails << tabindent << "grave_tables= " << inValue->grave_tables << g_pNewline;
		strDetails << tabindent << "circumflex_tables= " << inValue->circumflex_tables << g_pNewline;
		strDetails << tabindent << "dieresis_tables= " << inValue->dieresis_tables << g_pNewline;
		strDetails << tabindent << "tilde_tables= " << inValue->tilde_tables << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The key_map was NULL.\n";
	}
}


/***************************************************************
defined in InterfaceDefs.h as:
struct mouse_map {
	uint32	left;
	uint32	right;
	uint32	middle;
};
***************************************************************/
void
Inspect_Struct_mouse_map
	(
	BString & strDetails
,	mouse_map * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[mouse_map object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		for (int i = 0; i < 3; ++i)
		{
	 		strDetails << tabindent << "button[" << i << "]=" << inValue->button[i] << g_pNewline;
		}
	}
	else
	{
		strDetails << tabindent << "The mouse_map was NULL.\n";
	}
}


/***************************************************************
defined in InterfaceDefs.h as:
struct scroll_bar_info {
	bool	proportional;
	bool	double_arrows;
	int32	knob;
	int32	min_knob_size;
};
***************************************************************/
void
Inspect_Struct_scroll_bar_info
	(
	BString & strDetails
,	scroll_bar_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[scroll_bar_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "proportional= " << (inValue->proportional ? pTrue : pFalse);
		strDetails << tabindent << "double_arrows= " << (inValue->double_arrows ? pTrue : pFalse);
		strDetails << tabindent << "knob= " << inValue->knob << g_pNewline;
		strDetails << tabindent << "min_knob_size= " << inValue->min_knob_size << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The scroll_bar_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaAddOn.h as:
struct dormant_node_info {
	dormant_node_info();
	~dormant_node_info();

	media_addon_id addon;
	int32 flavor_id;
	char name[B_MEDIA_NAME_LENGTH];
private:
	char reserved[128];
};
***************************************************************/
void
Inspect_Struct_dormant_node_info
	(
	BString & strDetails
,	dormant_node_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[dormant_node_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "addon= " << inValue->addon << g_pNewline;
		strDetails << tabindent << "flavor_id= " << inValue->flavor_id << g_pNewline;
		BString str (inValue->name, B_MEDIA_NAME_LENGTH);
		strDetails << tabindent << "name= " << str.String () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The dormant_node_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaAddOn.h as:
struct flavor_info {
	char *				name;
	char *				info;
	uint64				kinds;			// node_kind
	uint32				flavor_flags;
	int32				internal_id;	// For BMediaAddOn internal use
	int32				possible_count;	// 0 for "any number"

	int32				in_format_count;	// for BufferConsumer kinds
	uint32				in_format_flags;	// set to 0
	const media_format *	in_formats;

	int32				out_format_count;	// for BufferProducer kinds
	uint32				out_format_flags;	// set to 0
	const media_format *	out_formats;

	uint32				_reserved_[16];

private:
	flavor_info & operator=(const flavor_info & other);
};
***************************************************************/
void
Inspect_Struct_flavor_info
	(
	BString & strDetails
,	flavor_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[flavor_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		if (inValue->name != NULL)
			strDetails << tabindent << "name= " << inValue->name << g_pNewline;

		if (inValue->info != NULL)
			strDetails << tabindent << "info= " << inValue->info << g_pNewline;

		GetHexString (hexbuf, (intptr_t) inValue->kinds);
		strDetails << tabindent << "kinds= (" << hexbuf << "), ";
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		GetHexString (hexbuf, (intptr_t) inValue->flavor_flags);
		strDetails << tabindent << "flavor_flags= (" << hexbuf << "), ";

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;


		strDetails << tabindent << "internal_id= " << inValue->internal_id << g_pNewline;
		strDetails << tabindent << "possible_count= " << inValue->possible_count << g_pNewline;
		strDetails << tabindent << "in_format_count= " << inValue->in_format_count << g_pNewline;
		strDetails << tabindent << "in_format_flags= " << inValue->in_format_flags << g_pNewline;
		GetHexString (hexbuf, (intptr_t) inValue->in_formats);
		strDetails << tabindent << "in_formats= pointer value is: " << hexbuf << g_pNewline;
		strDetails << tabindent << "out_format_count= " << inValue->out_format_count << g_pNewline;
		strDetails << tabindent << "out_format_flags= " << inValue->out_format_flags << g_pNewline;
		GetHexString (hexbuf, (intptr_t) inValue->out_formats);
		strDetails << tabindent << "out_formats= pointer value is: " << hexbuf << g_pNewline;
		strDetails << tabindent << "_reserved= not implemented in this release\n";
	}
	else
	{
		strDetails << tabindent << "The flavor_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaAddOn.h as:
struct dormant_flavor_info : public flavor_info, public BFlattenable {

		dormant_flavor_info();
virtual	~dormant_flavor_info();
		dormant_flavor_info(const dormant_flavor_info &);
		dormant_flavor_info& operator=(const dormant_flavor_info &);
		dormant_flavor_info& operator=(const flavor_info &);

		dormant_node_info	node_info;

		void set_name(const char * in_name);
		void set_info(const char * in_info);
		void add_in_format(const media_format & in_format);
		void add_out_format(const media_format & out_format);

virtual	bool		IsFixedSize() const;
virtual	type_code	TypeCode() const;
virtual	ssize_t		FlattenedSize() const;
virtual	status_t	Flatten(void *buffer, ssize_t size) const;
virtual	status_t	Unflatten(type_code c, const void *buf, ssize_t size);

private:
		void assign_atoms(const flavor_info & that);
};
***************************************************************/
void
Inspect_Struct_dormant_flavor_info
	(
	BString & strDetails
,	dormant_flavor_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[dormant_flavor_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The dormant_flavor_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_destination {
	media_destination(port_id, int32);
	media_destination(const media_destination & clone);
	media_destination & operator=(const media_destination & clone);
	media_destination();
	~media_destination();
	port_id port;	// can be different from media_node.port
	int32 id;
***************************************************************/
void
Inspect_Struct_media_destination
	(
	BString & strDetails
,	media_destination * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_destination object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "port= " << inValue->port << g_pNewline;
		strDetails << tabindent << "id= " << inValue->id << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_destination was NULL.\n";
	}
}


/***************************************************************
defined in Mediadefs.h as:
struct media_source {
	media_source(port_id, int32);
	media_source(const media_source & clone);
	media_source & operator=(const media_source & clone);
	media_source();
	~media_source();
	port_id port;	// must be the same as media_node.port	for owner
	int32 id;
***************************************************************/
void
Inspect_Struct_media_source
	(
	BString & strDetails
,	media_source * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_source object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "port= " << inValue->port << g_pNewline;
		strDetails << tabindent << "id= " << inValue->id << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_source was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_raw_audio_format {
	enum {						// for "format"
		B_AUDIO_FLOAT = 0x24,	// 0 == mid, -1.0 == bottom, 1.0 == top (the preferred format for non-game audio)
		B_AUDIO_INT = 0x4,		// 0 == mid, 0x80000001 == bottom, 0x7fffffff == top (all >16-bit formats, left-adjusted)
		B_AUDIO_SHORT = 0x2,	// 0 == mid, -32767 == bottom, +32767 == top
		B_AUDIO_UCHAR = 0x11,	// 128 == mid, 1 == bottom, 255 == top (discouraged but supported format)
		B_AUDIO_CHAR = 0x1,		// 0 == mid, -127 == bottom, +127 == top (not officially supported format)
		B_AUDIO_SIZE_MASK = 0xf
	};							// we guarantee that (format&0xf) == sizeof(sample) for raw formats

	float		frame_rate;
	uint32		channel_count;		// 1 or 2, mostly
	uint32		format;				// for compressed formats, go to media_encoded_audio_format
	uint32		byte_order;			// 2 for little endian (B_MEDIA_LITTLE_ENDIAN), 1 for big endian (B_MEDIA_BIG_ENDIAN)
	size_t		buffer_size;		// size of each buffer

static media_multi_audio_format wildcard;
};
***************************************************************/
void
Inspect_Struct_media_raw_audio_format
	(
	BString & strDetails
,	media_raw_audio_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_raw_audio_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "frame_rate= " << inValue->frame_rate << g_pNewline;
		strDetails << tabindent << "channel_count= " << inValue->channel_count << g_pNewline;
		strDetails << tabindent << "format= " << inValue->format << g_pNewline;
		strDetails << tabindent << "byte_order= " << inValue->byte_order << g_pNewline;
		strDetails << tabindent << "buffer_size= " << inValue->buffer_size << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_raw_audio_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_audio_header {
	// please put actual data at the end
	int32		_reserved_[16];		// gotta have something
};
***************************************************************/
void
Inspect_Struct_media_audio_header
	(
	BString & strDetails
,	media_audio_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_audio_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "_reserved_= not implemented in this release\n";
	}
	else
	{
		strDetails << tabindent << "The media_audio_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_multi_audio_info {
	uint32		channel_mask;		//	bitmask
	int16		valid_bits;			//	if < 32, for B_AUDIO_INT
	uint16		matrix_mask;		//	each of these bits may mean more than one channel

	uint32		_reserved_b[3];
};
***************************************************************/
void
Inspect_Struct_media_multi_audio_info
	(
	BString & strDetails
,	media_multi_audio_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_multi_audio_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		GetHexString (hexbuf, (intptr_t) inValue->channel_mask);
		strDetails << tabindent << "channel_mask= (" << hexbuf << "), " << inValue->channel_mask << g_pNewline;
		strDetails << tabindent << "valid_bits= " << inValue->valid_bits << g_pNewline;
		GetHexString (hexbuf, (intptr_t) inValue->matrix_mask);
		strDetails << tabindent << "matrix_mask= (" << hexbuf << "), " << inValue->matrix_mask << g_pNewline;
		strDetails << tabindent << "_reserved_b[0]= " << inValue->_reserved_b[1] << g_pNewline;
		strDetails << tabindent << "_reserved_b[1]= " << inValue->_reserved_b[1] << g_pNewline;
		strDetails << tabindent << "_reserved_b[2]= " << inValue->_reserved_b[2] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_multi_audio_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_encoded_audio_format {
	enum audio_encoding {
		B_ANY
	};
	media_raw_audio_format	output;
	audio_encoding			encoding;

	float					bit_rate;		// BIT rate, not byte rate
	size_t					frame_size;

	media_multi_audio_info	multi_info;

	uint32					_reserved_[3];

static media_encoded_audio_format wildcard;
};
***************************************************************/
void
Inspect_Struct_media_encoded_audio_format
	(
	BString & strDetails
,	media_encoded_audio_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_encoded_audio_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		GetHexString (hexbuf, (intptr_t) inValue->encoding);
		strDetails << tabindent << "encoding= (" << hexbuf << "), ";

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		strDetails << tabindent << "bit_rate= " << inValue->bit_rate << g_pNewline;
		strDetails << tabindent << "frame_size= " << inValue->frame_size << g_pNewline;

		strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;
		strDetails << tabindent << "_reserved_[2]= " << inValue->_reserved_[2] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_encoded_audio_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_encoded_audio_header {
	// please put actual data at the end 
	int32		_reserved_0[14];	// gotta have something
	uint32		buffer_flags;		// B_MEDIA_KEY_FRAME for key buffers (ADPCM etc)
	uchar		unused_mask;		// mask of unused bits for the last byte of data
	uchar		_reserved_2[3];

};
***************************************************************/
void
Inspect_Struct_media_encoded_audio_header
	(
	BString & strDetails
,	media_encoded_audio_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_encoded_audio_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "_reserved_0= not implemented in this release\n";
		strDetails << tabindent << "buffer_flags= " << inValue->buffer_flags << g_pNewline;
		strDetails << tabindent << "unused_mask= " << inValue->unused_mask << g_pNewline;

		strDetails << tabindent << "_reserved_2[0]= " << inValue->_reserved_2[0] << g_pNewline;
		strDetails << tabindent << "_reserved_2[1]= " << inValue->_reserved_2[1] << g_pNewline;
		strDetails << tabindent << "_reserved_2[2]= " << inValue->_reserved_2[2] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_encoded_audio_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_video_display_info {
	color_space	format;
	uint32		line_width;
	uint32		line_count;		// total of all interlace fields 
	uint32		bytes_per_row;	// bytes_per_row is in format, not header, because it's part of SetBuffers
	uint32		pixel_offset;	// (in pixels) ... These are offsets from the start of the buffer ... 
	uint32		line_offset;	// (in lines) ... to the start of the field. Think "buffer == framebuffer" ... 
								// ... when the window displaying the active field moves on screen. 
	uint32		flags;
	uint32		_reserved_[3];
static media_video_display_info wildcard;
};
***************************************************************/
void
Inspect_Struct_media_video_display_info
	(
	BString & strDetails
,	media_video_display_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_video_display_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		Inspect_Enum_color_space (strDetails, inValue->format, inIndent, "format= ");
		strDetails << tabindent << "line_width= " << inValue->line_width << g_pNewline;
		strDetails << tabindent << "line_count= " << inValue->line_count << g_pNewline;
		strDetails << tabindent << "bytes_per_row= " << inValue->bytes_per_row << g_pNewline;
		strDetails << tabindent << "pixel_offset= " << inValue->pixel_offset << g_pNewline;
		strDetails << tabindent << "line_offset= " << inValue->line_offset << g_pNewline;
		
		GetHexString (hexbuf, (intptr_t) inValue->flags);
		strDetails << tabindent << "flags= (" << hexbuf << "), " << hexbuf << g_pNewline;

		strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;
		strDetails << tabindent << "_reserved_[2]= " << inValue->_reserved_[2] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_video_display_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_raw_video_format {
	float		field_rate;
	uint32		interlace;		// how many fields per frame -- 1 means progressive (non-interlaced)
	uint32		first_active;	// 0, typically (wildcard, or "don't care")
	uint32		last_active;	// line_count-1, if first_active is 0.
	uint32		orientation;	// B_VIDEO_TOP_LEFT_RIGHT is preferred
	// PIXEL aspect ratio; not active area aspect ratio...
	uint16		pixel_width_aspect;		// 1:1 has 1 here, 4:3 has 4 here
	uint16		pixel_height_aspect;	// 1:1 has 1 here, 4:3 has 3 here

	media_video_display_info	display;

static media_raw_video_format wildcard;
};
***************************************************************/
void
Inspect_Struct_media_raw_video_format
	(
	BString & strDetails
,	media_raw_video_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_raw_video_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "field_rate= " << inValue->field_rate << g_pNewline;
		strDetails << tabindent << "interlace= " << inValue->interlace << g_pNewline;
		strDetails << tabindent << "first_active= " << inValue->first_active << g_pNewline;
		strDetails << tabindent << "last_active= " << inValue->last_active << g_pNewline;
		strDetails << tabindent << "orientation= " << inValue->orientation << g_pNewline;
		strDetails << tabindent << "pixel_width_aspect= " << inValue->pixel_width_aspect << g_pNewline;
		strDetails << tabindent << "pixel_height_aspect= " << inValue->pixel_height_aspect << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_raw_video_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_video_header {
	uint32		_reserved_[12];		// at the top to push used data to the end
	float		field_gamma;
	uint32		field_sequence;		// sequence since start of capture -- may roll over if machine is on for a LONG time
	uint16		field_number;		// 0 .. {interlace-1}; F1 == 0 ("odd"), F2 == 1 ("even")
	uint16		pulldown_number;	// 0..2 for pulldown duplicated sequence
	uint16		first_active_line;	// the NTSC/PAL line number (1-based) of the first line in this field
	uint16		line_count;			// number of active lines in buffer
};
***************************************************************/
void
Inspect_Struct_media_video_header
	(
	BString & strDetails
,	media_video_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_video_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "_reserved_= not implemented in this release\n";
		strDetails << tabindent << "field_gamma= " << inValue->field_gamma << g_pNewline;
		strDetails << tabindent << "field_sequence= " << inValue->field_sequence << g_pNewline;
		strDetails << tabindent << "field_number= " << inValue->field_number << g_pNewline;
		strDetails << tabindent << "pulldown_number= " << inValue->pulldown_number << g_pNewline;
		strDetails << tabindent << "first_active_line= " << inValue->first_active_line << g_pNewline;
		strDetails << tabindent << "line_count= " << inValue->line_count << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_video_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_encoded_video_format {
	enum video_encoding {
		B_ANY
	};
	media_raw_video_format	output;				// set unknowns to wildcard
	float					avg_bit_rate;
	float					max_bit_rate;
	video_encoding			encoding;
	size_t					frame_size;
	int16					forward_history;	//	maximum forward memory required by algorithm
	int16					backward_history;	//	maximum backward memory required by algorithm

	uint32					_reserved_[3];		//	can't grow more than this

static media_encoded_video_format wildcard;
};
***************************************************************/
void
Inspect_Struct_media_encoded_video_format
	(
	BString & strDetails
,	media_encoded_video_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_encoded_video_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "avg_bit_rate= " << inValue->avg_bit_rate << g_pNewline;
		strDetails << tabindent << "max_bit_rate= " << inValue->max_bit_rate << g_pNewline;
		strDetails << tabindent << "encoding= " << inValue->encoding;
		strDetails << g_pNewline;
		strDetails << tabindent << "frame_size= " << inValue->frame_size << g_pNewline;
		strDetails << tabindent << "forward_history= " << inValue->forward_history << g_pNewline;
		strDetails << tabindent << "backward_history= " << inValue->backward_history << g_pNewline;
		
		strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;
		strDetails << tabindent << "_reserved_[2]= " << inValue->_reserved_[2] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_encoded_video_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_encoded_video_header {
	// please put actual data at the end
	int32		_reserved_1[9];		// gotta have something... 

	uint32		field_flags;		//	B_MEDIA_KEY_FRAME

	int16		forward_history;	// forward memory required by this buffer (0 for key frames)
	int16		backward_history;	// backward memory required by this buffer (0 for key frames)
	uchar		unused_mask;		// mask of unused bits for the last byte of data
	uchar		_reserved_2[3];
	float		field_gamma;
	uint32		field_sequence;		// sequence since start of capture
	uint16		field_number;		// 0 .. {interlace-1};  F1 == 0, F2 == 1
	uint16		pulldown_number;	// 0..2 for pulldown duplicated sequence
	uint16		first_active_line;	// 0 or 1, typically, but could be 10 or 11 for full-NTSC formats
	uint16		line_count;			// number of actual lines in buffer
};
***************************************************************/
void
Inspect_Struct_media_encoded_video_header
	(
	BString & strDetails
,	media_encoded_video_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_encoded_video_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "_reserved_1[0]= " << inValue->_reserved_1[0] << g_pNewline;
		strDetails << tabindent << "_reserved_1[1]= " << inValue->_reserved_1[1] << g_pNewline;
		strDetails << tabindent << "_reserved_1[2]= " << inValue->_reserved_1[2] << g_pNewline;
		strDetails << tabindent << "_reserved_1[3]= " << inValue->_reserved_1[3] << g_pNewline;
		strDetails << tabindent << "_reserved_1[4]= " << inValue->_reserved_1[4] << g_pNewline;
		strDetails << tabindent << "_reserved_1[5]= " << inValue->_reserved_1[5] << g_pNewline;
		strDetails << tabindent << "_reserved_1[6]= " << inValue->_reserved_1[6] << g_pNewline;
		strDetails << tabindent << "_reserved_1[7]= " << inValue->_reserved_1[7] << g_pNewline;
		strDetails << tabindent << "_reserved_1[8]= " << inValue->_reserved_1[8] << g_pNewline;

		strDetails << tabindent << "field_flags= " << inValue->field_flags;
		if (B_MEDIA_KEY_FRAME == inValue->field_flags)
		{
			strDetails << ", B_MEDIA_KEY_FRAME";
		}
		strDetails << g_pNewline;
		strDetails << tabindent << "forward_history= " << inValue->forward_history << g_pNewline;
		strDetails << tabindent << "backward_history= " << inValue->backward_history << g_pNewline;
		GetHexString (hexbuf, (intptr_t) inValue->unused_mask);
		strDetails << tabindent << "unused_mask= (" << hexbuf << "), " << inValue->unused_mask << g_pNewline;

		strDetails << tabindent << "_reserved_2[0]= " << inValue->_reserved_2[0] << g_pNewline;
		strDetails << tabindent << "_reserved_2[1]= " << inValue->_reserved_2[1] << g_pNewline;
		strDetails << tabindent << "_reserved_2[2]= " << inValue->_reserved_2[2] << g_pNewline;

		strDetails << tabindent << "field_gamma= " << inValue->field_gamma << g_pNewline;
		strDetails << tabindent << "field_sequence= " << inValue->field_sequence << g_pNewline;
		strDetails << tabindent << "field_number= " << inValue->field_number << g_pNewline;
		strDetails << tabindent << "pulldown_number= " << inValue->pulldown_number << g_pNewline;
		strDetails << tabindent << "first_active_line= " << inValue->first_active_line << g_pNewline;
		strDetails << tabindent << "line_count= " << inValue->line_count << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_encoded_video_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_multistream_format {
	enum {
		B_ANY = 0,
		B_VID = 1,					// raw raw_video/raw_audio buffers
		B_AVI,
		B_MPEG1,
		B_MPEG2,
		B_QUICKTIME,
		B_PRIVATE = 90000,
		B_FIRST_USER_TYPE = 100000	// user formats >= 100000
	};
	float		avg_bit_rate;		// 8 * byte rate, on average
	float		max_bit_rate;		// 8 * byte rate, tops
	uint32		avg_chunk_size;		// == max_chunk_size for fixed-size chunks
	uint32		max_chunk_size;		// max buffer size
	enum {
		B_HEADER_HAS_FLAGS = 0x1,	// are flags important?
		B_CLEAN_BUFFERS = 0x2,		// each buffer represents an integral number of "frames"
		B_HOMOGENOUS_BUFFERS = 0x4	// a buffer has only one format in it
	};
	uint32		flags;
	int32		format;
	uint32		_reserved_[2];

	struct vid_info {
		float frame_rate;
		uint16 width;
		uint16 height;
		color_space space;

		float sampling_rate;
		uint32 sample_format;
		uint16 byte_order;
		uint16 channel_count;
	};
	struct avi_info {
		uint32 us_per_frame;
		uint16 width;
		uint16 height;
		uint16 _reserved_;
		uint16 type_count;
		media_type types[5];
	};

	union {
		vid_info	vid;
		avi_info	avi;
	}			u;

static media_multistream_format wildcard;
};
***************************************************************/
void
Inspect_Struct_media_multistream_format
	(
	BString & strDetails
,	media_multistream_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_multistream_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "avg_bit_rate= " << inValue->avg_bit_rate << g_pNewline;
		strDetails << tabindent << "max_bit_rate= " << inValue->max_bit_rate << g_pNewline;
		strDetails << tabindent << "avg_chunk_size= " << inValue->avg_chunk_size << g_pNewline;
		strDetails << tabindent << "max_chunk_size= " << inValue->max_chunk_size << g_pNewline;

		GetHexString (hexbuf, (intptr_t) inValue->flags);
		strDetails << tabindent << "flags= (" << hexbuf << ", " << inValue->flags << "), ";
#ifndef CLUE_ON_ZETA_HACK
		if (media_multistream_format::B_HEADER_HAS_FLAGS & inValue->flags)
		{
			strDetails << "B_HEADER_HAS_FLAGS, ";
		}
		if (media_multistream_format::B_CLEAN_BUFFERS & inValue->flags)
		{
			strDetails << "B_CLEAN_BUFFERS, ";
		}
		if (media_multistream_format::B_HOMOGENOUS_BUFFERS & inValue->flags)
		{
			strDetails << "B_HOMOGENOUS_BUFFERS, ";
		}
#endif
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		strDetails << tabindent << "format= " << inValue->format;
#ifndef CLUE_ON_ZETA_HACK
		if (inValue->format >= media_multistream_format::B_FIRST_USER_TYPE)
		{
			strDetails << ", B_FIRST_USER_TYPE range\n";
		}
		else if (inValue->format >= media_multistream_format::B_PRIVATE)
		{
			strDetails << ", B_PRIVATE range\n";
		}
		else
		{
			switch (inValue->format)
			{
			case media_multistream_format::B_ANY:
				strDetails << ", B_ANY\n";
				break;
			case media_multistream_format::B_VID:
				strDetails << ", B_VID\n";
				break;
			case media_multistream_format::B_AVI:
				strDetails << ", B_AVI\n";
				break;
			case media_multistream_format::B_MPEG1:
				strDetails << ", B_MPEG1\n";
				break;
			case media_multistream_format::B_MPEG2:
				strDetails << ", B_MPEG2\n";
				break;
			case media_multistream_format::B_QUICKTIME:
				strDetails << ", B_QUICKTIME\n";
				break;
			default:
				strDetails << ", unknown\n";
				break;
			}
		}
#endif

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;
		
		strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_multistream_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_multistream_header {
	uint32 _reserved_[14];
	uchar	unused_mask;			// mask of unused bits for the last byte of data
	uchar	_reserved_2[3];
	enum {
		B_MASTER_HEADER = 0x1,		// for master stream header data in buffer
		B_SUBSTREAM_HEADER = 0x2,	// for sub-stream header data in buffer
		B_COMPLETE_BUFFER = 0x4		// data is an integral number of "frames"
	};
	uint32 	flags;
};
***************************************************************/
void
Inspect_Struct_media_multistream_header
	(
	BString & strDetails
,	media_multistream_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_multistream_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "_reserved_= not implemented in this release\n";
		GetHexString (hexbuf, (intptr_t) inValue->unused_mask);
		strDetails << tabindent << "unused_mask= (" << hexbuf << ") " << inValue->unused_mask << g_pNewline;

		strDetails << tabindent << "_reserved_2[0]= " << inValue->_reserved_2[0] << g_pNewline;
		strDetails << tabindent << "_reserved_2[1]= " << inValue->_reserved_2[1] << g_pNewline;
		strDetails << tabindent << "_reserved_2[2]= " << inValue->_reserved_2[2] << g_pNewline;

		uint32 aUint32 (inValue->flags);
		GetHexString (hexbuf, aUint32);
		strDetails << tabindent << "flags= (" << hexbuf << ", " << aUint32 << "), ";
#ifndef CLUE_ON_ZETA_HACK
		if (media_multistream_header::B_MASTER_HEADER & aUint32)
		{
			strDetails << "B_MASTER_HEADER, ";
		}
		if (media_multistream_header::B_SUBSTREAM_HEADER & aUint32)
		{
			strDetails << "B_SUBSTREAM_HEADER, ";
		}
		if (media_multistream_header::B_COMPLETE_BUFFER & aUint32)
		{
			strDetails << "B_COMPLETE_BUFFER, ";
		}
#endif
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_multistream_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
// typically, a field of 0 means "anything" or "wildcard"
struct media_format {	// no more than 192 bytes
	media_type						type;
	type_code						user_data_type;
	uchar							user_data[48];
	uint32							_reserved_[3];
	uint16							require_flags;			//	media_format_flags
	uint16							deny_flags;				//	media_format_flags

	private:

	void *							meta_data;
	int32							meta_data_size;
	area_id							meta_data_area;
	area_id							use_area;
	team_id							team;
	void *							thisPtr;

	public:

	union {
		media_multi_audio_format	raw_audio;
		media_raw_video_format		raw_video;
		media_multistream_format	multistream;
		media_encoded_audio_format	encoded_audio;
		media_encoded_video_format	encoded_video;
		char						_reserved_[96];	 // pad to 96 bytes
	} u;
	
	bool 			IsVideo() const		{ return (type==B_MEDIA_ENCODED_VIDEO)||(type==B_MEDIA_RAW_VIDEO); };
	uint32  		Width() const		{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.line_width:u.raw_video.display.line_width; };
	uint32 			Height() const		{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.line_count:u.raw_video.display.line_count; };
	color_space  	ColorSpace() const	{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.format:u.raw_video.display.format; };
	uint32 & 		Width()				{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.line_width:u.raw_video.display.line_width; };
	uint32 & 		Height()			{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.line_count:u.raw_video.display.line_count; };
	color_space & 	ColorSpace()		{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.output.display.format:u.raw_video.display.format; };

	bool 			IsAudio() const		{ return (type==B_MEDIA_ENCODED_AUDIO)||(type==B_MEDIA_RAW_AUDIO); };
	uint32 			AudioFormat() const	{ return (type==B_MEDIA_ENCODED_AUDIO)?u.encoded_audio.output.format:u.raw_audio.format; };
	uint32 & 		AudioFormat()		{ return (type==B_MEDIA_ENCODED_AUDIO)?u.encoded_audio.output.format:u.raw_audio.format; };

	uint32			Encoding() const	{ return (type==B_MEDIA_ENCODED_VIDEO)?u.encoded_video.encoding:(type==B_MEDIA_ENCODED_AUDIO)?u.encoded_audio.encoding:(type==B_MEDIA_MULTISTREAM)?u.multistream.format:0UL; }

	bool			Matches(const media_format *otherFormat) const;
	void			SpecializeTo(const media_format *otherFormat);

	status_t		SetMetaData(const void *data, size_t size);
	const void *	MetaData() const;
	int32			MetaDataSize() const;

					media_format();
					media_format(const media_format &other);
					~media_format();
	media_format &	operator=(const media_format & clone);
};
***************************************************************/
void
Inspect_Struct_media_format
	(
	BString & strDetails
,	media_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		Inspect_Enum_media_type (strDetails, inValue->type, inIndent, "type= ");

		strDetails << tabindent << "user_data= not implemented in this release\n";

		strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;
		strDetails << tabindent << "_reserved_[2]= " << inValue->_reserved_[2] << g_pNewline;

		strDetails << tabindent << "require_flags= " << inValue->require_flags << g_pNewline;
		strDetails << tabindent << "deny_flags= " << inValue->deny_flags << g_pNewline;
		strDetails << tabindent << "IsVideo= " << inValue->IsVideo () << g_pNewline;
		strDetails << tabindent << "Width= " << inValue->Width () << g_pNewline;
		strDetails << tabindent << "Height= " << inValue->Height () << g_pNewline;
		Inspect_Enum_color_space (strDetails, inValue->ColorSpace (), inIndent, "ColorSpace= ");

		strDetails << tabindent << "IsAudio= " << inValue->IsAudio () << g_pNewline;
		strDetails << tabindent << "AudioFormat= " << inValue->AudioFormat () << g_pNewline;
		strDetails << tabindent << "encoding= " << inValue->Encoding () << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_seek_tag {
	char data[16];
};
***************************************************************/
void
Inspect_Struct_media_seek_tag
	(
	BString & strDetails
,	media_seek_tag * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_seek_tag object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		for (int i = 0; i < 16; i++)
		{
			strDetails << tabindent << "data[" << i << "]= " << inValue->data[i] << g_pNewline;
		}
	}
	else
	{
		strDetails << tabindent << "The media_seek_tag was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_header_time_code {
	int8	type;		//	See TimeCode.h; don't use the "DEFAULT" value
	int8	_reserved;
	int8	hours;
	int8	minutes;
	int8	seconds;
	int8	frames;
	int16	subframes;	//	-1 if not available
};
***************************************************************/
void
Inspect_Struct_media_header_time_code
	(
	BString & strDetails
,	media_header_time_code * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_header_time_code object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "type= " << inValue->type << g_pNewline;
		strDetails << tabindent << "_reserved= " << inValue->_reserved << g_pNewline;
		strDetails << tabindent << "hours= " << inValue->hours << g_pNewline;
		strDetails << tabindent << "minutes= " << inValue->minutes << g_pNewline;
		strDetails << tabindent << "seconds= " << inValue->seconds << g_pNewline;
		strDetails << tabindent << "frames= " << inValue->frames << g_pNewline;
		strDetails << tabindent << "subframes= " << inValue->subframes << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_header_time_code was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_header {		// Broadcast() fills in fields marked with "//+"
	media_type		type;			// what kind of data (for union)
	media_buffer_id buffer;			//+ what buffer does this header go with? 
	int32			destination;	//+ what 'socket' is this intended for?
	media_node_id	time_source;	// node that encoded start_time
	uint32			_deprecated_;	// used to be change_tag
	uint32			size_used;		// size within buffer that is used
	bigtime_t		start_time;		// performance time
	area_id			owner;			//+ buffer owner info area
	enum {
		B_SEEK_TAG = 'TRST',			// user data type of the codec seek
									// protocol. size of seek tag is 16 bytes
		B_TIME_CODE = 'TRTC'			//	user data is media_header_time_code
	};
	type_code		user_data_type;
	uchar			user_data[64];	// user_data_type indicates what this is
	uint32			_reserved_[2];

	off_t			file_pos;		// where in a file this data came from
	size_t			orig_size;		// and how big it was.  if unused, zero out

	uint32			data_offset;	// offset within buffer (already reflected in Data())

	union {
		media_audio_header			raw_audio;
		media_video_header			raw_video;
		media_multistream_header	multistream;
		media_encoded_audio_header	encoded_audio;
		media_encoded_video_header	encoded_video;
		char						_reserved_[64];		// pad to 64 bytes
	} u;
};
***************************************************************/
void
Inspect_Struct_media_header
	(
	BString & strDetails
,	media_header * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_header object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		Inspect_Enum_media_type (strDetails, inValue->type, inIndent, "type= ");

		strDetails << tabindent << "buffer= " << inValue->buffer << g_pNewline;
		strDetails << tabindent << "destination= " << inValue->destination << g_pNewline;
		strDetails << tabindent << "time_source= " << inValue->time_source << g_pNewline;
		strDetails << tabindent << "_deprecated_= " << inValue->_deprecated_ << g_pNewline;
		strDetails << tabindent << "size_used= " << inValue->size_used << g_pNewline;
		strDetails << tabindent << "start_time= " << inValue->start_time << g_pNewline;
		strDetails << tabindent << "owner= " << inValue->owner << g_pNewline;
		strDetails << tabindent << "user_data_type= " << inValue->user_data_type << g_pNewline;
		strDetails << tabindent << "user_data[]= not implemented in this release\n";
		//FIXME update for Haiku
		//strDetails << tabindent << "_reserved_[0]= " << inValue->_reserved_[0] << g_pNewline;
		//strDetails << tabindent << "_reserved_[1]= " << inValue->_reserved_[1] << g_pNewline;

		strDetails << tabindent << "file_pos= " << inValue->file_pos << g_pNewline;
		strDetails << tabindent << "orig_size= " << inValue->orig_size << g_pNewline;
		strDetails << tabindent << "data_offset= " << inValue->data_offset << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_header was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_file_format_id {
	ino_t	node;
	dev_t	device;
	uint32	internal_id;
};
***************************************************************/
void
Inspect_Struct_media_file_format_id
	(
	BString & strDetails
,	media_file_format_id * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_file_format_id object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "node= " << inValue->node << g_pNewline;
		strDetails << tabindent << "device= " << inValue->device << g_pNewline;
		strDetails << tabindent << "internal_id= " << inValue->internal_id << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_file_format_id was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_file_format {
		enum {	// flags
			B_READABLE = 0x1,
			B_WRITABLE = 0x2,
			B_PERFECTLY_SEEKABLE = 0x4,
			B_IMPERFECTLY_SEEKABLE = 0x8,
			B_KNOWS_RAW_VIDEO = 0x10,
			B_KNOWS_RAW_AUDIO = 0x20,
			B_KNOWS_MIDI = 0x40,
			B_KNOWS_ENCODED_VIDEO = 0x80,
			B_KNOWS_ENCODED_AUDIO = 0x100,
			B_KNOWS_OTHER = 0x1000000,	// clipping, text, control, ...
			B_KNOWS_ANYTHING = 0x2000000
		};
	uint32	capabilities;			// can this format support audio, video, etc
	media_file_format_id	id;		// opaque id used to construct a BMediaFile
	media_format_family family;		// one of the family enums
	int32	version;				// 100 for 1.0

	uint32		_reserved_[25];

	char	mime_type[64];			// eg: "video/quicktime", "audio/aiff", etc
	char	pretty_name[64];		// eg: "QuickTime File Format"
	char	short_name[32];			// eg: "quicktime", "avi", "mpeg"
	char	file_extension[8];		// eg: "mov", "avi", "mpg"
	char	reserved[88];
};
***************************************************************/
void
Inspect_Struct_media_file_format
	(
	BString & strDetails
,	media_file_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_file_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "capabilities= " << inValue->capabilities << g_pNewline;
		Inspect_Struct_media_file_format_id (strDetails, &inValue->id, inIndent, "id= ");
		Inspect_Enum_media_format_family (strDetails, inValue->family, inIndent, "family= ");
		strDetails << tabindent << "version= " << inValue->version << g_pNewline;
		strDetails << tabindent << "_reserved_[]= not implemented in this release\n";

		BString str (inValue->mime_type, 64);
		strDetails << tabindent << "mime_type= " << str.String () << g_pNewline;
		str.SetTo (inValue->pretty_name, 64);
		strDetails << tabindent << "pretty_name= " << str.String () << g_pNewline;
		str.SetTo (inValue->short_name, 32);
		strDetails << tabindent << "short_name= " << str.String () << g_pNewline;
		str.SetTo (inValue->file_extension, 8);
		strDetails << tabindent << "file_extension= " << str.String () << g_pNewline;
		strDetails << tabindent << "reserved[]= not implemented in this release\n";
	}
	else
	{
		strDetails << tabindent << "The media_file_format was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_encode_info {
	uint32		flags;					// B_MEDIA_KEY_FRAME, set before every use
	int32		used_data_size;			// data size used by other tracks
										// add output size used by this encoder
	bigtime_t	start_time;				// us from start of file
	bigtime_t	time_to_encode;			// 0 - hurry up, B_INFINITE_TIMEOUT - don't care
	int32		_pad[22];
	void		*file_format_data;		// file format specific info
	size_t		file_format_data_size;
	void		*codec_data;			// codec specific info
	size_t		codec_data_size;
	
	media_encode_info();
};
***************************************************************/
void
Inspect_Struct_media_encode_info
	(
	BString & strDetails
,	media_encode_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_encode_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_encode_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct encode_parameters {
	float		quality;				// 0.0-1.0 , 1.0 is high quality
	int32		avg_field_size;			// in bytes
	int32		max_field_size;			// in bytes
	int32		_pad[27];
	void		*user_data;				// codec specific info
	size_t		user_data_size;
};
***************************************************************/
void
Inspect_Struct_encode_parameters
	(
	BString & strDetails
,	encode_parameters * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[encode_parameters object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The encode_parameters was NULL.\n";
	}
}


/***************************************************************
defined in MediaDefs.h as:
struct media_decode_info {
	bigtime_t	time_to_decode;			// 0 - hurry up, B_INFINITE_TIMEOUT - don't care
	int32		_pad[26];
	void		*file_format_data;		// file format specific info
	size_t		file_format_data_size;
	void		*codec_data;			// codec specific info
	size_t		codec_data_size;
	
	media_decode_info();
};
***************************************************************/
void
Inspect_Struct_media_decode_info
	(
	BString & strDetails
,	media_decode_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_decode_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_decode_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaNode.h as:
struct media_input {
	media_input();
	~media_input();
	media_node node;
	media_source source;
	media_destination destination;
	media_format format;
	char name[B_MEDIA_NAME_LENGTH];
private:
	uint32 _reserved_media_input_[4];
};
***************************************************************/
void
Inspect_Struct_media_input
	(
	BString & strDetails
,	media_input * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_input object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_input was NULL.\n";
	}
}


/***************************************************************
defined in MediaNode.h as:
struct media_output {
	media_output();
	~media_output();
	media_node node;
	media_source source;
	media_destination destination;
	media_format format;
	char name[B_MEDIA_NAME_LENGTH];
private:
	uint32 _reserved_media_output_[4];
};
***************************************************************/
void
Inspect_Struct_media_output
	(
	BString & strDetails
,	media_output * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_output object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_output was NULL.\n";
	}
}


/***************************************************************
defined in MediaNode.h as:
struct live_node_info {
	live_node_info();
	~live_node_info();
	media_node node;
	BPoint hint_point;
	char name[B_MEDIA_NAME_LENGTH];
private:
	char reserved[160];
};
***************************************************************/
void
Inspect_Struct_live_node_info
	(
	BString & strDetails
,	live_node_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[live_node_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The live_node_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaNode.h as:
struct media_request_info
{
	enum what_code
	{
		B_SET_VIDEO_CLIPPING_FOR = 1, 
		B_REQUEST_FORMAT_CHANGE, 
		B_SET_OUTPUT_ENABLED,
		B_SET_OUTPUT_BUFFERS_FOR,

		B_FORMAT_CHANGED = 4097
	};
	what_code what;
	int32 change_tag;
	status_t status;
	int32 cookie;
	void * user_data;
	media_source source;
	media_destination destination;
	media_format format;
	uint32 _reserved_[32];
};
***************************************************************/
void
Inspect_Struct_media_request_info
	(
	BString & strDetails
,	media_request_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_request_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_request_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaNode.h as:
struct media_node_attribute
{
	enum {
		B_R40_COMPILED = 1,		//	has this attribute if compiled using R4.0 headers
		B_USER_ATTRIBUTE_NAME = 0x1000000,
		B_FIRST_USER_ATTRIBUTE
	};
	uint32		what;
	uint32		flags;			//	per attribute
	int64		data;			//	per attribute
};
***************************************************************/
void
Inspect_Struct_media_node_attribute
	(
	BString & strDetails
,	media_node_attribute * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_node_attribute object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_node_attribute was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
struct media_codec_info {
	char	pretty_name[96];   // eg: "SuperSqueeze Encoder by Foo Inc"
	char	short_name[32];    // eg: "supersqueeze"
	
	int32	id;                // opaque id passed to BMediaFile::CreateTrack
	int32	sub_id;
	
	int32	pad[63];
};
***************************************************************/
void
Inspect_Struct_media_codec_info
	(
	BString & strDetails
,	media_codec_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_codec_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_codec_info was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint8 data[16];
} GUID;
***************************************************************/
void
Inspect_Struct_GUID
	(
	BString & strDetails
,	GUID * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[GUID object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The GUID was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	int32 format;
} media_beos_description;
***************************************************************/
void
Inspect_Struct_media_beos_description
	(
	BString & strDetails
,	media_beos_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_beos_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_beos_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 codec;
	uint32 vendor;
} media_quicktime_description;
***************************************************************/
void
Inspect_Struct_media_quicktime_description
	(
	BString & strDetails
,	media_quicktime_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_quicktime_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_quicktime_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 codec;
} media_avi_description;
***************************************************************/
void
Inspect_Struct_media_avi_description
	(
	BString & strDetails
,	media_avi_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_avi_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_avi_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 id;
} media_avr_description;
***************************************************************/
void
Inspect_Struct_media_avr_description
	(
	BString & strDetails
,	media_avr_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_avr_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_avr_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	GUID guid;
} media_asf_description;
***************************************************************/
void
Inspect_Struct_media_asf_description
	(
	BString & strDetails
,	media_asf_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_asf_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_asf_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 id;
} media_mpeg_description;
***************************************************************/
void
Inspect_Struct_media_mpeg_description
	(
	BString & strDetails
,	media_mpeg_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_mpeg_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_mpeg_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 codec;
} media_wav_description;
***************************************************************/
void
Inspect_Struct_media_wav_description
	(
	BString & strDetails
,	media_wav_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_wav_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_wav_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 codec;
} media_aiff_description;
***************************************************************/
void
Inspect_Struct_media_aiff_description
	(
	BString & strDetails
,	media_aiff_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_aiff_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_aiff_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct {
	uint32 file_format;
	uint32 codec;
} media_misc_description;
***************************************************************/
void
Inspect_Struct_media_misc_description
	(
	BString & strDetails
,	media_misc_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_misc_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_misc_description was NULL.\n";
	}
}


/***************************************************************
defined in MediaFormats.h as:
typedef struct _media_format_description {
#if defined(__cplusplus)
	_media_format_description();
	~_media_format_description();
	_media_format_description(const _media_format_description & other);
	_media_format_description & operator=(const _media_format_description & other);
#endif
	media_format_family family;
	uint32 _reserved_[3];
	union {
		media_beos_description beos;
		media_quicktime_description quicktime;
		media_avi_description avi;
		media_asf_description asf;
		media_mpeg_description mpeg;
		media_wav_description wav;
		media_aiff_description aiff;
		media_misc_description misc;
		media_avr_description avr;
		uint32 _reserved_[12];
	} u;
} media_format_description;
***************************************************************/
void
Inspect_Struct_media_format_description
	(
	BString & strDetails
,	media_format_description * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_format_description object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_format_description was NULL.\n";
	}
}


/***************************************************************
defined in Node.h as:
struct node_ref {
						node_ref();
						node_ref(const node_ref &ref);

	bool				operator==(const node_ref &ref) const;
	bool				operator!=(const node_ref &ref) const;
	node_ref &			operator=(const node_ref &ref);

	dev_t				device;
	ino_t				node;
};
***************************************************************/
void
Inspect_Struct_node_ref
	(
	BString & strDetails
,	node_ref * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[node_ref object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The node_ref was NULL.\n";
	}
}


/***************************************************************
defined in PropertyInfo.h as:
struct compound_type {
	struct field_pair {
		char		*name;			// name of entry in message
		type_code	type;			// type_code of entry in message
	};
	field_pair	pairs[5];
};
***************************************************************/
void
Inspect_Struct_compound_type
	(
	BString & strDetails
,	compound_type * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[compound_type object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The compound_type was NULL.\n";
	}
}


/***************************************************************
defined in PropertyInfo.h as:
struct property_info {
	char			*name;
	uint32			commands[10];
	uint32			specifiers[10];
	char			*usage;
	uint32			extra_data;
	uint32			types[10];
	compound_type	ctypes[3];
	uint32			_reserved[10];
};
***************************************************************/
void
Inspect_Struct_property_info
	(
	BString & strDetails
,	property_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[property_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The property_info was NULL.\n";
	}
}


/***************************************************************
defined in PropertyInfo.h as:
struct value_info {
	char			*name;
	uint32			value;
	value_kind		kind;
	char			*usage;
	uint32			extra_data;
	uint32			_reserved[10];
};
***************************************************************/
void
Inspect_Struct_value_info
	(
	BString & strDetails
,	value_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[value_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The value_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct area_info {
	area_id		area;
	char		name[B_OS_NAME_LENGTH];
	size_t		size;
	uint32		lock;
	uint32		protection;
	team_id		team;
	uint32		ram_size;
	uint32		copy_count;
	uint32		in_count;
	uint32		out_count;
	void		*address;
} area_info;
***************************************************************/
void
Inspect_Struct_area_info
	(
	BString & strDetails
,	area_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[area_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The area_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct port_info {
	port_id		port;
	team_id		team;
	char		name[B_OS_NAME_LENGTH];
	int32		capacity; // queue depth
	int32		queue_count; // # msgs waiting to be read
	int32		total_count; // total # msgs read so far
} port_info;
***************************************************************/
void
Inspect_Struct_port_info
	(
	BString & strDetails
,	port_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[port_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The port_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct sem_info {
	sem_id 		sem;
	team_id 	team;
	char		name[B_OS_NAME_LENGTH];
	int32		count;
	thread_id 	latest_holder;
} sem_info;
***************************************************************/
void
Inspect_Struct_sem_info
	(
	BString & strDetails
,	sem_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[sem_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The sem_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct  {
	thread_id		thread;
	team_id			team;
	char			name[B_OS_NAME_LENGTH];
	thread_state	state;
	int32			priority;
	sem_id			sem;
	bigtime_t		user_time;
	bigtime_t		kernel_time;
	void			*stack_base;
	void			*stack_end;
} thread_info;
***************************************************************/
void
Inspect_Struct_thread_info
	(
	BString & strDetails
,	thread_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[thread_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The thread_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct {
	bigtime_t		user_time;
	bigtime_t		kernel_time;
} team_usage_info;
***************************************************************/
void
Inspect_Struct_team_usage_info
	(
	BString & strDetails
,	team_usage_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[team_usage_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The team_usage_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct {
	team_id			team;
	int32			image_count;
	int32			thread_count;
	int32			area_count;
	thread_id		debugger_nub_thread;
	port_id			debugger_nub_port;

	int32           argc;      // number of args on the command line
	char            args[64];  // abbreviated command line args
	uid_t        	uid;
	gid_t        	gid;
} team_info;
***************************************************************/
void
Inspect_Struct_team_info
	(
	BString & strDetails
,	team_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[team_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The team_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct {
	bigtime_t		active_time;		// # usec doing useful work since boot
} cpu_info;
***************************************************************/
void
Inspect_Struct_cpu_info
	(
	BString & strDetails
,	cpu_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[cpu_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The cpu_info was NULL.\n";
	}
}


/***************************************************************
defined in OS.h as:
typedef struct {
	machine_id	   id;							// unique machine ID
	bigtime_t	   boot_time;					// time of boot (# usec since 1/1/70)

	int32		   cpu_count;					// # of cpus
	enum cpu_types cpu_type;					// type of cpu
	int32		   cpu_revision;				// revision # of cpu
	cpu_info	   cpu_infos[B_MAX_CPU_COUNT];	// info about individual cpus
	int64          cpu_clock_speed;	 			// processor clock speed (Hz)
	int64          bus_clock_speed;				// bus clock speed (Hz)
	enum platform_types platform_type;          // type of machine we're on

	int32		  max_pages;					// total # physical pages
	int32		  used_pages;					// # physical pages in use
	int32		  page_faults;					// # of page faults
	int32		  max_sems;						// maximum # semaphores
	int32		  used_sems;					// # semaphores in use
	int32		  max_ports;					// maximum # ports
	int32		  used_ports;					// # ports in use
	int32		  max_threads;					// maximum # threads
	int32		  used_threads;					// # threads in use
	int32		  max_teams;					// maximum # teams
	int32		  used_teams;					// # teams in use

	char		  kernel_name [B_FILE_NAME_LENGTH];		// name of kernel
	char          kernel_build_date[B_OS_NAME_LENGTH];	// date kernel built
	char          kernel_build_time[B_OS_NAME_LENGTH];	// time kernel built 
	int64         kernel_version;             	// version of this kernel

	bigtime_t	  _busy_wait_time;				// reserved for Be
	int32         pad[4];   	               	// just in case... 
} system_info;
***************************************************************/
void
Inspect_Struct_system_info
	(
	BString & strDetails
,	system_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[system_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		//FIXME update for Haiku
		//strDetails << tabindent << "id= " << inValue->id[0] << inValue->id[1] << g_pNewline;
		strDetails << tabindent << "boot_time= " << inValue->boot_time << g_pNewline;
		strDetails << tabindent << "cpu_count= " << inValue->cpu_count << g_pNewline;
		//Inspect_Enum_cpu_type (strDetails, inValue->cpu_type, inIndent, "  |  cpu_type= ");
		//strDetails << tabindent << "cpu_revision= " << inValue->cpu_revision << g_pNewline;
		//strDetails << tabindent << "cpu_clock_speed= " << inValue->cpu_clock_speed << g_pNewline;
		//strDetails << tabindent << "bus_clock_speed= " << inValue->bus_clock_speed << g_pNewline;
		//Inspect_Enum_platform_type (strDetails, inValue->platform_type, inIndent, "  |  platform_type= ");
		strDetails << tabindent << "max_pages= " << inValue->max_pages << g_pNewline;
		strDetails << tabindent << "used_pages= " << inValue->used_pages << g_pNewline;
		strDetails << tabindent << "page_faults= " << inValue->page_faults << g_pNewline;
		strDetails << tabindent << "max_sems= " << inValue->max_sems << g_pNewline;
		strDetails << tabindent << "used_sems= " << inValue->used_sems << g_pNewline;
		strDetails << tabindent << "max_ports= " << inValue->max_ports << g_pNewline;
		strDetails << tabindent << "used_ports= " << inValue->used_ports << g_pNewline;
		strDetails << tabindent << "max_threads= " << inValue->max_threads << g_pNewline;
		strDetails << tabindent << "used_threads= " << inValue->used_threads << g_pNewline;
		strDetails << tabindent << "max_teams= " << inValue->max_teams << g_pNewline;
		strDetails << tabindent << "used_teams= " << inValue->used_teams << g_pNewline;
		strDetails << tabindent << "kernel_name= " << inValue->kernel_name << g_pNewline;
		strDetails << tabindent << "kernel_build_date= " << inValue->kernel_build_date << g_pNewline;
		strDetails << tabindent << "kernel_build_time= " << inValue->kernel_build_time << g_pNewline;
		strDetails << tabindent << "kernel_version= " << inValue->kernel_version << g_pNewline;
		//strDetails << tabindent << "_busy_wait_time= " << inValue->_busy_wait_time << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The system_info was NULL.\n";
	}
}



/***************************************************************
defined in TimedEventQueue.h as:
struct media_timed_event {
					media_timed_event();
					media_timed_event(bigtime_t inTime, int32 inType);
					media_timed_event(bigtime_t inTime, int32 inType,
						void *inPointer, uint32 inCleanup);
					media_timed_event(
						bigtime_t inTime, int32 inType,
						void *inPointer, uint32 inCleanup,
						int32 inData, int64 inBigdata,
						char *inUserData, size_t dataSize = 0);
					
					media_timed_event(const media_timed_event & clone);
					void operator=(const media_timed_event & clone);
					
					~media_timed_event();
					
	bigtime_t		event_time;
	int32			type;
	void *			pointer;
	uint32			cleanup;
	int32			data;
	int64			bigdata;
	char			user_data[64];
	uint32			_reserved_media_timed_event_[8];
};
***************************************************************/
void
Inspect_Struct_media_timed_event
	(
	BString & strDetails
,	media_timed_event * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[media_timed_event object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The media_timed_event was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
struct TranslatorBitmap {
	uint32		magic;		//	B_TRANSLATOR_BITMAP
	BRect		bounds;
	uint32		rowBytes;
	color_space	colors;
	uint32		dataSize;
};	//	data follows, padded to rowBytes
***************************************************************/
void
Inspect_Struct_TranslatorBitmap
	(
	BString & strDetails
,	TranslatorBitmap * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorBitmap object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorBitmap was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
//	This is the standard sound format
//	Note that data is always in big-endian format in the stream!
struct TranslatorSound {
	uint32		magic;		//	B_TRANSLATOR_SOUND
	uint32		channels;	//	Left should always be first
	float		sampleFreq;	//	16 bit linear is assumed
	uint32		numFrames;
};	//	data follows
***************************************************************/
void
Inspect_Struct_TranslatorSound
	(
	BString & strDetails
,	TranslatorSound * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorSound object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorSound was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
struct TranslatorStyledTextRecordHeader {
	uint32		magic;
	uint32		header_size;
	uint32		data_size;
};	//	any number of records
***************************************************************/
void
Inspect_Struct_TranslatorStyledTextRecordHeader
	(
	BString & strDetails
,	TranslatorStyledTextRecordHeader * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorStyledTextRecordHeader object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorStyledTextRecordHeader was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
struct TranslatorStyledTextStreamHeader {
#if defined(__cplusplus)
	enum {
		STREAM_HEADER_MAGIC = 'STXT'
	};
#endif
	TranslatorStyledTextRecordHeader	header;
	int32		version;	// 100
};	//	no data for this header
***************************************************************/
void
Inspect_Struct_TranslatorStyledTextStreamHeader
	(
	BString & strDetails
,	TranslatorStyledTextStreamHeader * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorStyledTextStreamHeader object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorStyledTextStreamHeader was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
struct TranslatorStyledTextTextHeader {
#if defined(__cplusplus)
	enum {
		TEXT_HEADER_MAGIC = 'TEXT'
	};
#endif
	TranslatorStyledTextRecordHeader	header;
	int32		charset;	//	Always write B_UTF8 for now!
};	//	text data follows
***************************************************************/
void
Inspect_Struct_TranslatorStyledTextTextHeader
	(
	BString & strDetails
,	TranslatorStyledTextTextHeader * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorStyledTextTextHeader object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorStyledTextTextHeader was NULL.\n";
	}
}


/***************************************************************
defined in TranslatorFormats.h as:
struct TranslatorStyledTextStyleHeader {
#if defined(__cplusplus)
	enum {
		STYLE_HEADER_MAGIC = 'STYL'
	};
#endif
	TranslatorStyledTextRecordHeader	header;
	uint32		apply_offset;
	uint32		apply_length;
};	//	flattened R3 BTextView style records for preceding text
***************************************************************/
void
Inspect_Struct_TranslatorStyledTextStyleHeader
	(
	BString & strDetails
,	TranslatorStyledTextStyleHeader * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[TranslatorStyledTextStyleHeader object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The TranslatorStyledTextStyleHeader was NULL.\n";
	}
}


/***************************************************************
defined in Region.h as:
// Integer rect used to define a cliping rectangle. All bounds are included
// Moved from DirectWindow.h
typedef struct {
	int32		left;
	int32		top;
	int32		right;
	int32		bottom;
} clipping_rect;
***************************************************************/
void
Inspect_Struct_clipping_rect
	(
	BString & strDetails
,	clipping_rect * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[clipping_rect object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The clipping_rect was NULL.\n";
	}
}


/***************************************************************
defined in TextView.h as:
struct text_run {
	int32			offset;		// byte offset of first character of run
	BFont			font;		// font of run
	rgb_color		color;		// color of run
};
***************************************************************/
void
Inspect_Struct_text_run
	(
	BString & strDetails
,	text_run * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[text_run object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The text_run was NULL.\n";
	}
}


/***************************************************************
defined in TextView.h as:
struct text_run_array {
	int32			count;		// number of text runs
	text_run		runs[1];	// array of count number of runs
};
***************************************************************/
void
Inspect_Struct_text_run_array
	(
	BString & strDetails
,	text_run_array * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[text_run_array object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The text_run_array was NULL.\n";
	}
}


/***************************************************************
defined in TimeCode.h as:
struct timecode_info {
	timecode_type type;
	int drop_frames;
	int every_nth;
	int except_nth;
	int fps_div;
	char name[32];		// for popup menu etc
	char format[32];	// for sprintf(fmt, h, m, s, f)
	char _reserved_[64];
};
***************************************************************/
void
Inspect_Struct_timecode_info
	(
	BString & strDetails
,	timecode_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[timecode_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The timecode_info was NULL.\n";
	}
}


/***************************************************************
defined in TranslationDefs.h as:
struct translation_format {
	uint32		type;				// B_ASCII_TYPE, ...
	uint32		group;				// B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...
	float		quality;			// format quality 0.0-1.0
	float		capability;			// translator capability 0.0-1.0
	char		MIME[251];			// MIME string 
	char		name[251];			// only descriptive
};
***************************************************************/
void
Inspect_Struct_translation_format
	(
	BString & strDetails
,	translation_format * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[translation_format object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The translation_format was NULL.\n";
	}
}


/***************************************************************
defined in TranslationDefs.h as:
struct translator_info {			// Info about a specific translation
	uint32			type;			// B_ASCII_TYPE, ...
	translator_id	translator;		// Filled in by BTranslationRoster
	uint32			group;			// B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...
	float			quality;		// Quality of format in group 0.0-1.0
	float			capability;		// How much of the format do we do? 0.0-1.0
	char			name[251];
	char			MIME[251];
};
***************************************************************/
void
Inspect_Struct_translator_info
	(
	BString & strDetails
,	translator_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[translator_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
//		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The translator_info was NULL.\n";
	}
}


/***************************************************************
defined in Accelerant.h as
typedef struct {
	uint16	h_res;			// minimum effective change in horizontal pixels, usually 8
	uint16	h_sync_min;		// min/max horizontal sync pulse width in pixels, a multiple of h_res
	uint16	h_sync_max;
	uint16	h_blank_min;	// min/max horizontal blank pulse width in pixels, a multiple of h_res
	uint16	h_blank_max;
	uint16	v_res;			// minimum effective change in vertical lines, usually 1
	uint16	v_sync_min;		// min/max vertical sync pulse width in lines, a multiple of v_res 
	uint16	v_sync_max;
	uint16	v_blank_min;	// min/max vertical blank pulse width in linex, a multiple of v_res
	uint16	v_blank_max;
} display_timing_constraints;
***************************************************************/
void
Inspect_Struct_display_timing_constraints
	(
	BString & strDetails
,	display_timing_constraints * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[display_timing_constraints object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "h_res= " << (uint32) inValue->h_res  << " pixels\n";
		strDetails << tabindent << "h_sync_min= " << (uint32) inValue->h_sync_min << " pixels\n";
		strDetails << tabindent << "h_sync_max= " << (uint32) inValue->h_sync_max << " pixels\n";
		strDetails << tabindent << "h_blank_min= " << (uint32) inValue->h_blank_min << " pixels\n";
		strDetails << tabindent << "h_blank_max= " << (uint32) inValue->h_blank_max << " pixels\n";
		strDetails << tabindent << "v_res= " << (uint32) inValue->v_res << " lines\n";
		strDetails << tabindent << "v_sync_min= " << (uint32) inValue->v_sync_min << " lines\n";
		strDetails << tabindent << "v_sync_max= " << (uint32) inValue->v_sync_max << " lines\n";
		strDetails << tabindent << "v_blank_min= " << (uint32) inValue->v_blank_min << " lines\n";
		strDetails << tabindent << "v_blank_max= " << (uint32) inValue->v_blank_max << " lines\n";
	}
	else
	{
		strDetails << tabindent << "The display_timing_constraints was NULL.\n";
	}
}


/***************************************************************
defined in Accelerant.h as:
typedef struct {
	uint32	pixel_clock;	// kHz
	uint16	h_display;		// in pixels (not character clocks)
	uint16	h_sync_start;
	uint16	h_sync_end;
	uint16	h_total;
	uint16	v_display;		// in lines
	uint16	v_sync_start;
	uint16	v_sync_end;
	uint16	v_total;
	uint32	flags;			// sync polarity, etc.
} display_timing;
***************************************************************/
void
Inspect_Struct_display_timing
	(
	BString & strDetails
,	display_timing * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[display_timing object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "pixel_clock= " << inValue->pixel_clock << " kHz\n";
		strDetails << tabindent << "h_display= " << (uint32) inValue->h_display << " pixels\n";
		strDetails << tabindent << "h_sync_start= " << (uint32) inValue->h_sync_start << g_pNewline;
		strDetails << tabindent << "h_sync_end= " << (uint32) inValue->h_sync_end << g_pNewline;
		strDetails << tabindent << "h_total= " << (uint32) inValue->h_total << g_pNewline;
		strDetails << tabindent << "v_display= " << (uint32) inValue->v_display << " lines\n";
		strDetails << tabindent << "v_sync_start= " << (uint32) inValue->v_sync_start << g_pNewline;
		strDetails << tabindent << "v_sync_end= " << (uint32) inValue->v_sync_end << g_pNewline;
		strDetails << tabindent << "v_total= " << (uint32) inValue->v_total << g_pNewline;

		uint32 aUInt32 (inValue->flags);
		strDetails << tabindent << "flags= (" << aUInt32 << "), ";
		if (B_BLANK_PEDESTAL & aUInt32)
		{
			strDetails << "B_BLANK_PEDESTAL, ";
		}
		if (B_TIMING_INTERLACED & aUInt32)
		{
			strDetails << "B_TIMING_INTERLACED, ";
		}
		if (B_POSITIVE_HSYNC & aUInt32)
		{
			strDetails << "B_POSITIVE_HSYNC, ";
		}
		if (B_POSITIVE_VSYNC & aUInt32)
		{
			strDetails << "B_POSITIVE_VSYNC, ";
		}
		if (B_SYNC_ON_GREEN & aUInt32)
		{
			strDetails << "B_SYNC_ON_GREEN, ";
		}

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The display_timing was NULL.\n";
	}
}


/***************************************************************
defined in Accelerant.h as:
typedef struct {
	display_timing	timing;			// CTRC info
	uint32		space;				// pixel configuration
	uint16		virtual_width;		// in pixels
	uint16		virtual_height;		// in lines
	uint16		h_display_start;	// first displayed pixel in line
	uint16		v_display_start;	// first displayed line
	uint32		flags;				// mode flags
} display_mode;
***************************************************************/
void
Inspect_Struct_display_mode
	(
	BString & strDetails
,	display_mode * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[display_mode object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		display_timing aDT (inValue->timing);
		Inspect_Struct_display_timing (strDetails, &aDT, inIndent, "timing: ");

		strDetails << tabindent << "space= " << inValue->space << g_pNewline;
		strDetails << tabindent << "virtual_width= " << (uint32) inValue->virtual_width << g_pNewline;
		strDetails << tabindent << "virtual_height= " << (uint32) inValue->virtual_height << g_pNewline;
		strDetails << tabindent << "h_display_start= " << (uint32) inValue->h_display_start << g_pNewline;
		strDetails << tabindent << "v_display_start= " << (uint32) inValue->v_display_start << g_pNewline;

		uint32 aUInt32 (inValue->flags);
		strDetails << tabindent << "flags= (" << aUInt32 << "), ";
		if (B_SCROLL & aUInt32)
		{
			strDetails << "B_SCROLL, ";
		}
		if (B_8_BIT_DAC & aUInt32)
		{
			strDetails << "B_8_BIT_DAC, ";
		}
		if (B_HARDWARE_CURSOR & aUInt32)
		{
			strDetails << "B_HARDWARE_CURSOR, ";
		}
		if (B_PARALLEL_ACCESS & aUInt32)
		{
			strDetails << "B_PARALLEL_ACCESS, ";
		}
		if (B_DPMS & aUInt32)
		{
			strDetails << "B_DPMS, ";
		}
		if (B_IO_FB_NA & aUInt32)
		{
			strDetails << "B_IO_FB_NA,";
		}

		strDetails.RemoveLast (",");
		strDetails << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The display_mode was NULL.\n";
	}
}


/***************************************************************
defined in Accelerant.h as:
typedef struct {
	uint32	version;			// structure version number
	char 	name[32];			// a name the user will recognize the device by
	char	chipset[32];		// the chipset used by the device
	char	serial_no[32];		// serial number for the device
	uint32	memory;				// amount of memory on the device, in bytes
	uint32	dac_speed;			// nominal DAC speed, in MHz
} accelerant_device_info;
***************************************************************/
void
Inspect_Struct_accelerant_device_info
	(
	BString & strDetails
,	accelerant_device_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[accelerant_device_info object, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "version= " << inValue->version << g_pNewline;
		strDetails << tabindent << "name= " << inValue->name << g_pNewline;
		strDetails << tabindent << "chipset= " << inValue->chipset << g_pNewline;
		strDetails << tabindent << "serial_no= " << inValue->serial_no << g_pNewline;
		strDetails << tabindent << "memory= " << inValue->memory << g_pNewline;
		strDetails << tabindent << "dac_speed= " << inValue->dac_speed << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The accelerant_device_info was NULL.\n";
	}
}


/***************************************************************
defined in AppFileInfo.h
struct	version_info {
	uint32	major;
	uint32	middle;
	uint32	minor;
	uint32	variety;
	uint32	internal;
	char	short_info[64];
	char	long_info[256];
};
***************************************************************/
void
Inspect_Struct_version_info
	(
	BString & strDetails
,	version_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[version_info struct, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "major= " << inValue->major << g_pNewline;
		strDetails << tabindent << "middle= " << inValue->middle << g_pNewline;
		strDetails << tabindent << "minor= " << inValue->minor << g_pNewline;
		strDetails << tabindent << "variety= " << inValue->variety << g_pNewline;
		strDetails << tabindent << "internal= " << inValue->internal << g_pNewline;
		strDetails << tabindent << "short_info= " << inValue->short_info << g_pNewline;
		strDetails << tabindent << "long_info= " << inValue->long_info << g_pNewline;

	}
	else
	{
		strDetails << tabindent << "The version_info was NULL.\n";
	}
}


/***************************************************************
defined in fs_attr.h as:
typedef struct attr_info
{
	uint32     type;
	off_t      size;
} attr_info;
***************************************************************/
void
Inspect_Struct_attr_info
	(
	BString & strDetails
,	attr_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[attr_info struct, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		strDetails << tabindent << "type= " << inValue->type << g_pNewline;
		strDetails << tabindent << "size= " << inValue->size << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The attr_info was NULL.\n";
	}
}


/***************************************************************
defined in Roster.h
struct app_info {
				app_info();
				~app_info();

	thread_id	thread;
	team_id		team;
	port_id		port;
	uint32		flags;
	entry_ref	ref;
	char		signature[B_MIME_TYPE_LENGTH];
};
***************************************************************/
void
Inspect_Struct_app_info
	(
	BString & strDetails
,	app_info * inValue
,	int32 inIndent
,	const char * pDescription
	)
{
	BString tabindent;
	for (int32 i (0); i < inIndent; i++)
	{
		tabindent << g_pIndentation;
	}

	char hexbuf[20];
	GetHexString (hexbuf, (intptr_t) inValue);
	strDetails << tabindent << pDescription << "[app_info struct, ptr=" << hexbuf << "]\n";
	tabindent << g_pIndentation;

	if (NULL != inValue)
	{
		++inIndent;

		strDetails << tabindent << "thread= " << inValue->thread << g_pNewline;
		strDetails << tabindent << "team= " << inValue->team << g_pNewline;
		strDetails << tabindent << "port= " << inValue->port << g_pNewline;

		GetHexString (hexbuf, (intptr_t) inValue->flags);
		strDetails << tabindent << "flags= (" << hexbuf << ") ";
		switch (B_LAUNCH_MASK & inValue->flags)
		{
			case B_SINGLE_LAUNCH:
				strDetails << "B_SINGLE_LAUNCH,";
				break;
			case B_MULTIPLE_LAUNCH:
				strDetails << "B_MULTIPLE_LAUNCH,";
				break;
			case B_EXCLUSIVE_LAUNCH:
				strDetails << "B_EXCLUSIVE_LAUNCH,";
				break;
		}

		if (B_BACKGROUND_APP & inValue->flags)
		{
			strDetails << "B_BACKGROUND_APP,";
		}
		if (B_ARGV_ONLY & inValue->flags)
		{
			strDetails << "B_ARGV_ONLY,";
		}
		strDetails.RemoveLast (",");
		strDetails << g_pNewline;

		Inspect_Struct_entry_ref (strDetails, &inValue->ref, inIndent, "ref: ");
		strDetails << tabindent << "signature= " << inValue->signature << g_pNewline;
	}
	else
	{
		strDetails << tabindent << "The app_info was NULL.\n";
	}
}





