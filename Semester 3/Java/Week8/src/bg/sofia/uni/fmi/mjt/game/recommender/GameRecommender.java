package bg.sofia.uni.fmi.mjt.game.recommender;

import java.io.*;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.*;

public class GameRecommender {

    List<Game> games;

    /**
     * Loads the dataset from the given {@code dataInput} stream.
     *
     * @param dataInput java.io.Reader input stream from which the dataset can be read
     */
    public GameRecommender(Reader dataInput) {
        try (BufferedReader reader = new BufferedReader(dataInput)) {
            this.games = reader.lines()
                    .skip(1)
                    .map(Game::of)
                    .toList();
        } catch (IOException e) {
            throw new IllegalArgumentException("Failed reading");
        }
    }

    /**
     * @return All games from the dataset as an unmodifiable copy.
     * If the dataset is empty, return an empty collection
     */
    public List<Game> getAllGames() {
        if (this.games.size() == 0) {
            return List.copyOf(new ArrayList<>());
        }
        return List.copyOf(this.games);
    }

    /**
     * Returns all games in the dataset released after the specified {@code date} as an unmodifiable list.
     * If no games have been released after the given date, returns an empty list.
     *
     * @param date
     * @return a list of all games released after {@code date}, in an undefined order.
     */
    public List<Game> getGamesReleasedAfter(LocalDate date) {
        if (date == null) {
            throw new IllegalArgumentException("Date is null. Cannot proceed");
        }
        return List.copyOf(this.games.stream()
                .filter(game -> game.releaseDate().isAfter(date))
                .toList());
    }

    /**
     * Returns the top {@code n} games by user review score.
     *
     * @param n maximum number of games to return
     *          If {@code n} exceeds the total number of games in the dataset, return all games.
     * @return unmodifiable list of the games sorted by user review score in descending order
     * @throws IllegalArgumentException in case {@code n} is a negative number.
     */
    public List<Game> getTopNUserRatedGames(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("Cannot return negative amount of games");
        }
        return List.copyOf(this.games.stream()
                .sorted(Comparator.comparingDouble(Game::userReview).reversed())
                .limit(n)
                .toList());
    }

    /**
     * Returns a list (without repetitions) of all years in which at least one game with meta score
     * {@code minimalScore} or higher has been released. The order of the years in the result is undefined.
     * If there are no such years, return an empty list.
     *
     * @param minimalScore
     * @return the years when a game with at least {@code minimalScore} meta score has been released
     */
    public List<Integer> getYearsWithTopScoringGames(int minimalScore) {
        return this.games.stream()
                .filter(game -> game.metaScore() >= minimalScore)
                .map(game -> game.releaseDate().getYear())
                .distinct()
                .toList();
    }

    /**
     * Returns the names of all games in the dataset released in {@code year} as a comma-separated String.
     * Each comma in the result must be followed by a space. The order of the game names in the result is undefined.
     * If no games have been released in the given year, returns an empty String.
     *
     * @param year
     * @return a comma-separated String containing all game names released in {@code year}
     */
    public String getAllNamesOfGamesReleasedIn(int year) {
        return this.games.stream()
                .filter(game -> game.releaseDate().getYear() == year)
                .map(Game::name)
                .collect(joining(", "));
    }

    /**
     * Returns the game for the specified {@code platform} with the highest user review score.
     *
     * @param platform the name of the platform
     * @return the game for the specified {@code platform} with the highest review score
     * @throws NoSuchElementException if there is no game at all released for the specified platform,
     *                                or if {@code platform} is null or an empty String.
     */
    public Game getHighestUserRatedGameByPlatform(String platform) {
        return this.games.stream()
                .filter(game -> game.platform().equals(platform))
                .max(Comparator.comparingDouble(Game::userReview))
                .orElseThrow(NoSuchElementException::new);
    }

    /**
     * Returns all games by platform. The result should map a platform name to the set of all games
     * released for this platform.
     *
     * @return all games by platform
     */
    public Map<String, Set<Game>> getAllGamesByPlatform() {
        return this.games.stream().collect(groupingBy(Game::platform, toSet()));
    }

    /**
     * Returns the number of years a game platform has been live.
     * The lifecycle of a platform is assumed to start and end with the release year of the oldest and newest game
     * released for this platform (the exact date is not significant).
     * In case all games for a given platform have been released in a single year, return 1.
     * In case {@code platform} is null, blank or unknown in the dataset, return 0.
     *
     * @return the number of years a game platform has been live
     */
    public int getYearsActive(String platform) {
        var ints = this.games.stream()
                .filter(game -> game.platform().equals(platform))
                .map(game -> game.releaseDate().getYear())
                .collect(Collectors.summarizingInt(Integer::intValue));
        if (ints.getCount() == 0) {
            return 0;
        }
        return ints.getMax() - ints.getMin() == 0 ? 1 : ints.getMax() - ints.getMin() + 1;
    }

    /**
     * Returns the games whose summary contains all {@code keywords} specified, as an unmodifiable list.
     * <p>
     * If there are no such games, return an empty list.
     * In case no keywords are specified, or any of the keywords is null or blank, the result is undefined.
     *
     * @param keywords the keywords to search for in the game summary
     * @return the games whose summary contains the specified keywords
     */
    public List<Game> getGamesSimilarTo(String... keywords) {
        return List.copyOf(this.games.stream()
                .filter(game -> {
                    boolean contains = true;
                    for (String keyWord : keywords) {
                        if (!game.summary().contains(keyWord)) {
                            contains = false;
                            break;
                        }
                    }
                    return contains;
                }).toList());
//        List<Game> result = new ArrayList<>();
//        for (String word : keywords) {
//            result.addAll(this.games.stream()
//                    .filter(game -> game.summary().contains(word))
//                    .toList());
//        }
//        return List.copyOf(result);
    }
}