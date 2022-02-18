package api;

import bg.sofia.uni.fmi.mjt.news.feed.api.Article;
import bg.sofia.uni.fmi.mjt.news.feed.api.ErrorObject;
import bg.sofia.uni.fmi.mjt.news.feed.api.NewsCollection;
import bg.sofia.uni.fmi.mjt.news.feed.api.NewsSource;
import bg.sofia.uni.fmi.mjt.news.feed.api.QueryExecutor;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalKeyException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalParametersException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.IllegalSourcesException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.NewsFeedException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.RateLimitedException;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.ServerErrorException;
import com.google.gson.Gson;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentMatchers;
import org.mockito.Mock;
import org.mockito.Mockito;

import java.io.IOException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.when;

public class QueryExecutorTest {

    @Mock
    private static HttpClient newsHttpClientMock = Mockito.mock(HttpClient.class);

    @Mock
    private static HttpResponse<String> httpNewsResponseMock = Mockito.mock(HttpResponse.class);

    private static NewsCollection collection;
    private static final QueryExecutor queryExecutor = new QueryExecutor(newsHttpClientMock);
    private static final Gson gson = new Gson();

    @BeforeAll
    public static void setupArticles() {
        NewsSource s1 = new NewsSource("1", "bbc");
        NewsSource s2 = new NewsSource("2", "cnn");
        Article[] articles = new Article[2];
        articles[0] = (new Article(s1, "Author1", "News1", "Description1", "www.google.com", "www.bing.com", "2022/4/1", "Content1"));
        articles[1] = (new Article(s2, "Author2", "News2", "Description2", "www.youtube.com", "www.yahoo.com", "2022/3/1", "Content2"));
        collection = new NewsCollection("ok", 2, articles);
    }

    @Test
    void testGetNewsValidQuery() throws NewsFeedException, IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(200);
        String collectionJSON = gson.toJson(collection);
        when(httpNewsResponseMock.body()).thenReturn(collectionJSON);
        assertEquals(Arrays.stream(collection.getArticles()).toList(), queryExecutor.getNews("a query"),
                "Results from the method should be the same as the result of the API");
    }

    @Test
    void testGetNewsIllegalKeyException() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "apiKeyInvalid", "Missing API key");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(IllegalKeyException.class, () -> queryExecutor.getNews("a query"),
                "A problem with the API key should throw an IllegalKeyException");
    }

    @Test
    void testGetNewsIllegalParametersException() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "parameterInvalid", "Invalid parameter in your query");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(IllegalParametersException.class, () -> queryExecutor.getNews("a query"),
                "A problem with the parameters should throw an IllegalParameterException");
    }

    @Test
    void testGetNewsIllegalSourcesException() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "sourceDoesNotExist", "A non-existent source");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(IllegalSourcesException.class, () -> queryExecutor.getNews("a query"),
                "A problem with the news source should throw an IllegalSourcesException");
    }

    @Test
    void testGetNewsRateLimitedException() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "rateLimited", "Rate limit exceeded");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(RateLimitedException.class, () -> queryExecutor.getNews("a query"),
                "An exceeded limit for an API key should throw a RateLimitedException");
    }

    @Test
    void testGetNewsServerErrorException() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "unexpectedError", "Missing API key");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(ServerErrorException.class, () -> queryExecutor.getNews("a query"),
                "A server error should throw a ServerErrorException");
    }

    @Test
    void testGetNewsUnexpectedError() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(400);
        ErrorObject errorObject = new ErrorObject("error", "WhoAmI", "An undocumented error");
        when(httpNewsResponseMock.body()).thenReturn(gson.toJson(errorObject));
        assertThrows(NewsFeedException.class, () -> queryExecutor.getNews("a query"),
                "An unspecified error by the API should still throw a NewsFeedException, not the original " +
                        "or an unhandled exception");
    }

    @Test
    void testGetNewsSendExceptions() throws IOException, InterruptedException {
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenThrow(IOException.class);
        assertThrows(NewsFeedException.class, () -> queryExecutor.getNews("someQuery"),
                "A problem sending a request to the API should wrap the exception and throw a NewsFeedException");
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenThrow(InterruptedException.class);
        assertThrows(NewsFeedException.class, () -> new QueryExecutor(newsHttpClientMock, "abc").getNews("someQuery"),
                "A problem parsing the query URI should wrap the exception and throw a NewsFeedException");
    }
}
