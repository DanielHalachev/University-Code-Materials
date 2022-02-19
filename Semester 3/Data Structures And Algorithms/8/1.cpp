https://www.hackerrank.com/contests/sda-hw-8-2021/challenges/elitism

#include <iostream>
#include <queue>
#include <iomanip>

double median(const std::priority_queue<int, std::vector<int>, std::greater<>> &leftSide,
              const std::priority_queue<int, std::vector<int>, std::less<>> &rightSide) {
    if (leftSide.size() < rightSide.size()) {
        return rightSide.top();
    }
    if (leftSide.size() > rightSide.size()) {
        return leftSide.top();
    }
    return ((leftSide.top() + rightSide.top()) / 2.0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // contains the elements bigger than the median
    // smallest is at the top
    std::priority_queue<int, std::vector<int>, std::greater<>> minHeap;
    // contains the elements smaller than the median
    // biggest is at the top
    std::priority_queue<int, std::vector<int>, std::less<>> maxHeap;
    int n;
    std::cin >> n;
    int temp;
    auto *results = new double[n];
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        // add the element to the correct priority_queue
        // but also balance the queues by size
        if (!minHeap.empty() && temp < minHeap.top()) {
            maxHeap.emplace(temp);
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.emplace(maxHeap.top());
                maxHeap.pop();
            }
        } else {
            minHeap.emplace(temp);
            if (minHeap.size() > maxHeap.size() + 1) {
                maxHeap.emplace(minHeap.top());
                minHeap.pop();
            }
        }
        results[i] = median(minHeap, maxHeap);
    }
    // print the result
    for (int i = 0; i < n; i++) {
        printf("%.1f\n",  results[i]);
    }
    delete[] results;
}
