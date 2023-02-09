.data
	n: .space 4             # numarul de varfuri
	nrCerinta: .space 4
	i: .space 4
	j: .space 4
	nrLeg: .space 4
	elem: .space 4
	lung: .space 4
	sursa: .space 4
	dest: .space 4
	nrDrumuri: .space 4
	dim: .space 4   
	m: .space 404           # numarul de legaturi pentru fiecare nod
	matrice: .space 40804   # matricea de adiacenta
	m1: .space 40804
	m2: .space 40804
	mres: .space 4
	formatScanf: .asciz "%ld"
	formatPrintf: .asciz "%ld\n"
	
	
.text

matrix_mult:
	pushl %ebp
	movl %esp, %ebp
	
	# salvam registrii callee-saved
	pushl %esi
	pushl %ebx
	
	# 8(%ebp) = m1
	# 12(%ebp) = m2
	# 16(%ebp) = mres
	
	# punem n in ecx
	movl 20(%ebp), %ecx  # n
	
	# alocam trei spatii pe stiva pentru indici si ii initializam cu 0
	xorl %esi, %esi
	subl $4, %esp
	movl %esi, -4(%ebp)  # i
	subl $4, %esp
	movl %esi, -8(%ebp)  # j
	subl $4, %esp
	movl %esi, -12(%ebp) # k
	
	jmp loop_inmult_i
	
	
loop_inmult_i:
	# verificam daca mai sunt elemente de parcurs
	cmp %ecx, -4(%ebp)
	jge exit_loop_inmult_i
	
	# punem 0 in j
	xorl %esi, %esi
	movl %esi, -8(%ebp)
	
	jmp loop_inmult_j
	
exit_loop_inmult_i:
	addl $12, %esp
	
	# restauram registrii callee-saved
	popl %ebx
	popl %esi
	
	popl %ebp
	ret
	
	
loop_inmult_j:
	# verificam daca mai sunt elemente de parcurs
	cmp %ecx, -8(%ebp)
	jge exit_loop_inmult_j
	
	# punem 0 in k
	xorl %esi, %esi
	movl %esi, -12(%ebp)
	
	jmp loop_inmult_k
	
exit_loop_inmult_j:
	incl -4(%ebp)
	jmp loop_inmult_i
	
	
loop_inmult_k:
	# verificam daca mai sunt elemente de parcurs
	cmp %ecx, -12(%ebp)
	jge exit_loop_inmult_k
	
	# mres[i][j] += m1[i][k] * m2[k][j]
	
	# punem m1[i][k] in -16(%ebp) = m1 + n*i*4 + k*4
	movl -4(%ebp), %eax
	xorl %edx, %edx
	imul %ecx
	movl $4, %esi
	xorl %edx, %edx
	imul %esi
	addl 8(%ebp), %eax
	subl $4, %esp
	movl -12(%ebp), %ebx
	movl (%eax, %ebx, 4), %esi
	movl %esi, -16(%ebp)
	
	# punem m2[k][j] in -20(%ebp) = m2 + n*k*4 + j*4
	movl -12(%ebp), %eax
	xorl %edx, %edx
	imul %ecx
	movl $4, %esi
	xorl %edx, %edx
	imul %esi
	addl 12(%ebp), %eax
	subl $4, %esp
	movl -8(%ebp), %ebx
	movl (%eax, %ebx, 4), %esi
	movl %esi, -20(%ebp)
	
	# punem m1[i][k] * m2[k][j] in -24(%ebp)
	movl -16(%ebp), %eax
	movl -20(%ebp), %ebx
	xorl %edx, %edx
	imul %ebx
	subl $4, %esp
	movl %eax, -24(%ebp)
	
	# punem mres[i][j] in esi = mres + n*i*4 + j*4
	movl -4(%ebp), %eax
	xor %edx, %edx
	imul %ecx
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	addl 16(%ebp), %eax
	movl -8(%ebp), %ebx
	movl (%eax, %ebx, 4), %esi
	
	# adaugam in esi m1[i][k] * m2[k][j]
	addl -24(%ebp), %esi
	
	# punem esi in mres[i][j]
	movl -4(%ebp), %eax
	xorl %edx, %edx
	imul %ecx
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	addl 16(%ebp), %eax
	movl -8(%ebp), %ebx
	movl %esi, (%eax, %ebx, 4)
	
	addl $12, %esp
	
	incl -12(%ebp)
	jmp loop_inmult_k
	
exit_loop_inmult_k:
	incl -8(%ebp)
	jmp loop_inmult_j



.global main

main:
	# il citim pe nrCerinta
	pushl $nrCerinta
	pushl $formatScanf
	call scanf
	addl $8, %esp

	# il citim pe n
	pushl $n
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	xorl %eax, %eax
	movl %eax, i
	jmp loop_citire_m
	
	
loop_citire_m:
	# verificam daca mai sunt numere de citit
	movl i, %ecx
	cmp n, %ecx
	jge exit_loop_citire_m
	
	# punem adresa (edi + i*4)
	lea m, %edi
	movl %ecx, %eax
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	addl %eax, %edi
	
	# citim urmatorul numar
	pushl %edi
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	incl i
	jmp loop_citire_m
	
exit_loop_citire_m:
	xorl %eax, %eax
	movl %eax, i
	
	# punem n^2 in ebp
	movl n, %eax
	movl n, %ebx
	xorl %edx, %edx
	imul %ebx
	movl %eax, %ebp
	
	jmp loop_init_matrice
	
	
loop_init_matrice:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp %ebp, %ecx
	jge exit_loop_init_matrice
	
	# punem 0 in urmatorul element
	xorl %eax, %eax
	lea matrice, %edi
	movl %eax, (%edi, %ecx, 4)
	
	incl i
	jmp loop_init_matrice
	
exit_loop_init_matrice:
	xorl %eax, %eax
	movl %eax, i
	jmp loop_linii
	
	
loop_linii:
	# verificam daca mai sunt linii de parcurs
	movl i, %ecx
	cmp n, %ecx
	jge exit_loop_linii
	
	# punem m[i] (numarul de legaturi al nodului i) in nrLeg
	lea m, %edi
	movl (%edi, %ecx, 4), %esi
	movl %esi, nrLeg
	
	# initilizam j
	xorl %eax, %eax
	movl %eax, j
	
	jmp loop_coloane

exit_loop_linii:
	xorl %eax, %eax
	movl %eax, i
	jmp cont_citire
	

loop_coloane:
	# verificam daca mai sunt elemente de citit
	movl j, %ecx
	cmp nrLeg, %ecx
	jge exit_loop_coloane
	
	# citim urmatorul element cu care are legatura in elem
	pushl $elem
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# punem 1 adresa ((matrice + n*i*4) + elem * 4)
	lea matrice, %edi
	movl n, %eax
	movl i, %ebx
	xorl %edx, %edx
	imul %ebx
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	addl %eax, %edi
	movl elem, %ebx
	movl $1, (%edi, %ebx, 4)
	
	incl j
	jmp loop_coloane
	
exit_loop_coloane:
	incl i
	jmp loop_linii
	
	
cont_citire:
	# il citim pe lung
	pushl $lung
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# il citim pe sursa
	pushl $sursa
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# il citim pe dest
	pushl $dest
	pushl $formatScanf
	call scanf
	addl $8, %esp
	
	# punem n^2 in ebp
	movl n, %eax
	movl n, %ebx
	xorl %edx, %edx
	imul %ebx
	movl %eax, %ebp
	
	# punem 0 in i
	xorl %eax, %eax
	movl %eax, i
	
	jmp loop_init_m1_m2
	
	
loop_init_m1_m2:
	# verificam daca mai sunt elemente de parcurs
	movl i, %ecx
	cmp %ebp, %ecx
	jge exit_loop_init_m1_m2
	
	# punem urmatorul element in m1 si m2
	lea matrice, %edi
	movl (%edi, %ecx, 4), %esi
	lea m1, %edi
	movl %esi, (%edi, %ecx, 4)
	lea m2, %edi
	movl %esi, (%edi, %ecx, 4)
	
	incl i
	jmp loop_init_m1_m2
	
exit_loop_init_m1_m2:
	movl $1, i
	jmp alocare_mres
	
	
alocare_mres:
	# punem (n+1) * (n+1) * 4 in dim
	movl n, %eax
	incl %eax
	movl %eax, %ebx
	xorl %edx, %edx
	imul %ebx
	movl $4, %ebx
	xorl %edx, %edx
	imul %ebx
	movl %eax, dim

	movl $192, %eax     # codul pentru apelul de sistem mmap2
	movl $0, %ebx       # kernel-ul va alege adresa de mapare
	movl dim, %ecx      # dimensiunea de alocat ((n+1) * (n+1) * 4)
	movl $3, %edx       # PROT_READ (memoria poate fi citita) | PROT_WRITE (se poate scrie in memorie) 
			    # protectia memoriei (avem nevoie sa citim si sa scriem)
	movl $34, %esi      # MAP_PRIVATE (update-urile la mapare nu sunt vizibile pentru alte procese) 
			    # | MAP_ANON (maparea nu este sustinuta/conectata de niciun fisier, continutul este initializat cu zero)
	movl $-1, %edi      # fd (file descriptor) nu exista pentru ca nu avem niciun fisier (MAP_ANON) si trebuie sa fie -1
	movl $0, %ebp       # offset nu exista pentru ca nu avem niciun fisier
	int $0x80
	
	# punem adresa catre memoria alocata in mres
	movl %eax, mres
	
	jmp loop_ridicare_putere
	
	
loop_ridicare_putere:
	# verificam daca mai trebuie sa inmultim
	movl i, %ecx
	cmp lung, %ecx
	jge exit_loop_ridicare_putere

	# punem pe stiva numarul n, adresele mres, m2 si m1
	pushl n
	pushl mres
	pushl $m2
	pushl $m1
	
	# apelam procedura
	call matrix_mult
	
	addl $16, %esp
	
	# punem valorile din mres in m1
	# punem n^2 in ebp
	movl n, %eax
	movl n, %ebx
	xorl %edx, %edx
	imul %ebx
	movl %eax, %ebp
	
	xorl %eax, %eax
	movl %eax, j
	
	jmp loop_mres_m1
	
	
loop_mres_m1:
	# verificam daca mai sunt elemente de parcurs
	movl j, %ecx
	cmp %ebp, %ecx
	jge exit_loop_mres_m1
	
	# punem urmatorul element
	movl mres, %edi
	movl (%edi, %ecx, 4), %esi
	lea m1, %edi
	movl %esi, (%edi, %ecx, 4)
	
	incl j
	jmp loop_mres_m1
	
exit_loop_mres_m1:
	incl i
	jmp loop_ridicare_putere

exit_loop_ridicare_putere:
	jmp dealocare_mres
	
	
dealocare_mres:
	movl $91, %eax      # codul pentru apelul de sistem munmap
	movl mres, %ebx     # adresa unde a fost alocata memoria
	movl dim, %ecx      # dimensiunea care a fost alocata
	int $0x80
	
	jmp numar_drumuri
	
	
numar_drumuri:
	# numarul se afla pe pozitia m1 + n*sursa*4 + dest*4
	movl n, %eax
	movl sursa, %ebx
	xorl %edx, %edx
	imul %ebx
	movl $4, %ebx
	imul %ebx
	lea m1, %edi
	addl %eax, %edi
	movl dest, %ebx
	movl (%edi, %ebx, 4), %esi
	movl %esi, nrDrumuri
	
	jmp afisare_nr_drumuri
	
afisare_nr_drumuri:
	pushl nrDrumuri
	pushl $formatPrintf
	call printf
	addl $8, %esp
	
	jmp exit
	
	
exit:
	pushl $0
	call fflush
	addl $4, %esp
	
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	

