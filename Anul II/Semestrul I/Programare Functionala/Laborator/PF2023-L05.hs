import Data.List

-- 1
sumaPatrImp :: [Int] -> Int
sumaPatrImp xs = foldr (+) 0 (map(^2) (filter odd xs))

-- 2
verifTrue :: [Bool] -> Bool
verifTrue xs = foldr (&&) True xs

-- 3
allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies prop xs = foldr (&&) True (map prop xs) 

-- 4
anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies prop xs = foldr (||) False (map prop xs)

-- 5
mapFoldr :: (a -> b) -> [a] -> [b]
mapFoldr f xs = foldr (\x acc -> f x : acc) [] xs

filterFoldr :: (a -> Bool) -> [a] -> [a]
filterFoldr f xs = foldr (\x acc -> if f x then x : acc else acc) [] xs

-- 6
listToInt :: [Integer]-> Integer
listToInt xs = foldl (\acc x -> acc * 10 + x) 0 xs

-- 7
-- a
rmChar :: Char -> String -> String
rmChar c cs = foldr (\x acc -> if x == c then acc else x : acc) [] cs

-- b
rmCharsRec :: String -> String -> String
rmCharsRec [] xs = xs
rmCharsRec (h:t) xs = rmCharsRec t (rmChar h xs)

-- c
rmCharsFold :: String -> String -> String
rmCharsFold ys xs = foldr (\y xs -> rmChar y xs) xs ys

-- 8
myReverse :: [Int] -> [Int]
myReverse xs = foldl (flip (:)) [] xs

-- 9
myElem :: Int -> [Int] -> Bool
myElem x lista = foldr (\y acc -> if y == x then True else acc) False lista
    
-- 10
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip lista = foldr (\p acc -> (fst p : fst acc, snd p : snd acc)) ([], []) lista

-- 11
myUnion :: [Int] -> [Int] -> [Int]
myUnion xs ys = nub(foldr (++) [] [xs, ys])

-- 12
myIntersect :: [Int] -> [Int] -> [Int]
myIntersect xs ys = foldr (\x ys -> if elem x ys then xs else (delete x xs)) xs ys
