package bg.sofia.uni.fmi.mjt.twitch.user;

import java.util.Objects;

public class TwitchUser implements User {

    private final String name;
    private UserStatus status;

    public TwitchUser(String name) {
        this.name = name;
        this.status = UserStatus.OFFLINE;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public UserStatus getStatus() {
        return this.status;
    }

    @Override
    public void setStatus(UserStatus status) {
        if (status == null) {
            throw new IllegalArgumentException("Status is null. Cannot set it.");
        }
        this.status = status;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TwitchUser that = (TwitchUser) o;
        return getName().equals(that.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName());
    }
}
