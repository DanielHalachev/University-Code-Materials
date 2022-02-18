package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class PlaylistCapacityExceededException extends Exception {
    public PlaylistCapacityExceededException() {
    }

    public PlaylistCapacityExceededException(String message) {
        super(message);
    }

    public PlaylistCapacityExceededException(String message, Throwable cause) {
        super(message, cause);
    }
}
