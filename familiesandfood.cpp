#include <iostream>
#include <algorithm>
using namespace std;

int maxSatisfiedFamilies(int p[], int n, int f[], int m)
{
    sort(p, p + n);
    sort(f, f + m);

    int i = 0, j = 0;
    int satisfied = 0;

    while(i < n && j < m)
    {
        if(p[i] >= f[j])
        {
            satisfied++;
            i++;
            j++;
        }
        else
        {
            i++;
        }
    }

    return satisfied;
}

int main()
{
    vector<int> foodpackages = {4, 2, 8, 6};
    vector<int> familyrequirements = {3, 5, 7};

    int n = foodpackages.size();
    int m = familyrequirements.size();

    cout << maxSatisfiedFamilies(foodpackages.data(), n, familyrequirements.data(), m);

    return 0;
}