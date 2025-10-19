import Data.Char

-- 1
data Expr = Var String | Val Int | Plus Expr Expr | Mult Expr Expr  
    deriving (Show, Eq)

class Operations exp where  
    simplify :: exp -> exp 

instance Operations Expr where
    simplify (Var s) = (Var s)
    simplify (Val x) = (Val x)

    simplify (Plus (Val 0) e) = simplify e
    simplify (Plus e (Val 0)) = simplify e

    simplify (Mult (Val 0) e) = Val 0
    simplify (Mult e (Val 0)) = Val 0

    simplify (Mult (Val 1) e) = simplify e
    simplify (Mult e (Val 1)) = simplify e

    simplify (Plus e1 e2)
        | simplify e1 == Val 0 || simplify e2 == Val 0 = simplify (Plus (simplify e1) (simplify e2))
        | otherwise = Plus (simplify e1) (simplify e2)

    simplify (Mult e1 e2)
        | simplify e1 == Val 0 || simplify e1 == Val 1 || simplify e2 == Val 0 || simplify e2 == Val 1 =
            simplify (Mult (simplify e1) (simplify e2))
        | otherwise = Mult (simplify e1) (simplify e2)

ex1 = Mult (Plus (Val 1) (Var "x")) (Val 1) 
ex2 = Plus ex1 (Val 3) 
ex3 = Plus (Mult (Val 0) (Val 2)) (Val 3) 
ex4 = Mult ex3 (Val 5)


-- 2
f2 :: String -> String
f2 "" = ""
f2 (h : t)
    | isConsonant h = [h] ++ "P" ++ [h] ++ (f2 t)
    | otherwise     = [h] ++ (f2 t)

isConsonant :: Char -> Bool
isConsonant c
    | (isAlpha c) && (not (elem c "aeiouAEIOU")) = True
    | otherwise                                  = False


-- 3
newtype ReaderM env a = ReaderM { runReaderM :: env -> Either String a }

instance Monad (ReaderM env) where
    return va = ReaderM (\_ -> (Right va))
    ma >>= k = ReaderM (\env -> case runReaderM ma env of
                        Right va -> runReaderM (k va) env
                        Left s   -> Left s
                    )

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
        ma = ReaderM (\ str -> if length str > 10 then Right (length str) else Left "") 
        k val = ReaderM (\ str -> if val `mod` 2 == 0 then Right "par" else Left "")

main :: IO ()
main = do
    let result = runReaderM testReaderM "HelloWorld!!"
    print result

-- "HelloWorld" => len 10 => Left "" => Left ""
-- "HelloWorld!" => len 11 => Right 11 =>  Left ""
-- "HelloWorld!!" => len 12 => Right 12 => Right "par"
