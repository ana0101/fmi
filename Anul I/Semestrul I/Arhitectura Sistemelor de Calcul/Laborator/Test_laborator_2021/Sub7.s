.data
.text
.global main

main:
	movl $0xae2b, %eax
	movl %eax, %ecx
	decl %ecx
	
et_loop:
	cmp $0, %ecx
	jl et_exit
	incl %ecx
	jmp et_loop
	
et_exit:
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	
# nu contine o bucla infinita
# ecx incepe bucla cu 0xae2a = (44586)10
# apoi tot creste pana la (0111111111111111111111111111111)2,
# apoi ajunge la 0x80000000 = (10000000000000000000000000000000)2,
# si devine negativ
# si astfel iese din bucla

