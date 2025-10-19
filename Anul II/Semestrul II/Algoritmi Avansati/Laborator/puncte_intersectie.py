class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, val):
        if self.root is None:
            self.root = Node(val)
            return
        
        node = self.root
        while True:
            if val < node.val:
                if node.left is None:
                    node.left = Node(val)
                    break
                else:
                    node = node.left
            else:
                if node.right is None:
                    node.right = Node(val)
                    break
                else:
                    node = node.right


    def delete(self, val):
        self.root = self.delete2(self.root, val)

    # sterge nodul cu valoarea val din subarborele cu radacina in node
    # si returneaza radacina subarborelui modificat
    def delete2(self, node, val):
        root = node
        parent = None

        # cat timp inca nu am gasit nodul de sters
        while node and node.val != val:
            parent = node
            if val < node.val:
                node = node.left
            else:
                node = node.right

        # teoretic nu ar trebui sa se intample asta
        if node is None:
            return root
        
        # daca nodul nu are copii
        if node.left is None and node.right is None:
            # daca nodul e radacina il stergem
            if node == root:
                root = None
            # altfel il stergem din parinte
            elif parent.left == node:
                parent.left = None
            elif parent.right == node:
                parent.right = None

        # daca nodul are un singur copil
        elif node.left is None or node.right is None:
            if node.left:
                child = node.left
            elif node.right:
                child = node.right
            
            # daca nodul e radacina il inlocuim cu copilul
            if node == root:
                root = child
            # altfel il inlocuim in parinte cu copilul
            elif parent.left == node:
                parent.left = child
            elif parent.right == node:
                parent.right = child

        # daca nodul are 2 copii
        elif node.left and node.right:
            # gasim succesorul si il inlocuim cu el, apoi il stergem pe succesor
            successor = self.find_min(node.right)
            aux = successor.val
            self.delete2(node.right, aux)
            node.val = aux

        return root
        
    # gaseste minimul dintr-un subarbore cu radacina in node
    def find_min(self, node):
        while node.left is not None:
            node = node.left
        return node
    
    def find_in_range(self, a, b):
        nodes = []
        self.find_in_range2(self.root, a, b, nodes)
        return nodes
    
    def find_in_range2(self, node, a, b, nodes):
        if node is None:
            return
        if a <= node.val <= b:
            nodes.append(node.val)
        if a < node.val:
            self.find_in_range2(node.left, a, b, nodes)
        if node.val < b:
            self.find_in_range2(node.right, a, b, nodes)
            

n = int(input())

# points = punctele pe care le parcurgem
points = []

for _ in range(n):
    x1, y1, x2, y2 = [int(x) for x in input().split()]
    # segment vertical
    if x1 == x2:
        points.append((x1, y1, y2, 'v'))
    # segment orizontal
    elif y1 == y2:
        points.append((x1, y1, 'h', 'left'))
        points.append((x2, y2, 'h', 'right'))

# sortam points dupa x pentru a putea parcurge de la stanga la dreapta toate evenimentele
points.sort(key=lambda p: p[0])

# print(points)

# bst = arbore binar de cautare in care tinem coordonatele y ale segmentelor orizontale
bst = BinarySearchTree()

num = 0

for p in points:
    # daca segmentul e orizontal
    if p[2] == 'h':
        # daca e capatul stang inseram coordonata y in bst
        if p[3] == 'left':
            bst.insert(p[1])
        # daca e capatul drept stergem coordonata y din bst
        else:
            bst.delete(p[1])
    # daca segmentul e vertical
    elif p[3] == 'v':
        # cautam in bst toate coordonatele y care sunt in intervalul [y1, y2]
        y1, y2 = p[1], p[2]
        if y1 > y2:
            y1, y2 = y2, y1
        nodes = bst.find_in_range(p[1], p[2])
        num += len(nodes)

print(num)