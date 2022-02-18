package bg.sofia.uni.fmi.mjt.game.recommender;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

public class GameRecommenderTest {

    private GameRecommender recommender;
    private static LocalDate[] dates;

    @BeforeAll
    static void setupDates() {
        dates = new LocalDate[10];
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-LLL-yyyy", Locale.ENGLISH);
        dates[0] = LocalDate.parse("23-Nov-1998", formatter);
        dates[1] = LocalDate.parse("20-Sep-2000", formatter);
        dates[2] = LocalDate.parse("29-Apr-2008", formatter);
        dates[3] = LocalDate.parse("08-Sep-1999", formatter);
        dates[4] = LocalDate.parse("29-Apr-2008", formatter);
        dates[5] = LocalDate.parse("12-Nov-2007", formatter);
        dates[6] = LocalDate.parse("23-May-2010", formatter);
        dates[7] = LocalDate.parse("26-Oct-2018", formatter);
        dates[8] = LocalDate.parse("18-Nov-2014", formatter);
        dates[9] = LocalDate.parse("17-Sep-2013", formatter);
    }

    @BeforeEach
    void setup() throws IOException {
        this.recommender = new GameRecommender(new FileReader(Path.of("test_file.csv").toFile(), StandardCharsets.UTF_8));
    }

    @Test
    void testGetAllGames() {
        List<Game> expectedGames = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            expectedGames.add(new Game("Game" + (i + 1), "Platform" + ((i / 2) + 1), dates[i], "GameDescription" + (i + 1), 99 - i, 9.5 - i * 0.5));
        }
        assertIterableEquals(expectedGames, this.recommender.getAllGames(), "Imported games should be the as in the file");
    }

    @Test
    void testGetGamesReleasedAfter() {
        assertThrows(IllegalArgumentException.class, () -> this.recommender.getGamesReleasedAfter(null),
                "Filtering by null should throw an IllegalArgumentException");
        List<Game> expectedGames = new ArrayList<>();
        expectedGames.add(new Game("Game8", "Platform4", LocalDate.of(2018, 10, 26), "GameDescription8", 92, 6.0));
        expectedGames.add(new Game("Game9", "Platform5", LocalDate.of(2014, 11, 18), "GameDescription9", 91, 5.5));
        expectedGames.add(new Game("Game10", "Platform5", LocalDate.of(2013, 9, 17), "GameDescription10", 90, 5.0));
        assertIterableEquals(expectedGames, this.recommender.getGamesReleasedAfter(LocalDate.of(2013, 1, 1)), "Filtering by date should return only the games after a date");
    }

    @Test
    void testGetTopNUserRatedGamesWhenMoreThanAvailable() {
        List<Game> expectedGames = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            expectedGames.add(new Game("Game" + (i + 1), "Platform" + (i / 2 + 1), dates[i], "GameDescription" + (i + 1), 99 - i, 9.5 - i * 0.5));
        }
        assertIterableEquals(expectedGames, this.recommender.getTopNUserRatedGames(20), "Method should return all games if n>total number of games");
    }

    @Test
    void testGetTopNUserRatedGames() {
        assertThrows(IllegalArgumentException.class, () -> this.recommender.getTopNUserRatedGames(-1), "Method should throw IllegalArgumentException when called with negative number of games as parameter");
        List<Game> expectedGames = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            expectedGames.add(new Game("Game" + (i + 1), "Platform" + ((i / 2) + 1), dates[i], "GameDescription" + (i + 1), 99 - i, 9.5 - i * 0.5));
        }
        assertIterableEquals(expectedGames, this.recommender.getTopNUserRatedGames(5), "Imported games should be the same as in the file");
    }

    @Test
    void testGetYearsWithTopScoringGames() {
        List<Integer> expectedYears = new ArrayList<>();
        expectedYears.add(1998);
        expectedYears.add(2000);
        expectedYears.add(2008);
        assertIterableEquals(expectedYears, this.recommender.getYearsWithTopScoringGames(97),
                "The first three games in test are the of score>=97 and their years are 1998, 2000 and 2008. " +
                        "Method getYearsWithTopScoringGames should return the years with the games of highest score above the specified");
    }

    @Test
    void testGetAllNamesOfGamesReleasedIn() {
        String expectedString = "Game3, Game5";
        assertEquals(expectedString, this.recommender.getAllNamesOfGamesReleasedIn(2008), "Method getAllGamesReleasedIn should return all game names of the specified year");
    }

    @Test
    void testGetHighestUserRatedGameByPlatform() {
        assertThrows(NoSuchElementException.class, () -> this.recommender.getHighestUserRatedGameByPlatform("Platform6"));
        Game expectedGame = new Game("Game1", "Platform1", LocalDate.of(1998, 11, 23), "GameDescription1", 99, 9.5);
        assertEquals(expectedGame, this.recommender.getHighestUserRatedGameByPlatform("Platform1"),
                "Method getHighestRatedGamesByPlatform should return the highest-rated games of a specific platform");
    }

    @Test
    void testGetAllGamesByPlatform() {
        List<Set<Game>> sets = new ArrayList<>(5);
        for (int i = 0; i < 5; i++) {
            sets.add(new HashSet<>());
        }
        for (int i = 0; i < 10; i++) {
            sets.get(i / 2).add(new Game("Game" + (i + 1), "Platform" + ((i / 2) + 1), dates[i], "GameDescription" + (i + 1), 99 - i, 9.5 - i * 0.5));
        }
        Map<String, Set<Game>> expected = new HashMap<>();
        for (int i = 0; i < 5; i++) {
            expected.put("Platform" + (i + 1), sets.get(i));
        }
        assertEquals(expected, this.recommender.getAllGamesByPlatform(),
                "Mapping the games by Category should distribute all games in the correct sets of value of each category");
    }

    @Test
    void testGetYearsActive() {
        assertEquals(3, this.recommender.getYearsActive("Platform1"),
                "Getting active years of a platform should return the difference between the first and last year, unless they are the same");
    }

    @Test
    void testGetGamesSimilarTo() {
        List<Game> expectedGames = new ArrayList<>();
        expectedGames.add(new Game("Game1", "Platform1", dates[0], "GameDescription1", 99, 9.5));
        expectedGames.add(new Game("Game10", "Platform5", dates[9], "GameDescription10", 90, 5.0));
        String[] keywords = {"Game", "Description", "1"};
        assertIterableEquals(expectedGames, this.recommender.getGamesSimilarTo(keywords),
                "Method getGamesSimilarTo should return only the games that have ALL keywords included");
    }
}
