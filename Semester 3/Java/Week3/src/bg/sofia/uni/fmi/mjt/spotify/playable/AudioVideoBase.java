package bg.sofia.uni.fmi.mjt.spotify.playable;

import java.util.Objects;

public abstract class AudioVideoBase implements Playable {
    protected int totalPlays;
    protected String title;
    protected String artist;
    protected int year;
    protected double duration;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AudioVideoBase that = (AudioVideoBase) o;
        return getYear() == that.getYear() &&
                Double.compare(that.getDuration(), getDuration()) == 0 &&
                getTitle().equals(that.getTitle()) &&
                getArtist().equals(that.getArtist());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTitle(), getArtist(), getYear(), getDuration());
    }

    public AudioVideoBase(String title, String artist, int year, double duration) {
        this.title = title;
        this.artist = artist;
        this.year = year;
        this.duration = duration;
        this.totalPlays = 0;
    }

    @Override
    public int getTotalPlays() {
        return this.totalPlays;
    }

    @Override
    public String getTitle() {
        return this.title;
    }

    @Override
    public String getArtist() {
        return this.artist;
    }

    @Override
    public int getYear() {
        return this.year;
    }

    @Override
    public double getDuration() {
        return this.duration;
    }
}
