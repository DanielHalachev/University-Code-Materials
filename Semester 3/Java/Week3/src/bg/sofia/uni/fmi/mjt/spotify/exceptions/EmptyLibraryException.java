package bg.sofia.uni.fmi.mjt.spotify.exceptions;

public class EmptyLibraryException extends Exception {

    public EmptyLibraryException() {
    }

    public EmptyLibraryException(String message) {
        super(message);
    }

    public EmptyLibraryException(String message, Throwable cause) {
        super(message, cause);
    }
}
