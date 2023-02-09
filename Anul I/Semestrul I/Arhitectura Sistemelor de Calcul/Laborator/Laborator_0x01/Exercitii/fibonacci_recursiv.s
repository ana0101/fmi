.data
	n: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "Al %ld-lea termen din sirul lui Fibonacci este %ld.\n"
	
.text

fibonacci:
	pushl %ebp
	movl %esp, %ebp
	
	pushl %ebx
	pushl %esi
	
	cmp $0, 8(%ebp)
	jne continue1
	xor %eax, %eax
	jmp exit
	
continue1:
	cmp $1, 8(%ebp)
	jne continue2
	movl $1, %eax
	jmp exit
	
continue2:
	# fibonacci(n-1)
	pushl %ebx
	pushl %esi
	
	movl 8(%ebp), %ebx
	decl %ebx
	pushl %ebx
	call fibonacci
	addl $4, %esp
	
	popl %esi
	popl %ebx
	
	# salvam fibonacci(n-1) in esi
	movl %eax, %esi
	
	# fibonacci(n-2)
	pushl %ebx
	pushl %esi
	
	movl 8(%ebp), %ebx
	sub $2, %ebx
	pushl %ebx
	call fibonacci
	addl $4, %esp
	
	popl %esi
	popl %ebx
	
	# punem suma in eax
	addl %esi, %eax
	
exit:
	popl %esi
	popl %ebx
	
	popl %ebp
	ret


.global main

main:
	# citim n
	pushl $n
	pushl $formatScanf
	call scanf
	addl $8, %esp

	# chemam procedura
	pushl n
	call fibonacci
	addl $4, %esp
	
	# afisare
	pushl %eax
	pushl n
	pushl $formatPrintf
	call printf
	addl $12, %esp
	
	# exit
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	
