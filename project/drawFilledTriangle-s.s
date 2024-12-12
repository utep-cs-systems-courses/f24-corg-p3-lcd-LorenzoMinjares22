	.arch msp430g2553

	.p2align 1,0



	.text





	.global drawFilledTriangle

	.extern drawPixel

drawFilledTriangle:

	sub #7, r1

	mov #0, 0(r1)

	jmp OutLoop



OutLoop:

	cmp 0(r1), r15

	jnc end 		;end

	jmp InLoop



InLoop:

	mov r12, 5(r1)

	sub 0(r1), 5(r1)

	mov 5(r1), 2(r1)

	mov r12, 6(r1)

	add 0(r1), 6(r1)

	cmp 6(r1), 2(r1)

	jc interm

;;;

	mov r13, 7(r1)

	add 0(r1), 7(r1)

	mov 2(r1), r12

	mov 7(r1), r13

	call #drawPixel

	add #1, 2(r1)

	jmp InLoop



interm:

	add #1, 0(r1)

	jmp OutLoop



end:

	add #7, r1

	pop r0

	
