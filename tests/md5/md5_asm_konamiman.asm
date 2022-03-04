	.module md5_asm_konamiman
	.optsdcc -mz80
	
	.area _CODE

; https://github.com/Konamiman/MSX/blob/master/SRC/INL1/INL-RES.ASM#L5462


;--- MD5 Message-Digest algorithm for Z80 processor
;    Conforming to RFC1321
;    By Nestor Soriano (Konami Man), 27-5-2001
;    http://www.konamiman.com
;    <konamiman@konamiman.com>

	;Input:  HL = Address of message to digest
	;        BC = Length of message in bytes (maximum 8191)
	;Output: HL = Address where calculated digest is stored

	;NOTE: A 72 byte buffer for padding must be placed
	;      IMMEDIATELY AFTER the message (that is, at address HL+BC)
	;For example:
	;      ld hl,MSG
	;      ld bc,18
	;      call MD5
	;      ret
	;MSG:  defb "This is a message!"
	;      defs 72

	;Only messages using complete bytes are supported
	;(that is, the number of bits must be multiple of 8)

	;This source code is for the MSX assembler COMPASS,
	;other assemblers may differ in the macros syntax

	;Some values for testing (taken from RFC1321):

	;MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
	;MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
	;MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
	;MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
	;MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
	;MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") =
	;d174ab98d277d9f5a5611c2c9f419d9f
	;MD5 ("123456789012345678901234567890123456789012345678901234567890123456
	;78901234567890") = 57edf4a22be3c955ac49da2e2107b67a


	;--- Macro for 32 bit addition

m_add32:	macro	@a,@b	;Performs (@a) = (@a) + (@b)
	ld	hl,(@a)
	ld	bc,(@b)
	add	hl,bc
	ld	(@a),hl
	ld	hl,(@a+2)
	ld	bc,(@b+2)
	adc	hl,bc
	ld	(@a+2),hl
	endm


	;----------------------
	;---  MAIN PROGRAM  ---
	;----------------------

MD5:	ld	(MSG_PNT),hl
	ld	(MSG_LEN),bc

	;--- Step 1: append padding bits

	add	hl,bc
	ld	(hl),80h	;First adds the mandatory padding "1" bit
	inc	bc
	inc	hl

	ld	a,c
	and	3Fh
	cp	56
	jr	z,OKPAD1	;No more padding necessary if already
	sub	56	;congruent to 56 bytes, modulo 64
	neg
	and	3Fh	;Now A=Number of 0 bytes to add

	ld	b,a	;Adds padding "0" bits
PADLOOP:
	ld	(hl),0
	inc	hl
	djnz	PADLOOP
OKPAD1:	;

	;--- Step 2: append length

	push	hl
	ld	hl,(MSG_LEN)
	ld	bc,(MSG_LEN)
	add	hl,bc
	add	hl,hl
	add	hl,hl
	push	hl
	pop	bc	;Now BC = Length of message in bits
	pop	hl
	ld	(hl),c
	inc	hl
	ld	(hl),b	;Appends length to the end of the message
	inc	hl

	ld	b,6	;Since length is 2 bytes long and
PADLOP2:
	ld	(hl),0	;8 bytes are required, adds another
	inc	hl	;6 zero bytes
	djnz	PADLOP2

	ld	bc,(MSG_PNT)	;Calculates total message length
	or	a	;in bytes, which is multiple of 64
	sbc	hl,bc

	ld	b,6
PADLOP3:
	srl	h	;Calculates the message length
	rr	l	;in blocks of 16 32-bit words
	djnz	PADLOP3	;(that is, divides length by 64)
	ld	(MSG_BLK),hl

	;--- Step 3: initialize buffer

	ld	hl,INIT_ABCD
	ld	de,BUF_A
	ld	bc,16
	ldir

	;--- Step 4: process blocks

	;* Copy current block to buffer X:
	;  No need for that! Message data is read directly,
	;  and value of (MSG_PNT) acts as the starting address of X

	;* Backup A,B,C,D

PBLOCKS:
	ld	hl,BUF_A	;Sets buffers AA,BB,CC,DD
	ld	de,BUF_AA
	ld	bc,16
	ldir

	;* Rounds execution

	ld	hl,R_DATA
	ld	(ROUND_PNT),hl
	ld	a,1
	ld	(ROUND_N),a
	ld	(PAR_I),a

	call	ROUND
	call	ROUND
	call	ROUND
	call	ROUND

	;* Adds AA to A, BB to B, CC to C, DD to D

	m_add32	BUF_A,BUF_AA
	m_add32	BUF_B,BUF_BB
	m_add32	BUF_C,BUF_CC
	m_add32	BUF_D,BUF_DD

	;* Continues to next block, if any

	ld	bc,(MSG_BLK)
	dec	bc
	ld	a,b
	or	c
	jr	z,MD5END
	ld	(MSG_BLK),bc

	ld	hl,(MSG_PNT)	;Updates message pointer by adding 64
	ld	bc,64
	add	hl,bc
	ld	(MSG_PNT),hl
	jp	PBLOCKS

	;--- Step 5: output

MD5END:	ld	hl,BUF_A
	ret


	;--------------------------------
	;---  ROUTINES AND FUNCTIONS  ---
	;--------------------------------

	;--- Sets parameters for round execution and executes round;
	;    after each operation exchanges A,B,C,D, and after
	;    the entire round increases ROUND_N

ROUND:	ld	b,16	;There are 16 operations per round

DO_RLOOP:
	push	bc
	ld	hl,(ROUND_PNT)
	ld	a,(hl)
	ld	(PAR_K),a	;Sets parameters and executes operation
	inc	hl
	ld	a,(hl)
	ld	(PAR_S),a
	inc	hl
	ld	(ROUND_PNT),hl
	call	ROUND_OP
	call	SH_ABCD	;After each operation A,B,C,D are shifted
	ld	hl,PAR_I	;and PAR_I is increased
	inc	(hl)
	pop	bc
	djnz	DO_RLOOP

	ld	hl,ROUND_N	;After the 16 operations, round number
	inc	(hl)	;is increased
	ret

	;--- SH_ABCD: Transforms ABCD into DABC, DABC into CDAB, CDAB into BCDA,
	;             or BCDA into ABCD

SH_ABCD:
	ld	hl,BUF_D+3	;D->temp
	ld	de,RES_FGHI+3
	ld	bc,4
	lddr

	ld	de,BUF_D+3
	ld	c,12	;C->D, B->C, A->B
	lddr

	ld	hl,RES_FGHI+3
	ld	c,4	;temp->A
	lddr

	ret

	;--- Function for ROUND operation execution
	;    Executes  A = B + ((A + F/G/H/I(B,C,D) + X[k] + T[i]) <<< s)
	;              where F,G,H,I is choosen when ROUND_N is 1,2,3,4 respectively
	;    Input:  PAR_K, PAR_S and PAR_I appropriately set
	;            ABCD buffer approriately rotated so it is ABCD,DABC,CDAB or BCDA
	;            ROUND_N set to 1,2,3 or 4
	;    Output: BUF_A with the result of the operation

ROUND_OP:
	ld	a,(ROUND_N)	;Calls function F,G,H or I
	ld	hl,FUN_F	;depending on the round number
	dec	a
	jr	z,OKR1
	ld	hl,FUN_G
	dec	a
	jr	z,OKR1
	ld	hl,FUN_H
	dec	a
	jr	z,OKR1
	ld	hl,FUN_I
OKR1:	ld	de,OKR2
	push	de
	jp	(hl)
OKR2:	;

	m_add32	BUF_A,RES_FGHI	;Adds A to the result of F/G/H/I
	;                        ;and stores result on A

	ld	a,(PAR_K)	;Adds X[k] to the previous result
	ld	ix,(MSG_PNT)	;and stores it to A again.
	call	ADD_XT	;Note that actually no X buffer is used.

	ld	a,(PAR_I)	;Adds T[i] to the previous result
	dec	a	;ans stores it to A again
	ld	ix,BUF_T
	call	ADD_XT

	ld	ix,BUF_A	;Shifts s bits A
	ld	a,(PAR_S)
	ld	b,a
	call	SHIFT

	m_add32	BUF_A,BUF_B	;Finally, adds B to A

	ret

ADD_XT:	ld	c,a	;Routine for adding X[k] or T[i] to A
	ld	b,0	;Input: IX=(MSG_PNT) and A=(PAR_K)
	add	ix,bc	;or IX=BUF_T and A=(PAR_I)-1
	add	ix,bc
	add	ix,bc
	add	ix,bc
	ld	l,(ix+0)
	ld	h,(ix+1)
	ld	de,(BUF_A)
	add	hl,de
	ld	(BUF_A),hl
	ld	l,(ix+2)
	ld	h,(ix+3)
	ld	de,(BUF_A+2)
	adc	hl,de
	ld	(BUF_A+2),hl
	ret

	;--- Circular left shifting of a 32 bit word (stored low byte first)
	;    Input: IX = Pointer to the word, B = Positions to shift

SHIFT:	sla	(ix+0)
	rl	(ix+1)
	rl	(ix+2)
	rl	(ix+3)
	jr	nc,SHIFT2
	set	0,(ix+0)
SHIFT2:	djnz	SHIFT
	ret

	;--- Function F

nXaZ:	macro	@n	;Calculates "not(X) and Z"
	ld	a,(ix+@n)	;for the byte @n (0 to 3)
	cpl		;                ;of the 32-bit word
	and	(ix+8+@n)
	ld	(iy+@n),a
	endm

XaYo:	macro	@n	;Calculates "X and Y or nXaZ"
	ld	a,(ix+@n)
	and	(ix+4+@n)
	or	(iy+@n)
	ld	(iy+@n),a
	endm

FUN_F:	call	FUN_SETP

	nXaZ	0
	nXaZ	1
	nXaZ	2
	nXaZ	3

	XaYo	0
	XaYo	1
	XaYo	2
	XaYo	3

	ret

	;--- Function G

nZaY:	macro	@n	;Calculates "not(Z) and Y"
	ld	a,(ix+8+@n)
	cpl
	and	(ix+4+@n)
	ld	(iy+@n),a
	endm

XaZo:	macro	@n	;Calculates "X and Z or nZaY"
	ld	a,(ix+@n)
	and	(ix+8+@n)
	or	(iy+@n)
	ld	(iy+@n),a
	endm

FUN_G:	call	FUN_SETP

	nZaY	0
	nZaY	1
	nZaY	2
	nZaY	3

	XaZo	0
	XaZo	1
	XaZo	2
	XaZo	3

	ret

	;--- Function H

XxYxZ:	macro	@n	;Calculates "X xor Y xor Z"
	ld	a,(ix+@n)
	xor	(ix+4+@n)
	xor	(ix+8+@n)
	ld	(iy+@n),a
	endm

FUN_H:	call	FUN_SETP

	XxYxZ	0
	XxYxZ	1
	XxYxZ	2
	XxYxZ	3

	ret

	;--- Function I

XonZ:	macro	@n	;Calculates "X or (not Z)"
	ld	a,(ix+8+@n)
	cpl
	or	(ix+@n)
	ld	(iy+@n),a
	endm

Yx:	macro	@n	;Calculates "Y xor XonZ"
	ld	a,(ix+4+@n)
	xor	(iy+@n)
	ld	(iy+@n),a
	endm

FUN_I:	call	FUN_SETP

	XonZ	0
	XonZ	1
	XonZ	2
	XonZ	3

	Yx	0
	Yx	1
	Yx	2
	Yx	3

	ret

	;--- Initial pointer setting for functions

FUN_SETP:	ld	ix,PAR_X
	ld	iy,RES_FGHI
	ret


	;-------------------
	;---  DATA AREA  ---
	;-------------------

	;*** Do not modify the buffers order in memory ***

	;--- Data for round execution
	;    Parameter I is omitted, since it is always the one for the
	;    previous operation plus one

R_DATA:
	;* ROUND 1

	defb	0,7
	defb	1,12
	defb	2,17
	defb	3,22
	defb	4,7
	defb	5,12
	defb	6,17
	defb	7,22
	defb	8,7
	defb	9,12
	defb	10,17
	defb	11,22
	defb	12,7
	defb	13,12
	defb	14,17
	defb	15,22

	;* ROUND 2

	defb	1,5
	defb	6,9
	defb	11,14
	defb	0,20
	defb	5,5
	defb	10,9
	defb	15,14
	defb	4,20
	defb	9,5
	defb	14,9
	defb	3,14
	defb	8,20
	defb	13,5
	defb	2,9
	defb	7,14
	defb	12,20

	;* ROUND 3

	defb	5,4
	defb	8,11
	defb	11,16
	defb	14,23
	defb	1,4
	defb	4,11
	defb	7,16
	defb	10,23
	defb	13,4
	defb	0,11
	defb	3,16
	defb	6,23
	defb	9,4
	defb	12,11
	defb	15,16
	defb	2,23

	;* ROUND 4

	defb	0,6
	defb	7,10
	defb	14,15
	defb	5,21
	defb	12,6
	defb	3,10
	defb	10,15
	defb	1,21
	defb	8,6
	defb	15,10
	defb	6,15
	defb	13,21
	defb	4,6
	defb	11,10
	defb	2,15
	defb	9,21

	;--- Result of F/G/H/I functions

RES_FGHI:
	defs	4

	;---- Buffers for A,B,C,D,AA,BB,CC,DD

BUF_A:	defs	4
BUF_B:	defs	4
BUF_C:	defs	4
BUF_D:	defs	4
BUF_AA:	defs	4
BUF_BB:	defs	4
BUF_CC:	defs	4
BUF_DD:	defs	4

	;--- Buffers for parameters X,Y,Z to use on functions F,G,H,I
	;    (must be consecutive in memory)
	;    Since these functions are always called with (X,Y,Z)=(B,C,D),
	;    actually no buffers are defined but B,C,D buffers are directly referred

PAR_X:	equ	BUF_B
PAR_Y:	equ	BUF_C
PAR_Z:	equ	BUF_D

	;--- Initial values for BUF_A/B/C/D

INIT_ABCD:
	defb	1h,23h,45h,67h
	defb	89h,0ABh,0CDh,0EFh
	defb	0FEh,0DCh,0BAh,98h
	defb	76h,54h,32h,10h

	;--- Some variables

MSG_LEN:	defw	0	;Message length in bytes (without padding)
MSG_BLK:	defw	0	;Message length in blocks of 32-bit words
MSG_PNT:	defw	0	;Pointer to the start of next block
PAR_K:		defb	0	;Parameters k,s,i for round steps
PAR_S:		defb	0
PAR_I:		defb	0
ROUND_N:	defb	0	;Current round number (1 to 4)
ROUND_PNT:	defw	0	;Current round data pointer
