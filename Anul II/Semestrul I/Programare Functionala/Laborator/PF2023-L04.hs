-- 1
{-
[x^2 |x <- [1..10], x `rem` 3 == 2]
[(x,y) | x <- [1..5], y <- [x..(x+2)]]
[(x,y) | x <- [1..3], let k = x^2, y <- [1..k]]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']]
[[x..y] | x <- [1..5], y <- [1..5], x < y]
-}

-- 2
factori :: Int -> [Int]
factori n = [x | x <- [1..n], n `mod` x == 0]

-- 3
prim :: Int -> Bool
prim n 
    | (length (factori n) == 2) = True
    | otherwise = False

-- 4
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x == True]

-- 5
myzip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
myzip3 (h1:t1) (h2:t2) (h3:t3) 
    | (length t1 > 0 && length t2 > 0 && length t3 > 0) = (h1, h2, h3) : myzip3 t1 t2 t3
    | otherwise = [(h1, h2, h3)]

-- 6
firstEl :: [(a, b)] -> [a]
-- firstEl l = [fst(t) | t <- l]
firstEl l = map fst l 

-- 7
sumList :: [[Int]] -> [Int]
sumList l = map sum l

-- 8
prel2 :: [Int] -> [Int]
prel2 l = map (\x -> if even x then x `div` 2 else x * 2) l

-- 9
contCaract :: Char -> [[Char]] -> [[Char]]
contCaract c l = filter (elem c) l

-- 10
patrateImp :: [Int] -> [Int]
patrateImp l = map (^2) $ filter odd l

-- 11
patratePozImp :: [Int] -> [Int]
patratePozImp l = map ((^2) . fst) $ filter (odd . snd) (l `zip` [0..])
-- patratePozImp l = [x^2 | (x, poz) <- l `zip` [0..], odd poz]

-- 12
vocala :: Char -> Bool
vocala c = (if elem c "aeiouAEIOU" then True else False)

elimVocale :: [Char] -> [Char]
elimVocale l = filter vocala l

numaiVocale :: [[Char]] -> [[Char]]
numaiVocale l = map elimVocale l

-- 13
mymap :: (a -> a) -> [a] -> [a]
mymap f [] = []
mymap f (h:t) = (f h) : l
                where l = mymap f t

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter cond [] = []
myfilter cond (h:t) 
    | (cond h == True) = h : l
    | otherwise = l
    where l = myfilter cond t

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = undefined

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata = undefined