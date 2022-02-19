https://www.hackerrank.com/contests/sda-hw-8-2021/challenges/fullstack-developer

#include <iostream>
#include <queue>
#include <list>

class Task {
private:
    int index;
    int time;
    int start;
public:
    Task(int index, int start, int time) {
        this->index = index;
        this->time = time;
        this->start = start;
    }

    constexpr int getIndex() const {
        return this->index;
    }

    constexpr int getTime() const {
        return this->time;
    }

    constexpr int getStart() const {
        return this->start;
    }
};

struct startComparator {
    constexpr bool operator()(Task const &a, Task const &b) const noexcept {
        return a.getStart() < b.getStart();
    }
};

struct timeComparator {
    constexpr bool operator()(Task const &a, Task const &b) const noexcept {
        if (a.getTime() == b.getTime()) {
            return a.getIndex() > b.getIndex();
        }
        return a.getTime() > b.getTime();
    }
};

int main() {
    std::list<Task> tasks;
    std::priority_queue<Task, std::vector<Task>, timeComparator> buffer;
    int n;
    std::cin >> n;
    int temp1, temp2;
    for (int i = 0; i < n; i++) {
        std::cin >> temp1 >> temp2;
        tasks.emplace_back(i, temp1, temp2);
    }
    tasks.sort(::startComparator());
    int pointInTime = tasks.front().getStart();
    while (!tasks.empty()) {
        if (buffer.empty() && pointInTime < tasks.front().getStart()) {
            pointInTime = tasks.front().getStart();
        }
        while (!tasks.empty() && tasks.front().getStart() <= pointInTime) {
            buffer.emplace(tasks.front());
            tasks.pop_front();
        }
        pointInTime += buffer.top().getTime();
        std::cout << buffer.top().getIndex() << " "; //printf
        buffer.pop();
    }
    while (!buffer.empty()) {
        std::cout << buffer.top().getIndex() << " ";
        buffer.pop();
    }
}
