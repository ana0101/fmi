-- class Functor f where
--     fmap :: (a -> b) -> f a -> f b

-- class Functor f => Applicative f where
--     pure :: a -> f a
--     (<*>) :: f (a -> b) -> f a -> f b

-- Just length <*> Just "world" => Just 5
-- Just (++" world") <*> Just "hello," => Just "hello, world"
-- pure (+) <*> Just 3 <*> Just 5 => Just 8
-- pure (+) <*> Just 3 <*> Nothing => Nothing

-- (++) <$> ["ha", "heh"] <*> ["?", "!"] 
-- fmap (++) ["ha", "heh"] <*> ["?", "!"] 
-- [("ha" ++), ("heh" ++)] <*> ["?", "!"]
-- ("ha" ++) = sectiune
-- f = []
-- => ["ha?", "ha!", "heh?", "heh!"]

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
    -- lista de functii pe care o aplic unei liste de elemente
    -- aplic fiecare functie listei de elemente cu fmap, unde t (f) o sa fie []
    -- fmap o sa aplice functia tuturor elementelor din lista si o sa returneze lista cu rezultatele     -- concatenez toate listele cu rezultate pt a o forma pe cea finala cu toate
    -- operatorul ++ e pt [] si nu merge pt List, deci trebuie sa imi fac eu unul

f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test1 = (f <*> v) == Cons 2 (Cons 3 (Cons 2 (Cons 4 Nil)))

-- sau:
-- instance Applicative List where
--     pure x = Cons x Nil
--     Nil <*> _ = Nil
--     (Cons f fs) <*> xs = (fmap f xs) <++> (fs <*> xs)

-- (<++>) :: List a -> List a -> List a
-- Nil <++> ys = ys
-- (Cons x xs) <++> ys = Cons x (xs <++> ys)


-- 2
data Cow = Cow {
    name :: String,
    age :: Int,
    weight :: Int
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
test25 = cowFromString "Milka" (-2) 100 == Nothing

-- c
cowFromString2 :: String -> Int -> Int -> Maybe Cow
cowFromString2 n a w = fmap Cow (noEmpty n) <*> (noNegative a) <*> (noNegative w)

-- Cow :: String -> Int -> Int -> Cow
-- fmap Cow (noEmpty n) = Nothing, noEmpty n = Nothing
--                      = Maybe (Int -> Int -> Cow)
-- Cow = (a -> b), a = String, b = Int -> Int -> Cow, f = Maybe

-- Nothing <*> (noNegative a) = Nothing
-- Maybe (Int -> Int -> Cow) <*> (noNegative a) = Nothing, noNegative a = Nothing
--                                              = Maybe (Int -> Cow)
-- a = Int, b = Int -> Cow, f = Maybe

-- Nothing <*> (noNegative w) = Nothing
-- Maybe (Int -> Cow) <*> (noNegative w) = Nothing, noNegative w = Nothing
--                                       = Maybe Cow
-- a = Int, b = Cow, f = Maybe

test26 = cowFromString2 "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})
test27 = cowFromString2 "Milka" (-2) 100 == Nothing


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
mkName n
    | (validateLength 26 n) /= Nothing = Just (Name n)
    | otherwise                        = Nothing

mkAddress :: String -> Maybe Address
mkAddress a
    | (validateLength 101 a) /= Nothing = Just (Address a)
    | otherwise                         = Nothing

test32 = mkName "Gigel" == Just (Name "Gigel")
test33 = mkAddress "Str Academiei" == Just (Address "Str Academiei")

-- c
mkPerson :: String -> String -> Maybe Person
mkPerson n a
    | (mkName n) /= Nothing && (mkAddress a) /= Nothing = Just (Person (Name n) (Address a))
    | otherwise                                         = Nothing

test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))

-- d
mkName2 :: String -> Maybe Name
mkName2 n = fmap Name (validateLength 26 n)
-- Name :: String -> Name
-- Name = (a -> b)
-- a = String, b = Name, f = Maybe

mkAddress2 :: String -> Maybe Address
mkAddress2 a = fmap Address (validateLength 101 a)

test35 = mkName2 "Gigel" == Just (Name "Gigel")
test36 = mkAddress2 "Str Academiei" == Just (Address "Str Academiei")

mkPerson2 :: String -> String -> Maybe Person
mkPerson2 n a = fmap Person (mkName2 n) <*> (mkAddress2 a)
-- Person :: Name -> Address -> Person
-- Person = (a -> b)
-- a = Name, b = Address -> Person, f = Maybe
-- mkName2 n = Maybe Name = f a
-- fmap Person (mkName2 n) => Maybe (Address -> Person) = f b

-- Maybe (Address -> Person) <*> (mkAddress2 a)
-- a = Address, b = Person, f = Maybe
-- mkAddress2 a = Maybe Address = f a
-- Maybe (Address -> Person) <*> (mkAddress2 a) => Maybe Person = f b

test37 = mkPerson2 "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))
