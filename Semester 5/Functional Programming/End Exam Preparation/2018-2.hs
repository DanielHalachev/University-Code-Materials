{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use find" #-}
import Data.List ( group, insert )
import Data.Maybe ( fromMaybe, listToMaybe )

-- generatePowers k l = [n | n <- [1 ..], n `elem` res n]
--   where
--     first n = takeWhile (<= n) (map (k ^) [0 ..])
--     second n = takeWhile (<= n) (map (l ^) [0 ..])
--     res n = liftM2 (*) (first n) (second n)

generatePowers k l = map head . group . go $ [[k ^ x * l ^ y | x <- [0 ..]] | y <- [0 ..]]
  where
    go ((x : xs) : xss) = x : go (insert xs xss)

--3
aProg :: [[Integer]] -> [Integer -> Integer] -> [Integer]
aProg lln lf = fromMaybe [] result
  where
    result = listToMaybe $ filter (isAProg . makeProg lf) products
    makeProg :: [Integer -> Integer] -> [Integer] -> [Integer]
    makeProg = zipWith (\f n -> f n)
    products = cartProd lln

cartProd :: [[Integer]] -> [[Integer]]
cartProd [] = [[]]
cartProd (xs : xss) = [x : y | x <- xs, y <- cartProd xss]

isAProg :: [Integer] -> Bool
isAProg [] = True
isAProg [x] = True
isAProg [x, xs] = True
isAProg (x : xs : xss : xsss) = (x + xss == 2 * xs) && isAProg (xs : xss : xsss)
