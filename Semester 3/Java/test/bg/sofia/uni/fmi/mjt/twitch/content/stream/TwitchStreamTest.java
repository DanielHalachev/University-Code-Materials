package bg.sofia.uni.fmi.mjt.twitch.content.stream;

import bg.sofia.uni.fmi.mjt.twitch.content.Category;
import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.user.TwitchUser;
import bg.sofia.uni.fmi.mjt.twitch.user.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TwitchStreamTest {

    private final User streamer = new TwitchUser("user");
    private final Metadata metadata = new Metadata("title", Category.GAMES, this.streamer);
    private Stream stream;

    @BeforeEach
    void setup() {
        this.stream = new TwitchStream(this.metadata);
    }

    @Test
    void testStartWatchingNullUser() {
        assertThrows(IllegalArgumentException.class, () -> this.stream.startWatching(null),
                "Calling method startWatching for null user should throw an IllegalArgumentException");
    }

    @Test
    void testStartWatchingNonNullUser() {
        User watcher = new TwitchUser("watcher");
        this.stream.startWatching(watcher);
        assertEquals(1, this.stream.getNumberOfViews(), "A user watching the stream should increment the number of views");
    }

    @Test
    void testStopWatchingNullUser() {
        assertThrows(IllegalArgumentException.class, () -> this.stream.stopWatching(null),
                "Calling method stopWatching for null user should throw an IllegalArgumentException");
    }

    @Test
    void testStopWatchingNonNullUser() {
        User fake = new TwitchUser("Mr. Fake");
        this.stream.startWatching(fake);
        this.stream.stopWatching(fake);
        assertEquals(0, this.stream.getNumberOfViews());
    }
}
