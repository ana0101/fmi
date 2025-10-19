-- 1
data Point = Pt [Int]
    deriving Show

data Arb = Empty | Node Int Arb Arb
    deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

instance ToFromArb Point where
    toArb (Pt []) = Empty
    toArb (Pt (h : t)) = insert h tree
                         where tree = toArb (Pt t)

    fromArb Empty = Pt []
    fromArb (Node value left right) = (fromArb left) <++> Pt [value] <++> (fromArb right)
    -- fromArb arb :: Point

insert :: Int -> Arb -> Arb
insert x Empty = Node x Empty Empty
insert x (Node value left right)
    | x < value = (Node value (insert x left) right)
    | x > value = (Node value left (insert x right))
    | otherwise = (Node value left right)

(<++>) :: Point -> Point -> Point
(Pt l1) <++> (Pt l2) = Pt (l1 ++ l2)

pt = Pt [1, 5, 2, 6, 3]
arb = Node 3 (Node 2 (Node 1 Empty Empty) Empty) (Node 6 (Node 5 Empty Empty) Empty)


-- 2
getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval a b xs = [x | x <- xs, a <= x && x <= b]
-- getFromInterval 5 7 [1..10]

getFromIntervalM :: Int -> Int -> [Int] -> [Int]
getFromIntervalM a b xs = do
    x <- xs
    if a <= x && x <= b then
        return x    -- [x]
    else
        []


-- 3
newtype ReaderWriter env a = RW {getRW :: env -> (a, String)}

instance Monad (ReaderWriter env) where
    return va = RW (\_ -> (va, ""))
    ma >>= k = RW (\env -> 
                    let (va, log1) = getRW ma env
                        (vb, log2) = getRW (k va) env
                    in (vb, log1 ++ log2)
                )

instance Applicative (ReaderWriter env) where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance Functor (ReaderWriter env) where              
    fmap f ma = pure f <*> ma  
    