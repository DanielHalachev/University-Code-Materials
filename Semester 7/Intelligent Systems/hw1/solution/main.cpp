#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <unordered_set>
#include <stack>
#include "ManhattanState.h"

std::stack<ManhattanState> path;
Board goal;
std::unordered_set<Board> visited;

inline std::pair<std::stack<ManhattanState>, int> search(const ManhattanState &root);
inline int search(int bound);

inline std::pair<std::stack<ManhattanState>, int> search(const ManhattanState &root) {

    int bound = root.h;
    path.push(root);
    visited.insert(root.board);

    while (true) {
        int t = search(bound);
        if (t == std::numeric_limits<int>::max()) {
            return std::make_pair(std::stack<ManhattanState>(), -1);
        }
        if (t == 0) {
            return std::make_pair(path, path.size() - 1);
        }
        bound = t;
    }
}

inline int search(int bound) {
    ManhattanState node = path.top();
    int f = node.g + node.h;

    if (f > bound) {
        return f;
    }

    if (node.board == goal) {
        return 0;
    }

    int min = std::numeric_limits<int>::max();

    for (const auto &child: node.getNeighbours()) {
        if (visited.find(child.board) == visited.end()) {
            path.push(child);
            visited.insert(child.board);
            int t = search(bound);
            if (t == 0) {
                return 0;
            }
            if (t < min) {
                min = t;
            }
            path.pop();
            visited.erase(child.board);
        }
    }

    return min;
}

int main(int argc, char *argv[]) {
    int size;
    int emptyTileIndex;
    std::cin >> size >> emptyTileIndex;

    Board board(size);
    std::cin >> board;

    goal = Board::goalBoard(size, emptyTileIndex);

    std::unordered_map<Tile, int> index;
    for (int i = 0; i < goal.tiles.size(); i++) {
        index[goal.tiles[i]] = i;
    }
    ManhattanState::goalBoard = index;

    ManhattanState start(board, goal, Direction::NONE, 0);
    auto t1 = std::chrono::high_resolution_clock::now();
    if (!board.isSolvable()) {
        std::cout << -1 << std::endl;
    } else {
        auto result = search(start);
        std::cout << result.second;
        if (result.second != -1) {
          while(!result.first.empty()){
                std::cout << ManhattanState::getDirectionString(result.first.top().direction) << std::endl;
                result.first.pop();
          }
        }
    }
    if (argc > 1) {
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = t2 - t1;
        std::cout << std::fixed << std::setprecision(2) << duration.count() << "s" << std::endl;
    }

    return 0;
}
