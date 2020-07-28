#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, par[50000][20], depth[50000], id[50000], ans[50000];
vector<pair<int,int> > g[50000];
vector<int> in[50000], out[50000];
multiset<int> ms[50000];

void dfs1(int x, int p)
{
    for(int i = 1; i<20; i++)
        par[x][i] = par[par[x][i-1]][i-1];
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i].f!=p)
            par[g[x][i].f][0] = x, depth[g[x][i].f] = depth[x]+1, dfs1(g[x][i].f,x);
}

void dfs2(int x, int p, int ind)
{
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i].f!=p)
        {
            dfs2(g[x][i].f,x,g[x][i].s);
            if(ms[id[x]].size()<ms[id[g[x][i].f]].size())
                swap(id[x],id[g[x][i].f]);
            while(!ms[id[g[x][i].f]].empty())
            {
                ms[id[x]].insert(*ms[id[g[x][i].f]].begin());
                ms[id[g[x][i].f]].erase(ms[id[g[x][i].f]].begin());
            }
        }
    for(int i = 0; i<in[x].size(); i++)
        ms[id[x]].insert(in[x][i]);
    for(int i = 0; i<out[x].size(); i++)
        ms[id[x]].erase(ms[id[x]].find(out[x][i]));
    ans[ind] = ((ms[id[x]].empty())?-1:*ms[id[x]].begin());
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
    freopen("disrupt.in","r",stdin);
    freopen("disrupt.out","w",stdout);
    cin >> n >> m;
    for(int i = 0, p, q; i<n-1; i++)
    {
        cin >> p >> q;
        g[p-1].push_back({q-1,i});
        g[q-1].push_back({p-1,i});
    }
    dfs1(0,0);
    for(int i = 0, p, q, r, k; i<m; i++)
    {
        cin >> p >> q >> r;
        p--, q--, k = lca(p,q);
        if((p==k)||(q==k))
            in[k^p^q].push_back(r);
        else
            in[p].push_back(r), in[q].push_back(r), out[k].push_back(r);
        out[k].push_back(r);
    }
    for(int i = 0; i<n; i++)
        id[i] = i;
    dfs2(0,0,n-1);
    for(int i = 0; i<n-1; i++)
        cout << ans[i] << endl;
}
