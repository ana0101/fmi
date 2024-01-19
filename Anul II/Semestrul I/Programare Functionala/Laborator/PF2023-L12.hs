{- 
class Functor f where 
     fmap :: (a -> b) -> f a -> f b 
class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b

Just length <*> Just "world" => Just 5
Just (++" world") <*> Just "hello,"
pure (+) <*> Just 3 <*> Just 5 => Just 8
pure (+) <*> Just 3 <*> Nothing
(++) <$> ["ha","heh"] <*> ["?","!"]
-}

-- 1
data List a = Nil | Cons a (List a) deriving (Eq, Show)

(<++>) :: (List a) -> (List a) -> (List a)
(<++>) Nil ys = ys
(<++>) (Cons x1 xs) ys = Cons x1 (xs <++> ys)

instance Functor List where
    fmap f Nil = Nil
    fmap f (Cons x xs) = Cons (f x) (fmap f xs)

instance Applicative List where
    pure x = Cons x Nil
    (<*>) Nil xs = Nil
    (<*>) (Cons f fs) xs = (fmap f xs) <++> ((<*>) fs xs)

f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test1 = (f <*> v) == Cons 2 (Cons 3 (Cons 2 (Cons 4 Nil)))


-- 2
data Cow = Cow {
        name :: String
        , age :: Int
        , weight :: Int
        } deriving (Eq, Show)

-- a
noEmpty :: String -> Maybe String
noEmpty "" = Nothing
noEmpty s = Just s

noNegative :: Int -> Maybe Int
noNegative x
    | x < 0     = Nothing
    | otherwise = Just x

test21 = noEmpty "abc" == Just "abc"
test22 = noNegative (-5) == Nothing 
test23 = noNegative 5 == Just 5 

-- b
cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString n a w 
    | ((noEmpty n == Nothing) || (noNegative a == Nothing) || (noNegative w == Nothing)) = Nothing
    | otherwise = Just (Cow n a w)

test24 = cowFromString "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})

-- c
cowFromString2 :: String -> Int -> Int -> Maybe Cow
cowFromString2 n a w = fmap Cow (noEmpty n) <*> (noNegative a) <*> (noNegative w)

test25 = cowFromString2 "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})


-- 3
newtype Name = Name String deriving (Eq, Show)
newtype Address = Address String deriving (Eq, Show)

data Person = Person Name Address
    deriving (Eq, Show)

-- a
validateLength :: Int -> String -> Maybe String
validateLength x s
    | length s < x = Just s
    | otherwise    = Nothing

test31 = validateLength 5 "abc" == Just "abc"

-- b
mkName :: String -> Maybe Name
mkName s = fmap Name (validateLength 26 s)

mkAddress :: String -> Maybe Address
mkAddress s = fmap Address (validateLength 101 s)

test32 = mkName "Gigel" ==  Just (Name "Gigel")
test33 = mkAddress "Str Academiei" ==  Just (Address "Str Academiei")

-- c
mkPerson :: String -> String -> Maybe Person
mkPerson n a = fmap Person (mkName n) <*> (mkAddress a)

test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))