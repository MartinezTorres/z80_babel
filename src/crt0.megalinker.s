    .module crt0_megalinker

; crt0 for MSX ROM of 32KB, starting at 0x4000
;------------------------------------------------

.globl  _main

.globl  ___ML_CONFIG_RAM_START

.globl  ___ML_CONFIG_INIT_ROM_START
.globl  ___ML_CONFIG_INIT_RAM_START
.globl  ___ML_CONFIG_INIT_SIZE

.globl  ___ML_current_segment_a
.globl  ___ML_current_segment_b
.globl  ___ML_current_segment_c
.globl  ___ML_current_segment_d
.globl  ___ML_address_d
.globl  ___ML_address_c
.globl  ___ML_address_b
.globl  ___ML_address_a



.area _DATA
;--------------------------------------------------------
; MSX BIOS CALLS
;--------------------------------------------------------
ENASLT = 0x0024
RSLREG = 0x0138

;--------------------------------------------------------
; MSX BIOS WORK AREA
;--------------------------------------------------------
HIMEM = 0xFC4A
EXPTBL = 0xFCC1

;--------------------------------------------------------
; MSX BIOS SYSTEM HOOKS
;--------------------------------------------------------
HTIMI = 0xFD9F

;--------------------------------------------------------
; DATA
;--------------------------------------------------------
.area _DATA
___ML_CONFIG_RAM_START =   0xC000

;___ML_address_a =   0x6000
;___ML_address_b =   0x6800
;___ML_address_c =   0x7000
;___ML_address_d =   0x7800
___ML_current_segment_a::
    .ds 1
___ML_current_segment_b::
    .ds 1
___ML_current_segment_c::
    .ds 1
___ML_current_segment_d::
    .ds 1

;--------------------------------------------------------
; HEADER
;--------------------------------------------------------

.area _HEADER (ABS)
; Reset vector
    .org 0x4000
    .db  0x41
    .db  0x42
    .dw  init
    .dw  0x0000
    .dw  0x0000
    .dw  0x0000
    .dw  0x0000
    .dw  0x0000
    .dw  0x0000
;
;   .ascii "END ROMHEADER"
;

init:
;   Disables Interruptions
    di

;   We initialize the mapper repeatedly, to trigger correctly megaflashrom and openmsx mapper detection.
    xor a
    ld  (___ML_current_segment_a),a
    ld  (___ML_address_a),a
    ld  (___ML_address_a),a
    inc a
    ld  (___ML_current_segment_b),a
    ld  (___ML_address_b),a
    ld  (___ML_address_b),a
    inc a
    ld  (___ML_current_segment_c),a
    ld  (___ML_address_c),a
    ld  (___ML_address_c),a
    inc a
    ld  (___ML_current_segment_d),a
    ld  (___ML_address_d),a
    ld  (___ML_address_d),a

;   Sets the stack at the top of the memory.
    ld sp,(HIMEM)

; Detection and set of ROM page 2 (0x8000 - 0xbfff)
; based on a snippet taken from: http://karoshi.auic.es/index.php?topic=117.msg1465
    ; Primary slot
    call RSLREG
    di
    rrca
    rrca
    and #0x03
    ; Secondary slot
    ld c, a
    ld hl, #EXPTBL
    add a, l
    ld l, a
    ld a, (hl)
    and #0x80
    or c
    ld c, a
    inc l
    inc l
    inc l
    inc l
    ld a, (hl)
    and #0x0c
    or c
    ld h, #0x80
    call ENASLT     
    di
    
;   copies intial values to RAM
    ld de, #___ML_CONFIG_INIT_RAM_START
    ld hl, #___ML_CONFIG_INIT_ROM_START
    ld bc, #___ML_CONFIG_INIT_SIZE
	ldir
    
.area _NONE
.area _GSINIT
.area _GSFINAL

;   enables interruptions and calls main
    ei
    call    _main 
    
    jp      init


;--------------------------------------------------------
; HOME
;--------------------------------------------------------

    .area   _HOME
    
___sdcc_call_hl::
    jp  (hl)
    
___sdcc_call_ix::
    jp  (ix)
    
___sdcc_call_iy::
    jp  (iy)
    
