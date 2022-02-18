package bg.sofia.uni.fmi.mjt.investment.wallet.exception;

public class OfferPriceException extends WalletException {
    public OfferPriceException() {
    }

    public OfferPriceException(String exceptionMessage) {
        super(exceptionMessage);
    }

    public OfferPriceException(String message, Throwable cause) {
        super(message, cause);
    }
}
