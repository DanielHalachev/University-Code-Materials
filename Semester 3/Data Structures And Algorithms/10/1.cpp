https://www.hackerrank.com/contests/sda-hw-10-2021/challenges/if-you-reading-this-get-baited

#include <list>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;
    std::unordered_set<int> vertices;

    bool hasCycle(int v, std::unordered_set<int> &visited) {
        if (visited.find(v) != visited.end()) {
            return true;
        }
        visited.insert(v);
        if (this->adjacencyList.find(v) != this->adjacencyList.end()) {
            for (int i: this->adjacencyList.find(v)->second) {
                if (visited.find(i) != visited.end() || hasCycle(i, visited)) {
                    return true;
                }
            }
        }
        visited.erase(v);
        return false;
    }

public:
    void insertEdge(int start, int end) {
        this->vertices.insert(start);
        this->vertices.insert(end);
        const std::unordered_map<int, std::vector<int>>::iterator &iterator = adjacencyList.find(start);
        if (iterator != adjacencyList.end()) {
            iterator->second.push_back(end);
        } else {
            adjacencyList.insert(std::make_pair(start, std::vector<int>())).first->second.push_back(end);
        }
    }

    bool answer() {
        std::unordered_set<int> visited;
        for (const auto &i: this->vertices) {
            visited.clear();
            if (hasCycle(i, visited)) {
                return true;
            }
        }
        return false;
    }

};

int main() {
    int q;
    std::cin >> q;
    int sizeOfQuery;
    int temp1, temp2;
    bool *results = new bool[q];
    for (int i = 0; i < q; i++) {
        std::cin >> sizeOfQuery;
        Graph tempGraph;
        for (int j = 0; j < sizeOfQuery; j++) {
            std::cin >> temp1 >> temp2;
            tempGraph.insertEdge(temp1, temp2);
        }
        results[i] = tempGraph.answer();
    }
    for (int i = 0; i < q; i++) {
        std::cout << results[i] << " ";
    }
    delete[] results;
}
