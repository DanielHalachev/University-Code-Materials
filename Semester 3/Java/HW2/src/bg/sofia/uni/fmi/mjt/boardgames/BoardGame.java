package bg.sofia.uni.fmi.mjt.boardgames;

import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public record BoardGame(int id, String name, String description, int maxPlayers, int minAge, int minPlayers,
                        int playingTimeMins, Collection<String> categories, Collection<String> mechanics) {

    private static final int ID_POSITION = 0;
    private static final int NAME_POSITION = 4;
    private static final int DESCRIPTION_POSITION = 8;
    private static final int MAX_PLAYERS_POSITION = 1;
    private static final int MIN_AGE_POSITION = 2;
    private static final int MIN_PLAYERS_POSITION = 3;
    private static final int PLAYING_TIME_MINS_POSITION = 5;
    private static final int CATEGORIES_POSITION = 6;
    private static final int MECHANICS_POSITION = 7;

    public static double calculateGameSimilarity(BoardGame game1, BoardGame game2) {
        double numberedAttributesDistance = 0;
        double typeAttributesDistance = 0;

        // squared distances between numbered attributes
        numberedAttributesDistance += Math.pow(game1.playingTimeMins() - game2.playingTimeMins(), 2);
        numberedAttributesDistance += Math.pow(game1.maxPlayers() - game2.maxPlayers(), 2);
        numberedAttributesDistance += Math.pow(game1.minAge() - game2.minAge(), 2);
        numberedAttributesDistance += Math.pow(game1.minPlayers() - game2.minPlayers(), 2);
        numberedAttributesDistance = Math.sqrt(numberedAttributesDistance);

        // distance between categories
        Set<String> union = new HashSet<>(game1.categories());
        union.addAll(game2.categories());
        Set<String> intersection = new HashSet<>(game1.categories());
        intersection.retainAll(game2.categories());
        // if there are no common categories, we return an invalid distance
        if (intersection.isEmpty()) {
            return -1;
        }
        typeAttributesDistance += union.size() - intersection.size();

        // distance between mechanics
        union = new HashSet<>(game1.mechanics());
        union.addAll(game2.mechanics());
        intersection = new HashSet<>(game1.mechanics());
        intersection.retainAll(game2.mechanics());
        typeAttributesDistance += union.size() - intersection.size();

        // return total distance between two games according to attributes
        return numberedAttributesDistance + typeAttributesDistance;
    }

    public static BoardGame of(String string) {
        String[] stringArray = string.split(";");
        return new BoardGame(Integer.parseInt(stringArray[ID_POSITION]),
                stringArray[NAME_POSITION],
                stringArray[DESCRIPTION_POSITION],
                Integer.parseInt(stringArray[MAX_PLAYERS_POSITION]),
                Integer.parseInt(stringArray[MIN_AGE_POSITION]),
                Integer.parseInt(stringArray[MIN_PLAYERS_POSITION]),
                Integer.parseInt(stringArray[PLAYING_TIME_MINS_POSITION]),
                Arrays.asList(stringArray[CATEGORIES_POSITION].split(",")),
                Arrays.asList(stringArray[MECHANICS_POSITION].split(",")));
    }
}