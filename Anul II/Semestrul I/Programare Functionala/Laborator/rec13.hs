{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
    return = Just
    Just va >>= k = k va
    Nothing >>= _ = Nothing

instance Applicative Maybe where
    pure = return
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)       

instance Functor Maybe where              
    fmap f ma = pure f <*> ma   
-}

-- 1
pos :: Int -> Bool
pos x = if (x >= 0) then True else False

fct :: Maybe Int -> Maybe Bool
fct mx = mx >>= (\x -> Just (pos x))
-- fct Nothing = Nothing
-- fct (Just 2) = Just True
-- fct (Just (-2)) = Just False

fct2 :: Maybe Int -> Maybe Bool
fct2 mx = do
    x <- mx
    Just (pos x)


-- 2
-- a
addM :: Maybe Int -> Maybe Int -> Maybe Int
addM (Just x) (Just y) = Just (x + y)
addM _ _ = Nothing

-- b
addM2 :: Maybe Int -> Maybe Int -> Maybe Int
addM2 mx my = do
    x <- mx
    y <- my
    return (x + y)  -- Just (x + y)


-- 3
-- monada lista
cartesian_product xs ys = xs >>= (\x -> (ys >>= \y -> return (x, y)))
-- cartesian_product2 [1, 2, 3] ["a", "b"] => [(1,"a"),(1,"b"),(2,"a"),(2,"b"),(3,"a"),(3,"b")]

cartesian_product2 xs ys = do
    x <- xs
    y <- ys
    return (x, y)   -- [(x, y)]

-- monada lista
prod f xs ys = [f x y | x <- xs, y <- ys]
-- prod (*) [1, 2] [3, 4, 5] => [3,4,5,6,8,10]

prod2 f xs ys = do
    x <- xs
    y <- ys
    return (f x y)  -- [f x y]

myGetLine :: IO String
myGetLine = getChar >>= \x ->
    if x == '\n' then
        return []
    else
        myGetLine >>= \xs -> return (x : xs)

myGetLine2 :: IO String
myGetLine2 = do
    x <- getChar
    if x == '\n' then
        return []
    else
        do
            xs <- myGetLine2
            return (x : xs)
        
-- pt testare
main :: IO ()
main = do
    putStrLn "Enter a line: "
    line <- myGetLine2
    putStrLn $ "You entered: " ++ line

-- ca sa rulez programul:
-- terminal deschis in folder-ul cu programul (nu ghci)
-- compilez: ghc nume.hs
-- rulez: .\nume.exe


-- 4
prelNo noin = sqrt noin

ioNumber = do
    noin <- readLn :: IO Float
    putStrLn $ "Intrare\n" ++ (show noin)
    let noout = prelNo noin
    putStrLn $ "Iesire"
    print noout

ioNumber2 = readLn >>= \noin -> 
    putStrLn ("Intrare\n" ++ show noin) >>
    let noout = prelNo noin 
    in putStrLn $ "Iesire\n" ++ show noout


-- 6
data Person = Person { name :: String, age :: Int }

-- a
showPersonN :: Person -> String
showPersonN (Person n a) = "NAME: " ++ n

showPersonA :: Person -> String
showPersonA (Person n a) = "AGE: " ++ show a

-- b
showPerson :: Person -> String
showPerson p = "(" ++ showPersonN p ++ ", " ++ showPersonA p ++ ")"

-- c
newtype Reader env a = Reader { runReader :: env -> a }

ask :: Reader env env
ask = Reader id

instance Monad (Reader env) where
    return x = Reader (\_ -> x)
    ma >>= k = Reader f
        where f env = let a = runReader ma env
                      in  runReader (k a) env

instance Applicative (Reader env) where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance Functor (Reader env) where              
    fmap f ma = pure f <*> ma 

mshowPersonN :: Reader Person String
mshowPersonN = do
    env <- ask
    return ("NAME: " ++ name env)

mshowPersonA = do
    env <- ask
    return ("AGE: " ++ show(age env))

mshowPerson :: Reader Person String
mshowPerson = do
    env <- ask
    name <- mshowPersonN
    age <- mshowPersonA
    return $ "(" ++ name ++ ", " ++  age ++ ")"
    