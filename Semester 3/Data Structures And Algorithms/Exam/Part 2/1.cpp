https://www.hackerrank.com/contests/exam-2022-part2-sda/challenges/linked-numbers

#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *next;
    int data;
};


class LinkedList {
public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        Node *temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(int value) {
        Node *temp = new Node;
        temp->data = value;
        temp->next = nullptr;

        if (head == nullptr and tail == nullptr) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    void print() {
        Node *curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
    }

    Node *head, *tail;
};


void solve(LinkedList &num1, LinkedList &num2) {
    Node *runner1 = num1.head;
    Node *runner2 = num2.head;
    std::stack<int> stack;
    int additional = 0;
    while (runner1 != nullptr && runner2 != nullptr) {
        int sum = runner1->data + runner2->data + additional;
        if (sum >= 10) {
            stack.emplace(sum - 10);
            additional = sum / 10;
        } else {
            stack.emplace(sum);
            additional = 0;
        }
        runner1 = runner1->next;
        runner2 = runner2->next;
    }
    while (runner1 != nullptr) {
        int sum = runner1->data + additional;
        if (sum >= 10) {
            stack.emplace(sum - 10);
            additional = sum / 10;
        } else {
            stack.emplace(sum);
            additional = 0;
        }
        runner1 = runner1->next;
    }
    while (runner2 != nullptr) {
        int sum = runner2->data + additional;
        if (sum >= 10) {
            stack.emplace(sum - 10);
            additional = sum / 10;
        } else {
            stack.emplace(sum);
            additional = 0;
        }
        runner2 = runner2->next;
    }
    if (additional != 0) {
        stack.emplace(additional);
    }
    while (!stack.empty()) {
        std::cout << stack.top();
        stack.pop();
    }
}

int main() {
    LinkedList num1, num2;

    int size1, size2;
    cin >> size1;
    for (int i = 0; i < size1; i++) {
        int digit;
        cin >> digit;
        num1.add(digit);
    }

    cin >> size2;
    for (int i = 0; i < size2; i++) {
        int digit;
        cin >> digit;
        num2.add(digit);
    }

    solve(num1, num2);
}
