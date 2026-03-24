#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int satisfiedFamilies(vector<int> &p, vector<int> &m)
{
    sort(p.begin(), p.end());
    sort(m.begin(), m.end());

    int i = 0, j = 0;
    int satisfied = 0;

    while (i < p.size() && j < m.size())
    {
        if (p[i] >= m[j])
        {
            i++, j++, satisfied++;
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
    vector<int> p = {1, 1, 2, 8, 1, 7, 8, 6, 4, 5, 3, 6, 2, 4, 5, 7, 8, 9, 1, 2};
    vector<int> m = {3, 5, 7, 8, 9, 10, 11, 12, 20, 16, 4, 5, 6, 7, 8, 9, 10};

    cout << satisfiedFamilies(p, m);

    return 0;
}