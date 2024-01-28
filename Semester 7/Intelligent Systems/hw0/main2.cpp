#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <iomanip>
#include <chrono>
#include <map>

std::stack<std::string> stepStack;

std::string swapPositions(std::string frogs, uint16_t i, uint16_t j) {
    char c = frogs[i];
    frogs[i] = frogs[j];
    frogs[j] = c;
    return frogs;
}


bool dfs(const std::string &frogs, const std::string &goalFrogs, std::unordered_set<std::string> &visited, int steps,
         uint16_t blank) {
    if (frogs == goalFrogs) {
        return true;
    }

    std::map<std::string, uint16_t> children;

    //  * L _ *
    if (blank >= 1 && frogs[blank - 1] == 'L') {
        children[swapPositions(frogs, blank, blank - 1)] = blank - 1;
    }
    // * _ R *
    if (blank <= (frogs.length() - 2) && frogs[blank + 1] == 'R') {
        children[swapPositions(frogs, blank, blank + 1)] = blank + 1;
    }
    // * L . _ *
    if (blank >= 2 && frogs[blank - 2] == 'L') {
        children[swapPositions(frogs, blank, blank - 2)] = blank - 2;

    }
    // * _ . R *
    if (blank <= frogs.length() - 3 && frogs[blank + 2] == 'R') {
        children[swapPositions(frogs, blank, blank + 2)] = blank + 2;

    }

    for (const auto &child: children) {
        if (visited.find(child.first) == visited.end()) {
            visited.insert(child.first);
            if (dfs(child.first, goalFrogs, visited, steps + 1, child.second)) {
                stepStack.push(child.first);
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    uint16_t n;
    std::cin >> n;

    std::string initialFrogs = std::string(n, 'L') + "_" + std::string(n, 'R');
    std::string goalFrogs = std::string(n, 'R') + "_" + std::string(n, 'L');

    std::unordered_set<std::string> visited;
    visited.insert(initialFrogs);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    if (!dfs(initialFrogs, goalFrogs, visited, 0, n)) {
        t2 = std::chrono::high_resolution_clock::now();
        std::cout << "No solution found." << std::endl;
    } else {
        t2 = std::chrono::high_resolution_clock::now();
        stepStack.push(initialFrogs);
        while (!stepStack.empty()) {
            std::cout << stepStack.top() << std::endl;
            stepStack.pop();
        }
    }
    if (argc > 1) {
        std::chrono::duration<double> duration = t2 - t1;
        std::cout << std::fixed << std::setprecision(2) << duration.count() << "s" << std::endl;
    }

    return 0;
}
