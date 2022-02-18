package bg.sofia.uni.fmi.mjt.cocktail.server;

public record Ingredient(String name, String amount) {

    @Override
    public String toString() {
        return String.format("{\"name\":\"%S\",\"amount\":\"%s\"}", this.name, this.amount);
    }
}
