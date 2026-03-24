#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int linearSearch (int arr[], int size, int key) {
    for (int i=0; i<size; i++) {
        if (arr[i] == key) {
            return i; // Return the index of the found element
        }
    }
    return -1; // Return -1 if the element is not found
}

int main() {
    int arr[] = {5, 3, 8, 1, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 2;
    int result = linearSearch(arr, size, key);
    cout << result << endl; // Output the index of the found element or -1 if not found
    return 0;
}