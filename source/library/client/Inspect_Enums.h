#ifndef INSPECT_ENUMS_H
#define INSPECT_ENUMS_H

#ifndef CLUE_BUILD_H
#include "ClueBuild.h"
#endif

#ifndef _E_MAIL_H
#include <E-mail.h>
#endif

void Inspect_Class_unicode_block (BString &, unicode_block *, int32, const char *);

void Inspect_Flags_mode_t (BString &, mode_t, int32, const char *);

void Inspect_Enum_button_width (BString &, button_width, int32, const char *);
void Inspect_Enum_file_panel_mode (BString &, file_panel_mode, int32, const char *);
void Inspect_Enum_file_panel_button (BString &, file_panel_button, int32, const char *);
void Inspect_Enum_menu_bar_border (BString &, menu_bar_border, int32, const char *);
void Inspect_Enum_window_feel (BString &, window_feel, int32, const char *);
void Inspect_Enum_window_look (BString &, window_look, int32, const char *);
void Inspect_Enum_window_type (BString &, window_type, int32, const char *);
void Inspect_Enum_join_mode (BString &, join_mode, int32, const char *);
void Inspect_Enum_cap_mode (BString &, cap_mode, int32, const char *);
void Inspect_Enum_drawing_mode (BString &, drawing_mode, int32, const char *);
void Inspect_Enum_undo_state (BString &, undo_state, int32, const char *);
void Inspect_Enum_alignment (BString &, alignment, int32, const char *);
void Inspect_Enum_font_direction (BString &, font_direction, int32, const char *);
void Inspect_Enum_font_file_format (BString &, font_file_format, int32, const char *);
void Inspect_Enum_message_source (BString &, message_source, int32, const char *);
void Inspect_Enum_message_delivery (BString &, message_delivery, int32, const char *);
void Inspect_Enum_thumb_style (BString &, thumb_style, int32, const char *);
void Inspect_Enum_orientation (BString &, orientation, int32, const char *);
void Inspect_Enum_hash_mark_location (BString &, hash_mark_location, int32, const char *);
void Inspect_Enum_color_control_layout (BString &, color_control_layout, int32, const char *);
void Inspect_Enum_border_style (BString &, border_style, int32, const char *);
void Inspect_Enum_color_space (BString &, color_space, int32, const char *);
void Inspect_Enum_swap_action (BString &, swap_action, int32, const char *);
void Inspect_Enum_info_location (BString &, info_location, int32, const char *);
void Inspect_Enum_version_kind (BString &, version_kind, int32, const char *);
void Inspect_Enum_media_parameter_flags (BString &, media_parameter_flags, int32, const char *);
void Inspect_Enum_direct_buffer_state (BString &, direct_buffer_state, int32, const char *);
void Inspect_Enum_direct_driver_state (BString &, direct_driver_state, int32, const char *);
void Inspect_Enum_mail_flags (BString &, mail_flags, int32, const char *);
void Inspect_Enum_directory_which (BString &, directory_which, int32, const char *);
void Inspect_Enum_font_metric_mode (BString &, font_metric_mode, int32, const char *);
void Inspect_Enum_gs_attributes (BString &, gs_attributes, int32, const char *);
void Inspect_Enum_buffer_orientation (BString &, buffer_orientation, int32, const char *);
void Inspect_Enum_buffer_layout (BString &, buffer_layout, int32, const char *);
void Inspect_Enum_source_alpha (BString &, source_alpha, int32, const char *);
void Inspect_Enum_alpha_function (BString &, alpha_function, int32, const char *);
void Inspect_Enum_image_type (BString &, image_type, int32, const char *);
void Inspect_Enum_input_method_op (BString &, input_method_op, int32, const char *);
void Inspect_Enum_input_device_type (BString &, input_device_type, int32, const char *);
void Inspect_Enum_input_device_notification (BString &, input_device_notification, int32, const char *);
void Inspect_Enum_list_view_type (BString &, list_view_type, int32, const char *);
void Inspect_Enum_media_type (BString &, media_type, int32, const char *);
void Inspect_Enum_node_kind (BString &, node_kind, int32, const char *);
void Inspect_Enum_video_orientation (BString &, video_orientation, int32, const char *);
void Inspect_Enum_media_flags (BString &, media_flags, int32, const char *);
void Inspect_Enum_media_producer_status (BString &, media_producer_status, int32, const char *);
void Inspect_Enum_media_realtime_flags (BString &, media_realtime_flags, int32, const char *);
void Inspect_Enum_media_frame_flags (BString &, media_frame_flags, int32, const char *);
#ifndef CLUE_ON_ZETA_HACK
	void Inspect_Enum_media_multi_channels (BString &, media_multi_channels, int32, const char *);
#endif
void Inspect_Enum_media_multi_matrix (BString &, media_multi_matrix, int32, const char *);
void Inspect_Enum_media_display_flags (BString &, media_display_flags, int32, const char *);
void Inspect_Enum_media_format_flags (BString &, media_format_flags, int32, const char *);
void Inspect_Enum_media_format_family (BString &, media_format_family, int32, const char *);
void Inspect_Enum_media_seek_type (BString &, media_seek_type, int32, const char *);
void Inspect_Enum_media_file_accept_format_flags (BString &, media_file_accept_format_flags, int32, const char *);
void Inspect_Enum_mpeg_id (BString &, mpeg_id, int32, const char *);
void Inspect_Enum_menu_layout (BString &, menu_layout, int32, const char *);
void Inspect_Enum_filter_result (BString &, filter_result, int32, const char *);
void Inspect_Enum_synth_mode (BString &, synth_mode, int32, const char *);
void Inspect_Enum_midi_axe (BString &, midi_axe, int32, const char *);
void Inspect_Enum_icon_size (BString &, icon_size, int32, const char *);
void Inspect_Enum_thread_state (BString &, thread_state, int32, const char *);
void Inspect_Enum_cpu_type (BString &, cpu_type, int32, const char *);
void Inspect_Enum_value_kind (BString &, value_kind, int32, const char *);
void Inspect_Enum_query_op (BString &, query_op, int32, const char *);
void Inspect_Enum_data_rate (BString &, data_rate, int32, const char *);
void Inspect_Enum_data_bits (BString &, data_bits, int32, const char *);
void Inspect_Enum_stop_bits (BString &, stop_bits, int32, const char *);
void Inspect_Enum_parity_mode (BString &, parity_mode, int32, const char *);
void Inspect_Enum_node_flavor (BString &, node_flavor, int32, const char *);
void Inspect_Enum_interpolation_mode (BString &, interpolation_mode, int32, const char *);
void Inspect_Enum_reverb_mode (BString &, reverb_mode, int32, const char *);
void Inspect_Enum_tab_position (BString &, tab_position, int32, const char *);
void Inspect_Enum_timecode_type (BString &, timecode_type, int32, const char *);
void Inspect_Enum_window_alignment (BString &, window_alignment, int32, const char *);
void Inspect_Enum_B_TRANSLATION_ERROR (BString &, B_TRANSLATION_ERROR, int32, const char *);
void Inspect_Enum_platform_type (BString &, platform_type, int32, const char *);
void Inspect_Enum_alert_type (BString &, alert_type, int32, const char *);
void Inspect_Enum_button_spacing (BString &, button_spacing, int32, const char *);
void Inspect_Enum_TranslatorGroups (BString &, TranslatorGroups, int32, const char *);

#endif //INSPECT_ENUMS_H

