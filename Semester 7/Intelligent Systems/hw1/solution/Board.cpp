#include <cmath>
#include <map>
#include "Board.h"
#include "ManhattanState.h"




Board::Board() {
    this->dimension = 3;
    this->emptyTileIndex = 8;
    this->tiles.resize(this->dimension * this->dimension);
}


Board::Board(int size) {
    this->dimension = (int) sqrt(size + 1);
    this->tiles.resize(size + 1);
    this->emptyTileIndex = size;
}


bool Board::operator==(const Board &other) const {
    return this->tiles == other.tiles;
}


bool Board::isSolvable() const {
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


Board Board::goalBoard(int size, int index) {
    if (index == -1) {
        index = size;
    }
    Board board(size);
    board.emptyTileIndex = index;
    size_t i = 0;
    for (; i < index; i++)
        board.tiles[i] = (Tile) i + 1;

    for (; i <= size; i++) {
        board.tiles[i] = i;
    }
    board.tiles[index] = 0;
    return board;
}


bool Board::isValidIndex(const int &index) const {
    return (index >= 0 && index < this->dimension);
}


std::ostream &operator<<(std::ostream &os, const Board &simplifiedBoard) {
    int i = 1;
    for (auto tile: simplifiedBoard.tiles) {
        os << (int) tile << " ";
        if (i % simplifiedBoard.dimension == 0) {
            os << std::endl;
        }
        i++;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Board &simplifiedBoard) {
    for (size_t i = 0; i < simplifiedBoard.dimension * simplifiedBoard.dimension; i++) {
        int temp;
        is >> temp;
        simplifiedBoard.tiles[i] = (Tile)temp;
        if (temp == 0) {
            simplifiedBoard.emptyTileIndex = (int)i;
        }
    }
    return is;
}

int Board::manhattan(const Board &goal) const {
    std::map<Tile, std::pair<int, int>> currentPositions;
    std::map<Tile, std::pair<int, int>> goalPositions;
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

int Board::manhattanByIndex(int index) const {
    return
            abs(index / this->dimension - ManhattanState::goalBoard[this->tiles[index]] / this->dimension) +
            abs(index % this->dimension - ManhattanState::goalBoard[this->tiles[index]] % this->dimension);
}

std::optional<Board> Board::getLeft() {
    int emptyTileY = this->emptyTileIndex % this->dimension;
    if (isValidIndex(emptyTileY - 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex - 1], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex - 1;
        return temp;
    }
    return std::nullopt;
}

std::optional<Board> Board::getRight() {
    int emptyTileY = this->emptyTileIndex % this->dimension;
    if (isValidIndex(emptyTileY + 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex], temp.tiles[this->emptyTileIndex + 1]);
        temp.emptyTileIndex = emptyTileIndex + 1;
        return temp;
    }
    return std::nullopt;
}

std::optional<Board> Board::getTop() {
    int emptyTileX = this->emptyTileIndex / this->dimension;
    if (isValidIndex(emptyTileX - 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex - dimension], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex - dimension;
        return temp;
    }
    return std::nullopt;
}

std::optional<Board> Board::getDown() {
    int emptyTileX = this->emptyTileIndex / this->dimension;
    if (isValidIndex(emptyTileX + 1)) {
        Board temp = *this;
        std::swap(temp.tiles[this->emptyTileIndex + dimension], temp.tiles[this->emptyTileIndex]);
        temp.emptyTileIndex = emptyTileIndex + dimension;
        return temp;
    }
    return std::nullopt;
}
