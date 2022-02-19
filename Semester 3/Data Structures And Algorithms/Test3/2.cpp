https://www.hackerrank.com/contests/sda-2021-2021-test-3-november16/challenges/tree-specific-print

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
    Node *left;
    Node *right;
    int value;
    Node(int value){
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

class BST{

public:
    BST(){
        root = NULL;
    }
    void insert(int value){
        root = insert(root, value);
    }

	

    void printSpecific(int dividedBy) {
        print(this->root, dividedBy);
    }

private:
	// you can implemented helper functions if you want
    // forgot to make it private the first time
    void print(Node *from, int dividedBy) {
        Node *runner = from;
        if (from == nullptr) {
            return;
        }
        if (runner->value % dividedBy == 0 && (runner->left != nullptr || runner->right != nullptr)) {
            std::cout << runner->value << " ";
        }
        print(runner->left, dividedBy);
        print(runner->right, dividedBy);
    }

    Node* root;

    Node* insert(Node *curNode, int value){
        if(curNode == NULL){
            curNode =  new Node(value);
        }else if(curNode->value < value){
            curNode->right = insert(curNode->right, value);
        }else if(curNode->value > value){
            curNode->left = insert(curNode->left, value);
        }else {
        	//if we already have this value at the tree - do nothing
        }
        return curNode;
    }
};
int main() {
    int n;
  	cin >> n;
  	int value;
  	BST tree;
  	for(int i = 0 ; i < n; i++){
      cin >> value;
      tree.insert(value);
    }
  	int dividedBy;
  	cin >> dividedBy;
  	tree.printSpecific(dividedBy);
    return 0;
}
