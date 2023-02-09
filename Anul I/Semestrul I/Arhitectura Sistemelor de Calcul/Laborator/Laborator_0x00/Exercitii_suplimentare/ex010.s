.data
.text
.global main

main:
	movl $0x090E, %eax
	
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
