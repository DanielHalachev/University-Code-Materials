https://www.hackerrank.com/contests/sda-hw-2/challenges/logging-monitoring-alerting/submissions/code/1337711820

#include <algorithm>
#include <iostream>

class Timestamp {
public:
    Timestamp() = default;

    Timestamp(const std::string &data) {
        this->hours = data.at(0) * 10 + data.at(1);
        this->minutes = data.at(3) * 10 + data.at(4);
        this->seconds = data.at(6) * 10 + data.at(7);
        this->date = data.at(9) * 10 + data.at(10);
        this->month = data.at(12) * 10 + data.at(13);
        this->year = data.at(15) * 1000 + data.at(16) * 100 + data.at(17) * 10 + data.at(18);
    }

    bool operator<(const Timestamp &other) const {
        if (this->year > other.year) {
            return false;
        }
        if (this->year < other.year) {
            return true;
        }
        if (this->month > other.month) {
            return false;
        }
        if (this->month < other.month) {
            return true;
        }
        if (this->date > other.date) {
            return false;
        }
        if (this->date < other.date) {
            return true;
        }
        if (this->hours > other.hours) {
            return false;
        }
        if (this->hours < other.hours) {
            return true;
        }
        if (this->minutes > other.minutes) {
            return false;
        }
        if (this->minutes < other.minutes) {
            return true;
        }
        return this->seconds < other.seconds;
    }

private:
    int hours;
    int minutes;
    int seconds;
    int date;
    int month;
    int year;
};

int partition(std::pair<Timestamp, int> arr[], int start, int end) {
    std::pair<Timestamp, int> pivot = arr[end]; // pivot
    int iMin = (start - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = start; j <= end - 1; j++) {
        // If current element < the pivot
        if (arr[j] < pivot) {
            iMin++; // increment index of smaller element
            std::swap(arr[iMin], arr[j]);
        }
    }
    std::swap(arr[iMin + 1], arr[end]);
    return (iMin + 1);
}

void quickSort(std::pair<Timestamp, int> arr[], int start, int end) {
    if (start < end) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, start, end);

        // Sort elements before on both sides of the partition
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}


int main() {
    int n = 0;
    std::cin >> n;
    std::pair<Timestamp, int> *arr = new std::pair<Timestamp, int>[n];
    std::string input1, input2;
    for (int i = 0; i < n; i++) {
        std::cin >> input1 >> input2;

        arr[i] = std::pair<Timestamp, int>(Timestamp(input1 + " " + input2), i + 1);
    }
    quickSort(arr, 0, n - 1);
//    std::sort(arr, arr + n);
    for (int i = 0; i < n - 1; i++) {
        std::cout << arr[i].second << std::endl;
    }
    std::cout << arr[n - 1].second;
    delete[] arr;
}
