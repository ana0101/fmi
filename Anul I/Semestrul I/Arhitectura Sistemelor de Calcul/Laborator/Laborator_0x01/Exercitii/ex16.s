.data
	x: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld "
	
.text

proc:
	pushl %ebp
	movl %esp, %ebp
	
	cmp $0, 8(%ebp)
	je exit
	
	# afisam
	pushl 8(%ebp)
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	pushl $0
	call fflush
	addl $4, %esp
	
	# chemam proc
	movl 8(%ebp), %ebx
	decl %ebx
	pushl %ebx
	call proc
	addl $4, %esp
	
exit:
	popl %ebp
	ret	
	

.global main

main:
	# citim x
	pushl $x
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	pushl %ebx
	
	# chemam proc
	pushl x
	call proc
	addl $4, %esp
	
	popl %ebx
	
	# exit
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	
