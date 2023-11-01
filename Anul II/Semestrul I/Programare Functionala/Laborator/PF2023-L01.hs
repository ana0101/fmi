import Data.List

myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x + x

triple :: Integer -> Integer
triple x = x + x + x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in (maxim  u z)

max4 a b c d = let
               e = max3 a b c
               in (maxim d e)  

verif :: Integer -> Integer -> Integer -> Integer -> Bool
verif a b c d = if (r >= a && r >= b && r >= c && r >= d)
                    then True
               else False  
			   where r = max4 a b c d        

suma_patr :: Integer -> Integer -> Integer
suma_patr x y = x*x + y*y

par :: Integer -> String
par x = if (mod x 2 == 0)
	        then "par"
		else "impar"

factorial :: Integer -> Integer
factorial x = product elem
			  where elem = [1..x]

mai_mare_dublu :: Integer -> Integer -> Bool
mai_mare_dublu x y = if (x > y * 2)
				        then True
					else False

max_lista :: [Integer] -> Integer
max_lista [x] = x
max_lista (x:y:xs) = if (x > y)
					 	then max_lista (x:xs)
					else max_lista (y:xs)