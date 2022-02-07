#pragma once
#include <common.h>

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
