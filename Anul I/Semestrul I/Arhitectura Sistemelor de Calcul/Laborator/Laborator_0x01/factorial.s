.data
	x: .space 4
	fact: .long 1
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "factorialul este: %ld\n"

.text
.global main

main:
	# citim numarul x
	pushl $x
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx

	movl $1, %ecx
	
	# calculam factorialul
	loop:
		cmp x, %ecx
		jg afisare
		
		movl fact, %ebx
		movl %ecx, %eax
		imul %ebx
		movl %eax, fact
		
		inc %ecx
		jmp loop
		
	afisare:
		pushl fact
		pushl $formatPrintf
		call printf
		popl %ebx
		popl %ebx
		jmp exit
		
	exit:
		mov $1, %eax
		xor %ebx, %ebx
		int $0x80
