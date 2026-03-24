#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

    vector <int> myVector(5,0); // Create a vector of 5 elements, all initialized to 0
    for (int i = 0; i < myVector.size(); i++) {
        cout << myVector[i] << " ";
    }

    return 0;
}