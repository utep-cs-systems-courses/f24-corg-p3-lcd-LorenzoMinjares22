	.arch msp430g2553

	.p2align 1,0

	.text



	.global redControl

	.extern P1OUT



redControl:

	cmp #0, r12		;if on

	jz itsOff

	and #~64, &P1OUT

	mov #0, r12

	pop r0

itsOff:

	bis #64, &P1OUT

	mov #1, r12

	pop r0



	ret
