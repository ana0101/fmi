.data
	x: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	
.text

f:
	pushl %ebp
	movl %esp, %ebp
	
	# chemam g
	pushl 8(%ebp)
	call g
	addl $4, %esp
	
	# rezultatul e in eax
	# il inmultim cu 2
	movl $2, %ebx
	imul %ebx
	
	popl %ebp
	ret
	
g:
	pushl %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %eax
	incl %eax
	
	popl %ebp
	ret


.global main

main:
	# citim x
	pushl $x
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# chemam f
	pushl x
	call f
	addl $4, %esp
	
	# afisam
	pushl %eax
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	# exit
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	
