-- cover all cases!
{-# OPTIONS_GHC -fwarn-incomplete-patterns #-}
-- warn about incomplete patterns v2
{-# OPTIONS_GHC -fwarn-incomplete-uni-patterns #-}
-- write all your toplevel signatures!
{-# OPTIONS_GHC -fwarn-missing-signatures #-}
-- use all your pattern matches!
{-# OPTIONS_GHC -fwarn-unused-matches #-}

-- inf 2

-- 1
zipWith' :: (t1 -> t2 -> a) -> [t1] -> [t2] -> [a]
zipWith' f l1 l2 = [f x y | x <- l1, y <- l2]

-- 2
quicksort :: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x : xs) = [a | a <- xs, a < x] ++ [x] ++ [b | b <- xs, b >= x]

-- 3
subsets :: [a] -> [[a]]
subsets [] = [[]]
subsets (x : xs) = subsets xs ++ map (x :) (subsets xs)

-- 4
from :: Num t => t -> [t]
from start = start : from (start + 1)

-- 5
pythagoreanTriples :: (Num c, Eq c, Enum c) => c -> [(c, c, c)]
pythagoreanTriples to = [(x, y, z) | x <- [1 .. to], y <- [x .. to], z <- [y .. to], x ^ 2 + y ^ 2 == z ^ 2]

-- 6
factorials :: [Integer]
factorials = map factorial [0 ..]
  where
    factorial 0 = 1
    factorial n = n * factorial (n - 1)

-- 7
sumLast :: Num a => a -> Int -> [a]
sumLast k n = k : helper n [k]
  where
    helper n lst = last : helper n newlst
      where
        last = sum (take n lst)
        newlst = last : lst

-- 8
histogram :: (Eq a, Num b) => [a] -> [(a, b)]
histogram [] = []
histogram (x : xs) = helper xs x 1 []
  where
    helper [] last times res = (last, times) : res
    helper (x : xs) last times res =
      if x == last
        then helper xs x (times + 1) res
        else helper xs x 1 ((last, times) : res)

sort :: Ord a => [a] -> [a]
sort [] = []
sort (x : xs) = sort [a | a <- xs, a < x] ++ [x] ++ sort [b | b <- xs, b >= x]

specialSort :: (Ord a) => [[a]] -> [[a]]
specialSort ll = map snd (sort (map (\l -> (mostCommon (sort l), l)) ll))
  where
    mostCommon :: (Eq a, Ord a) => [a] -> a
    mostCommon sl =
      fst
        ( foldl1
            ( \(a1, n1) (a2, n2) ->
                ( if n1 > n2
                    then (a1, n1)
                    else
                      if n1 < n2
                        then (a2, n2)
                        else
                          if a1 > a2
                            then (a1, n1)
                            else (a2, n2)
                )
            )
            (histogram sl)
        )
