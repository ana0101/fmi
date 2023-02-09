.data
	min1: .space 4
	min2: .space 4
	x: .space 4
	n: .space 4
	k: .long 0
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "cele doua minime sunt %ld si %ld\n"
	
.text

.global main

main:
	# citim numarul de elemente in n
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	# citim primul numar
	pushl $x
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	# punem primul numar in min1
	movl x, %eax
	movl %eax, min1
	
	inc k
	
	# citim al doilea numar
	pushl $x
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	# il comparam cu min1
	movl x, %eax
	movl min1, %ebx
	cmp %ebx, %eax
	jl schimb
	movl x, %eax
	movl %eax, min2
	
	schimb:
		movl min1, %eax
		movl %eax, min2
		movl x, %eax
		movl %eax, min1
		
	inc k
		
	loop:
		# verificam daca mai avem numere de citit
		movl n, %eax
		cmp %eax, k
		jge afisare
		
		# citim urmatorul numar
		pushl $x
		pushl $formatScanf
		call scanf
		popl %ebx
		popl %ebx
		
		# il comparam cu min1
		movl x, %eax
		cmp min1, %eax
		jle minim1
		
		# il comparam cu min2
		cmp min2, %eax
		jle minim2	
		
		inc k
		jmp loop
		
	minim1:
		# mutam min1 in min2
		movl min1, %eax
		movl %eax, min2
		
		# mutam x in min1
		movl x, %eax
		movl %eax, min1
		
		inc k
		jmp loop
		
	minim2:
		# mutam x in min2
		movl x, %eax
		movl %eax, min2
		
		inc k
		jmp loop
		
	afisare:
		pushl min2
		pushl min1
		pushl $formatPrintf
		call printf
		popl %ebx
		popl %ebx
		popl %ebx
		jmp exit
		
	exit:
		mov $1, %eax
		xor %ebx, %ebx
		int $0x80
			
	
	
	
	
