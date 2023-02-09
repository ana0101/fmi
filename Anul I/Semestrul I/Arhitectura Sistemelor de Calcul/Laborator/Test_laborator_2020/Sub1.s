.data
	x: .space 4
	y: .space 4
	i: .space 4
	n: .long 6
	v: .long 1, 2, 3, 4, 5, 6
	formatPrintf1: .asciz "numar: %ld\n"
	formatPrintf2: .asciz "divizor: %ld\n"
	
.text

customEven:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	
	# x = 8(%ebp)
	# y = 12(%ebp)
	
	# eax = x*y
	movl 8(%ebp), %eax
	movl 12(%ebp), %ebx
	xorl %edx, %edx
	imul %ebx
	
	subl $4, %esp
	movl $0, -4(%ebp)
	
forCustomEven:
	cmp $0, %eax
	je exitForCustomEven
	
	movl $10, %ebx
	xorl %edx, %edx
	idiv %ebx
	
	addl %edx, -4(%ebp)
	
	jmp forCustomEven
	
exitForCustomEven:
	movl -4(%ebp), %eax
	movl $2, %ebx
	xorl %edx, %edx
	idiv %ebx
	
	cmp $0, %edx
	je para
	
	cmp $1, %edx
	je impara
	
para:
	movl $1, %eax
	jmp exitCustomEven
	
impara:
	xorl %eax, %eax
	jmp exitCustomEven
	
exitCustomEven:
	addl $4, %esp
	popl %ebx
	popl %ebp
	ret
	
	
divisors:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	
	movl $1, %ebx
	
forDivisors:
	cmp 8(%ebp), %ebx
	jg exitDivisors
	
	movl 8(%ebp), %eax
	xorl %edx, %edx
	idiv %ebx
	
	cmp $0, %edx
	je afisare
	
	incl %ebx
	jmp forDivisors
	
afisare:
	pushl %ebx
	pushl $formatPrintf2
	call printf
	addl $8, %esp
	
	incl %ebx
	jmp forDivisors
	
exitDivisors:
	popl %ebx
	popl %ebp
	ret


.global main

main:
	xorl %eax, %eax
	movl %eax, i
	
forMain:
	movl i, %ecx
	cmp n, %ecx
	jge exitMain
	
	# punem v[i] in x
	lea v, %edi
	movl (%edi, %ecx, 4), %eax
	movl %eax, x
	
	# verificam i+1
	incl %ecx
	cmp n, %ecx
	je ultimul
	
	# punem v[i+1] in y
	lea v, %edi
	movl (%edi, %ecx, 4), %eax
	movl %eax, y
	
continue1:
	# chemam customEven
	pushl y
	pushl x
	call customEven
	addl $8, %esp
	
	# verificam rezultatul
	cmp $1, %eax
	je unu
	
continue2:
	incl i
	jmp forMain
	
ultimul:
	# punem v[0] in y
	lea v, %edi
	xorl %ecx, %ecx
	movl (%edi, %ecx, 4), %eax
	movl %eax, y
	jmp continue1
	
unu:
	pushl x
	pushl $formatPrintf1
	call printf
	addl $8, %esp
	
	pushl x
	call divisors
	addl $4, %esp
	jmp continue2
	
exitMain:
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
		
