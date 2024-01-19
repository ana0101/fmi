import Data.Char(toUpper)

data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

-- a
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala s i)
    | (elem s ["Tarocco", "Moro", "Sanguinello"]) = True
    | (otherwise) = False
ePortocalaDeSicilia(a) = False

-- test_ePortocalaDeSicilia1 =
--     ePortocalaDeSicilia (Portocala "Moro" 12) == True
-- test_ePortocalaDeSicilia2 =
--     ePortocalaDeSicilia (Mar "Ionatan" True) == False

-- b
felii :: Fruct -> Int
felii (Portocala s i) = i

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (h:t)
    | (ePortocalaDeSicilia h == True) = felii h + s
    | otherwise = s
    where s = nrFeliiSicilia t

-- test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

-- c
areViermi :: Fruct -> Bool
areViermi (Mar s b) = b
areViermi (a) = False

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (h:t)
    | (areViermi h ==  True) = nr + 1
    | otherwise = nr
    where nr = nrMereViermi t

-- test_nrMereViermi = nrMereViermi listaFructe == 2


-- 2
type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

-- a
vorbeste :: Animal -> String
vorbeste a = case a of
    Pisica n -> "Meow!"
    Caine n r -> "Woof!"

-- b
rasa :: Animal -> Maybe String
rasa a = case a of
    Pisica n -> Nothing
    Caine n r -> Just r


-- 3
data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

-- a
suma :: Linie -> Int
suma (L l) = foldr (+) 0 l

sumaN :: Linie -> Int -> Bool
sumaN l n 
    | (suma l == n) = True
    | otherwise = False

verifica :: Matrice -> Int -> Bool
verifica (M m) n = foldr (&&) True (map (\linie -> sumaN linie n) m)

-- test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
-- test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True

-- b
lungime :: Linie -> Int
lungime (L []) = 0
lungime (L (h:t)) = l + 1
                    where l = lungime (L t)

lungimeN :: Linie -> Int -> Bool
lungimeN (L l) n
    | (lungime (L l) == n) = True
    | otherwise = False

doarPoz :: Linie -> Bool
doarPoz (L l) = foldr (&&) True (map (\x -> if x > 0 then True else False) l)

verif :: Linie -> Int -> Bool
verif (L l) n = 
    if lungimeN (L l) n == True then
        if doarPoz (L l) == True then True
        else False
    else True

doarPozN :: Matrice -> Int -> Bool
doarPozN (M m) n = foldr (&&) True (map (\l -> verif l n) m)

-- testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True
-- testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False

-- c
primaLinie :: Matrice -> Linie
primaLinie (M (h:t)) = h 

corect :: Matrice -> Bool
corect (M m) = foldr (&&) True (map (\l -> lungimeN l (lungime (primaLinie (M m)))) m)

-- testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
-- testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True

f :: String -> String
f s = map toUpper s