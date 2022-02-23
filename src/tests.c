#if defined(LOAD_DEFINITIONS)

	TEST(md5, language, "Language",

		CASE(md5, "C"   , _c  , ,    _50k, T(F_SDCC) + T(B_SDCC) + T(T50K))

		CASE(md5, "C"   , _c  , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(md5, "C"   , _c  , , _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(md5, "C"   , _c  , , _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2"   , _c  , _2 ,    _50k, T(F_SDCC) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2"   , _c  , _2 , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2"   , _c  , _2 , _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2"   , _c  , _2 , _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))
	)

	TEST(quicksort, language, "Language",

		CASE(quicksort, "C"   , _c  , ,    _50k, T(F_SDCC) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C"   , _c  , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C++" , _cc , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C"   , _c  , , _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C++" , _cc , , _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C"   , _c  , , _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(quicksort, "C++" , _cc , , _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, language, "Language",

		CASE(sieve, "ASM" , _asm, , , T(HAND_CODED_ASM))

		CASE(sieve, "C"   , _asm, _llvm_z80, , T(F_LLVM) + T(OZ) + T(B_LLVM_Z80))

		CASE(sieve, "C"   , _c  , _1,    _50k, T(F_SDCC) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C"   , _c  , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++" , _cc , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D"   , _d  , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "ZIG" , _zig,   , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs ,   , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, z_vs_s, "Oz vs Os",

		CASE(sieve, "C", _c , _1, _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Oz_50k, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C", _c , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, fast_vs_s, "Ofast vs Os",

		CASE(sieve, "C", _c , _1, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _O3_50k, T(F_LLVM) + T(O3) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _O3_50k, T(F_LLVM) + T(O3) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C", _c , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, allocs_llvm, "ALLOCS LLVM - 1", 

		CASE(sieve, "C 1K", _c , _1, _Ofast_1k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _1, _Ofast_2k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _1, _Ofast_5k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _1, _Ofast_10k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _1, _Ofast_20k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _1, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _1, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _1, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _1, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)

	TEST(sieve, allocs_llvm_2, "ALLOCS LLVM - 2", 

		CASE(sieve, "C 1K", _c , _2, _Ofast_1k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _2, _Ofast_2k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _2, _Ofast_5k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _2, _Ofast_10k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _2, _Ofast_20k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _2, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _2, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _2, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _2, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)


	TEST(sieve, allocs_llvm_3, "ALLOCS LLVM - 3", 

		CASE(sieve, "C 1K", _c , _3, _Ofast_1k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _3, _Ofast_2k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _3, _Ofast_5k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _3, _Ofast_10k, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _3, _Ofast_20k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _3, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _3, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _3, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _3, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)


	TEST(sieve, allocs_llvm_3_mdl, "ALLOCS LLVM - MDL - 3 ", 

//		CASE(sieve, "C 1K", _c , _3, _Ofast_1k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 2K", _c , _3, _Ofast_2k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _3, _Ofast_5k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _3, _Ofast_10k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _3, _Ofast_20k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _3, _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _3, _Ofast_100k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _3, _Ofast_1000k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _3, _Ofast_10000k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))
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
		O3,
		OF,
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
		[O3] = "-O3",
		[OF] = "-Ofast",
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
		/*static T_TEST_RESULT ALGO_NAME ## TEST_NAME ## _results[sizeof(ALGO_NAME ## TEST_NAME ## _cases)/sizeof(T_TEST_CASE)];*/ \
		static const T_TEST ALGO_NAME ## TEST_NAME = { \
			.name = TEXT " - " # ALGO_NAME, \
			.test_cases = ALGO_NAME ## TEST_NAME ## _cases, \
			.test_results = results /*ALGO_NAME ## TEST_NAME ## _results*/, \
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

	static T_TEST_RESULT results[20];

	#include __FILE__

	#undef TEST
	#undef CASE

	#define TEST(ALGO_NAME, TEST_NAME, TEXT, CASES) &ALGO_NAME ## TEST_NAME,  


	const T_TEST *all_tests[] = {

	#include __FILE__

	};

	const uint8_t n_tests = sizeof(all_tests) / sizeof(T_TEST *);

#endif
