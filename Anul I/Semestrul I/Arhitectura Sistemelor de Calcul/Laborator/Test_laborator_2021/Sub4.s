.data
	x: .long 3
	lindex: .long L0, L1, L2, L3
	n: .long 7
	v: .long 15, 3, 2, 10, 1, 20, 0
	formatPrintf: .asciz "%d\n"
	
.text

.global main

f:
	pushl %ebp
	movl %esp, %ebp
	
	# salvam registrii callee-saved
	pushl %edi
	
	movl $0, %eax
	movl 8(%ebp), %ecx
	cmp $4, %ecx
	jge final
	
	cmp $-1, %ecx
	jle final  # jle in loc de jae
	
	movl $lindex, %edi
	movl (%edi, %ecx, 4), %eax
	
	jmp *%eax
	
L0:
	movl $1, %eax
	jmp final
	
L1:
	movl $2, %eax
	jmp final
	
L2:
	movl $3, %eax
	jmp final
	
L3:
	movl $4, %eax
	jmp final
	
final:
	# restauram registrii callee-saved
	popl %edi
	
	popl %ebp
	ret

	
main:
	movl $v, %edi
	movl $0, %ecx
	
for_main:
	cmp n, %ecx
	jge final_main
	
	movl 0(%edi), %eax
	
	# salvam ecx
	pushl %ecx
	
	pushl %eax
	call f
	popl %ebx
	
	# restauram ecx
	popl %ecx
	
	pushl %ecx
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	popl %ecx
	
	incl %ecx
	# crestem cu 4 in loc de 1 pe edi
	addl $4, %edi
	
	jmp for_main
	
final_main:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	
	
