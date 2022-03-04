#if defined(LOAD_DEFINITIONS)

	TEST(sieve, language, "Language",

		CASE(sieve, "ASM" , _asm_ped7g, _2, _mdl_dev, T(HAND_CODED_ASM) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "C"   , _asm_llvm  , , _mdl_dev, T(F_LLVM) + T(OS) + T(B_LLVM_Z80) + T(MDL_DEV))

		CASE(sieve, "C"   , _c  , _1,    _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C"   , _c  , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C++" , _cc , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "D"   , _d  , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "ZIG" , _zig,   , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "RUST", _rs ,   , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))
	)

	TEST(sieve, asm_variants, "ASM VARIANTS",

		CASE(sieve, "PED7G v1" , _asm_ped7g, _1, _mdl_dev, T(HAND_CODED_ASM) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "PED7G v2" , _asm_ped7g, _2, _mdl_dev, T(HAND_CODED_ASM) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "MMT" , _asm, , _mdl_dev, T(HAND_CODED_ASM) + T(MDL_DEV))

	)

	TEST(sieve, mdl_improvements, "MDL IMPROVEMENTS",

		CASE(sieve, "ASM+MDL" , _asm_ped7g, _2, _mdl_dev, T(HAND_CODED_ASM) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "C+MDL"   , _c  , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "ZIG+MDL" , _zig,   , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "RUST+MDL", _rs ,   , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "ASM-MDL" , _asm_ped7g, _2, , T(HAND_CODED_ASM) + T(PED7G))

		CASE(sieve, "C-MDL"   , _c  , _1, _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "ZIG-MDL" , _zig,   , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST-MDL", _rs ,   , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)
	

	TEST(sieve, c_variants_llvm, "C VARIANTS (LLVM)",

		CASE(sieve, "C v1"   , _c  , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C v2"   , _c  , _2, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C v3"   , _c  , _3, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C ped7g-1"   , _c_ped7g  , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "C ped7g-2"   , _c_ped7g  , _2, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(PED7G) + T(MDL_DEV))

	)

	TEST(sieve, c_variants_sdcc, "C VARIANTS (SDCC)",

		CASE(sieve, "C v1"   , _c  , _1, _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C v2"   , _c  , _2, _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C v3"   , _c  , _3, _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(sieve, "C ped7g-1"   , _c_ped7g  , _1, _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(PED7G) + T(MDL_DEV))

		CASE(sieve, "C ped7g-2"   , _c_ped7g  , _2, _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(PED7G) + T(MDL_DEV))

	)
	TEST(quicksort, language, "Summary",

		CASE(quicksort, "ASM"   , _asm_ped7g, , _mdl_dev, T(HAND_CODED_ASM) + T(PED7G) + T(MDL_DEV))

		CASE(quicksort, "C"   , _c  , ,    _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C"   , _c  , , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C++" , _cc , , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C"   , _c  , , _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C++" , _cc , , _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C"   , _c  , , _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(quicksort, "C++" , _cc , , _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K) + T(MDL_DEV))
	)

	TEST(md5, language, "Summary",

		CASE(md5, "C"   , _c  , ,    _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K) + T(MDL_DEV))

		CASE(md5, "C no MDL"   , _c  , , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
		
		//CASE(md5, "C"   , _c  , , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		//CASE(md5, "C"   , _c  , , _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		//CASE(md5, "C"   , _c  , , _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2"   , _c  , _2 ,    _50k_mdl_dev, T(F_SDCC) + T(B_SDCC) + T(T50K))

		CASE(md5, "C v2 no MDL"   , _c  , _2 , _Os_50k, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		//CASE(md5, "C v2"   , _c  , _2 , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		//CASE(md5, "C v2"   , _c  , _2 , _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		//CASE(md5, "C v2"   , _c  , _2 , _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))
	)


/*



	TEST(sieve, z_vs_s, "Oz vs Os",

		CASE(sieve, "C", _c , _1, _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Oz_50k_mdl_dev, T(F_LLVM) + T(OZ) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C", _c , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, fast_vs_s, "Ofast vs Os",

		CASE(sieve, "C", _c , _1, _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _O3_50k_mdl_dev, T(F_LLVM) + T(O3) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _O3_50k_mdl_dev, T(F_LLVM) + T(O3) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C", _c , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "C++", _cc , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "D", _d , _1, _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))

		CASE(sieve, "RUST", _rs , , _Os_50k_mdl_dev, T(F_LLVM) + T(OS) + T(B_SDCC) + T(T50K))
	)

	TEST(sieve, allocs_llvm, "ALLOCS LLVM - 1", 

		CASE(sieve, "C 1K", _c , _1, _Ofast_1k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _1, _Ofast_2k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _1, _Ofast_5k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _1, _Ofast_10k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _1, _Ofast_20k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _1, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _1, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _1, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _1, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)

	TEST(sieve, allocs_llvm_2, "ALLOCS LLVM - 2", 

		CASE(sieve, "C 1K", _c , _2, _Ofast_1k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _2, _Ofast_2k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _2, _Ofast_5k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _2, _Ofast_10k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _2, _Ofast_20k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _2, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _2, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _2, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _2, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)


	TEST(sieve, allocs_llvm_3, "ALLOCS LLVM - 3", 

		CASE(sieve, "C 1K", _c , _3, _Ofast_1k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _3, _Ofast_2k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _3, _Ofast_5k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _3, _Ofast_10k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _3, _Ofast_20k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _3, _Ofast_50k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _3, _Ofast_100k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _3, _Ofast_1000k, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _3, _Ofast_10000k, T(F_LLVM) + T(OF) + T(B_SDCC))
	)


	TEST(sieve, allocs_llvm_3_mdl, "ALLOCS LLVM - MDL - 3 ", 

		CASE(sieve, "C 1K", _c , _3, _Ofast_1k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 2K", _c , _3, _Ofast_2k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 5K", _c , _3, _Ofast_5k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 10K", _c , _3, _Ofast_10k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

		CASE(sieve, "C 20K", _c , _3, _Ofast_20k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 50K", _c , _3, _Ofast_50k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 100K", _c , _3, _Ofast_100k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 1M", _c , _3, _Ofast_1000k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))

//		CASE(sieve, "C 10M", _c , _3, _Ofast_10000k_mdl_dev, T(F_LLVM) + T(OF) + T(B_SDCC))
	)

*/
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
		PED7G,
		T50K,
		MDL, 
		MDL_DEV,
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
		[PED7G] = "by PED7G",
		[B_SDCC] = "SDCC BACK",
		[T50K] = "50.000 MAX-ALLOCS",
		[MDL] = "MDL",
		[MDL_DEV] = "MDL DEV",
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
