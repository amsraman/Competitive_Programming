#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[100000], bit[100000];
ll ans[100001];

ll qry(int x)
{
    ll ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret+=bit[x-1];
    return ret;
}

void upd(int x)
{
    for(x++; x<=n; x+=(x&(-x)))
        bit[x-1]++;
}

int main()
{
    freopen("haircut.in","r",stdin);
    freopen("haircut.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<n; i++)
        a[i] = min(a[i],n-1);
    for(int i = 0; i<n; i++)
    {
        ans[a[i]+1]+=(i-qry(a[i]));
        upd(a[i]);
    }
    for(int i = 1; i<n; i++)
        ans[i]+=ans[i-1];
    for(int i = 0; i<n; i++)
        cout << ans[i] << endl;
}
