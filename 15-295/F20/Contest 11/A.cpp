#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int h, w, m, pos[10000], depth[1000000], par[1000000][20];
ll ans;
string in;
vector<int> g[1000000];

int conv(int a, int b)
{
    return w*a+b;
}

void addEdge(int a, int b)
{
    g[a].push_back(b);
    g[b].push_back(a);
}

int dfs(int x, int p)
{
    for(int i = 1; i<20; i++)
        par[x][i] = par[par[x][i-1]][i-1];
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            depth[g[x][i]] = depth[x]+1, par[g[x][i]][0] = x, dfs(g[x][i],x);
}

int lca(int x, int y)
{
    if(depth[x]<depth[y])
        swap(x,y);
    for(int i = 0; i<20; i++)
        if((1<<i)&(depth[x]-depth[y]))
            x = par[x][i];
    for(int i = 19; i>=0; i--)
        if(par[x][i]!=par[y][i])
            x = par[x][i], y = par[y][i];
    return (x==y?x:par[x][0]);
}

int main()
{
    cin >> h >> w;
    cin.ignore();
    for(int i = 0; i<h+1; i++)
    {
        getline(cin,in);
        for(int j = 0; j<2*w+1; j++)
        {
            if(i>0 && j&1^1 && in[j]==' ')
                addEdge(conv(i-1,j/2-1),conv(i-1,j/2));
            if(j&1 && in[j]==' ')
                addEdge(conv(i-1,j/2),conv(i,j/2));
        }
    }
    dfs(0,0);
    cin >> m;
    for(int i = 0, x, y; i<m; i++)
    {
        cin >> x >> y;
        pos[i] = conv(x-1,y-1);
    }
    for(int i = 0; i<m-1; i++)
        ans+=(depth[pos[i]]+depth[pos[i+1]]-2*depth[lca(pos[i],pos[i+1])]);
    cout << ans << endl;
}