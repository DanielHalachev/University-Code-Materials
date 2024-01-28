#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <unordered_set>
#include "Board.h"
#include "ManhattanState.h"


template<typename T>
std::pair<std::vector<ManhattanState<T>>, int> search(const ManhattanState<T> &root, const Board<T> &goal) {

    int bound = root.h;
    std::vector<ManhattanState<T>> path;
    path.push_back(root);

    while (true) {
        int t = search(path, goal, bound);
        if (t == std::numeric_limits<int>::max()) {
            return std::make_pair(std::vector<ManhattanState<T>>(), -1);
        }
        if (t == 0) {
            return std::make_pair(path, path.size() - 1);
        }
        bound = t;
    }
}

template<typename T>
int search(std::vector<ManhattanState<T>> &path, const Board<T> &goal, int bound) {
    ManhattanState<T> node = path.back();
    int f = node.g + node.h;

    if (f > bound) {
        return f;
    }

    if (node.board == goal) {
        return 0;
    }

    int min = std::numeric_limits<int>::max();

    auto neighbours = node.getNeighbours();
    while (!neighbours.empty()) {
        ManhattanState<T> child = neighbours.top();
        neighbours.pop();
        if (std::find(path.begin(), path.end(), child) == path.end()) {
            path.push_back(child);
            int t = search(path, goal, bound);
            if (t == 0) {
                return 0;
            }
            if (t < min) {
                min = t;
            }
            path.pop_back();
        }
    }

    return min;
}

int main(int argc, char *argv[]) {
    int size;
    int emptyTileIndex;
    std::cin >> size >> emptyTileIndex;
    Board<short> board(size);
    std::cin >> board;

    Board<short> goal = Board<short>::goalBoard(size, emptyTileIndex);
    std::map<short, int> index;
    for (int i = 0; i < goal.tiles.size(); i++) {
        index[goal.tiles[i]] = i;
    }
    ManhattanState<short>::goalBoard = index;

    ManhattanState<short> start(board, goal, Direction::NONE, 0);
    auto t1 = std::chrono::high_resolution_clock::now();
    if (!board.isSolvable()) {
        std::cout << -1 << std::endl;
    } else {
        auto result = search(start, goal);
        std::cout << result.second;
        if (result.second != -1) {
            for (const ManhattanState<short> &state: result.first) {
                std::cout << ManhattanState<int>::getDirectionString(state.direction) << std::endl;
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
