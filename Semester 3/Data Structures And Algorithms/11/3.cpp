https://www.hackerrank.com/contests/sda-hw-11-2021/challenges/discos

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

const int M = 1000000;

std::unordered_set<int> T;

class Node {
public:
    int endVertex;  // stores the second vertex of the edge
    int weight;     // stores the weight of the edge
    Node(int end, int weight) {
        this->endVertex = end;
        this->weight = weight;
    }
};

struct NodeComparator {
    bool operator()(const Node &first, const Node &second) {
        return first.weight > second.weight;
    }
};


class Graph {
private:
    std::unordered_map<int, std::vector<Node>> adjacencyList; // it's a vector because there may be repeated Nodes
    int numberOfVertices;

public:
    explicit Graph(int n) {
        this->numberOfVertices = n;
    }

    void addEdge(int start, int end, int weight) {
        this->adjacencyList[start].emplace_back(end, weight);
        this->adjacencyList[end].emplace_back(start, weight);
    }

    std::vector<int> inline dijkstra(int source) {
        std::priority_queue<Node, std::vector<Node>, NodeComparator> heap;
        std::vector<int> distances(this->numberOfVertices, M);
        std::vector<int> visited(this->numberOfVertices, 0);
        // distance source->source is 0
        distances[source] = 0;
        heap.emplace(source, 0);
        while (!heap.empty()) {
            int vertex = heap.top().endVertex;
            heap.pop();
            // to avoid repetition
            if (visited[vertex]) {
                continue;
            }
            for (Node node: adjacencyList[vertex]) {
                // relaxation
                if (distances[node.endVertex] > distances[vertex] + node.weight) {
                    distances[node.endVertex] = distances[vertex] + node.weight;
                    heap.emplace(node.endVertex, distances[node.endVertex]);
                }
            }
            // mark as visited to avoid going through the same vertex again
            visited[vertex] = 1;
        }
        return distances;
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    // include 1 artificial vertex
    Graph graph(n + 1);
    // enter graph
    int start, end, weight;
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end >> weight;
        graph.addEdge(start, end, weight);
    }
    // enter which elements are part of T
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        std::cin >> start;
        T.insert(start);
        graph.addEdge(n, start, 0); // add an edge between the artificial vertex and all T vertices
    }
    int q;
    std::cin >> q;
    std::vector<int> distances = graph.dijkstra(n);
    for (int i = 0; i < q; i++) {
        std::cin >> start;
        std::cout << distances[start] << std::endl;
    }
}
