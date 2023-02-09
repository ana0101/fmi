.data
	n: .space 4
	x: .space 4
	nr: .long 0
	i: .long 0
	suma: .long 0
	d: .long 1
	y: .space 4
	perf: .space 4
	v: .space 400
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "numar elemente perfecte: %ld\n"
	
.text

perfect:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %edi
	pushl %esi
		
	# punem valoarea lui x in eax
	movl 8(%ebp), %eax
		
	# punem valoarea lui x in edi
	movl %eax, %edi
		
	# punem valoarea lui x/2 in ebx
	movl $2, %ecx
	xorl %edx, %edx
	idiv %ecx
	movl %eax, %ebx
		
	movl $1, %ecx    # ecx = potential divizor
	movl $0, %esi    # esi = suma divizorilor
		
loop_perf:
	cmp %ebx, %ecx
	jg verif_perf
	
	# verificam daca ecx divide x
	movl %edi, %eax
	xorl %edx, %edx
	idiv %ecx
	cmp $0, %edx
	je divizor_perf
			
	incl %ecx
	jmp loop_perf
			
divizor_perf:
	addl %ecx, %esi
	incl %ecx
	jmp loop_perf
			
verif_perf:
	cmp %edi, %esi
	je nr_perfect
	jne nr_nu_perfect
			
nr_perfect:
	movl $1, %eax
	jmp exit_perf
		
nr_nu_perfect:
	movl $0, %eax
	jmp exit_perf
			
exit_perf:
	popl %esi
	popl %edi
	popl %ebx
	popl %ebp
	ret
		
		
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
	jmp loop_verificare
	

loop_verificare:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge afisare

	# punem elementul curent in x
	lea v, %edi
	movl (%edi, %ecx, 4), %esi
	movl %esi, x

	# punem pe stiva numarul x si apelam procedura perfect
	pushl x
	call perfect
	popl %ebx
	
	movl %eax, perf
		
	movl perf, %ebx
	cmp $1, %ebx
	je nr_perf
		
	incl i
	jmp loop_verificare
		
nr_perf:
	incl nr
	incl i
	jmp loop_verificare
		
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
		
		
