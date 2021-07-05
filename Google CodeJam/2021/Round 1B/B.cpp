#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a, b, u[20];

bool ok(int x)
{
    ll num[5001];
    for(int i = 0; i<x; i++)
        num[i] = 0;
    num[x] = 1;
    for(int i = max(n-1,x); i>=0; i--)
    {
        if(i<n&&num[i]<u[i])
            return false;
        if(i<n)
            num[i]-=u[i];
        if(i>a-1)
            num[i-a] = min(1000000LL,num[i-a]+num[i]);
        if(i>b-1)
            num[i-b] = min(1000000LL,num[i-b]+num[i]);
    }
    return true;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> a >> b;
        for(int i = 0; i<n; i++)
            cin >> u[i];
        int ans = -1;
        for(int i = 5001; i>=0; i--)
            if(ok(i))
                ans = i;
        cout << "Case #" << _ << ": ";
        if(ans==-1)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << ans+1 << endl;
    }
}