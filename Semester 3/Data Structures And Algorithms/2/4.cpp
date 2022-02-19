https://www.hackerrank.com/contests/sda-hw-2/challenges/challenge-3089/problem

#include <algorithm>
#include <iostream>

class WeightPair {
public:
    WeightPair() {
        this->diameter = this->time = 0;
        this->effectiveness = 0;
    }

    WeightPair(double diameter, double time) {
        this->diameter = diameter;
        this->time = time;
        this->effectiveness = this->diameter * this->diameter / this->time;
    }

    bool operator<(const WeightPair &other) const {
        if (this->effectiveness > other.effectiveness) {
            return false;
        }
        if (this->effectiveness < other.effectiveness) {
            return true;
        }
        return this->diameter < other.diameter;
    }

private:
    double diameter;
    double time;
    double effectiveness;
};

int partition(std::pair<WeightPair, int> arr[], int start, int end) {
    std::pair<WeightPair, int> pivot = arr[end]; // pivot
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

void quickSort(std::pair<WeightPair, int> arr[], int start, int end) {
    if (start < end) {
        // pi - partitioning index,
        // we assume that arr[p] is now at the right spot
        int pi = partition(arr, start, end);

        // Sort elements on both sides of the partition
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}


int main() {
    int n = 0;
    std::cin >> n;
    auto *arr = new std::pair<WeightPair, int>[n];
    double input1, input2;
    for (int i = 0; i < n; i++) {
        std::cin >> input1 >> input2;

        arr[i] = std::pair<WeightPair, int>(WeightPair(input1, input2), i + 1);
    }
    quickSort(arr, 0, n - 1);
    // print them in downwards order
    for (int i = n - 1; i >= 0; i--) {
        std::cout << arr[i].second << " ";
    }
    delete[] arr;
}
