package bg.sofia.uni.fmi.mjt.boardgames.analyzer;

import java.util.List;
import java.util.Map;

public interface StatisticsAnalyzer {

    /**
     * @param n the max number of categories we should return. If n > categories count, returns all categories.
     * @return the most popular games categories in the dataset.
     */
    List<String> getNMostPopularCategories(int n);

    /**
     * @return the average minimal age to play among the games in the dataset.
     * In case the dataset contains no games, returns 0.0.
     */
    double getAverageMinAge();

    /**
     * @param category the category name.
     * @return the average playtime for the games in the given category.
     * In case there are no games in the specified category, returns 0.0
     */
    double getAveragePlayingTimeByCategory(String category);

    /**
     * @return the average playtime for all game categories - the map key matches a category name.
     * In case the dataset contains no games, returns 0.0.
     */
    Map<String, Double> getAveragePlayingTimeByCategory();
}