package bg.sofia.uni.fmi.mjt.spotify.playable;

public class Video extends AudioVideoBase {
    public Video(String title, String artist, int year, double duration) {
        super(title, artist, year, duration);
    }

    @Override
    public String play() {
        this.totalPlays++;
        return "" + "Currently playing Video content: " + this.title;
    }
}
