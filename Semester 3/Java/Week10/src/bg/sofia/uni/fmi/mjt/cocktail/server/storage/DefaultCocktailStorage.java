package bg.sofia.uni.fmi.mjt.cocktail.server.storage;

import bg.sofia.uni.fmi.mjt.cocktail.server.Cocktail;
import bg.sofia.uni.fmi.mjt.cocktail.server.Ingredient;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailAlreadyExistsException;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailNotFoundException;

import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.stream.Collectors;

public class DefaultCocktailStorage implements CocktailStorage {

    Set<Cocktail> cocktails;

    public DefaultCocktailStorage() {
        this.cocktails = new HashSet<>();
    }

    @Override
    public void createCocktail(Cocktail cocktail) throws CocktailAlreadyExistsException {
        Objects.requireNonNull(cocktail);
        if (this.cocktails.contains(cocktail)) {
            throw new CocktailAlreadyExistsException("Cocktail " + cocktail.name() + " already exists");
        }
        this.cocktails.add(cocktail);
    }

    @Override
    public Collection<Cocktail> getCocktails() {
        return this.cocktails;
    }

    @Override
    public Collection<Cocktail> getCocktailsWithIngredient(String ingredientName) {
        return this.cocktails.stream()
                .filter(cocktail -> cocktail.ingredients().stream()
                        .map(Ingredient::name)
                        .collect(Collectors.toSet())
                        .contains(ingredientName))
                .toList();
    }

    @Override
    public Cocktail getCocktail(String name) throws CocktailNotFoundException {
        Map<String, Cocktail> map = this.cocktails.stream()
                .collect(Collectors.toMap(Cocktail::name, cocktail -> cocktail));
        if (!map.containsKey(name)) {
            throw new CocktailNotFoundException("Cocktail " + name + " not found");
        }
        return map.get(name);
    }
}
