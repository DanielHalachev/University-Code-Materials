package bg.sofia.uni.fmi.mjt.twitch.content.video;

import bg.sofia.uni.fmi.mjt.twitch.content.Category;
import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.user.TwitchUser;
import bg.sofia.uni.fmi.mjt.twitch.user.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.*;

public class TwitchVideoTest {

    private final User streamer = new TwitchUser("user");
    private final Metadata metadata = new Metadata("title", Category.GAMES, this.streamer);
    private final Duration duration = Duration.ofSeconds(150);

    private Video video;

    @BeforeEach
    void setup() {
        this.video = new TwitchVideo(this.metadata, this.duration);
    }

    @Test
    void testStartWatchingNullUser() {
        assertThrows(IllegalArgumentException.class, () -> this.video.startWatching(null),
                "Calling method startWatching for null user should throw an IllegalArgumentException");
    }

    @Test
    void testStartWatchingNonNullUser() {
        User watcher = new TwitchUser("watcher");
        this.video.startWatching(watcher);
        assertEquals(1, this.video.getNumberOfViews(), "A user watching the video should increment the number of views");
    }

    @Test
    void testStopWatchingNullUser() {
        assertThrows(IllegalArgumentException.class, () -> this.video.stopWatching(null),
                "Calling method stopWatching for null user should throw an IllegalArgumentException");
    }

    @Test
    void testGetDuration() {
        assertEquals(this.duration, this.video.getDuration());
    }
}
