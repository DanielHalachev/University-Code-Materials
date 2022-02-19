https://www.hackerrank.com/contests/sda-2021-2021-test-1/challenges/challenge-3099

#include <algorithm>
#include <iostream>

class TeamPair {
public:
    TeamPair() {
        this->num1 = this->num2 = 0;
        this->score = 0;
    }

    TeamPair(double team1, double team2) {
        this->num1 = team1;
        this->num2 = team2;
        this->score = this->num1 * this->num1 / this->num2;
    }

    bool operator<(const TeamPair &other) const {
        if (this->score > other.score) {
            return false;
        }
        if (this->score < other.score) {
            return true;
        }
        return this->num1 < other.num1;
    }

private:
    double num1;
    double num2;
    double score;
};

int partition(std::pair<TeamPair, int> arr[], int start, int end) {
    std::pair<TeamPair, int> pivot = arr[end]; // pivot
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

void quickSort(std::pair<TeamPair, int> arr[], int start, int end) {
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
    auto *arr = new std::pair<TeamPair, int>[n];
    double input1, input2;
    for (int i = 0; i < n; i++) {
        std::cin >> input1 >> input2;

        arr[i] = std::pair<TeamPair, int>(TeamPair(input1, input2), i + 1);
    }
    quickSort(arr, 0, n - 1);
    // print them in downwards order
    for (int i = n - 1; i >= 0; i--) {
        std::cout << arr[i].second << " ";
    }
    delete[] arr;
}
