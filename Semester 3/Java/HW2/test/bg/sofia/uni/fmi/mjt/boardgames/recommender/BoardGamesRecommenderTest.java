package bg.sofia.uni.fmi.mjt.boardgames.recommender;

import bg.sofia.uni.fmi.mjt.boardgames.BoardGame;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;
import java.io.StringWriter;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class BoardGamesRecommenderTest {

    private static final Path stopwordsPath = Path.of("stopwords.txt");
    private static final Path zipDataFile = Path.of("data.zip");
    private static final Path rawDataFIle = Path.of("data.csv");
    private static List<BoardGame> games;
    private Recommender recommender;

    @BeforeAll
    static void setGames() {
        //  id;details.maxPlayers;details.minAge;details.minPlayers;details.name;details.playingTime;attributes.boardGameCategory;attributes.boardGameMechanic;details.description
        //  0;2;0;1;Game0;2;Category0,Category1;Mechanics0,Mechanics1,woRd1 word2 word3
        //  1;4;1;2;Game1;3;Category1,Category2;Mechanics1,Mechanics2,word2 wOrd3 word4
        //  2;6;2;3;Game2;4;Category2,Category3;Mechanics2,Mechanics3,word1 word4 Word5
        //  3;8;3;4;Game3;5;Category3,Category4;Mechanics3,Mechanics4,word1 worD5 word7
        //  4;10;4;5;Game4;6;Category4,Category5;Mechanics4,Mechanics5,Word1 word5 word8
        List<String> categories = new LinkedList<>();
        List<String> mechanics = new LinkedList<>();
        games = new LinkedList<>();
        for (int i = 0; i <= 5; i++) {
            mechanics.add(("Mechanics" + i));
        }
        for (int i = 0; i <= 5; i++) {
            categories.add(("Category" + i));
        }
        List<String> descriptions = List.of(
                "woRd1 word2 word3",
                "word2 wOrd3 word4",
                "word1 word4 Word5",
                "word1 worD5 word7",
                "Word1 word5 word8");
        for (int i = 0; i < 5; i++) {
            games.add(new BoardGame(i,
                    "Game" + i,
                    descriptions.get(i),
                    (i + 1) * 2,
                    i,
                    i + 1,
                    i + 2,
                    categories.subList(i, i + 2),
                    mechanics.subList(i, i + 2)
            ));
        }
    }

    @BeforeEach
    void setup() {
        this.recommender = new BoardGamesRecommender(zipDataFile, "data.csv", stopwordsPath);
    }

    @Test
    void testZipConstructorFail() {
        // favourable scenario is tested in every other test implicitly
        // unfavourable scenario:
        File zip = zipDataFile.toFile();
        zip.setReadable(false);
        assertThrows(IllegalArgumentException.class,
                () -> new BoardGamesRecommender(null, "data.csv", null),
                "Null parameters should throw IllegalArgumentException");
        assertDoesNotThrow(() -> new BoardGamesRecommender(zipDataFile, "data.csv", stopwordsPath),
                "Failing IO operation should not break the program");
        zip.setReadable(true);
    }

    @Test
    void testReadersConstructor() throws IOException {
        File myFile = rawDataFIle.toFile();
        // test behaviour in case of a successful reading
        try (Reader dataReader = new FileReader(myFile)) {
            try (Reader stopwordsReader = new FileReader("stopwords.txt")) {
                this.recommender = new BoardGamesRecommender(dataReader, stopwordsReader);
                assertEquals(new HashSet<>(games), new HashSet<>(this.recommender.getGames()),
                        "Method getGames should return all games, passed in the reader constructor");
            }
        }
        // test behaviour in case of a failed reading
        assertThrows(IllegalArgumentException.class, () -> new BoardGamesRecommender(null, null),
                "Null parameters should throw IllegalArgumentException");
        myFile.setReadable(false);
        try (Reader stopwordsReader = new FileReader("stopwords.txt")) {
            try (Reader failReader = new FileReader(myFile)) {
                assertDoesNotThrow(() -> new BoardGamesRecommender(failReader, stopwordsReader),
                        "Failed IO operation should not break the program");
            }
        }
        myFile.setReadable(true);
    }


    @Test
    void getGames() {
        assertEquals(new HashSet<>(games), new HashSet<>(this.recommender.getGames()),
                "Method getGames() by zip constructor should return all games");
    }

    @Test
    void testGetSimilarTo() {
        assertThrows(IllegalArgumentException.class, () -> this.recommender.getSimilarTo(null, 2),
                "Null parameters should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.recommender.getSimilarTo(games.get(0), -1),
                "Method getSimilarTo() cannot return a negative amount of Games");
        List<BoardGame> expected = new ArrayList<>();
        // Game0 is absolutely the same, it should be excluded
        // Only Game1 contains at least one of Game0's categories
        expected.add(games.get(1));
        assertIterableEquals(expected, this.recommender.getSimilarTo(games.get(0), 4),
                "Method getSimilarTo() should return all games similar to the specified and not including it, " +
                        "and with at least one common category, while also ordering by similarity");
    }

    @Test
    void testGetByDescription() {
        assertThrows(IllegalArgumentException.class, () -> this.recommender.getByDescription((String[]) null),
                "Null parameters should throw IllegalArgumentException");
        String[] keywords = new String[]{"wOrd2", "woRd3", "Word4"};
        List<BoardGame> expected = new ArrayList<>();
        // Game1 contains all 3 words, Game0 contains two (word2, word3) and Game2 contains only "word4"
        // the other two games don't contain even a single word, therefore they are excluded
        expected.add(games.get(1));
        expected.add(games.get(0));
        expected.add(games.get(2));
        assertIterableEquals(expected, this.recommender.getByDescription(keywords),
                "Method getByDescription should return only the games that contain at least one " +
                        "of the specified words on their description and the result should be sorted");
    }

    @Test
    void testStoreGamesIndex() {
        assertThrows(IllegalArgumentException.class, () -> this.recommender.storeGamesIndex(null),
                "Null parameters should throw IllegalArgumentException");
        Writer failWriter;
        try {
            File failFile = Path.of("forbiddenFile.txt").toFile();
            failFile.setWritable(false);
            failWriter = new PrintWriter(failFile, StandardCharsets.UTF_8);
            assertDoesNotThrow(() -> this.recommender.storeGamesIndex(failWriter),
                    "IO operations in storeGamesIndex should not break the program");
            failFile.delete();
        } catch (Exception e) {
            e.printStackTrace();
        }
        Writer writer = new StringWriter();
        String expected = """
                word1: 3, 0, 2, 4
                word3: 0, 1
                word2: 0, 1
                word5: 3, 2, 4
                word4: 1, 2
                word7: 3
                word8: 4
                """;
        this.recommender.storeGamesIndex(writer);
        assertEquals(expected, writer.toString(), "Method storeGamesIndex should store the index correctly");
    }
}
