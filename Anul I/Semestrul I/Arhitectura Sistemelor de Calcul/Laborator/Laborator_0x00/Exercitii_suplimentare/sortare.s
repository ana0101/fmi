.data
	n: .space 4
	i: .long 0
	j: .long 0
	x: .space 4
	y: .space 4
	v: .space 400
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
.text
.global main

main:
	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
# citim vectorul
loop_citire:
	# verificam daca mai sunt elemente de citit
	movl i, %ecx
	cmp n, %ecx
	je exit_loop_citire
	
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
	addl $8, %esp
	
	incl i
	jmp loop_citire
	
exit_loop_citire:
	xor %eax, %eax
	movl %eax, i
	
loop_sort1:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	je exit_loop_sort1
	
	lea v, %edi
	
	# punem elementul de pe pozitia i in x
	movl (%edi, %ecx, 4), %eax
	movl %eax, x
	
	# initializam j
	movl i, %eax
	movl %eax, j
	incl j
	
	jmp loop_sort2
	
exit_loop_sort1:
	xor %eax, %eax
	movl %eax, i
	jmp loop_afisare
	
loop_sort2:
	# verificam daca mai sunt elemente de parcurs
	movl j, %ecx
	cmp n, %ecx
	je exit_loop_sort2
	
	lea v, %edi

	# punem elementul de pe pozitia j in y
	movl j, %ecx
	movl (%edi, %ecx, 4), %eax
	movl %eax, y
	
	# comparam cele doua elemente
	movl x, %eax
	movl y, %ebx
	cmp %ebx, %eax
	jg schimb
	
	incl j
	jmp loop_sort2
	
exit_loop_sort2:
	incl i
	jmp loop_sort1
	
schimb:
	# interchimbam cele doua elemente
	lea v, %edi
	movl i, %ecx
	movl %ebx, (%edi, %ecx, 4)
	movl j, %ecx
	movl %eax, (%edi, %ecx, 4)
	
	incl j
	jmp loop_sort2
	
loop_afisare:
	# verificam daca mai sunt elemente de afisat
	movl i, %ecx
	cmp n, %ecx
	je exit
	
	lea v, %edi
	# punem elementul ce urmeaza sa fie afisat in esi
	movl (%edi, %ecx, 4), %esi
	
	# afisam elementul
	pushl %esi
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	incl i
	jmp loop_afisare	
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
