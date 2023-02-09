.data
	n1: .long 5
	n2: .long 6
	k: .long 3
	fs: .asciz "%ld\n"
	
.text

rest:
	pushl %ebp
	mov %esp, %ebp
	push %ebx
	
	mov 8(%ebp), %eax
	mov 12(%ebp), %ebx
	mov $0, %edx
	div %ebx
	# eax = cat, %edx = rest
	mov %edx, %eax
	
	pop %ebx
	pop %ebp
	ret

proc:
	pushl %ebp
	mov %esp, %ebp
	
	subl $4, %esp
	
	mov 8(%ebp), %eax
	add 12(%ebp), %eax
	
	# push %eax
	mov %eax, -4(%ebp)
	
	pushl 16(%ebp)
	pushl -4(%ebp)
	call rest
	addl $8, %esp
	# rest intoarce rezultatul in eax
	
	addl $4, %esp
	
	popl %ebp
	ret
	
	
# pop %eax = mov 0(%esp), %eax
#            addl $4, %esp


.global main

main:
	pushl k
	pushl n2
	pushl n1
	call proc
	addl $12, %esp
	
	push %eax
	pushl $fs
	call printf
	addl $8, %esp
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
