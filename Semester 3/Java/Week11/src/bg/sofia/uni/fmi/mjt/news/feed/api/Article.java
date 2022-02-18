package bg.sofia.uni.fmi.mjt.news.feed.api;

import com.google.gson.annotations.SerializedName;

import java.util.Objects;

// the class, which would represent a news article
public class Article {

    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_ITALIC = "\033[3m";
    private static final String ANSI_RESET_ITALIC = "\033[0m";

    private final NewsSource source;
    private final String author;
    private final String title;
    private final String description;
    private final String url;
    private final String urlToImage;
    @SerializedName("publishedAt")
    private String publishDate;
    private final String content;

    public Article(NewsSource source, String author,
                   String title, String description,
                   String url,
                   String urlToImage,
                   String publishDate, String content) {
        this.source = source;
        this.author = author;
        this.title = title;
        this.description = description;
        this.url = url;
        this.urlToImage = urlToImage;
        this.publishDate = publishDate;
        this.content = content;
    }

    public String toReadableString() {
        return String.format("%sTitle%s:%s%S" +
                        "%sSource%s:%s%s" +
                        "%sAuthor%s:%s%s" +
                        "%sDescription%s:%s%s" +
                        "%sURL%s:%s%s" +
                        "%sDate%s:%s%s" +
                        "%s%s%s%s",
                ANSI_RED, ANSI_RESET, title, System.lineSeparator(),
                ANSI_RED, ANSI_RESET, source.getName(), System.lineSeparator(),
                ANSI_RED, ANSI_RESET, author, System.lineSeparator(),
                ANSI_RED, ANSI_RESET, description, System.lineSeparator(),
                ANSI_RED, ANSI_RESET, url, System.lineSeparator(),
                ANSI_RED, ANSI_RESET, publishDate, System.lineSeparator(),
                ANSI_ITALIC, content, ANSI_RESET_ITALIC, System.lineSeparator());
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (Article) obj;
        return Objects.equals(this.source, that.source) &&
                Objects.equals(this.author, that.author) &&
                Objects.equals(this.title, that.title) &&
                Objects.equals(this.description, that.description) &&
                Objects.equals(this.url, that.url) &&
                Objects.equals(this.urlToImage, that.urlToImage) &&
                Objects.equals(this.publishDate, that.publishDate) &&
                Objects.equals(this.content, that.content);
    }

    @Override
    public int hashCode() {
        return Objects.hash(source, author, title, description, url, urlToImage, publishDate, content);
    }

    public NewsSource getSource() {
        return source;
    }

    public String getAuthor() {
        return author;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public String getURL() {
        return url;
    }

    public String getURLToImage() {
        return urlToImage;
    }

    public String getPublishDate() {
        return publishDate;
    }

    public String getContent() {
        return content;
    }
}
