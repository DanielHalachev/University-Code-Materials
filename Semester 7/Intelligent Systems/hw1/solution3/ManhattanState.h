
#ifndef IS_MANHATTANSTATE_H
#define IS_MANHATTANSTATE_H

#include <queue>
#include <deque>
#include "Board.h"

enum Direction {
    NONE, LEFT, UP, DOWN, RIGHT
};

template<typename T>
class ManhattanState {
public:

    struct Comparator {
        bool operator()(const ManhattanState<T>& lhs, const ManhattanState<T>& rhs) const {
            return (lhs.h < rhs.h); // TODO - not sure about this one
        }
    };

    Board<T> board;
    Direction direction = LEFT;
    int g = 0;
    int h = 0;

    explicit ManhattanState(Board<T> board, Board<T> goal, Direction direction = Direction::NONE, int g = 0);
    std::priority_queue<ManhattanState<T>, std::deque<ManhattanState<T>>, ManhattanState<T>::Comparator> getNeighbours(Board<T> goal);
    static std::string getDirectionString(Direction direction);
    bool operator==(const ManhattanState<T> &other);
};

template<typename T>
bool ManhattanState<T>::operator==(const ManhattanState<T> &other) {
    return this->board == other.board;
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

template<typename T>
ManhattanState<T>::ManhattanState(Board<T> board, Board<T> goal, Direction direction, int g) {
    this->board = board;
    this->direction = direction;
    this->g = g;
    this->h = this->board.manhattan(goal);
}


template<typename T>
std::priority_queue<ManhattanState<T>, std::deque<ManhattanState<T>>, typename ManhattanState<T>::Comparator> ManhattanState<T>::getNeighbours(Board<T> goal) {
    std::priority_queue<ManhattanState<T>, std::deque<ManhattanState<T>>, ManhattanState<T>::Comparator> neighbours;
    std::optional<Board<T>> left = this->board.getLeft();
    std::optional<Board<T>> right = this->board.getRight();
    std::optional<Board<T>> top = this->board.getTop();
    std::optional<Board<T>> down = this->board.getDown();
    if (left.has_value()) {
        neighbours.push(ManhattanState<T>(left.value(), goal, LEFT, this->g + 1));
    }
    if (right.has_value()) {
        neighbours.push(ManhattanState<T>(right.value(), goal, RIGHT, this->g + 1));
    }
    if (top.has_value()) {
        neighbours.push(ManhattanState<T>(top.value(), goal, UP, this->g + 1));
    }
    if (down.has_value()) {
        neighbours.push(ManhattanState<T>(down.value(), goal, DOWN, this->g + 1));
    }
    return neighbours;
}


#endif //IS_MANHATTANSTATE_H
