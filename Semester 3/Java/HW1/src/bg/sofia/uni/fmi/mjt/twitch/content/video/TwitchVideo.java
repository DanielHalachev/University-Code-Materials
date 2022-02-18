package bg.sofia.uni.fmi.mjt.twitch.content.video;

import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.content.TwitchContent;

import java.time.Duration;

public class TwitchVideo extends TwitchContent implements Video {

    Duration duration;

    public TwitchVideo(Metadata metadata, Duration duration) {
        super(metadata);
        this.duration = duration;
    }

    @Override
    public Duration getDuration() {
        return this.duration;
    }
}
