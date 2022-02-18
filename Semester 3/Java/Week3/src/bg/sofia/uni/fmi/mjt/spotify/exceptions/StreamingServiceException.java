package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class StreamingServiceException extends Exception {
    public StreamingServiceException() {
    }

    public StreamingServiceException(String message) {
        super(message);
    }

    public StreamingServiceException(String message, Throwable cause) {
        super(message, cause);
    }
}
