#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, k, q, a[50000], pref[50001][21][21], inv[50001][21][21];

int add(int a, int b)
{
    if(a+b>=MOD)
        return a+b-MOD;
    return a+b;
}

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

int main()
{
    freopen("nondec.in","r",stdin);
    freopen("nondec.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<=k; i++)
        for(int j = 0; j <=k; j++)
            pref[0][i][j] = inv[0][i][j] = int(i==j);
    for(int i = 0; i<n; i++)
    {
        for(int x = 0; x<=k; x++)
            for(int y = 0; y<=k; y++)
                pref[i+1][x][y] = pref[i][x][y];
        for(int x = 0; x<=k; x++)
            for(int y = 0; y<=a[i]; y++)
                pref[i+1][a[i]][x] = add(pref[i+1][a[i]][x],pref[i][y][x]);
        for(int x = 0; x<=k; x++)
            for(int y = 0; y<=a[i]; y++)
                inv[i+1][x][y] = add(inv[i][x][y],mul(5e8+3,inv[i][x][a[i]]));
        for(int x = 0; x<=k; x++)
            for(int y = a[i]+1; y<=k; y++)
                inv[i+1][x][y] = inv[i][x][y];
    }
    for(int i = 0; i<=n; i++)
        for(int x = 1; x<=k; x++)
            for(int y = 0; y<=k; y++)
                pref[i][x][y] = add(pref[i][x][y],pref[i][x-1][y]);
    cin >> q;
    for(int i = 0, l, r; i<q; i++)
    {
        cin >> l >> r;
        int ans = 0;
        for(int i = 0; i<=k; i++)
            ans = add(ans,mul(pref[r][k][i],inv[l-1][i][0]));
        cout << ans << endl;
    }
}
