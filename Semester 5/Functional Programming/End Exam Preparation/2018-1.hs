{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use find" #-}

import Data.List (group, insert)
import Data.Maybe (fromMaybe, listToMaybe)

-- generateExponents k l = [n | n <- [1 ..], n `elem` products n]
--   where
--     xs n = takeWhile (<= n) $ map (^ k) [1 ..]
--     ys n = takeWhile (<= n) $ map (^ l) [1 ..]
--     products n = liftA2 (*) (xs n) (ys n)

generateExponents' k l = map head . group . go $ [[x ^ k * y ^ l | x <- [1 ..]] | y <- [1 ..]]
  where
    go ((x : xs) : xss) = x : go (insert xs xss)

bullshit [] = [[]]
bullshit (x : xs) = (:) <$> x <*> (bullshit xs)

-- 2
data Tree = Empty | Tree {root :: Int, left :: Tree, right :: Tree}

sameAsCode :: Tree -> Int
sameAsCode tree = helper tree [1]
  where
    helper :: Tree -> [Int] -> Int
    helper Empty _ = 0
    helper (Tree root left right) binary
      | root == toDecimal binary 0 = root
      | l /= 0 = l
      | otherwise = r
      where
        l :: Int
        l = helper left (0 : binary)
        r :: Int
        r = helper right (1 : binary)

toDecimal :: [Int] -> Int -> Int
toDecimal [] _ = 0
toDecimal (x : xs) pos = x * 2 ^ pos + toDecimal xs (pos + 1)

t = Tree 5 (Tree 3 Empty (Tree 2 Empty Empty)) (Tree 4 (Tree 6 Empty Empty) Empty)

-- 3

allEqual :: [[Integer]] -> [Integer -> Integer] -> [Integer]
allEqual lln lf = fromMaybe [] result
  where
    result = listToMaybe $ filter (allTheSame . zipWith (\f n -> f n) lf) (cartProd lln)

allTheSame :: [Integer] -> Bool
allTheSame [] = True
allTheSame [x] = True
allTheSame [x, y] = x == y
allTheSame (x : xs : xss) = (x == xs) && allTheSame (xs : xss)

cartProd :: [[a]] -> [[a]]
cartProd [] = [[]]
cartProd (xs : xss) = [x : y | x <- xs, y <- cartProd xss]

-- 4
type Name = String

data Medicine = Medicine {medicineName :: Name, ingredients :: [Ingredient]} deriving (Show)

data Ingredient = Ingredient {ingredientName :: Name, quantity :: Integer} deriving (Show)

sort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
sort _ [] = []
sort f (x : xs) = sort f [a | a <- xs, f a < f x] ++ [x] ++ sort f [b | b <- xs, f x < f b]

l :: [Medicine]
l = [Medicine "A" [Ingredient "p" 6, Ingredient "q" 9], Medicine "B" [Ingredient "p" 2, Ingredient "q" 3], Medicine "C" [Ingredient "p" 3]]

isSubstitute m1@(Medicine n1 i1) m2@(Medicine n2 i2) = (length i1 == length i2) && and (zipWith (\(Ingredient name1 q1) (Ingredient name2 q2) -> name1 == name2 && fromIntegral q1 / fromIntegral q2 == ratio) i1 i2)
  where
    sortedIng1 = sort ingredientName i1
    sortedIng2 = sort ingredientName i2
    ratio = fromIntegral (quantity (head i1)) / fromIntegral (quantity (head i2))

isLessSubstitute m1@(Medicine n1 i1) m2@(Medicine n2 i2) = (length i1 == length i2) && and (zipWith (\(Ingredient name1 q1) (Ingredient name2 q2) -> name1 == name2 && fromIntegral q1 / fromIntegral q2 == ratio && ratio >= 1) i1 i2)
  where
    sortedIng1 = sort ingredientName i1
    sortedIng2 = sort ingredientName i2
    ratio = fromIntegral (quantity (head i1)) / fromIntegral (quantity (head i2))

bestSubstitute med@(Medicine name ingredients) l = sort (ratio med) $ filter (isLessSubstitute med) l
  where
    ratio (Medicine _ i1) (Medicine _ i2) = fromIntegral (quantity (head i1)) / fromIntegral (quantity (head i2))

groupSubstitutes :: [Medicine] -> [[Medicine]]
groupSubstitutes [] = []
groupSubstitutes (x : xs) = (x : substitutes) : groupSubstitutes xs
  where
    classes :: ([Medicine], [Medicine])
    classes = divide (isSubstitute x) xs
    substitutes = fst classes
    nonSubstitutes = snd classes

divide :: (a -> Bool) -> [a] -> ([a], [a])
divide _ [] = ([], [])
divide p l = helper p l [] []
  where
    helper _ [] l1 l2 = (l1, l2)
    helper p (x : xs) l1 l2
      | p x = helper p xs (x : l1) l2
      | otherwise = helper p xs l1 (x : l2)