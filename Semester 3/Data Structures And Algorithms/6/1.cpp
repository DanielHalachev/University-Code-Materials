https://www.hackerrank.com/contests/sda-hw-6-2021/challenges/1-266

#include <iostream>
#include <vector>
#include <queue>

struct Node {
public:
    int data;
    std::vector<Node *> children;

    Node(int data) {
        this->data = data;
    }
};

int numberOfChildren(Node *node) {
    int numChildren = 0;
    if (node == nullptr)
        return 0;
    for (int i = 0; i < node->children.size(); i++) {
        numChildren += numberOfChildren(node->children[i]) + 1;
    }
    return numChildren;
}

int main() {
    int n;
    std::cin >> n;
    int tempParent, tempChild;
    std::vector<Node *> nodes(n);
    std::cin >> tempParent >> tempChild;
    nodes[0] = new Node(tempParent);
    Node *temp1 = new Node(tempChild);
    nodes[0]->children.push_back(temp1);
    nodes[tempChild] = temp1;
    for (int i = 2; i < n; i++) {
        std::cin >> tempParent >> tempChild;
        Node *temp = new Node(tempChild);
        nodes[tempParent]->children.push_back(temp);
        nodes[tempChild] = temp;
    }
    for (int i = 0; i < n; i++) {
        std::cout << numberOfChildren(nodes[i]) << " ";
        delete nodes[i];
    }
}
