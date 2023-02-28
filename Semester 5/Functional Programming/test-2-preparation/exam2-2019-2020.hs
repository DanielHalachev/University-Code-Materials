-- 2
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Redundant bracket" #-}
forestFire :: [Integer]
forestFire = map f [0 ..]
  where
    f 0 = 1
    f n = findMinNotIn [2 * f (n - k) - f (n - 2 * k) | k <- [1 .. (n / 2)]]
    findMinNotIn l = head [x | x <- [1 ..], x `notElem` l]

-- 3
sort :: Ord a => [a] -> [a]
sort [] = []
sort (x : xs) = (sort [a | a <- xs, a > x]) ++ [x] ++ sort ([b | b <- xs, b <= x])

makeSet :: Eq a => [a] -> [a]
makeSet [] = []
makeSet (x : xs) =
  if x `elem` xs
    then makeSet xs
    else x : makeSet xs

-- ("Store", "Category", Price = 1.20)
pcs :: [(String, String, Double)]
pcs =
  [ ("Ikea", "Furniture", 150.5),
    ("Billa", "Food", 24.4),
    ("Fantastiko", "Food", 5.0),
    ("Mebeli Videnov", "Furniture", 400.0),
    ("Billa", "Food", 13.3),
    ("Lidl", "Food", 10.5),
    ("Medea", "Pharmaceuticals", 40.0),
    ("Ikea", "Furniture", 50.0)
  ]

calculatePurchases :: [(String, String, Double)] -> [(String, Double, String)]
calculatePurchases purchases = map (\category -> (category, (sum (map (\(_, _, p) -> p) (filterByCategory category))), mostExpensiveStore category)) categories
  where
    categories = makeSet (map (\(_, category, _) -> category) purchases)
    filterByCategory category = filter (\(_, cat, _) -> cat == category) purchases
    getStores category = map (\(store, _, _) -> store) (filterByCategory category)
    mostExpensiveStore category = snd (minimum (map (\store -> (sum (map (\(_, _, p) -> p) (filter (\(s, c, p) -> s == store && c == category) purchases)), store)) (getStores category)))

-- 2
flatten :: [[a]] -> [a]
flatten [] = []
flatten (x : xs) = x ++ flatten xs

stern :: [Integer]
stern = 1 : start [1, 1]
  where
    start [] = []
    start [x] = [x]
    start (x:y:ys) = init result ++ start result
      where
        -- result = flatten (map (\i -> head (drop (i - 1) l) : [sum (take 2 (drop (i - 1) l))]) [1 .. ((length l) - 1)]) ++ [1]
        result = x : x + y : start (y : ys)