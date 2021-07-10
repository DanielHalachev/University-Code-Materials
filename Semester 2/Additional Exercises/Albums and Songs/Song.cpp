//
// Created by User on 3.6.2021 г..
//

#include <cstring>
#include "Song.hpp"

Song::Song(const char *title, const char *artist, const int &year, const unsigned int length)
        : year(year), length(length) {
    strcpy(this->title, title);
    strcpy(this->artist, artist);
}

const char *Song::getTitle() const {
    return this->title;
}

const char *Song::getArtist() const {
    return this->artist;
}

int Song::getYear() const {
    return this->year;
}

unsigned int Song::getLength() const {
    return this->length;
}

std::ostream &operator<<(std::ostream &out, const Song &song) {
    out << song.artist << " - " << song.title << ": " << song.year << ", " << song.length << "s.";
    return out;
}

bool Song::operator==(const Song &other) const {
    return (strcmp(this->artist, other.artist) == 0 &&
            strcmp(this->title, other.title) == 0 &&
            this->length == other.length &&
            this->year == other.year);
}

//Song::Song(const Song &other) {
//    strcpy(this->artist, other.artist);
//    strcpy(this->title, other.title);
//    this->year = other.year;
//    this->length = other.length;
//}
//
//Song &Song::operator=(const Song &other) {
//    if(this!=&other){
//        strcpy(this->artist, other.artist);
//        strcpy(this->title, other.title);
//        this->year = other.year;
//        this->length = other.length;
//    }
//    return *this;
//}
//
//Song::~Song() {
//    delete[] this->artist;
//    delete[] this->title;
//}
