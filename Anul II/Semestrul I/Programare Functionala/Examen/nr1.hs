data Piece = One    -- primul jucător
            | Two   -- al doilea jucător
            | Empty -- căsuță liberă pe tablă
   deriving (Show, Eq)

data Table = Table [Piece] [Piece] [Piece]
   deriving (Show, Eq)

table1 :: Table
table1 = Table [Empty, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table2 :: Table
table2 = Table [Two, One, Two, One, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]

table3 :: Table
table3 = Table [Empty, One, Empty, Empty, Empty, Empty, Two, One]
               [Two, Empty, One, Two, One, Two, One, Two]
               [Two, Empty, One, Empty, Empty, One, Two, One]

table4 :: Table
table4 = Table [Empty, Empty, Two, One, Empty, Empty, Two, One]
               [Two, One, One, Two, One, Two, One, Two]
               [Two, Two, One, Empty, Empty, One, Two, One]


-- 1
validTable :: Table -> Bool
validTable (Table l1 l2 l3)
    | (length l1 == 8) && (length l2 == 8) && (length l3 == 8) &&
        (count One (Table l1 l2 l3) <= 9) && (count Two (Table l1 l2 l3) <= 9) = True
    | otherwise = False

count :: Piece -> Table -> Int
count p (Table l1 l2 l3) = (count2 p l1) + (count2 p l2) + (count2 p l3)

count2 :: Piece -> [Piece] -> Int
count2 p [] = 0
count2 p (h : t)
    | p == h    = 1 + (count2 p t)
    | otherwise = (count2 p t)

test11 = validTable table1 == True
test12 = validTable table2 == False
test13 = validTable table3 == True


-- 2
data Position = P (Int, Int)

instance Show Position where
    show (P (i, j)) = "careul " ++ show i ++ " pozitia " ++ show j

move :: Table -> Position -> Position -> Maybe Table
move t p1 p2
    | (not (isPositionEmpty p1 t) && (isPositionEmpty p2 t)) && (connected p1 p2) = Just (move2 t p1 p2)
    | otherwise = Nothing

isPositionEmpty :: Position -> Table -> Bool
isPositionEmpty (P (i, j)) (Table l1 l2 l3)
    | i == 1 = (l1 !! j == Empty)
    | i == 2 = (l2 !! j == Empty)
    | i == 3 = (l3 !! j == Empty)

connected :: Position -> Position -> Bool
connected (P (i1, j1)) (P (i2, j2)) = 
    if i1 == i2 then
        if (abs (j1 - j2)) == 1 || (abs (j1 - j2) == 7) then True
        else False
    else
        if (abs (i1 - i2)) == 1 then
            if (j1 `mod` 2 == 1) && (j1 == j2) then True
            else False
        else False 

move2 :: Table -> Position -> Position -> Table
move2 (Table l1 l2 l3) (P (i1, j1)) (P (i2, j2)) = case (i1, i2) of
    (1, 1) -> Table (replace (replace l1 j2 (l1 !! i1)) j1 Empty) l2 l3
    (2, 2) -> Table l1 (replace (replace l2 j2 (l2 !! i1)) j1 Empty) l3
    (3, 3) -> Table l1 l2 (replace (replace l3 j2 (l3 !! i1)) j1 Empty)
    (1, 2) -> Table (replace l1 i1 Empty) (replace l2 i2 (l1 !! i1)) l3

replace :: [Piece] -> Int -> Piece -> [Piece]
replace l pos p = take pos l ++ [p] ++ drop (pos + 1) l


test21 = move table2 (P (1,2)) (P (2,2)) == Nothing
test22 = move table1 (P (1,2)) (P (2,2)) == Nothing
test23 = move table1 (P (1,1)) (P (2,1))
       == Just (Table [Empty,Empty,Two,One,Empty,Empty,Two,One]
                      [Two,One,One,Two,One,Two,One,Two]
                      [Two,Two,One,Empty,Empty,One,Two,One])
                      -- table4
test24 = move table1 (P (3,1)) (P (2,1))
        == Just (Table [Empty,One,Two,One,Empty,Empty,Two,One]
                       [Two,Two,One,Two,One,Two,One,Two]
                       [Two,Empty,One,Empty,Empty,One,Two,One])


-- 3
data EitherWriter a = EW { getValue :: Either String (a, String) }

-- instance Monad EitherWriter where
--     return va = EW (Right (va, ""))
--     ma >>= f = EW (case getValue ma of
--                     Right (va, s) -> getValue (f va)
--                     Left s -> Left s
--                 ) 

instance Monad EitherWriter where
    return va = EW (Right (va, ""))
    (EW (Left err)) >>= _ = EW (Left err)
    (EW (Right (x, log1))) >>= f = let (EW (Right (y, log2))) = f x 
                                   in EW (Right (y, log1 ++ log2))

instance Applicative EitherWriter where
    pure = return
    mf <*> ma = do
        f <- mf
        a <- ma
        return (f a)       

instance Functor EitherWriter where              
    fmap f ma = pure f <*> ma  

-- Example function that performs division with logging
divideWithLog :: Int -> Int -> EitherWriter Int
divideWithLog x y
    | y == 0    = EW (Left "Division by zero!")
    | otherwise = EW (Right (x `div` y, "Divided " ++ show x ++ " by " ++ show y ++ ". "))

-- Test function
testEitherWriter :: EitherWriter Int
testEitherWriter = do
    result <- divideWithLog 10 0
    logMessage <- EW (Right ("Custom log message. ", ""))
    return (result)

main :: IO ()
main = do
    let result = getValue testEitherWriter
    putStrLn $ "Result: " ++ show result


playGame :: Table -> [(Position, Position)] -> [(Position, Position)] -> EitherWriter Table
playGame = undefined

printGame :: EitherWriter Table -> IO ()
printGame ewt = do
    let t = getValue ewt
    case t of
      Left v -> putStrLn v
      Right (t,v) -> putStrLn v

list1, list2 :: [(Position,Position)]
list1 = [(P(1,1),P(1,0)), (P(2,2),P(2,1)), (P(1,3),P(2,3)) ]
list2 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test41 = printGame $ playGame table1 list1 list2


{-
> test41
Jucatorul One a mutat din careul 1 pozitia 1 in  careul 1 pozitia 0
Jucatorul Two a mutat din careul 1 pozitia 6 in  careul 1 pozitia 5
Jucatorul One a mutat din careul 2 pozitia 2 in  careul 2 pozitia 1
Jucatorul Two a mutat din careul 2 pozitia 3 in  careul 3 pozitia 3
Jucatorul One a mutat din careul 1 pozitia 3 in  careul 2 pozitia 3
Jucatorul Two a mutat din careul 1 pozitia 2 in  careul 1 pozitia 3
Table finala este Table [One,Empty,Empty,Two,Empty,Two,Empty,One] [Two,One,Empty,One,One,Two,One,Two] [Two,Two,One,Two,Empty,One,Two,One]
-}
list3, list4 :: [(Position,Position)]
list3 = [(P(1,1),P(1,0)), (P(2,2),P(2,4)), (P(1,3),P(2,3)) ]
list4 = [(P(1,6),P(1,5)), (P(2,3),P(3,3)), (P(1,2),P(1,3)) ]

test42 = printGame $ playGame table1 list3 list4
-- test42
-- Jucatorul One nu poate muta din careul 2 pozitia 2 in  careul 2 pozitia 4
