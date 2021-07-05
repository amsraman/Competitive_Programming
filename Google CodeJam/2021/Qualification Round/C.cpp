#include <bits/stdc++.h>

using namespace std;

int t, n, c, ans[100];

void bld(int x, int num)
{
    if(x==n)
        return;
    int pl = min(n,x+num-(n-x-2));
    bld(x+1,num-(pl-x));
    for(int i = x; i<pl-1; i++)
        ans[i] = ans[i+1];
    reverse(ans+x,ans+pl-1);
    ans[pl-1] = x+1;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> c;
        cout << "Case #" << _ << ": ";
        if(c<n-1||c>n*(n+1)/2-1)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            bld(0,c);
            for(int i = 0; i<n; i++)
                cout << ans[i] << " ";
            cout << endl;
        }
    }
}