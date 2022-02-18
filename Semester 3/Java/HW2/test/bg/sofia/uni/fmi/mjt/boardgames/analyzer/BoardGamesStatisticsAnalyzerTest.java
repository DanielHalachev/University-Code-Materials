package bg.sofia.uni.fmi.mjt.boardgames.analyzer;

import bg.sofia.uni.fmi.mjt.boardgames.BoardGame;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertIterableEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class BoardGamesStatisticsAnalyzerTest {

    private static List<String> categories;
    private static List<String> mechanics;
    private Set<BoardGame> games;
    private StatisticsAnalyzer analyzer;

    @BeforeAll
    static void setUpCategoriesAndMechanics() {
        categories = new LinkedList<>();
        mechanics = new LinkedList<>();
        for (int i = 0; i <= 10; i++) {
            mechanics.add(("Mechanic" + i));
        }
        for (int i = 0; i <= 10; i++) {
            categories.add(("Category" + i));
        }
    }

    @BeforeEach
    void setup() {
        //       ID Name    Description     Pl  Age Pl  P.T.    Categories       Mechanics - same as categories
        //        0	Game0	Description0	2	0	1	2	Category0, Category1
        //        1	Game1	Description1	4	1	2	3	Category1, Category2
        //        2	Game2	Description2	6	2	3	4	Category2, Category3
        //        3	Game3	Description3	8	3	4	5	Category3, Category4
        //        4	Game4	Description4	10	4	5	6	Category4, Category5
        //        5	Game5	Description5	12	5	6	7	Category5, Category6
        //        6	Game6	Description6	14	6	7	8	Category6, Category7
        //        7	Game7	Description7	16	7	8	9	Category7, Category8
        //        8	Game8	Description8	18	8	9	10	Category8, Category9
        //        9	Game9	Description9	20	9	10	11	Category9, Category10
        // Additional game for method testGetNMostPopularCategories():
        //        10	Game10	Description10	22	10	11	12	Category0, Category1

        this.games = new HashSet<>();
        for (int i = 0; i < 10; i++) {
            this.games.add(new BoardGame(i,
                    "Game" + i,
                    "Description" + i,
                    (i + 1) * 2,
                    i,
                    i + 1,
                    i + 2,
                    categories.subList(i, i + 2),
                    mechanics.subList(i, i + 2)));
        }
        this.analyzer = new BoardGamesStatisticsAnalyzer(this.games);
    }

    @Test
    void testNullConstructor() {
        assertThrows(IllegalArgumentException.class, () -> new BoardGamesStatisticsAnalyzer(null),
                "Null parameter should throw IllegalArgumentException");
    }

    @Test
    void testGetNMostPopularCategories() {
        assertThrows(IllegalArgumentException.class, () -> this.analyzer.getNMostPopularCategories(-1),
                "Method getNMostPopularCategories cannot return a negative amount of Categories");
        this.games.add(new BoardGame(10,
                "Game10",
                "Description10",
                22,
                10,
                11,
                12,
                categories.subList(0, 2),
                mechanics.subList(0, 2)));
        this.analyzer = new BoardGamesStatisticsAnalyzer(this.games);
        List<String> expectedCategories = new ArrayList<>();
        expectedCategories.add("Category1");
        expectedCategories.add("Category5");
        assertIterableEquals(expectedCategories, this.analyzer.getNMostPopularCategories(2),
                "Method getNMostPopularCategories should return only the specified number of categories " +
                        "and in the right order");
    }

    @Test
    void testGetAverageMinAge() {
        assertEquals(4.5, this.analyzer.getAverageMinAge(),
                "MethodGetAverageMinAge should return the correct average minimum age of all games");
    }

    @Test
    void testGetAveragePlayingTimeByCategoryByParameter() {
        assertThrows(IllegalArgumentException.class, () -> this.analyzer.getAveragePlayingTimeByCategory(null),
                "Null parameters should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.analyzer.getAveragePlayingTimeByCategory(""),
                "Empty string parameter should throw IllegalArgumentException");
        assertEquals(2.0, this.analyzer.getAveragePlayingTimeByCategory("Category0"),
                "Method getAveragePlayingTimeByCategory should return the playing time of one game " +
                        "only if the category is seen only in that game");
        assertEquals(2.5, this.analyzer.getAveragePlayingTimeByCategory("Category1"),
                "Method getAveragePlayingTimeByCategory should return the average playing time of all games " +
                        "that have the specified category");
    }

    @Test
    void testGetAveragePlayingTimeByCategory() {
        Map<String, Double> expected = new HashMap<>();
        expected.put("Category0", 2.0);
        expected.put("Category1", 2.5);
        expected.put("Category2", 3.5);
        expected.put("Category3", 4.5);
        expected.put("Category4", 5.5);
        expected.put("Category5", 6.5);
        expected.put("Category6", 7.5);
        expected.put("Category7", 8.5);
        expected.put("Category8", 9.5);
        expected.put("Category9", 10.5);
        expected.put("Category10", 11.0);
        assertEquals(expected, this.analyzer.getAveragePlayingTimeByCategory(),
                "Method getAveragePlayingTimeByCategory() should return the correct average playing time of " +
                        "all games of a specific category");
    }
}
