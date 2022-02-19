https://www.hackerrank.com/contests/sda-hw-7/challenges/zoros-mask

#include <iostream>

class TrieNode {
public:
    int data;
    TrieNode *left;
    TrieNode *right;

    explicit TrieNode(int data) {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

class Trie {
public:
    TrieNode *root;
    // this will count how many alternatives to 1 we have
    // in the binary representation of the numbers
    int counter = 1;

    Trie() {
        this->root = new TrieNode(0);
    }

    void freeNode(TrieNode *toFree) {
        if (!toFree) {
            return;
        }
        freeNode(toFree->left);
        freeNode(toFree->right);
        delete toFree;
    }

    ~Trie() {
        freeNode(this->root);
    }

    void insertAt(int value, TrieNode *node) {
        if (!value) {
            return;
        }
        // if the digit is 0
        // then make the child
        if (value % 2 == 0) {
            if (node->left == nullptr) {
                node->left = new TrieNode(0);
            }
            insertAt(value / 2, node->left);
        }
            // if the digit is one, this means that
            // there will be an extra mask for Zoro
            // we make this mask by inserting not only
            // the 1-child but also its 0 alternative
        else if (value % 2 == 1) {
            if (node->left == nullptr) {
                node->left = new TrieNode(0);
            }
            insertAt(value / 2, node->left);

            if (node->right == nullptr) {
                node->right = new TrieNode(1);
                this->counter++;
            }
            insertAt(value / 2, node->right);
        }
    }
};

int main() {
    Trie trie;
    int n;
    std::cin >> n;
    int temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        trie.insertAt(temp, trie.root);
    }
    std::cout << trie.counter;
    return 0;
}
