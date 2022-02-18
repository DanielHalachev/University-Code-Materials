package bg.sofia.uni.fmi.mjt.news.feed.api;

import bg.sofia.uni.fmi.mjt.news.feed.exceptions.NewsFeedException;

import java.net.http.HttpClient;
import java.util.List;
import java.util.Objects;

// a class, which would allow the convenient construction of queries and the receiving of responses
public class Query {

    private List<Article> articles;
    private final QueryExecutor queryExecutor;
    private final String category;
    private final String country;
    private final String keywords;
    private final String pageSize;
    private boolean isSent = false;

    private Query(QueryBuilder builder) {
        this.queryExecutor = builder.queryExecutor;
        this.category = builder.category;
        this.country = builder.country;
        this.keywords = builder.keywords;
        this.pageSize = builder.pageSize;
    }

    private void send() throws NewsFeedException {
        this.articles = queryExecutor.getNews(toQueryString());
        this.isSent = true;
    }

    public List<Article> ask() throws NewsFeedException {
        if (!isSent) {
            send();
        }
        return this.articles;
    }

    public String askForString() throws NewsFeedException {
        if (!isSent) {
            send();
        }
        return toPrintableString(this.articles);
    }

    private static String toPrintableString(List<Article> news) {
        StringBuilder builder = new StringBuilder();
        for (Article article : news) {
            builder.append(article.toReadableString()).append(System.lineSeparator());
        }
        return builder.toString();
    }

    private String toQueryString() {
        return this.category + this.country + this.keywords + this.pageSize;
    }

    public static class QueryBuilder {

        QueryExecutor queryExecutor = new QueryExecutor(HttpClient.newHttpClient());
        private String category = "";
        private String country = "";
        private final String keywords;
        private String pageSize = "&pageSize=50";

        public QueryBuilder(String... keywords) {
            Objects.requireNonNull(keywords);
            this.keywords = "&q=" + String.join("+", keywords);
        }

        public Query build() {
            return new Query(this);
        }

        public QueryBuilder key(String apiKey) {
            Objects.requireNonNull(apiKey);
            this.queryExecutor = new QueryExecutor(HttpClient.newHttpClient(), apiKey);
            return this;
        }

        public QueryBuilder executor(QueryExecutor queryExecutor) {
            Objects.requireNonNull(queryExecutor);
            this.queryExecutor = queryExecutor;
            return this;
        }

        public QueryBuilder category(String category) {
            Objects.requireNonNull(category);
            this.category = "&category=" + category;
            return this;
        }

        public QueryBuilder country(String country) {
            Objects.requireNonNull(country);
            this.country = "&country=" + country;
            return this;
        }

        public QueryBuilder pageSize(int pageSize) {
            if (pageSize < 1) {
                throw new IllegalArgumentException("Page size cannot be non-positive number");
            }
            this.pageSize = "&pageSize=" + pageSize;
            return this;
        }
    }
}