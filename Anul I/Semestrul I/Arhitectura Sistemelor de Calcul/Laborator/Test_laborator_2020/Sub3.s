# 1
# v[i] = v + i*4
# i[v] = i*4 + v
.data
	i: .long 2
	v: .long 1, 2, 3, 4, 5
	formatPrintf: .asciz "%ld\n"
.text
.global main
main:
	movl $v, %edi
	movl i, %ecx
	movl (%edi, %ecx, 4), %esi
	
	pushl %esi
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	movl i, %eax
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	movl $v, %edi
	movl (%eax, %edi, 1), %esi
	
	pushl %esi
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80


# 2
# popl %ebx = movl 0(%esp), %ebx
#             addl $4, %esp
# valoarea din esp va fi 0xffffd05c + 0x4 = 4294955100 + 4 = 4294955104 = 0xffffd060

.data
.text
proc:
	call proc
	ret
.global main
main:
	call proc
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	
	
# 3
# Putem citi adresele incarcandu-le cu mov $ sau cu lea
# Nu le putem modifica
# Zona de text este read-only
	
	
# 4
# v: 00 00 00 0a, 00 00 00 14, 00 00 00 1e
#    03 02 01 00  07 06 05 04  11 10 09 08
     
# ebx: 00 14 00 00
#      05 04 03 02


