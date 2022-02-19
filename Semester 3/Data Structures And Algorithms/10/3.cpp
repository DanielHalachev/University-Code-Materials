https://www.hackerrank.com/contests/sda-hw-10-2021/challenges/challenge-2752


#include <unordered_set>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <iostream>

typedef const std::vector<std::string> Dictionary;
typedef std::unordered_map<char, std::vector<char>> AlphabeticalOrder;

class AlphabetGraph {
private:
    AlphabeticalOrder adjacencyList;
    std::list<char> alphabet;

    void DFS(char letter, std::unordered_set<char> &visited) {
        visited.insert(letter);
        for (char &ch: this->adjacencyList[letter]) {
            if (visited.find(ch) == visited.end()) {
                DFS(ch, visited);
            }
        }
        this->alphabet.push_front(letter);
    }

public:
    std::list<char> answer(Dictionary &dictionary) {
        for (const std::string &word: dictionary) {
            for (const char &ch: word) {
                this->adjacencyList[ch] = std::vector<char>(0);
            }
        }
        for (size_t i = 0; i < dictionary.size() - 1; i++) {
            size_t minimumLength = std::min(dictionary[i].length(), dictionary[i + 1].length());
            for (size_t j = 0; j < minimumLength; j++) {
                if (dictionary[i][j] != dictionary[i + 1][j]) {
                    this->adjacencyList[dictionary[i][j]].push_back(dictionary[i + 1][j]);
                    break;
                }
            }
        }
        std::unordered_set<char> visitedLetters;
        for (auto &pair: this->adjacencyList) {
            if (visitedLetters.find(pair.first) == visitedLetters.end()) {
                DFS(pair.first, visitedLetters);
            }
        }
        return this->alphabet;
    }

};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> dictionary(n);
    for (int i = 0; i < n; i++) {
        std::cin >> dictionary[i];
    }
    AlphabetGraph graph;
    for (auto i: graph.answer(dictionary)) {
        std::cout << i << " ";
    }
}
