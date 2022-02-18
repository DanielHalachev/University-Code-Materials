package bg.sofia.uni.fmi.mjt.twitch.user;

public interface User {

    /**
     * Returns the name of the user.
     *
     * @return the name of the user
     */
    String getName();

    /**
     * Returns the {@link UserStatus} of the user.
     *
     * @return the {@link UserStatus} of the user
     */
    UserStatus getStatus();

    /**
     * Sets the {@link UserStatus} of the user.
     *
     * @param status the new {@link UserStatus} to set
     */
    void setStatus(UserStatus status);
}