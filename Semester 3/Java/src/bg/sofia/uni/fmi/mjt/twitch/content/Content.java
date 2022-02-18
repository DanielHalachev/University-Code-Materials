package bg.sofia.uni.fmi.mjt.twitch.content;

import bg.sofia.uni.fmi.mjt.twitch.user.User;

import java.time.Duration;

public interface Content {

    /**
     * Returns the {@link Metadata} of the content.
     *
     * @return the {@link Metadata} of the content
     */
    Metadata getMetadata();

    /**
     * Returns the {@link Duration} of the content.
     *
     * @return the {@link Duration} of the content
     */
    Duration getDuration();

    /**
     * {@link User} starts watching the content.
     *
     * @param user which starts watching the content
     */
    void startWatching(User user);

    /**
     * {@link User} stops watching the content.
     *
     * @param user which stops watching the content
     */
    void stopWatching(User user);

    /**
     * Returns the number of views of the content.
     *
     * @return the number of views of the content
     */
    int getNumberOfViews();
}