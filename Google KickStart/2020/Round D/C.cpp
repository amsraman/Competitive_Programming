#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, a, b, par[500000][20];
ll n, ans1[500000], ans2[500000], ans;
vector<int> g[500000];

int pt(int x, int y)
{
    for(int i = 19; i>=0; i--)
        if((1<<i)&y)
            x = par[x][i];
    return x;
}

void dfs(int x, int y, int d)
{
    ans1[x]++, ans2[x]++;
    for(int i = 0; (1<<i)<n; i++)
        par[x][i+1] = par[par[x][i]][i];
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=y)
            dfs(g[x][i],x,d+1);
    if(d>=a)
        ans1[pt(x,a)]+=ans1[x];
    if(d>=b)
        ans2[pt(x,b)]+=ans2[x];
    ans+=(ans1[x]*n+ans2[x]*n-ans1[x]*ans2[x]);
}

int main()
{
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> a >> b;
        for(int i = 0; i<n-1; i++)
        {
            cin >> par[i+1][0];
            par[i+1][0]--;
            g[par[i+1][0]].push_back(i+1);
            g[i+1].push_back(par[i+1][0]);
        }
        dfs(0,0,0);
        cout << "Case #" << _+1 << ": " << fixed << setprecision(6) << double(ans)/double(n*n) << endl;
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<20; j++)
                par[i][j] = 0;
            ans1[i] = ans2[i] = 0;
        }
        ans = 0;
        for(int i = 0; i<n; i++)
            g[i].clear();
    }
}
