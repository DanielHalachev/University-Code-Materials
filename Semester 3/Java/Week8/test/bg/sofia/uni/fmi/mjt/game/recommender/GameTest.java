package bg.sofia.uni.fmi.mjt.game.recommender;

import org.junit.jupiter.api.Test;

import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.*;

public class GameTest {

    @Test
    void testOfIncorrectData() {
        assertThrows(IllegalArgumentException.class, () -> Game.of("Game1,Platform1,23Nov1998,GameDescription1,99,9.5\n"), "Incorrect Date should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> Game.of("Game1,Platform1,23-Nov-1998,GameDescription1,9.2,9.5\n"), "Incorrect meta score should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> Game.of("Game1,23Nov1998,GameDescription1,99,9.5\n"), "Missing field should throw IllegalArgumentException");
    }

    @Test
    void testOfCorrectData() {
        assertEquals(new Game("Game1", "Platform1", LocalDate.of(1998, 11, 23), "GameDescription1", 99, 9.5), Game.of("Game1,Platform1,23-Nov-1998,GameDescription1,99,9.5"));
    }
}
