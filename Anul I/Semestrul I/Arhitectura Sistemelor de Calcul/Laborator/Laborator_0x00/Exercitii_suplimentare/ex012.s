.data
	n: .long 4
	v: .long 1, 2, 3, 4
	suma: .long 0
	cat: .long 0
	rest: .long 0
	formatPrintf: .asciz "suma elementelor este %ld, catul mediei este %ld si restul mediei este %ld\n"
	
.text

.global main

main:
	movl $0, %ecx
	lea v, %edi
	
loop:
	# verificam daca mai sunt numere
	cmp n, %ecx
	jge medie
	
	# adugam numarul la suma
	movl (%edi, %ecx, 4), %esi
	add %esi, suma
	
	inc %ecx
	jmp loop
	
medie:
	movl suma, %eax
	movl n, %ebx
	xor %edx, %edx
	idiv %ebx
	movl %eax, cat
	movl %edx, rest
	jmp afisare
	
afisare:
	pushl rest
	pushl cat
	pushl suma
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
