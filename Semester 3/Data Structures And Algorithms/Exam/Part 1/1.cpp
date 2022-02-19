https://www.hackerrank.com/contests/exam-2022-part1-sda/challenges/unique-rows

#include <iostream>
#include <unordered_map>

int main() {
    int n;
    int m;
    std::cin >> n >> m;
    std::string line;
    std::unordered_map<std::string, int> map;
    char ch;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> ch;
            line += ch;
        }
        map[line]++;
        line = "";
    }
    int count = 0;
    for (const auto &pair: map) {
        if (pair.second == 1) {
            count++;
        }
    }
    std::cout << count;
    return 0;
}
