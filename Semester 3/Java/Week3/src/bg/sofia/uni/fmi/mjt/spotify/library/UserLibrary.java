package bg.sofia.uni.fmi.mjt.spotify.library;

import bg.sofia.uni.fmi.mjt.spotify.exceptions.EmptyLibraryException;
import bg.sofia.uni.fmi.mjt.spotify.exceptions.LibraryCapacityExceededException;
import bg.sofia.uni.fmi.mjt.spotify.exceptions.PlaylistNotFoundException;
import bg.sofia.uni.fmi.mjt.spotify.playlist.Playlist;

public class UserLibrary implements Library {
    private final int maxCapacity = 21;
    private int currentCapacity = 1;
    Playlist[] playlists;

    public UserLibrary() {
        this.playlists = new Playlist[this.maxCapacity];
    }

    @Override
    public void add(Playlist playlist) throws LibraryCapacityExceededException {
        if (playlist == null) {
            throw new IllegalArgumentException("Playlist is null. Cannot add");
        }
        if (this.currentCapacity == this.maxCapacity) {
            throw new LibraryCapacityExceededException("Max number of playlists reached");
        } else {
            this.playlists[this.currentCapacity] = playlist;
            this.currentCapacity++;
        }
    }

    @Override
    public void remove(String name) throws EmptyLibraryException, PlaylistNotFoundException {
        if (name == null || name.equals("")) {
            throw new IllegalArgumentException("Invalid name. Cannot remove");
        }
        if (name.equals("Liked Content")) {
            throw new IllegalArgumentException("Cannot remove Liked Content Playlist");
        }
        if (this.currentCapacity == 1) {
            throw new EmptyLibraryException("Cannot remove playlist as only existing is Liked Songs");
        }
        for (int i = 1; i < this.currentCapacity; i++) {
            if (this.playlists[i].getName().equals(name)) {
                for (int j = i; j < this.currentCapacity - 1; j++) {
                    this.playlists[j] = this.playlists[j + 1];
                }
                this.currentCapacity--;
                return;
            }
        }
        throw new PlaylistNotFoundException("Playlist to remove couldn't be found");
    }

    @Override
    public Playlist getLiked() {
        return this.playlists[0];
    }
}
