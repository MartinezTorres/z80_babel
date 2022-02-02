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


ML_REQUEST_B(bench_calibration); 
ML_REQUEST_B(bench_c); 
ML_REQUEST_B(bench_cc); 
ML_REQUEST_B(bench_d); 
ML_REQUEST_B(bench_zig); 
ML_REQUEST_B(bench_rs); 


uint16_t sieve_of_eratosthenes_calibration(uint16_t *out, uint8_t *work, uint16_t max );
uint16_t sieve_of_eratosthenes_c(uint16_t *out, uint8_t *work, uint16_t max );
uint16_t sieve_of_eratosthenes_cc(uint16_t *out, uint8_t *work, uint16_t max );
uint16_t sieve_of_eratosthenes_d(uint16_t *out, uint8_t *work, uint16_t max );
uint16_t sieve_of_eratosthenes_zig(uint16_t *out, uint8_t *work, uint16_t max );
uint16_t sieve_of_eratosthenes_rust(uint16_t *out, uint8_t *work, uint16_t max );
