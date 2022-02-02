#pragma once

// Removes warning for unused expressions
#define UNUSED(expr) do { (void)(expr); } while (0)

#define APPEND_INNER(a,b) a##b
#define APPEND(a,b) APPEND_INNER(a,b)

////////////////////////////////////////////////////////////////////////
// INLINE and FASTCALL
#ifdef __SDCC

	#define INLINE inline

#else

	#define INLINE static inline
    #define __z88dk_fastcall
#endif


////////////////////////////////////////////////////////////////////////
// TYPES

#include <stdint.h>

typedef enum {
	false = 0,
	true = 1 
} bool;

#define nullptr ((void *)0)

typedef struct {
	int16_t x,y,dx,dy;
} TRect16;

typedef struct {
    union { uint8_t x,j; };
    union { uint8_t y,i; };
} uint8_tp;

typedef struct {
    union { int16_t x,j; };
    union { int16_t y,i; };
} int16_tp;

typedef struct {
    union { uint16_t x,j; };
    union { uint16_t y,i; };
} uint16_tp;

typedef uint16_t U16x16[16];
typedef uint8_t  U8x8  [8];

////////////////////////////////////////////////////////////////////////
// COMMON HELPER FUNCTIONS

#define cropped(a,b,c) (a<(b)?(b):(a>(c)?(c):a))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

//#define swap(a,b,c) do { a k_=b; b=c; c=k_; } while(false)

#define REPEAT0(a)  do { } while (false)
#define REPEAT1(a)  do { a; } while (false)
#define REPEAT2(a)  do { REPEAT1(a);  REPEAT1(a);  } while (false)
#define REPEAT3(a)  do { REPEAT1(a);  REPEAT2(a);  } while (false)
#define REPEAT4(a)  do { REPEAT2(a);  REPEAT2(a);  } while (false)
#define REPEAT8(a)  do { REPEAT4(a);  REPEAT4(a);  } while (false)
#define REPEAT16(a) do { REPEAT8(a);  REPEAT8(a);  } while (false)
#define REPEAT32(a) do { REPEAT16(a); REPEAT16(a); } while (false)
#define REPEAT64(a) do { REPEAT32(a); REPEAT32(a); } while (false)
#define REPEAT(N, a) do { \
	if (N&(1<<0)) REPEAT1(a);  \
	if (N&(1<<1)) REPEAT2(a);  \
	if (N&(1<<2)) REPEAT4(a);  \
	if (N&(1<<3)) REPEAT8(a);  \
	if (N&(1<<4)) REPEAT16(a); \
	if (N&(1<<5)) REPEAT32(a); \
	if (N&(1<<6)) REPEAT64(a); \
} while (false)

#define UNROLL1(nn,t,a)  do { if (nn<t) { uint8_t n = nn; a; UNUSED(n); } } while (false)
#define UNROLL2(nn,t,a)  do { if (nn<t) { UNROLL1(nn,t,a);  UNROLL1(nn+1,t,a);   } } while (false)
#define UNROLL4(nn,t,a)  do { if (nn<t) { UNROLL2(nn,t,a);  UNROLL2(nn+2,t,a);   } } while (false)
#define UNROLL8(nn,t,a)  do { if (nn<t) { UNROLL4(nn,t,a);  UNROLL4(nn+4,t,a);   } } while (false)
#define UNROLL16(nn,t,a) do { if (nn<t) { UNROLL8(nn,t,a);  UNROLL8(nn+8,t,a);   } } while (false)
#define UNROLL32(nn,t,a) do { if (nn<t) { UNROLL16(nn,t,a); UNROLL16(nn+16,t,a); } } while (false)
#define UNROLL64(nn,t,a) do { if (nn<t) { UNROLL32(nn,t,a); UNROLL32(nn+32,t,a); } } while (false)

#define UNROLL(t,a)      do { UNROLL64(0,t,a); UNROLL64(64,t,a); } while (false)

////////////////////////////////////////////////////////////////////////
// COMMON ASM INTEGRATIONS

#ifdef __SDCC

	#define NOP(a)  do { __asm nop  __endasm;  } while (false)
	#define DI(a)   do { __asm di   __endasm;  } while (false) // Dangerous, please use wait_frame and yield instead.
	#define EI(a)   do { __asm ei   __endasm;  } while (false) // Dangerous, please use wait_frame and yield instead.
	#define HALT(a) do { __asm halt __endasm;  } while (false) // Dangerous, please use wait_frame and yield instead.

	INLINE void wait_frame(void) { 
		__asm 
			ei
			nop
			halt
			di 
		__endasm;
	}
	INLINE void yield(void) {
		__asm 
			ei
			nop
			di 
		__endasm;
	}
		
//	inline int printf(const char *f, ...) { (f); return 0;}
	#define printf(...)
	#define fflush(a) do {} while(false)
	
	#define memset(d,c,n) __builtin_memset(d,c,n);
	#define memcpy(d,s,n) __builtin_memcpy(d,s,n);
	#define strcpy(d,s) __builtin_strcpy(d,s);

#else

	void yield();
	void wait_frame();

	#define NOP(a)  do { } while (false)
	#define DI(a)
	#define EI(a)
	#define HALT(a) wait_frame()

	#include <stdio.h>
	#include <string.h>

#endif

////////////////////////////////////////////////////////////////////////
// MSX INFO FUNCTIONS

enum    { 
	MSX_CHARACTER_SET_JAPANESE=0x00,
	MSX_CHARACTER_SET_ASCII=0x01,
	MSX_CHARACTER_SET_KOREAN=0x02,

	MSX_DATE_FORMAT_YMD=0x00,
	MSX_DATE_FORMAT_MDY=0x10,
	MSX_DATE_FORMAT_DMY=0x20,

	MSX_FREQUENCY_60HZ=0x00,
	MSX_FREQUENCY_50HZ=0x80,

	MSX_KEYBOARD_TYPE_JAPANESE=0x00,
	MSX_KEYBOARD_TYPE_INTERNATIONAL=0x01,
	MSX_KEYBOARD_TYPE_FRENCH=0x02,
	MSX_KEYBOARD_TYPE_UK=0x03,
	MSX_KEYBOARD_TYPE_GERMAN=0x04,

	MSX_BASIC_VERSION_JAPANESE=0x00,
	MSX_BASIC_VERSION_INTERNATIONAL=0x10,
	
	MSX_VERSION_MSX1=0x00,
	MSX_VERSION_MSX2=0x01,
	MSX_VERSION_MSX2P=0x02,
	MSX_VERSION_MSXTR=0x03

};


#ifdef __SDCC

	#define BIOS_IDBYT1 (*(const uint8_t*)0x002B)
	#define BIOS_IDBYT2 (*(const uint8_t*)0x002C)
	#define BIOS_ROMID  (*(const uint8_t*)0x002D)

#else

	#define BIOS_IDBYT1 (MSX_CHARACTER_SET_ASCII+MSX_DATE_FORMAT_DMY+MSX_FREQUENCY_60HZ)
	#define BIOS_IDBYT2 (MSX_KEYBOARD_TYPE_INTERNATIONAL+MSX_BASIC_VERSION_INTERNATIONAL)
	#define BIOS_ROMID  (MSX_VERSION_MSX1)

#endif


INLINE uint8_t msxhal_get_character_set() { return BIOS_IDBYT1 & 0x0F; }
INLINE uint8_t msxhal_get_date_format()   { return BIOS_IDBYT1 & 0x70; }
INLINE uint8_t msxhal_get_interrupt_frequency() { return BIOS_IDBYT1 & 0x80; }
INLINE uint8_t msxhal_get_keyboard_type() { return BIOS_IDBYT2 & 0x0F; }
INLINE uint8_t msxhal_get_basic_version() { return BIOS_IDBYT2 & 0xF0; }
INLINE uint8_t msxhal_get_msx_version()   { return BIOS_ROMID; }

////////////////////////////////////////////////////////////////////////
// TURBO FUNCTIONS

#ifdef __SDCC

INLINE void msxhal_request60Hz() {
    __asm
    push hl
    push af
    ld   hl,#0xFFE8
    ld   a,(hl)
    and   #0xFD
    ld   (hl),a
    out  (_VDP1),a
    ld   a,#0x89
    out  (_VDP1),a
    pop af
    pop hl
    __endasm; 
}

INLINE void msxhal_enableR800() {
    __asm
    ld   A,(#0x0180) ; CHGCPU
    cp   #0xC3
    ld   a,#0x81              ; can be ld a,81h for R800 ROM if you wish
    call z,#0x0180
    __endasm; 
}

typedef void (*isr_function)();
INLINE void msxhal_install_isr(isr_function new_isr) {

//    void *HTIMI = (void *)0xFD9F;

    *((uint8_t *)0xFD9F) = 0xC3; // JP opcode
    *((isr_function *)(0xFD9F+1)) = new_isr;
}


#else
INLINE void msxhal_request60Hz() {}
INLINE void msxhal_enableR800() {}
#endif

