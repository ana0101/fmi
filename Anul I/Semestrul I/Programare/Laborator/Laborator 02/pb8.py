s = input("s = ")
lista = s.split()

if len(lista) != 2:
    print("nume complet incorect")
else:
    for i in range(2):
        if lista[i].count('-') > 1:
            print("nume complet incorect")
            break
        else:
            nume = lista[i].split('-')
            for j in range(len(nume)):
                if nume[j].isalpha == False:
                    print("nume complet incorect")
                    break
                if len(nume[j]) < 3:
                    print("nume complet incorect")
                    break
                if nume[j].istitle == False:
                    print("nume complet incorect")
                    break
    else:
        print("nume complet corect")
