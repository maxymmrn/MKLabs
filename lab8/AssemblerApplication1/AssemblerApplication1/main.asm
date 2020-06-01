.include "m2560def.inc"
 
ldi r21, 0x01    ; register for comparing

ldi r17, 0x00    ; register for timing
ldi r18, 0x00    ; register for timing 2

ldi r26, 0x00    ; register for reading buttons

ldi r23, 0xFF 
out DDRF, r23    ; config port F

out DDRA, r23    ; config port A

out DDRD, r28    ; config port D





reset:
	clt
	ldi r19, 0x00
	ldi r22, 0x00
	ldi r20, 0x00
	ldi r26, 0x00

	ldi r24, 0x00   ; set 0 to register for algo1
	out PORTF, r24  ; set LOW to all diods in port F

	ldi r29, 0x00 ; set 0 to register for algo1
	out PORTA, r29 ; set LOW to all diods in port A


start:
	sbis PINC, 0
		rjmp algo1_setup
	nop
	sbis PINC, 7
		rjmp algo2_setup1
	nop
	rjmp start



;-----------------------------------ALGO 1----------------------------------------------------------------
algo1_setup:
	ldi r24, 0x01
	out PORTF, r24
	rjmp algo1_inc1

algo1_loop:
	brts reset
	lsl r24
	out PORTF, r24
	brvs is_end1
	rjmp algo1_inc1

is_end1:
	set
	rjmp algo1_inc1

algo1_inc2:
	inc r18
	brvs algo1_loop

algo1_inc1:
	nop
	nop
	nop
	nop
	inc r17
	brvs algo1_inc2
	rjmp algo1_inc1




;-----------------------------------ALGO 2----------------------------------------------------------------
algo2_setup1:
	ldi r29, 0x01
	out PORTA, r29
	rjmp algo2_inc1

algo2_setup2:
	ldi r20, 0x00
	ldi r19, 0x01
	ldi r29, 0x02
	out PORTA, r29
	rjmp algo2_inc1

algo2_loop:
	cp r22, r21
	breq reset
	cp r20, r21
	breq algo2_setup2
	lsl r29
	lsl r29
	out PORTA, r29
	brvs is_half2
	rjmp algo2_inc1

is_half2:
	cp r19, r21
	breq is_end2
	ldi r20, 0x01
	rjmp algo2_inc1

is_end2:
	ldi r22, 0x01
	rjmp algo2_inc1
	

algo2_inc2:
	inc r18
	brvs algo2_loop

algo2_inc1:
	nop
	nop
	nop
	nop
	inc r17
	brvs algo2_inc2
	rjmp algo2_inc1
