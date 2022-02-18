package bg.sofia.uni.fmi.mjt.twitch.user.service;

import bg.sofia.uni.fmi.mjt.twitch.user.TwitchUser;
import bg.sofia.uni.fmi.mjt.twitch.user.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TwitchUserServiceTest {

    private Map<String, User> users;
    private UserService service;

    @BeforeEach
    void setupService() {
        this.users = new HashMap<>();
        String userName1 = "user1";
        String userName2 = "user2";
        User user1 = new TwitchUser(userName1);
        User user2 = new TwitchUser(userName2);
        this.users.put(userName1, user1);
        this.users.put(userName2, user2);
        this.service = new TwitchUserService(this.users);
    }

    @Test
    void testGetUser() {
        assertEquals(this.users, new HashMap<>(this.service.getUsers()));
    }
}
