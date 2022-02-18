package bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions;

public class CocktailNotFoundException extends Exception {

    public CocktailNotFoundException() {
    }

    public CocktailNotFoundException(String message) {
        super(message);
    }

    public CocktailNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }
}
