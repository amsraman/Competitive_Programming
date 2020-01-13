#include <bits/stdc++.h>

using namespace std;

int n, a, b, d[100000], ans;

int main()
{
    freopen("planting.in","r",stdin);
    freopen("planting.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        d[a-1]++, d[b-1]++;
    }
    for(int i = 0; i<n; i++)
    {
        ans = max(ans,d[i]+1);
    }
    cout << ans << endl;
}
