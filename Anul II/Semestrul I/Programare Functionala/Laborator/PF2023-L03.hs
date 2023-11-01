import Data.Char
import Data.List
import Data.Ord

-- ex 1
nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h:t)
    | (reverse h == h) = suma + nrVocale2 h
    | otherwise = suma
    where suma = nrVocale t

-- verifica daca un caracter e vocala
vocala :: Char -> Bool
vocala c = elem c "aeiou"

-- nr de vocale intr-un string
nrVocale2 :: String -> Int
nrVocale2 [] = 0
nrVocale2 (h:t)
    | (vocala h) = suma + 1
    | otherwise = suma
    where suma = nrVocale2 t

-- ex 2
adunarePar :: Int -> [Int] -> [Int]
adunarePar n l = [if even x then x + n else x | x <- l]

semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

-- ex 3
divizori :: Int -> [Int]
divizori n = [x | x <- [1..n], n `mod` x == 0]

-- ex 4
listaDiv :: [Int] -> [[Int]]
listaDiv l = [divizori n | n <- l] 

-- ex 5
-- a
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y [] = []
inIntervalRec x y (h:t) 
    | (h >= x && h <= y) = h : lista
    | otherwise = lista
    where lista = inIntervalRec x y t

-- b
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y l = [n | n <- l, n >= x, n <= y]

-- ex 6
-- a
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t)
    | (h > 0) = nr + 1
    | otherwise = nr
    where nr = pozitiveRec t

-- b
pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x <- l, x > 0]

-- ex 7
-- a
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec [] = []
pozitiiImpareRec lista = pozitiiImpareRec2 lista 0

pozitiiImpareRec2 :: [Int] -> Int -> [Int]
pozitiiImpareRec2 [] poz = []
pozitiiImpareRec2 (h:t) poz 
    | (odd h) = poz : lista
    | otherwise = lista
    where lista = pozitiiImpareRec2 t (poz+1)

-- b
-- pozitiiImpareComp :: [Int] -> [Int]
-- pozitiiImpareComp l = [poz | poz = zip [0..] l]
-- -- pozitiiImpareRec [0,1,-3,-2,8,-1,6,1] == [1,2,5,7]

-- ex 8
-- a
multDigitsRec :: String -> Int
multDigitsRec [] = 1
multDigitsRec (h:t)
    | (isDigit h) = ((digitToInt h) * prod)
    | otherwise = prod
    where prod = multDigitsRec t

-- b
multDigitsComp :: String -> Int
multDigitsComp l = product [digitToInt x | x <- l, isDigit x]

-- ex 9
permutari :: (Eq a) => [a] -> [[a]]
permutari [] = [[]]
permutari l = [a:as | a <- l, as <- permutari (delete a l)]

-- ex 10
combinari :: (Ord a) => [a] -> Int -> [[a]]
combinari l 0 = [[]]
combinari l k = [a:as | a <- l, as <- combinari (delete2 a l) (k-1)]

delete2 :: (Ord a) => a -> [a] -> [a]
delete2 x l = [y | y <- l, y > x]

-- ex 11
aranjamente :: (Eq a) => [a] -> Int -> [[a]]
aranjamente l 0 = [[]]
aranjamente l k = [a:as | a <- l, as <- aranjamente (delete a l) (k-1)]
