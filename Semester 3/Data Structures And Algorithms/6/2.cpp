https://www.hackerrank.com/contests/sda-hw-6-2021/challenges/top

#include <iostream>
#include <queue>
#include <map>

struct Node {
    Node *left;
    Node *right;
    int distance;
    int data;

    explicit Node(int data) {
        this->left = this->right = nullptr;
        this->data = data;
        this->distance = 0;
    }
};

void printTopVisible(Node *root) {
    if (root == nullptr) {
        return;
    }
    std::queue<Node *> queueOfNodes;
    // stores distances
    std::map<int, int> mapOfDistances;
    int tempDistance = 0;
    root->distance = tempDistance;
    queueOfNodes.push(root);
    while (!queueOfNodes.empty()) {
        tempDistance = root->distance;
        // if there is no such tempDistance in the map
        if (mapOfDistances.count(tempDistance) == 0)
            mapOfDistances[tempDistance] = root->data;
        if (root->left != nullptr) {
            // left child has x=x-1
            root->left->distance = tempDistance - 1;
            queueOfNodes.push(root->left);
        }
        if (root->right != nullptr) {
            // right child has x=x+1
            root->right->distance = tempDistance + 1;
            queueOfNodes.push(root->right);
        }
        // throw away the root
        queueOfNodes.pop();
        // make root the next (left child)
        root = queueOfNodes.front();
    }
    // print everything
    for (auto &pair: mapOfDistances) {
        std::cout << pair.second << " ";
    }
}

int main() {
    int n;
    std::cin >> n;
    Node *root = new Node(0);
    int child1, child2;
    std::vector<Node *> nodes(n);
    nodes[0] = root;
    for (int i = 0; i < n - 1; i++) {
        std::cin >> child1 >> child2;
        if (child1 == -1) {
            nodes[i]->left = nullptr;
        } else {
            Node *temp1 = new Node(child1);
            nodes[child1] = temp1;
            nodes[i]->left = temp1;
        }
        if (child2 == -1) {
            nodes[i]->right = nullptr;
        } else {
            Node *temp2 = new Node(child2);
            nodes[child2] = temp2;
            nodes[i]->right = temp2;
        }
    }
    printTopVisible(root);
    for(int i = 0; i < n; i++){
        delete nodes[i];
    }
    return 0;
}
