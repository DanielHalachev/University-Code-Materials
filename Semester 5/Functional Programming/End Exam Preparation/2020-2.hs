import Data.Maybe

type Name = String

data Database = Database {databaseName :: Name, size :: Integer}

data Server = Server {serverName :: Name, capacity :: Integer, databases :: [Database]}

sort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
sort f [] = []
sort f (x : xs) = sort f [a | a <- xs, f a < f x] ++ [x] ++ sort f [b | b <- xs, f x <= f b]

reverseSort :: Ord a1 => (a2 -> a1) -> [a2] -> [a2]
reverseSort f [] = []
reverseSort f (x : xs) = sort f [a | a <- xs, f a > f x] ++ [x] ++ sort f [b | b <- xs, f x >= f b]

mostUtilized :: [Server] -> Server
mostUtilized [] = error "No servers to compare"
mostUtilized l = head $ reverseSort coefficient l
  where
    coefficient (Server _ capacity databases) = fromIntegral (sum (map size databases)) / fromIntegral capacity

addNew :: Server -> [Server] -> [Server]
addNew srv = helper srv []
  where
    helper :: Server -> [Server] -> [Server] -> [Server]
    helper server processed [] = server : processed
    helper server@(Server n c dbs) processed (x : xs) = case biggestDB of
      Nothing -> helper server (x : processed) xs
      (Just db) ->
        if c >= sz
          then helper (Server n (c - sz) (db : dbs)) (newX : processed) xs
          else helper (Server n c dbs) (x : processed) xs
        where
          sz = size db
          newX = Server (serverName x) (capacity x + sz) (tail orderedDBs)
      where
        orderedDBs = reverseSort size (databases x)
        biggestDB = listToMaybe orderedDBs
        orderedDBs :: [Database]
        biggestDB :: Maybe Database

-- 2
bins :: (Integer -> Integer -> Integer) -> Integer -> [Integer]
bins f arg = arg : f arg arg : concatMap (\n -> [f n (f n n), f (f n n) n, f (f n n) (f n n)]) (bins f arg)

f x y = x^2+3*y

-- 3
data Tree = Leaf {root::Integer}| Tree{root::Integer, children::[Tree]}
maxSuccessors x (Leaf root) = root
maxSuccessors x (Tree root children)
   | x==root = 1
    