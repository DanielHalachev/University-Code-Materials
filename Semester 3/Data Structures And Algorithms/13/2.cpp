https://www.hackerrank.com/contests/sda-hw-13-2022/challenges/challenge-2806

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>

class Graph {
private:
    unsigned long numberOfVertices;
    std::unordered_map<int, std::unordered_set<int>> adjacencyList;
    std::vector<int> degrees;
public:
    explicit Graph(int V) {
        this->numberOfVertices = V;
        this->degrees.resize(this->numberOfVertices, 0);
    }

    void addEdge(int start, int end) {
        if (this->adjacencyList.find(start) == this->adjacencyList.end()) {
            this->adjacencyList.emplace(start, std::unordered_set<int>());
        }
        if (this->adjacencyList.find(end) == this->adjacencyList.end()) {
            this->adjacencyList.emplace(end, std::unordered_set<int>());
        }
        this->adjacencyList[start].emplace(end);
        this->adjacencyList[end].emplace(start);
        this->degrees[start]++;
        this->degrees[end]++;
    }

    std::set<int> getAnswer() {
        std::queue<int> queue;
        for (int i = 0; i < this->numberOfVertices; i++)
            if (degrees[i] == 1) {
                queue.push(i);
            }

        while (numberOfVertices > 2) {
            unsigned long temp = queue.size();
            this->numberOfVertices -= temp;
            for (unsigned long i = 0; i < temp; i++) {
                int vertex = queue.front();
                queue.pop();
                for (int neighbour: this->adjacencyList[vertex]) {
                    this->degrees[neighbour]--;
                    if (this->degrees[neighbour] == 1) {
                        queue.push(neighbour);
                    }
                }
            }
        }
        std::set<int> answer;
        while (!queue.empty()) {
            answer.emplace(queue.front());
            queue.pop();
        }
        return answer;
    }
};

int main() {
    int numberOfVertices = 0;
    std::cin >> numberOfVertices;
    Graph graph(numberOfVertices);
    int start, end;
    for (int i = 1; i < numberOfVertices; i++) {
        std::cin >> start >> end;
        graph.addEdge(start, end);
    }
    std::set<int> answer = graph.getAnswer();
    for (int root: answer) {
        std::cout << root << " ";
    }
}
