# a
s1 = input("text = ")
s2 = ""
k = int(input("k = "))
l = len(s1)

for i in range(l):
    if 'a' <= s1[i] <= 'z':
        aux = ord(s1[i]) + k
        while aux > ord('a') + 25:
            aux -= 26
        s2 += chr(aux)
    else:
        if 'A' <= s1[i] <= 'Z':
            aux = ord(s1[i]) + k
            while aux > ord('A') + 25:
                aux -= 26
            s2 += chr(aux)
        else:
            s2 += s1[i]

print("text criptat: ", s2)


# b
s1 = input("text criptat = ")
s2 = ""
k = int(input("k = "))
l = len(s1)

for i in range(l):
    if 'a' <= s1[i] <= 'z':
        aux = ord(s1[i]) - k
        while aux < ord('a'):
            aux += 26
        s2 += chr(aux)
    else:
        if 'A' <= s1[i] <= 'Z':
            aux = ord(s1[i]) - k
            while aux < ord('A'):
                aux += 26
            s2 += chr(aux)
        else:
            s2 += s1[i]

print("text decriptat: ", s2)
