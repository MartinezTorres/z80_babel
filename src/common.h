#pragma once

#include <megalinker.h>

#include <hal/msxhal.h>
#include <hal/tms99X8.h>

#include <graphics/graphics.h>
ML_REQUEST_C(graphics);

extern const uint16_t font_newsgeek_pts[];
extern const uint16_t font_newsgeek_pos[];
extern const uint8_t font_newsgeek_len[];
ML_REQUEST_D(font_newsgeek);

extern const uint16_t font_didone_pts[];
extern const uint16_t font_didone_pos[];
extern const uint8_t font_didone_len[];
ML_REQUEST_D(font_didone);

extern const uint16_t font_tiny_pts[];
extern const uint16_t font_tiny_pos[];
extern const uint8_t font_tiny_len[];
ML_REQUEST_D(font_tiny);

extern const uint16_t font_thin_pts[];
extern const uint16_t font_thin_pos[];
extern const uint8_t font_thin_len[];
ML_REQUEST_D(font_thin);


__at ((48+2)*1024U) uint8_t algorithm_work_area[4*1024U];
