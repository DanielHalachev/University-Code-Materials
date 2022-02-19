https://www.hackerrank.com/contests/sda-hw-9-2021/challenges/longest-match

#include <iostream>
#include <string>
#include <vector>

int longestSubsequenceLength(std::string first, std::string second, int firstSize, int secondSize) {
    int maxLength = 0;
    std::vector<int> previous(secondSize + 1, 0);
    std::vector<int> current(secondSize + 1, 0);
    for (int i = 1; i <= firstSize; i++) {
        for (int j = 1; j <= secondSize; j++) {
            if (first[i] == second[j]) {                
                current[j] = previous[j - 1] + 1;
                maxLength = std::max(maxLength, current[j]);
            } else {
                current[j] = 0;
            }
        }
        previous = current;
    }
    return maxLength;
}

int main() {
    std::string first, second;
    std::cin >> first >> second;
    int m = first.length(), n = second.length();
    std::cout << longestSubsequenceLength(first, second, m, n);
    return 0;
}
