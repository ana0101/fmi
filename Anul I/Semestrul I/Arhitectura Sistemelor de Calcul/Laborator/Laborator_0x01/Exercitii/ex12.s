.data
	n: .space 4
	dest: .space 50
	src: .space 50
	dest_ret: .space 50
	i: .long 0
	formatScanf: .asciz "%d"
	formatPrintf: .asciz "dest este %s\n"
	formatPrintf1: .asciz "edi este %d\n"
	
.text

memcpy:
	pushl %ebp
	mov %esp, %ebp
	
	# punem dest in ebx, src in ecx si n in edx
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	
	# esi = contor
	xor %esi, %esi
	
	jmp loop_copy
	
	
loop_copy:
	# verificam daca mai sunt caractere de copiat
	cmp %edx, %esi
	jge exit_loop_copy
	
	# copiem urmatorul caracter
	movb (%ecx, %esi, 1), %al
	movb %al, (%ebx, %esi, 1)
	
	incl %esi
	jmp loop_copy
	
exit_loop_copy:
	movb $' ', %al
	movb %al, (%ebx, %esi, 1)
	
	mov %ebx, %eax
	pop %ebp
	ret


.global main

main:
	# il citim pe dest
	pushl $dest
	call gets
	popl %ebx
	
	# il citim pe src
	pushl $src
	call gets
	popl %ebx
	
	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	

	# punem pe stiva numarul n, adresa lui src si adresa lui dest si apelam procedura memcpy
	pusha
	pushl n
	pushl $src
	pushl $dest
	call memcpy
	popl %ebx
	popl %ebx
	popl %ebx
	
	mov %eax, dest_ret
	popa
	
	jmp afisare
	
	
afisare:
	pushl dest_ret
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	jmp exit
	
exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
	
	

	
