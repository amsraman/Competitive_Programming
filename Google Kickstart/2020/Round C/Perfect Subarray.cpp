#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a[100000], um[40000001], mx;
ll ans;

ll num(int x)
{
    um[20000000]++;
    int tot = 0;
    ll ret = 0;
    for(int i = 0; i<n; i++)
    {
        tot+=a[i];
        ret+=um[tot-x+20000000];
        um[tot+20000000]++;
    }
    tot = 0;
    for(int i = 0; i<n; i++)
        tot+=a[i], um[tot+20000000] = 0;
    um[20000000] = 0;
    return ret;
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        mx = 0, ans = 0;
        for(int i = 0; i<n; i++)
            mx = max(mx,a[i]);
        for(int i = 0; i*i<=mx*n; i++)
            ans+=num(i*i);
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
