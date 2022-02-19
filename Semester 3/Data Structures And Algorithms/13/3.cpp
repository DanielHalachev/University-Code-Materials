https://www.hackerrank.com/contests/sda-hw-13-2022/challenges/islander

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

const int LIMIT = 10'000;

inline void DFS(int source, std::unordered_map<int, std::unordered_set<int>> &adjList, std::unordered_set<int> &visited) {
    visited.emplace(source);
    for (int i: adjList[source]) {
        if (visited.find(i) == visited.end()) {
            DFS(i, adjList, visited);
        }
    }
}

int main() {
    std::vector<int> vertexDegrees(LIMIT, 0);
    int numberOfEdges = 0, numberOfVertices = 0;
    std::vector<std::string> result;

    int a, b;
    int numberOfQueries = 0;
    std::cin >> numberOfQueries;

    while (numberOfQueries--) {
        int numberOfOddDegrees = 0;
        std::cin >> numberOfVertices >> numberOfEdges;

        std::fill(vertexDegrees.begin(), vertexDegrees.end(), 0);
        std::unordered_set<int> visited;
        std::unordered_map<int, std::unordered_set<int>> adjacencyList;
        for (int i = 0; i < numberOfEdges; i++) {
            std::cin >> a >> b;
            vertexDegrees[a]++;
            vertexDegrees[b]++;
            if (adjacencyList.find(a) == adjacencyList.end()) {
                adjacencyList.emplace(a, std::unordered_set<int>());
            }
            if (adjacencyList.find(b) == adjacencyList.end()) {
                adjacencyList.emplace(b, std::unordered_set<int>());
            }
            adjacencyList[a].emplace(b);
            adjacencyList[b].emplace(a);
        }
        DFS(a, adjacencyList, visited);
        if (visited.size() != numberOfVertices) {
            result.emplace_back("none");
            continue;
        }
        for (int vertexDegree: vertexDegrees) {
            if (vertexDegree % 2 != 0) {
                numberOfOddDegrees++;
            }
        }
        if (numberOfOddDegrees == 0) {
            result.emplace_back("ecycle");
        } else if (numberOfOddDegrees == 2) {
            result.emplace_back("epath");
        } else {
            result.emplace_back("none");
        }
    }

    for (std::string &string: result) {
        std::cout << string << std::endl;
    }
    return 0;
}
