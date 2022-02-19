https://www.hackerrank.com/contests/12-2/challenges/challenge-2799

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>


class Edge {
public:
    int start;
    int end;
    int optimalSpeed;

    Edge(int start, int end, int optimalSpeed) {
        this->start = start;
        this->end = end;
        this->optimalSpeed = optimalSpeed;
    }

    bool operator<(const Edge &other) const {
        if (this->optimalSpeed == other.optimalSpeed) {
            if (this->start == other.start) {
                return this->end < other.end;
            }
            return this->start < other.start;
        }
        return this->optimalSpeed < other.optimalSpeed;
    }
};

class Graph {
private:
    std::set<Edge> graphEdges;
    std::vector<int> parentVector;

public:
    explicit Graph(int n) {
        this->parentVector.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            this->parentVector[i] = i;
        }
    }

    Graph(std::set<Edge> edges, int n) {
        this->graphEdges = std::move(edges);
        this->parentVector = std::vector<int>(n + 1);
        for (int i = 0; i <= n; i++) {
            this->parentVector[i] = i;
        }
    }

//    void insertEdge(int start, int end, int optimalSpeed) {
//        this->graphEdges.emplace(start, end, optimalSpeed);
//    }

    void inline unifyVertices(int start, int end) {
        int set1 = findSet(start), set2 = findSet(end);
        if (set1 == set2) {
            return;
        }
        parentVector[set2] = set1;
    }

    int inline findSet(int vertex) {
        if (parentVector[vertex] == vertex) {
            return vertex;
        }
        parentVector[vertex] = findSet(parentVector[vertex]);
        return parentVector[vertex];
    }

    std::set<Edge> inline kruskal() {
        std::set<Edge> answer;
        for (auto edge: this->graphEdges) {
            if (this->findSet(edge.start) != this->findSet(edge.end)) {
                this->unifyVertices(edge.start, edge.end);
                answer.insert(edge);
            }
        }
        return answer;
    }

    void inline update() {
        for (int i = 0; i < this->parentVector.size(); i++) {
            this->parentVector[i] = i;
        }
        this->graphEdges.erase(this->graphEdges.begin());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, start, end, optimalSpeed;
    std::cin >> n >> m;
    // enter edges
    std::set<Edge> edges;
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end >> optimalSpeed;
        edges.emplace(start, end, optimalSpeed);
    }
    // start and remove the smallest edge one by one
    Graph graph(edges, n);
    std::set<Edge> tempKruskal = graph.kruskal();
    int tempLow = tempKruskal.begin()->optimalSpeed, tempHigh = tempKruskal.rbegin()->optimalSpeed;
    int tempRange = tempHigh - tempLow;
    while (tempKruskal.size() == n - 1) {
        graph.update();
        tempKruskal = graph.kruskal();
        int x = tempKruskal.rbegin()->optimalSpeed - tempKruskal.begin()->optimalSpeed;
        if (x < tempRange) {
            tempRange = x;
            tempLow = tempKruskal.begin()->optimalSpeed;
            tempHigh = tempKruskal.rbegin()->optimalSpeed;
        }
    }
    printf("%d %d", tempLow, tempHigh);
}
