package bg.sofia.uni.fmi.mjt.twitch.content.video;

import bg.sofia.uni.fmi.mjt.twitch.content.Content;

import java.time.Duration;

public interface Video extends Content {

    /**
     * Returns the {@link Duration} of the content, as specified in the constructor.
     *
     * @return the {@link Duration} of the content
     */
    @Override
    Duration getDuration();
}
