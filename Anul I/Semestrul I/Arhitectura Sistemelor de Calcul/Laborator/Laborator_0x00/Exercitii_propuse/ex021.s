.data
	x: .long 32
	y: .long 3
	r1: .space 4
	r2: .space 4
	aux1: .space 4
	aux2: .space 4
.text
.globl main

main:
	mov x, %eax
	mov $16, %ebx
	mov $0, %edx
	div %ebx
	mov %eax, aux1

	mov y, %eax
	mov $16, %ebx
	mul %ebx
	mov %eax, aux2

	mov aux1, %eax
	add aux2, %eax
	mov %eax, r1


	


	mov $1, %eax
	mov $0, %ebx
	int $0x80
