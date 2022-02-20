#pragma once
#include <common.h>

/*
// C
ML_REQUEST_TEST(sieve_c); 
DEF_TEST(sieve_of_eratosthenes_c_1)
DEF_TEST(sieve_of_eratosthenes_c_2)
DEF_TEST(sieve_of_eratosthenes_c_3)


// C++
ML_REQUEST_TEST(sieve_cc); 
DEF_TEST(sieve_of_eratosthenes_cc_1)
DEF_TEST(sieve_of_eratosthenes_cc_2)
DEF_TEST(sieve_of_eratosthenes_cc_3)


// D LANG
ML_REQUEST_TEST(sieve_d); 
DEF_TEST(sieve_of_eratosthenes_d_1)
DEF_TEST(sieve_of_eratosthenes_d_2)
DEF_TEST(sieve_of_eratosthenes_d_3)


// ZIG
ML_REQUEST_TEST(sieve_zig); 
DEF_TEST(sieve_of_eratosthenes_zig)


// RUST
ML_REQUEST_TEST(sieve_rs); 
DEF_TEST(sieve_of_eratosthenes_rust)

// ASM
ML_REQUEST_TEST(sieve_asm); 
DEF_TEST(sieve_of_eratosthenes_asm)
DEF_TEST(sieve_of_eratosthenes_asm_llvm_z80)

// FORTRAN
ML_REQUEST_TEST(sieve_f); 
DEF_TEST_FORTRAN(sieve_of_eratosthenes_fortran)

static uint16_t sieve_of_eratosthenes_fortran_50k(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran__50k((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
}

static uint16_t sieve_of_eratosthenes_fortran_1k(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran__1k((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
}

static uint16_t sieve_of_eratosthenes_fortran_50k_mdl(uint16_t *primes, uint8_t *work_mdl_ro, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran__50k_mdl((uint64_t *)primes, (uint64_t *)work_mdl_ro, (uint64_t *)&max);
}

static uint16_t sieve_of_eratosthenes_fortran_1k_mdl(uint16_t *primes, uint8_t *work_mdl_ro, uint16_t max ) {
	
	return sieve_of_eratosthenes_fortran__1k_mdl((uint64_t *)primes, (uint64_t *)work_mdl_ro, (uint64_t *)&max);
}*/


typedef struct {
	
	uint16_t n_primes;
	uint16_t n_primes_reference;
	uint16_t primes[400];
	uint16_t primes_reference[400];
	uint8_t  work_area[2048];

} T_SIEVE;

__at ((48+2)*1024U) T_SIEVE sieve;

typedef uint16_t (*T_FN_SIEVE)(uint16_t *primes, uint8_t *work, uint16_t max );

static void run_sieve(T_FN_SIEVE f) {
	
	memset(sieve.primes, 0, sizeof(sieve.primes));
	
	if (f)
		sieve.n_primes = (*f)(sieve.primes, sieve.work_area, 2048);
}

static void reference_sieve() {
	
	uint8_t old = ML_LOAD_MODULE_B(sieve_c_50k);
				
//	sieve.n_primes_reference = ((T_FN_SIEVE)sieve_of_eratosthenes_c_1_50k)(sieve.primes_reference, sieve.work_area, 2048);
	ML_RESTORE_B(old);
}

static bool verify_sieve(T_TEST *t, T_TEST_CASE *tc) {
	
	(void)t;
	(void)tc;
	
	if (sieve.n_primes != sieve.n_primes_reference) return false;
	
	for (uint16_t i=0; i<sieve.n_primes; i++)
		if (sieve.primes_reference[i] != sieve.primes[i]) return false;
		
	return true;
}

