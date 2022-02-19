https://www.hackerrank.com/contests/sda-hw-2/challenges/challenge-3088

#include <algorithm>
#include <iostream>

int partition(int arr[], int start, int end) {
    int pivot = arr[end]; // pivot
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

void quickSort(int arr[], int start, int end) {
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
    int *arr = new int[n];
    char c;
    int k;
    for (int i = 0; i < n; i++) {
        std::cin >> c;
        k = (int) c;
        if (c > 47 && c < 58) {
            k = k - 47;
        } else if (c > 64 && c < 91) {
            k = k - 28;
        } else if (c > 96) {
            k = k - 86;
        }
        arr[i] = k;
    }
    
//    quickSort(arr, 0, n - 1);
    std::sort(arr, arr + n);
    for (int i = 0; i < n; i++) {
        k = arr[i];
        if (k > 0 && k < 11) {
            k = k + 47;
        } else if (k > 10 && k < 37) {
            k = k + 86;
        } else if (k > 36) {
            k = k + 28;
        }
        c = k;
        std::cout << c;
    }
    delete[] arr;
}
