#include <stdint.h>
#include <stddef.h>

typedef __SIZE_TYPE__ size_t;

#include <algorithm>

extern "C" {

    uint16_t sieve_of_eratosthenes_cc_1(uint16_t *out, uint8_t *work, uint16_t max );
    uint16_t sieve_of_eratosthenes_cc_2(uint16_t *out, uint8_t *work, uint16_t max );
    uint16_t sieve_of_eratosthenes_cc_3(uint16_t *out, uint8_t *work, uint16_t max );

    void sieve_of_eratosthenes_cc_1_end();
    void sieve_of_eratosthenes_cc_2_end();
    void sieve_of_eratosthenes_cc_3_end();


};

uint16_t sieve_of_eratosthenes_cc_1(uint16_t *out, uint8_t *work, uint16_t max ) {
    
    
    for (uint16_t i = 0; i < max; i++) {
        
        work[i] = 0x00;        
    }
    
    uint16_t *p = out;
    *p++ = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        *p++ = i;

        for (uint16_t j = i + i + i; j < max; j += i + i)
            work[j] = 1;
    }
    
    
//    std::sort(&out[0], &out[10]);
    
    return p-out;
}
void sieve_of_eratosthenes_cc_1_end() {}

uint16_t sieve_of_eratosthenes_cc_2(uint16_t *out, uint8_t *work, uint16_t max ) {
    
    
    for (uint16_t i = 0; i < max; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 1;
    *out++ = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        *out++ = i;
        n_primes++;

        for (uint16_t j = i + i + i; j < max; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}
void sieve_of_eratosthenes_cc_2_end() {}


uint16_t sieve_of_eratosthenes_cc_3(uint16_t *out, uint8_t *work, uint16_t max ) {
    
    
    for (uint16_t i = 0; i < max; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 0;
    out[n_primes++] = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        out[n_primes++] = i;

        for (uint16_t j = i + i + i; j < max; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}
void sieve_of_eratosthenes_cc_3_end() {}
