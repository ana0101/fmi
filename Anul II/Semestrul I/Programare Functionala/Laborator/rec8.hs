-- 1
class Collection c where
    empty :: c key value
    singleton :: key -> value -> c key value
    insert :: Ord key => key -> value -> c key value -> c key value
    clookup :: Ord key => key -> c key value -> Maybe value
    delete :: Ord key => key -> c key value -> c key value

    keys :: c key value -> [key]
    keys c = map fst (toList c)

    values :: c key value -> [value]
    values c = map snd (toList c)

    toList :: c key value -> [(key, value)]

    fromList :: Ord key => [(key, value)] -> c key value
    fromList [] = empty
    fromList ((key, value) : t) = insert key value c
                                where c = fromList t

-- 2
newtype PairList k v = PairList { getPairList :: [(k, v)] }
instance Collection PairList where
    empty = PairList []

    singleton key value = PairList [(key, value)]

    insert key value (PairList []) = singleton key value
    insert key value (PairList ((k, v) : t))
        | key == k  = PairList ((key, value) : t)
        | otherwise = PairList ((k, v) : getPairList (insert key value (PairList t)))

    clookup key (PairList []) = Nothing
    clookup key (PairList ((k, v) : t))
        | key == k  = Just v
        | otherwise = clookup key (PairList t)

    delete key (PairList []) = PairList []
    delete key (PairList ((k, v) : t))
        | key == k  = PairList t
        | otherwise = PairList ((k, v) : getPairList  (delete key (PairList t)))

    toList (PairList l) = l

instance (Show k, Show v) => Show (PairList k v) where
	show (PairList l) = show l

lista = PairList [(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd')]

-- 3
data SearchTree key value 
    = Empty
    | BNode (SearchTree key value) key (Maybe value) (SearchTree key value)
    deriving (Show)

instance Collection SearchTree where
    empty = Empty

    singleton key value = BNode Empty key (Just value) Empty

    insert k v Empty = BNode Empty k (Just v) Empty
    insert k v (BNode left key value right)
        | k == key = BNode left key (Just v) right
        | k < key  = BNode (insert k v left) key value right
        | k > key  = BNode left key value (insert k v right)

    clookup k Empty = Nothing
    clookup k (BNode left key value right)
        | k == key = value
        | k < key  = clookup k left
        | k > key  = clookup k right

    delete k Empty = Empty
    delete k (BNode left key value right)
        | k == key = BNode left key Nothing right
        | k < key  = BNode (delete k left) key value right
        | k > key  = BNode left key value (delete k right)

    toList Empty = []
    toList (BNode left key Nothing right) = (toList left) ++ (toList right)
    toList (BNode left key (Just value) right) = (toList left) ++ [(key, value)] ++ (toList right)


data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
        deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

-- 4
instance Show Punct where
    show (Pt []) = "()"
    show (Pt (h : t)) = "(" ++ show h ++ show2 t

show2 :: [Int] -> String
show2 [] = ")"
show2 (h : t) = ", " ++ show h ++ show2 t

-- 5
instance ToFromArb Punct where
    toArb (Pt []) = Vid
    toArb (Pt (h : t)) = N (F h) (toArb (Pt t))

    fromArb Vid = Pt []
    fromArb (F x) = Pt [x]
    fromArb (N left right) = append (fromArb left) (fromArb right)

append :: Punct -> Punct -> Punct
append (Pt l1) (Pt l2) = Pt (l1 ++ l2)


data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
    perimeter :: (Floating a) => g a -> a
    area :: (Floating a) => g a -> a

-- 6
instance GeoOps Geo where
    perimeter (Square x) = 4 * x
    perimeter (Rectangle x y) = 2 * (x + y)
    perimeter (Circle x) = 2 * pi * x

    area (Square x) = x * x
    area (Rectangle x y) = x * y
    area (Circle x) = pi * x * x

-- 7
instance (Eq a, Floating a) => Eq (Geo a) where
    geo1 == geo2 = perimeter geo1 == perimeter geo2
