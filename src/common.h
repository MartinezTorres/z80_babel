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

#define DEF_TEST(F) DEF_TEST_COMPILER(F) DEF_TEST_COMPILER(F##_end)

#define DEF_TEST_COMPILER(F)  \
	DEF_TEST_ARCH(F) 

#define DEF_TEST_ARCH(F)  \
	DEF_TEST_OPT(F) \
	DEF_TEST_OPT(F##_z80) \
	DEF_TEST_OPT(F##_avr) \
	DEF_TEST_OPT(F##_clang_z80) \
	DEF_TEST_OPT(F##_clang_avr)

#define DEF_TEST_OPT(F)  \
	DEF_TEST_ALLOC(F) \
	DEF_TEST_ALLOC(F##_Ofast) \
	DEF_TEST_ALLOC(F##_Oz) 

#define DEF_TEST_ALLOC(F)  \
	DEF_TEST_MDL_RO(F) \
	DEF_TEST_MDL_RO(F##_1k) \
	DEF_TEST_MDL_RO(F##_2k) \
	DEF_TEST_MDL_RO(F##_5k) \
	DEF_TEST_MDL_RO(F##_10k) \
	DEF_TEST_MDL_RO(F##_20k) \
	DEF_TEST_MDL_RO(F##_50k) 

#define DEF_TEST_MDL_RO(F)  \
	void F(); \
	void F##_mdl(); \
	void F##_mdl_alt();

#define DEF_TEST_FORTRAN(F)  \
	int32_t F##__1k (uint64_t *, uint64_t *, uint64_t *); void F##_end__1k (); \
	int32_t F##__2k (uint64_t *, uint64_t *, uint64_t *); void F##_end__2k (); \
	int32_t F##__5k (uint64_t *, uint64_t *, uint64_t *); void F##_end__5k (); \
	int32_t F##__10k(uint64_t *, uint64_t *, uint64_t *); void F##_end__10k(); \
	int32_t F##__20k(uint64_t *, uint64_t *, uint64_t *); void F##_end__20k(); \
	int32_t F##__50k(uint64_t *, uint64_t *, uint64_t *); void F##_end__50k(); \
	int32_t F##__1k_mdl (uint64_t *, uint64_t *, uint64_t *); void F##_end__1k_mdl (); \
	int32_t F##__2k_mdl (uint64_t *, uint64_t *, uint64_t *); void F##_end__2k_mdl (); \
	int32_t F##__5k_mdl (uint64_t *, uint64_t *, uint64_t *); void F##_end__5k_mdl (); \
	int32_t F##__10k_mdl(uint64_t *, uint64_t *, uint64_t *); void F##_end__10k_mdl(); \
	int32_t F##__20k_mdl(uint64_t *, uint64_t *, uint64_t *); void F##_end__20k_mdl(); \
	int32_t F##__50k_mdl(uint64_t *, uint64_t *, uint64_t *); void F##_end__50k_mdl(); 

#define ML_REQUEST_TEST(module) ML_REQUEST_TEST_COMPILER(module) extern const uint8_t __ML_SEGMENT_B_## module

#define ML_REQUEST_TEST_COMPILER(module)  \
	ML_REQUEST_TEST_ARCH(module) 

#define ML_REQUEST_TEST_ARCH(module)  \
	ML_REQUEST_TEST_OPT(module) \
	ML_REQUEST_TEST_OPT(module##_z80) \
	ML_REQUEST_TEST_OPT(module##_avr) \
	ML_REQUEST_TEST_OPT(module##_clang_z80) \
	ML_REQUEST_TEST_OPT(module##_clang_avr)

#define ML_REQUEST_TEST_OPT(module)  \
	ML_REQUEST_TEST_ALLOC(module) \
	ML_REQUEST_TEST_ALLOC(module##_Ofast) \
	ML_REQUEST_TEST_ALLOC(module##_Oz) 

#define ML_REQUEST_TEST_ALLOC(module)  \
	ML_REQUEST_TEST_MDL_RO(module) \
	ML_REQUEST_TEST_MDL_RO(module##_1k) \
	ML_REQUEST_TEST_MDL_RO(module##_2k) \
	ML_REQUEST_TEST_MDL_RO(module##_5k) \
	ML_REQUEST_TEST_MDL_RO(module##_10k) \
	ML_REQUEST_TEST_MDL_RO(module##_20k) \
	ML_REQUEST_TEST_MDL_RO(module##_50k) 

#define ML_REQUEST_TEST_MDL_RO(module)  \
	extern const uint8_t __ML_SEGMENT_B_## module; \
	extern const uint8_t __ML_SEGMENT_B_## module ##_mdl; \
	extern const uint8_t __ML_SEGMENT_B_## module ##_mdl_alt;
	
