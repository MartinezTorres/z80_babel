#pragma once

ML_REQUEST_B(bench_calibration); 
ML_REQUEST_B(bench_c); 
ML_REQUEST_B(bench_cc); 
ML_REQUEST_B(bench_d); 
ML_REQUEST_B(bench_zig); 
ML_REQUEST_B(bench_rs); 
ML_REQUEST_B(bench_f); 


// EMPTY FUNCTION FOR CALIBRATION
uint16_t sieve_of_eratosthenes_calibration(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_calibration_end();


// C
uint16_t sieve_of_eratosthenes_c_1(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_c_1_end();

uint16_t sieve_of_eratosthenes_c_2(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_c_2_end();

uint16_t sieve_of_eratosthenes_c_3(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_c_3_end();


// C++
uint16_t sieve_of_eratosthenes_cc_1(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_cc_1_end();

uint16_t sieve_of_eratosthenes_cc_2(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_cc_2_end();

uint16_t sieve_of_eratosthenes_cc_3(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_cc_3_end();


// C
uint16_t sieve_of_eratosthenes_d_1(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_d_1_end();

uint16_t sieve_of_eratosthenes_d_2(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_d_2_end();

uint16_t sieve_of_eratosthenes_d_3(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_d_3_end();


// ZIG
uint16_t sieve_of_eratosthenes_zig(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_zig_end();


// RUST
uint16_t sieve_of_eratosthenes_rust(uint16_t *primes, uint8_t *work, uint16_t max );
void sieve_of_eratosthenes_rust_end();


// FORTRAN
int32_t sieve_of_eratosthenes_fortran_(uint64_t*, uint64_t*, uint64_t*);
void sieve_of_eratosthenes_fortran_end_();

static uint16_t sieve_of_eratosthenes_fortran(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran_((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
}



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
	
	uint8_t old = ML_LOAD_MODULE_B(bench_c);
				
	sieve.n_primes_reference = sieve_of_eratosthenes_c_1(sieve.primes_reference, sieve.work_area, 2048);
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

static const T_TEST_CASE test_cases_sieve[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(bench_c),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1,
		.fn_end = sieve_of_eratosthenes_c_1_end
	},

	
	{
		.name = "C v2",
		.segment = ML_SEGMENT_B(bench_c),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_2,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_2,
		.fn_end = sieve_of_eratosthenes_c_2_end
	},

	{
		.name = "C v3",
		.segment = ML_SEGMENT_B(bench_c),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3,
		.fn_end = sieve_of_eratosthenes_c_3_end
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(bench_cc),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1,
		.fn_end = sieve_of_eratosthenes_cc_1_end
	},

	{
		.name = "C++ v2",
		.segment = ML_SEGMENT_B(bench_cc),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_2,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_2,
		.fn_end = sieve_of_eratosthenes_cc_2_end
	},

	{
		.name = "C++ v3",
		.segment = ML_SEGMENT_B(bench_cc),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3,
		.fn_end = sieve_of_eratosthenes_cc_3_end
	},


	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(bench_d),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1,
		.fn_end = sieve_of_eratosthenes_d_1_end
	},
	
	{
		.name = "D v2",
		.segment = ML_SEGMENT_B(bench_d),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_2,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_2,
		.fn_end = sieve_of_eratosthenes_d_2_end
	},

	{
		.name = "D v3",
		.segment = ML_SEGMENT_B(bench_d),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_3,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_3,
		.fn_end = sieve_of_eratosthenes_d_3_end
	},

	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(bench_zig),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig,
		.fn_end = sieve_of_eratosthenes_zig_end
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(bench_rs),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust,
		.fn_end = sieve_of_eratosthenes_rust_end
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(bench_f),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran_,
		.fn_end = sieve_of_eratosthenes_fortran_end_
	},
};

static T_TEST_RESULT test_results_sieve[12];

static const T_TEST test_sieve = {
	
	.name = "Sieve of Eratosthenes",
	.test_cases = test_cases_sieve,
	.test_results = test_results_sieve,
	.n_test_cases = 12,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};
