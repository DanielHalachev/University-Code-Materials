
#ifndef IS_STATE_H
#define IS_STATE_H

#include "Board.h"

enum Direction {
    NONE, LEFT, UP, DOWN, RIGHT
};

template<typename T>
class State {
public:
    static std::map<Direction, std::string> DIRECTION_STRING;
    Board<T> board;
    Direction direction = LEFT;
    explicit State(Board<T> board);
    State(Board<T> board, Direction direction);
    std::vector<State<T>> getNeighbours();
    static std::string getDirectionString(Direction direction);
    bool operator==(const State<T> &other);
};

template<typename T>
bool State<T>::operator==(const State<T> &other) {
    return this->board == other.board;
}

template<typename T>
std::string State<T>::getDirectionString(Direction direction) {
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
State<T>::State(Board<T> board) {
    this->board = board;
    this->direction = Direction::NONE;
}

template<typename T>
State<T>::State(Board<T> board, Direction direction) {
    this->board = board;
    this->direction = direction;
}

template<typename T>
std::vector<State<T>> State<T>::getNeighbours() {
    std::vector<State<T>> neighbours;
    std::optional<Board<T>> left = this->board.getLeft();
    std::optional<Board<T>> right = this->board.getRight();
    std::optional<Board<T>> top = this->board.getTop();
    std::optional<Board<T>> down = this->board.getDown();
    if (left.has_value()) {
        neighbours.push_back(State<T>(left.value(), LEFT));
    }
    if (right.has_value()) {
        neighbours.push_back(State<T>(right.value(), RIGHT));
    }
    if (top.has_value()) {
        neighbours.push_back(State<T>(top.value(), UP));
    }
    if (down.has_value()) {
        neighbours.push_back(State<T>(down.value(), DOWN));
    }
    return neighbours;
}


#endif //IS_STATE_H
