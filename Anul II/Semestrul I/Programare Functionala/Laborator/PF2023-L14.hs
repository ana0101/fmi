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
    toArb (Pt (h : t)) = Node h Empty (toArb (Pt t)) -- pt Pt sortat

    fromArb Empty = Pt []
    fromArb (Node value left right) = Pt (l ++ [value] ++ r)
                                        where Pt l = fromArb left
                                              Pt r = fromArb right

arb = Node 2 (Node 1 Empty Empty) (Node 4 (Node 3 Empty Empty) (Node 5 Empty Empty))

-- sau:
-- instance ToFromArb Point where
--     toArb (Pt []) = Empty
--     toArb (Pt (h : t)) = insert h tree
--                          where tree = toArb (Pt t)

--     fromArb Empty = Pt []
--     fromArb (Node value left right) = (fromArb left) <++> Pt [value] <++> (fromArb right)
--     -- fromArb arb :: Point

-- insert :: Int -> Arb -> Arb
-- insert x Empty = Node x Empty Empty
-- insert x (Node value left right)
--     | x < value = (Node value (insert x left) right)
--     | x > value = (Node value left (insert x right))
--     | otherwise = (Node value left right)

-- (<++>) :: Point -> Point -> Point
-- (Pt l1) <++> (Pt l2) = Pt (l1 ++ l2)


-- 2
getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval a b l = [x | x <- l, a <= x && x <= b]

getFromIntervalM :: Int -> Int -> [Int] -> [Int]
getFromIntervalM a b l = do
    x <- l
    if a <= x && x <= b then do
        return x -- sau [x]
    else do
        []


-- 3
newtype ReaderWriter env a = RW { getRW :: env -> (a, String) } -- functie care returneaza (a, String)

instance Monad (ReaderWriter env) where -- monad se asteapta la un sg parametru - seamana cu functori
    return va = RW (\_ -> (va, ""))
    ma >>= k = RW (\env ->
                    let (va, log1) = getRW ma env
                        (vb, log2) = getRW (k va) env
                    in (vb, log1 ++ log2)
                )

-- sau:
-- instance Monad (ReaderWriter env) where
--     return x = RW (\_ -> (x, ""))
--     ma >>= k = RW f where f env =  let (va, log1) = getRW ma env
--                                        (vb, log2) = getRW (k va) env
--                                     in (vb, log1 ++ log2)
                    
instance Applicative (ReaderWriter env) where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance Functor (ReaderWriter env) where              
    fmap f ma = pure f <*> ma  
