package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class PlaylistNotFoundException extends Exception {
    public PlaylistNotFoundException() {
    }

    public PlaylistNotFoundException(String message) {
        super(message);
    }

    public PlaylistNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }
}
