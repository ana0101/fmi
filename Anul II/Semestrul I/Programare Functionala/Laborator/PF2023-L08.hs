-- 1
class Collection c where
  	empty :: c key value
  	singleton :: key -> value -> c key value
  	insert :: Ord key => key -> value -> c key value -> c key value
  	clookup :: Ord key => key -> c key value -> Maybe value
	delete :: Ord key => key -> c key value -> c key value

	keys :: c key value -> [key]
	keys t = map fst $ toList t

	values :: c key value -> [value]
	values t = map snd $ toList t

	toList :: c key value -> [(key, value)]

	fromList :: Ord key => [(key, value)] -> c key value
	fromList [] = empty
	fromList ((k, v) : tail) = insert k v t 
							   where t = fromList tail


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
		| otherwise = PairList ((k, v) : getPairList (delete key (PairList t)))

	toList (PairList p) = p

instance (Show k, Show v) => Show (PairList k v) where
	show (PairList p) = show p

lista = PairList [(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd')]


-- 3
data SearchTree key value
	= Empty
	| BNode
		(SearchTree key value) -- elemente cu cheia mai mica
		key                    -- cheia elementului
		(Maybe value)          -- valoarea elementului
		(SearchTree key value) -- elemente cu cheia mai mare
	deriving Show

instance Collection SearchTree where
	empty = Empty
	singleton key value = BNode Empty key (Just value) Empty

	insert key value Empty = singleton key value
	insert key value (BNode left k v right)
		| key == k  = BNode left k (Just value) right
		| key < k   = BNode (insert key value left) k v right
		| otherwise = BNode left k v (insert key value right)

	clookup key Empty = Nothing
	clookup key (BNode left k v right)
		| key == k  = v
		| key < k   = clookup key left
		| otherwise = clookup key right

	delete key Empty = Empty
	delete key (BNode left k v right)
		| key == k  = BNode left k Nothing right
		| key < k   = BNode (delete key left) k v right
		| otherwise = BNode left k v (delete key right)

	toList Empty = []
	toList (BNode left k v right) = case v of
		Just v  -> toList left ++ [(k, v)] ++ toList right
		Nothing -> toList left ++  toList right

abc = BNode (BNode Empty 1 (Just "a") (BNode Empty 3 (Just "c") Empty)) 4 (Just "d") (BNode Empty 6 Nothing Empty)


-- 4
data Punct = Pt [Int]

instance Show Punct where
	show (Pt []) = "()"
	show (Pt (h:t)) = "(" ++ show h ++ myShow t

myShow :: [Int] -> String
myShow [] = ")"
myShow (h:t) = "," ++ show h ++ myShow t 

pct = Pt [1, 2, 3]


-- 5
data Arb = Vid | F Int | N Arb Arb
    deriving Show

class ToFromArb a where
 	toArb :: a -> Arb
	fromArb :: Arb -> a

instance ToFromArb Punct where
	toArb (Pt []) = Vid
	toArb (Pt (h:t)) = N (F h) (toArb (Pt t))

	-- fromArb Vid = Pt []
	-- fromArb (F x) = Pt [x]
	-- fromArb (N a1 a2) = Pt ((fromArb $ a1 :: Punct) ++ (fromArb $ a2 :: Punct))


-- 6
data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
	perimeter :: (Floating a) => g a -> a
	area :: (Floating a) =>  g a -> a

instance GeoOps Geo where
	perimeter (Square x) = 4 * x
	perimeter (Rectangle x y) = 2 * (x + y)
	perimeter (Circle r) = 2 * pi * r

	area (Square x) = x * x
	area (Rectangle x y) = x * y
	area (Circle r) = pi * r * r

s :: Geo Double
s = Square 2
r :: Geo Double
r = Rectangle 2 3
c :: Geo Double
c = Circle 3

-- 7
instance (Eq a, Floating a) => Eq (Geo a) where
	geo1 == geo2 = perimeter geo1 == perimeter geo2
