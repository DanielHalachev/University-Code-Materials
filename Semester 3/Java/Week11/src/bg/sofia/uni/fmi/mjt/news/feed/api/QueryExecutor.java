package bg.sofia.uni.fmi.mjt.news.feed.api;

import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalKeyException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalParametersException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalSourcesException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.NewsFeedException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.RateLimitedException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.ServerErrorException;
import com.google.gson.Gson;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

// the class, which would implement the connection between the server and the user
public class QueryExecutor {

    // please change this constant if you want
    // to use the builder with a default key, instead of your own
    private static final String API_KEY = "SOME_KEY";
    private static final String SCHEME = "https";
    private static final String HOST = "newsapi.org";
    private static final String API_ENDPOINT = "/v2/top-headlines";
    private static final int MAXIMUM_RESULTS = 100;
    private static final String QUERY_PAGE_PARAMETER = "&page=";

    private final HttpClient newsFeedClient;
    private final String apiKey;
    private final Gson gson;

    public QueryExecutor(HttpClient newsFeedClient) {
        this.newsFeedClient = newsFeedClient;
        this.apiKey = API_KEY;
        this.gson = new Gson();
    }

    public QueryExecutor(HttpClient newsFeedClient, String apiKey) {
        this.newsFeedClient = newsFeedClient;
        this.apiKey = apiKey;
        this.gson = new Gson();
    }

    public List<Article> getNews(String query) throws NewsFeedException {
        Objects.requireNonNull(query);

        HttpResponse<String> response;
        StringBuilder builder = new StringBuilder(query);
        int maximumResults = MAXIMUM_RESULTS; //100

        try {
            List<Article> news = new ArrayList<>();
            int pageNumber = 1;
            do {
                HttpRequest request = HttpRequest.newBuilder().uri(
                        new URI(SCHEME,
                                HOST,
                                API_ENDPOINT,
                                "apiKey=" + this.apiKey + builder,
                                null)).build();
                response = newsFeedClient.send(request, HttpResponse.BodyHandlers.ofString(StandardCharsets.UTF_8));

                // successful scenario
                if (response.statusCode() == HttpURLConnection.HTTP_OK) {
                    NewsCollection result = gson.fromJson(response.body(), NewsCollection.class);
                    maximumResults = Math.min(maximumResults, result.getTotalResults());
                    news.addAll(List.of(result.getArticles()));
                    pageNumber++;
                    builder = new StringBuilder(query).append(QUERY_PAGE_PARAMETER).append(pageNumber);
                } else { //unsuccessful scenario

                    ErrorObject error = gson.fromJson(response.body(), ErrorObject.class);
                    throw switch (error.getCode()) {
                        case ErrorObject.API_KEY_DISABLED,
                                ErrorObject.API_KEY_EXHAUSTED,
                                ErrorObject.API_KEY_INVALID,
                                ErrorObject.API_KEY_MISSING -> new IllegalKeyException(error.getMessage());
                        case ErrorObject.PARAMETER_INVALID,
                                ErrorObject.PARAMETERS_MISSING -> new IllegalParametersException(error.getMessage());
                        case ErrorObject.RATE_LIMITED -> new RateLimitedException(error.getMessage());
                        case ErrorObject.SOURCE_DOES_NOT_EXIST,
                                ErrorObject.SOURCES_TOO_MANY -> new IllegalSourcesException(error.getMessage());
                        case ErrorObject.UNEXPECTED_ERROR -> new ServerErrorException(error.getMessage());
                        default -> new NewsFeedException(error.getMessage());
                    };
                }
            }
            while (pageNumber < 2 || news.size() < maximumResults);

            // now news contains the maximum number of results that we can get
            return news;
        } catch (URISyntaxException e) {
            throw new NewsFeedException("There was an error converting the query to URI:" + e.getMessage());
        } catch (IOException | InterruptedException e) {
            throw new NewsFeedException("There was an error sending the request to the API:" + e.getMessage());
        }
    }
}
