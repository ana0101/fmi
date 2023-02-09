.data
	n: .space 4
	m: .space 4
	d: .long 1
	rest: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
.text
.global main

main:
	# citirea numarului
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx

	# punem in m valoarea lui n/2
	mov n, %eax
	mov $2, %ebx
	xor %edx, %edx
	idiv %ebx
	mov %eax, m

	loop:
		mov m, %eax
		cmp d, %eax
		jl print_numar
		
		mov n, %eax
		mov d, %ebx
		xor %edx, %edx
		idiv %ebx

		cmp $0, %edx
		je divizor

		inc d
		jmp loop
	
	# daca am gasit un divizor, il afisam pe ecran
	divizor:
                pushl d
                pushl $formatPrintf
                call printf
                popl %ebx
                popl %ebx
		inc d
		jmp loop

	print_numar:
		# afisam si numarul insusi pe ecran
		pushl n
		pushl $formatPrintf
		call printf
		popl %ebx
		popl %ebx
		jmp exit


exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
