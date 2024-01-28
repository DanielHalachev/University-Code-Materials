//#include <iostream>
//#include <vector>
//#include <limits>
//#include <algorithm>
//#include <chrono>
//#include <iomanip>
//#include <unordered_set>
//#include "Board.h"
//#include "State.h"
//
//
//template<typename T>
//std::pair<std::vector<State<T>>, int> search(const State<T> &root, const Board<T> &goal) {
//    int bound = root.board.manhattan(goal);
//    std::vector<State<T>> path;
//    std::unordered_set<Board<T>> visited;
//    path.push_back(root);
//    visited.insert(root.board);
//
//    while (true) {
//        int t = search(path, goal, 0, bound, visited);
//        if (t == std::numeric_limits<int>::max()) {
//            return std::make_pair(std::vector<State<T>>(), -1);
//        }
//        if (t == 0) {
//            return std::make_pair(path, path.size() - 1);
//        }
//        bound = t;
//    }
//}
//
//template<typename T>
//int search(std::vector<State<T>> &path, const Board<T> &goal, int g, int bound, std::unordered_set<Board<T>> &visited) {
//    State<T> node = path.back();
//    int f = g + node.board.manhattan(goal);
//
//    if (f > bound) {
//        return f;
//    }
//
//    if (node.board == goal) {
//        return 0;
//    }
//
//    int min = std::numeric_limits<int>::max();
//
//    for (const State<T> &child: node.getNeighbours()) {
//        if (std::find(visited.begin(), visited.end(), child.board) == visited.end()) {
//            path.push_back(child);
//            visited.insert(child.board);
//            int t = search(path, goal, g + 1, bound, visited);
//            if (t == 0) {
//                return 0;
//            }
//            if (t < min) {
//                min = t;
//            }
//            path.pop_back();
//            visited.erase(child.board);
//        }
//    }
//
//    return min;
//}
//
//int main(int argc, char *argv[]) {
//    int size;
//    int emptyTileIndex;
//    std::cin >> size >> emptyTileIndex;
//    Board<unsigned short> board(size);
//    std::cin >> board;
//
//    State<unsigned short> start(board);
//    Board<unsigned short> goal = Board<unsigned short>::goalBoard(size, emptyTileIndex);
//    auto t1 = std::chrono::high_resolution_clock::now();
//    if (!board.isSolvable()) {
//        std::cout << -1 << std::endl;
//    } else {
//        auto result = search(start, goal);
//        std::cout << result.second;
//        if (result.second != -1) {
//            for (const State<unsigned short> &state: result.first) {
//                std::cout << State<int>::getDirectionString(state.direction) << std::endl;
//            }
//        }
//    }
//    if (argc > 1) {
//        auto t2 = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double> duration = t2 - t1;
//        std::cout << std::fixed << std::setprecision(2) << duration.count() << "s" << std::endl;
//    }
//
//    return 0;
//}
