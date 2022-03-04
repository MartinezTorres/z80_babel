	.module sieve_asm
	.optsdcc -mz80
	
	.area _CODE

; Quick & Dirty implmentation of the sieve.
_sieve_asm::

    exx
    pop hl
    exx
    pop bc
    exx
    push hl
    exx

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


