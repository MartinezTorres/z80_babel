#include <stdint.h>

uint16_t sieve_of_eratosthenes_c(uint16_t *out, uint8_t *work, uint16_t max ) {
    
    
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
    
    return p-out;
    
}

