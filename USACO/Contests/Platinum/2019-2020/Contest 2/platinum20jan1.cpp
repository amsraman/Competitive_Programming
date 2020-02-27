#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, m, link[1000000];
ll dp[1000000], ans = 1;
char in[1000][1000];

ll modx(ll a)
{
    return (a%MOD+MOD)%MOD;
}

int f(int a)//Better way to impl find
{
    return ((a == link[a])?(a):(link[a] = f(link[a])));
}

void unite(int a, int b)//Non-better way to impl union
{
    if(f(a)==f(b))
        return;
    a = f(a), b = f(b);
    if((a/m==b/m)&&(b<a)) swap(a,b);
    link[b] = a;
    dp[a] = modx(dp[a]*dp[b]);
}

int main()
{
    freopen("cave.in","r",stdin);
    freopen("cave.out","w",stdout);
    cin >> n >> m;
    for(int i = n-1; i>=0; i--)
        for(int j = 0; j<m; j++)
            cin >> in[i][j];
    for(int i = 0; i<n*m; i++)
        link[i] = i, dp[i] = 1;
    for(int i = 1; i<n-1; i++)
    {
        for(int j = 1; j<m-1; j++)
        {
            if((in[i][j]=='.')&&(in[i][j+1]=='.'))
                unite(m*i+j,m*i+j+1);
            if((in[i][j]=='.')&&(in[i-1][j])=='.')
                unite(m*i+j,m*(i-1)+j);
        }
        for(int j = 1; j<m-1; j++)
            if(m*i+j==f(m*i+j))
                dp[m*i+j] = modx(dp[m*i+j]+1);
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if((in[i][j]=='.')&&(f(m*i+j)==m*i+j))
                ans = modx(ans*dp[m*i+j]);
    cout << ans << endl;
}
