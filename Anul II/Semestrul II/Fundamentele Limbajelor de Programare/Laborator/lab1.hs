import Data.Char

newtype Parser a = Parser { parse :: String -> [(a,String)] }

item :: Parser Char
item = Parser (\cs -> case cs of
                "" -> []
                (c:cs) -> [(c,cs)])
-- parse item "abc" => [('a', "bc")]

instance Monad Parser where
    return a = Parser (\cs -> [(a,cs)])
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))

instance Applicative Parser where
    pure = return
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)    

instance Functor Parser where              
    fmap f ma = pure f <*> ma   
  
{-
instance Functor Parser where              
    fmap g p = Parser (\cs -> map (\(a,cs') -> (g a, cs')) (parse p cs))

instance Applicative Parser where
    pure a = Parser (\cs -> [(a, cs)])
    pg <*> pa = Parser (\cs -> concat (map (\(g, cs') -> (parse (fmap g pa) cs')) (parse pg cs)))

instance Monad Parser where
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))
-}

zero :: Parser a
zero = Parser (const [])
-- parse zero "abc" => []

psum :: Parser a -> Parser a -> Parser a
psum p q = Parser (\cs -> (parse p cs) ++ (parse q cs))
-- parse (psum item item) "abc" => [('a',"bc"), ('a',"bc")]

(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = Parser (\cs -> case parse (psum p q) cs of
                                [] -> []
                                (x:xs) -> [x])
-- parse (item <|> item) "abc" => [('a', "bc")]

dpsum0 :: Parser [a] -> Parser [a]
dpsum0 p = p <|> (return [])

sat :: (Char -> Bool) -> Parser Char
sat p = do
            c <- item
            if p c then return c else zero
-- parse (sat (== 'a')) "abc" => [('a', "bc")]
-- parse (sat (== 'b')) "abc" => []

char :: Char -> Parser Char
char c = sat (c ==)
-- parse (char 'x') "xabc" => [('x', "abc")]
-- parse (char 'a') "xabc" => []
-- parse (char 'a') "" => []

string :: String -> Parser String
string [] = return []
string (c:cs) = do
                    pc <- char c
                    prest <- string cs
                    return (pc : prest)
-- parse (string "abc") "abcdef" => [("abc", "def")]
-- parse (string "bc") "abcdef" => []
-- parse (string "bc") "" => []

many0 :: Parser a -> Parser [a]
many0 p = dpsum0 (many1 p)
-- parse (many0 (char 'x')) "" => [("", "")]
-- parse (many0 (char 'x')) "x" => [("x", "")]
-- parse (many0 (char 'x')) "xxabc" => [("xx", "abc")]
-- parse (many0 (char 'a')) "xxabc" => [("", "xxabc")]

many1 :: Parser a -> Parser [a]
many1 p = do 
    a <- p
    aa <- many0 p
    return (a : aa)
-- parse (many1 (char 'x')) "" => []
-- parse (many1 (char 'x')) "x" => [("x", "")]
-- parse (many1 (char 'x')) "xxabc" => [("xx", "abc")]
-- parse (many1 (char 'a')) "xxabc" => []

spaces :: Parser String
spaces = many0 (sat isSpace)
--

token :: Parser a -> Parser a
token p = do
            spaces
            x <- p
            spaces
            return x
-- parse (token (string "xyz")) "  xyz  " => [("xyz", "")]

symbol :: String -> Parser String
symbol symb = token (string symb)

sepBy0 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy0` sep = dpsum0 (p `sepBy1` sep)
-- parse (sepBy0 (string "ab") (char ',')) "ab,ab,ab" => [(["ab", "ab", "ab"], "")]

sepBy1 :: Parser a1 -> Parser a2 -> Parser [a1]
p `sepBy1` sep = do
                    a <- p
                    as <- many0 (do
                                    sep
                                    p)
                    return (a:as)

look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )
-- parse look "xyz" => [(Just 'x', "xyz")]

takeUntil :: Char -> Parser [Char]
takeUntil stop = consumeRest "" stop
    where consumeRest acc stop = do
                                    l <- look
                                    if l == Just stop then return [] else do
                                                                            c <- item
                                                                            cs <- consumeRest (acc ++ [c]) stop
                                                                            return (c:cs)

chainl1 :: Parser t -> Parser (t -> t -> t) -> Parser t
p `chainl1` op = do
                    x <- p
                    rest x
                 where rest x = (do
                                    f <- op
                                    y <- p
                                    rest (f x y)
                                ) <|> return x

digit :: Parser Int
digit = do
            d <- sat isDigit
            return (digitToInt d)

integer :: Parser Int
integer = do
              spaces
              d <- digitToInt <$> sat isDigit
              if d == 0 
                then 
                  return 0 
                else 
                  do
                    ds <- many0 digit
                    return (asInt (d:ds))
          where asInt ds = sum [d * (10^p) | (d, p) <- zip (reverse ds) [0..] ]

number :: Parser Double
number = withDecimalPt <|> withoutDecimalPt
  where
    withoutDecimalPt = fromIntegral <$> integer
    withDecimalPt = do
                      wholePart <- withoutDecimalPt
                      char '.'
                      fractionalPart <- fmap asFracPt (many0 digit)
                      return (wholePart + fractionalPart)
    asFracPt ds = sum [fromIntegral d * (10 ** (-p)) | (d, p) <- zip ds [1..]]

addop :: Parser (Double -> Double -> Double)
addop = add <|> sub
  where add = do
                symbol "+"
                return (+)
        sub = do
                symbol "-"
                return (-)

mulop :: Parser (Double -> Double -> Double)
mulop = mul <|> div
  where mul = do
                symbol "*"
                return (*)
        div = do
                symbol "/"
                return (/)

factor :: Parser Double
factor = negativeFactor <|> parensExpr <|> number
  where
    negativeFactor = do
                        symbol "-"
                        negate <$> factor
    parensExpr = do
                    symbol "("
                    x <- expr
                    symbol ")"
                    return x
                    
term :: Parser Double
term = factor `chainl1` mulop

expr :: Parser Double
expr = term `chainl1` addop

--1. TestaČi parser-ul de mai sus

--2. CreaČi un tip de date abstract pt expresii aritmetice Či modificaČi parser-ul astfel ĂŽncĂ˘t el sÄ returneze o asemenea expresie

data Expr
    = ENum Double
    | EPlu Expr Expr
    | EMin Expr Expr
    | EMul Expr Expr
    | EDiv Expr Expr
    | EminuU Expr
    deriving Show

enum :: Parser Expr
enum = ENum <$> number
-- parse enum "3.14" => [(ENum 3.14, "")]

efactor :: Parser Expr
efactor = negativeExpr <|> parensExpr <|> enum where
    negativeExpr = do
        symbol "-"
        x <- efactor
        return (EminuU x)

    parensExpr = do
        symbol "("
        x <- efactor
        symbol ")"
        return x

-- parse efactor "-1" => [(EMinuU (ENum 1.0), "")]
-- parse efactor "(-1)" => [(EMinuU (ENum 1.0), "")]
-- parse efactor "10" -> [(ENum 10.0, "")]

eaddop :: Parser (Expr -> Expr -> Expr)
eaddop = eadd <|> esub where
    eadd = do
        symbol "+"
        return EPlu
    esub = do
        symbol "-"
        return EMin

emulop :: Parser (Expr -> Expr -> Expr)
emulop = emul <|> ediv where
    emul = do
        symbol "*"
        return EMul
    ediv = do
        symbol "/"
        return EDiv

eterm :: Parser Expr
eterm = efactor `chainl1` emulop
-- parse eterm "1 * (-2) * 3" => [(EMul (EMul (ENum 1.0) (EminuU (ENum 2.0))) (ENum 3.0), "")]

eexpr :: Parser Expr
eexpr = eterm `chainl1` eaddop
-- parse eexpr "1 * (-2) + 3.2" => [(EPlu (EMul (ENum 1.0) (EminuU (ENum 2.0))) (ENum 3.2), "")]
