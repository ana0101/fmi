prop = input("propozitie: ")
sirGresit = input("sir gresit: ")
sirCorect = input("sir corect: ")

if prop.count(sirGresit) <= 2:
    prop = prop.replace(sirGresit, sirCorect)
    print("propozitia corecta: ", prop)
else:
    prop = prop.replace(sirGresit, sirCorect, 2)
    print("textul contine prea multe greseli, doar 2 au fost corectate")
