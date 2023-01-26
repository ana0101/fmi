def cautare_cuvant(cuv, nume_fis_out, *nume_fis_in):
    fout = open(nume_fis_out, "w")

    for nume_fisier in nume_fis_in:
        fout.writelines(nume_fisier)
        fin = open(nume_fisier, "r")
        text = fin.read().split("\n")

        i = 0
        for i in range(0, len(text)):
            if cuv.lower() in text[i].lower():
                r = " " + str(i+1)
                fout.writelines(r)

        fout.writelines("\n")
        fin.close()
    fout.close()

cautare_cuvant("floare", "rez.txt", "eminescu.txt", "paunescu.txt")