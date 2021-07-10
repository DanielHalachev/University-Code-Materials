//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_ALBUM_HPP
#define EXERCISES_ALBUM_HPP


#include "Song.hpp"

class Album {
public:
    Album();

    Album(const Album &other);

    Album &operator=(const Album &other);

    ~Album();

    unsigned int getLength() const;

    const char *getArtist() const;

    Song *findSong(const char *songName) const;

    void deleteDuplicates();

    void addSong(const Song &song);

private:
    Song *playlist;
    char albumName[100];
    int numberOfSongs;
};


#endif //EXERCISES_ALBUM_HPP
