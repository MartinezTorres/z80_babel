#include <stdint.h>
#include <megalinker.h>

ML_MOVE_SYMBOLS_TO(sieve_fc, sieve_f_Oz_50k_mdl);

extern int32_t sieve_f__Oz_50k_mdl(uint64_t *, uint64_t *, uint64_t *); 
extern void sieve_f_end__Oz_50k_mdl(); 


uint16_t sieve_fc(uint16_t *primes, uint8_t *work, uint16_t max ) {
	
	return sieve_f__Oz_50k_mdl((uint64_t *)primes, (uint64_t *)work, (uint64_t *)&max);
}

void sieve_fc_end() {
	
}
