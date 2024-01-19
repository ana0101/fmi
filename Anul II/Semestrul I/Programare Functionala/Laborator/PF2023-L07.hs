data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq    

-- 1
evalExp :: Expr -> Int
evalExp e = case e of
	Const x -> x
	e1 :+: e2 -> evalExp e1 + evalExp e2
	e1 :*: e2 -> evalExp e1 * evalExp e2

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16


data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)
           
instance Show Expr where
	show (Const x) = show x
	show (e1 :+: e2) = "(" ++ show e1 ++ " + "++ show e2 ++ ")"
	show (e1 :*: e2) = "(" ++ show e1 ++ " * "++ show e2 ++ ")"       

-- 2
evalArb :: Tree -> Int
evalArb a = case a of
	Lf x -> x
	Node Add a1 a2 -> evalArb a1 + evalArb a2
	Node Mult a1 a2 -> evalArb a1 * evalArb a2

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
expToArb e = case e of
	Const x -> Lf x
	e1 :+: e2 -> Node Add (expToArb e1) (expToArb e2)
	e1 :*: e2 -> Node Mult (expToArb e1) (expToArb e2)


data IntSearchTree value
  	= Empty
  	| BNode
    	(IntSearchTree value)     -- elemente cu cheia mai mica
      	Int                       -- cheia elementului
      	(Maybe value)             -- valoarea elementului
      	(IntSearchTree value)     -- elemente cu cheia mai mare
	deriving Show

abc = BNode (BNode Empty 2 (Just "b") (BNode Empty 3 (Just "a") Empty)) 4 (Just "a") (BNode Empty 8 Nothing Empty)
  
-- 4
lookup' :: Int -> IntSearchTree value -> Maybe value
lookup' x v = case v of
	Empty -> Nothing
	BNode c1 c val c2 -> if x == c then val
						 else if x < c then lookup' x c1
						 else lookup' x c2

-- 5
keys :: IntSearchTree value -> [Int]
keys v = case v of
	Empty -> []
	BNode c1 c val c2 -> c : keys c1 ++ keys c2

-- 6
values :: IntSearchTree value -> [value]
values v = case v of
	Empty -> []
	BNode c1 c val c2 -> case val of
							Nothing -> values c1 ++ values c2
							Just val -> val : values c1 ++ values c2

-- 7
insert :: Int -> Maybe value -> IntSearchTree value -> IntSearchTree value
insert c v Empty = case v of
  	Nothing -> BNode Empty c Nothing Empty
  	Just val -> BNode Empty c (Just val) Empty
insert c v (BNode left key val right)
  	| c == key  = BNode left key v right 
  	| c < key   = BNode (insert c v left) key val right
  	| otherwise = BNode left key val (insert c v right)

-- 8
delete :: Int -> IntSearchTree value -> IntSearchTree value
delete c Empty = Empty
delete c (BNode left key val right)
	| c == key   = BNode left key Nothing right
	| c < key    = delete c left
	| otherwise  = delete c right 

-- 9
toList :: IntSearchTree value -> [(Int, Maybe value)]
toList Empty = []
toList (BNode left key val right) = (key, val) : toList left ++ toList right

-- 10
fromList :: [(Int, value)] -> IntSearchTree value 
fromList [] = Empty
fromList ((key, val):t) = insert key (Just val) tree
						  where tree = fromList t 

-- 11
printTree :: IntSearchTree value -> String
printTree Empty = ""
printTree (BNode left key val right) = printTree left ++ " " ++ show key ++ " " ++ printTree right

-- balance :: IntSearchTree value -> IntSearchTree value
-- balance = undefined
