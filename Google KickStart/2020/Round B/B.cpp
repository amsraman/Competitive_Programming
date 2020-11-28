#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n;
ll d, x[1000];

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n >> d;
        for(int i = 0; i<n; i++)
            cin >> x[i];
        for(int i = n-1; i>=0; i--)
            d-=(d%x[i]);
        cout << "Case #" << cs+1 << ": " << d << endl;
    }
}
