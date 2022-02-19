https://www.hackerrank.com/contests/exam-2022-part1-sda/challenges/sda-exam

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

int M = INT32_MAX;

class Graph {
public:
    class Node {
    public:
        int end;
        int weight;

        Node() = default;

        Node(int end, int weight) {
            this->end = end;
            this->weight = weight;
        }

        bool operator<(const Node &other) const {
            return this->weight > other.weight;
        }
    };

    int numberOfVertices = 0;
    std::unordered_map<int, std::vector<Node>> adjacencyList;

    explicit Graph(int n) {
        this->numberOfVertices = n;
    }

    void addEdge(int start, int end) {
        this->adjacencyList[start].emplace_back(end, 6);
        this->adjacencyList[end].emplace_back(start, 6);
    }

    std::vector<int> dijkstra(int source) {
        std::vector<int> distances(this->numberOfVertices + 1, M);
        std::priority_queue<Node> heap;
        std::unordered_set<int> visited;
        distances[source] = 0;
        heap.emplace(source, 0);
        while (!heap.empty()) {
            int vertex = heap.top().end;
            heap.pop();
            if (visited.find(vertex) != visited.end()) {
                continue;
            }
            for (Node node: this->adjacencyList[vertex]) {
                if (distances[node.end] > distances[vertex] + node.weight) {
                    distances[node.end] = distances[vertex] + node.weight;
                    heap.emplace(node.end, distances[node.end]);
                }
            }
            visited.insert(vertex);
        }
        std::vector<int> result(this->numberOfVertices - 1);
        int j = 0;
        for (int i = 1; i <= this->numberOfVertices; i++) {
            if (i == source) {
                continue;
            }
            result[j] = (distances[i] == M ? -1 : distances[i]);
            j++;
        }
        return result;
    }
};

int main() {
    int q = 0;
    std::cin >> q;
    int n;
    int m;
    int start, end;
    int source;

    for (int i = 0; i < q; i++) {
        std::cin >> n >> m;
        Graph g(n);
        for (int j = 0; j < m; j++) {
            std::cin >> start >> end;
            g.addEdge(start, end);
        }
        std::cin >> source;
        for (int integer: g.dijkstra(source)) {
            std::cout << integer << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
