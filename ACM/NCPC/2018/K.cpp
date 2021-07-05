#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007

using namespace std;

int n, k, p[2500], ncr[2501][2501], ans;
vector<int> g[2500];

int mul(int a, int b)
{
    return ((ll)a*b)%MOD;
}

int dfs(int x, int p, int num)
{
    int ret = 1;
    for(int i: g[x])
        if(i!=p)
            ret = mul(ret,mul(num-1,dfs(i,x,num)));
    return ret;
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n-1; i++)
    {
        cin >> p[i];
        g[i+1].push_back(p[i]);
        g[p[i]].push_back(i+1);
    }
    ncr[0][0] = 1;
    for(int i = 0; i<n; i++)
    {
        ncr[i+1][0] = 1;
        for(int j = 0; j<=i; j++)
            ncr[i+1][j+1] = (ncr[i][j]+ncr[i][j+1])%MOD;
    }
    for(int i = k; i>0; i--)
    {
        int tmp = mul(ncr[k][k-i],mul(i,dfs(0,0,i)));
        if(i%2==k%2)
            ans = (ans+tmp)%MOD;
        else
            ans = (ans+MOD-tmp)%MOD;
    }
    cout << ans << endl;
}