https://www.hackerrank.com/contests/sda-hw-8-2021/challenges/call-center-1

#include <iostream>

int main() {
    int clients;
    int operators;
    int clientNum, length;
    std::cin >> clients >> operators;
    int *timetable = new int[operators];
    int *counter = new int[operators];
    for (int i = 0; i < operators; i++) {
        timetable[i] = 0;
        counter[i] = 0;
    }
    for (int i = 0; i < clients; i++) {
        std::cin >> clientNum >> length;
        int j = i;
        int start = i % operators;
        do {
            if (timetable[j % operators] <= clientNum) {
                timetable[j % operators] = clientNum + length;
                counter[j % operators]++;
                break;
            }
            j++;
        } while (j % operators != start);
    }
    int max = INT32_MIN;
    for (int i = 0; i < operators; i++) {
        if (counter[i] > max) {
            max = counter[i];
        }
    }
    for (int i = 0; i < operators; i++) {
        if (counter[i] == max) {
            std::cout << i << " ";
        }
    }
    delete[]timetable;
    delete[] counter;
}
