package bg.sofia.uni.fmi.mjt.twitch;

import bg.sofia.uni.fmi.mjt.twitch.content.Category;
import bg.sofia.uni.fmi.mjt.twitch.content.Content;
import bg.sofia.uni.fmi.mjt.twitch.content.Metadata;
import bg.sofia.uni.fmi.mjt.twitch.content.stream.Stream;
import bg.sofia.uni.fmi.mjt.twitch.content.stream.TwitchStream;
import bg.sofia.uni.fmi.mjt.twitch.content.video.TwitchVideo;
import bg.sofia.uni.fmi.mjt.twitch.content.video.Video;
import bg.sofia.uni.fmi.mjt.twitch.user.User;
import bg.sofia.uni.fmi.mjt.twitch.user.UserNotFoundException;
import bg.sofia.uni.fmi.mjt.twitch.user.UserStatus;
import bg.sofia.uni.fmi.mjt.twitch.user.UserStreamingException;
import bg.sofia.uni.fmi.mjt.twitch.user.service.UserService;

import java.util.*;

public class Twitch implements StreamingPlatform {

    // Twitch Users will be stored here
    private final UserService userService;
    // Twitch Content will be stored here
    private final List<Content> twitchContent;
    // Twitch viewed Categories by users will be stored here
    // each user will have a map of Categories and corresponding values to them
    private final Map<User, Map<Category, Integer>> viewedCategories;

    public Twitch(UserService userService) {
        this.userService = userService;
        this.twitchContent = new LinkedList<>();
        this.viewedCategories = new HashMap<>();
    }

    @Override
    public Stream startStream(String username, String title, Category category)
            throws UserNotFoundException, UserStreamingException {
        if (username == null || title == null || category == null) {
            throw new IllegalArgumentException("The username, title or category is null. Cannot create Stream");
        }
        if (username.equals("") || title.equals("")) {
            throw new IllegalArgumentException("Empty username or title. Cannot create Stream");
        }
        User streamer = this.userService.getUsers().get(username);
        if (streamer == null) {
            throw new UserNotFoundException("User " + username + " does not exist in the Twitch User Service");
        }
        if (streamer.getStatus() == UserStatus.STREAMING) {
            throw new UserStreamingException("User " + username + " is already streaming. Cannot start new stream");
        }
        // set status of streamer to STREAMING
        streamer.setStatus(UserStatus.STREAMING);
        // create Metadata of Stream
        Metadata streamMetadata = new Metadata(title, category, streamer);
        // create Stream
        Stream stream = new TwitchStream(streamMetadata);
        // add the Stream to the platform
        this.twitchContent.add(stream);
        return stream;
    }

    @Override
    public Video endStream(String username, Stream stream) throws UserNotFoundException, UserStreamingException {
        if (username == null || stream == null) {
            throw new IllegalArgumentException("Username or stream is null. Cannot stop stream");
        }
        if (username.equals("")) {
            throw new IllegalArgumentException("Username is empty. Cannot stop stream");
        }
        User user = this.userService.getUsers().get(username);
        if (user == null) {
            throw new UserNotFoundException(
                    "Specified user " + username + " does not exist in Twitch User Service. Cannot stop stream");
        }
        if (user.getStatus() != UserStatus.STREAMING) {
            throw new UserStreamingException(
                    "Specified user " + username + " isn't currently streaming. Cannot end stream");
        }
        // create a video by using the Metadata of the stream and its duration
        TwitchVideo video = new TwitchVideo(stream.getMetadata(), stream.getDuration());
        // replace the stream with the video
        this.twitchContent.remove(stream);
        this.twitchContent.add(video);
        // set the status of the streamer to OFFLINE
        user.setStatus(UserStatus.OFFLINE);
        // return the video
        return video;
    }

    @Override
    public void watch(String username, Content content) throws UserNotFoundException, UserStreamingException {
        if (username == null || content == null) {
            throw new IllegalArgumentException("Username or content is null. Cannot watch");
        }
        if (username.equals("")) {
            throw new IllegalArgumentException("Username is empty. Cannot watch");
        }
        User watcher = this.userService.getUsers().get(username);
        if (watcher == null) {
            throw new UserNotFoundException("User " + username + " does not exist in this User Service");
        }
        if (watcher.getStatus() == UserStatus.STREAMING) {
            throw new UserStreamingException("User " + username + " is already streaming");
        }
        // fill the category register of the user, who is watching
        Category category = content.getMetadata().category();
        // if the user has already seen content
        // this means his Map already exists
        if (this.viewedCategories.containsKey(watcher)) {
            Map<Category, Integer> userCategories = this.viewedCategories.get(watcher);
            // in case they have already seen a content of a particular category
            // we will have to update the entry
            if (userCategories.containsKey(category)) {
                userCategories.put(category, userCategories.get(category) + 1);
            }
            // otherwise, we will have to create the entry for that category from scratch
            else {
                userCategories.put(category, 1);
            }
        }
        // if the user hasn't seen any content yet
        else {
            // we will create an entry for him in ViewedCategories
            this.viewedCategories.put(watcher, new HashMap<>());
            // and in the value of this entry, which is a Map<Category, Integer>
            // we will add the first ever category
            this.viewedCategories.get(watcher).put(category, 1);
        }
        content.startWatching(watcher);
    }

    @Override
    public User getMostWatchedStreamer() {
        // this map will store a relation between a user and the number of views on all of their content
        Map<User, Integer> viewsPerStreamer = new HashMap<>();
        // go through the Twitch content and fill the map accordingly
        for (Content content : this.twitchContent) {
            // get the creator of the content
            User streamer = content.getMetadata().streamer();
            // if they already exist in the Map, update the entry, otherwise create it from scratch
            if (viewsPerStreamer.containsKey(streamer)) {
                viewsPerStreamer.put(streamer, viewsPerStreamer.get(streamer) + content.getNumberOfViews());
            } else {
                viewsPerStreamer.put(streamer, content.getNumberOfViews());
            }
        }
        // get the most watched streamer in an entry
        Map.Entry<User, Integer> mostWatched = null;
        for (Map.Entry<User, Integer> entry : viewsPerStreamer.entrySet()) {
            if (mostWatched == null || mostWatched.getValue() < entry.getValue()) {
                mostWatched = entry;
            }
        }
        // if Twitch has no content, this means there is no most watched streamer -> return null
        if (mostWatched == null || mostWatched.getValue() == 0) {
            return null;
        }

        return mostWatched.getKey();
    }

    @Override
    public Content getMostWatchedContent() {
        // go through all the content and get the one with most views
        Content mostWatched = null;
        for (Content content : this.twitchContent) {
            if (mostWatched == null || content.getNumberOfViews() > mostWatched.getNumberOfViews()) {
                mostWatched = content;
            }
        }
        // if Twitch has no content, this means the most watched content is null
        // we assume that a content with 0 views isn't technically watched
        if (mostWatched == null || mostWatched.getNumberOfViews() == 0) {
            return null;
        }
        return mostWatched;
    }

    @Override
    public Content getMostWatchedContentFrom(String username) throws UserNotFoundException {
        if (username == null || username.equals("")) {
            throw new IllegalArgumentException("Incorrect username");
        }
        if (!this.userService.getUsers().containsKey(username)) {
            throw new UserNotFoundException("User " + username + " does not exist in Twitch User Service");
        }
        Content mostWatched = null;
        for (Content content : this.twitchContent) {
            if (content.getMetadata().streamer().getName().equals(username)) {
                if (mostWatched == null || content.getNumberOfViews() > mostWatched.getNumberOfViews()) {
                    mostWatched = content;
                }
            }
        }
        // of there is no content in Twitch (from the user at least),
        // this means that the most watched content from the user is null
        // we assume that a content with 0 views technically hasn't been watched
        if (mostWatched == null || mostWatched.getNumberOfViews() == 0) {
            return null;
        }
        return mostWatched;
    }

    @Override
    public List<Category> getMostWatchedCategoriesBy(String username) throws UserNotFoundException {
        if (username == null || username.equals("")) {
            throw new IllegalArgumentException("Username is either null or empty");
        }
        User user = this.userService.getUsers().get(username);
        if (user == null) {
            throw new UserNotFoundException("User " + username + " does not exist in Twitch User Service");
        }
        // categories not viewed by the user will not exist in this list
        List<Map.Entry<Category, Integer>> list = new ArrayList<>(this.viewedCategories.get(user).entrySet());
        list.sort(Map.Entry.comparingByValue());
        List<Category> answer = new ArrayList<>();
        for (int i = list.size() - 1; i >= 0; i--) {
            answer.add(list.get(i).getKey());
        }
        return Collections.unmodifiableList(answer);
    }
}
