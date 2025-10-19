data Expr = Const Int
            | Expr :+: Expr
            | Expr :*: Expr
            deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int
            | Node Operation Tree Tree
            deriving (Eq, Show)

instance Show Expr where
    show (Const x) = show x
    show (e1 :+: e2) = "(" ++ show e1 ++  "+" ++ show e2 ++ ")"
    show (e1 :*: e2) = "(" ++ show e1 ++  "*" ++ show e2 ++ ")"

-- 1
evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (e1 :+: e2) = (evalExp e1) + (evalExp e2)
evalExp (e1 :*: e2) = (evalExp e1) * (evalExp e2)

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

-- 2
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add left right) = (evalArb left) + (evalArb right)
evalArb (Node Mult left right) = (evalArb left) * (evalArb right)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)
test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

-- 3
expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)

data IntSearchTree value 
    = Empty
    | BNode (IntSearchTree value) Int (Maybe value) (IntSearchTree value)
    deriving (Show)

abc = BNode (BNode Empty 2 (Just "b") (BNode Empty 3 (Just "a") Empty)) 4 (Just "a") (BNode Empty 8 Nothing Empty)

-- 4
lookup' :: Int -> IntSearchTree value -> Maybe value
lookup' k Empty = Nothing
lookup' k (BNode left key value right)
    | k == key = value
    | k < key  = lookup' k left
    | k > key  = lookup' k right

-- 5
keys :: IntSearchTree value -> [Int]
keys Empty = []
keys (BNode left key value right) = (keys left) ++ [key] ++ (keys right)

-- 6
values :: IntSearchTree value -> [value]
values Empty = []
values (BNode left key Nothing right) = []
values (BNode left key (Just value) right) = (values left) ++ [value] ++ (values right)

-- 7
insert :: Int -> value -> IntSearchTree value -> IntSearchTree value
insert k v Empty = BNode Empty k (Just v) Empty
insert k v (BNode left key value right)
    | k == key = BNode left key (Just v) right
    | k < key  = BNode (insert k v left) key value right
    | k > key  = BNode left key value (insert k v right)

-- 8
delete :: Int -> IntSearchTree value -> IntSearchTree value
delete k Empty = Empty
delete k (BNode left key value right)
    | k == key = BNode left key Nothing right
    | k < key  = BNode (delete k left) key value right
    | k > key  = BNode left key value (delete k right)

-- 9
toList :: IntSearchTree value -> [(Int, value)]
toList Empty = []
toList (BNode left key Nothing right) = (toList left) ++ (toList right)
toList (BNode left key (Just value) right) = (toList left) ++ [(key, value)] ++ (toList right)

-- 10
fromList :: [(Int, value)] -> IntSearchTree value
fromList [] = Empty
fromList ((k, v) : t) = insert k v tree
                        where tree = fromList t

-- 11
printTree :: IntSearchTree value -> String
printTree Empty = ""
printTree (BNode left key value right) = (printTree left) ++ " " ++ show key ++ " " ++ (printTree right)
