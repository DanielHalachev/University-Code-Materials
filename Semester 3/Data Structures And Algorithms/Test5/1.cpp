https://www.hackerrank.com/contests/sda-2021-2022-test5-8dec/challenges/challenge-3156

#include <map>
#include <iostream>
#include <vector>

int main() {
    std::map<std::string, int> words;
    int n;
    std::cin >> n;
    std::string temp;
    std::vector<std::string> list(n);
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        list[i] = temp;
        auto position = words.find(temp);
        if (position == words.end()) {
            words.emplace(temp, 1);
        } else {
            position->second++;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << words.find(list[i])->second << " ";
    }

}
