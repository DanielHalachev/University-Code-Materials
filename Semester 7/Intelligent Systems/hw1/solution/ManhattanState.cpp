
#include "ManhattanState.h"

std::unordered_map<Tile, int> ManhattanState::goalBoard = {};

ManhattanState::ManhattanState(const Board &board, const Board &goal, Direction direction, int g) {
    this->board = board;
    this->direction = direction;
    this->g = g;
    this->h = this->board.manhattan(goal);
}


ManhattanState::ManhattanState(const Board &board, Direction direction, int g, int h, int previousEmptyTileIndex) {
    this->board = board;
    this->direction = direction;
    this->g = g;
    this->h = h + this->board.manhattanByIndex(previousEmptyTileIndex) +
              this->board.manhattanByIndex(this->board.emptyTileIndex);
}

bool ManhattanState::operator==(const ManhattanState &other) const {
    return this->board == other.board;
}


std::vector<ManhattanState> ManhattanState::getNeighbours() {
    std::vector<ManhattanState> neighbours;
    neighbours.reserve(4);
    std::optional<Board> left = this->board.getLeft();
    std::optional<Board> right = this->board.getRight();
    std::optional<Board> top = this->board.getTop();
    std::optional<Board> down = this->board.getDown();
    if (left.has_value()) {
        neighbours.emplace_back(left.value(), LEFT, this->g + 1,
                                this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                this->board.manhattanByIndex(left.value().emptyTileIndex),
                                this->board.emptyTileIndex);
    }
    if (right.has_value()) {
        neighbours.emplace_back(right.value(), RIGHT, this->g + 1,
                                this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                this->board.manhattanByIndex(right.value().emptyTileIndex),
                                this->board.emptyTileIndex);
    }
    if (top.has_value()) {
        neighbours.emplace_back(top.value(), UP, this->g + 1,
                                this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                this->board.manhattanByIndex(top.value().emptyTileIndex),
                                this->board.emptyTileIndex);
    }
    if (down.has_value()) {
        neighbours.emplace_back(down.value(), DOWN, this->g + 1,
                                this->h - this->board.manhattanByIndex(this->board.emptyTileIndex) -
                                this->board.manhattanByIndex(down.value().emptyTileIndex),
                                this->board.emptyTileIndex);
    }
    return neighbours;
}


std::string ManhattanState::getDirectionString(Direction direction) {
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
