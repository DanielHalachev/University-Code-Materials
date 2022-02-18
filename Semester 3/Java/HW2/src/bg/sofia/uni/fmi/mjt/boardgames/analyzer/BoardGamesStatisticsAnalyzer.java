package bg.sofia.uni.fmi.mjt.boardgames.analyzer;

import bg.sofia.uni.fmi.mjt.boardgames.BoardGame;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class BoardGamesStatisticsAnalyzer implements StatisticsAnalyzer {

    // store all games here
    private final Collection<BoardGame> games;
    // store playing times by category for faster methods
    private Map<String, Double> averagePlayingTimes;
    // mapping of categories and their corresponding games for faster methods
    private Map<String, Set<BoardGame>> categoryPlayingTimes;
    // categories, sorted by popularity
    private List<String> categoryPopularity;

    public BoardGamesStatisticsAnalyzer(Collection<BoardGame> games) {
        if (games == null) {
            throw new IllegalArgumentException("Games for statistics should not be null");
        }

        this.games = games;
        // ensure this.categoryPlayingTimes is initialized before this.averagePlayingTimes
        mapData();
    }

    private void mapData() {
        // always perform mapByCategory() before mapCategoryByPlayingTimes() and calculateCategoryPopularity
        // because the second and methods depend on the execution of the first
        mapByCategory();
        mapCategoryByPlayingTimes();
        calculateCategoryPopularity();
    }

    private void mapByCategory() {
        this.categoryPlayingTimes = new HashMap<>();
        for (BoardGame game : this.games) {
            for (String category : game.categories()) {
                this.categoryPlayingTimes.putIfAbsent(category, new HashSet<>());
                this.categoryPlayingTimes.get(category).add(game);
            }
        }
    }

    private void mapCategoryByPlayingTimes() {
        this.averagePlayingTimes = this.categoryPlayingTimes.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, entry -> entry.getValue().stream()
                        .mapToInt(BoardGame::playingTimeMins)
                        .average().orElse(0.0)
                ));
    }

    private void calculateCategoryPopularity() {
        this.categoryPopularity = this.categoryPlayingTimes.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, entry -> entry.getValue().size()))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<String, Integer>comparingByValue().reversed())
                .map(Map.Entry::getKey)
                .toList();
    }

    @Override
    public List<String> getNMostPopularCategories(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Cannot have a non-positive number of categories");
        }

        return this.categoryPopularity.subList(0, n);
    }

    @Override
    public double getAverageMinAge() {
        return this.games.stream().mapToInt(BoardGame::minAge).average().orElse(0.0);
    }

    @Override
    public double getAveragePlayingTimeByCategory(String category) {
        if (category == null || category.equals("")) {
            throw new IllegalArgumentException("Category is either null or empty");
        }

        return this.averagePlayingTimes.get(category);
    }

    @Override
    public Map<String, Double> getAveragePlayingTimeByCategory() {
        return this.averagePlayingTimes;
    }
}

