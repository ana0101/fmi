.data
	n: .space 4
	k: .space 4
	ok: .asciz "ok"
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	
.text

combinari:
	pushl %ebp
	movl %esp, %ebp
	
	# n = 8(%ebp)
	# k = 12(%ebp)
	
	movl 12(%ebp), %ebx
	cmp %ebx, 8(%ebp)
	je unu
	
	cmp $0, %ebx
	je unu
	
	# combinari(n-1, k)
	movl 8(%ebp), %ebx
	decl %ebx
	
	pushl %edi
	
	pushl 12(%ebp)
	pushl %ebx
	call combinari
	addl $8, %esp
	
	popl %edi
	
	# punem rezultatul in edi
	movl %eax, %edi
	
	#pushl %edi
	#pushl $formatPrintf
	#call printf
	#addl $4, %esp
	
	# combinari(n-1, k-1)
	movl 8(%ebp), %ebx
	decl %ebx
	movl 12(%ebp), %esi
	decl %esi
	
	pushl %edi
	
	pushl %esi
	pushl %ebx
	call combinari
	addl $8, %esp
	
	popl %edi
	
	# punem suma in eax
	addl %edi, %eax
	
exit:
	popl %ebp
	ret
	
unu:
	movl $1, %eax
	jmp exit


.global main

main:
	# citim n
	pushl $n
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# citim k
	pushl $k
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# salvam registrii
	pushl %edi
	
	# chemam procedura
	pushl k
	pushl n
	call combinari
	addl $8, %esp
	
	# restauram registrii
	popl %edi
	
	# afisam
	pushl %eax
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	# exit
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
