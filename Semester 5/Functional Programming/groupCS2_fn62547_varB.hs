{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use uncurry" #-}
{-# HLINT ignore "Redundant map" #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

-- 1

tournament :: [(String, String, Integer, Integer)]
tournament = [("A", "B", 1, 0), ("B", "C", 4, 1), ("C", "B", 3, 4), ("B", "A", 1, 2), ("A", "C", 0, 1)]

flatten :: [[a]] -> [a]
flatten = concat

makeSet :: Eq a => [a] -> [a]
makeSet [] = []
makeSet (x : xs)
  | x `elem` xs = makeSet xs
  | otherwise = x : makeSet xs

maximumBy' :: Ord a1 => (a2 -> a1) -> [a2] -> a2
maximumBy' _ [] = error "Empty list"
maximumBy' _ [x] = x
maximumBy' f (x : xs)
  | f x > f mx = x
  | otherwise = mx
  where
    mx = maximumBy' f xs

minimumBy' :: Ord a1 => (a2 -> a1) -> [a2] -> a2
minimumBy' _ [] = error "Empty list"
minimumBy' _ [x] = x
minimumBy' f (x : xs)
  | f x < f mx = x
  | otherwise = mx
  where
    mx = minimumBy' f xs


maxPointsMinGoal results = fst (minimumBy' snd goalDiffsWinningTeams)
  where
    goalDiffsWinningTeams = map (\team -> (team, sum (map (calculateGoalsDiff team) results))) winningTeams
    winningTeams = map fst (filter (\(t, p) -> p == maxPoints) totalPoints)
    maxPoints = snd (maximumBy' snd totalPoints)
    totalPoints = map (\team -> (team, sum (map snd (filter (\(t, _) -> team == t) points)))) teams
    points = flatten (map calculateOutcome results)
    teams = makeSet (flatten (map (\(team1, team2, _, _) -> [team1, team2]) results))
    calculateOutcome (team1, team2, goals1, goals2)
      | goals1 > goals2 = [(team1, 3), (team2, 0)]
      | goals1 < goals2 = [(team1, 0), (team2, 3)]
      | otherwise = [(team1, 1), (team2, 1)]
    calculateGoalsDiff team (team1, team2, goals1, goals2)
      | team == team1 = goals1 - goals2
      | team == team2 = goals2 - goals1
      | otherwise = 0

-- TODO
sort :: Ord a => [a] -> [a]
sort [] = []
sort (x:xs) = (sort [a | a <- xs, a<x])++[x]++sort [b | b <-xs, b >= x]

exceedSelf results = fst (foldr1 (\(a,b) (c,d) -> if b==c then (a,d) else (a,b)) uniqieExceeds)
  where
    uniqieExceeds = sort (makeSet (filter (\(t1, t2) -> t1 /= t2) (map makeExceeding results)))
    teams = makeSet (flatten (map (\(team1, team2, _, _) -> [team1, team2]) results))
    makeExceeding (team1, team2, goals1, goals2)
      | goals1 > goals2 = (team1, team2)
      | goals2 > goals1 = (team2, team1)
      | otherwise = (team1, team1)

-- 2

prime :: Integral a => a -> Bool
prime n = sum [1 | x <- [1 .. n], n `mod` x == 0] <= 2

tr = Node (< 2) (Node odd (Node (> 6) Empty Empty) (Node prime Empty Empty)) (Node (> 0) Empty Empty)
tr1 = Node (< 2) Empty Empty

data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Show)

trace :: t -> Tree (t -> Bool) -> [String]
trace _ Empty = []
trace arg (Node f l r)
    | not (f arg) = "l":trace arg l
    | f arg  = "r":trace arg r

sameTrace tree numbers@(x:xs) = any (\(trace, times) -> times >1) (map (\trace -> (trace, count trace traces)) uniqueTraces)
    where
        traces = map (`trace` tree) numbers
        uniqueTraces = makeSet traces
        count _ [] = 0
        count target (x:xs) = if target==x then 1 + count target xs else count target xs

-- 3
-- TODO
combStreams [a:as:aas, b:bs:bbs, c:cs:ccs] = helper
    where
        helper = [(x, y) |
           x <- [a, as, b, bs, c, cs],
           y <- [a, as, b, bs, c, cs],
           x /= y]