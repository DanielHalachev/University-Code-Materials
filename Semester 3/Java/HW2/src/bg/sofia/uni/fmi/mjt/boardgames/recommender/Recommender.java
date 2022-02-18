package bg.sofia.uni.fmi.mjt.boardgames.recommender;

import bg.sofia.uni.fmi.mjt.boardgames.BoardGame;

import java.io.Writer;
import java.util.Collection;
import java.util.List;

public interface Recommender {

    /**
     * @return all board games in the dataset as an unmodifiable view.
     */
    Collection<BoardGame> getGames();

    /**
     * @param game the game we want the recommendation to be based on
     * @return a list of top n similar games to the provided one, ordered in descending order by their match.
     * The returned games share at least one common category. The similarity metric is described in the assignment.
     */
    List<BoardGame> getSimilarTo(BoardGame game, int n);

    /**
     * @param keywords the keywords to search for in games' description
     * @return a list of games with description containing at least one of the provided keywords, ordered by
     * decreasing number of matching keywords.
     * In case of ties, the relative order of the respective games with equal number of matching keywords is undefined.
     */
    List<BoardGame> getByDescription(String... keywords);

    /**
     * Stores the game index to a Writer, representing a persistent storage.
     * Each line in the output contains a word and the list of game IDs and has the following format:
     * <word1>: <gameId11>, <gameId12>,..., <gameId1N>
     * <word2>: <gameId21>, <gameId22>, ..., <gameId2N>
     * The capitalization of words, the order of words and the order of game IDs per word are all undefined.
     *
     * @param writer the writer stream to output the index to
     */
    void storeGamesIndex(Writer writer);
}