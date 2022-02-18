package bg.sofia.uni.fmi.mjt.game.recommender;

import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Locale;

public record Game(String name, String platform, LocalDate releaseDate, String summary, int metaScore,
                   double userReview) {

    public static final int NAME_POSITION = 0;
    public static final int PLATFORM_POSITION = 1;
    public static final int DATE_POSITION = 2;
    public static final int SUMMARY_POSITION = 3;
    public static final int META_SCORE_POSITION = 4;
    public static final int USER_REVIEW_POSITION = 5;

    public static Game of(String string) {
        String[] stringArray;
        String name;
        String platform;
        LocalDate releaseDate;
        String summary;
        int metaScore;
        double userReview;
        try {
            stringArray = string.split(",");
            name = stringArray[NAME_POSITION];
            platform = stringArray[PLATFORM_POSITION];
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-LLL-yyyy", Locale.ENGLISH);
            releaseDate = LocalDate.parse(stringArray[DATE_POSITION], formatter);
            summary = stringArray[SUMMARY_POSITION];
            metaScore = Integer.parseInt(stringArray[META_SCORE_POSITION]);
            userReview = Double.parseDouble(stringArray[USER_REVIEW_POSITION]);
        } catch (DateTimeException e) {
            throw new IllegalArgumentException("Incorrect Date: ", e);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Incorrect Meta score or User score: ", e);
        } catch (IndexOutOfBoundsException e) {
            throw new IllegalArgumentException("Line contains too few arguments: ", e);
        }
        return new Game(name, platform, releaseDate, summary, metaScore, userReview);
    }
}
