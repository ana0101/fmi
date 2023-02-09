.data
	n: .space 4
	x: .long 0
	y: .long 1
	nr: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	formatPrintf1: .asciz "numarul dat nu este valid\n"
	
.text
.global main

main:
	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	# verificam daca n este intreg si pozitiv
	movl n, %eax
	cmp $0, %eax
	jle invalid
	
	# verificam daca n este 1 sau 2
	movl n, %eax
	cmp $1, %eax
	je unu
	
	movl n, %eax
	cmp $2, %eax
	je doi
	
	movl $2, %ecx
	jmp loop
	
invalid:
	pushl $formatPrintf1
	call printf
	popl %ebx
	jmp exit
	
unu:
	movl x, %eax
	movl %eax, nr
	jmp afisare
	
doi:
	movl y, %eax
	movl %eax, nr
	jmp afisare
	
loop:
	cmp n, %ecx
	je afisare
	
	movl x, %eax
	movl y, %ebx
	movl %ebx, x
	add %eax, y
	
	movl y, %eax
	movl %eax, nr
	
	inc %ecx
	jmp loop
	
afisare:
	pushl nr
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
	
	
