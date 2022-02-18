package bg.sofia.uni.fmi.mjt.investment.wallet.exception;

public class InsufficientResourcesException extends WalletException {
    public InsufficientResourcesException() {
    }

    public InsufficientResourcesException(String exceptionMessage) {
        super(exceptionMessage);
    }

    public InsufficientResourcesException(String message, Throwable cause) {
        super(message, cause);
    }
}
