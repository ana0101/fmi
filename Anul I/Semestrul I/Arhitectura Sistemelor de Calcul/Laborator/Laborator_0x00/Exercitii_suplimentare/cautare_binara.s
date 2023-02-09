.data
	elem: .long 5
	n: .long 8
	v: .long 1, 2, 3, 4, 5, 6, 7, 8
	st: .space 4
	dr: .space 4
	mij: .space 4
	poz: .long -1
	formatPrintf: .asciz "pozitia este %ld\n"
	
.text

.global main

main:
	# initializam stanga si dreapta
	movl $0, st
	movl n, %eax
	movl %eax, dr
	dec dr
	
	# punem adresa lui v in edi
	lea v, %edi
	
loop:
	# verificam daca stanga e mai mare decat dreapta
	movl st, %eax
	movl dr, %ebx
	cmp %ebx, %eax
	jg afisare
	
	# calculam pozitia de mijloc - (st+dr)/2
	movl st, %eax
	add dr, %eax
	movl $2, %ebx
	xor %edx, %edx
	idiv %ebx
	movl %eax, mij
	
	# comparam elementul de pe pozitia de mijloc cu cel care trebuie gasit
	movl elem, %eax
	movl mij, %ecx
	movl (%edi, %ecx, 4), %ebx
	cmp %eax, %ebx
	je elem_gasit
	jg stanga
	jl dreapta
	
elem_gasit:
	# punem pozitia
	movl mij, %eax
	movl %eax, poz
	jmp afisare
	
stanga:
	# ducem cautarea in stanga
	movl mij, %eax
	movl %eax, dr
	dec dr
	jmp loop
	
dreapta:
	# ducem cautarea in dreapta
	movl mij, %eax
	movl %eax, st
	inc st
	jmp loop
	
afisare:
	pushl poz
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	

