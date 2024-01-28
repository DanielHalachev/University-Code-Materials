#ifndef IS_SIMPLIFIEDSimplifiedBoard_H
#define IS_SIMPLIFIEDSimplifiedBoard_H


#include <vector>
#include <iostream>
#include <optional>
#include <cstdint>

typedef uint8_t Tile;

class Board {
public:
    std::vector<Tile> tiles;
    int dimension = 3;
    int emptyTileIndex = 8;


public:
    Board();
    explicit Board(int size);

    bool operator==(const Board &other) const;

    bool isSolvable() const;

    static Board goalBoard(int size, int index);

    bool isValidIndex(const int &index) const;

    friend std::ostream &operator<<(std::ostream &os, const Board &simplifiedBoard);

    friend std::istream &operator>>(std::istream &is, Board &simplifiedBoard);

    int manhattan(const Board &goal) const;

    int manhattanByIndex(int index) const;

    std::optional<Board> getLeft();

    std::optional<Board> getRight();

    std::optional<Board> getDown();

    std::optional<Board> getTop();


};

// efficient hashing with 0x9e3779b9 from Internet
namespace std {
    template<>
    struct hash<Board> {
        std::size_t operator()(const Board &board) const {
            std::size_t seed = 0;
            for (const Tile &tile: board.tiles) {
                seed ^= std::hash<Tile>{}(tile) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif //IS_SIMPLIFIEDSimplifiedBoard_H
