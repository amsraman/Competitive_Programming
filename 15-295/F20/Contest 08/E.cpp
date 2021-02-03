#include <bits/stdc++.h>
#define f first
#define s second
#define INF 0x3f3f3f3f

using namespace std;

int n, m, a, b, edge[2502][2502], level[2502], ptr[2502];
pair<int,int> dir[4] = {{-1,0},{0,-1},{1,0},{0,1}};
string grid[50];
vector<int> g[2502];

int dfs(int a, int c, int t)
{
    if(a==t) return c;
    while(ptr[a]<g[a].size())
    {
        while((ptr[a]<g[a].size())&&((level[g[a][ptr[a]]]!=level[a]+1)||(edge[a][g[a][ptr[a]]]==0))) ptr[a]++;
        if(ptr[a]==g[a].size()) continue;
        int k = dfs(g[a][ptr[a]],min(c,edge[a][g[a][ptr[a]]]),t);
        if(k!=0)
        {
            edge[a][g[a][ptr[a]]]-=k;
            edge[g[a][ptr[a]]][a]+=k;
            return k;
        }
        else ptr[a]++;
    }
    return 0;
}

int dinic_flow(int a, int b, int flow)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<m*n+2; i++) level[i] = ptr[i] = 0;
        queue<int> q;
        q.push(a), level[a] = 1;
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
                if((level[g[z][i]]==0)&&(edge[z][g[z][i]]!=0))
                    level[g[z][i]] = level[z]+1, q.push(g[z][i]);
        }
        lg = (level[b]!=0);
        if(!lg) continue;
        while(int p = dfs(a,INF,b)) flow+=p;
    }
    return flow;
}

int main()
{
    cin >> n >> m >> a >> b;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    for(int i = 0; i<n*m; i++)
        g[0].push_back(i+1), g[i+1].push_back(0), g[i+1].push_back(n*m+1), g[n*m+1].push_back(i+1);
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            for(pair<int,int> x: dir)
                if(i+x.f>=0&&i+x.f<n&&j+x.s>=0&&j+x.s<m)
                    g[m*i+j+1].push_back(m*(i+x.f)+j+x.s+1), g[m*(i+x.f)+j+x.s+1].push_back(m*i+j+1), edge[m*i+j+1][m*(i+x.f)+j+x.s+1] = edge[m*(i+x.f)+j+x.s+1][m*i+j+1] = a;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
        {
            if(grid[i][j]=='.')
                edge[0][m*i+j+1] = b;
            else
                edge[m*i+j+1][n*m+1] = b;
        }
    cout << dinic_flow(0,n*m+1,0) << endl;
}