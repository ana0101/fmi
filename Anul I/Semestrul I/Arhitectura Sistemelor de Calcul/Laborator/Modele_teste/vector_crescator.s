.data
	n: .space 4
	i: .long 0
	x: .space 4
	y: .space 4
	v: .space 400
	formatScanf: .asciz "%ld"
	formatPrintf1: .asciz "vectorul este crescator\n"
	formatPrintf2: .asciz "vectorul nu este crescator: pozitia %ld care contine elementul %ld\n"
	
.text
.global main

main:
	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	
# citim vectorul
loop_citire:
	# verificam daca mai sunt elemente de citit
	movl i, %ecx
	cmp n, %ecx
	jge exit_loop_citire
	
	# punem adresa elemetului ce urmeaza sa fie citit in edi (edi + i*4)
	lea v, %edi
	movl i, %eax
	movl $4, %ebx
	xor %edx, %edx
	imul %ebx
	addl %eax, %edi
	
	# citim urmatorul element
	pushl %edi
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	incl i
	jmp loop_citire
	
	
exit_loop_citire:
	# punem primul element in x
	lea v, %edi
	movl $0, %ecx
	movl (%edi, %ecx, 4), %eax
	movl %eax, x

	movl $1, %eax
	movl %eax, i
	
	
loop_verificare:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge exit_loop_verificare
	
	# punem urmatorul element in y
	lea v, %edi
	movl i, %ecx
	movl (%edi, %ecx, 4), %esi
	movl %esi, y
	
	# il comparam pe x cu y
	movl x, %eax
	movl y, %ebx
	cmp %ebx, %eax
	jg nu_crescator
	
	# il mutam pe y in x
	movl %ebx, x
	
	incl i
	jmp loop_verificare
	
	
nu_crescator:
	# afisam mesajul
	pushl y
	pushl i
	pushl $formatPrintf2
	call printf
	popl %ebx
	popl %ebx
	popl %ebx
	jmp exit
	
exit_loop_verificare:
	# afisam mesajul
	pushl $formatPrintf1
	call printf
	popl %ebx
	jmp exit
	
exit:
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	

