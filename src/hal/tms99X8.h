#pragma once

#include <hal/msxhal.h>

////////////////////////////////////////////////////////////////////////
// Typedefs


typedef enum {
BTransparent  =0x00U,
BBlack        =0x01U,
BMediumGreen  =0x02U,
BLightGreen   =0x03U,
BDarkBlue     =0x04U,
BLightBlue    =0x05U,
BDarkRed      =0x06U,
BCyan         =0x07U,
BMediumRed    =0x08U,	
BLightRed     =0x09U,
BDarkYellow   =0x0AU,
BLightYellow  =0x0BU,
BDarkGreen    =0x0CU,
BMagenta      =0x0DU,
BGray         =0x0EU,
BWhite        =0x0FU}
TMS99X8_BackgroundColor;

typedef enum {
FTransparent  =0x00U,
FBlack        =0x10U,
FMediumGreen  =0x20U,
FLightGreen   =0x30U,
FDarkBlue     =0x40U,
FLightBlue    =0x50U,
FDarkRed      =0x60U,
FCyan         =0x70U,
FMediumRed    =0x80U,	
FLightRed     =0x90U,
FDarkYellow   =0xA0U,
FLightYellow  =0xB0U,
FDarkGreen    =0xC0U,
FMagenta      =0xD0U,
FGray         =0xE0U,
FWhite        =0xF0U} 
TMS99X8_ForegroundColor;


////////////////////////////////////////////////////////////////////////
// Mode2 Interface

typedef enum {
MODE2_ADDRESS_PN0 = 0x1800,
MODE2_ADDRESS_PN1 = 0x1C00,
MODE2_ADDRESS_CT  = 0x2000,
MODE2_ADDRESS_PG  = 0x0000,
MODE2_ADDRESS_SA0 = 0x1F00,
MODE2_ADDRESS_SA1 = 0x1F80,
MODE2_ADDRESS_SG  = 0x3800} 
EM2_Adresses;

typedef struct {
	uint8_t y,x;
	uint8_t pattern;
	uint8_t color;} 
EM2_Sprite;

#define N_SPRITES 32
#define TILE_WIDTH 32
#define TILE_HEIGHT 24
#define TEX_WIDTH (TILE_WIDTH*8)
#define TEX_HEIGHT (TILE_HEIGHT*8)

typedef uint8_t T_PN[TILE_HEIGHT][TILE_WIDTH]; // Pattern Name Table
typedef U8x8 T_CT[3][256]; // Pattern Color Table
typedef U8x8 T_PG[3][256]; // Pattern Generator Table
typedef EM2_Sprite T_SA[N_SPRITES]; // Sprite Attribute Table
typedef U8x8 T_SG[256]; // Sprite Generator Table

////////////////////////////////////////////////////////////////////////
// Registers and Flags

typedef enum {
TMS99X8_M2 = 0x0002,
TMS99X8_EXTVID = 0x0001,
TMS99X8_MEM416K = 0x8000,
TMS99X8_ENABLE = 0x4000,
TMS99X8_GINT = 0x2000,
TMS99X8_M1 = 0x1000,
TMS99X8_M3 = 0x0800,
TMS99X8_SI = 0x0200,
TMS99X8_MAG = 0x0100} 
TMS99X8_Flags;
typedef uint16_t TMS99X8_TFlags;

typedef struct {
	union {
		uint8_t reg[8];
		uint16_t flags;
		struct {
			struct {
				uint8_t extvid : 1;		
				uint8_t mode2 : 1;
				uint8_t reserved1 : 6;
			};
			struct {
				uint8_t magnifySprites : 1;
				uint8_t sprites16 : 1;
				uint8_t reserved2: 1;
				uint8_t mode3 : 1;
				uint8_t mode1 : 1;
				uint8_t generateInterrupts : 1;
				uint8_t blankScreen : 1;
				uint8_t mem416K : 1;
			};
			uint8_t pn10, ct6, pg11, sa7, sg11;
			struct {
				uint8_t backdrop : 4;
				uint8_t textcolor : 4;
			};
		};
	};
} 
TMS99X8_Register;

typedef struct {
	union {
		uint8_t status;
        struct {
            uint8_t illegalSprite : 5;
            uint8_t C : 1;
            uint8_t _5S : 1;
            uint8_t _int : 1;		
        };
	};
}
TMS99X8_Status;

#ifdef __SDCC
	__sfr __at 0x98 VDP0;
	__sfr __at 0x99 VDP1;
	TMS99X8_Register __at 0xF3DF TMS99X8;
	TMS99X8_Status __at 0xF3E7 TMS99X8_status;
#else
	extern TMS99X8_Register TMS99X8;
	extern TMS99X8_Status TMS99X8_status;
#endif


////////////////////////////////////////////////////////////////////////
// Low Level Interface


#ifdef __SDCC
	INLINE void writeVDP0(uint8_t v) { VDP0 = v; }

	INLINE void writeVDP1(uint8_t v) { VDP1 = v; }

	INLINE uint8_t readVDP1() {	return VDP1; }
#endif

INLINE uint8_t TMS99X8_getStatusFromBios() { return TMS99X8_status.status; }

INLINE uint8_t TMS99X8_readStatus() { return readVDP1(); }

INLINE void TMS99X8_syncRegister(uint8_t reg) {

	writeVDP1(TMS99X8.reg[reg]);
	writeVDP1(0x80 | reg);
}    

INLINE void TMS99X8_syncFlags() {

	register uint8_t *r = (uint8_t *)TMS99X8;
	register uint8_t idx = 0x80;
	REPEAT2( 
		writeVDP1(*r++);
		writeVDP1(idx++);
	);
}    

INLINE void TMS99X8_syncAllRegisters() {

	register uint8_t *r = (uint8_t *)TMS99X8;
	register uint8_t idx = 0x80;
	REPEAT8( 
		writeVDP1(*r++);
		writeVDP1(idx++);
	);
}

INLINE void TMS99X8_setPtr(uint16_t dst) {
	
	writeVDP1(dst & 0xFF); 
	writeVDP1((dst+0x4000)>>8);
}

INLINE void TMS99X8_write(uint8_t val) { writeVDP0(val); }

INLINE void TMS99X8_setRegister(uint8_t reg, uint8_t val) {
	
	TMS99X8.reg[reg] = val; 
	TMS99X8_syncRegister(reg);
}

////////////////////////////////////////////////////////////////////////
// High Level Interface


INLINE void TMS99X8_activateBuffer0() {
	
	TMS99X8.pn10 = MODE2_ADDRESS_PN0 >> 10; 
	TMS99X8.sa7  = MODE2_ADDRESS_SA0 >>  7; 
	TMS99X8_syncRegister(2);
	TMS99X8_syncRegister(5);
}

INLINE void TMS99X8_activateBuffer1() {

	TMS99X8.pn10 = MODE2_ADDRESS_PN1 >> 10; 
	TMS99X8.sa7  = MODE2_ADDRESS_SA1 >>  7; 
	TMS99X8_syncRegister(2);
	TMS99X8_syncRegister(5);
}

INLINE void TMS99X8_debugBorder(TMS99X8_BackgroundColor color) {

	UNUSED(color);
	#if defined DEBUG && defined __SDCC
		VDP1 = color; 
		VDP1 = 0x87;
	#endif
}

extern uint8_t _TMS99X8_tmp;
void _TMS99X8_memcpy_slow(const uint8_t *src) __z88dk_fastcall __nonbanked;
void _TMS99X8_memset_slow(const uint16_t size_value) __z88dk_fastcall __nonbanked; 
void _TMS99X8_memcpy_fast_8(const uint8_t *src) __z88dk_fastcall __nonbanked;
void _TMS99X8_memset_fast_8(const uint16_t size8_value) __z88dk_fastcall __nonbanked;

INLINE void TMS99X8_memcpy(uint16_t dst, const uint8_t *src, uint16_t size) {
	
	if (size==0) return;
	TMS99X8_setPtr(dst);
	if ((uint8_t)(size>>8)>4) {
		const uint8_t *src2 = src;
		for (uint8_t i=0; i<(uint8_t)(size>>8); i++) {
			_TMS99X8_tmp = 0;
			_TMS99X8_memcpy_slow(src2 );
			src2 += 256;
		}
	} else {
		if ((uint8_t)(size>>8)>0) {
			_TMS99X8_tmp = 0;
			_TMS99X8_memcpy_slow(src);
		}
		if ((uint8_t)(size>>8)>1) _TMS99X8_memcpy_slow(src + 1*256);
		if ((uint8_t)(size>>8)>2) _TMS99X8_memcpy_slow(src + 2*512);
		if ((uint8_t)(size>>8)>3) _TMS99X8_memcpy_slow(src + 3*256);
	}
	if (size&0xFF) {
		_TMS99X8_tmp = size&0xFF;
		_TMS99X8_memcpy_slow(src + (size & 0xFF00));
	}
}
    
INLINE void TMS99X8_memset(uint16_t dst, uint8_t value, uint16_t size) {
	
	if (size==0) return;
	TMS99X8_setPtr(dst);
	if ((uint8_t)(size>>8)>4) {
		for (uint8_t i=0; i<(uint8_t)(size>>8); i++) _TMS99X8_memset_slow(value);
	} else {
		if ((uint8_t)(size>>8)>0) _TMS99X8_memset_slow(value);
		if ((uint8_t)(size>>8)>1) _TMS99X8_memset_slow(value);
		if ((uint8_t)(size>>8)>2) _TMS99X8_memset_slow(value);
		if ((uint8_t)(size>>8)>3) _TMS99X8_memset_slow(value);
	}		
	if (size&0xFF) _TMS99X8_memset_slow((size<<8) | value);
}

INLINE void TMS99X8_memcpy_fast(uint16_t dst, const uint8_t *src, uint16_t size) {
	
	if (size==0) return;
	TMS99X8_setPtr(dst);
	if ((uint8_t)(size>>11)>4) {
		const uint8_t *src2 = src;
		for (uint8_t i=0; i<(uint8_t)(size>>11); i++) {
			_TMS99X8_tmp = 0;
			_TMS99X8_memcpy_fast_8(src2);
			src2 += 8 * 256;
		}
	} else {
		if ((uint8_t)(size>>11)>0) {
			_TMS99X8_tmp = 0;
			_TMS99X8_memcpy_fast_8(src);
		}
		if ((uint8_t)(size>>11)>1) _TMS99X8_memcpy_fast_8(src + 1*256);
		if ((uint8_t)(size>>11)>2) _TMS99X8_memcpy_fast_8(src + 2*512);
		if ((uint8_t)(size>>11)>3) _TMS99X8_memcpy_fast_8(src + 3*256);
	}
	if (size&0x7F8) {
		_TMS99X8_tmp = (size>>3) & 0xFF;
		_TMS99X8_memcpy_fast_8(src + (size&0xF800));
	}
	if (size&0x7) {
		src += ((size>>3) & 0xFF) << 3;
		_TMS99X8_tmp = size&0x7;
		_TMS99X8_memcpy_slow(src + (size&0xFFF8));
	}
}
    
INLINE void TMS99X8_memset_fast(uint16_t dst, uint8_t value, uint16_t size) {
	
	if (size==0) return;
	TMS99X8_setPtr(dst);
	if ((uint8_t)(size>>11)>4) {
		for (uint8_t i=0; i<(uint8_t)(size>>11); i++) _TMS99X8_memset_fast_8(value);
	} else {
		if ((uint8_t)(size>>11)>0) _TMS99X8_memset_fast_8(value);
		if ((uint8_t)(size>>11)>1) _TMS99X8_memset_fast_8(value);
		if ((uint8_t)(size>>11)>2) _TMS99X8_memset_fast_8(value);
		if ((uint8_t)(size>>11)>3) _TMS99X8_memset_fast_8(value);
	}		
	if (size&0x7F8) _TMS99X8_memset_fast_8((((size>>3)<<8)) | value);
	if (size&0x008) _TMS99X8_memset_slow(((size&0x07)<<8) | value);
}

INLINE void TMS99X8_setFlags(TMS99X8_TFlags flags) {
	
	
	TMS99X8.flags = flags; 
	TMS99X8_syncFlags();
}

INLINE void TMS99X8_writeSprite8 (uint8_t pos, const U8x8 s) {
	
	TMS99X8_memcpy(MODE2_ADDRESS_SG+(((uint16_t)pos)<<3), (const uint8_t *)s, 8);
}

INLINE void TMS99X8_writeSprite16(uint8_t pos, const U16x16 s) {

	uint8_t tmp[32];
	register uint8_t i;
	register uint8_t *src, *tgt;

	tgt = ((uint8_t *)tmp)+0;
	src = ((uint8_t *)s)+1;
	for (i=0; i<16; i++) {
		*tgt = *src;
		tgt++; src+=2;
	}

	src = ((uint8_t *)s)+0;
	for (i=0; i<16; i++) {
		*tgt = *src;
		tgt++; src+=2;
	}

	tgt = ((uint8_t *)s)+0;
	src = ((uint8_t *)tmp)+0;
	for (i=0; i<32; i++) 
		*tgt++ = *src++;

	TMS99X8_memcpy(MODE2_ADDRESS_SG+(((uint16_t)pos)<<3), (const uint8_t *)s, 32);
}

INLINE void TMS99X8_writeSpriteAttributes0(const T_SA sa) { 
    TMS99X8_memcpy(MODE2_ADDRESS_SA0, (const uint8_t *)sa, sizeof(T_SA)); 
}

INLINE void TMS99X8_writeSpriteAttributes1(const T_SA sa) { 
    TMS99X8_memcpy(MODE2_ADDRESS_SA1, (const uint8_t *)sa, sizeof(T_SA)); 
}

INLINE void TMS99X8_activateMode2() {
	
	TMS99X8.flags = TMS99X8_M2 | TMS99X8_GINT | TMS99X8_MEM416K;

	TMS99X8.ct6  = ((int16_t)MODE2_ADDRESS_CT  >>  6) | 0x7F; // 0b01111111 
	TMS99X8.pg11 = (((int16_t)MODE2_ADDRESS_PG)  >> 11) | 0x03; //0b00000011;
	
	TMS99X8.pn10 =  MODE2_ADDRESS_PN0 >> 10;
	TMS99X8.sa7  =  MODE2_ADDRESS_SA0 >>  7;
	TMS99X8.sg11 =  MODE2_ADDRESS_SG  >> 11;
	
	TMS99X8.backdrop  = BBlack;
	TMS99X8.textcolor = BWhite;
	
	TMS99X8_syncAllRegisters();

	TMS99X8_memset_fast(0,0,16*1024);

	TMS99X8_memset_fast(MODE2_ADDRESS_SA0, 208, sizeof(T_SA));
	TMS99X8_memset_fast(MODE2_ADDRESS_SA1, 208, sizeof(T_SA));

//	TMS99X8_setFlags(TMS99X8_M2 | TMS99X8_ENABLE | TMS99X8_GINT | TMS99X8_MEM416K);
}




