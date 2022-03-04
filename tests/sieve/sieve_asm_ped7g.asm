	.module sieve_asm_ped7g
	.optsdcc -mz80
	
	.area _CODE

; Author: Ped7g ; (C) 2022 ; license: MIT / GPL / Public Domain (pick whichever fits best for you)
; Updated by Manuel Martinez Torres on 23.Feb.2022 to sdasm format and sdcc call 
; based on https://github.com/MartinezTorres/z80_babel project, written as comparison
_sieve_asm_ped7g_1::
	
    pop iy
    pop bc
    push iy
    push ix

    ; bc work_size
    ; de work
    ; hl primes

	push hl
	pop ix

    ; IX = primes
    ; DE = work (can overlap primes starting from primes+2 address)
    ; BC = work_size
    ; 108 bytes

    ; primes[0] = 2;
    xor     a
    ld       0 (ix),#2
    ld      +1 (ix),a

    ; if work_size is < 4, return only one prime number 2
    ld      hl,#-4
    add     hl,bc
    jr      nc,.small_size

    ; 4 <= work_size asserted

    push    ix          ; store "primes" into stack for return code, IX becomes "p"
    inc     ix
    inc     ix          ; p++; (2 is already written)

    ; clear the work buffer (from 0, like C code, even if starting from 3 is enough)
    ; for (uint16_t i = 0; i < work_size; i++) work[i] = 0x00;
    ld      l,e         ; HL = work
    ld      h,d
    push    hl          ; preserve original "work" on stack
    inc     de
    ld      (hl),a
    dec     bc
    ldir

    ; HL = work + work_size - 1 => inverted equals to -(work+work_size) -> useful constant for tests
    ld      a,l
    cpl
    ld      e,a
    ld      a,h
    cpl
    ld      d,a         ; DE = -(work+work_size)

    ; outer loop checking numbers
    ; for (uint16_t i = 3; i < work_size; i+=2) {
    ld      a,#1         ; useful constant to check/fill work buffer
    ld      c,a         ; BC = i-2 = 1 (BC was zero from `ldir`)
.outer_loop:
    pop     hl
    push    hl
    inc     bc          ; i += 2
    inc     bc
    add     hl,bc       ; HL = work+i
    jr      c,.outer_loop_done

    ;   if (work[i]) continue;
    cp      (hl)        ; set ZF (the HL may be invalid here)

    ; test (i < work_size) <=> work+i < work+work_size <=> -(work+work_size)+work+i < 0
    add     hl,de       ; preserves ZF
    jr      c,.outer_loop_done

    jr      z,.outer_loop   ; "continue" part of `if (work[i])`
    sbc     hl,de       ; restore HL back to work+i

    ; is prime ; HL = work+i, BC = i, DE = -(work+work_size), IX = p
    ;   *p++ = i
    ld       0 (ix),c
    ld      +1 (ix),b
    inc     ix
    inc     ix

    ; inner loop setting the sieve
    ; for (uint16_t j = i + i + i; j < work_size; j += i + i) work[j] = 1;
    push    bc
    push    de
    ex      de,hl
    add     hl,bc
    jr      c,.inner_setup_ov_1
    add     hl,bc
    jr      c,.inner_setup_ov_1
    ld      c,l
    ld      b,h
    ex      de,hl       ; BC = i+i-(work+work_size), HL = work+i
    pop     de          ; DE = -(work+work_size)
    jr      .inner_loop_entry

.inner_setup_ov_1:
    pop     de
    pop     bc
    jr      .outer_loop

.inner_loop_1:
    sbc     hl,de       ; restore hl to hl+j
    ld      (hl),a      ; work[j] = 1
.inner_loop_entry:
    add     hl,bc       ; hl += i+i + test for work_size, none of this overflow
    jr      nc,.inner_loop_1
    pop     bc
    jr      .outer_loop

.outer_loop_done:
    ; return p-primes;
    pop     de          ; throw away "work" pointer
    pop     hl          ; primes
    .db 0xDD, 0x7D ;ld      a,ixl
    sub     l
    ld      l,a
    .db 0xDD, 0x7C ;ld      a,ixh
    sbc     a,h         ; cf:A:L = (p - primes) * 2; // technically 17b result
    rra
    rr      l
    ld      h,a         ; HL = number of primes

	ex      de,hl
    pop ix
    ret

.small_size:
    ld      de, #1
    pop ix
    ret                 ; return value 1 (number of primes in `primes`)

_sieve_asm_ped7g_1_end::
	ret
    


    

;typedef struct {
	
;	uint16_t n_primes;
;	uint16_t n_primes_reference;
;	uint16_t primes[400];
;	uint16_t primes_reference[400];
;	uint8_t  work_area[2048];

;} T_SIEVE;

_sieve	=	0xc800
primes  =   0xc800 + 2 + 2
work    =   0xc800 + 2 + 2 + 2*400 + 2*400

work_size   =     1023 ; enough for 2860 primes, ending with 25999 (same as 26000 buffer for sieve_c_1)


;----------------------------------------------------------------------------------------------------------------------
; "primes" and "work" buffers

;primes:     ds      2*primes_size,$AA
;work:       ds      work_size,$BB


;----------------------------------------------------------------------------------------------------------------------
; 138B hand written asm sieve optimised for performance, taking many shortcuts, using odd-number-only sieve
; "work" can overlap "primes" starting from primes+8 address (to maximise amount of primes calculated and returned)
_sieve_asm_ped7g_2::

    pop iy
    pop bc
    push iy
    push ix

    ; bc work_size
    ; de work
    ; hl primes

    ;ASSERT high work && 2 <= work_size
    ;ASSERT (primes + 8 <= work) || (work + work_size <= primes)
    ;ASSERT work + work_size <= 0xFFFF   ; if work buffer would have last byte at 0xFFFF, the calculation of "i" breaks

    ; logical : memory address offset into work buffer, storing only odd numbers sieve
    ; work[3] : -1 (not stored in memory at all)
    ; work[5] : +0
    ; work[7] : +1
    ; work[9] : +2

    ; *p++ = 2;
    ld      ix, #primes
    xor     a
    ld       0 (ix), #2
    ld      +1 (ix),  a
    inc     ix
    inc     ix

    ; clear the work buffer (full clear, first byte of buffer is marker for prime 5)
    ; for (uint16_t i = 0; i < work_size; i++) work[i] = 0x00;
    ld      hl, # work
    ld      de, # work+1
    ld      bc, # work_size-1
    ld      (hl), a
    ldir

    ld      hl, #work
    ld      bc, #work_size

    ; mark prime 3 without searching by starting .mark_and_loop at work[5]

.mark_and_loop:
    ; work[i] signals prime ; IX = p, HL = work[i+2] = work + (i-5)/2 + 1, BC = bytes to check (>0)
    ex      de,hl
    ; i = 2*(hl - work + 1) + 1
    ld      hl,# 1-work
    add     hl,de       ; always cf=1 when 0xFFFF is not part of work buffer
    adc     hl,hl

    ; *p++ = i;
    ld       0 (ix),l
    ld      +1 (ix),h
    inc     ix
    inc     ix

    ; IX = p, HL = i, DE = work[i+2], BC = bytes to check (BTW DE+BC = work.end(), but unable to use it)

    ; mark work buffer at all multiplies of `i` (inner loop setting the sieve)
    ; for (uint16_t j = i + i + i; j < work_size; j += i+i) work[j] = 1;
    push    bc          ; preserve bytes to check
    push    de          ; preserve work[i+2]
    ld      bc, # -(work+work_size)
    add     hl,bc       ; HL = i-(work+work_size)   ; constant to check buffer overrun and add i+i to "j"
    jr      c,.inner_setup_ov   ; when this happens, it happens for all following primes -> faster final loop
    ex      de,hl
    dec     hl          ; HL = work[i], DE = i-(work+work_size), BC = -(work+work_size)
    add     hl,de       ; j = i + i + i (adjusting work[j] address), plus test for work_size, must not overflow
    jr      c,.inner_setup_ov   ; when this happens, it happens for all following primes -> faster final loop
.inner_loop:
    sbc     hl,bc       ; restore hl to hl+j
    ld      (hl),h      ; work[j] = non_zero_value
    add     hl,de       ; hl += i + test for work_size, must not overflow
    jp      nc,.inner_loop
    pop     hl          ; restore work[i+2] pointer = next to check
    pop     bc          ; restore bytes to check

    ; outer_loop ; for (uint16_t i = 3; i < work_size; i+=2)
    cpir
    jp      pe,.mark_and_loop   ; zf=1, pv=1
    ; pv=0 case is UNREACHABLE ; should never happen, because sooner the inner loop setup will overflow

    ; outer_loop phase 2, when marking primes is always impossible, (j >= work_size) == true because of large i
.inner_setup_ov:
    pop     hl          ; restore work[i+2] pointer = next to check
    pop     bc          ; restore bytes to check
    jp      .final_loop_entry

.final_loop:
    ; work[i] signals prime ; IX = p, HL = work[i+2] = work + (i-5)/2 + 1, BC = bytes to check (>0)
    ex      de,hl
    ; i = 2*(hl - work + 1) + 1
    ld      hl, # 1-work
    add     hl,de       ; always cf=1 when 0xFFFF is not part of work buffer
    adc     hl,hl
    ; *p++ = i;
    ld      0 (ix),l
    ld      1 (ix),h
    inc     ix
    inc     ix
    ex      de,hl       ; restore HL to work[i+2] and continue with final loop
.final_loop_entry:
    cpir
    jp      pe,.final_loop  ; zf=1, pv=1
    jr      nz,.final_loop_done ; zf=0, pv=0 (last work[i] was not prime)

    ; zf=1, pv=0 (match at last byte) - store last prime
    ld      de, #1-work
    add     hl,de       ; always cf=1 when 0xFFFF is not part of work buffer
    adc     hl,hl
    ; *p++ = i;
    ld      0 (ix),l
    ld      1 (ix),h
    inc     ix
    inc     ix

.final_loop_done:
    ; return p-primes;
    .db 0xDD, 0x7D ;ld      a,ixl
    sub     #<(primes)
    ld      l,a
    .db 0xDD, 0x7C ;ld      a,ixh
    sbc     a,#>(primes)
    rra
    ld      h,a
    rr      l           ; HL = number of primes

	ex      de,hl
    pop ix
    ret

_sieve_asm_ped7g_2_end::
	ret

