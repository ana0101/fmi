.data
	s: .space 100
	n: .space 4
	nrVocale: .long 0
	formatScanf: .asciz "%s"
	formatPrintf: .asciz "numarul de vocale este: %d\n"
.text
.global main

main:
	# citirea sirului de caractere
	pushl $s
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx

	# punem lungimea sirului de caractere in n
	pushl $s
	call strlen
	popl %ebx
	movl %eax, n

	movl $0, %ecx
	lea s, %edi

# parcurgem sirul si cautam vocale
loop:
	cmp n, %ecx
	jge afisare

	movb (%edi, %ecx, 1), %bl

	cmp $'a', %bl
	je vocala
	cmp $'e', %bl
	je vocala
	cmp $'i', %bl
	je vocala
	cmp $'o', %bl
	je vocala
	cmp $'u', %bl
	je vocala
 	inc %ecx
	jmp loop

	vocala:
		inc nrVocale
		inc %ecx
		jmp loop
	

afisare:
	pushl nrVocale
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit

exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
