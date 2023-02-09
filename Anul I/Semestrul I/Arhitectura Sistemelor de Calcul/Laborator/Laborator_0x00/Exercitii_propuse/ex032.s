.data
	s: .asciz "Hello\n"
	n: .long 7
	t: .space 7
.text
.globl main

main:
	lea t, %edi
	lea s, %esi
	mov n, %ecx
	sub $2, %ecx

	loop:
		mov n, %eax
		sub $2, %eax
		sub %ecx, %eax
		mov %ecx, %ebx
		dec %ebx

		mov (%esi, %ebx, 1), %edx 
		mov %edx, (%edi, %eax, 1)
		loop loop

	terminatorul_de_sir:
		mov n, %ecx
		sub $2, %ecx
		mov (%esi, %ecx, 1), %edx
		mov %edx, (%edi, %ecx, 1)
		inc %ecx
		mov (%esi, %ecx, 1), %edx
                mov %edx, (%edi, %ecx, 1)

	afis:
		mov $4, %eax
		mov $1, %ebx
		mov $t, %ecx
		mov $7, %edx
		int $0x80

	exit:
		mov $1, %eax
		xor %ebx, %ebx
		int $0x80
