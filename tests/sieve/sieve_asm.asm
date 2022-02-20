;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.14 #12922 (Linux)
;--------------------------------------------------------
	.module sieve_asm
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
;	.globl _sieve_asm_1_end
;	.globl _sieve_asm_1
	
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
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

_sieve_asm::

    di 
    exx
    pop hl
    exx
    pop bc
    exx
    push hl
    exx
    ei

    ; bc work_size
    ; de work
    ; hl primes
    
    ; if work_size == 0 return
	ld a, b
	or a, c
	ret z

	push ix

	push hl ; we'll need the start of primes at the end

    push hl
    pop ix


    ; bc work_size
    ; de work
    ; ix primes
    

    ;for (uint16_t i = 0; i < work_size; i++) {
        
	;	work[i] = 0x00;        
    ;}
    push bc
    push de

    ld h, d
    ld l, e
    dec bc
    inc de
    ld (hl), #0
    ldir

    pop de
    pop bc

        
    ; bc work_size
    ; de work
    ; ix primes
    
    ;uint16_t *p = primes;
    ;*p++ = 2;
	ld 0 (ix), #2
	inc ix
	ld 0 (ix), #0
	inc ix
	
	; bc work_size + work
	ld h, b
	ld l, c
	add hl, de
	ld b, h
	ld c, l
	
	;for (uint16_t i = 3; i < work_size; i+=2) {
	;for (uint16_t i = work + 3; i < work + work_size; i+=2) {
	ld hl, #1
	add hl, de

_begin_loop_1:
	inc hl
	inc hl
	xor a
	sbc	hl, bc
	jp NC, _end_loop_1
	add hl, bc

		;if (work[i]) continue;
	cp (hl)
	jp NZ, _begin_loop_1 

        ;*p++ = i;	
        
    push hl
    push de
    
	sbc hl, de
	ld 0 (ix), l
	inc ix
	ld 0 (ix), h
	inc ix
	
	    ;for (uint16_t j = i + i + i; j < work_size; j += i + i)
        
		ex de, hl
		; de i
		; hl work
		add hl, de
		ex de, hl
		add hl, hl
		ex de, hl
		add hl, de
		; de 2 * i 
		; hl work + 3 * i

_begin_loop_2:
		xor a
		sbc	hl, bc
		jp NC, _end_loop_2
_begin_loop_2_b:
		add hl, bc


            ;work[j] = 1;
		ld (hl), #1
		
		add hl, de

		xor a
		sbc	hl, bc
		jp C, _begin_loop_2_b
		add hl, bc

_end_loop_2:
	pop de
	pop hl
	jp _begin_loop_1
    ;}
_end_loop_1:


    ;return p-primes;
    
    push ix
    pop hl
    xor a
    pop de
    sbc hl, de
    ex de, hl
    
   	sra	d
	rr	e

	pop ix
    ret
     
	
_sieve_asm_end::


_sieve_asm_llvm_z80::

    exx

	push	ix
	ld	ix, #0
	add	ix, sp

	ld	e, 4 (ix)
	ld	d, 5 (ix)
    
    
    pop ix
    
    push de ; work _ size
    
    exx
    
    push de ; work
    push hl ; primes
    push hl ; phony return address

	ld	hl, #-4
	call	__frameset

	
	push	hl
	ld	l, 4 (ix) ;ld hl, primes?
	ld	h, 5 (ix)
	ex	(sp), hl
	pop	iy
	ld	l, 8 (ix) ;ld hl, work_size?
	ld	h, 9 (ix)
	ld	bc, #3
	ld	de, #0

BB0_1:
	or	a, a
	sbc	hl, de
	jr	z, BB0_2
	ld	l, 6 (ix) ; ld hl, work?
	ld	h, 7 (ix)
	add	hl, de
	ld	(hl), #0
	inc	de
	ld	l, 8 (ix) ; ld hl, work_size?
	ld	h, 9 (ix)
	jr	BB0_1
BB0_2:


	ld	hl, #2
	ex	de, hl
	add	iy, de
	push	iy
	ex	(sp), hl
	ld	-2 (ix), l
	ld	-1 (ix), h
	pop	hl
	ld	l, 4 (ix)
	ld	h, 5 (ix)
	ld	(hl), e
	inc	hl
	ld	(hl), d
	push	bc
	pop	iy
	ld	e, 8 (ix)
	ld	d, 9 (ix)
BB0_3:
	push	iy
	pop	hl
	or	a, a
	sbc	hl, de
	jr nc, BB0_12
	push	iy
	pop	de
	ld	l, 6 (ix)
	ld	h, 7 (ix)
	add	hl, de
	ld	a, (hl)
	or	a, a
	jr	nz, BB0_5
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	push	de
	push	iy
	pop	de
	ld	(hl), e
	inc	hl
	ld	(hl), d
	pop	de
	push	iy
	pop	hl
	add	hl, hl
	ld	-4 (ix), l
	ld	-3 (ix), h
	push	iy
	pop	hl
	;ld b, h
	;ld c, l
	;add hl, hl
	;add hl, bc
	call	__smulu
BB0_7:
	ld	c, l
	ld	b, h
	ld	e, 8 (ix)
	ld	d, 9 (ix)
	or	a, a
	sbc	hl, de
	jr	nc, BB0_9
	ld	e, c
	ld	d, b
	ld	l, 6 (ix)
	ld	h, 7 (ix)
	add	hl, de
	ld	(hl), #1
	ld	e, -4 (ix)
	ld	d, -3 (ix)
	ld	l, c
	ld	h, b
	add	hl, de
	jr	BB0_7
BB0_5:
	ld	e, 8 (ix)
	ld	d, 9 (ix)
	ld	bc, #2
	jr	BB0_10
BB0_9:
	ld	bc, #2
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	add	hl, bc
	ld	-2 (ix), l
	ld	-1 (ix), h
BB0_10:
	add	iy, bc
	ld	bc, #3
	jr	BB0_3
BB0_12:
	ld	e,  4 (ix)
	ld	d,  5 (ix)
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	or	a, a
	sbc	hl, de
    
    ex de, hl
    
   	sra	d
	rr	e
        
	ld	sp, ix
	pop	ix
    
    pop hl
    pop hl
    pop hl
    pop hl

	pop	hl
	pop	af
	jp	(hl)
    
	ret
_sieve_asm_llvm_z80_end::
    ret


__frameset:
	pop	de
	push	ix
	ld	ix, #0
	add	ix,sp
	add	hl,sp
	ld	sp,hl
	ex	de,hl
	jp	(hl)

    
__smulu:
	push	af
	push	bc
	push	de
	ld	e,c
	ld	d,b
	call	.mul
	pop	de
	pop	bc
	pop	af
	ret
.mul:
	xor	a
	cp	h
	jr	z,.swap
	ex	de,hl
.swap:
	ld	c,l
	ld	l,a
	add	a,h
	call	nz,.byte__
	ld	a,c
.byte__:
	ld	b,#8
.next:
	add	hl,hl
	add	a,a
	jr	nc,.skip
	add	hl,de
.skip:
	djnz	.next
	ret    

