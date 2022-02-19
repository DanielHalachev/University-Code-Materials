https://www.hackerrank.com/contests/12-2/challenges/2-146

#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Edge {
public:
    long long start;
    long long end;
    long long effort;
    long long profitPerEffort;
    long long id;

    Edge(long long start, long long end, long long effort,
         long long profitPerEffort, long long id) {
        this->start = start;
        this->end = end;
        this->effort = effort;
        this->profitPerEffort = profitPerEffort;
        this->id = id;
    }

    bool operator<(const Edge &other) const {
        if (this->effort == other.effort) {
            return this->profitPerEffort >= other.profitPerEffort;
        }
        return this->effort < other.effort;
    }
};

class Graph {
private:
    std::vector<Edge> graphEdges;
    std::vector<long long> parentVector;

public:
    explicit Graph(long long n) {
        this->parentVector.resize(n + 1);
        for (long long i = 0; i <= n; i++) {
            this->parentVector[i] = i;
        }
    }

    void insertEdge(long long start, long long end, long long effort,
                    long long profitPerEffort, long long id) {
        this->graphEdges.emplace_back(start, end, effort, profitPerEffort, id);
    }

    void unifyVertices(long long start, long long end) {
        long long set1 = findSet(start), set2 = findSet(end);
        if (set1 == set2) {
            return;
        }
        parentVector[set2] = set1;
    }

    long long findSet(long long vertex) {
        if (parentVector[vertex] == vertex) {
            return vertex;
        }
        parentVector[vertex] = findSet(parentVector[vertex]);
        return parentVector[vertex];
    }

    std::set<long long> kruskal() {
        std::set<long long> answer;
        std::sort(graphEdges.begin(), graphEdges.end());
        for (auto edge: this->graphEdges) {
            if (this->findSet(edge.start) != this->findSet(edge.end)) {
                this->unifyVertices(edge.start, edge.end);
                answer.insert(edge.id);
            }
        }
        return answer;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n, m, start, end, effort, profitPerEffort;
    std::cin >> n >> m;
    Graph graph(n);
    for (long long i = 0; i < m; i++) {
        std::cin >> start >> end >> effort >> profitPerEffort;
        graph.insertEdge(start, end, effort, profitPerEffort, i + 1);
    }
    for (long long i: graph.kruskal()) {
        printf("%llu\n", i);
    }
}
