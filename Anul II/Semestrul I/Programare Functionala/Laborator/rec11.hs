-- class Functor f where
-- fmap :: (a -> b) -> f a -> f b

-- class Functor t where
-- fmap :: (a -> b) -> t a -> t b
--            f        t = Two a

newtype Identity a = Identity a
instance Functor Identity where
    fmap f (Identity x) = Identity (f x)

data Pair a = Pair a a
instance Functor Pair where
    fmap f (Pair x y) = Pair (f x) (f y)

data Constant a b = Constant b
instance Functor (Constant a) where
    fmap f (Constant y) = Constant (f y)

data Two a b = Two a b
instance Functor (Two a) where
    fmap f (Two x y) = Two x (f y)

data Three a b c = Three a b c
instance Functor (Three a b) where
    fmap f (Three x y z) = Three x y (f z)

data Three' a b = Three' a b b
instance Functor (Three' a) where
    fmap f (Three' x y z) = Three' x (f y) (f z)

data Four a b c d = Four a b c d
instance Functor (Four a b c) where
    fmap f (Four w x y z) = Four w x y (f z)

data Four'' a b = Four'' a a a b
instance Functor (Four'' a) where
    fmap f (Four'' w x y z) = Four'' w x y (f z)

data Quant a b = Finance | Desk a | Bloor b
instance Functor (Quant a) where
    fmap f Finance = Finance
    fmap f (Desk x) = Desk x
    fmap f (Bloor y) = Bloor (f y)

data LiftItOut f a = LiftItOut (f a)
instance (Functor f) => Functor (LiftItOut f) where
    fmap g (LiftItOut x) = LiftItOut (fmap g x)
    -- g: a -> b
    -- fmap g (LiftItOut x) = fmap g (LiftItOut (f a)) = LiftItOut (fmap g x) = 
    -- = LiftItOut (fmap g (f a)) = LiftItOut (f(g(a))) = LiftItOut (f b)

data Parappa f g a = DaWrappa (f a) (g a)
instance (Functor f, Functor g) => Functor (Parappa f g) where
    fmap h (DaWrappa x y) = DaWrappa (fmap h x) (fmap h y)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
instance (Functor g) => Functor (IgnoreOne f g a) where
    fmap h (IgnoringSomething x y) = IgnoringSomething x (fmap h y)

data Notorious g o a t = Notorious (g o) (g a) (g t)
instance (Functor g) => Functor (Notorious g o a) where
    fmap f (Notorious x y z) = Notorious x y (fmap f z)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Functor GoatLord where
    fmap f NoGoat = NoGoat
    fmap f (OneGoat x) = OneGoat (f x)
    fmap f (MoreGoats x y z) = MoreGoats (fmap f x) (fmap f y) (fmap f z)

data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Functor TalkToMe where
    fmap f Halt = Halt
    fmap f (Print s x) = Print s (f x)
    fmap f (Read g) = Read (f . g)
    