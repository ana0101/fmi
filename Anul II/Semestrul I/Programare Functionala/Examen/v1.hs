import Data.Char

-- 1
data Expr = Var String | Val Int | Expr :+: Expr | Expr :*: Expr  
    deriving (Show, Eq)

class Operations exp where  
    simplify :: exp -> exp 

instance Operations Expr where
    simplify (Var s) = Var s
    simplify (Val x) = Val x

    simplify (e :+: (Val 0)) = simplify e
    simplify ((Val 0) :+: e) = simplify e

    simplify (e :*: (Val 0)) = Val 0
    simplify ((Val 0) :*: e) = Val 0

    simplify (e :*: (Val 1)) = simplify e
    simplify ((Val 1) :*: e) = simplify e

    simplify (e1 :+: e2)
        | (simplify e1) == Val 0 || (simplify e2) == Val 0 = simplify ((simplify e1) :+: (simplify e2))
        | otherwise = (simplify e1) :+: (simplify e2)

    simplify (e1 :*: e2)
        | (simplify e1) == Val 0 || (simplify e2) == Val 0 || (simplify e1) == Val 1 || (simplify e2) == Val 1 =
            simplify ((simplify e1) :*: (simplify e2))
        | otherwise = (simplify e1) :*: (simplify e2)

ex1 = ((Val 1) :+: (Var "x")) :*: (Val 1) 
ex2 = ex1 :+: (Val 3) 
ex3 = ((Val 0) :*: (Val 2)) :+: (Val 3) 
ex4 = ex3 :*: Val 5
ex5 = Val 0 :+: Val 3


-- 2
f2 :: String -> String
f2 "" = ""
f2 (h : t)
    | isVowel h = [h] ++ "p" ++ [toLower h] ++ (f2 t)
    | otherwise = [h] ++ (f2 t)

f2M :: String -> String
f2M "" = ""
f2M (h : t) = do
    if isVowel h then do
        ([h] ++ "p" ++ [toLower h] ++ (f2M t))
    else do
        ([h] ++ (f2M t))

isVowel :: Char -> Bool
isVowel c = elem c "aeiouAEIOU"


-- 3
newtype ReaderM env a = ReaderM { runReaderM :: env -> Maybe a }

instance Monad (ReaderM env) where
    return va = ReaderM (\_ -> (Just va))
    ma >>= k = ReaderM f where 
        f env = case runReaderM ma env of
            Just a  -> runReaderM (k a) env
            Nothing -> Nothing

instance Applicative (ReaderM env) where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance Functor (ReaderM env) where              
    fmap f ma = pure f <*> ma  

testReaderM :: ReaderM String String
testReaderM = ma >>= k
    where
        ma = ReaderM (\str -> if length str > 10 then Just (length str) else Nothing)
        k val = ReaderM (\str -> if val `mod` 2 == 0 then Just "par" else Nothing)

main :: IO ()
main = do
    let result = runReaderM testReaderM "HelloWorld!!"
    print result

-- "HelloWorld" => len = 10 => Nothing => Nothing
-- "HelloWorld!" => len = 11 => Just 11 => Nothing (impar)
-- "HelloWorld!!" => len 12 => Just 12 => Just "par"
