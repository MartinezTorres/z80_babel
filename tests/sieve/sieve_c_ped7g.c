#include <stdint.h>

// Author: Ped7g ; (C) 2022 ; license: MIT / GPL / Public Domain (pick whichever fits best for you)
// Updated by Manuel Martinez Torres on 23.Feb.2022 to sdasm format and sdcc call 


// globals defined like this;
#define C4_WORK_SIZE 1024        // same as 2048 work_size for sieve_c_1
// uint16_t g_primes[4000];         // makes sure there's enough room for all results
// uint8_t g_work[C4_WORK_SIZE];    // C4_WORK_SIZE must be >= 2 (to be on par with assumptions used in asm version)

uint16_t sieve_c_ped7g_1( uint16_t *primes, uint8_t *work, uint16_t work_size ) {
    
    (void)primes; (void)work; (void)work_size;
    // using "work" buffer to mark only odd numbers, work[0] belongs to prime 5
    // (work[-1] is prime 3, work[1] is prime 7, work[2] is 9, ...)

    static uint16_t * const g_primes = (uint16_t * const)(0xc800 + 2 + 2);
    static uint8_t *  const g_work   = (uint8_t *  const)(0xc800 + 2 + 2 + 2*400 + 2*400);


    uint16_t* p = g_primes;
    *p++ = 2;                       // hard-code prime 2 into result

    for (uint16_t i = 0; i < C4_WORK_SIZE; ++i) g_work[i] = 0x00;   // reset "work" array

    uint8_t* w = g_work;
    uint8_t* const w_end = g_work + C4_WORK_SIZE;

    // phase 1, search for primes which can mark new fields in sieve, enter directly into marking (for prime 3)
    do {
        // w points at work for i+2 number, and i is prime, mark it in sieve
        uint16_t i = 2 * (w - g_work + 1) + 1;
        *p++ = i;

        uint8_t* mark = w - 1 + i;  // initial mark pointer, check also for 16b overflow on ZX (mark < w) case
        if (w_end <= mark || mark < w) break;   // already outside of work, stop first phase
        while (w < mark && mark < w_end) {      // mark g_work at multiplies of i
            *mark = 1;
            mark += i;
        }
        // search from "w" for next prime
        while (*w++) ;              // and move past the found w[i] == 0
    } while (1);                    // infinite loop breaks when marking would go outside of buffer

    // phase 2, search for remaining large primes, which don't need to mark sieve
    do {
        if (*w++) continue;
        uint16_t i = 2 * (w - g_work + 1) + 1;
        *p++ = i;
    } while (w < w_end);

    return p - g_primes;
}

uint16_t sieve_c_ped7g_1_end() { return (uint16_t)&sieve_c_ped7g_1; }

uint16_t sieve_c_ped7g_2(uint16_t *primes, uint8_t *work, uint16_t work_size) {
    
    (void)primes; (void)work; (void)work_size;
    // using "work" buffer to mark only odd numbers, work[0] belongs to prime 5
    // (work[-1] is prime 3, work[1] is prime 7, work[2] is 9, ...)

    static uint16_t * const g_primes = (uint16_t * const)(0xc800 + 2 + 2);
    static uint8_t  * const g_work   = (uint8_t  * const)(0xc800 + 2 + 2 + 2*400 + 2*400);

    uint16_t* p = g_primes;
    *p++ = 2;                       // hard-code prime 2 into result

    for (uint16_t i = 0; i < C4_WORK_SIZE; ++i) g_work[i] = 0x00;   // reset "work" array

    uint8_t* w = g_work;
    uint8_t* const w_end = g_work + C4_WORK_SIZE;
    uint16_t prime = 3;

    // phase 1, search for primes which can mark new fields in sieve, enter directly into marking (for prime 3)
    do {
        // w points at work for i+2 number, and i is prime, mark it in sieve
        *p++ = prime;
        uint8_t* mark = w - 1 + prime;  // initial mark pointer, check also for 16b overflow on ZX (mark < w) case
        if (w_end <= mark || mark < w) break;   // already outside of work, stop first phase
        while (w < mark && mark < w_end) {      // mark g_work at multiplies of i
            *mark = 1;
            mark += prime;
        }
        // search from "w" for next prime
        while (prime += 2, *w++) ;                // and move past the found w[i] == 0
    } while (1);                    // infinite loop breaks when marking would go outside of buffer

    // phase 2, search for remaining large primes, which don't need to mark sieve
    do {
        if (prime += 2, *w++) continue;
        *p++ = prime;
    } while (w < w_end);

    return p - g_primes;
}

uint16_t sieve_c_ped7g_2_end() { return (uint16_t)&sieve_c_ped7g_2; }
