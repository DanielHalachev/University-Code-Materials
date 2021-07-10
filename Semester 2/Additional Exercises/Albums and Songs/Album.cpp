//
// Created by User on 3.6.2021 г..
//

#include <cstring>
#include "Album.hpp"

Album::Album() {
    this->albumName[0] = '\0';
    this->playlist = nullptr;
    this->numberOfSongs = 0;
}

Album::Album(const Album &other) {
    strcpy(this->albumName, other.albumName);
    this->numberOfSongs = other.numberOfSongs;
    this->playlist = new Song[this->numberOfSongs];
    for (int i = 0; i < this->numberOfSongs; i++) {
        this->playlist[i] = other.playlist[i];
    }
}

Album &Album::operator=(const Album &other) {
    if (this != &other) {
        strcpy(this->albumName, other.albumName);
        this->numberOfSongs = other.numberOfSongs;
        this->playlist = new Song[this->numberOfSongs];
        for (int i = 0; i < this->numberOfSongs; i++) {
            this->playlist[i] = other.playlist[i];
        }
    }
    return *this;
}

Album::~Album() {
    delete[] this->playlist;
}

unsigned int Album::getLength() const {
    return this->numberOfSongs;
}

const char *Album::getArtist() const {
    if (this->numberOfSongs == 0) {
        return "No artist";
    }
    for (int i = 0; i < this->numberOfSongs - 1; i++) {
        for (int j = i + 1; j < this->numberOfSongs; j++) {
            if (this->playlist[i].getArtist() != this->playlist[j].getArtist()) {
                return "Various artists";
            }
        }
    }
    return this->playlist[0].getArtist();
}

Song *Album::findSong(const char *songName) const {
    for (int i = 0; i < this->numberOfSongs; i++) {
        if (strcmp(this->playlist[i].getArtist(), songName) == 0) {
            return &this->playlist[i];
        }
    }
    return nullptr;
}

void Album::deleteDuplicates() {
    if (this->numberOfSongs < 2) {
        return;
    }
    for (int i = 0; i < this->numberOfSongs - 1; i++) {
        for (int j = i + 1; j < this->numberOfSongs; j++) {
            if (this->playlist[j] == this->playlist[i]) {
                this->numberOfSongs--;
                for (int t = j; t < this->numberOfSongs; t++) {
                    this->playlist[t] = this->playlist[t + 1];
                }
            }
        }
    }
    Song *newArray = new Song[this->numberOfSongs];
    for (int i = 0; i < this->numberOfSongs; i++) {
        newArray[i] = this->playlist[i];
    }
    delete[] this->playlist;
    this->playlist = newArray;
}

void Album::addSong(const Song &song) {
    Song *newArray = new Song[this->numberOfSongs + 1];
    for (int i = 0; i < this->numberOfSongs; i++) {
        newArray[i] = this->playlist[i];
    }
    newArray[this->numberOfSongs] = song;
    delete[] this->playlist;
    this->playlist = newArray;
    this->numberOfSongs++;
}
