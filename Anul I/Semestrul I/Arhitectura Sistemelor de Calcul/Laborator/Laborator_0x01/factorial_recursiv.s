.data
	n: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	
.text

factorial:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %edi
	
	cmp $0, 8(%ebp)
	je zero
	
	movl 8(%ebp), %edi
	decl %edi
	
	pushl %edi
	call factorial
	addl $4, %esp
	
	movl 8(%ebp), %ebx
	imul %ebx, %eax
	
continue:
	popl %edi
	popl %ebx
	popl %ebp
	ret
	
zero:
	movl $1, %eax
	jmp continue


.global main

main:
	# citim n
	pushl $n
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# chemam procedura
	pushl n
	call factorial
	addl $4, %esp
	
	pushl %eax
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	
