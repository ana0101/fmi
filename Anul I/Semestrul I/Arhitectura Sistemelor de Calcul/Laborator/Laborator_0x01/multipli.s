.data
	x: .space 4
	n: .space 4
	nr: .space 4
	k: .long 0
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "multiplu de %ld: %ld\n"
	
.text
.global main

main:
	# il citim pe x
	pushl $x
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	
	# citim numerele si verificam daca sunt multipli de x
	loop:
		# verificam daca mai sunt numere de citit
		movl k, %ecx
		cmp n, %ecx
		jge exit
		
		# citim un numar
		pushl $nr
		pushl $formatScanf
		call scanf
		popl %ebx
		popl %ebx
		
		# verificam daca este multiplu de x
		xor %edx, %edx
		movl nr, %eax
		movl x, %ebx
		idiv %ebx
		cmp $0, %edx
		je multiplu
		
		inc k
		jmp loop
		
		# daca este multiplu de x, il afisam
		multiplu:
			pushl nr
			pushl x
			pushl $formatPrintf
			call printf
			popl %ebx
			popl %ebx
			popl %ebx
			
			inc k
			jmp loop
		
	exit:
		mov $1, %eax
		xor %ebx, %ebx
		int $0x80
		
		
