https://www.hackerrank.com/contests/sda-hw-5/challenges/challenge-3105

#include <iostream>

template<class T>
class DoublyLinkedListNode {
public:
    T data;
    DoublyLinkedListNode<T> *previous;
    DoublyLinkedListNode<T> *next;

    explicit DoublyLinkedListNode(T data) {
        this->data = data;
        this->previous = nullptr;
        this->next = nullptr;
    }
};

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedListNode<T> *head;
    DoublyLinkedListNode<T> *tail;
    int size = 0;

    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    ~DoublyLinkedList() {
        if (this->head != nullptr) {
            DoublyLinkedListNode<T> *previous = nullptr;
            DoublyLinkedListNode<T> *current = this->head;
            while (current->next != nullptr) {
                previous = current;
                current = current->next;
                delete previous;
            }
            delete current;
        }
    }

    void push_back(T data) {
        auto *temp = new DoublyLinkedListNode<T>(data);
        this->size++;
        if (this->head == nullptr) {
            this->head = temp;
            this->tail = temp;
        } else {
            this->tail->next = temp;
            temp->previous = this->tail;
            this->tail = temp;
        }
    }

    void push_front(T data) {
        auto *temp = new DoublyLinkedListNode<T>(data);
        this->size++;
        if (this->head == nullptr) {
            this->head = this->tail = temp;
        } else {
            temp->previous = nullptr;
            temp->next = this->head;
            this->head->previous = temp;
            this->head = temp;
        }
    }

    DoublyLinkedListNode<T> *insert(DoublyLinkedListNode<T> *after, T data) {
        if (after == nullptr) {
            throw std::out_of_range("Cannot insert after nullpointer");
        }
        if (this->head == nullptr) {
            throw std::out_of_range("Cannot insert in empty list.Use push_front/ push_back instead");
        }
        this->size++;
        auto *temp = new DoublyLinkedListNode<T>(data);
        temp->previous = after;
        temp->next = after->next;
        after->next->previous = temp;
        after->next = temp;
        if (temp->next == nullptr) {
            this->tail = temp;
        }
        return temp;
    }

    DoublyLinkedListNode<T> *insert(int after, T data) {
        if (after >= this->size) {
            throw std::out_of_range("Cannot insert after end of list");
        }
        this->size++;
        auto *temp = new DoublyLinkedListNode<T>(data);
        if (this->head == nullptr) {
            this->head = this->tail = temp;
            return this->head;
        }
        DoublyLinkedListNode<T> *runner = this->head;
        int i = 0;
        while (runner->next != nullptr && i < after) {
            runner = runner->next;
        }
        temp->next = runner->next;
        if (runner->next != nullptr) {
            runner->next->previous = temp;
        }
        temp->previous = runner;
        runner->next = temp;
        if (temp->next == nullptr) {
            this->tail = temp;
        }
        return temp;
    }

    void pop_back() {
        if (this->head == nullptr) {
            throw std::out_of_range("Cannot delete from empty list");
        }
        this->size--;
        if (this->tail->previous == nullptr) {
            delete this->tail;
            this->tail = this->head = nullptr;
            return;
        }
        this->tail = this->tail->previous;
        delete this->tail->next;
        this->tail->next = nullptr;
    }

    void pop_front() {
        if (this->head == nullptr) {
            throw std::out_of_range("Cannot delete from empty list");
        }
        this->size--;
        if (this->head->next == nullptr) {
            delete this->head;
            this->head = this->tail = nullptr;
            return;
        }
        this->head = this->head->next;
        delete this->head->previous;
        this->head->previous = nullptr;
    }

    DoublyLinkedListNode<T> *erase(DoublyLinkedListNode<T> *toRemove) {
        if (toRemove == this->tail) {
            this->pop_back();
            return nullptr;
        }
        if (toRemove == this->head) {
            this->pop_front();
            return this->head;
        }
        this->size--;
        toRemove->previous->next = toRemove->next;
        toRemove->next->previous = toRemove->previous;
        DoublyLinkedListNode<T> *toReturn = toRemove->next;
        delete toRemove;
        return toReturn;
    }

    void print() {
        if (this->head == nullptr) {
            std::cout << "List is empty";
            return;
        }
        DoublyLinkedListNode<T> *runner = this->head;
        while (runner->next != nullptr) {
            std::cout << runner->data << " ";
            runner = runner->next;
        }
        std::cout << runner->data;
    }

    bool empty() {
        return this->size == 0;
    }
};

int main() {
    int n;
    std::cin >> n;

    DoublyLinkedList<int> players;
    DoublyLinkedList<DoublyLinkedListNode<int> *> mapOfIncreasingSubsequences;
    int temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        players.push_back(temp);
        if (i <= 0) {
            continue;
        }
        if (players.tail->previous->data < temp) {
            mapOfIncreasingSubsequences.push_back(players.tail);
        }
    }
    DoublyLinkedListNode<DoublyLinkedListNode<int> *> *runner;
    int counter = 0;
    bool battleHasBeenFought;
    while (mapOfIncreasingSubsequences.size > 0) {
        counter++;
        battleHasBeenFought = false;
        runner = mapOfIncreasingSubsequences.tail;
        do {
            if (runner->data->data > runner->data->previous->data) {
                battleHasBeenFought = true;
                runner->data = runner->data->next;
                if (runner->data == nullptr) {
                    players.pop_back();
                } else {
                    players.erase(runner->data->previous);
                }
                if (runner->next != mapOfIncreasingSubsequences.tail->next) {
                    if (runner->data == runner->next->data) {
                        mapOfIncreasingSubsequences.erase(runner->next);
                        if (runner->data->data <= runner->data->previous->data) {
                            runner = mapOfIncreasingSubsequences.erase(runner);
                        }
                    }
                } else if (runner->data == players.tail->next) {
                    runner = mapOfIncreasingSubsequences.erase(runner);
                }
            } else {
                runner = mapOfIncreasingSubsequences.erase(runner);
            }
            if (runner == mapOfIncreasingSubsequences.head) {
                break;
            }
            if (runner == nullptr) {
                runner = mapOfIncreasingSubsequences.tail;
            } else {
                runner = runner->previous;
            }
        } while (true);

        if (!battleHasBeenFought) {
            counter--;
        }
    }
    std::cout << counter << std::endl;
    return 0;
}
