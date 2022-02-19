https://www.hackerrank.com/contests/12-2/challenges/roads-5

#include <list>
#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::pair<int, int>> graphEdges;
    std::vector<int> parentVector;

public:
    explicit Graph(int n) {
        this->parentVector.resize(n + 1);
        for (int i = 0; i < n; i++) {
            this->parentVector[i] = i;
        }
    }

    void insertEdge(int start, int end) {
        this->graphEdges.emplace_back(start, end);
    }

    //Chazelle algorithm - determine the parent of each vertex and try to make an MST
    void unifyVertices(int start, int end) {
        int set1 = findSet(start), set2 = findSet(end);
        if (set1 == set2) {
            return;
        }
        parentVector[set2] = set1;
    }

    int findSet(int vertex) {
        if (parentVector[vertex] == vertex) {
            return vertex;
        }
        parentVector[vertex] = findSet(parentVector[vertex]);
        return parentVector[vertex];
    }

    void updateAll() {
        for (const std::pair<int, int> &pair: this->graphEdges) {
            unifyVertices(pair.first, pair.second);
        }
    }

    bool isAccessible(int start, int end) {
        // for two vertices to be connected, they need to be in the same MST
        return this->findSet(start) == this->findSet(end);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q, start, end, queryType;
    std::cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end;
        graph.insertEdge(start, end);
    }
    graph.updateAll();
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::cin >> queryType >> start >> end;
        if (queryType == 2) {
            graph.unifyVertices(start, end);
        } else {
            printf("%d", graph.isAccessible(start, end));
        }
    }
}
