data Tree 
    = Empty
    | Node Int Tree Tree Tree

-- 1
class ArbInfo t where
    level :: t -> Int
    sumval :: t -> Int
    nrFrunze :: t -> Int

instance ArbInfo Tree where
    level Empty = 0
    level (Node x left middle right) = 1 + maximum [level left, level middle, level right]

    sumval Empty = 0
    sumval (Node x left middle right) = x + sumval left + sumval middle + sumval right

    nrFrunze Empty = 0
    nrFrunze (Node x Empty Empty Empty) = 1
    nrFrunze (Node x left middle right) = nrFrunze left + nrFrunze middle + nrFrunze right

extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty


class Scalar a where
    zero :: a
    one :: a
    adds :: a -> a -> a
    mult :: a -> a -> a
    negates :: a -> a
    recips :: a -> a

-- 2
instance Scalar Int where
    zero = 0
    one = 1
    adds = (+)
    mult = (*)
    negates = negate
    recips x = 1 `div` x

class (Scalar a) => Vector v a where
    zerov :: v a
    onev :: v a
    addv :: v a -> v a -> v a 
    smult :: a -> v a -> v a 
    negatev :: v a -> v a 

-- 3
data Vector2D a = Vector2D a a
    deriving Show

instance (Scalar a) => Vector Vector2D a where
    zerov = Vector2D zero zero
    onev = Vector2D one one
    addv (Vector2D x1 y1) (Vector2D x2 y2) = Vector2D (adds x1 x2) (adds y1 y2)
    smult s (Vector2D x y) = Vector2D (mult s x) (mult s y)
    negatev (Vector2D x y) = Vector2D (negates x) (negates y)
