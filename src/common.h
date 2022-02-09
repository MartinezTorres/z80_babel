#pragma once

#include <megalinker.h>

#include <hal/msxhal.h>
#include <hal/tms99X8.h>

#include <graphics/graphics.h>
ML_REQUEST_C(graphics);
ML_REQUEST_D(scroll_bar);

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

typedef enum {
	SORT_SIZE = 0,
	SORT_SPEED = 1 
} T_SELECTED_SORT;

extern T_SELECTED_SORT selected_sort;

typedef struct S_TEST_CASE T_TEST_CASE;
typedef struct S_TEST T_TEST;
typedef struct S_TEST_RESULT T_TEST_RESULT;

typedef void (*T_FN)();
typedef void (*T_FN_CALL_TEST)(T_FN);
typedef bool (*T_FN_VERIFY_TEST)(const T_TEST *, const T_TEST_CASE *);


struct S_TEST_CASE {
	
	const char *name;

	const uint8_t segment;

	const T_FN fn_test;

	const T_FN fn_begin, fn_end;
	
};

struct S_TEST {
	
	const char *name;

	const T_TEST_CASE *test_cases;
	
	      T_TEST_RESULT *test_results;

	const uint8_t n_test_cases;

	const T_FN fn_reference;

	const T_FN_VERIFY_TEST fn_verify;

	const T_FN_CALL_TEST fn_run_test;

};

struct S_TEST_RESULT {

	const T_TEST *test;
	const T_TEST_CASE *test_case;
	
	uint8_t y;
	
	
	bool executed;
	bool verified;
	
	uint16_t frames;
	uint16_t max_frames;
	
	uint16_t size;
	uint16_t max_size;

	uint8_t frames_x;
	uint8_t frames_x_target;
	uint8_t frames_x_speed;
	
	uint8_t size_x;
	uint8_t size_x_target;
	uint8_t size_x_speed;
};

extern const T_TEST *all_tests[];
extern const uint8_t n_tests;

#define DEF_BENCH(F)  \
	uint16_t F##_1k (uint16_t *, uint8_t *, uint16_t); void F##_end_1k (); \
	uint16_t F##_2k (uint16_t *, uint8_t *, uint16_t); void F##_end_2k (); \
	uint16_t F##_5k (uint16_t *, uint8_t *, uint16_t); void F##_end_5k (); \
	uint16_t F##_10k(uint16_t *, uint8_t *, uint16_t); void F##_end_10k(); \
	uint16_t F##_20k(uint16_t *, uint8_t *, uint16_t); void F##_end_20k(); \
	uint16_t F##_50k(uint16_t *, uint8_t *, uint16_t); void F##_end_50k(); \
	uint16_t F##_1k_mdl_ro (uint16_t *, uint8_t *, uint16_t); void F##_end_1k_mdl_ro (); \
	uint16_t F##_2k_mdl_ro (uint16_t *, uint8_t *, uint16_t); void F##_end_2k_mdl_ro (); \
	uint16_t F##_5k_mdl_ro (uint16_t *, uint8_t *, uint16_t); void F##_end_5k_mdl_ro (); \
	uint16_t F##_10k_mdl_ro(uint16_t *, uint8_t *, uint16_t); void F##_end_10k_mdl_ro(); \
	uint16_t F##_20k_mdl_ro(uint16_t *, uint8_t *, uint16_t); void F##_end_20k_mdl_ro(); \
	uint16_t F##_50k_mdl_ro(uint16_t *, uint8_t *, uint16_t); void F##_end_50k_mdl_ro(); 

#define DEF_BENCH_FORTRAN(F)  \
	int32_t F##__1k (uint64_t *, uint64_t *, uint64_t *); void F##_end__1k (); \
	int32_t F##__2k (uint64_t *, uint64_t *, uint64_t *); void F##_end__2k (); \
	int32_t F##__5k (uint64_t *, uint64_t *, uint64_t *); void F##_end__5k (); \
	int32_t F##__10k(uint64_t *, uint64_t *, uint64_t *); void F##_end__10k(); \
	int32_t F##__20k(uint64_t *, uint64_t *, uint64_t *); void F##_end__20k(); \
	int32_t F##__50k(uint64_t *, uint64_t *, uint64_t *); void F##_end__50k(); \
	int32_t F##__1k_mdl_ro (uint64_t *, uint64_t *, uint64_t *); void F##_end__1k_mdl_ro (); \
	int32_t F##__2k_mdl_ro (uint64_t *, uint64_t *, uint64_t *); void F##_end__2k_mdl_ro (); \
	int32_t F##__5k_mdl_ro (uint64_t *, uint64_t *, uint64_t *); void F##_end__5k_mdl_ro (); \
	int32_t F##__10k_mdl_ro(uint64_t *, uint64_t *, uint64_t *); void F##_end__10k_mdl_ro(); \
	int32_t F##__20k_mdl_ro(uint64_t *, uint64_t *, uint64_t *); void F##_end__20k_mdl_ro(); \
	int32_t F##__50k_mdl_ro(uint64_t *, uint64_t *, uint64_t *); void F##_end__50k_mdl_ro(); 

#define ML_REQUEST_BENCH(module) \
	extern const uint8_t __ML_SEGMENT_B_## module ## _1k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _2k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _5k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _10k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _20k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _50k; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _1k_mdl_ro; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _2k_mdl_ro; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _5k_mdl_ro; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _10k_mdl_ro; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _20k_mdl_ro; \
	extern const uint8_t __ML_SEGMENT_B_## module ## _50k_mdl_ro 
	
ML_MOVE_SYMBOLS_TO( main, tests );
