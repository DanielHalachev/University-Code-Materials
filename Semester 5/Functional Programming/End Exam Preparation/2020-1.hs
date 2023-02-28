import Text.XHtml (treeColors)

type Name = String

data Database = Database {databaseName :: Name, size :: Int}

data Server = Server {serverName :: Name, capacity :: Int, databases :: [Database]}

maxFree :: [Server] -> Name
maxFree l = serverName $ foldl1 compare l
  where
    compare s1@(Server _ c1 d1) s2@(Server _ c2 d2)
      | freeSpace s1 > freeSpace s2 = s1
      | otherwise = s2
    freeSpace (Server _ capacity databases) = capacity - sum (map size databases)

sort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
sort _ [] = []
sort f (x : xs) = sort f [a | a <- xs, f a < f x] ++ [x] ++ sort f [b | b <- xs, f x <= f b]

-- tryRemove :: Name -> [Server] -> [Server]
-- tryRemove name l = zipWith (\(Server name capacity dbs) db@(Database _ size) -> Server name (capacity - size) (db : dbs)) sortedServers sortedDbs
--   where
--     srv :: Server
--     srv = head $ filter (\(Server n _ _) -> name == n) l
--     otherServers :: [Server]
--     otherServers = filter (\(Server n _ _) -> name /= n) l
--     sortedDbs = sort size $ databases srv
--     sortedServers = sort freeSpace otherServers
--     freeSpace (Server _ capacity databases) = capacity - sum (map size databases)
--     checkSpaces = all (>= 0) (zipWith (-) (map freeSpace sortedServers) (map size sortedDbs))

tryRemove :: Name -> [Server] -> [Server]
tryRemove name l = zipWith (\srv dbs -> Server (serverName srv) (capacity srv - sum (map size dbs)) (dbs ++ databases srv)) sortedSrvs dbsList
  where
    srv :: Server
    srv = head $ filter (\(Server n _ _) -> name == n) l
    otherServers :: [Server]
    otherServers = filter (\(Server n _ _) -> name /= n) l
    sortedDbs = reverse $ sort size (databases srv)
    sortedSrvs = sort freeSpace otherServers
    freeSpace (Server _ capacity databases) = capacity - sum (map size databases)
    dbsList = distribute sortedDbs sortedSrvs

distribute :: [Database] -> [Server] -> [[Database]]
distribute [] _ = []
distribute dbs [] = [dbs]
distribute dbs (srv : srvs)
  | totalSize first <= freeSpace srv = first : distribute rest srvs
  | otherwise = [dbs]
  where
    (first, rest) = span (\(Database _ size) -> size <= freeSpace srv) dbs
    totalSize = sum . map size
    freeSpace (Server _ capacity databases) = capacity - sum (map size databases)

-- 2
comps :: [Int -> Int] -> [Int -> Int]
comps fl = concatMap (`helper` fl) times
  where
    times = [0 ..]
    helper :: Integer -> [Int -> Int] -> [Int -> Int]
    helper 0 fl = [id]
    helper 1 fl = fl
    helper n fl = concatMap (\f -> map (f .) (helper (n - 1) fl)) fl

f :: Num a => a -> a
f x = x

g :: Num a => a -> a
g x = x + 2

comps2 :: [Int -> Int] -> [Int -> Int]
comps2 fl = id : concatMap (\f -> map (f .) fl) (comps2 fl)

-- 3
data Tree = Leaf {root :: Integer} | Tree {root :: Integer, children :: [Tree]}

minPredecessor :: Integer -> Tree -> Integer
minPredecessor x (Leaf root) = root
minPredecessor x tree@(Tree root children)
  | root == x = root
  | length positiveChildren > 1 = root
  | length positiveChildren == 1 = min root (minPredecessor x (head positiveChildren))
  | otherwise = minInTree tree
  where
    positiveChildren = filter (hasElement x) children
    hasElement :: Integer -> Tree -> Bool
    hasElement x (Leaf root) = x == root
    hasElement x (Tree root children)
      | root == x = True
      | otherwise = any (hasElement x) children
    minInTree (Leaf root) = root
    minInTree (Tree root children) = min root (minimum (map minInTree children))

tree1 = Leaf 5

tree2 = Tree 3 [Leaf 4, Leaf 5]

tree3 = Tree 6 [Leaf 5, Leaf 7]

tree4 = Tree 4 [Leaf 5, Leaf 10]

tree5 = Tree 8 [Leaf 5, Tree 10 [Leaf 9, Leaf 11]]

tree6 = Tree 8 [Leaf 5, Tree 10 [Leaf 9, Leaf 5]]
