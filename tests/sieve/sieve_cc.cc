#include <stdint.h>
#include <stddef.h>

typedef __SIZE_TYPE__ size_t;

//#include <algorithm>

extern "C" {

    uint16_t sieve_cc_1(uint16_t *primes, uint8_t *work, uint16_t work_size );
    uint16_t sieve_cc_2(uint16_t *primes, uint8_t *work, uint16_t work_size );
    uint16_t sieve_cc_3(uint16_t *primes, uint8_t *work, uint16_t work_size );

    uint16_t sieve_cc_1_end();
    uint16_t sieve_cc_2_end();
    uint16_t sieve_cc_3_end();

    extern const uint16_t szzz;

};

const uint16_t szzz = 3;

uint16_t sieve_cc_1(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    
    for (uint16_t i = 0; i < work_size; i++) {
        
        work[i] = 0x00;        
    }
    
    uint16_t *p = primes;
    *p++ = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        *p++ = i;

        for (uint16_t j = i + i + i; j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return p-primes;
}

uint16_t sieve_cc_1_end() { return (uint16_t)&sieve_cc_1; }

uint16_t sieve_cc_2(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    
    for (uint16_t i = 0; i < work_size; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 1;
    *primes++ = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        *primes++ = i;
        n_primes++;

        for (uint16_t j = i + i + i; j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}

uint16_t sieve_cc_2_end() { return (uint16_t)&sieve_cc_2; }


uint16_t sieve_cc_3(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    
    for (uint16_t i = 0; i < work_size; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 0;
    primes[n_primes++] = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        primes[n_primes++] = i;

        for (uint16_t j = i + i + i; j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}

uint16_t sieve_cc_3_end() { return (uint16_t)&sieve_cc_3; }
