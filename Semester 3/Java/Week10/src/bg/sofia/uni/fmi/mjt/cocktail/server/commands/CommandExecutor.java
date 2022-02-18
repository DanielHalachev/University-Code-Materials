package bg.sofia.uni.fmi.mjt.cocktail.server.commands;

import bg.sofia.uni.fmi.mjt.cocktail.server.Cocktail;
import bg.sofia.uni.fmi.mjt.cocktail.server.Ingredient;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.CocktailStorage;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailAlreadyExistsException;
import bg.sofia.uni.fmi.mjt.cocktail.server.storage.exceptions.CocktailNotFoundException;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class CommandExecutor {

    public static final String STATUS_OK_COCKTAILS = "\"status\":\"OK\",\"cocktails\":";
    public static final String STATUS_ERROR = "\"status\":\"ERROR\",\"errorMessage\":";
    public static final String UNKNOWN_COMMAND = "Unknown command";
    public static final String STATUS_CREATED = "\"status\":\"CREATED\"";

    private final CocktailStorage storage;

    public CommandExecutor(CocktailStorage storage) {
        this.storage = storage;
    }

    public String execute(String cmd) {
        String[] commandAndArguments = cmd.split(" ");
        if (commandAndArguments[0].equals("create")) {
            return create(commandAndArguments[1], Arrays.stream(commandAndArguments)
                    .skip(2)
                    .toList()
                    .toArray(new String[0]));
        } else if (commandAndArguments[0].equals("get")) {
            return get(Arrays.stream(commandAndArguments)
                    .skip(1)
                    .toList()
                    .toArray(new String[0]));
        } else {
            return UNKNOWN_COMMAND;
        }
    }

    private String get(String[] args) {
        if (args.length == 1 && args[0].equals("all")) {
            return "{" + STATUS_OK_COCKTAILS + this.storage.getCocktails().toString() + "}";
        } else if (args.length > 1 && args[0].equals("by-name")) {
            try {
                return String.format("{%s%s}", STATUS_OK_COCKTAILS, this.storage.getCocktail(args[1]).toString());
            } catch (CocktailNotFoundException e) {
                return String.format("{%s\"%s\"}", STATUS_ERROR, e.getMessage());
            }
        } else if (args.length > 1 && args[0].equals("by-ingredient")) {
            return String.format("{%s%s}", STATUS_OK_COCKTAILS,
                    this.storage.getCocktailsWithIngredient(args[1]).toString());
        } else {
            return UNKNOWN_COMMAND;
        }
    }

    private String create(String name, String[] ingredients) {
        Set<Ingredient> ingredientSet = new HashSet<>();
        for (String ingredient : ingredients) {
            String[] nameAndQuantity = ingredient.split("=");
            ingredientSet.add(new Ingredient(nameAndQuantity[0], nameAndQuantity[1]));
        }
        Cocktail newCocktail = new Cocktail(name, ingredientSet);
        try {
            this.storage.createCocktail(newCocktail);
            return String.format("{%s}", STATUS_CREATED);
        } catch (CocktailAlreadyExistsException e) {
            return String.format("{%s\"%s\"}", STATUS_ERROR, e.getMessage());
        }
    }
}