{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Redundant bracket" #-}
import Language.Haskell.TH (Lit (IntegerL))

type Name = String

data Database = Database {databaseName :: Name, size :: Integer}

data Server = Server {serverName :: Name, capacity :: Integer, databases :: [Database]}

sort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
sort f [] = []
sort f (x : xs) = sort f [a | a <- xs, f a < f x] ++ [x] ++ sort f [b | b <- xs, f x <= f b]

reverseSort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
reverseSort f [] = []
reverseSort f (x : xs) = sort f [a | a <- xs, f a > f x] ++ [x] ++ sort f [b | b <- xs, f x >= f b]

hasLargestDB :: [Server] -> Server
hasLargestDB [] = error "No such server"
hasLargestDB l = head $ sort ratio l
  where
    ratio :: Server -> Double
    ratio (Server n c dbs) = fromIntegral (biggestDBSize dbs) / fromIntegral c
    biggestDBSize :: [Database] -> Integer
    biggestDBSize [] = 0
    biggestDBSize dbs = maximum (map size dbs)

instance Eq Database where
  (Database name1 size1) == (Database name2 size2) = name1 == name2 && size1 == size2

cleanDuplicates l = helper [] (reverseSort freeSpace l)
  where
    helper :: [Server] -> [Server] -> [Server]
    helper processed [] = filter (\s -> freeSpace s > 0) processed
    helper processed (x : xs) = helper (x : processed) newXS
      where
        newXS :: [Server]
        newXS = map (purgeDBs (databases x)) xs
        purgeDBs dbs (Server name capacity sdbs) = Server name (capacity - sum (map size cleanedDBs)) cleanedDBs
          where
            cleanedDBs = filter (`notElem` dbs) sdbs
    freeSpace :: Server -> Integer
    freeSpace (Server n c dbs) = c - sum (map size dbs)

-- 2
-- nums :: (a -> a) -> [a] -> [a]
-- nums f l = l ++ map f (nums f l)
funcs :: (Integer -> Integer) -> [(Integer -> Integer)]
funcs f = id : map (f .) (funcs f)

nums :: (Integer -> Integer) -> [Integer] -> [Integer]
nums f l = [n | n <- [1 ..], n `elem` (res n)]
  where
    res x = concatMap (takeWhile (<= x) . (\num -> (map (\fnt -> fnt num) funcs))) l
    funcs :: [Integer -> Integer]
    funcs = id : map (f .) (funcs)

f x = x ^ 2 + 1