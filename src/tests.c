#if defined(LOAD_DEFINITIONS)

	TEST(sieve, language, "Language",

		CASE(sieve, "ASM", _asm , , _mdl, T(HAND_CODED_ASM) + T(MDL))

		CASE(sieve, "C", _asm , _llvm_z80, _mdl, T(F_LLVM) + T(OZ) + T(B_LLVM_Z80) + T(MDL))

		CASE(sieve, "C", _c , _1, _50k_mdl, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL))

		CASE(sieve, "C", _c , _1, _Oz_50k_mdl, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL))

		CASE(sieve, "C++", _cc , _1, _Oz_50k_mdl, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL))

		CASE(sieve, "D", _d , _1, _Oz_50k_mdl, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL))

		CASE(sieve, "ZIG", _zig , , _Os_50k_mdl, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL))

		CASE(sieve, "RUST", _rs , , _Oz_50k_mdl, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL))

	)

#elif defined(DEPENDENCIES)

	#define LOAD_DEFINITIONS
	
	#define TEST(ALGO_NAME, TEST_NAME, TEXT, CASES) ALGO_NAME/ALGO_NAME ## _common CASES 
	#define CASE(ALGO_NAME, TEXT, FILE_SUFFIX, FLAVOUR_SUFFIX, COMPILER_OPTIONS, NOTES) ALGO_NAME/ALGO_NAME ## FILE_SUFFIX ## COMPILER_OPTIONS
	
	#include __FILE__ 

#else 
	#define LOAD_DEFINITIONS

	#include <common.h>

	#define T(a) (((uint32_t)1) << ((uint32_t)a))

	enum {
		HAND_CODED_ASM,
		B_LLVM_Z80,
		F_LLVM,
		F_SDCC,
		OZ,
		OS,
		B_SDCC,
		T50K,
		MDL, 
		MDL_ALT,
	};

	const char *test_texts[32] = {
		[HAND_CODED_ASM] = "HAND CODED ASM",
		[F_LLVM] = "LLVM FRONT",
		[F_SDCC] = "SDCC FRONT",
		[OZ] = "-OZ",
		[OS] = "-OS",
		[B_LLVM_Z80] = "LLVM-Z80 BACK (JACOBLY0)",
		[B_SDCC] = "SDCC BACK",
		[T50K] = "50.000 MAX-ALLOCS",
		[MDL] = "MDL",
		[MDL_ALT] = "MDL DEV",
	};

	#define TEST(ALGO_NAME, TEST_NAME, TEXT, CASES) \
		extern void reference_ ## ALGO_NAME(); \
		extern void verify_ ## ALGO_NAME(); \
		extern void run_ ## ALGO_NAME(); \
		CASES 
		
	#define CASE(ALGO_NAME, TEXT, FILE_SUFFIX, FLAVOUR_SUFFIX, COMPILER_OPTIONS, NOTES) \
		extern void ALGO_NAME ## FILE_SUFFIX ## FLAVOUR_SUFFIX ## COMPILER_OPTIONS(); \
		extern void ALGO_NAME ## FILE_SUFFIX ## FLAVOUR_SUFFIX ## _end ## COMPILER_OPTIONS(); \
		ML_REQUEST_B(ALGO_NAME ## FILE_SUFFIX ## COMPILER_OPTIONS); 


	#include __FILE__

	#undef TEST
	#undef CASE


	#define TEST(ALGO_NAME, TEST_NAME, TEXT, CASES) \
		static const T_TEST_CASE ALGO_NAME ## TEST_NAME ## _cases[] = { CASES }; \
		static T_TEST_RESULT ALGO_NAME ## TEST_NAME ## _results[sizeof(ALGO_NAME ## TEST_NAME ## _cases)/sizeof(T_TEST_CASE)]; \
		static const T_TEST ALGO_NAME ## TEST_NAME = { \
			.name = TEXT, \
			.test_cases = ALGO_NAME ## TEST_NAME ## _cases, \
			.test_results = ALGO_NAME ## TEST_NAME ## _results, \
			.n_test_cases = sizeof(ALGO_NAME ## TEST_NAME ## _cases)/sizeof(T_TEST_CASE), \
			.fn_reference = reference_ ## ALGO_NAME, \
			.fn_verify = (T_FN_VERIFY_TEST)verify_ ## ALGO_NAME, \
			.fn_run_test = (T_FN_CALL_TEST)run_ ## ALGO_NAME \
		};

	#define CASE(ALGO_NAME, TEXT, FILE_SUFFIX, FLAVOUR_SUFFIX, COMPILER_OPTIONS, NOTES) { \
			.name = TEXT, \
			.segment = ML_SEGMENT_B(ALGO_NAME ## FILE_SUFFIX ## COMPILER_OPTIONS), \
			.fn_test = (T_FN)ALGO_NAME ## FILE_SUFFIX ## FLAVOUR_SUFFIX ## COMPILER_OPTIONS, \
			.fn_begin = (T_FN)ALGO_NAME ## FILE_SUFFIX ## FLAVOUR_SUFFIX ## COMPILER_OPTIONS, \
			.fn_end = (T_FN)ALGO_NAME ## FILE_SUFFIX ## FLAVOUR_SUFFIX ## _end ## COMPILER_OPTIONS, \
			.notes = NOTES \
		},

	#define CASE_EXT(ALGO_NAME, TEXT, FILE_SUFFIX, FLAVOUR_SUFFIX, COMPILER_OPTIONS, NOTES, MODULE, TEST, BEGIN, END) { \
			.name = TEXT, \
			.segment = ML_SEGMENT_B(ALGO_NAME/MODULE), \
			.fn_test = (T_FN)TEST, \
			.fn_begin = (T_FN)BEGIN, \
			.fn_end = (T_FN)END, \
			.notes = NOTES \
		},


	#include __FILE__

	/*


	static const T_TEST_CASE test_cases_sieve_language[] = {
		
		{
			.name = "ASM",
			.segment = ML_SEGMENT_B(sieve_asm_mdl),
			.fn_test = (T_FN)sieve_asm_mdl,
			.fn_begin = (T_FN)sieve_asm_mdl,
			.fn_end = sieve_asm_end_mdl,
			.notes = T(HAND_CODED_ASM) + T(MDL)
		},

		{
			.name = "C",
			.segment = ML_SEGMENT_B(sieve_asm_mdl),
			.fn_test = (T_FN)sieve_asm_llvm_z80_mdl,
			.fn_begin = (T_FN)sieve_asm_llvm_z80_mdl,
			.fn_end = sieve_asm_llvm_z80_end_mdl,
			.notes = T(F_LLVM) + T(OZ) + T(B_LLVM_Z80) + T(MDL)	
		},
		{
			.name = "C",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl,
			.notes = T(F_SDCC)  + T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "C",
			.segment = ML_SEGMENT_B(sieve_c_clang_z80_Oz_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_clang_z80_Oz_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_clang_z80_Oz_50k_mdl,
			.fn_end = sieve_c_1_end_clang_z80_Oz_50k_mdl,
			.notes = T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C++",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl,
			.notes = T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "D",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl,
			.notes =  T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_50k_mdl),
			.fn_test = (T_FN)sieve_zig_50k_mdl,
			.fn_begin = (T_FN)sieve_zig_50k_mdl,
			.fn_end = sieve_zig_end_50k_mdl,
			.notes = T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_50k_mdl),
			.fn_test = (T_FN)sieve_rust_50k_mdl,
			.fn_begin = (T_FN)sieve_rust_50k_mdl,
			.fn_end = sieve_rust_end_50k_mdl,
			.notes = T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "FORTRAN",
			.segment = ML_SEGMENT_B(sieve_f_50k_mdl),
			.fn_test = (T_FN)sieve_fortran_50k_mdl,
			.fn_begin = (T_FN)sieve_fortran__50k_mdl,
			.fn_end = sieve_fortran_end__50k_mdl,
			.notes =  T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL)
		},
	};

	static const T_TEST test_sieve_language = {
		
		.name = "Language  - Prime Sieve",
		.test_cases = test_cases_sieve_language,
		.test_results = test_results_global,
		.n_test_cases = sizeof(test_cases_sieve_language)/sizeof(T_TEST_CASE),
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_mdl[] = {
		
		{
			.name = "C MDL",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl,
			.notes =  T(F_SDCC)  + T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "C++ MDL",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "D MDL",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "ZIG MDL",
			.segment = ML_SEGMENT_B(sieve_zig_50k_mdl),
			.fn_test = (T_FN)sieve_zig_50k_mdl,
			.fn_begin = (T_FN)sieve_zig_50k_mdl,
			.fn_end = sieve_zig_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "RUST MDL",
			.segment = ML_SEGMENT_B(sieve_rs_50k_mdl),
			.fn_test = (T_FN)sieve_rust_50k_mdl,
			.fn_begin = (T_FN)sieve_rust_50k_mdl,
			.fn_end = sieve_rust_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C",
			.segment = ML_SEGMENT_B(sieve_c_50k),
			.fn_test = (T_FN)sieve_c_1_50k,
			.fn_begin = (T_FN)sieve_c_1_50k,
			.fn_end = sieve_c_1_end_50k,
			.notes =  T(F_SDCC)  + T(B_SDCC) + T(T50K)
		},
		
		{
			.name = "C++",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k),
			.fn_test = (T_FN)sieve_cc_1_z80_50k,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k,
			.fn_end = sieve_cc_1_end_z80_50k,
			.notes = T(B_SDCC) + T(T50K)
		},

		{
			.name = "D",
			.segment = ML_SEGMENT_B(sieve_d_50k),
			.fn_test = (T_FN)sieve_d_1_50k,
			.fn_begin = (T_FN)sieve_d_1_50k,
			.fn_end = sieve_d_1_end_50k,
			.notes = T(B_SDCC) + T(T50K)
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_50k),
			.fn_test = (T_FN)sieve_zig_50k,
			.fn_begin = (T_FN)sieve_zig_50k,
			.fn_end = sieve_zig_end_50k,
			.notes = T(B_SDCC) + T(T50K) 
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_50k),
			.fn_test = (T_FN)sieve_rust_50k,
			.fn_begin = (T_FN)sieve_rust_50k,
			.fn_end = sieve_rust_end_50k,
			.notes = T(B_SDCC) + T(T50K)
		},

	};

	static const T_TEST test_sieve_mdl = {
		
		.name = "MDL - Prime Sieve",
		.test_cases = test_cases_sieve_mdl,
		.test_results = test_results_global,
		.n_test_cases = 10,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_mdl_dev[] = {
		
		{
			.name = "C dev",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl,
			.notes = T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_ALT)
		},
		
		{
			.name = "C++ dev",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL_ALT)
		},

		{
			.name = "D dev",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL_ALT)
		},
		
		{
			.name = "ZIG dev",
			.segment = ML_SEGMENT_B(sieve_zig_50k_mdl),
			.fn_test = (T_FN)sieve_zig_50k_mdl,
			.fn_begin = (T_FN)sieve_zig_50k_mdl,
			.fn_end = sieve_zig_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL_ALT)
		},
		
		{
			.name = "RUST dev",
			.segment = ML_SEGMENT_B(sieve_rs_50k_mdl),
			.fn_test = (T_FN)sieve_rust_50k_mdl,
			.fn_begin = (T_FN)sieve_rust_50k_mdl,
			.fn_end = sieve_rust_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL_ALT)
		},

		{
			.name = "C",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl,
			.notes = T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "C++",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "D",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_50k_mdl),
			.fn_test = (T_FN)sieve_zig_50k_mdl,
			.fn_begin = (T_FN)sieve_zig_50k_mdl,
			.fn_end = sieve_zig_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_50k_mdl),
			.fn_test = (T_FN)sieve_rust_50k_mdl,
			.fn_begin = (T_FN)sieve_rust_50k_mdl,
			.fn_end = sieve_rust_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

	};


	static const T_TEST test_sieve_mdl_dev = {
		
		.name = "MDL DEVELOPMENT  - Prime Sieve",
		.test_cases = test_cases_sieve_mdl_dev,
		.test_results = test_results_global,
		.n_test_cases = 10,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};

	static const T_TEST_CASE test_cases_sieve_algo[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl,
			.notes = T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		
		{
			.name = "C v2",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_2_50k_mdl,
			.fn_begin = (T_FN)sieve_c_2_50k_mdl,
			.fn_end = sieve_c_2_end_50k_mdl,
			.notes = T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C v3",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_3_50k_mdl,
			.fn_begin = (T_FN)sieve_c_3_50k_mdl,
			.fn_end = sieve_c_3_end_50k_mdl,
			.notes = T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C++ v2",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_2_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_2_z80_50k_mdl,
			.fn_end = sieve_cc_2_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "C++ v3",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_3_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_3_z80_50k_mdl,
			.fn_end = sieve_cc_3_end_z80_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},


		{
			.name = "D v1",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
		
		{
			.name = "D v2",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_2_50k_mdl,
			.fn_begin = (T_FN)sieve_d_2_50k_mdl,
			.fn_end = sieve_d_2_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},

		{
			.name = "D v3",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_3_50k_mdl,
			.fn_begin = (T_FN)sieve_d_3_50k_mdl,
			.fn_end = sieve_d_3_end_50k_mdl,
			.notes = T(B_SDCC) + T(T50K) + T(MDL)
		},
	};

	static const T_TEST test_sieve_algo = {
		
		.name = "Algorithm Test - Prime Sieve",
		.test_cases = test_cases_sieve_algo,
		.test_results = test_results_global,
		.n_test_cases = 9,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};

	static const T_TEST_CASE test_cases_sieve_50k_3[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(sieve_c_50k),
			.fn_test = (T_FN)sieve_c_1_50k,
			.fn_begin = (T_FN)sieve_c_1_50k,
			.fn_end = sieve_c_1_end_50k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k),
			.fn_test = (T_FN)sieve_cc_1_z80_50k,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k,
			.fn_end = sieve_cc_1_end_z80_50k
		},

		{
			.name = "D v1",
			.segment = ML_SEGMENT_B(sieve_d_50k),
			.fn_test = (T_FN)sieve_d_1_50k,
			.fn_begin = (T_FN)sieve_d_1_50k,
			.fn_end = sieve_d_1_end_50k
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_50k),
			.fn_test = (T_FN)sieve_zig_50k,
			.fn_begin = (T_FN)sieve_zig_50k,
			.fn_end = sieve_zig_end_50k
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_50k),
			.fn_test = (T_FN)sieve_rust_50k,
			.fn_begin = (T_FN)sieve_rust_50k,
			.fn_end = sieve_rust_end_50k
		},

		{
			.name = "FORTRAN",
			.segment = ML_SEGMENT_B(sieve_f_50k),
			.fn_test = (T_FN)sieve_fortran_50k,
			.fn_begin = (T_FN)sieve_fortran__50k,
			.fn_end = sieve_fortran_end__50k
		},

		{
			.name = "C v1 MDL",
			.segment = ML_SEGMENT_B(sieve_c_50k_mdl),
			.fn_test = (T_FN)sieve_c_1_50k_mdl,
			.fn_begin = (T_FN)sieve_c_1_50k_mdl,
			.fn_end = sieve_c_1_end_50k_mdl
		},

		{
			.name = "C++ v1 MDL",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k_mdl,
			.fn_end = sieve_cc_1_end_z80_50k_mdl
		},

		{
			.name = "D v1 MDL",
			.segment = ML_SEGMENT_B(sieve_d_50k_mdl),
			.fn_test = (T_FN)sieve_d_1_50k_mdl,
			.fn_begin = (T_FN)sieve_d_1_50k_mdl,
			.fn_end = sieve_d_1_end_50k_mdl
		},
		
		{
			.name = "ZIG MDL",
			.segment = ML_SEGMENT_B(sieve_zig_50k_mdl),
			.fn_test = (T_FN)sieve_zig_50k_mdl,
			.fn_begin = (T_FN)sieve_zig_50k_mdl,
			.fn_end = sieve_zig_end_50k_mdl
		},
		
		{
			.name = "RUST MDL",
			.segment = ML_SEGMENT_B(sieve_rs_50k_mdl),
			.fn_test = (T_FN)sieve_rust_50k_mdl,
			.fn_begin = (T_FN)sieve_rust_50k_mdl,
			.fn_end = sieve_rust_end_50k_mdl
		},

		{
			.name = "F. MDL",
			.segment = ML_SEGMENT_B(sieve_f_50k_mdl),
			.fn_test = (T_FN)sieve_fortran_50k_mdl,
			.fn_begin = (T_FN)sieve_fortran__50k_mdl,
			.fn_end = sieve_fortran_end__50k_mdl
		},
	};

	static const T_TEST test_sieve_50k_3 = {
		
		.name = "Sieve of Eratosthenes 50k - 3",
		.test_cases = test_cases_sieve_50k_3,
		.test_results = test_results_global,
		.n_test_cases = 12,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};

	static const T_TEST_CASE test_cases_sieve_1k_1[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_1_1k,
			.fn_begin = (T_FN)sieve_c_1_1k,
			.fn_end = sieve_c_1_end_1k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_1_z80_1k,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k,
			.fn_end = sieve_cc_1_end_z80_1k
		},

		{
			.name = "D v1",
			.segment = ML_SEGMENT_B(sieve_d_1k),
			.fn_test = (T_FN)sieve_d_1_1k,
			.fn_begin = (T_FN)sieve_d_1_1k,
			.fn_end = sieve_d_1_end_1k
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_1k),
			.fn_test = (T_FN)sieve_zig_1k,
			.fn_begin = (T_FN)sieve_zig_1k,
			.fn_end = sieve_zig_end_1k
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_1k),
			.fn_test = (T_FN)sieve_rust_1k,
			.fn_begin = (T_FN)sieve_rust_1k,
			.fn_end = sieve_rust_end_1k
		},

		{
			.name = "FORTRAN",
			.segment = ML_SEGMENT_B(sieve_f_1k),
			.fn_test = (T_FN)sieve_fortran_1k,
			.fn_begin = (T_FN)sieve_fortran__1k,
			.fn_end = sieve_fortran_end__1k
		},
	};

	static const T_TEST test_sieve_1k_1 = {
		
		.name = "Sieve of Eratosthenes 1k - 1",
		.test_cases = test_cases_sieve_1k_1,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_1k_2[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_1_1k,
			.fn_begin = (T_FN)sieve_c_1_1k,
			.fn_end = sieve_c_1_end_1k
		},

		
		{
			.name = "C v2",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_2_1k,
			.fn_begin = (T_FN)sieve_c_2_1k,
			.fn_end = sieve_c_2_end_1k
		},

		{
			.name = "C v3",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_3_1k,
			.fn_begin = (T_FN)sieve_c_3_1k,
			.fn_end = sieve_c_3_end_1k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_1_z80_1k,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k,
			.fn_end = sieve_cc_1_end_z80_1k
		},

		{
			.name = "C++ v2",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_2_z80_1k,
			.fn_begin = (T_FN)sieve_cc_2_z80_1k,
			.fn_end = sieve_cc_2_end_z80_1k
		},

		{
			.name = "C++ v3",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_3_z80_1k,
			.fn_begin = (T_FN)sieve_cc_3_z80_1k,
			.fn_end = sieve_cc_3_end_z80_1k
		},


		{
			.name = "D v1",
			.segment = ML_SEGMENT_B(sieve_d_1k),
			.fn_test = (T_FN)sieve_d_1_1k,
			.fn_begin = (T_FN)sieve_d_1_1k,
			.fn_end = sieve_d_1_end_1k
		},
		
		{
			.name = "D v2",
			.segment = ML_SEGMENT_B(sieve_d_1k),
			.fn_test = (T_FN)sieve_d_2_1k,
			.fn_begin = (T_FN)sieve_d_2_1k,
			.fn_end = sieve_d_2_end_1k
		},

		{
			.name = "D v3",
			.segment = ML_SEGMENT_B(sieve_d_1k),
			.fn_test = (T_FN)sieve_d_3_1k,
			.fn_begin = (T_FN)sieve_d_3_1k,
			.fn_end = sieve_d_3_end_1k
		},

		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_1k),
			.fn_test = (T_FN)sieve_zig_1k,
			.fn_begin = (T_FN)sieve_zig_1k,
			.fn_end = sieve_zig_end_1k
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_1k),
			.fn_test = (T_FN)sieve_rust_1k,
			.fn_begin = (T_FN)sieve_rust_1k,
			.fn_end = sieve_rust_end_1k
		},
	};

	static const T_TEST test_sieve_1k_2 = {
		
		.name = "Sieve of Eratosthenes 1k - 2",
		.test_cases = test_cases_sieve_1k_2,
		.test_results = test_results_global,
		.n_test_cases = 11,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};

	static const T_TEST_CASE test_cases_sieve_1k_3[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_1_1k,
			.fn_begin = (T_FN)sieve_c_1_1k,
			.fn_end = sieve_c_1_end_1k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_1_z80_1k,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k,
			.fn_end = sieve_cc_1_end_z80_1k
		},

		{
			.name = "D v1",
			.segment = ML_SEGMENT_B(sieve_d_1k),
			.fn_test = (T_FN)sieve_d_1_1k,
			.fn_begin = (T_FN)sieve_d_1_1k,
			.fn_end = sieve_d_1_end_1k
		},
		
		{
			.name = "ZIG",
			.segment = ML_SEGMENT_B(sieve_zig_1k),
			.fn_test = (T_FN)sieve_zig_1k,
			.fn_begin = (T_FN)sieve_zig_1k,
			.fn_end = sieve_zig_end_1k
		},
		
		{
			.name = "RUST",
			.segment = ML_SEGMENT_B(sieve_rs_1k),
			.fn_test = (T_FN)sieve_rust_1k,
			.fn_begin = (T_FN)sieve_rust_1k,
			.fn_end = sieve_rust_end_1k
		},

		{
			.name = "FORTRAN",
			.segment = ML_SEGMENT_B(sieve_f_1k),
			.fn_test = (T_FN)sieve_fortran_1k,
			.fn_begin = (T_FN)sieve_fortran__1k,
			.fn_end = sieve_fortran_end__1k
		},

		{
			.name = "C v1 MDL",
			.segment = ML_SEGMENT_B(sieve_c_1k_mdl),
			.fn_test = (T_FN)sieve_c_1_1k_mdl,
			.fn_begin = (T_FN)sieve_c_1_1k_mdl,
			.fn_end = sieve_c_1_end_1k_mdl
		},

		{
			.name = "C++ v1 MDL",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k_mdl),
			.fn_test = (T_FN)sieve_cc_1_z80_1k_mdl,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k_mdl,
			.fn_end = sieve_cc_1_end_z80_1k_mdl
		},

		{
			.name = "D v1 MDL",
			.segment = ML_SEGMENT_B(sieve_d_1k_mdl),
			.fn_test = (T_FN)sieve_d_1_1k_mdl,
			.fn_begin = (T_FN)sieve_d_1_1k_mdl,
			.fn_end = sieve_d_1_end_1k_mdl
		},
		
		{
			.name = "ZIG MDL",
			.segment = ML_SEGMENT_B(sieve_zig_1k_mdl),
			.fn_test = (T_FN)sieve_zig_1k_mdl,
			.fn_begin = (T_FN)sieve_zig_1k_mdl,
			.fn_end = sieve_zig_end_1k_mdl
		},
		
		{
			.name = "RUST MDL",
			.segment = ML_SEGMENT_B(sieve_rs_1k_mdl),
			.fn_test = (T_FN)sieve_rust_1k_mdl,
			.fn_begin = (T_FN)sieve_rust_1k_mdl,
			.fn_end = sieve_rust_end_1k_mdl
		},

		{
			.name = "F. MDL",
			.segment = ML_SEGMENT_B(sieve_f_1k_mdl),
			.fn_test = (T_FN)sieve_fortran_1k_mdl,
			.fn_begin = (T_FN)sieve_fortran__1k_mdl,
			.fn_end = sieve_fortran_end__1k_mdl
		},
	};

	static const T_TEST test_sieve_1k_3 = {
		
		.name = "Sieve of Eratosthenes 1k - 3",
		.test_cases = test_cases_sieve_1k_3,
		.test_results = test_results_global,
		.n_test_cases = 12,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_c_1[] = {
		
		{
			.name = "C 1k",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_1_1k,
			.fn_begin = (T_FN)sieve_c_1_1k,
			.fn_end = sieve_c_1_end_1k
		},

		{
			.name = "C 2k",
			.segment = ML_SEGMENT_B(sieve_c_2k),
			.fn_test = (T_FN)sieve_c_1_2k,
			.fn_begin = (T_FN)sieve_c_1_2k,
			.fn_end = sieve_c_1_end_2k
		},

		{
			.name = "C 5k",
			.segment = ML_SEGMENT_B(sieve_c_5k),
			.fn_test = (T_FN)sieve_c_1_5k,
			.fn_begin = (T_FN)sieve_c_1_5k,
			.fn_end = sieve_c_1_end_5k
		},

		{
			.name = "C 10k",
			.segment = ML_SEGMENT_B(sieve_c_10k),
			.fn_test = (T_FN)sieve_c_1_10k,
			.fn_begin = (T_FN)sieve_c_1_10k,
			.fn_end = sieve_c_1_end_10k
		},

		{
			.name = "C 20k",
			.segment = ML_SEGMENT_B(sieve_c_20k),
			.fn_test = (T_FN)sieve_c_1_20k,
			.fn_begin = (T_FN)sieve_c_1_20k,
			.fn_end = sieve_c_1_end_20k
		},

		{
			.name = "C 50k",
			.segment = ML_SEGMENT_B(sieve_c_50k),
			.fn_test = (T_FN)sieve_c_1_50k,
			.fn_begin = (T_FN)sieve_c_1_50k,
			.fn_end = sieve_c_1_end_50k
		},
	};

	static const T_TEST test_sieve_c_1 = {
		
		.name = "Sieve of Eratosthenes (C v1)",
		.test_cases = test_cases_sieve_c_1,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_c_3[] = {
		

		{
			.name = "C 1k",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_3_1k,
			.fn_begin = (T_FN)sieve_c_3_1k,
			.fn_end = sieve_c_3_end_1k
		},

		{
			.name = "C 2k",
			.segment = ML_SEGMENT_B(sieve_c_2k),
			.fn_test = (T_FN)sieve_c_3_2k,
			.fn_begin = (T_FN)sieve_c_3_2k,
			.fn_end = sieve_c_3_end_2k
		},

		{
			.name = "C 5k",
			.segment = ML_SEGMENT_B(sieve_c_5k),
			.fn_test = (T_FN)sieve_c_3_5k,
			.fn_begin = (T_FN)sieve_c_3_5k,
			.fn_end = sieve_c_3_end_5k
		},

		{
			.name = "C 10k",
			.segment = ML_SEGMENT_B(sieve_c_10k),
			.fn_test = (T_FN)sieve_c_3_10k,
			.fn_begin = (T_FN)sieve_c_3_10k,
			.fn_end = sieve_c_3_end_10k
		},

		{
			.name = "C 20k",
			.segment = ML_SEGMENT_B(sieve_c_20k),
			.fn_test = (T_FN)sieve_c_3_20k,
			.fn_begin = (T_FN)sieve_c_3_20k,
			.fn_end = sieve_c_3_end_20k
		},

		{
			.name = "C 50k",
			.segment = ML_SEGMENT_B(sieve_c_50k),
			.fn_test = (T_FN)sieve_c_3_50k,
			.fn_begin = (T_FN)sieve_c_3_50k,
			.fn_end = sieve_c_3_end_50k
		},

	};

	static const T_TEST test_sieve_c_3 = {
		
		.name = "Sieve of Eratosthenes (C v3)",
		.test_cases = test_cases_sieve_c_3,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};



	static const T_TEST_CASE test_cases_sieve_cpp_1[] = {
		
		{
			.name = "C++ 1k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_1_z80_1k,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k,
			.fn_end = sieve_cc_1_end_z80_1k
		},

		{
			.name = "C++ 2k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_2k),
			.fn_test = (T_FN)sieve_cc_1_z80_2k,
			.fn_begin = (T_FN)sieve_cc_1_z80_2k,
			.fn_end = sieve_cc_1_end_z80_2k
		},

		{
			.name = "C++ 5k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_5k),
			.fn_test = (T_FN)sieve_cc_1_z80_5k,
			.fn_begin = (T_FN)sieve_cc_1_z80_5k,
			.fn_end = sieve_cc_1_end_z80_5k
		},

		{
			.name = "C++ 10k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_10k),
			.fn_test = (T_FN)sieve_cc_1_z80_10k,
			.fn_begin = (T_FN)sieve_cc_1_z80_10k,
			.fn_end = sieve_cc_1_end_z80_10k
		},

		{
			.name = "C++ 20k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_20k),
			.fn_test = (T_FN)sieve_cc_1_z80_20k,
			.fn_begin = (T_FN)sieve_cc_1_z80_20k,
			.fn_end = sieve_cc_1_end_z80_20k
		},

		{
			.name = "C++ 50k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k),
			.fn_test = (T_FN)sieve_cc_1_z80_50k,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k,
			.fn_end = sieve_cc_1_end_z80_50k
		},
	};

	static const T_TEST test_sieve_cpp_1 = {
		
		.name = "Sieve of Eratosthenes (C++ v1)",
		.test_cases = test_cases_sieve_cpp_1,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_cpp_3[] = {
		

		{
			.name = "C++ 1k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_3_z80_1k,
			.fn_begin = (T_FN)sieve_cc_3_z80_1k,
			.fn_end = sieve_cc_3_end_z80_1k
		},

		{
			.name = "C++ 2k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_2k),
			.fn_test = (T_FN)sieve_cc_3_z80_2k,
			.fn_begin = (T_FN)sieve_cc_3_z80_2k,
			.fn_end = sieve_cc_3_end_z80_2k
		},

		{
			.name = "C++ 5k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_5k),
			.fn_test = (T_FN)sieve_cc_3_z80_5k,
			.fn_begin = (T_FN)sieve_cc_3_z80_5k,
			.fn_end = sieve_cc_3_end_z80_5k
		},

		{
			.name = "C++ 10k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_10k),
			.fn_test = (T_FN)sieve_cc_3_z80_10k,
			.fn_begin = (T_FN)sieve_cc_3_z80_10k,
			.fn_end = sieve_cc_3_end_z80_10k
		},

		{
			.name = "C++ 20k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_20k),
			.fn_test = (T_FN)sieve_cc_3_z80_20k,
			.fn_begin = (T_FN)sieve_cc_3_z80_20k,
			.fn_end = sieve_cc_3_end_z80_20k
		},

		{
			.name = "C++ 50k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k),
			.fn_test = (T_FN)sieve_cc_3_z80_50k,
			.fn_begin = (T_FN)sieve_cc_3_z80_50k,
			.fn_end = sieve_cc_3_end_z80_50k
		},

	};

	static const T_TEST test_sieve_cpp_3 = {
		
		.name = "Sieve of Eratosthenes (C++ v3)",
		.test_cases = test_cases_sieve_cpp_3,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};



	static const T_TEST_CASE test_cases_sieve_d_1[] = {
		
		{
			.name = "D 1k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_1k),
			.fn_test = (T_FN)sieve_cc_1_z80_1k,
			.fn_begin = (T_FN)sieve_cc_1_z80_1k,
			.fn_end = sieve_cc_1_end_z80_1k
		},

		{
			.name = "D 2k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_2k),
			.fn_test = (T_FN)sieve_cc_1_z80_2k,
			.fn_begin = (T_FN)sieve_cc_1_z80_2k,
			.fn_end = sieve_cc_1_end_z80_2k
		},

		{
			.name = "D 5k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_5k),
			.fn_test = (T_FN)sieve_cc_1_z80_5k,
			.fn_begin = (T_FN)sieve_cc_1_z80_5k,
			.fn_end = sieve_cc_1_end_z80_5k
		},

		{
			.name = "D 10k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_10k),
			.fn_test = (T_FN)sieve_cc_1_z80_10k,
			.fn_begin = (T_FN)sieve_cc_1_z80_10k,
			.fn_end = sieve_cc_1_end_z80_10k
		},

		{
			.name = "D 20k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_20k),
			.fn_test = (T_FN)sieve_cc_1_z80_20k,
			.fn_begin = (T_FN)sieve_cc_1_z80_20k,
			.fn_end = sieve_cc_1_end_z80_20k
		},

		{
			.name = "D 50k",
			.segment = ML_SEGMENT_B(sieve_cc_z80_50k),
			.fn_test = (T_FN)sieve_cc_1_z80_50k,
			.fn_begin = (T_FN)sieve_cc_1_z80_50k,
			.fn_end = sieve_cc_1_end_z80_50k
		},
	};

	static const T_TEST test_sieve_d_1 = {
		
		.name = "Sieve of Eratosthenes (D v1)",
		.test_cases = test_cases_sieve_d_1,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_d_3[] = {
		

		{
			.name = "D 1k",
			.segment = ML_SEGMENT_B(sieve_c_1k),
			.fn_test = (T_FN)sieve_c_3_1k,
			.fn_begin = (T_FN)sieve_c_3_1k,
			.fn_end = sieve_c_3_end_1k
		},

		{
			.name = "D 2k",
			.segment = ML_SEGMENT_B(sieve_c_2k),
			.fn_test = (T_FN)sieve_c_3_2k,
			.fn_begin = (T_FN)sieve_c_3_2k,
			.fn_end = sieve_c_3_end_2k
		},

		{
			.name = "D 5k",
			.segment = ML_SEGMENT_B(sieve_c_5k),
			.fn_test = (T_FN)sieve_c_3_5k,
			.fn_begin = (T_FN)sieve_c_3_5k,
			.fn_end = sieve_c_3_end_5k
		},

		{
			.name = "D 10k",
			.segment = ML_SEGMENT_B(sieve_c_10k),
			.fn_test = (T_FN)sieve_c_3_10k,
			.fn_begin = (T_FN)sieve_c_3_10k,
			.fn_end = sieve_c_3_end_10k
		},

		{
			.name = "D 20k",
			.segment = ML_SEGMENT_B(sieve_c_20k),
			.fn_test = (T_FN)sieve_c_3_20k,
			.fn_begin = (T_FN)sieve_c_3_20k,
			.fn_end = sieve_c_3_end_20k
		},

		{
			.name = "D 50k",
			.segment = ML_SEGMENT_B(sieve_c_50k),
			.fn_test = (T_FN)sieve_c_3_50k,
			.fn_begin = (T_FN)sieve_c_3_50k,
			.fn_end = sieve_c_3_end_50k
		},

	};

	static const T_TEST test_sieve_d_3 = {
		
		.name = "Sieve of Eratosthenes (D v3)",
		.test_cases = test_cases_sieve_d_3,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};


	static const T_TEST_CASE test_cases_sieve_rust[] = {
		
		{
			.name = "RUST 1k",
			.segment = ML_SEGMENT_B(sieve_rs_1k),
			.fn_test = (T_FN)sieve_rust_1k,
			.fn_begin = (T_FN)sieve_rust_1k,
			.fn_end = sieve_rust_end_1k
		},

		{
			.name = "RUST 2k",
			.segment = ML_SEGMENT_B(sieve_rs_2k),
			.fn_test = (T_FN)sieve_rust_2k,
			.fn_begin = (T_FN)sieve_rust_2k,
			.fn_end = sieve_rust_end_2k
		},

		{
			.name = "RUST 5k",
			.segment = ML_SEGMENT_B(sieve_rs_5k),
			.fn_test = (T_FN)sieve_rust_5k,
			.fn_begin = (T_FN)sieve_rust_5k,
			.fn_end = sieve_rust_end_5k
		},

		{
			.name = "RUST 10k",
			.segment = ML_SEGMENT_B(sieve_rs_10k),
			.fn_test = (T_FN)sieve_rust_10k,
			.fn_begin = (T_FN)sieve_rust_10k,
			.fn_end = sieve_rust_end_10k
		},

		{
			.name = "RUST 20k",
			.segment = ML_SEGMENT_B(sieve_rs_20k),
			.fn_test = (T_FN)sieve_rust_20k,
			.fn_begin = (T_FN)sieve_rust_20k,
			.fn_end = sieve_rust_end_20k
		},

		{
			.name = "RUST 50k",
			.segment = ML_SEGMENT_B(sieve_rs_50k),
			.fn_test = (T_FN)sieve_rust_50k,
			.fn_begin = (T_FN)sieve_rust_50k,
			.fn_end = sieve_rust_end_50k
		},
	};

	static const T_TEST test_sieve_rust = {
		
		.name = "Sieve of Eratosthenes (RUST)",
		.test_cases = test_cases_sieve_rust,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};

	static const T_TEST_CASE test_cases_sieve_zig[] = {
		
		{
			.name = "ZIG 1k",
			.segment = ML_SEGMENT_B(sieve_zig_1k),
			.fn_test = (T_FN)sieve_zig_1k,
			.fn_begin = (T_FN)sieve_zig_1k,
			.fn_end = sieve_zig_end_1k
		},

		{
			.name = "ZIG 2k",
			.segment = ML_SEGMENT_B(sieve_zig_2k),
			.fn_test = (T_FN)sieve_zig_2k,
			.fn_begin = (T_FN)sieve_zig_2k,
			.fn_end = sieve_zig_end_2k
		},

		{
			.name = "ZIG 5k",
			.segment = ML_SEGMENT_B(sieve_zig_5k),
			.fn_test = (T_FN)sieve_zig_5k,
			.fn_begin = (T_FN)sieve_zig_5k,
			.fn_end = sieve_zig_end_5k
		},

		{
			.name = "ZIG 10k",
			.segment = ML_SEGMENT_B(sieve_zig_10k),
			.fn_test = (T_FN)sieve_zig_10k,
			.fn_begin = (T_FN)sieve_zig_10k,
			.fn_end = sieve_zig_end_10k
		},

		{
			.name = "ZIG 20k",
			.segment = ML_SEGMENT_B(sieve_zig_20k),
			.fn_test = (T_FN)sieve_zig_20k,
			.fn_begin = (T_FN)sieve_zig_20k,
			.fn_end = sieve_zig_end_20k
		},

		{
			.name = "ZIG 50k",
			.segment = ML_SEGMENT_B(sieve_zig_50k),
			.fn_test = (T_FN)sieve_zig_50k,
			.fn_begin = (T_FN)sieve_zig_50k,
			.fn_end = sieve_zig_end_50k
		},
	};

	static const T_TEST test_sieve_zig = {
		
		.name = "Sieve of Eratosthenes (ZIG)",
		.test_cases = test_cases_sieve_zig,
		.test_results = test_results_global,
		.n_test_cases = 6,
		.fn_reference = run_reference_sieve_of_erastosthenes,
		.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
		.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
	};



	static const T_TEST_CASE test_cases_quicksort_50k_1[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(quicksort_c_50k),
			.fn_test = (T_FN)quicksort_c_50k,
			.fn_begin = (T_FN)quicksort_c_50k,
			.fn_end = quicksort_c_end_50k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(quicksort_cc_z80_50k),
			.fn_test = (T_FN)quicksort_cc_z80_50k,
			.fn_begin = (T_FN)quicksort_cc_z80_50k,
			.fn_end = quicksort_cc_end_z80_50k
		},


		{
			.name = "C v1 MDL",
			.segment = ML_SEGMENT_B(quicksort_c_50k_mdl),
			.fn_test = (T_FN)quicksort_c_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_50k_mdl,
			.fn_end = quicksort_c_end_50k_mdl
		},

		{
			.name = "C++ v1 MDL",
			.segment = ML_SEGMENT_B(quicksort_cc_z80_50k_mdl),
			.fn_test = (T_FN)quicksort_cc_z80_50k_mdl,
			.fn_begin = (T_FN)quicksort_cc_z80_50k_mdl,
			.fn_end = quicksort_cc_end_z80_50k_mdl
		},

	};


	static const T_TEST test_quicksort_50k_1 = {
		
		.name = "Quicksort 50k - 1",
		.test_cases = test_cases_quicksort_50k_1,
		.test_results = test_results_global,
		.n_test_cases = 4,
		.fn_reference = run_reference_quicksort,
		.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
		.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
	};


	static const T_TEST_CASE test_cases_quicksort_50k_2[] = {
		

			{
			.name = "CM SDCC",
			.segment = ML_SEGMENT_B(quicksort_c_50k_mdl),
			.fn_test = (T_FN)quicksort_c_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_50k_mdl,
			.fn_end = quicksort_c_end_50k_mdl
		},

		{
			.name = "CMZ Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Oz_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Oz_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Oz_50k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Oz_50k_mdl
		},

		{
			.name = "CMZ Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Ofast_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Ofast_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Ofast_50k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Ofast_50k_mdl
		},

		{
			.name = "CMA Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Oz_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Oz_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Oz_50k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Oz_50k_mdl
		},

		{
			.name = "CMA Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Ofast_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Ofast_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Ofast_50k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Ofast_50k_mdl
		},

		{
			.name = "C++ avr ",
			.segment = ML_SEGMENT_B(quicksort_cc_avr_50k_mdl),
			.fn_test = (T_FN)quicksort_cc_avr_50k_mdl,
			.fn_begin = (T_FN)quicksort_cc_avr_50k_mdl,
			.fn_end = quicksort_cc_end_avr_50k_mdl
		},

		{
			.name = "d CM SDCC",
			.segment = ML_SEGMENT_B(quicksort_c_50k_mdl),
			.fn_test = (T_FN)quicksort_c_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_50k_mdl,
			.fn_end = quicksort_c_end_50k_mdl
		},

		{
			.name = "d CMZ Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Oz_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Oz_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Oz_50k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Oz_50k_mdl
		},

		{
			.name = "d CMZ Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Ofast_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Ofast_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Ofast_50k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Ofast_50k_mdl
		},

		{
			.name = "d CMA Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Oz_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Oz_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Oz_50k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Oz_50k_mdl
		},

		{
			.name = "d CMA Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Ofast_50k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Ofast_50k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Ofast_50k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Ofast_50k_mdl
		},

		{
			.name = "d C++ avr ",
			.segment = ML_SEGMENT_B(quicksort_cc_avr_50k_mdl),
			.fn_test = (T_FN)quicksort_cc_avr_50k_mdl,
			.fn_begin = (T_FN)quicksort_cc_avr_50k_mdl,
			.fn_end = quicksort_cc_end_avr_50k_mdl
		},

	};

	static const T_TEST test_quicksort_50k_2 = {
		
		.name = "Quicksort 50k - 2",
		.test_cases = test_cases_quicksort_50k_2,
		.test_results = test_results_global,
		.n_test_cases = 12,
		.fn_reference = run_reference_quicksort,
		.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
		.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
	};



	static const T_TEST_CASE test_cases_quicksort_1k_1[] = {
		
		{
			.name = "C v1",
			.segment = ML_SEGMENT_B(quicksort_c_1k),
			.fn_test = (T_FN)quicksort_c_1k,
			.fn_begin = (T_FN)quicksort_c_1k,
			.fn_end = quicksort_c_end_1k
		},

		{
			.name = "C++ v1",
			.segment = ML_SEGMENT_B(quicksort_cc_z80_1k),
			.fn_test = (T_FN)quicksort_cc_z80_1k,
			.fn_begin = (T_FN)quicksort_cc_z80_1k,
			.fn_end = quicksort_cc_end_z80_1k
		},


		{
			.name = "C v1 MDL",
			.segment = ML_SEGMENT_B(quicksort_c_1k_mdl),
			.fn_test = (T_FN)quicksort_c_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_1k_mdl,
			.fn_end = quicksort_c_end_1k_mdl
		},

		{
			.name = "C++ v1 MDL",
			.segment = ML_SEGMENT_B(quicksort_cc_z80_1k_mdl),
			.fn_test = (T_FN)quicksort_cc_z80_1k_mdl,
			.fn_begin = (T_FN)quicksort_cc_z80_1k_mdl,
			.fn_end = quicksort_cc_end_z80_1k_mdl
		},

	};

	static const T_TEST test_quicksort_1k_1 = {
		
		.name = "Quicksort 1k - 1",
		.test_cases = test_cases_quicksort_1k_1,
		.test_results = test_results_global,
		.n_test_cases = 4,
		.fn_reference = run_reference_quicksort,
		.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
		.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
	};



	static const T_TEST_CASE test_cases_quicksort_1k_2[] = {
		
		{
			.name = "CM SDCC",
			.segment = ML_SEGMENT_B(quicksort_c_1k_mdl),
			.fn_test = (T_FN)quicksort_c_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_1k_mdl,
			.fn_end = quicksort_c_end_1k_mdl
		},

		{
			.name = "CMZ Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Oz_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Oz_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Oz_1k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Oz_1k_mdl
		},

		{
			.name = "CMZ Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Ofast_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Ofast_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Ofast_1k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Ofast_1k_mdl
		},

		{
			.name = "CMA Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Oz_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Oz_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Oz_1k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Oz_1k_mdl
		},

		{
			.name = "CMA Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Ofast_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Ofast_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Ofast_1k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Ofast_1k_mdl
		},

		{
			.name = "C++ avr ",
			.segment = ML_SEGMENT_B(quicksort_cc_avr_1k_mdl),
			.fn_test = (T_FN)quicksort_cc_avr_1k_mdl,
			.fn_begin = (T_FN)quicksort_cc_avr_1k_mdl,
			.fn_end = quicksort_cc_end_avr_1k_mdl
		},

		{
			.name = "d CM SDCC",
			.segment = ML_SEGMENT_B(quicksort_c_1k_mdl),
			.fn_test = (T_FN)quicksort_c_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_1k_mdl,
			.fn_end = quicksort_c_end_1k_mdl
		},

		{
			.name = "d CMZ Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Oz_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Oz_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Oz_1k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Oz_1k_mdl
		},

		{
			.name = "d CMZ Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_z80_Ofast_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_z80_Ofast_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_z80_Ofast_1k_mdl,
			.fn_end = quicksort_c_end_clang_z80_Ofast_1k_mdl
		},

		{
			.name = "d CMA Oz",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Oz_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Oz_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Oz_1k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Oz_1k_mdl
		},

		{
			.name = "d CMA Ofast",
			.segment = ML_SEGMENT_B(quicksort_c_clang_avr_Ofast_1k_mdl),
			.fn_test = (T_FN)quicksort_c_clang_avr_Ofast_1k_mdl,
			.fn_begin = (T_FN)quicksort_c_clang_avr_Ofast_1k_mdl,
			.fn_end = quicksort_c_end_clang_avr_Ofast_1k_mdl
		},

		{
			.name = "d C++ avr ",
			.segment = ML_SEGMENT_B(quicksort_cc_avr_1k_mdl),
			.fn_test = (T_FN)quicksort_cc_avr_1k_mdl,
			.fn_begin = (T_FN)quicksort_cc_avr_1k_mdl,
			.fn_end = quicksort_cc_end_avr_1k_mdl
		},


	};

	static const T_TEST test_quicksort_1k_2 = {
		
		.name = "Quicksort 1k - 2",
		.test_cases = test_cases_quicksort_1k_2,
		.test_results = test_results_global,
		.n_test_cases = 12,
		.fn_reference = run_reference_quicksort,
		.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
		.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
	};
	*/


	#undef TEST
	#undef CASE

	#define TEST(ALGO_NAME, TEST_NAME, TEXT, CASES) &ALGO_NAME ## TEST_NAME,  


	const T_TEST *all_tests[] = {

	#include __FILE__

	};

	const uint8_t n_tests = sizeof(all_tests) / sizeof(T_TEST *);

#endif
