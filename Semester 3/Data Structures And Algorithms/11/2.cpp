https://www.hackerrank.com/contests/sda-hw-11-2021/challenges/tunnel-maps

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

const int M = 1000000000;

class Node {
public:
    int endVertex;  // stores the second vertex of the edge
    int kilograms;  // stores the kilograms that Santa needs to drop
    int time;       // stores the time required, it is the weight of the edge

    Node(int end, int kilograms, int time) {
        this->endVertex = end;
        this->kilograms = kilograms;
        this->time = time;
    }
};

// for the heap, we need to sort the edges by time because it is more important than Santa's kilograms
struct NodeComparator {
    bool operator()(const Node &first, const Node &second) {
        return first.time > second.time;
    }
};


class Graph {
private:
    std::unordered_map<int, std::vector<Node>> adjacencyList; // it's a vector because there may be repeated Nodes
    int numberOfVertices;

    int dijkstra(int maxKilograms) {
        std::priority_queue<Node, std::vector<Node>, NodeComparator> heap;
        std::vector<int> durations(this->numberOfVertices + 1, M);
        std::set<int> visited;
        // duration 1->1 is 0
        durations[1] = 0;
        heap.emplace(1, 0, 0);
        while (!heap.empty()) {
            int vertex = heap.top().endVertex;
            heap.pop();
            // to avoid repetition
            if (visited.find(vertex) != visited.end()) {
                continue;
            }
            for (Node node: adjacencyList[vertex]) {
                // relaxation
                if (node.kilograms <= maxKilograms && durations[node.endVertex] > durations[vertex] + node.time) {
                    durations[node.endVertex] = durations[vertex] + node.time;
                    heap.emplace(node.endVertex, 0, durations[node.endVertex]);
                }
            }
            // mark as visited to avoid going through the same vertex again
            visited.insert(vertex);
        }
        // return path time between 1 and N bounded by maxKilograms
        return durations.back();
    }

public:
    explicit Graph(int n) {
        this->numberOfVertices = n;
    }

    void addEdge(int start, int end, int kilograms, int time) {
        this->adjacencyList[start].emplace_back(end, kilograms, time);
    }

    // shooting in the dark trying to find the least kilograms under timeLimit
    int answer(int timeLimit) {
        int left = 1;
        int right = M;
        int answer = M;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            int time = dijkstra(middle);
            if (time <= timeLimit) {
                answer = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        if (answer == M) {
            return -1;
        }
        return answer;
    }
};


int main() {
    int n, m, timeLimit;
    std::cin >> n >> m >> timeLimit;
    Graph graph(n);
    int start, end, kilograms, time;
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end >> kilograms >> time;
        graph.addEdge(start, end, kilograms, time);
    }
    std::cout << graph.answer(timeLimit) << std::endl;
}
