package api;

import bg.sofia.uni.fmi.mjt.news.feed.api.Article;
import bg.sofia.uni.fmi.mjt.news.feed.api.NewsCollection;
import bg.sofia.uni.fmi.mjt.news.feed.api.NewsSource;
import bg.sofia.uni.fmi.mjt.news.feed.api.Query;
import bg.sofia.uni.fmi.mjt.news.feed.api.QueryExecutor;
import bg.sofia.uni.fmi.mjt.news.feed.exceptions.NewsFeedException;
import com.google.gson.Gson;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentMatchers;
import org.mockito.Mock;
import org.mockito.Mockito;

import java.io.IOException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.when;

public class QueryTest {


    @Mock
    private static final HttpClient newsHttpClientMock = Mockito.mock(HttpClient.class);

    @Mock
    private static final HttpResponse<String> httpNewsResponseMock = Mockito.mock(HttpResponse.class);

    @Test
    void testQuery() throws NewsFeedException, IOException, InterruptedException {
        Gson gson = new Gson();
        NewsSource source = new NewsSource("1", "bbc");
        Article article = new Article(source,
                "Author1",
                "News1",
                "Description1",
                "www.google.com",
                "www.bing.com",
                "2022/4/1",
                "Content1");
        List<Article> articleList = new ArrayList<>();
        articleList.add(article);
        NewsCollection collection = new NewsCollection("ok", 1, new Article[]{article});
        when(newsHttpClientMock.send(any(HttpRequest.class), ArgumentMatchers.<HttpResponse.BodyHandler<String>>any())).thenReturn(httpNewsResponseMock);
        when(httpNewsResponseMock.statusCode()).thenReturn(200);
        String s = gson.toJson(collection);
        when(httpNewsResponseMock.body()).thenReturn(s);
        QueryExecutor executor = new QueryExecutor(newsHttpClientMock);
        String[] keywords = new String[2];
        keywords[0] = "hello";
        keywords[1] = "world";
        Query q = new Query.QueryBuilder(keywords).category("health").key("someKey").executor(executor).country("de").pageSize(100).build();
        q.ask();
        assertEquals(articleList, q.ask());
        assertEquals(article.toReadableString() + System.lineSeparator(), q.askForString());
    }

    @Test
    void testPatternIllegalParameterPageSize() {
        assertThrows(IllegalArgumentException.class, () -> new Query.QueryBuilder("hello").pageSize(-1).build(),
                "Non-positive number of pages parameter in method pageSize() should throw an exception");
    }
}
