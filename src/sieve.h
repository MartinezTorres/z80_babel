#pragma once

ML_REQUEST_B(bench_c); 
ML_REQUEST_B(bench_cc); 
ML_REQUEST_B(bench_d); 
ML_REQUEST_B(bench_zig); 
ML_REQUEST_B(bench_rs); 
ML_REQUEST_B(bench_f); 

#define DEF_SIEVE(F)  \
	uint16_t F##_1k (uint16_t *, uint8_t *, uint16_t); void F##_end_1k (); \
	uint16_t F##_2k (uint16_t *, uint8_t *, uint16_t); void F##_end_2k (); \
	uint16_t F##_5k (uint16_t *, uint8_t *, uint16_t); void F##_end_5k (); \
	uint16_t F##_10k(uint16_t *, uint8_t *, uint16_t); void F##_end_10k(); \
	uint16_t F##_20k(uint16_t *, uint8_t *, uint16_t); void F##_end_20k(); \
	uint16_t F##_50k(uint16_t *, uint8_t *, uint16_t); void F##_end_50k(); 

#define DEF_SIEVE_FORTRAN(F)  \
	int32_t F##__1k (uint64_t *, uint64_t *, uint64_t *); void F##_end__1k (); \
	int32_t F##__2k (uint64_t *, uint64_t *, uint64_t *); void F##_end__2k (); \
	int32_t F##__5k (uint64_t *, uint64_t *, uint64_t *); void F##_end__5k (); \
	int32_t F##__10k(uint64_t *, uint64_t *, uint64_t *); void F##_end__10k(); \
	int32_t F##__20k(uint64_t *, uint64_t *, uint64_t *); void F##_end__20k(); \
	int32_t F##__50k(uint64_t *, uint64_t *, uint64_t *); void F##_end__50k(); 
	

// C
ML_REQUEST_B(sieve_c_1k); 
ML_REQUEST_B(sieve_c_2k); 
ML_REQUEST_B(sieve_c_5k); 
ML_REQUEST_B(sieve_c_10k); 
ML_REQUEST_B(sieve_c_20k); 
ML_REQUEST_B(sieve_c_50k); 

DEF_SIEVE(sieve_of_eratosthenes_c_1)
DEF_SIEVE(sieve_of_eratosthenes_c_2)
DEF_SIEVE(sieve_of_eratosthenes_c_3)


// C++
ML_REQUEST_B(sieve_cc_1k); 
ML_REQUEST_B(sieve_cc_2k); 
ML_REQUEST_B(sieve_cc_5k); 
ML_REQUEST_B(sieve_cc_10k); 
ML_REQUEST_B(sieve_cc_20k); 
ML_REQUEST_B(sieve_cc_50k); 

DEF_SIEVE(sieve_of_eratosthenes_cc_1)
DEF_SIEVE(sieve_of_eratosthenes_cc_2)
DEF_SIEVE(sieve_of_eratosthenes_cc_3)


// D LANG
ML_REQUEST_B(sieve_d_1k); 
ML_REQUEST_B(sieve_d_2k); 
ML_REQUEST_B(sieve_d_5k); 
ML_REQUEST_B(sieve_d_10k); 
ML_REQUEST_B(sieve_d_20k); 
ML_REQUEST_B(sieve_d_50k); 

DEF_SIEVE(sieve_of_eratosthenes_d_1)
DEF_SIEVE(sieve_of_eratosthenes_d_2)
DEF_SIEVE(sieve_of_eratosthenes_d_3)


// ZIG
ML_REQUEST_B(sieve_zig_1k); 
ML_REQUEST_B(sieve_zig_2k); 
ML_REQUEST_B(sieve_zig_5k); 
ML_REQUEST_B(sieve_zig_10k); 
ML_REQUEST_B(sieve_zig_20k); 
ML_REQUEST_B(sieve_zig_50k); 

DEF_SIEVE(sieve_of_eratosthenes_zig)


// RUST
ML_REQUEST_B(sieve_rs_1k); 
ML_REQUEST_B(sieve_rs_2k); 
ML_REQUEST_B(sieve_rs_5k); 
ML_REQUEST_B(sieve_rs_10k); 
ML_REQUEST_B(sieve_rs_20k); 
ML_REQUEST_B(sieve_rs_50k); 

DEF_SIEVE(sieve_of_eratosthenes_rust)


// FORTRAN
ML_REQUEST_B(sieve_f_1k); 
ML_REQUEST_B(sieve_f_2k); 
ML_REQUEST_B(sieve_f_5k); 
ML_REQUEST_B(sieve_f_10k); 
ML_REQUEST_B(sieve_f_20k); 
ML_REQUEST_B(sieve_f_50k); 

DEF_SIEVE_FORTRAN(sieve_of_eratosthenes_fortran)

uint16_t sieve_of_eratosthenes_fortran_50k(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran__50k((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
}

//static uint16_t sieve_of_eratosthenes_fortran_50k(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
//	return sieve_of_eratosthenes_fortran__50k((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
//}


typedef struct {
	
	uint16_t n_primes;
	uint16_t n_primes_reference;
	uint16_t primes[400];
	uint16_t primes_reference[400];
	uint8_t  work_area[2048];

} T_SIEVE;

__at ((48+2)*1024U) T_SIEVE sieve;

typedef uint16_t (*T_FN_SIEVE)(uint16_t *primes, uint8_t *work, uint16_t max );

static void run_test_sieve_of_erastosthenes(T_FN_SIEVE f) {
	
	memset(sieve.primes, 0, sizeof(sieve.primes));
	
	if (f)
		sieve.n_primes = (*f)(sieve.primes, sieve.work_area, 2048);
}

static void run_reference_sieve_of_erastosthenes() {
	
	uint8_t old = ML_LOAD_MODULE_B(sieve_c_50k);
				
	sieve.n_primes_reference = sieve_of_eratosthenes_c_1_50k(sieve.primes_reference, sieve.work_area, 2048);
	ML_RESTORE_B(old);
}

static bool verify_sieve_of_erastosthenes(T_TEST *t, T_TEST_CASE *tc) {
	
	(void)t;
	(void)tc;
	
	if (sieve.n_primes != sieve.n_primes_reference) return false;
	
	for (uint16_t i=0; i<sieve.n_primes; i++)
		if (sieve.primes_reference[i] != sieve.primes[i]) return false;
		
	return true;
}

static const T_TEST_CASE test_cases_sieve_50k[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k
	},

	
	{
		.name = "C v2",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_2_50k,
		.fn_end = sieve_of_eratosthenes_c_2_end_50k
	},

	{
		.name = "C v3",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_end = sieve_of_eratosthenes_c_3_end_50k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},

	{
		.name = "C++ v2",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_2_50k,
		.fn_end = sieve_of_eratosthenes_cc_2_end_50k
	},

	{
		.name = "C++ v3",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_50k
	},


	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_end = sieve_of_eratosthenes_d_1_end_50k
	},
	
	{
		.name = "D v2",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_2_50k,
		.fn_end = sieve_of_eratosthenes_d_2_end_50k
	},

	{
		.name = "D v3",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_3_50k,
		.fn_end = sieve_of_eratosthenes_d_3_end_50k
	},

	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_end = sieve_of_eratosthenes_zig_end_50k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_end = sieve_of_eratosthenes_rust_end_50k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__50k,
		.fn_end = sieve_of_eratosthenes_fortran_end__50k
	},
};

static T_TEST_RESULT test_results_sieve_50k[12];

static const T_TEST test_sieve_50k = {
	
	.name = "Sieve of Eratosthenes (50k)",
	.test_cases = test_cases_sieve_50k,
	.test_results = test_results_sieve_50k,
	.n_test_cases = 12,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};
