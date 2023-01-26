# a
cod = input("textul codificat: ")
l = len(cod)
k = -1
text = ""

for i in range(l):
    if cod[i]>='0' and cod[i]<='9':
        if k == -1:
            k = int(cod[i])
        else:
            k = k*10 + int(cod[i])
    else:
        text = text + cod[i]*k
        k = -1

print("textul decodificat: ", text)


# b
text = input("textul decodificat: ")
l = len(text)
cod = ""
x = text[0]
k = 1
i = 1

while i<l:
    if text[i] == x:
        k += 1
    else:
        cod = cod + str(k) + x
        x = text[i]
        k = 1
    i += 1
cod = cod + str(k) + x

print("textul codificat: ", cod)
