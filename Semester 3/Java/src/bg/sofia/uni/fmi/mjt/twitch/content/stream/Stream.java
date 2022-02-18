package bg.sofia.uni.fmi.mjt.twitch.content.stream;

import bg.sofia.uni.fmi.mjt.twitch.content.Content;

import java.time.Duration;

public interface Stream extends Content {

    /**
     * Returns the {@link Duration} duration of time
     * passed between the creation of the Stream
     * and the time of calling the method.
     *
     * @return the {@link Duration} of the content
     */
    @Override
    Duration getDuration();
}
