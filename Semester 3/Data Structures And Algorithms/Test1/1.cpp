https://www.hackerrank.com/contests/sda-2021-2021-test-1/challenges/challenge-3098

#include <algorithm>
#include "iostream"

void merge(int arr[], int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;
    // create temp arrays
    int *leftArray = new int[leftSize];
    int *rightArray = new int[rightSize];
    // copy the data to the temp arrays
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = arr[middle + i + 1];
    }
    int leftIndex = 0, rightIndex = 0;
    int indexOfMergedArray = left;
    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            arr[indexOfMergedArray] = leftArray[leftIndex];
            leftIndex++;
        } else {
            arr[indexOfMergedArray] = rightArray[rightIndex];
            rightIndex++;
        }
        indexOfMergedArray++;
    }
    // copy the rest of the left array if something's missing
    while (leftIndex < leftSize) {
        arr[indexOfMergedArray] = leftArray[leftIndex];
        leftIndex++;
        indexOfMergedArray++;
    }
    // copy the rest of the right array if something's missing
    while (rightIndex < rightSize) {
        arr[indexOfMergedArray] = rightArray[rightIndex];
        rightIndex++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int arr[], int left, int right) {
    int middle = left + (right - left) / 2;
    if (left < right) {
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    mergeSort(arr, 0, n - 1);
    // get the first item
    int current = arr[0];
    // if it is repeated, the copies will be omitted later
    std::cout << arr[0] << " ";
    // compare it with every other item
    for (int i = 1; i < n; i++) {
        if (current != arr[i]) {
            // the current becomes the next
            std::cout << arr[i] << " ";
            current = arr[i];
        }
    }
    delete[] arr;
}
