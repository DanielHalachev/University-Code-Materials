https://www.hackerrank.com/contests/sda-hw-13-2022/challenges/all-paths42

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

int correctPaths = 0;

class Graph {
private:
    std::unordered_map<int, std::unordered_set<int>> adjacencyList;
public:
    int numberOfVertices = 0;

    void addEdge(int start, int end) {
        if (this->adjacencyList.find(start) == this->adjacencyList.end()) {
            this->adjacencyList.emplace(start, std::unordered_set<int>());
        }
        if (this->adjacencyList.find(end) == this->adjacencyList.end()) {
            this->adjacencyList.emplace(end, std::unordered_set<int>());
        }
        this->adjacencyList[start].emplace(end);
        this->adjacencyList[end].emplace(start);
    }

    void DFS(int source, int end, std::unordered_set<int> &visited) {
        visited.emplace(source);
        if (source == end) {
            if (visited.size() == this->adjacencyList.size()) {
                correctPaths++;
            }
            visited.erase(source);
            return;
        }
        for (int i: this->adjacencyList[source]) {
            if (visited.find(i) == visited.end()) {
                DFS(i, end, visited);
            }
        }
        visited.erase(source);
    }

    int countHamiltons(int start, int end) {
        std::unordered_set<int> visited;
        DFS(start, end, visited);
        return correctPaths;
    }
};

int main() {
    int rows, columns;
    std::cin >> rows >> columns;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(columns));
    char symbol;
    int start = 0, end = 0, counter = 0;
    Graph graph;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cin >> symbol;
            matrix[i][j] = symbol;
            if (symbol == 's') {
                start = counter;
            } else if (symbol == 'e') {
                end = counter;
            }
            if (symbol != 'x') {
                if (j > 0 && matrix[i][j - 1] != 'x') {
                    graph.addEdge(counter, counter - 1);
                }
                if (i > 0 && matrix[i - 1][j] != 'x') {
                    graph.addEdge(counter, counter - columns);
                }
            }
            counter++;
        }
    }
    graph.numberOfVertices = counter;
    std::cout << graph.countHamiltons(start, end);
    return 0;
}
