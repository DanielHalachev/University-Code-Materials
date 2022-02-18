package bg.sofia.uni.fmi.mjt.spotify.account;

import bg.sofia.uni.fmi.mjt.spotify.library.Library;

public class FreeAccount extends Account {

    public static final int NUM_PLAYABLES_PER_AD = 5;

    public FreeAccount(String email, Library library) {
        super(email, library);
    }

    @Override
    public int getAdsListenedTo() {
        return this.totalPlays / NUM_PLAYABLES_PER_AD;
    }

    @Override
    public AccountType getType() {
        return AccountType.FREE;
    }
}
