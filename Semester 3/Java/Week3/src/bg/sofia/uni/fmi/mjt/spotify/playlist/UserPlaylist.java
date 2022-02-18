package bg.sofia.uni.fmi.mjt.spotify.playlist;

import bg.sofia.uni.fmi.mjt.spotify.exceptions.PlaylistCapacityExceededException;
import bg.sofia.uni.fmi.mjt.spotify.playable.Playable;

public class UserPlaylist implements Playlist {
    public static final int MAX_PLAYLIST_CAPACITY = 20;
    private final String name;
    int currentCapacity = 0;
    int maxCapacity = MAX_PLAYLIST_CAPACITY;
    Playable[] items;

    public UserPlaylist(String name) {
        this.name = name;
        this.items = new Playable[this.maxCapacity];
    }

    @Override
    public void add(Playable playable) throws PlaylistCapacityExceededException {
        if (currentCapacity == maxCapacity) {
            throw new PlaylistCapacityExceededException("Playlist capacity exceeded");
        } else {
            this.items[currentCapacity] = playable;
            this.currentCapacity++;
        }
    }

    @Override
    public String getName() {
        return this.name;
    }
}
