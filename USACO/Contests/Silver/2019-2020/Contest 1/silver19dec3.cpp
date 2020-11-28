#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, a, b, comp[100000][2], co[2];
bool vis[100000][2], ans[100000];
vector<int> g[100000][2];
string type;
char cow;

void dfs(int u, int v)
{
    vis[u][v] = true;
    comp[u][v] = co[v];
    for(int i = 0; i<g[u][v].size(); i++)
        if(!vis[g[u][v][i]][v])
            dfs(g[u][v][i],v);
}

int main()
{
    freopen("milkvisits.in","r",stdin);
    freopen("milkvisits.out","w",stdout);
    cin >> n >> m >> type;
    for(int i = 0; i<n-1; i++)
    {
        cin >> x >> y;
        if((type[x-1]=='H')&&(type[y-1]=='H'))
        {
            g[x-1][0].push_back(y-1);
            g[y-1][0].push_back(x-1);
        }
        else if((type[x-1]=='G')&&(type[y-1]=='G'))
        {
            g[x-1][1].push_back(y-1);
            g[y-1][1].push_back(x-1);
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(!vis[i][0])
            dfs(i,0), co[0]++;
        if(!vis[i][1])
            dfs(i,1), co[1]++;
    }
    for(int i = 0; i<m; i++)
    {
        cin >> a >> b >> cow;
        int temp = (cow=='H');
        cout << ((comp[a-1][temp]!=comp[b-1][temp])||(type[a-1]==cow));
    }
    cout << endl;
}
