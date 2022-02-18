package bg.sofia.uni.fmi.mjt.news.feed.exceptions;

public class RateLimitedException extends NewsFeedException {

    public RateLimitedException(String message) {
        super(message);
    }
}
