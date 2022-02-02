;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.14 #12922 (Linux)
;--------------------------------------------------------
	.module bench_asm
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _sieve_of_eratosthenes_asm
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
out:
	.ds 2
work:
	.ds 2
max:
	.ds 2
n_primes:
	.ds 2

;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/bench_c.c:3: uint16_t sieve_of_eratosthenes_c(uint16_t *out, uint8_t *work, uint16_t max ) {
;	---------------------------------
; Function sieve_of_eratosthenes_c
; ---------------------------------
_sieve_of_eratosthenes_asm::

	push	ix
	ld	ix,#0
	add	ix,sp

	ld	b, 4 (ix)
	ld	c, 5 (ix)
	
	pop ix
	
	; store the three variables
	ld (#(max)), bc
	ld (#(work)), de
	ld (#(out)), hl

	; init number of primes: we start with number 2
	ld hl, #1
	ld (#(n_primes)), hl

	ld h, d
	ld l, e
	
	ld	(hl), #2
	inc	hl
	ld	(hl), b	
	inc hl
	ld (#(out)), hl
	
	dec bc
	ld h, d
	ld l, e
	ld (hl), #0
	ldir
	

	ld bc, #1
	
;src/bench_c.c:13: for (uint16_t i = 2; i < max; i++) {	
00100$:
	inc bc
	inc bc
	ld hl, (#(work))
	add hl, bc
	xor a
	xor (hl)
	jr NZ, 00100$
	
	ld hl, (#(n_primes))
	inc hl
	ld (#(n_primes)), hl	
	
	ld hl, (#(out))
	ld	(hl), c
	inc	hl
	ld	(hl), b	
	inc hl
	ld (#(out)), hl
	
	
	
	
	
	
	
	
	
	
	
	
;src/bench_c.c:13: for (uint16_t i = 2; i < max; i++) {
	ld	-4 (ix), c
	ld	-3 (ix), b
	ld	de, #0x0002
00114$:
	ld	a, e
	sub	a, 4 (ix)
	ld	a, d
	sbc	a, 5 (ix)
	jr	NC, 00106$
;src/bench_c.c:15: if (work[i]) continue;
	pop	hl
	push	hl
	add	hl, de
	ld	a, (hl)
	or	a, a
	jr	NZ, 00105$
;src/bench_c.c:17: *p++ = i;
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	(hl), e
	inc	hl
	ld	(hl), d
	ld	a, -4 (ix)
	add	a, #0x02
	ld	-4 (ix), a
	jr	NC, 00154$
	inc	-3 (ix)
00154$:
;src/bench_c.c:19: for (uint16_t j = i+i; j < max; j += i)
	ld	-2 (ix), e
	ld	-1 (ix), d
	sla	-2 (ix)
	rl	-1 (ix)
00111$:
	ld	a, -2 (ix)
	sub	a, 4 (ix)
	ld	a, -1 (ix)
	sbc	a, 5 (ix)
	jr	NC, 00105$
;src/bench_c.c:20: work[j] = 1;
	ld	a, -6 (ix)
	add	a, -2 (ix)
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, -5 (ix)
	adc	a, -1 (ix)
	ld	h, a
	ld	(hl), #0x01
;src/bench_c.c:19: for (uint16_t j = i+i; j < max; j += i)
	ld	a, -2 (ix)
	add	a, e
	ld	-2 (ix), a
	ld	a, -1 (ix)
	adc	a, d
	ld	-1 (ix), a
	jp	00111$
00105$:
;src/bench_c.c:13: for (uint16_t i = 2; i < max; i++) {
	inc	de
	jp	00114$
00106$:
;src/bench_c.c:23: return p-out;
	ld	a, -4 (ix)
	sub	a, c
	ld	e, a
	ld	a, -3 (ix)
	sbc	a, b
	ld	d, a
	sra	d
	rr	e
;src/bench_c.c:25: }
	ld	sp, ix
	pop	ix
	pop	hl
	pop	af
	jp	(hl)
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
