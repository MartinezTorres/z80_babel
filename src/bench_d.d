alias int8_t   = byte;   ///
alias int16_t  = short;  ///
alias uint8_t  = ubyte;  ///
alias uint16_t = ushort; ///
alias int32_t  = int;    ///
alias uint32_t = uint;   ///
alias int64_t  = long;   ///
alias uint64_t = ulong;  ///


extern(C) uint8_t sum_d(uint8_t a, uint8_t b) {    

    return cast(uint8_t)(a + b);
}

extern(C) uint16_t sieve_of_eratosthenes_d(uint16_t *result, uint8_t *work, uint16_t max ) {
    
    
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
