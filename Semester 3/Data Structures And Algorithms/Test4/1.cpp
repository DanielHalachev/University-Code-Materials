https://www.hackerrank.com/contests/sda-2021-2022-test4-nov30/challenges/challenge-3148

#include <list>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

class Task {
public:
    int startTime;
    int duration;

    Task(int startTime, int duration) {
        this->startTime = startTime;
        this->duration = duration;
    }
};

struct TaskDurationComparator {
    bool operator()(const Task &task1, const Task &task2) const {
        return task1.duration > task2.duration;
    }
};

int main() {
    std::list<Task> tasks;
    std::priority_queue<Task, std::vector<Task>, TaskDurationComparator> queue;
    int n;
    std::cin >> n;
    int temp;
    int minWaitingTime = INT32_MAX, maxWaitingTime = -1;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        tasks.emplace_back(i, temp);
    }
    int positionInTime = tasks.front().startTime;
    while (!tasks.empty()) {
        if (tasks.front().startTime > positionInTime) {
            positionInTime = tasks.front().startTime;
        }
        while (!tasks.empty() && tasks.front().startTime <= positionInTime) {
            queue.push(tasks.front());
            tasks.pop_front();
        }
        int tempWaitingTime = positionInTime - queue.top().startTime + queue.top().duration;
        minWaitingTime = std::min(minWaitingTime, tempWaitingTime);
        maxWaitingTime = std::max(maxWaitingTime, tempWaitingTime);
        positionInTime += queue.top().duration;
        queue.pop();
    }
    while (!queue.empty()) {
        int tempWaitingTime = positionInTime - queue.top().startTime + queue.top().duration;
        minWaitingTime = std::min(minWaitingTime, tempWaitingTime);
        maxWaitingTime = std::max(maxWaitingTime, tempWaitingTime);
        positionInTime += queue.top().duration;
        queue.pop();
    }
    std::cout << minWaitingTime << " " << maxWaitingTime;
}
