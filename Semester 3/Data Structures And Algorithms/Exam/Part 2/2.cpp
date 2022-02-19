https://www.hackerrank.com/contests/exam-2022-part2-sda/challenges/puncakes

#include <vector>
#include "iostream"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int numberOfChefs;
    int numberOfRequiredPancakes;
    std::cin >> numberOfRequiredPancakes >> numberOfChefs;
    std::vector<int> times(numberOfChefs);
    for (int i = 0; i < numberOfChefs; i++) {
        std::cin >> times[i];
    }
    int minutes = 1;
    int numberOfReadyPancakes = 0;
    while (numberOfReadyPancakes < numberOfRequiredPancakes) {
        for (int time: times) {
            if (minutes % time == 0) {
                numberOfReadyPancakes++;
            }
        }
        minutes++;
    }
    printf("%i", minutes - 1);

}
