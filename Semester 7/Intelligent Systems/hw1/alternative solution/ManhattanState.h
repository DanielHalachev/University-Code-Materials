
#ifndef IS_MANHATTANSTATE_H
#define IS_MANHATTANSTATE_H

#include <queue>
#include <deque>
#include "Board.h"

enum Direction {
    NONE, LEFT, UP, DOWN, RIGHT
};

template<typename T>
class Board;

template<typename T>
class ManhattanState {
public:

    static std::map<T, int> goalBoard;

    struct Comparator {
        bool operator()(const ManhattanState<T> &lhs, const ManhattanState<T> &rhs) const {
            return (lhs.h < rhs.h);
        }
    };

    Board<T> board;
    Direction direction = LEFT;
    int g = 0;
    int h = 0;

    explicit ManhattanState(Board<T> board, Board<T> goal, Direction direction = Direction::NONE, int g = 0);

    explicit ManhattanState(Board<T> board, Direction direction, int g, int h, int previousEmptyTileIndex);

    bool operator==(const ManhattanState<T> &other);

    std::priority_queue<ManhattanState<T>, std::vector<ManhattanState<T>>, ManhattanState::Comparator> getNeighbours();

    static std::string getDirectionString(Direction direction);

};

template<typename T>
std::map<T, int> ManhattanState<T>::goalBoard = {};

template<typename T>
ManhattanState<T>::ManhattanState(Board<T> board, Board<T> goal, Direction direction, int g) {
    this->board = board;
    this->direction = direction;
    this->g = g;
    this->h = this->board.manhattan(goal);
}


template<typename T>
ManhattanState<T>::ManhattanState(Board<T> board, Direction direction, int g, int h, int previousEmptyTileIndex) {
    this->board = board;
    this->direction = direction;
    this->g = g;
    this->h = h + this->board.manhattanByIndex(previousEmptyTileIndex) +
              this->board.manhattanByIndex(this->board.emptyTileIndex);
}

template<typename T>
bool ManhattanState<T>::operator==(const ManhattanState<T> &other) {
    return this->board == other.board;
}


template<typename T>
std::priority_queue<ManhattanState<T>, std::vector<ManhattanState<T>>, typename ManhattanState<T>::Comparator>
ManhattanState<T>::getNeighbours() {
    std::priority_queue<ManhattanState<T>, std::vector<ManhattanState<T>>, typename ManhattanState<T>::Comparator> neighbours;
    std::optional<Board<T>> left = this->board.getLeft();
    std::optional<Board<T>> right = this->board.getRight();
    std::optional<Board<T>> top = this->board.getTop();
    std::optional<Board<T>> down = this->board.getDown();
    if (left.has_value()) {
        neighbours.push(ManhattanState<T>(left.value(), LEFT, this->g + 1,
                                          this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                          this->board.manhattanByIndex(left.value().emptyTileIndex),
                                          this->board.emptyTileIndex));
    }
    if (right.has_value()) {
        neighbours.push(ManhattanState<T>(right.value(), RIGHT, this->g + 1,
                                          this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                          this->board.manhattanByIndex(right.value().emptyTileIndex),
                                          this->board.emptyTileIndex));
    }
    if (top.has_value()) {
        neighbours.push(ManhattanState<T>(top.value(), UP, this->g + 1,
                                          this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                          this->board.manhattanByIndex(top.value().emptyTileIndex),
                                          this->board.emptyTileIndex));
    }
    if (down.has_value()) {
        neighbours.push(ManhattanState<T>(down.value(), DOWN, this->g + 1,
                                          this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                          this->board.manhattanByIndex(down.value().emptyTileIndex),
                                          this->board.emptyTileIndex));
    }
    return neighbours;
}


template<typename T>
std::string ManhattanState<T>::getDirectionString(Direction direction) {
    switch (direction) {
        case LEFT:
            return "right";
        case RIGHT:
            return "left";
        case UP:
            return "down";
        case DOWN:
            return "up";
        default:
            return "";
    }
}


#endif //IS_MANHATTANSTATE_H
