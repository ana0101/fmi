.data
	n: .space 4
	k: .long 0
	i: .long 0
	suma: .long 0
	medie: .long 0
	v: .space 400
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld elemente sunt egale cu media aritmetica si media este %ld\n"
	
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
	
	# punem adresa elementului ce urmeaza sa fie citit in edi (edi + i*4)
	lea v, %edi
	movl i, %eax
	movl $4, %ebx
	xor %edx, %edx
	imul %ebx
	addl %eax, %edi
	
	# citim elementul
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
	jmp loop_suma
	
	
loop_suma:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge exit_loop_suma
	
	# adaugam elementul in suma
	lea v, %edi
	movl (%edi, %ecx, 4), %esi
	addl %esi, suma
	
	incl i
	jmp loop_suma
	
exit_loop_suma:
	xor %eax, %eax
	movl %eax, i
	jmp calcul_medie
	
	
calcul_medie:
	movl suma, %eax
	movl n, %ebx
	xor %edx, %edx
	idiv %ebx
	movl %eax, medie
	jmp loop_verificare
	
	
loop_verificare:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge afisare
	
	# verificam daca elementul este egal cu media
	lea v, %edi
	movl (%edi, %ecx, 4), %esi
	cmp medie, %esi
	je egal_medie
	
	incl i
	jmp loop_verificare
	
egal_medie:
	incl k
	incl i
	jmp loop_verificare
	

afisare:
	pushl medie
	pushl k
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	movl $1, %eax
	xor %ebx, %ebx
	int $0x80
	

