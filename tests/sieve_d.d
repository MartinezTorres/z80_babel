alias int8_t   = byte;   ///
alias int16_t  = short;  ///
alias uint8_t  = ubyte;  ///
alias uint16_t = ushort; ///
alias int32_t  = int;    ///
alias uint32_t = uint;   ///
alias int64_t  = long;   ///
alias uint64_t = ulong;  ///

extern(C) uint16_t sieve_of_eratosthenes_d_1(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    
    for (uint16_t i = 0; i < work_size; i++) {
        
        work[i] = 0x00;        
    }
    
    uint16_t *p = primes;
    *p++ = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        *p++ = i;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return cast(uint16_t)(cast(uint16_t)(p)-cast(uint16_t)(primes))>>1;
    
}

extern(C) uint16_t sieve_of_eratosthenes_d_1_end() { return cast(uint16_t)(&sieve_of_eratosthenes_d_1); }


extern(C) uint16_t sieve_of_eratosthenes_d_2(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    
    for (uint16_t i = 0; i < work_size; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 1;
    *primes++ = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        *primes++ = i;
        n_primes++;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}

extern(C) uint16_t sieve_of_eratosthenes_d_2_end() { return cast(uint16_t)(&sieve_of_eratosthenes_d_2); }


extern(C) uint16_t sieve_of_eratosthenes_d_3(uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    for (uint16_t i = 0; i < work_size; ++i) {
        
        work[i] = 0x00;        
    }
    uint16_t n_primes = 0;
    primes[n_primes++] = 2;
    
    for (uint16_t i = 3; i < work_size; i+=2) {
        
        if (work[i]) continue;
        
        primes[n_primes++] = i;

        for (uint16_t j = cast(uint16_t)(i + i + i); j < work_size; j += i + i)
            work[j] = 1;
    }
    
    return n_primes;
}

extern(C) uint16_t sieve_of_eratosthenes_d_3_end() { return cast(uint16_t)(&sieve_of_eratosthenes_d_3); }

