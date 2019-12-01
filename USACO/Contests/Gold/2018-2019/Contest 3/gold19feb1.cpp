#include <bits/stdc++.h>

using namespace std;

int n, q, e[100000], a, b, type, t, depth[100000], par[100000][17], bit[100002];
pair<int,int> in[100000];
vector<int> g[100000];

int sum(int k)
{
    int ret = 0;
    while(k>0)
    {
        ret^=bit[k];
        k-=(k&(-k));
    }
    return ret;
}

void update(int k, int v)
{
    while(k<=n+1)
    {
        bit[k]^=v;
        k+=(k&(-k));
    }
}

void dfs(int x)
{
    in[x].first = ++t, update(t,e[x]);
    for(int i = 1; i<17; i++) par[x][i] = par[par[x][i-1]][i-1];
    for(int i = 0; i<g[x].size(); i++)
    {
        if(g[x][i]!=par[x][0])
        {
            par[g[x][i]][0] = x;
            depth[g[x][i]] = depth[x]+1;
            dfs(g[x][i]);
        }
    }
    in[x].second = t, update(t+1,e[x]);
}

int lca(int x, int y)
{
    int i = 16, j = 16;
    if(depth[y]>depth[x]) swap(x,y);
    while(depth[x]>depth[y])
    {
        if(depth[x]-depth[y]>=(1<<i)) x = par[x][i];
        i--;
    }
    while(x!=y)
    {
        if(j==-1) break;
        if(par[x][j]!=par[y][j]) x = par[x][j], y = par[y][j];
        j--;
    }
    if(x==y) return x;
    return par[x][0];
}

int main()
{
    freopen("cowland.in","r",stdin);
    freopen("cowland.out","w",stdout);
    cin >> n >> q;
    for(int i = 0; i<n; i++) cin >> e[i];
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    dfs(0);
    for(int i = 0; i<q; i++)
    {
        cin >> type >> a >> b;
        if(type==2)
        {
            cout << (sum(in[a-1].first)^sum(in[b-1].first)^e[lca(a-1,b-1)]) << endl;
        }
        else
        {
            update(in[a-1].first,b^e[a-1]);
            update(in[a-1].second+1,b^e[a-1]);
            e[a-1] = b;
        }
    }
}
