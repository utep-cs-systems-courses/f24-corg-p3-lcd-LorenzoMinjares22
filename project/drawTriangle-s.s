	.arch msp430g2553

	.p2align 1,0



	.text



	.global drawTriangle

	.extern drawPixel

drawTriangle:

	sub #8, r1		;int i

	mov #0, 0(r1)		;init i

	mov r12, r6		;acol

	mov r13, r7		;arow

	mov r14, r8		;size

	mov r15, r9		;color



	mov r8, 2(r1)		;temp1

	add r7, 2(r1)		;size+arow



	mov r8, 4(r1)		;temp2

	add r6, 4(r1)		;size+acol



	mov r7, 6(r1)

	sub r8, 6(r1)		;arow-size



	jmp cond1



cond1:

	mov 6(r1), 0(r1)	;i=arow-size

	jmp loop1

loop1:

	cmp 2(r1), 0(r1)

	jge cond2

;;;  move parameters to drawPixel

	mov 0(r1), r12

	mov 0(r1), r13

	mov r9, r14

	call #drawPixel

	add #1, 0(r1)

	jmp loop1



cond2:

	mov 2(r1), 0(r1)

	jmp loop2

loop2:

	cmp 0(r1), 6(r1)

	jz cond3

	mov 0(r1), r12

	mov 2(r1), r13

	mov r9, r14

	call #drawPixel

	sub #1, 0(r1)

	jmp loop2



cond3:

	mov 6(r1), 0(r1)

	jmp loop3



loop3:

	cmp 2(r1), 0(r1)

	jge end

	mov r6, r12

	mov 0(r1), r13

	mov r9, r14

	call #drawPixel

	add #1, 0(r1)

	jmp loop3

end:

	add #8, r1

	pop r0
