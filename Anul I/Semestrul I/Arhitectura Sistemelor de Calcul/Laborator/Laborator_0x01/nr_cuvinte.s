.data
	s: .space 100
	n: .space 4
	nrSpatii: .long 0
	formatPrintf: .asciz "numarul de cuvinte este %ld\n"
	
.text
.global main

main:
	# citirea sirului de caractere
	pushl $s
	call gets
	popl %ebx
	
	# punem lungimea sirului de caractere in n
	pushl $s
	call strlen
	popl %ebx
	movl %eax, n
	
	movl $0, %ecx
	lea s, %edi
	
# parcurgem sirul si cautam spatii
loop:
	cmp n, %ecx
	jge afisare

	movb (%edi, %ecx, 1), %bl
	
	cmp $' ', %bl
	je spatiu
	
	incl %ecx
	jmp loop
	
spatiu:
	incl nrSpatii
	incl %ecx
	jmp loop
	
afisare:
	incl nrSpatii
	pushl nrSpatii
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80	
	
	
