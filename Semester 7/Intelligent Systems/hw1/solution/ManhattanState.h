
#ifndef IS_MANHATTANSTATE_H
#define IS_MANHATTANSTATE_H

#include <queue>
#include <deque>
#include <unordered_map>
#include "Board.h"

enum Direction {
    NONE, LEFT, UP, DOWN, RIGHT
};

class ManhattanState {
public:

    static std::unordered_map<Tile, int> goalBoard;

    Board board;
    Direction direction = LEFT;
    int g = 0;
    int h = 0;

    explicit ManhattanState(const Board &board, const Board &goal, Direction direction = Direction::NONE, int g = 0);

    explicit ManhattanState(const Board &board, Direction direction, int g, int h, int previousEmptyTileIndex);

    bool operator==(const ManhattanState &other) const;

    std::vector<ManhattanState> getNeighbours();

    static std::string getDirectionString(Direction direction);

};

struct Comparator {
    bool operator()(const ManhattanState &lhs, const ManhattanState &rhs) const {
        return (lhs.h < rhs.h);
    }
};


#endif //IS_MANHATTANSTATE_H
