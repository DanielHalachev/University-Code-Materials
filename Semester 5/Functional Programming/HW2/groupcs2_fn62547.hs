-- settings
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use find" #-}

-- common
newtype Agency = Agency {customers :: [Customer]}

type Name = String

type Points = Int

type Destination = String

type Price = Double

type Duration = Int

data Status = Upcoming | Cancelled | InProgress | Finished deriving (Eq, Show)

data CancelPolicy = Flexible | Moderate | Strict deriving (Eq, Show)

data Activity = Activity {activityName :: Name, duration :: Int} deriving (Eq, Ord, Show)

data Customer = Customer {customerName :: Name, trips :: [Trip], points :: Points} deriving (Show)

data Trip = Trip {destination :: Destination, price :: Price, status :: Status, activities :: [Activity], policy :: CancelPolicy} deriving (Show)

-- there is only one place in the code, where we need to compare two trips
-- and the task states that "a trip is a unique combination of destination, activities and price"
instance Eq Trip where
  Trip d1 p1 s1 a1 po1 == Trip d2 p2 s2 a2 po2 = d1 == d2 && p1 == p2 && sort a1 == sort a2

-- utility functions
sort :: Ord a => [a] -> [a]
sort [] = []
sort (x : xs) = sort [a | a <- xs, a < x] ++ [x] ++ sort [b | b <- xs, b > x]

allDifferent :: Eq a => [a] -> Bool
allDifferent [] = True
allDifferent (x : xs) = x `notElem` xs && allDifferent xs

listToMaybe :: [a] -> Maybe a
listToMaybe (x : xs) = Just x
listToMaybe [] = Nothing

-- first part
data Thresholds = Thresholds {moneyThreshold :: Price, durationThreshold :: Duration, loyaltyPointsThreshold :: Points}

freeTripEligibleCustomers :: Agency -> Thresholds -> [Customer]
freeTripEligibleCustomers (Agency customers) (Thresholds moneyThreshold durationThreshold loyaltyPointsThreshold) =
  filter
    ( \customer ->
        not (hasCancelledTrips customer)
          && hasVisitedOnlyOnce customer
          && (customerMoney customer >= moneyThreshold)
          && (customerDuration customer >= 60 * durationThreshold)
          && (points customer >= loyaltyPointsThreshold)
    )
    customers
  where
    customerMoney :: Customer -> Price
    customerMoney (Customer _ trips _) =
      sum $ map price trips
    customerDuration :: Customer -> Duration
    customerDuration (Customer _ trips _) =
      sum $ map (sum . map duration . activities) trips
    hasCancelledTrips :: Customer -> Bool
    hasCancelledTrips (Customer _ trips _) = any (\(Trip _ _ status _ _) -> status == Cancelled) trips
    hasVisitedOnlyOnce :: Customer -> Bool
    hasVisitedOnlyOnce (Customer _ trips _) = allDifferent $ map destination trips

-- the task doesn't make it clear whether trips in progress and upcoming trips also contribute to the total duration and visits
-- if this is the case, then `trips` should be replaced with (filter (\trip -> status trip == Finished) trips)
-- like this:
-- customerDuration (Customer _ trips _) = sum $ map (sum . map duration . activities) (filter (\trip -> status trip == Finished) trips)

-- second part
c :: Trip -> Price
c (Trip _ _ _ _ Flexible) = 0.7
c (Trip _ _ _ _ Moderate) = 0.4
c (Trip _ _ _ _ Strict) = 0.1

isCancellable :: Trip -> Bool
isCancellable (Trip _ _ Upcoming _ _) = True
isCancellable (Trip _ _ InProgress _ _) = True
isCancellable _ = False

k :: Customer -> Price
k (Customer _ trips _)
  | null trips = 0
  | otherwise = fromIntegral (length (filter (\trip -> status trip /= Cancelled) trips)) / fromIntegral (length trips)

quotient :: Trip -> Agency -> Price
quotient trip (Agency customers) = fromIntegral (length cancelled) / fromIntegral (length enrolled)
  where
    enrolled :: [Customer]
    enrolled = filter (\(Customer _ trips _) -> trip `elem` trips) customers
    cancelled :: [Customer]
    cancelled = filter (\(Customer _ trips _) -> trip `elem` trips && status trip == Cancelled) customers

cancelledAvg :: Customer -> Trip -> Price
cancelledAvg (Customer _ trips _) toBeCancelled
  | null cancelledTripsPrices = 0
  | otherwise = sum cancelledTripsPrices / fromIntegral (length cancelledTripsPrices)
  where
    cancelledTripsPrices :: [Price]
    cancelledTripsPrices = map price $ filter (\trip -> (status trip == Cancelled) && trip /= toBeCancelled) trips

getRefund :: Agency -> Name -> Destination -> Maybe Price
getRefund (Agency customers) name tripDestination = case customer of
  Nothing -> Nothing
  Just customer ->
    if status trip == Upcoming
      then Just (max ((k customer * c trip * price trip) - (quotient trip (Agency customers) * cancelledAvg customer trip)) 0)
      else Nothing
  where
    customer :: Maybe Customer
    customer = listToMaybe $ filter (not . null . cancellableTrips . Just) (filter (\customer -> customerName customer == name) customers)
    cancellableTrips :: Maybe Customer -> [Trip]
    cancellableTrips Nothing = []
    cancellableTrips (Just (Customer _ trips _)) = filter (\(Trip d _ status _ _) -> d == tripDestination && (status == Upcoming || status == InProgress)) trips
    trip :: Trip
    trip = head (cancellableTrips customer)

-- REMARK:
-- the task guarantees that "customerName and destination define at most one cancellable trip"
-- therefore there are two possible cases -
-- 1. there is only one customer with the given name,
--    who has cancellable trips and there is only one such trip
-- 2. there are no customers with cancellable trips to the given destination
-- therefore
-- if the customer doesn't exist, the trip also doesn't exist   ->  Nothing is returned
-- if the customer exists and the trip is Upcoming              -> a refund is returned
-- if the customer exists and the trip is InProgress            ->  Nothing is returned