alias int8_t   = byte;   ///
alias int16_t  = short;  ///
alias uint8_t  = ubyte;  ///
alias uint16_t = ushort; ///
alias int32_t  = int;    ///
alias uint32_t = uint;   ///
alias int64_t  = long;   ///
alias uint64_t = ulong;  ///

extern(C) uint16_t sieve_of_eratosthenes_d_1(uint16_t *result, uint8_t *work, uint16_t max ) {
    
    
    for (uint16_t i = 0; i < max; i++) {
        
        work[i] = 0x00;        
    }
    
    uint16_t *p = result;
    *p++ = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        *p++ = i;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < max; j += i + i)
            work[j] = 1;
    }
    
    return cast(uint16_t)(cast(uint16_t)(p)-cast(uint16_t)(result))>>1;
    
}
extern(C) void sieve_of_eratosthenes_d_1_end() {}


extern(C) uint16_t sieve_of_eratosthenes_d_2(uint16_t *result, uint8_t *work, uint16_t max ) {
    
    
    for (uint16_t i = 0; i < max; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 1;
    *result++ = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        *result++ = i;
        n_primes++;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < max; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}
extern(C) void sieve_of_eratosthenes_d_2_end() {}


extern(C) uint16_t sieve_of_eratosthenes_d_3(uint16_t *result, uint8_t *work, uint16_t max ) {
    
    for (uint16_t i = 0; i < max; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 0;
    result[n_primes++] = 2;
    
    for (uint16_t i = 3; i < max; i+=2) {
        
        if (work[i]) continue;
        
        result[n_primes++] = i;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < max; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}
extern(C) void sieve_of_eratosthenes_d_3_end() {}
