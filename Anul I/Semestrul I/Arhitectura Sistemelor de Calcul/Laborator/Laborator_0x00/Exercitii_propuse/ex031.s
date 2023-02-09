.data
	v: .long 20, 30, 50, 40, 50
	n: .long 5
	max: .space 4
	nr: .space 4
.text
.globl main

main:
	lea v, %edi
	mov n, %ecx

	loop:
		mov n, %eax
		sub %ecx, %eax
		movl (%edi, %eax, 4), %edx
		cmp max, %edx
		jg maxim_nou
		je maxim_repetat
		loop loop

		maxim_nou:
			mov %edx, max
			mov $1, %esi
			mov %esi, nr
			loop loop

		maxim_repetat:
			mov $1, %esi
			add %esi, nr
			loop loop

	exit:
		mov $1, %eax
		xor %ebx, %ebx
		int $0x80
