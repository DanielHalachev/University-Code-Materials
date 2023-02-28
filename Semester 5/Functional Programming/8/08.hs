-- cover all cases!
{-# OPTIONS_GHC -fwarn-incomplete-patterns #-}
-- warn about incomplete patterns v2
{-# OPTIONS_GHC -fwarn-incomplete-uni-patterns #-}
-- write all your toplevel signatures!
{-# OPTIONS_GHC -fwarn-missing-signatures #-}
-- use all your pattern matches!
{-# OPTIONS_GHC -fwarn-unused-matches #-}

import Language.Haskell.TH (Lit (IntegerL))
import Text.Parsec.Token (GenLanguageDef (reservedNames))

saySign :: (Ord a, Num a) => a -> String
saySign number
  | number < 0 = "Negative"
  | number == 0 = "Zero"
  | otherwise = "Positive"

-- 2
countRoots :: Integer -> Integer -> Integer -> String
countRoots a b c
  | a == 0 = "Not quadratic"
  | discr == 0 = "One root"
  | otherwise = "Two roots"
  where
    discr = (b * b) - (4 * a * c)

-- 3
sayRoots :: Integer -> Integer -> Integer -> String
sayRoots a b c
  | b * b - 4 * a * c < 0 = "Not quadratic"
  | a * c < 0 = "Positive and Negative"
  | (a * c > 0) && (b * a < 0) = "Positive"
  | otherwise = "Negative"

-- 4
cylinderVolume :: Floating a => a -> a -> a
cylinderVolume r h = pi * r * r * h

-- 5
useless :: (Eq p, Num p) => p -> p -> p -> p -> p
useless a b c d
  | a * b * c * d == 0 = 1
  | otherwise = a + b + c + d

--6
power :: (Num b, Integral exp, Fractional exp) => b -> exp -> b
power base exp
  | exp == 0 = 1
  | even exp = power base (exp / 2) * power base (exp / 2)
  | otherwise = base * power base (exp / 2) * power base (exp / 2)

-- 7
modulus :: Floating a => a -> a -> a
modulus r im = sqrt (r ^ 2 + im ^ 2)

-- 8
type Complex = (Float, Float)

complAdd :: Complex -> Complex -> Complex
complAdd c1 c2 = (fst c1 + fst c2, snd c1 + snd c2)

-- data Complex = Complex Float Float

-- complAdd :: Complex -> Complex -> Complex
-- complAdd (Complex r1 i1) (Complex r2 i2) = Complex (r1 + r2) (i1 + i2)

-- complSub :: Complex -> Complex -> Complex
-- complSub (Complex r1 i1) (Complex r2 i2) = Complex (r1 - r2) (i1 - i2)

-- complMul :: Complex -> Complex -> Complex
-- complMul (Complex r1 i1) (Complex r2 i2) = Complex (r1 * r2 - i1 * i2) (r1 * i2 + r2 * i1)

-- 9
data Point = Point Float Float

distance :: Point -> Point -> Float
distance (Point x1 y1) (Point x2 y2) = sqrt ((x2 - x1) ^ 2 + (y2 - y1) ^ 2)

-- 10
replicate' :: Int -> a -> [a]
replicate' times obj = [obj | _ <- [1 .. times]]

-- myReplicate times obj = take times (repeat obj)

-- 11
take' :: Integer -> [a] -> [a]
take' n l
  | n == 0 = []
  | null l = []
  | otherwise = head l : take' (n - 1) (tail l)

map' :: (t -> a) -> [t] -> [a]
map' f l = [f x | x <- l]

filter' :: (a -> Bool) -> [a] -> [a]
filter' pred l = [x | x <- l, pred x]

countDelimiters :: Integral a => a -> Int
countDelimiters number = length [delimiter | delimiter <- [1 .. number], mod number delimiter == 0]

isPrime :: Integral a => a -> Bool
isPrime number = countDelimiters number == 2

descartes :: [a] -> [b] -> [(a, b)]
descartes l1 l2 = [(x, y) | x <- l1, y <- l2]

-- 13
primes :: [Integer]
primes = [num | num <- [1 ..], isPrime num]

-- 14

eratosten :: [Integer]
eratosten =
  helper [2 ..]
  where
    helper :: [Integer] -> [Integer]
    helper [] = []
    helper (x : xs) = x : helper (filter (\num -> mod num x > 0) xs)

-- 15
flip' :: (t1 -> t2 -> t3) -> t2 -> t1 -> t3
flip' f x y = f y x

-- 16
-- takeWhile' :: (a -> Bool) -> [a] -> [a]
-- takeWhile' pred l = fst (break (not . pred) l)

takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' pred l =
  helper pred l
  where
    helper _ [] = []
    helper pred (x : xs) = if pred x then x : helper pred xs else []

-- 17
compress :: (Eq a, Num b) => [a] -> [(a, b)]
compress [] = []
compress (x : xs) =
  reverse (helper xs x 1 [])
  where
    helper [] a t res = (a, t) : res
    helper (x : xs) last times res =
      if x == last
        then helper xs x (times + 1) res
        else helper xs x 1 ((last, times) : res)

-- 18
maxRepeated :: (Ord a, Ord b, Num a) => [b] -> a
maxRepeated l = fst (maximum (map (\p -> (snd p, fst p)) (compress l)))

-- 19
makeSet :: Eq a => [a] -> [a]
makeSet l = helper l []
  where
    helper [] res = res
    helper (x : xs) res
      | x `elem` res = helper xs res
      | otherwise = helper xs (x : res)

makeSet' :: (Eq a) => [a] -> [a]
makeSet' = foldl (\res x -> if x `elem` res then res else x : res) []

sort :: (Ord a) => [a] -> [a]
sort [] = []
sort (x : xs) =
  (sort [a | a <- xs, a < x])
    ++ [x]
    ++ sort [b | b <- xs, b >= x]

-- 20
histogram :: (Num b, Ord a) => [a] -> [(a, b)]
histogram [] = []
histogram l = helper sl (head sl) 1 []
  where
    sl = sort l
    helper [] last times res = (last, times) : res
    helper (x : xs) last times res =
      if x == last
        then helper xs x (times + 1) res
        else helper xs x 1 ((last, times) : res)

-- 21
maxDistance :: (Ord p, Floating p) => [(p, p)] -> p
maxDistance [] = 0
maxDistance lpoints = maximum ([distance x y | x <- lpoints, y <- lpoints, x /= y])
  where
    distance (x1, y1) (x2, y2) = sqrt (((x2 - x1) ^ 2) + ((y2 - y1) ^ 2))

-- 22
compositions :: (t -> t) -> t -> [t]
compositions f x = f x : map f (compositions f x)
