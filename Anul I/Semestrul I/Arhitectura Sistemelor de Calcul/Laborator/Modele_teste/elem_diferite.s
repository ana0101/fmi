.data
	n: .space 4
	x: .space 4
	y: .space 4
	i: .long 0
	j: .long 0
	v: .space 400
	formatScanf: .asciz "%ld"
	formatPrintf1: .asciz "elementele sunt diferite doua cate doua\n"
	formatPrintf2: .asciz "elementele nu sunt diferite doua cate doua\n"
	
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
	
	# punem adresa elementului ce urmeaza sa fie citit in edi (edi + 4*i)
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
	xor %eax, %eax
	movl %eax, i
	jmp loop_verificare_1
	
	
loop_verificare_1:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge afisare1
	
	# punem elementul curent in x
	lea v, %edi
	movl (%edi, %ecx, 4), %esi
	movl %esi, x
	
	# il initializam pe j
	movl %ecx, j
	incl j
	
	jmp loop_verificare_2
	
loop_verificare_2:
	# verificam daca mai sunt elemente de parcurs
	movl j, %ecx
	cmp n, %ecx
	jge exit_loop_verificare_2
	
	# punem elementul curent in y
	lea v, %edi
	movl (%edi, %ecx, 4), %esi
	movl %esi, y
	
	# verificam daca este diferit de x
	movl x, %eax
	movl y, %ebx
	cmp %eax, %ebx
	je afisare2
	
	incl j
	jmp loop_verificare_2
	
exit_loop_verificare_2:
	incl i
	jmp loop_verificare_1
	
afisare1:
	pushl $formatPrintf1
	call printf
	popl %ebx
	jmp exit
	
afisare2:
	pushl $formatPrintf2
	call printf
	popl %ebx
	jmp exit
	
exit:
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	
	
