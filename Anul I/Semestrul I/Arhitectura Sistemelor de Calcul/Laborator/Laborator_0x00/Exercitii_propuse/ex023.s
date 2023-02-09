.data
	a: .long 30
	b: .long 20
	c: .long 10
	min: .space 2
.text
.globl main

main:
	mov a, %eax
	mov b, %ebx
	cmp %ebx, %eax
	jle et1
	jg et2

et1:
	mov a, %eax
	mov c, %ebx
	cmp %ebx, %eax
	jle et3
	jg et4

et2:
	mov b, %eax
	mov c, %ebx
	cmp %ebx, %eax
	jle et5
	jg et4

et3:
	mov a, %eax
	mov %eax, min
	jmp exit

et4:
	mov c, %eax
	mov %eax, min
	jmp exit

et5:
	mov b, %eax
	mov %eax, min
	jmp exit

exit:
	mov $1, %eax
	mov $0, %ebx
	int $0x80




