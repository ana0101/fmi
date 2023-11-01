-- ex 1
poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x ^ 2 + b * x + c

-- ex 2
eeny :: Integer -> String
eeny x = if (even x == True)
            then "eeny"
        else "meeny"

-- ex 3
fizzbuzz :: Integer -> String
fizzbuzz x = if (x `mod` 3 == 0 && x `mod` 5 == 0)
                then "FizzBuzz"
            else if (x `mod` 3 == 0)
                    then "Fizz"
                else if (x `mod` 5 == 0)
                        then "Buzz"
                    else ""

fizzbuzz2 :: Integer -> String
fizzbuzz2 x
    | (x `mod` 3 == 0 && x `mod` 5 == 0) = "FizzBuzz"
    | (x `mod` 3 == 0) = "Fizz"
    | (x `mod` 5 == 0) = "Buzz"
    | otherwise = ""


fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)
    
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
    

-- ex 4
tribonacciCazuri :: Integer -> Integer
tribonacciCazuri n
    | (n == 1) = 1
    | (n == 2) = 1
    | (n == 3) = 2
    | otherwise = tribonacciCazuri(n-1) + tribonacciCazuri(n-2) + tribonacciCazuri(n-3)

tribonacciEcuational :: Integer -> Integer
tribonacciEcuational 1 = 1
tribonacciEcuational 2 = 1
tribonacciEcuational 3 = 2
tribonacciEcuational n = tribonacciEcuational(n-1) + tribonacciEcuational(n-2) + tribonacciEcuational(n-3)


-- ex 5
binomial :: Integer -> Integer -> Integer
binomial n k
    | (n == 0 || k == 0) = 1
    | otherwise = binomial (n-1) k + binomial(n-1) (k-1)


-- ex 6 a
verifL :: [Int] -> Bool
verifL list = if (even (length list) == True)
                then True
            else False

-- ex 6 b
takefinal :: [a] -> Int -> [a]
takefinal (x:xs) n
    | (length (x:xs) <= n) = x:xs
    | otherwise = takefinal xs n

-- ex 6 c
remove :: [a] -> Int -> [a]
remove list n = (take (n) list) ++ (drop (n+1) list) 

-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
 | even h    = h `div` 2 : t'
 | otherwise = t'
 where t' = semiPareRec t
 

-- ex 7 a
myReplicate :: Int -> a -> [a]
myReplicate n v
    | (n == 0) = []
    | otherwise = v : list
    where list = myReplicate (n-1) v

-- ex 7 b
sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t)
    | odd h = (suma + h)
    | otherwise = suma
    where suma = sumImp t

-- ex 7 c
totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h:t)
    | (head h == 'A') = (suma + length h)
    | otherwise = suma
    where suma = totalLen t