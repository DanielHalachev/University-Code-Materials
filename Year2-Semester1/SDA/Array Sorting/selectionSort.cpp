#include <algorithm>

void selectionSort(int arr[], int size) {
    for (int j = 0; j < size - 1; j++) {
        int iMin = j;
        for (int i = j + 1; i < size; i++) {
            if (arr[i] < arr[iMin]) {
                iMin = i;
            }
        }

        if (iMin != j) {
            std::swap(arr[j], arr[iMin]);
        }
    }
}
