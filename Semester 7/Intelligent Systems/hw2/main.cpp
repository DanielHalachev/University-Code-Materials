

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <optional>
#include <chrono>
#include <random>
#include <iomanip>


#define ITERATION_LIMIT 100000
//#define ITERATION_LIMIT (10*n)

int n = 0;
std::vector<int> queenIndexByColumn;
std::vector<int> queensInRow;
std::vector<int> queensInD1;
std::vector<int> queensInD2;
std::vector<int> conflictsPerQueen;

int randomBetween(int min, int max) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}


int conflicts(int queen) {
    int col = queen;
    int row = queenIndexByColumn[col];
    return queensInRow[row] + queensInD1[n - 1 + col - row] + queensInD2[col + row] - 3;
}


int getRowWithMinConflict(int col) {
    std::vector<int> potentialConflicts(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == col) {
            continue;
        }
        int row = queenIndexByColumn[i];
        potentialConflicts[row]++;
        int d1 = row + std::abs(i - col);
        int d2 = row - std::abs(i - col);
        if (d1 >= 0 && d1 < n) {
            potentialConflicts[d1]++;
        }
        if (d2 >= 0 && d2 < n) {
            potentialConflicts[d2]++;
        }
    }
    std::vector<int> possibleRows;
    int minConflicts = n + 1;
    for (int i = 0; i < n; i++) {
        if (potentialConflicts[i] < minConflicts) {
            minConflicts = potentialConflicts[i];
            possibleRows.clear();
            possibleRows.push_back(i);
        } else if (potentialConflicts[i] == minConflicts) {
            possibleRows.push_back(i);
        }
    }
    if (possibleRows.size() == 1) {
        return possibleRows[0];
    }
    return possibleRows[randomBetween(0, possibleRows.size() - 1)];
}


int getColWithQueenWithMaxConf() {
    std::vector<int> possiblePositions;
    int maxConflicts = -1;
    for (int i = 0; i < n; i++) {
        if (conflictsPerQueen[i] > maxConflicts) {
            maxConflicts = conflictsPerQueen[i];
            possiblePositions.clear();
            possiblePositions.push_back(i);
        } else if (conflictsPerQueen[i] == maxConflicts) {
            possiblePositions.push_back(i);
        }
    }
    if (possiblePositions.size() == 1) {
        return possiblePositions[0];
    }
    return possiblePositions[randomBetween(0, possiblePositions.size() - 1)];
}

void generateStartingQueens() {
    int t = 1;
    for (int i = 0; i < n; i++) {
        queenIndexByColumn[i] = t;
        t += 2;
        if (t >= n) {
            t = 0;
        }
    }
}

void generateStartingConflicts() {
    conflictsPerQueen = std::vector(n, 0);
    for (int col = 0; col < n; col++) {
        int row = queenIndexByColumn[col];
        queensInD1[n - 1 + col - row]++;
        queensInD2[row + col]++;
    }
    for (int col = 0; col < n; col++) {
        conflictsPerQueen[col] = conflicts(col);
    }
}

int updateConflicts() {
    int totalConflicts = 0;
    for (int i = 0; i < n; i++) {
        conflictsPerQueen[i] = conflicts(i);
        totalConflicts += conflictsPerQueen[i];
    }
    return totalConflicts;
}


void moveQueen(int col, int newRow) {
    int oldRow = queenIndexByColumn[col];
    queensInRow[oldRow]--;
    queensInRow[newRow]++;
    queensInD1[n - 1 + col - oldRow]--;
    queensInD2[oldRow + col]--;
    queensInD1[n - 1 + col - newRow]++;
    queensInD2[newRow + col]++;
    queenIndexByColumn[col] = newRow;
}

std::optional<std::vector<int>> solve() {
    int performedIterations = 0;
    generateStartingQueens();
    generateStartingConflicts();

    int totalConflicts = std::accumulate(conflictsPerQueen.begin(), conflictsPerQueen.end(), 0);
//    int lastCol = -1, lastRow = -1, repeatedCols = 0, repeatedRows = 0;
    while (performedIterations++ <= ITERATION_LIMIT) {
        if (totalConflicts == 0) {
            return queenIndexByColumn;
        }
        int col = getColWithQueenWithMaxConf();
//        if (col == lastCol) {
//            if (repeatedCols < 2) {
//                col = getColWithQueenWithMaxConf();
//            }
//            repeatedCols++;
//        } else {
//            lastCol = col;
//        }
        int newRow = getRowWithMinConflict(col);
//        if (newRow == lastRow) {
//            if (repeatedRows < 2) {
//                newRow = getRowWithMinConflict(col);
//            }
//            repeatedRows++;
//        } else {
//            lastRow = newRow;
//        }
        moveQueen(col, newRow);
        totalConflicts = updateConflicts();
    }
    return std::nullopt;
}

int main(int argc, char *argv[]) {

    std::cin >> n;
    queenIndexByColumn = std::vector<int>(n);
    queensInRow = std::vector<int>(n, 1);
    queensInD1 = std::vector<int>(2 * n - 1, 0);
    queensInD2 = std::vector<int>(2 * n - 1, 0);

    auto start = std::chrono::high_resolution_clock::now();
    std::optional<std::vector<int>> result = solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    if (n > 100) {
        std::cout << std::fixed << std::setprecision(2) << duration.count() << std::endl;
    } else {
        if (result.has_value()) {
            if (argc <= 1) {
                std::cout << "[";
                for (int i = 0; i < n - 1; i++) {
                    std::cout << result.value()[i] << ", ";
                }
                std::cout << result.value()[n - 1] << "]" << std::endl;
            } else {
                std::vector<int> transposed(n);
                for (int i = 0; i < n; i++) {
                    transposed[result.value()[i]] = i;
                }
                for (auto colIndex: transposed) {
                    std::string rowString(n, '_');
                    rowString[colIndex] = '*';
                    std::string spacedRowString;
                    spacedRowString.reserve(2 * rowString.length());
                    for (char i: rowString) {
                        spacedRowString += i;
                        spacedRowString += ' ';
                    }
                    std::cout << spacedRowString << std::endl;
                }
            }

        } else {
            std::cout << -1 << std::endl;
        }
    }

    return 0;
}
