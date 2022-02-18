package bg.sofia.uni.fmi.mjt.news.feed.api;

import java.util.Arrays;
import java.util.Objects;

// a class, which would be the java version of the object, returned in case of a successful query
public class NewsCollection {

    private final String status;
    private final int totalResults;
    private final Article[] articles;

    public NewsCollection(String status, int totalResults, Article[] articles) {
        this.status = status;
        this.totalResults = totalResults;
        this.articles = articles;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (NewsCollection) obj;
        return Objects.equals(this.status, that.status) &&
                this.totalResults == that.totalResults &&
                Arrays.equals(this.articles, that.articles);
    }

    @Override
    public int hashCode() {
        return Objects.hash(status, totalResults, Arrays.hashCode(articles));
    }

    public String getStatus() {
        return status;
    }

    public int getTotalResults() {
        return totalResults;
    }

    public Article[] getArticles() {
        return articles;
    }
}
