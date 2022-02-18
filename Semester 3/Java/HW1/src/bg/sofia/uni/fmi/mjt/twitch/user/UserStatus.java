package bg.sofia.uni.fmi.mjt.twitch.user;

public enum UserStatus {

    STREAMING("User is currently streaming"), OFFLINE("User is offline");

    private final String message;

    UserStatus(String message) {
        this.message = message;
    }

    public String getMessage() {
        return this.message;
    }
}