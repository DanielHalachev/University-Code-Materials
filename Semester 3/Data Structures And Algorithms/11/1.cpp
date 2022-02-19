https://www.hackerrank.com/contests/sda-hw-11-2021/challenges/shortest-paths-2

#include <set>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define BULLSHIT 1000000007

class Graph {
private:
    std::unordered_map<unsigned long long, std::vector<std::pair<unsigned long long, unsigned long long>>> adjacencyList;
public:
    void answer(unsigned long long n) {
        // replaces infinity
        unsigned long long M = ULLONG_MAX;
        std::vector<unsigned long long> distance(n + 1, M);
        std::vector<unsigned long long> paths(n + 1, 0);
        std::priority_queue<std::pair<unsigned long long, unsigned long long>, std::vector<std::pair<unsigned long long, unsigned long long>>, std::greater<>> heap;
        heap.emplace(0, 1);
        // distance 1->1 is 0
        distance[1] = 0;
        paths[1] = 1;
        while (!heap.empty()) {
            unsigned long long length = heap.top().first;
            unsigned long long vertex = heap.top().second;
            heap.pop();
            if (length > distance[vertex]) {
                continue;
            }
            for (std::pair<unsigned long long, unsigned long long> pair: this->adjacencyList[vertex]) {
                unsigned long long child = pair.first;
                unsigned long long weight = pair.second;
                // in case of a match in the shortest paths
                if (weight + length == distance[child]) {
                    (paths[child] += paths[vertex]) %= BULLSHIT;
                }
                // relaxation
                if (weight + length < distance[child]) {
                    distance[child] = weight + length;
                    paths[child] = paths[vertex];
                    heap.emplace(distance[child], child);
                }
            }
        }
        if (distance[n] == M) {
            std::cout << -1 << " " << 0;
        } else {
            std::cout << distance[n] << " " << paths[n];
        }
    }

    void addEdge(unsigned long long start, unsigned long long end, unsigned long long weight) {
        auto it = this->adjacencyList.find(start);
        if (it == this->adjacencyList.end()) {
            this->adjacencyList.emplace(start,
                                        std::vector<std::pair<unsigned long long, unsigned long long>>()).first->second.emplace_back(
                    end,
                    weight);
        } else {
            it->second.emplace_back(end, weight);
        }
    }
};

int main() {
    unsigned long long n, m;
    std::cin >> n >> m;
    unsigned long long tempStart, tempEnd, tempWeight;
    Graph graph;
    for (unsigned long long i = 0; i < m; i++) {
        std::cin >> tempStart >> tempEnd >> tempWeight;
        graph.addEdge(tempStart, tempEnd, tempWeight);
    }
    graph.answer(n);
}
