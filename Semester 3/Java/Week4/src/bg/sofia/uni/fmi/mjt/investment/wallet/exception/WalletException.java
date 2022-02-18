package bg.sofia.uni.fmi.mjt.investment.wallet.exception;

public class WalletException extends Exception {
    public WalletException() {
    }

    public WalletException(String exceptionMessage) {
        super(exceptionMessage);
    }

    public WalletException(String message, Throwable cause) {
        super(message, cause);
    }
}
