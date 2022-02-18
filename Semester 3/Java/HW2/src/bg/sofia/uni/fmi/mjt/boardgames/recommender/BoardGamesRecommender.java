package bg.sofia.uni.fmi.mjt.boardgames.recommender;

import bg.sofia.uni.fmi.mjt.boardgames.BoardGame;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class BoardGamesRecommender implements Recommender {

    private static final String REGEX = "[\\p{IsPunctuation}\\p{IsWhite_Space}]+";
    // the words that would have to be excluded
    private Set<String> stopWords;
    // the games to recommend
    private Set<BoardGame> games;
    // a map of keywords and game IDs that contain them in their description
    private Map<String, Set<BoardGame>> keywordsAndTheirCorrespondingGames;

    /**
     * Constructs an instance using the provided file names.
     *
     * @param datasetZipFile  ZIP file containing the board games dataset file
     * @param datasetFileName the name of the dataset file (inside the ZIP archive)
     * @param stopwordsFile   the stopwords file
     */
    public BoardGamesRecommender(Path datasetZipFile, String datasetFileName, Path stopwordsFile) {
        if (datasetZipFile == null || stopwordsFile == null || datasetFileName == null || datasetFileName.equals("")) {
            throw new IllegalArgumentException("Cannot have null paths to files");
        }

        try (FileSystem fileSystem = FileSystems.newFileSystem(datasetZipFile)) {
            Path fileToExtract = fileSystem.getPath(datasetFileName);
            this.games = Files.lines(fileToExtract, StandardCharsets.UTF_8)
                    .skip(1)
                    .map(BoardGame::of)
                    .collect(Collectors.toSet());
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            this.stopWords = Files.lines(stopwordsFile, StandardCharsets.UTF_8).collect(Collectors.toSet());
        } catch (IOException e) {
            e.printStackTrace();
        }

        mapKeywordToGameByDescription();
    }

    /**
     * Constructs an instance using the provided Reader streams.
     *
     * @param dataset   Reader from which the dataset can be read
     * @param stopwords Reader from which the stopwords list can be read
     */
    public BoardGamesRecommender(Reader dataset, Reader stopwords) {
        if (dataset == null || stopwords == null) {
            throw new IllegalArgumentException("Readers for constructors cannot be null");
        }

        try (BufferedReader dataReader = new BufferedReader(dataset)) {
            this.games = dataReader.lines()
                    .skip(1)
                    .map(BoardGame::of)
                    .collect(Collectors.toSet());
        } catch (IOException e) {
            this.games = new HashSet<>();
            e.printStackTrace();
        }

        try (BufferedReader stopWordReader = new BufferedReader(stopwords)) {
            this.stopWords = stopWordReader.lines().collect(Collectors.toSet());
        } catch (IOException e) {
            this.stopWords = new HashSet<>();
            e.printStackTrace();
        }

        mapKeywordToGameByDescription();
    }

    private void mapKeywordToGameByDescription() {
        this.keywordsAndTheirCorrespondingGames = new HashMap<>();
        for (BoardGame game : this.games) {
            Set<String> filteredKeywords = Arrays.stream(
                            game.description().toLowerCase().split(REGEX))
                    .filter(s -> !this.stopWords.contains(s))
                    .filter(s -> !s.isBlank())
                    .collect(Collectors.toSet());
            for (String word : filteredKeywords) {
                this.keywordsAndTheirCorrespondingGames.putIfAbsent(word, new HashSet<>());
                this.keywordsAndTheirCorrespondingGames.get(word).add(game);
            }
        }
    }

    @Override
    public Collection<BoardGame> getGames() {
        return Collections.unmodifiableCollection(this.games);
    }


    @Override
    public List<BoardGame> getSimilarTo(BoardGame game, int n) {
        if (game == null || n <= 0) {
            throw new IllegalArgumentException("Either game is null or a non-positive number of games is requested");
        }

        Map<Integer, Double> distances = new HashMap<>();
        for (BoardGame boardGame : this.games) {
            distances.put(boardGame.id(), BoardGame.calculateGameSimilarity(boardGame, game));
        }

        return this.games.stream()
                .filter(boardGame -> boardGame.id() != game.id())
                .filter(boardGame -> distances.get(boardGame.id()) != -1)
                .sorted(Comparator.comparingDouble(someGame -> distances.get(someGame.id())))
                .limit(n)
                .toList();
    }

    @Override
    public List<BoardGame> getByDescription(String... keywords) {
        if (keywords == null) {
            throw new IllegalArgumentException("List of keywords cannot be null");
        }

        Set<String> filteredKeyWords = Arrays.stream(keywords)
                .map(String::toLowerCase)
                .filter(s -> !this.stopWords.contains(s)).collect(Collectors.toSet());

        List<BoardGame> gamesByGivenKeywords = new ArrayList<>();
        for (String word : filteredKeyWords) {
            gamesByGivenKeywords.addAll(this.keywordsAndTheirCorrespondingGames.get(word));
        }

        return gamesByGivenKeywords.stream()
                .collect(Collectors.groupingBy(boardGame -> boardGame, Collectors.counting()))
                .entrySet().stream()
                .sorted(Map.Entry.<BoardGame, Long>comparingByValue().reversed())
                .map(Map.Entry::getKey)
                .toList();
    }

    @Override
    public void storeGamesIndex(Writer writer) {
        if (writer == null) {
            throw new IllegalArgumentException("Writer cannot be null");
        }

        for (var pair : this.keywordsAndTheirCorrespondingGames.entrySet()) {
            try {
                writer.write(pair.getKey() + ": " +
                        pair.getValue().stream()
                                .map(boardGame -> Integer.toString(boardGame.id()))
//                                .sorted(Comparator.comparingInt(Integer::valueOf))  //for testing purposes
                                .collect(Collectors.joining(", ")) +
                        System.lineSeparator());
                writer.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        try {
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
