package bg.sofia.uni.fmi.mjt.twitch;

import bg.sofia.uni.fmi.mjt.twitch.content.Category;
import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.content.stream.Stream;
import bg.sofia.uni.fmi.mjt.twitch.content.stream.TwitchStream;
import bg.sofia.uni.fmi.mjt.twitch.content.video.Video;
import bg.sofia.uni.fmi.mjt.twitch.user.*;
import bg.sofia.uni.fmi.mjt.twitch.user.service.TwitchUserService;
import bg.sofia.uni.fmi.mjt.twitch.user.service.UserService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

public class TwitchTest {

    private final String user1Name = "user1";
    private final String user2Name = "user2";
    private final String user3Name = "user3";

    private User user1;
    private User user2;
    private User user3;
    private StreamingPlatform twitch;

    @BeforeEach
    void setup() {
        Map<String, User> users = new HashMap<>();
        this.user1 = new TwitchUser(this.user1Name);
        this.user2 = new TwitchUser(this.user2Name);
        this.user3 = new TwitchUser(this.user3Name);
        users.put(this.user1Name, this.user1);
        users.put(this.user2Name, this.user2);
        users.put(this.user3Name, this.user3);
        UserService service = new TwitchUserService(users);
        this.twitch = new Twitch(service);
    }

    @Test
    void testStartStreamParametersAreNull() {
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream(null, "title", Category.GAMES), "Null parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream("user", null, Category.GAMES), "Null parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream("user", "title", null), "Null parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream(null, null, null), "Null parameters should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream("", "title", Category.GAMES), "Empty parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.startStream("user", "", Category.GAMES), "Empty parameter should throw exception");
    }

    @Test
    void testStartStreamingUserNotFound() {
        assertThrows(UserNotFoundException.class, () -> this.twitch.startStream("non-existing", "title", Category.GAMES), "Starting a stream by a non-existing user should throw UserNotFoundException");
    }

    @Test
    void testStartStreamingUserStreaming() throws UserNotFoundException, UserStreamingException {
        this.twitch.startStream(this.user1Name, "title1", Category.GAMES);
        assertThrows(UserStreamingException.class, () -> this.twitch.startStream(this.user1Name, "title2", Category.GAMES), "Starting a stream by a streaming user should throw UserStreamingException");
    }

    @Test
    void testStartStreamingCorrectData() throws UserNotFoundException, UserStreamingException {
        Metadata metadata = new Metadata("Title", Category.GAMES, this.user1);
        Stream stream = new TwitchStream(metadata);
        assertEquals(stream.getMetadata(), this.twitch.startStream(this.user1Name, "Title", Category.GAMES).getMetadata(), "Method startStream should start stream correctly");
        assertEquals(UserStatus.STREAMING, this.user1.getStatus(), "Streamer status should be set to STREAMING");
    }

    @Test
    void testEndStreamParametersAreNull() {
        assertThrows(IllegalArgumentException.class, () -> this.twitch.endStream(null, null), "Null parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.endStream("user", null), "Null parameter should throw exception");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.endStream("", null), "Empty parameter should throw exception");
    }

    @Test
    void testEndStreamUserNotFound() {
        Stream stream = new TwitchStream(new Metadata("Stream", Category.GAMES, this.user1));
        assertThrows(UserNotFoundException.class, () -> this.twitch.endStream("non-existing", stream), "Ending a stream by a non-existing user should throw UserNotFoundException");
    }

    @Test
    void testEndStreamUserNotStreaming() {
        Stream stream = new TwitchStream(new Metadata("Stream", Category.GAMES, this.user1));
        this.user1.setStatus(UserStatus.OFFLINE);
        assertThrows(UserStreamingException.class, () -> this.twitch.endStream(this.user1Name, stream), "Ending a stream by a non-streaming user should throw UserStreamingException");
    }

    @Test
    void testEndStreamCorrectData() throws UserNotFoundException, UserStreamingException {
        Stream stream = this.twitch.startStream(user1Name, "title", Category.GAMES);
        assertEquals(stream.getMetadata(), this.twitch.endStream(this.user1Name, stream).getMetadata(), "Method startStream should start stream correctly");
        assertEquals(UserStatus.OFFLINE, this.user1.getStatus(), "Streamer status should be set to STREAMING");
    }

    @Test
    void testWatchIncorrectData() throws UserNotFoundException, UserStreamingException {
        Stream stream = this.twitch.startStream(this.user1Name, "title", Category.GAMES);
        assertThrows(IllegalArgumentException.class, () -> this.twitch.watch(null, stream), "Null parameter should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.watch(this.user1Name, null), "Null parameter should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.watch("", stream), "Empty parameter should throw IllegalArgumentException");
        assertThrows(UserNotFoundException.class, () -> this.twitch.watch("non-existent", stream), "Non-existent user should throw IllegalArgumentException");
        assertThrows(UserStreamingException.class, () -> this.twitch.watch(this.user1Name, stream), "User already streaming cannot watch");
    }

    @Test
    void testWatchCorrectData() throws UserNotFoundException, UserStreamingException {
        Stream stream = this.twitch.startStream(this.user1Name, "Stream", Category.GAMES);
        this.twitch.watch(this.user2Name, stream);
        List<Category> expectedMostWatchedCategories = new ArrayList<>();
        expectedMostWatchedCategories.add(Category.GAMES);
        assertEquals(expectedMostWatchedCategories, this.twitch.getMostWatchedCategoriesBy(this.user2Name),
                "If user has watched only one video, the category of the video should be returned when calling getMostWatchedCategry");
        assertEquals(1, stream.getNumberOfViews(), "After a content has been watched by one user, its views must be 1");
        assertEquals(stream, this.twitch.getMostWatchedContent(),
                "If there is only one stream in Twitch and it has been watched only once, it should be the MostWatchedContent");
    }

    @Test
    void testGetMostWatchedStreamer() throws UserNotFoundException, UserStreamingException {
        assertNull(this.twitch.getMostWatchedStreamer(), "Empty Twitch should have no most watched streamer");
        Stream stream1 = this.twitch.startStream(this.user1Name, "Stream1", Category.GAMES);
        this.twitch.watch(this.user2Name, stream1);
        this.twitch.watch(this.user3Name, stream1);
        Stream stream2 = this.twitch.startStream(this.user2Name, "Stream2", Category.GAMES);
        this.twitch.watch(this.user3Name, stream1);
        assertEquals(this.user1, this.twitch.getMostWatchedStreamer(), "When user1 has two views and user2 has 1 view, user1 should be the most watched streamer");
    }

    @Test
    void testGetMostWatchedContentFromIncorrectData() {
        assertThrows(IllegalArgumentException.class, () -> this.twitch.getMostWatchedContentFrom(null),
                "Calling getMostWatchedContentFrom for null user should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.getMostWatchedContentFrom(""),
                "Calling getMostWatchedContentFrom for empty user should throw IllegalArgumentException");
        assertThrows(UserNotFoundException.class, () -> this.twitch.getMostWatchedContentFrom("non-existent"),
                "Calling getMostWatchedContentFrom for non-existent user should throw IllegalArgumentException");
    }

    @Test
    void testGetMostWatchedContentFromCorrectDataStream() throws UserNotFoundException, UserStreamingException {
        assertNull(this.twitch.getMostWatchedContentFrom(this.user1Name), "Getting mostWatchedContentFrom a user without content should return null");
        Stream s1 = this.twitch.startStream(this.user1Name, "Content1", Category.GAMES);
        Stream s2 = this.twitch.startStream(this.user2Name, "Content2", Category.GAMES);
        this.twitch.watch(this.user3Name, s1);
        assertEquals(s1, this.twitch.getMostWatchedContent());
    }

    @Test
    void testGetMostWatchedContentFromCorrectDataVideo1() throws UserNotFoundException, UserStreamingException {
        Stream s1 = this.twitch.startStream(this.user1Name, "Content1", Category.GAMES);
        Stream s2 = this.twitch.startStream(this.user2Name, "Content2", Category.GAMES);
        assertEquals(UserStatus.STREAMING, this.user1.getStatus());
        Video video1 = this.twitch.endStream(this.user1Name, s1);
        Video video2 = this.twitch.endStream(this.user2Name, s2);
        this.twitch.watch(this.user3Name, video1);
        assertEquals(video1, this.twitch.getMostWatchedContent());
    }

    @Test
    void testGetMostWatchedContentFromCorrectData2() throws UserNotFoundException, UserStreamingException {
        Stream stream1 = this.twitch.startStream(this.user1Name, "Stream1", Category.GAMES);
        this.twitch.watch(this.user2Name, stream1);
        this.twitch.watch(this.user3Name, stream1);
        Stream stream2 = this.twitch.startStream(this.user2Name, "Stream2", Category.GAMES);
        this.twitch.watch(this.user3Name, stream1);
        assertEquals(stream1, this.twitch.getMostWatchedContentFrom(user1Name), "When user1 has two views and user2 has 1 view, user1 should be the most watched streamer");
    }

    @Test
    void testGetMostWatchedCategoriesByIncorrectData() {
        assertThrows(IllegalArgumentException.class, () -> this.twitch.getMostWatchedCategoriesBy(""),
                "Calling method with empty username should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.twitch.getMostWatchedCategoriesBy(null),
                "Calling method with null username should throw IllegalArgumentException");
        assertThrows(UserNotFoundException.class, () -> this.twitch.getMostWatchedCategoriesBy("non-existing"),
                "Calling method with non-existent username should throw IllegalArgumentException");
    }
}
