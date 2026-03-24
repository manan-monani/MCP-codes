#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

    int counter = 0;
    for (int i=0 ; i<=100 ; i++){
        cout << i;
        i++ ;
        cout <<endl << i;
        i++ ;
        cout <<endl << i;
        i++ ;
        cout <<endl << i;
        counter ++ ;
        cout << "loop ran for " << counter-1 << " iterations\n";
    }
    
    return 0;
}