.data
	n: .long 5
	m: .long 100
	formatPrintf: .asciz "%d "
	
.text

.global main

f:
	pushl %ebp
	movl %esp, %ebp
	
	#2 trebuie salvati registrii callee-saved
	pushl %ebx
	
	#1 e inversata ordinea la instructiunile movl
	movl 8(%ebp), %ecx
	movl 12(%ebp), %eax
	
	#1 edx trebuie sa fie 0 inainte de impartire
	xorl %edx, %edx
	
	divl %ecx
	pushl %eax
	
f_for:
	#1 salvam ecx
	pushl %ecx
	
	pushl %ecx
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	pushl $0
	call fflush
	popl %ebx
	
	#1 restauram ecx
	popl %ecx
	loop f_for

f_exit:
	popl %eax
	
	#2 trebuie restaurati registrii callee-saved
	popl %ebx
	
	popl %ebp
	ret
	
	
main:
	movl n, %edx
	decl %edx
	
	pushl m
	pushl %edx
	call f
	popl %ebx
	popl %ebx
	
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	pushl $0
	call fflush
	popl %ebx
	
et_exit:
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	

# 3: se va afisa 4 3 2 1 25

# 4: fflush este necesar pentru ca altfel nu se va afisa nimic (formatPrintf nu are \n la final)
# pushl %eax este necesar in cadrul procedurii f ca sa nu iasa modificat dupa printf

	
	
