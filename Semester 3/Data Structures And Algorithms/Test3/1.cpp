https://www.hackerrank.com/contests/sda-2021-2021-test-3-november16/challenges/challenge-1692
#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *leftNode;
        Node *rightNode;
        Node(int d) {
            data = d;
            leftNode = NULL;
            rightNode = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->leftNode, data);
                    root->leftNode = cur;
                } else {
                    cur = insert(root->rightNode, data);
                    root->rightNode = cur;
               }

               return root;
           }
        }


	int intLeaves(Node *start) {
        int sum = 0;
        if (start->leftNode != nullptr) {
            sum += intLeaves(start->leftNode);
        }
        if (start->leftNode == nullptr && start->rightNode == nullptr && start->data % 2 == 1) {
            sum += start->data;
        }
        if (start->rightNode != nullptr) {
            sum += intLeaves(start->rightNode);
        }
        return sum;
    }

    void leaves(Node *root) {
        std::cout << intLeaves(root);
    }


}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
	myTree.leaves(root);
    return 0;
}
