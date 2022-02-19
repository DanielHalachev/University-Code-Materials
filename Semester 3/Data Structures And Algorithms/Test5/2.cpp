https://www.hackerrank.com/contests/sda-2021-2022-test5-8dec/challenges/challenge-3157

#include <map>
#include <iostream>
#include <vector>

int main() {
    std::map<int, int> numbers;
    int n;
    std::cin >> n;
    int temp;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        auto position = numbers.find(temp);
        if (position == numbers.end()) {
            numbers.emplace(temp, 1);
        } else {
            position->second++;
        }
    }
    for (std::pair<int, int> pair: numbers) {
        if (pair.second % 2 == 1) {
            sum += pair.first * pair.second;
        }
    }
    std::cout << sum;
}
