package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class LibraryCapacityExceededException extends Exception {
    public LibraryCapacityExceededException() {
    }

    public LibraryCapacityExceededException(String message) {
        super(message);
    }


    public LibraryCapacityExceededException(String message, Throwable cause) {
        super(message, cause);
    }
}
