package bg.sofia.uni.fmi.mjt.news.feed.exceptions;

public class ServerErrorException extends NewsFeedException {

    public ServerErrorException(String message) {
        super(message);
    }
}
