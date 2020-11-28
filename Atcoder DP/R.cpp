#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, ans;
ll k;

int add(int a, int b)
{
    return (a+b)%MOD;
}

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

struct mat
{
    int m[50][50];
    mat id()
    {
        mat res;
        memset(res.m,0,sizeof(res.m));
        for(int i = 0; i<n; i++)
            res.m[i][i] = 1;
        return res;
    }
    mat operator*(const mat& m2)
    {
        mat res;
        memset(res.m,0,sizeof(res.m));
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                for(int x = 0; x<n; x++)
                    res.m[i][j] = add(res.m[i][j],mul(m[i][x],m2.m[x][j]));
        return res;
    }
} adj;

mat exp(mat mt, ll e)
{
    mat res = res.id();
    while(e>0)
    {
        if(e&1)
            res = res*mt;
        mt = mt*mt, e>>=1;
    }
    return res;
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> adj.m[i][j];
    mat res = exp(adj,k);
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            ans = add(ans,res.m[i][j]);
    cout << ans << endl;
}
