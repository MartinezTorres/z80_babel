#include <hal/tms99X8.h>

////////////////////////////////////////////////////////////////////////
// Memory Copy Functions

#ifdef __SDCC

uint8_t _TMS99X8_tmp;

void _TMS99X8_memcpy_slow(const uint8_t *src) __z88dk_fastcall __nonbanked {
    UNUSED(src);
    __asm
    ld a, (__TMS99X8_tmp)
    ld b, a
    ld c, #_VDP0
__TMS99X8_memcpy_slow_l:
    outi
    jp nz, __TMS99X8_memcpy_slow_l
    __endasm;
}

void _TMS99X8_memset_slow(const uint16_t size_value) __z88dk_fastcall __nonbanked {
    UNUSED(size_value);
    __asm
    ld a, l
__TMS99X8_memset_slow_l:
    out (_VDP0), a // 12 cycles
    dec h // 5 cycles
    jp nz, __TMS99X8_memset_slow_l // 11 cycles
    __endasm;	
}

void _TMS99X8_memcpy_fast_8(const uint8_t *src) __z88dk_fastcall __nonbanked {
    UNUSED(src);
    __asm
    ld a, (__TMS99X8_tmp)
    ld c, #_VDP0
__TMS99X8_memcpy_fast_l:
    outi // 18 cycles
    outi // 18 cycles
    outi // 18 cycles
    outi // 18 cycles

    outi // 18 cycles
    outi // 18 cycles
    outi // 18 cycles
    outi // 18 cycles

	dec a
    jp nz, __TMS99X8_memcpy_fast_l
    __endasm;    
}

void _TMS99X8_memset_fast_8(const uint16_t size8_value) __z88dk_fastcall __nonbanked {
    UNUSED(size8_value);
    __asm
    ld a, l
__TMS99X8_memset_fast_l:
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    out (_VDP0), a // 12 cycles
    dec h // 5 cycles
    jp nz, __TMS99X8_memset_fast_l // 11 cycles
    __endasm;	
}

#else
#endif


////////////////////////////////////////////////////////////////////////
// Mode2 Interface






