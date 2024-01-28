//
// Created by daniel on 17.10.23.
//

#ifndef IS_SIMPLIFIEDSimplifiedBoard_H
#define IS_SIMPLIFIEDSimplifiedBoard_H


#include <vector>
#include <optional>
#include <ostream>
#include <cmath>
#include <ranges>
#include <map>
#include <iostream>
#include "ManhattanState.h"

template<typename T>
class ManhattanState;

template<typename T>
class Board {
public:
    std::vector<T> tiles;
    int dimension = 3;
    int emptyTileIndex = 8;


public:
    Board();

    explicit Board(int size);

    bool operator==(const Board<T> &other) const;

    bool isSolvable();

    static Board<T> goalBoard(int size, int index);

    bool isValidIndex(const int &index) const;

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Board<U> &simplifiedBoard);

    template<typename U>
    friend std::istream &operator>>(std::istream &is, Board<U> &simplifiedBoard);

    int manhattan(const Board<T> &goal) const;

    int manhattanByIndex(int index) const;

    std::optional<Board<T>> getLeft();

    std::optional<Board<T>> getRight();

    std::optional<Board<T>> getDown();

    std::optional<Board<T>> getTop();

};

// efficient hashing with 0x9e3779b9 from Internet
template<typename T>
struct std::hash<Board<T>> {
    std::size_t operator()(const Board<T> &board) const {
        std::size_t seed = 0;
        for (const T &tile: board.tiles) {
            seed ^= std::hash<T>{}(tile) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};


template<typename T>
Board<T>::Board() {
    this->dimension = 3;
    this->emptyTileIndex = 8;
    this->tiles.resize(this->dimension * this->dimension);
}


template<typename T>
Board<T>::Board(int size) {
    this->dimension = sqrt(size + 1);
    this->tiles.resize(size + 1);
    this->emptyTileIndex = size;
}


template<typename T>
bool Board<T>::operator==(const Board<T> &other) const {
    return this->tiles == other.tiles;
}


template<typename T>
bool Board<T>::isSolvable() {
    int inversions = 0;
    for (size_t i = 0; i < this->tiles.size() - 1; i++) {
        for (size_t j = i + 1; j < this->tiles.size(); j++) {
            if (this->tiles[i] > 0 && this->tiles[j] > 0 && this->tiles[i] > this->tiles[j]) {
                inversions++;
            }
        }
    }

    if (this->dimension % 2 != 0) {
        return (inversions % 2 == 0);
    } else {
        int emptyRowIndex = this->emptyTileIndex / this->dimension;
        return (((inversions + emptyRowIndex) % 2) != 0);
    }
}


template<typename T>
Board<T> Board<T>::goalBoard(int size, int index) {
    if (index == -1) {
        index = size;
    }
    Board<T> board(size);
    board.emptyTileIndex = index;
    size_t i = 0;
    for (; i < index; i++) {
        board.tiles[i] = i + 1;
    }
    for (; i <= size; i++) {
        board.tiles[i] = i;
    }
    board.tiles[index] = 0;
    return board;
}


template<typename T>
bool Board<T>::isValidIndex(const int &index) const {
    return (index >= 0 && index < this->dimension);
}


template<typename U>
std::ostream &operator<<(std::ostream &os, const Board<U> &simplifiedBoard) {
    int i = 1;
    for (auto tile: simplifiedBoard.tiles) {
        os << tile << " ";
        if (i % simplifiedBoard.dimension == 0) {
            os << std::endl;
        }
        i++;
    }
    return os;
}

template<typename U>
std::istream &operator>>(std::istream &is, Board<U> &simplifiedBoard) {
    for (size_t i = 0; i < simplifiedBoard.dimension * simplifiedBoard.dimension; i++) {
        U temp;
        is >> temp;
        simplifiedBoard.tiles[i] = temp;
        if (temp == 0) {
            simplifiedBoard.emptyTileIndex = i;
        }
    }
    return is;
}

template<typename T>
int Board<T>::manhattan(const Board<T> &goal) const {
    std::map<T, std::pair<int, int>> currentPositions;
    std::map<T, std::pair<int, int>> goalPositions;
    for (size_t i = 0; i < this->tiles.size(); i++) {
        currentPositions[this->tiles[i]] = std::pair(i / this->dimension, i % this->dimension);
        goalPositions[goal.tiles[i]] = std::pair(i / this->dimension, i % this->dimension);
    }
    int sum = 0;
    for (auto pair: currentPositions) {
        sum += abs(pair.second.first - goalPositions[pair.first].first) +
               abs(pair.second.second - goalPositions[pair.first].second);
    }
    return sum;
}

template<typename T>
int Board<T>::manhattanByIndex(int index) const {
    return
            abs(index / this->dimension - ManhattanState<T>::goalBoard[this->tiles[index]] / this->dimension) +
            abs(index % this->dimension - ManhattanState<T>::goalBoard[this->tiles[index]] % this->dimension);
}

template<typename T>
std::optional<Board<T>> Board<T>::getLeft() {
    int emptyTileY = this->emptyTileIndex % this->dimension;
    if (isValidIndex(emptyTileY - 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex - 1], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex - 1;
        return temp;
    }
    return std::nullopt;
}

template<typename T>
std::optional<Board<T>> Board<T>::getRight() {
    int emptyTileY = this->emptyTileIndex % this->dimension;
    if (isValidIndex(emptyTileY + 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex], temp.tiles[this->emptyTileIndex + 1]);
        temp.emptyTileIndex = emptyTileIndex + 1;
        return temp;
    }
    return std::nullopt;
}

template<typename T>
std::optional<Board<T>> Board<T>::getTop() {
    int emptyTileX = this->emptyTileIndex / this->dimension;
    if (isValidIndex(emptyTileX - 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex - dimension], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex - dimension;
        return temp;
    }
    return std::nullopt;
}

template<typename T>
std::optional<Board<T>> Board<T>::getDown() {
    int emptyTileX = this->emptyTileIndex / this->dimension;
    if (isValidIndex(emptyTileX + 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex + dimension], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex + dimension;
        return temp;
    }
    return std::nullopt;
}

#endif //IS_SIMPLIFIEDSimplifiedBoard_H
