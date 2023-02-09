.data
	x: .space 4
	k: .long 0
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	
.text

f:
	pushl %ebp
	movl %esp, %ebp
	
	# salvam registrii callee-saved
	pushl %ebx
	
	cmp $1, 8(%ebp)
	je f_stop
	
	# impartim x la 2
	movl 8(%ebp), %eax
	movl $2, %ebx
	xorl %edx, %edx
	idiv %ebx
	
	# verificam restul
	cmp $0, %edx
	je f_par
	
	cmp $1, %edx
	je f_impar
	
f_par:
	incl k
	pushl %ebx
	
	pushl %eax
	call f
	addl $4, %esp
	
	popl %ebx
	jmp f_stop
	
f_impar:
	incl k
	movl 8(%ebp), %eax
	movl $3, %ebx
	imul %ebx
	incl %eax
	
	pushl %ebx
	
	pushl %eax
	call f
	addl $4, %esp
	
	popl %ebx
	jmp f_stop
	
f_stop:
	# restauram registrii callee-saved
	popl %ebx
	
	popl %ebp
	ret


.global main

main:
	# citim x
	pushl $x
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# chemam procedura
	pushl x
	call f
	addl $4, %esp
	
	# afisare
	pushl k
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	# exit
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
	
