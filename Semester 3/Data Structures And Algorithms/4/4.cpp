https://www.hackerrank.com/contests/sda-hw-4/challenges/exam-5-1

#include <bits/stdc++.h>

using namespace std;

class DoublyLinkedListNode {
public:
    int data;
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *previous;

    explicit DoublyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
        this->previous = nullptr;
    }
};

class DoublyLinkedList {
public:
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
    DoublyLinkedListNode *middle;
    int size;


    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->middle = nullptr;
        this->size = 0;
    }

    void insert_node(int node_data) {
        auto *node = new DoublyLinkedListNode(node_data);
        this->size++;
        if (!this->head) {
            this->head = node;
            this->middle = this->head;
        } else {
            if (this->size > 3 && this->size % 2 == 0) {
                this->middle = this->middle->next;
            }
            node->previous = this->tail;
            this->tail->next = node;
        }
        this->tail = node;
    }

    DoublyLinkedListNode *removeLastNode() {
        if (this->head == nullptr) {
            size = 0;
            return nullptr;
        }
        if (head->next == nullptr) {
            size--;
            delete head;
            this->tail = nullptr;
            this->head = nullptr;
            this->middle = nullptr;
            return nullptr;
        }
        this->tail = this->tail->previous;
        delete this->tail->next;
        this->tail->next = nullptr;
        if (size > 2 && size % 2 == 0) {
            middle = middle->previous;
        }
        size--;
        return this->head;
    }
};

void print(DoublyLinkedListNode *head) {
    DoublyLinkedListNode *temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
}

int main() {
    int n;
    std::string command;
    std::cin >> n;
    DoublyLinkedList list;
    for (int i = 0; i < n; i++) {
        std::cin >> command;
        if (command == "milen") {
            if (list.size > 1) {
                DoublyLinkedListNode *temp = list.tail;
                list.tail->next = list.head;
                list.head->previous = list.tail;
                list.head = list.middle->next;
                list.head->previous = nullptr;
                list.tail = list.middle;
                list.tail->next = nullptr;
                if (list.size % 2 == 0) {
                    list.middle = temp;
                } else {
                    list.middle = temp->previous;
                }
            }
        } else if (command == "gun") {
            list.removeLastNode();
        } else {
            int num = 0;
            std::cin >> num;
            list.insert_node(num);
        }
        // print(list.head);
//        std::cout << "\n"<<list.middle->data<<"\n";
    }
    printf("%i\n", list.size);
    DoublyLinkedListNode *temp = list.head;
    while (temp != nullptr) {
        printf("%i ", temp->data);
        temp = temp->next;
    }
    return 0;
}
