package bg.sofia.uni.fmi.mjt.spotify;

import bg.sofia.uni.fmi.mjt.spotify.account.Account;
import bg.sofia.uni.fmi.mjt.spotify.account.AccountType;
import bg.sofia.uni.fmi.mjt.spotify.exceptions.*;
import bg.sofia.uni.fmi.mjt.spotify.playable.Playable;

public class Spotify implements StreamingService {
    public static final int PREMIUM_PRICE = 25;
    public static final double AD_REVENUE = 0.1;
    private final Account[] accounts;
    private final Playable[] playableContent;

    public Spotify(Account[] accounts, Playable[] playableContent) {
        this.accounts = accounts;
        this.playableContent = playableContent;
    }

    @Override
    public void play(Account account, String title) throws AccountNotFoundException, PlayableNotFoundException {
        if (account == null || title == null || title.equals("")) {
            throw new IllegalArgumentException("Invalid account or title information. Cannot play.");
        }
        // search for the account
        for (Account accountIterator : this.accounts) {
            // if we find the account
            if (accountIterator.equals(account)) {
                // throws PlayableNotFoundException of needed
                Playable playable = findByTitle(title);
                accountIterator.listen(playable);
                return;
            }
        }
        throw new AccountNotFoundException("Account couldn't be found");
    }

    @Override
    public void like(Account account, String title)
            throws AccountNotFoundException, PlayableNotFoundException, StreamingServiceException {
        if (account == null || title == null || title.equals("")) {
            throw new IllegalArgumentException("Invalid account or title information. Cannot play.");
        }
        for (Account accountIterator : this.accounts) {
            if (accountIterator.equals(account)) {
                // throws PlayableNotFoundException if needed
                Playable playable = findByTitle(title);
                try {
                    accountIterator.getLibrary().getLiked().add(playable);
                    return;
                } catch (PlaylistCapacityExceededException ex) {
                    throw new StreamingServiceException(ex.getMessage(), ex);
                }
            }
        }
        throw new AccountNotFoundException("Couldn't find an account match");
    }

    @Override
    public Playable findByTitle(String title) throws PlayableNotFoundException {
        if (title == null || title.equals("")) {
            throw new IllegalArgumentException("Title is empty");
        }
        for (Playable playable : this.playableContent) {
            if (playable.getTitle().equals(title)) {
                return playable;
            }
        }
        throw new PlayableNotFoundException("Playable couldn't be found by title");
    }

    @Override
    public Playable getMostPlayed() {
        int maxTotalPlays = 0;
        if (playableContent.length == 0) {
            return null;
        }
        Playable mostPlayed = null;
        for (Playable playable : playableContent) {
            if (playable.getTotalPlays() > maxTotalPlays) {
                mostPlayed = playable;
                maxTotalPlays = playable.getTotalPlays();
            }
        }
        return mostPlayed;
    }

    @Override
    public double getTotalListenTime() {
        double total = 0;
        for (Account account : this.accounts) {
            total += account.getTotalListenTime();
        }
        return total;
    }

    @Override
    public double getTotalPlatformRevenue() {
        double total = 0.0;
        for (Account account : this.accounts) {
            if (account.getType() == AccountType.FREE) {
                total += account.getAdsListenedTo() * AD_REVENUE;
            } else if (account.getType() == AccountType.PREMIUM) {
                total += PREMIUM_PRICE;
            }
        }
        return total;
    }
}

