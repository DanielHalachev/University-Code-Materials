https://www.hackerrank.com/contests/sda-hw-8-2021/challenges/challenge-2727

#include <iostream>
#include <queue>
#include <set>

class Task {
private:
    int time;
    int start;
public:
    Task(int start, int time) {
        this->time = time;
        this->start = start;
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
        return a.getStart() <= b.getStart();
    }
};

struct timeComparator {
    constexpr bool operator()(Task const &a, Task const &b) const noexcept {
        return a.getTime() > b.getTime();
    }
};

int main() {
    std::set<Task, ::startComparator> tasks;
    std::priority_queue<Task, std::vector<Task>, timeComparator> buffer;
    long n;
    long long sum = 0;
    std::cin >> n;
    int temp1, temp2;
    for (int i = 0; i < n; i++) {
        std::cin >> temp1 >> temp2;
        tasks.emplace(temp1, temp2);
    }
    long long pointInTime = tasks.begin()->getStart();
    while (!tasks.empty()) {
        if (buffer.empty() && pointInTime < tasks.begin()->getStart()) {
            pointInTime = tasks.begin()->getStart();
        }
        while (!tasks.empty() && tasks.begin()->getStart() <= pointInTime) {
            buffer.emplace(*tasks.begin());
            tasks.erase(tasks.begin());
        }
        sum += (pointInTime - buffer.top().getStart() + buffer.top().getTime());
        pointInTime += buffer.top().getTime();
        buffer.pop();
    }
    while (!buffer.empty()) {
        sum += (pointInTime - buffer.top().getStart() + buffer.top().getTime());
        pointInTime += buffer.top().getTime();
        buffer.pop();
    }
    std::cout << sum / n;
}
