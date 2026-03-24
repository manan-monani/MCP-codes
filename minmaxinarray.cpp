#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int arr[] = {3, 5, 1, 1500, 2,-25,-13,-100,100,8,-1000};
    int size = 11;

int min = INT16_MAX;
int max = INT16_MIN;
int minindex = 0;
int maxindex = 0;

    for (int i=0;i<size;i++){
        if (arr[i] < min){
            min = arr[i];
            minindex = i;
        }
        if (arr[i] > max){
            max = arr[i];
            maxindex = i;
        }
    }

    cout << "Minimum element is: " << min << " at index " << minindex << endl;
    cout << "Maximum element is: " << max << " at index " << maxindex << endl;

    return 0;
}