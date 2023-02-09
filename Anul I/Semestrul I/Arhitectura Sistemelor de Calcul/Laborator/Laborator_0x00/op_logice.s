.data
	x: .long 1
	y: .long 0
	rezNot: .space 4
	rezAnd: .space 4
	rezOr: .space 4
	rezXor: .space 4
.text
.globl main
main:
	mov x, %eax
	not %eax
	mov %eax, rezNot

	mov x, %eax
	mov y, %ebx
	and %eax, %ebx
	mov %ebx, rezAnd

	mov x, %eax
	mov y, %ebx
	or %eax, %ebx
	mov %ebx, rezOr

	mov x, %eax
	mov y, %ebx
	xor %eax, %ebx
	mov %ebx, rezXor

	mov $1, %eax
	mov $0, %ebx
	int $0x80
