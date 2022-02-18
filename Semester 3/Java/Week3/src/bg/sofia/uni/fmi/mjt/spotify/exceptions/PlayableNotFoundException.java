package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class PlayableNotFoundException extends Exception {
    public PlayableNotFoundException() {
    }

    public PlayableNotFoundException(String message) {
        super(message);
    }

    public PlayableNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }
}
