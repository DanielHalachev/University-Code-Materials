https://www.hackerrank.com/contests/sda-hw-4/challenges/zuma-1

#include <bits/stdc++.h>

class Ball {
public:
    Ball(int position, int color) {
        this->position = position;
        this->color = color;
    }

    Ball() {
        this->position = -1;
        this->color = -1;
    }

    bool operator==(const Ball &other) const {
        return this->color == other.color;
    }

    int position;
    int color;
};

class DoublyLinkedListNode {
public:
    Ball data;
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *previous;

    explicit DoublyLinkedListNode(const Ball &node_data) {
        this->data = Ball(node_data.position, node_data.color);
        this->next = nullptr;
        this->previous = nullptr;
    }
};

class DoublyLinkedList {
public:
    DoublyLinkedListNode *head;
    DoublyLinkedListNode *tail;
    int size;

    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    void push_back(Ball node_data) {
        auto *node = new DoublyLinkedListNode(node_data);
        this->size++;
        if (!this->head) {
            this->head = node;
        } else {
            node->previous = this->tail;
            this->tail->next = node;
        }
        this->tail = node;
        this->tail->next = nullptr;
    }

    DoublyLinkedListNode *pop_back() {
        if (this->head == nullptr) {
            size = 0;
            return nullptr;
        }
        if (head->next == nullptr) {
            size--;
            delete head;
            this->tail = nullptr;
            this->head = nullptr;
            return nullptr;
        }
        this->tail = this->tail->previous;
        delete this->tail->next;
        this->tail->next = nullptr;
        this->size--;
        return this->head;
    }

    DoublyLinkedListNode *pop_front() {
        if (this->head == nullptr) {
            size = 0;
            return nullptr;
        }
        if (head->next == nullptr) {
            size--;
            delete head;
            this->tail = nullptr;
            this->head = nullptr;
            return nullptr;
        }
        this->head = this->head->next;
        delete this->head->previous;
        this->head->previous = nullptr;
        this->size--;
        return this->head;
    }

    DoublyLinkedListNode *insertInPosition(Ball data, int position, DoublyLinkedListNode **map) {
        auto temp = new DoublyLinkedListNode(data);
        DoublyLinkedListNode *runner = this->head;
        runner = map[position];
        if (runner == this->tail) {
            this->push_back(data);
            map[data.position] = this->tail;
            return this->tail;
        }
        if (runner == this->head) {
            if (size == 1) {
                temp->next = nullptr;
                head->next = temp;
                temp->previous = head;
                this->tail = temp;
                this->size++;
                map[data.position] = temp;
                return this->tail;
            } else {
                temp->next = head->next;
                head->next->previous = temp;
                temp->previous = head;
                head->next = temp;
                this->size++;
                map[data.position] = temp;
                return this->head->next;
            }
        }
        temp->next = runner->next;
        runner->next->previous = temp;
        temp->previous = runner;
        runner->next = temp;
        this->size++;
        map[data.position] = temp;
        return temp;
    }

    void deleteLeftFrom(DoublyLinkedListNode *node) {
        // already checking if previous is nullptr before calling,
        // so that we know we've reached the beginning of the list
        if (node->previous->previous != nullptr) {
            auto newEnd = node->previous->previous;
            delete node->previous;
            newEnd->next = node;
            node->previous = newEnd;
        } else {
            this->head = node;
            delete this->head->previous;
            this->head->previous = nullptr;
        }
        this->size--;
    }

    void deleteRightFrom(DoublyLinkedListNode *node) {
        // already checking if next is nullptr before calling,
        // so that we know we've reached the end of the list
        if (node->next->next != nullptr) {
            auto newBeginning = node->next->next;
            newBeginning->previous = node;
            delete node->next;
            node->next = newBeginning;
        } else {
            this->tail = node;
            delete this->tail->next;
            this->tail->next = nullptr;
        }
        this->size--;
    }

    int strike(DoublyLinkedListNode *temp) {
        int sequence = 1;
        Ball current = temp->data;
        auto temp2 = temp;
        while (temp2->previous != nullptr && temp2->previous->data == current) {
            temp2 = temp2->previous;
            sequence++;
            if (sequence > 2) {
                break;
            }
        }
        if (sequence < 3) {
            temp2 = temp;
            while (temp2->next != nullptr && temp2->next->data == current) {
                temp2 = temp2->next;
                sequence++;
                if (sequence > 2) {
                    break;
                }
            }
        }
        int ballsDestroyed = 0;
        if (sequence > 2) {
            while (temp->previous != nullptr && temp->previous->data == current) {
                this->deleteLeftFrom(temp);
                ballsDestroyed++;
            }
            while (temp->next != nullptr && temp->next->data == current) {
                this->deleteRightFrom(temp);
                ballsDestroyed++;
            }
            // if temp is not the tail
            if (temp != this->tail) {
                // if temp is not the head -> generic case, we are somewhere in the middle
                if (temp != this->head) {
                    this->size--;
                    temp->previous->next = temp->next;
                    temp->next->previous = temp->previous;
                    // memory leak here - can't think how to destroy the node in the middle that got cut
                    // set temp to the left bound
                    temp = temp->previous;
                    // if it is the same as the right, repeat recursively
                    if (temp->data == temp->next->data) {
                        ballsDestroyed += this->strike(temp);
                    }
                }
                    // temp is the head but not the tail
                else {
                    this->pop_front();
                }
            }
                // if temp is the tail
            else {
                // doesn't matter if it's the head or not, we have checks in the method
                this->pop_back();
            }
            // +1 because temp also got destroyed
            ballsDestroyed++;
        }
        return ballsDestroyed;
    }
};

void print(DoublyLinkedListNode *head) {
    DoublyLinkedListNode *temp = head;
    while (temp != nullptr) {
        printf("%i ", temp->data.color);
        temp = temp->next;
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::string command;
    std::cin >> n;
    DoublyLinkedList list;
    int ball;
    for (int i = 0; i < n; i++) {
        std::cin >> ball;
        list.push_back(Ball(i, ball));
    }
    int q;
    std::cin >> q;
    int position, color;
    // enter queries
    std::vector<std::pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        std::cin >> position >> color;
        queries[i] = std::pair<int, int>(position, color);
    }
    auto **map = new DoublyLinkedListNode *[n + q];
    DoublyLinkedListNode *temp = list.head;
    for (int i = 0; i < n; i++) {
        map[i] = temp;
        temp = temp->next;
    }
    // go through all queries and display results
    for (int i = 0; i < q; i++) {
        if (list.size == 0) {
            printf("Game Over\n");
        } else {
            DoublyLinkedListNode *iterator = list.insertInPosition(Ball(list.size, queries[i].second),
                                                                   queries[i].first, map);
            printf("%i\n", list.strike(iterator));
        }
    }
    // if player didn't destroy all balls
    if (list.size > 0) {
        print(list.head);
    }
        // if they did
    else {
        printf("-1");
    }
    return 0;
}
