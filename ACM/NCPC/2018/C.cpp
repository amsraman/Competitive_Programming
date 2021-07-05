#include <bits/stdc++.h>

using namespace std;

int n, days[400], ans;

int main()
{
    cin >> n;
    for(int i = 0, d; i<n; i++)
    {
        cin >> d;
        ++days[d-1];
    }
    int cur = 0, tot = 0;
    for(int i = 0; i<400; i++)
    {
        if(tot+cur>=20)
            ++ans, cur = tot = 0;
        else
            tot+=cur;
        cur+=days[i];
    }
    cout << ans << endl;
}