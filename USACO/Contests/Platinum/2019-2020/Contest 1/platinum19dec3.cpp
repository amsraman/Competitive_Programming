#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, m, poly[44851], ans[300];

void mul(int x)
{
    for(int i = 1; i<=n*(n-1)/2; i++)
        poly[i] = (poly[i]+poly[i-1])%m;
    for(int i = n*(n-1)/2; i>=x; i--)
        poly[i] = (m+poly[i]-poly[i-x])%m;
}

void div(int x)
{
    for(int i = n*(n-1)/2; i>=0; i--)
        poly[i] = (m+poly[i]-poly[i-1])%m;
    for(int i = x; i<=n*(n-1)/2; i++)
        poly[i] = (poly[i]+poly[i-x])%m;
}

int get(int x)
{
    if(x<0||x>n*(n-1)/2)
        return 0;
    return poly[x];
}

int main()
{
    freopen("treedepth.in","r",stdin);
    freopen("treedepth.out","w",stdout);
    cin >> n >> k >> m;
    poly[0] = 1;
    for(int i = 1; i<=n; i++)
        mul(i);
    for(int i = 0; i<n; i++)
        ans[i] = poly[k];
    for(int diff = 1; diff<n; diff++)
    {
        div(diff+1);
        for(int i = 0; i+diff<n; i++)
            ans[i] = (ans[i]+get(k-diff))%m;
        for(int i = n-1; i-diff>=0; i--)
            ans[i] = (ans[i]+get(n*(n-1)/2-k-diff))%m;
        mul(diff+1);
    }
    cout << ans[0]; // do not get why this is necessary :/
    for(int i = 1; i<n; i++)
        cout << " " << ans[i];
    cout << endl;
}
