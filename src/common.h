#pragma once

#include <megalinker.h>

#include <hal/msxhal.h>
#include <hal/tms99X8.h>

#include <graphics/graphics.h>
ML_REQUEST_D(tests);

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
	
	const uint32_t notes;
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
	
	uint8_t size_x;
	uint8_t size_x_target;
};

extern const char *test_texts[];
extern const T_TEST *all_tests[];
extern const uint8_t n_tests;

