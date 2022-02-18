package bg.sofia.uni.fmi.mjt.cocktail.server.storage;

import bg.sofia.uni.fmi.mjt.cocktail.server.Cocktail;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailAlreadyExistsException;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailNotFoundException;

import java.util.Collection;

public interface CocktailStorage {

    /**
     * Creates a new cocktail recipe
     *
     * @param cocktail cocktail
     * @throws CocktailAlreadyExistsException if the same cocktail already exists
     */
    void createCocktail(Cocktail cocktail) throws CocktailAlreadyExistsException;

    /**
     * Retrieves all cocktail recipes
     *
     * @return all cocktail recipes from the storage, in undefined order.
     * If there are no cocktails in the storage, returns an empty collection.
     */
    Collection<Cocktail> getCocktails();

    /**
     * Retrieves all cocktail recipes with given ingredient
     *
     * @param ingredientName name of the ingredient (case-insensitive)
     * @return all cocktail recipes with given ingredient from the storage, in undefined order.
     * If there are no cocktails in the storage with the given ingredient, returns an empty collection.
     */
    Collection<Cocktail> getCocktailsWithIngredient(String ingredientName);

    /**
     * Retrieves a cocktail recipe with the given name
     *
     * @param name cocktail name (case-insensitive)
     * @return cocktail with the given name
     * @throws CocktailNotFoundException if a cocktail with the given name does not exist in the storage
     */
    Cocktail getCocktail(String name) throws CocktailNotFoundException;
}