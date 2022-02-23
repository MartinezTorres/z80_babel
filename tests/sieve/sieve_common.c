#include <common.h>

ML_MOVE_SYMBOLS_TO(tests, sieve_common);

typedef struct {
	
	uint16_t n_primes;
	uint16_t n_primes_reference;
	uint16_t primes[400];
	uint16_t primes_reference[400];
	uint8_t  work_area[2048];

} T_SIEVE;

__at ((48+2)*1024U) T_SIEVE sieve;

typedef uint16_t (*T_FN_SIEVE)(uint16_t *primes, uint8_t *work, uint16_t max );

void run_sieve(T_FN_SIEVE f) {
	
	memset(sieve.primes, 0, sizeof(sieve.primes));
	
	if (f)
		sieve.n_primes = (*f)(sieve.primes, sieve.work_area, 2048);
}

ML_REQUEST_B(sieve_c_50k);
extern void sieve_c_1_50k();
void reference_sieve() {
	
	uint8_t old = ML_LOAD_MODULE_B(sieve_c_50k);
				
	sieve.n_primes_reference = ((T_FN_SIEVE)sieve_c_1_50k)(sieve.primes_reference, sieve.work_area, 2048);
	ML_RESTORE_B(old);
}

bool verify_sieve(T_TEST *t, T_TEST_CASE *tc) {
	
	(void)t;
	(void)tc;
	
	if (sieve.n_primes != sieve.n_primes_reference) return false;
	
	for (uint16_t i=0; i<sieve.n_primes; i++)
		if (sieve.primes_reference[i] != sieve.primes[i]) return false;
		
	return true;
}

