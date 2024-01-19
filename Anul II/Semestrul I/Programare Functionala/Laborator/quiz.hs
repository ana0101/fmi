-- curs 1 quiz 2
-- x = let x = 3, y = 4 in x * y
-- eroare de la virgula - trebuia ;

-- foo :: Char -> Bool -> Bool

-- [True, 'a', "FP"] - eroare pt ca in lista trebuie sa fie de acelasi tip


-- curs 2 quiz 1
-- l = 3 : 4 : 5 : 6 : []
-- l = [3..6]
-- l = 3 : 4 : 5 : [6]

-- Prelude> let xs = [1,2,3]
-- Prelude> let ys = [11,12]
-- Prelude> zip xs ys
-- [(1, 11), (2, 12)]

-- Prelude> let natural = [0..]
-- Prelude> natural !! 5
-- 5


-- curs 3 quiz 1
-- f x = x + x
-- g x = x * x
-- g . f $ 3 = 36

-- ([1,2,3] ++) [4,5,6] = [1,2,3,4,5,6]

-- reverse . take 3 [1 .. 10] - eroare
-- cum ar merge:
-- reverse . take 3 $ [1 .. 10]
-- (reverse . take 3) [1 .. 10]
-- reverse $ take 3 $ [1 .. 10]
-- reverse (take 3 [1 .. 10])
-- reverse (take 3 $ [1 .. 10])
-- reverse $ (take 3 $ [1 .. 10])
-- reverse $ (take 3 [1 .. 10])
-- nu ar merge:
-- reverse . (take 3 [1 .. 10])
-- reverse . (take 3 $ [1 .. 10])


-- curs 4 quiz 1
-- map (+1) [1,2,3,4] => [2,3,4,5]

-- map (1-) [1,2,3,4] => [0,-1,-2,-3]
-- nu ar merge map (-1) [1,2,3,4]

-- map toUpper "abcd" => "ABCD" dar trebuie import Data.Char


-- curs 4 quiz 2
-- length . filter (== 'a') "abracadabra" => eroare
-- ar merge:
-- length . filter (== 'a') $ "abracadabra"
-- (length . filter (== 'a')) "abracadabra"
-- length (filter (== 'a') "abracadabra")
-- nu ar merge:
-- length . (filter (== 'a') "abracadabra")

-- length . filter (== 'a') $ "abracadabra" => 5

-- filter (\x -> (mod x 2) == 0) [1..10] => [2,4,6,8,10]


-- curs 4 quiz 3
-- foldr (++) ["woot","WOOT","woot"] => eroare
-- lipseste valoarea initiala
-- ar fi mers:
-- foldr (++) [] ["woot","WOOT","woot"] => "wootWOOTwoot"

-- foldr (&&) True [False,True] => False

-- foldr (\ x y -> concat ["(",x,"+",y,")"]) "0"  ["1","2","3","4","5"] => "(1+(2+(3+(4+(5+0)))))"s


-- curs 5 quiz 1
-- foldl (^) 2 [1..3] => 64

-- foldr (^) 2 [1..3] => 1

-- foldr (:) [] [1..3] => [1,2,3]

-- foldl (flip (:)) [] [1..3] => [3,2,1]


-- curs 6 quiz 1
data Doggies a = Husky a | Mastiff a

-- Doggies = constructor de tip

-- Mastiff "Scooby Doo" = Doggies [Char]

-- Husky (10 :: Integer) = Doggies Integer