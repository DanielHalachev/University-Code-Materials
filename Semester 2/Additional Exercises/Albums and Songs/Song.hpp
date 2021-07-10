//
// Created by User on 3.6.2021 г..
//

#ifndef EXERCISES_SONG_HPP
#define EXERCISES_SONG_HPP


#include <ostream>

class Song {
public:
    Song(const char *title = "", const char *artist = "", const int &year = 0, const unsigned int length = 0);

//    Song(const Song &other);
//
//    Song &operator=(const Song &other);
//
//    ~Song();

    const char *getTitle() const;

    const char *getArtist() const;

    int getYear() const;

    unsigned int getLength() const;

    friend std::ostream &operator<<(std::ostream &out, const Song &song);

    bool operator==(const Song &other) const;

private:
    char title[100];
    char artist[100];
    int year;
    unsigned int length;
};


#endif //EXERCISES_SONG_HPP
