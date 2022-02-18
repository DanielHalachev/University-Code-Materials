package bg.sofia.uni.fmi.mjt.twitch.user.service;

import bg.sofia.uni.fmi.mjt.twitch.user.User;

import java.util.Map;

public interface UserService {

    /**
     * Returns a map of users, where the key is the username.
     *
     * @return a map of users, where the key is the username
     */
    Map<String, User> getUsers();
}