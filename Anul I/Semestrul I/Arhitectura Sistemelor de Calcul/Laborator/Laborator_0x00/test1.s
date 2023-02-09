.data
x: .long 0x04030201
ty: .long 0x08070605

.text
.global main
main:

mov x, %eax
mov y, %al

mov $1, %eax
mov $0, %ebx
int $0x80
