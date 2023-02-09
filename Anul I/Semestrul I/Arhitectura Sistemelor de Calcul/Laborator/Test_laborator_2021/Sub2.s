.data
.text
.global main

main:
	movl $100, %esp
	
	pushl %eax
	
	movl $0, %eax
	xorl %ebx, %ebx
	int $0x80
	
	
# se muta o adresa mica de memorie in esp in care programul nu are drepturi
# cand se face pushl %eax, se incearca sa se puna o valoare pe stiva la o
# adresa la care nu este acces, rezulta segmentation fault

