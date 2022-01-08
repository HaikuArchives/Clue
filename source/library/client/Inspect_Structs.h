#ifndef INSPECT_STRUCTS_H
#define INSPECT_STRUCTS_H

void Inspect_Struct_display_timing_constraints(BString&, display_timing_constraints*, int32, const char*);
void Inspect_Struct_display_timing(BString&, display_timing*, int32, const char*);
void Inspect_Struct_display_mode(BString&, display_mode*, int32, const char*);
void Inspect_Struct_accelerant_device_info(BString&, accelerant_device_info*, int32, const char*);
void Inspect_Struct_version_info(BString&, version_info*, int32, const char*);
void Inspect_Struct_attr_info(BString&, attr_info*, int32, const char*);
void Inspect_Struct_app_info(BString&, app_info*, int32, const char*);
void Inspect_Struct_version_info(BString&, version_info*, int32, const char*);
void Inspect_Struct_buffer_clone_info(BString&, buffer_clone_info*, int32, const char*);
void Inspect_Struct_direct_buffer_info(BString&, direct_buffer_info*, int32, const char*);
void Inspect_Struct_mail_pop_account(BString&, mail_pop_account*, int32, const char*);
void Inspect_Struct_mail_notification(BString&, mail_notification*, int32, const char*);
void Inspect_Struct_entry_ref(BString&, entry_ref*, int32, const char*);
void Inspect_Struct_edge_info(BString&, edge_info*, int32, const char*);
void Inspect_Struct_font_height(BString&, font_height*, int32, const char*);
void Inspect_Struct_escapement_delta(BString&, escapement_delta*, int32, const char*);
void Inspect_Struct_tuned_font_info(BString&, tuned_font_info*, int32, const char*);
void Inspect_Struct_gs_audio_format(BString&, gs_audio_format*, int32, const char*);
void Inspect_Struct_gs_attribute(BString&, gs_attribute*, int32, const char*);
void Inspect_Struct_gs_attribute_info(BString&, gs_attribute_info*, int32, const char*);
void Inspect_Struct_pattern(BString&, pattern*, int32, const char*);
void Inspect_Struct_rgb_color(BString&, rgb_color*, int32, const char*);
void Inspect_Struct_color_map(BString&, color_map*, int32, const char*);
void Inspect_Struct_overlay_rect_limits(BString&, overlay_rect_limits*, int32, const char*);
void Inspect_Struct_overlay_restrictions(BString&, overlay_restrictions*, int32, const char*);
void Inspect_Struct_screen_id(BString&, screen_id*, int32, const char*);
void Inspect_Struct_image_info(BString&, image_info*, int32, const char*);
void Inspect_Struct_key_info(BString&, key_info*, int32, const char*);
void Inspect_Struct_key_map(BString&, key_map*, int32, const char*);
void Inspect_Struct_mouse_map(BString&, mouse_map*, int32, const char*);
void Inspect_Struct_scroll_bar_info(BString&, scroll_bar_info*, int32, const char*);
void Inspect_Struct_dormant_node_info(BString&, dormant_node_info*, int32, const char*);
void Inspect_Struct_flavor_info(BString&, flavor_info*, int32, const char*);
void Inspect_Struct_dormant_flavor_info(BString&, dormant_flavor_info*, int32, const char*);
void Inspect_Struct_media_destination(BString&, media_destination*, int32, const char*);
void Inspect_Struct_media_source(BString&, media_source*, int32, const char*);
void Inspect_Struct_media_raw_audio_format(BString&, media_raw_audio_format*, int32, const char*);
void Inspect_Struct_media_audio_header(BString&, media_audio_header*, int32, const char*);
void Inspect_Struct_media_multi_audio_info(BString&, media_multi_audio_info*, int32, const char*);
void Inspect_Struct_media_encoded_audio_format(BString&, media_encoded_audio_format*, int32, const char*);
void Inspect_Struct_media_encoded_audio_header(BString&, media_encoded_audio_header*, int32, const char*);
void Inspect_Struct_media_video_display_info(BString&, media_video_display_info*, int32, const char*);
void Inspect_Struct_media_raw_video_format(BString&, media_raw_video_format*, int32, const char*);
void Inspect_Struct_media_video_header(BString&, media_video_header*, int32, const char*);
void Inspect_Struct_media_encoded_video_format(BString&, media_encoded_video_format*, int32, const char*);
void Inspect_Struct_media_encoded_video_header(BString&, media_encoded_video_header*, int32, const char*);
void Inspect_Struct_media_multistream_format(BString&, media_multistream_format*, int32, const char*);
void Inspect_Struct_media_multistream_header(BString&, media_multistream_header*, int32, const char*);
void Inspect_Struct_media_format(BString&, media_format*, int32, const char*);
void Inspect_Struct_media_seek_tag(BString&, media_seek_tag*, int32, const char*);
void Inspect_Struct_media_header_time_code(BString&, media_header_time_code*, int32, const char*);
void Inspect_Struct_media_header(BString&, media_header*, int32, const char*);
void Inspect_Struct_media_file_format_id(BString&, media_file_format_id*, int32, const char*);
void Inspect_Struct_media_file_format(BString&, media_file_format*, int32, const char*);
void Inspect_Struct_media_encode_info(BString&, media_encode_info*, int32, const char*);
void Inspect_Struct_encode_parameters(BString&, encode_parameters*, int32, const char*);
void Inspect_Struct_media_decode_info(BString&, media_decode_info*, int32, const char*);
void Inspect_Struct_media_input(BString&, media_input*, int32, const char*);
void Inspect_Struct_media_output(BString&, media_output*, int32, const char*);
void Inspect_Struct_live_node_info(BString&, live_node_info*, int32, const char*);
void Inspect_Struct_media_request_info(BString&, media_request_info*, int32, const char*);
void Inspect_Struct_media_node_attribute(BString&, media_node_attribute*, int32, const char*);
void Inspect_Struct_media_codec_info(BString&, media_codec_info*, int32, const char*);
void Inspect_Struct_GUID(BString&, GUID*, int32, const char*);
void Inspect_Struct_media_beos_description(BString&, media_beos_description*, int32, const char*);
void Inspect_Struct_media_quicktime_description(BString&, media_quicktime_description*, int32, const char*);
void Inspect_Struct_media_avi_description(BString&, media_avi_description*, int32, const char*);
void Inspect_Struct_media_avr_description(BString&, media_avr_description*, int32, const char*);
void Inspect_Struct_media_asf_description(BString&, media_asf_description*, int32, const char*);
void Inspect_Struct_media_mpeg_description(BString&, media_mpeg_description*, int32, const char*);
void Inspect_Struct_media_wav_description(BString&, media_wav_description*, int32, const char*);
void Inspect_Struct_media_aiff_description(BString&, media_aiff_description*, int32, const char*);
void Inspect_Struct_media_misc_description(BString&, media_misc_description*, int32, const char*);
void Inspect_Struct_media_format_description(BString&, media_format_description*, int32, const char*);
void Inspect_Struct_node_ref(BString&, node_ref*, int32, const char*);
void Inspect_Struct_compound_type(BString&, compound_type*, int32, const char*);
void Inspect_Struct_property_info(BString&, property_info*, int32, const char*);
void Inspect_Struct_value_info(BString&, value_info*, int32, const char*);
void Inspect_Struct_area_info(BString&, area_info*, int32, const char*);
void Inspect_Struct_port_info(BString&, port_info*, int32, const char*);
void Inspect_Struct_sem_info(BString&, sem_info*, int32, const char*);
void Inspect_Struct_thread_info(BString&, thread_info*, int32, const char*);
void Inspect_Struct_team_usage_info(BString&, team_usage_info*, int32, const char*);
void Inspect_Struct_team_info(BString&, team_info*, int32, const char*);
void Inspect_Struct_cpu_info(BString&, cpu_info*, int32, const char*);
void Inspect_Struct_system_info(BString&, system_info*, int32, const char*);
void Inspect_Struct_media_timed_event(BString&, media_timed_event*, int32, const char*);
void Inspect_Struct_TranslatorBitmap(BString&, TranslatorBitmap*, int32, const char*);
void Inspect_Struct_TranslatorSound(BString&, TranslatorSound*, int32, const char*);
void Inspect_Struct_TranslatorStyledTextRecordHeader(BString&, TranslatorStyledTextRecordHeader*, int32, const char*);
void Inspect_Struct_TranslatorStyledTextStreamHeader(BString&, TranslatorStyledTextStreamHeader*, int32, const char*);
void Inspect_Struct_TranslatorStyledTextTextHeader(BString&, TranslatorStyledTextTextHeader*, int32, const char*);
void Inspect_Struct_TranslatorStyledTextStyleHeader(BString&, TranslatorStyledTextStyleHeader*, int32, const char*);
void Inspect_Struct_clipping_rect(BString&, clipping_rect*, int32, const char*);
void Inspect_Struct_app_info(BString&, app_info*, int32, const char*);
void Inspect_Struct_text_run(BString&, text_run*, int32, const char*);
void Inspect_Struct_text_run_array(BString&, text_run_array*, int32, const char*);
void Inspect_Struct_timecode_info(BString&, timecode_info*, int32, const char*);
void Inspect_Struct_translation_format(BString&, translation_format*, int32, const char*);
void Inspect_Struct_translator_info(BString&, translator_info*, int32, const char*);

#endif //INSPECT_STRUCTS_H

