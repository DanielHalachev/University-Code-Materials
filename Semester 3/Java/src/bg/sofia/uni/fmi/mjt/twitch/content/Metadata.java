package bg.sofia.uni.fmi.mjt.twitch.content;

import bg.sofia.uni.fmi.mjt.twitch.user.User;

// Since Metadata content isn't supposed to change, Metadata is a record
public record Metadata(String title, Category category, User streamer) {

}
