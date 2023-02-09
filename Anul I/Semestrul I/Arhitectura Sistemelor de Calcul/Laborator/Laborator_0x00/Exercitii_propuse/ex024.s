.data
	n: .long 2
	m: .space 4
	text1: .asciz "numarul este prim\n"
	text2: .asciz "numarul nu este prim\n"
.text
.globl main

main:
	mov $0, %eax
	cmp n, %eax
	je nuPrim

	mov $1, %eax
	cmp n, %eax
	je nuPrim

	mov $2, %eax
	cmp n, %eax
	je prim

	mov $2, %ecx

	mov n, %eax
	mov $2, %ebx
	mov $0, %edx
	div %ebx
	add $1, %eax
	mov %eax, m

loop:
	cmp m, %ecx
	je prim

	mov n, %eax
	mov %ecx, %ebx
	mov $0, %edx
	div %ebx

	cmp $0, %edx
	je nuPrim

	add $1, %ecx
	jmp loop

prim:
	mov $0, %edx
	mov $4, %eax
	mov $1, %ebx
	mov $text1, %ecx
	mov $19, %edx
	int $0x80
	jmp exit

nuPrim:
	mov $0, %edx
	mov $4, %eax
	mov $1, %ebx
	mov $text2, %ecx
	mov $22, %edx
	int $0x80
	jmp exit

exit:
	mov $1, %eax
	mov $0, %ebx
	int $0x80
