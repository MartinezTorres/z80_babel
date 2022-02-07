#include <stdint.h>
#ifdef __SDCC
volatile uint8_t __at (0x6000) __ML_address_a; 
volatile uint8_t __at (0x6800) __ML_address_b; 
volatile uint8_t __at (0x7000) __ML_address_c; 
volatile uint8_t __at (0x7800) __ML_address_d; 
#endif
