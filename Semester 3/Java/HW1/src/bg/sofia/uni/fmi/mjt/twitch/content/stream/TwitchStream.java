package bg.sofia.uni.fmi.mjt.twitch.content.stream;

import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.content.TwitchContent;
import bg.sofia.uni.fmi.mjt.twitch.user.User;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


public class TwitchStream extends TwitchContent implements Stream {

    private final LocalDateTime timeOfCreation;
    private final List<User> currentlyWatching;

    public TwitchStream(Metadata metadata) {
        super(metadata);
        this.timeOfCreation = LocalDateTime.now();
        this.currentlyWatching = new ArrayList<>();
    }

    @Override
    public Duration getDuration() {
        return Duration.between(this.timeOfCreation, LocalDateTime.now());
    }

    @Override
    public void startWatching(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User is null. Cannot start watching");
        }
        // it was said that we allow multiple simultaneous views of a stream
        this.currentlyWatching.add(user);
        this.numberOfViews++;
    }

    @Override
    public void stopWatching(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User is null. Cannot stop watching");
        }
        // cannot make a user stop watching, if they already don't
        if (this.currentlyWatching.contains(user)) {
            this.numberOfViews--;
            this.currentlyWatching.remove(user);
        }
    }
}
