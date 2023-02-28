{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Eta reduce" #-}
isNPerm :: (Num p, Enum p, Eq p) => p -> (p -> p) -> Bool
isNPerm n f = isInjection && isBijection
  where
    interval = [0 .. (n - 1)]
    isInjection = all (\x -> f x `elem` interval) interval
    isBijection = all (\x -> any (\y -> f y == x) interval) interval

sort :: Ord a => [a] -> [a]
sort [] = []
sort (x : xs) = (sort [a | a <- xs, a >= x]) ++ [x] ++ sort [b | b <- xs, b < x]

maxCycle :: Int -> (Int -> Int) -> [Int]
maxCycle n f = snd (minimum (map (\l -> (length l, l)) (map (\a -> unique (take n (iterate f a))) interval)))
  where
    interval = [0 .. (n - 1)]
    unique [] = []
    unique (x : xs) = if x `elem` xs then unique xs else x : unique xs

-- 2
movingAverage :: [Int] -> Int -> [Float]
movingAverage l n = average (take n l) : movingAverage (tail l) n
  where
    average :: [Int] -> Float
    average l = fromIntegral (sum l) / fromIntegral (length l)

allAverages :: [Int] -> [[Float]]
allAverages l = map (movingAverage l) [2 ..]

-- 3
flatten :: [[a]] -> [a]
flatten xs = foldr (++) [] xs

allObjects :: Eq a => [(a, [a])] -> [a]
allObjects inventory = filter (`notElem` boxes) contents
  where
    boxes = map fst inventory
    contents = flatten (map snd inventory)

cleanUp :: [(String, [String])] -> [(String, [String])]
cleanUp inventory =
  if null emptyBoxes
    then inventory
    else cleanUp (map (\(id, content) -> (id, cleanContent content)) fullBoxes)
  where
    emptyBoxes = filter (\(id, content) -> null content) inventory
    fullBoxes = filter (\(id, content) -> not (null content)) inventory
    cleanContent content = filter (\label -> label `notElem` map fst emptyBoxes) content

inv :: [(String, [String])]
inv =
  [ ("docs", ["ids", "invoices"]),
    ("ids", ["passport"]),
    ("invoices", []),
    ("memes", []),
    ("family", ["new year", "birthday"]),
    ("funny", ["memes"]),
    ("pics", ["family", "funny"])
  ]
