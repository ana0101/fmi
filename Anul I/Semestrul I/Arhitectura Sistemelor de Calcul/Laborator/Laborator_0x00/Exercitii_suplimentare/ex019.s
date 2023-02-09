.data
	n: .space 4
	x: .long 0
	y: .long 0
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "radicalul intreg este %ld\n"
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
	
	# verfificam daca n este pozitiv
	movl n, %eax
	cmp $0, %eax
	jl invalid
	
loop:
	# verificam daca y^2 este mai mic decat n
	movl y, %eax
	movl y, %ebx
	imul %ebx
	movl n, %ebx
	cmp %ebx, %eax
	jg afisare
	
	# il punem pe y in x
	movl y, %eax
	movl %eax, x
	
	# il marim pe y
	inc y
	
	jmp loop
	
invalid:
	pushl $formatPrintf1
	call printf
	popl %ebx
	jmp exit
	
afisare:
	pushl x
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
	
