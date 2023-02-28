-- cover all cases!
{-# OPTIONS_GHC -fwarn-incomplete-patterns #-}
-- warn about incomplete patterns v2
{-# OPTIONS_GHC -fwarn-incomplete-uni-patterns #-}
-- write all your toplevel signatures!
{-# OPTIONS_GHC -fwarn-missing-signatures #-}
-- use all your pattern matches!
{-# OPTIONS_GHC -fwarn-unused-matches #-}

-- inf 1
-- 1
-- length' :: [a] -> Int
-- length :: Num p => [a] -> p
-- length [] = 0
-- length' (_ : xs) = 1 + length' xs

-- 2
exists' :: (t -> Bool) -> [t] -> Bool
exists' _ [] = False
exists' p (x : xs) = p x || exists' p xs

-- 3
forall' :: (t -> Bool) -> [t] -> Bool
forall' _ [] = True
forall' p (x : xs) = p x && forall' p xs

-- 4
member' :: (Eq t) => t -> [t] -> Bool
member' _ [] = False
member' x (y : ys) = (x == y) || member' x ys

-- 5
map' :: (t -> a) -> [t] -> [a]
map' _ [] = []
map' f (x : xs) = f x : map' f xs

-- 6
filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (x : xs)
  | p x = x : filter' p xs
  | otherwise = filter' p xs

-- 7
push :: a -> [a] -> [a]
push x l = l ++ [x]

-- 8
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x : xs) = reverse' xs ++ [x]

--9
insert :: a -> Int -> [a] -> [a]
insert x n l = take (n - 1) l ++ [x] ++ drop (n - 1) l

-- 10
sum' :: (Num a) => [a] -> a
sum' = foldr (+) 0


