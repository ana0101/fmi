import Data.List (nub)
import Data.Maybe (fromJust)

type Nume = String
data Prop
	= Var Nume
	| F
	| T
	| Not Prop
	| Prop :|: Prop
	| Prop :&: Prop
	| Prop :->: Prop
	| Prop :<->: Prop
	deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

-- 1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: ((Not (Var "P")) :&: (Not (Var "Q")))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))


-- 2
instance Show Prop where
  	show (Var n) = n
	show (Not p) = "(~" ++ show p ++ ")"
	show (p1 :|: p2) = "(" ++ show p1 ++ "|" ++ show p2 ++ ")"
	show (p1 :&: p2) = "(" ++ show p1 ++ "&" ++ show p2 ++ ")"
	show (p1 :->: p2) = "(" ++ show p1 ++ "->" ++ show p2 ++ ")"
	show (p1 :<->: p2) = "(" ++ show p1 ++ "<->" ++ show p2 ++ ")"
 
test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"


type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a, b)] -> b
impureLookup a = fromJust . lookup a

-- 3
eval :: Prop -> Env -> Bool
eval (Var n) env = impureLookup n env
eval (Not p) env = not(eval p env)
eval (p1 :|: p2) env = (eval p1 env) || (eval p2 env)
eval (p1 :&: p2) env = (eval p1 env) && (eval p2 env)
eval (p1 :->: p2) env = (not (eval p1 env)) || (eval p2 env)
eval (p1 :<->: p2) env = (eval (p1 :->: p2) env) && (eval (p2 :->: p1) env)
 
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True


-- 4
variabile :: Prop -> [Nume]
variabile p = nub(variabile2 p)

variabile2 :: Prop -> [Nume]
variabile2 (Var n) = [n]
variabile2 (Not p) = variabile p
variabile2 (p1 :|: p2) = variabile p1 ++ variabile p2
variabile2 (p1 :&: p2) = variabile p1 ++ variabile p2
variabile2 (p1 :->: p2) = variabile p1 ++ variabile p2
variabile2 (p1 :<->: p2) = variabile p1 ++ variabile p2
 
test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]


-- 5
envs :: [Nume] -> [Env]
envs [] = [[]] 
envs (n : ns) = concatMap (\val -> map ((n, val):) (envs ns)) [False, True]
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]


-- 6
satisfiabila :: Prop -> Bool
satisfiabila p = satisfiabila2 p lenv
				 where lenv = envs (variabile p)

satisfiabila2 p [] = True
satisfiabila2 p (env : lenv) = (eval p env) || (satisfiabila2 p lenv)
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False


-- 7
valida :: Prop -> Bool
valida p = not(satisfiabila (Not p))

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True


-- 10
echivalenta :: Prop -> Prop -> Bool
echivalenta p1 p2 = echivalenta2 p1 p2 lenv
					where lenv = envs (nub(variabile p1 ++ variabile p2))

echivalenta2 p1 p2 [] = True
echivalenta2 p1 p2 (env : lenv) = ((eval p1 env) == (eval p2 env)) && (echivalenta2 p1 p2 lenv)
 
test_echivalenta1 = True == (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 = False == (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 = True == (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))
