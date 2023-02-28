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
-- length [] = 0
-- length' (x:xs) = 1 + length' xs
length' :: [a] -> Int
length' l =
  if null l
    then 0
    else 1 + length (tail l)

-- 2
product' :: Num a => [a] -> a
product' [] = error "Empty list"
product' (x : xs) = x * product' xs

-- product' l =
--     if null l
--         then error "Empty list"
--         else head l * product (tail l)

-- 3
maximum' :: Ord a => [a] -> a
maximum' [] = error "Empty list"
maximum' [x] = x
maximum' (x : xs) = if x > mx then x else mx
  where
    mx = maximum' xs

-- 4
-- elem' :: Eq t => t -> [t] -> Bool
-- elem' x [] = False
-- elem' x (y:ys) = (x==y) || elem' x ys

elem' :: (Foldable t, Eq a) => a -> t a -> Bool
elem' x = foldr (\y -> (||) (x == y)) False

-- 5
sumDivisors :: Integral a => a -> a
sumDivisors n = sum [x | x <- [1 .. n], n `mod` x == 0]

-- 6
rotate :: [a] -> Int -> [a]
rotate l i = drop i l ++ take i l
