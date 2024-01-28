//#include <iostream>
//#include <limits>
//#include <algorithm>
//#include <chrono>
//#include <iomanip>
//#include <unordered_set>
//#include <stack>
//#include "Board.h"
//#include "ManhattanState.h"
//
//
//template<typename T>
//std::pair<std::stack<ManhattanState<T>>, int> search(const ManhattanState<T> &root, const Board<T> &goal) {
//    int bound = root.h;
//    std::stack<ManhattanState<T>> path;
//    path.push(root);
//    std::unordered_set<Board<T>> visited;
//    visited.insert(root.board);
//
//    while (true) {
//        int t = search(path, goal, bound, visited);
//        if (t == std::numeric_limits<int>::max()) {
//            return std::make_pair(std::stack<ManhattanState<T>>(), -1);
//        }
//        if (t == 0) {
//            return std::make_pair(path, path.size() - 1);
//        }
//        bound = t;
//    }
//}
//
//template<typename T>
//int search(std::stack<ManhattanState<T>> &path, const Board<T> &goal, int bound, std::unordered_set<Board<T>> &visited) {
//    ManhattanState<T> node = path.top();
//    int f = node.g + node.h;
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
//    auto neighbours = node.getNeighbours(goal);
//    while(!neighbours.empty()) {
//        ManhattanState<T> child = neighbours.top();
//        neighbours.pop();
//        if (std::find(visited.begin(), visited.end(), child.board) == visited.end()) {
//            path.push(child);
//            visited.insert(child.board);
//            int t = search(path, goal, bound, visited);
//            if (t == 0) {
//                return 0;
//            }
//            if (t < min) {
//                min = t;
//            }
//            path.pop();
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
//    Board<short> board(size);
//    std::cin >> board;
//
//    Board<short> goal = Board<short>::goalBoard(size, emptyTileIndex);
//    ManhattanState<short> start(board, goal, Direction::NONE, 0);
//    auto t1 = std::chrono::high_resolution_clock::now();
//    if (!board.isSolvable()) {
//        std::cout << -1 << std::endl;
//    } else {
//        auto result = search(start, goal);
//        std::cout << result.second;
//        if (result.second != -1) {
//            while(!result.first.empty()){
//                std::cout << ManhattanState<int>::getDirectionString(result.first.top().direction) << std::endl;
//                result.first.pop();
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
