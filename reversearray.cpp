#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

int main() {
    int arr[] = {16 , 17, 4, 3, 5, 2,100};
    int size = sizeof(arr) / sizeof(arr[0]);


    reverseArray(arr, size);

    
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}