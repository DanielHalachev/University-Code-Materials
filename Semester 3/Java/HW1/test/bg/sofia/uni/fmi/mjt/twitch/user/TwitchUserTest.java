package bg.sofia.uni.fmi.mjt.twitch.user;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TwitchUserTest {

    private final String username = "user1";
    private final User user = new TwitchUser(this.username);

    @Test
    void testSetStatusNull() {
        assertThrows(IllegalArgumentException.class, () -> this.user.setStatus(null),
                "Setting null as status should throw new IllegalArgumentException");
    }

    @Test
    void testSetStatus() {
        UserStatus status = UserStatus.STREAMING;
        this.user.setStatus(status);
        assertEquals(status, this.user.getStatus(), "User status should be correctly set");
    }
}
