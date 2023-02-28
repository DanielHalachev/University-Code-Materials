import Distribution.Compat.CharParsing (letter)
import Data.List

segments :: (Ord t) => [t] -> [[t]]
segments [] = [[]]
segments [x] = [[x]]
segments (t : ts) = helper ts [] [t]
  where
    helper :: (Ord t) => [t] -> [[t]] -> [t] -> [[t]]
    helper [] res temp = res ++ [temp]
    helper (x : xs) res temp
      | last temp > x = helper xs res (temp ++ [x])
      | otherwise = helper xs (res ++ [temp]) [x]

l :: [Integer]
l = [1, 5, 3, 2, 2, 6, 4, 7]

fillSegments l = map (\(x : xs) -> enumFromThenTo x (x - 1) 0) $ segments l

-- 2





-- 3
wordle :: [([Char], [Char])] -> [Char]
wordle [] = []
wordle instructions@(i : is)
  | null result = "No solution"
  | length result == 1 = head result
  | otherwise = "Many solutions"
  where
    result = helper (i : is) possibleWords
    helper [] possibleWords = possibleWords
    helper (i : is) possibleWords = helper is (processInstruction i possibleWords 0)
    wordLength = length $ fst $ head instructions
    possibleWords = makeWords wordLength
    processInstruction ([], []) possibleWords _ = possibleWords
    processInstruction ([], _) possibleWords _ = possibleWords
    processInstruction (_, []) possibleWords _ = possibleWords
    processInstruction (word@(w : ws), template@(t : ts)) possibleWords position
      | t == '+' = processInstruction (ws, ts) (filter (\word -> word !! position == w) possibleWords) (position + 1)
      | t == '-' = processInstruction (ws, ts) (filter (notElem w) possibleWords) (position + 1)
      | t == '?' = processInstruction (ws, ts) (filter (\word -> word !! position /= w && w `elem` word) possibleWords) (position + 1)
      | otherwise = processInstruction (ws, ts) possibleWords (position + 1)

makeWords :: Int -> [[Char]]
makeWords 0 = [[]]
makeWords n = concatMap (\word -> map (: word) alphabet) (makeWords (n - 1))
  where
    alphabet :: [Char]
    alphabet = ['a' .. 'z']
