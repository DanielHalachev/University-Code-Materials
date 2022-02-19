https://www.hackerrank.com/contests/exam-2022-part2-sda/challenges/leafs

#include <unordered_map>
#include <unordered_set>
#include <iostream>

std::unordered_map<int, int> alreadyCalculated;

class Graph {
public:

    std::unordered_map<int, std::unordered_set<int>> adjacencyList;

    void addEdge(int start, int end) {
        this->adjacencyList[start].emplace(end);
    }

    void dfs(int source, std::unordered_set<int> &visited) {
        if (visited.find(source) != visited.end()) {
            return;
        }
        visited.emplace(source);
        int sum = source;
        for (int i: this->adjacencyList[source]) {
            if (alreadyCalculated.find(i) != alreadyCalculated.end()) {
                sum += alreadyCalculated[i];
            } else {
                dfs(i, visited);
                sum += alreadyCalculated[i];
            }
        }
        visited.erase(source);
        alreadyCalculated[source] = sum;
    }
};


int main() {
    Graph g;
    int m;
    int k;
    std::cin >> m >> k;
    int start, end;
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end;
        g.addEdge(start, end);
    }

    int source;
    std::unordered_set<int> visited;
    for (int i = 0; i < k; i++) {
        std::cin >> source;
        if (alreadyCalculated.find(source) == alreadyCalculated.end()) {
            visited.clear();
            g.dfs(source, visited);
        }
        std::cout << alreadyCalculated[source] - source << std::endl;
    }
}
