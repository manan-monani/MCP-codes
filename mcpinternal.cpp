// 23DCS063 - Manan Monani
// MCP CIE -1 : Problem Set - 1 (05/02/2026)

#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cout << "no. of hours: ";
    cin >> n;
    vector<int> energy(n);

    for (int i = 0; i < n; i++)
    {
        cout << "energy of hour " << i + 1 << ": ";
        cin >> energy[i];
    }

    vector<int> sumofenergy(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        sumofenergy[i] = sumofenergy[i - 1] + energy[i - 1];
    }

    int l, r;
    cout << "l r of the query: ";
    cin >> l >> r;
    long long sum = sumofenergy[r] - sumofenergy[l - 1];
    cout << sum << endl;

    return 0;
}