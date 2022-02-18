package bg.sofia.uni.fmi.mjt.spotify.account;

import bg.sofia.uni.fmi.mjt.spotify.library.Library;
import bg.sofia.uni.fmi.mjt.spotify.playable.Playable;

import java.util.Objects;

public abstract class Account {
    protected final String email;

    protected final Library library;

    protected double totalListenTime = 0;

    protected int totalPlays = 0;


    public Account(String email, Library library) {
        this.email = email;
        this.library = library;
    }

    /**
     * Returns the number of ads listened to.
     * - Free accounts get one ad after every 5 pieces of content played
     * - Premium accounts get no ads
     */
    public abstract int getAdsListenedTo();

    /**
     * Returns the account type as an enum with possible values FREE and PREMIUM
     */
    public abstract AccountType getType();

    /**
     * Simulates listening of the specified content.
     * This should increment the total number of content listened and the total listen time for this account.
     *
     * @param playable the content that is being listened
     */
    public void listen(Playable playable) {
        if (playable == null) {
            throw new IllegalArgumentException();
        }
        this.totalListenTime += playable.getDuration();
        this.totalPlays++;
        playable.play();
    }

    /**
     * Returns the library for this account.
     */
    public Library getLibrary() {
        return this.library;
    }

    /**
     * Returns the total listen time for this account. The time for any ads listened is not included.
     */
    public double getTotalListenTime() {
        return this.totalListenTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Account account = (Account) o;
        return email.equals(account.email);
    }

    @Override
    public int hashCode() {
        return Objects.hash(email);
    }
}