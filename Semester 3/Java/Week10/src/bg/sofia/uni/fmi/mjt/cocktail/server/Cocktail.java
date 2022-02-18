package bg.sofia.uni.fmi.mjt.cocktail.server;

import java.util.Set;

public record Cocktail(String name, Set<Ingredient> ingredients) {

    @Override
    public String toString() {
        return String.format("{\"name\":\"%s\",\"ingredients\":%s}", this.name, this.ingredients.toString());
    }
}
