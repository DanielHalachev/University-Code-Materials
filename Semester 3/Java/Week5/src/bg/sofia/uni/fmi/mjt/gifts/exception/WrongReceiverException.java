package bg.sofia.uni.fmi.mjt.gifts.exception;

public class WrongReceiverException extends RuntimeException {

    public WrongReceiverException() {
    }

    public WrongReceiverException(String message) {
        super(message);
    }

    public WrongReceiverException(String message, Throwable cause) {
        super(message, cause);
    }
}
