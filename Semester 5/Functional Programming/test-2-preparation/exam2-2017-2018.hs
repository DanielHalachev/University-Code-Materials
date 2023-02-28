import Distribution.Simple.Glob (GlobSyntaxError(EmptyGlob))

maximumBy' _ [] = error "fuck"
maximumBy' _ [x] = x
maximumBy' f (x : xs)
  | f x > f maxXS = x
  | otherwise = maxXS
  where
    maxXS = maximumBy' f xs

makeSet :: (Eq a) => [a] -> [a]
makeSet [] = []
makeSet (x : xs)
  | x `elem` xs = makeSet xs
  | otherwise = x : makeSet xs

histogram :: (Num b, Eq a) => [a] -> [(a, b)]
histogram l = map (\e -> (e, count e l)) (makeSet l)
  where
    count e l = sum [1 | x <- l, x == e]

intersection :: (Foldable t, Eq a) => [a] -> t a -> [a]
intersection l1 l2 = filter (`elem` l2) l1

mostFrequent :: (Eq p, Num p) => [[p]] -> p
mostFrequent ll
  | null (mostFrequentElements ll) = 0
  | otherwise = head (mostFrequentElements ll)
  where
    mostFrequentElements [xs] = innerMostFrequent xs
    mostFrequentElements (xs : xss) = intersection (innerMostFrequent xs) (mostFrequentElements xss)
    innerMostFrequent l = map fst (filter (\(element, occurences) -> occurences == maxOccurs) elementOccurs)
        where
            maxOccurs = snd (maximumBy' snd elementOccurs)
            elementOccurs = histogram l

data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Show)

pathTo :: Eq a => a -> Tree a -> [a]
pathTo _ Empty = []
pathTo x (Node root l r)
  | x == root = [x]
  | null pathsInL =
    if null pathsinR
      then []
      else root : pathsinR
  | otherwise =
    root:pathsInL
  where
      pathsInL = pathTo x l
      pathsinR = pathTo x r

tree = Node 1 (Node 2 (Node 3 Empty Empty) (Node 4 Empty Empty)) (Node 5 Empty Empty)
