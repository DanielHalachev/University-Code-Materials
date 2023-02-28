-- inf 1
-- 3
data RPS
  = Rock
  | Paper
  | Scissors
  deriving (Show)

beats :: RPS -> RPS -> RPS
beats Rock Paper = Paper
beats Rock Scissors = Rock
beats Paper Rock = Paper
beats Paper Scissors = Scissors
beats Scissors Rock = Rock
beats Scissors Paper = Scissors
beats Rock Rock = Rock
beats Paper Paper = Paper
beats Scissors Scissors = Scissors

-- beats (RPS rps1) (RPS rps2)
--     | rps1 == Rock && rps2 == Scissors  = rps1
--     | rps1 == Rock && rps2 == Paper     = rps2
--     | rps1 == Paper && rps2 == Rock     = rps1
--     | rps1 == Paper && rps2 == Scissors = rps2
--     | rps1 == Scissors && rps2 == Rock  = rps2
--     | rps1 == Scissors && rps2 == Paper = rps1