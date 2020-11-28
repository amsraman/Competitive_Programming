#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, tot, num, ans;
string grid[1000];
vector<pair<int,bool> > g[4000];
bool col[4000], vis[4000];

void dfs(int a)
{
    vis[a] = true, num++, tot+=col[a];
    for(int i = 0; i<g[a].size(); i++)
        if(!vis[g[a][i].f])
            col[g[a][i].f] = col[a]^g[a][i].s, dfs(g[a][i].f);
}

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> grid[i];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                g[2*n+i+j-1].push_back({n+i-j-1,(grid[i][j]=='.')});
                g[n+i-j-1].push_back({2*n+i+j-1,(grid[i][j]=='.')});
            }
        ans = 0;
        memset(vis,false,sizeof(vis));
        for(int i = 0; i<4*n-2; i++)
            if(!vis[i])
            {
                tot = num = 0;
                dfs(i);
                ans+=min(tot,num-tot);
            }
        cout << "Case #" << cs << ": " << min(ans,4*n-ans-2) << endl;
        for(int i = 0; i<4*n-2; i++)
            g[i].clear();
    }
}
