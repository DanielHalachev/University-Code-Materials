package bg.sofia.uni.fmi.mjt.twitch.content;

import bg.sofia.uni.fmi.mjt.twitch.user.User;

import java.util.Objects;

public abstract class TwitchContent implements Content {

    protected final Metadata metadata;
    protected int numberOfViews = 0;

    public TwitchContent(Metadata metadata) {
        this.metadata = metadata;
    }

    @Override
    public Metadata getMetadata() {
        return this.metadata;
    }

    @Override
    public void startWatching(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User is null. Cannot watch");
        }
        this.numberOfViews++;
    }

    @Override
    public void stopWatching(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User is null. Cannot stop watching");
        }
    }

    @Override
    public int getNumberOfViews() {
        return this.numberOfViews;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TwitchContent that = (TwitchContent) o;
        return getNumberOfViews() == that.getNumberOfViews() && getMetadata().equals(that.getMetadata());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getMetadata(), getNumberOfViews());
    }
}
