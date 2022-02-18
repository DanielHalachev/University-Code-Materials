package api;

import bg.sofia.uni.fmi.mjt.news.feed.api.Article;
import bg.sofia.uni.fmi.mjt.news.feed.api.NewsSource;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ArticleTest {

    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_ITALIC = "\033[3m";
    private static final String ANSI_RESET_ITALIC = "\033[0m";

    @Test
    void testArticle() {
        NewsSource source = new NewsSource("1", "bbc");
        Article article = new Article(source,
                "Author1",
                "News1",
                "Description1",
                "www.google.com",
                "www.bing.com",
                "2022/4/1",
                "Content1");
        String expected = String.format("%sTitle%s:%s%s%sSource%s:%s%s%sAuthor%s:%s%s%sDescription%s:%s%s%sURL%s:%s%s%sDate%s:%s%s%s%s%s%s",
                ANSI_RED, ANSI_RESET, article.getTitle(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, article.getSource().getName(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, article.getAuthor(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, article.getDescription(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, article.getURL(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, article.getPublishDate(), System.lineSeparator(),
                ANSI_ITALIC, article.getContent(), ANSI_RESET_ITALIC, System.lineSeparator());
        assertEquals(expected, article.toReadableString(),
                "Method toReadableString should return the article in a string with the correct formatting");
    }
}
