#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, a, b, x[200000], y[200000], anc[200000], depth[200000], par[200000][18];
ll pre[200000], ans;
map<pair<int,int>,ll> cnts;
vector<int> g[200000];

void dfs(int cur)
{
    for(int i = 1; i<18; i++)
        par[cur][i] = par[par[cur][i-1]][i-1];
    for(int i = 0; i<g[cur].size(); i++)
        if(g[cur][i]!=par[cur][0])
            par[g[cur][i]][0] = cur, depth[g[cur][i]] = depth[cur]+1, dfs(g[cur][i]);
}

int lca(int u, int v)
{
    if(depth[u]>depth[v])
        swap(u,v);
    for(int i = 17; i>=0; i--)
        if(depth[v]-depth[u]>=(1<<i))
            v = par[v][i];
    for(int i = 17; i>=0; i--)
        if(par[u][i]!=par[v][i])
            u = par[u][i], v = par[v][i];
    if(u==v)
        return u;
    return par[u][0];
}

int branch(int u, int v)
{
    if(u==v)
        return -1;
    for(int i = 17; i>=0; i--)
        if(depth[v]-depth[u]>(1<<i))
            v = par[v][i];
    return v;
}

void dfsum(int cur)
{
    for(int i = 0; i<g[cur].size(); i++)
        if(g[cur][i]!=par[cur][0])
            pre[g[cur][i]]+=pre[cur], dfsum(g[cur][i]);
}

int main()
{
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    dfs(0);
    for(int i = 0; i<=m-n; i++)
    {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--, anc[i] = lca(x[i],y[i]);
        int u = branch(anc[i],x[i]), v = branch(anc[i],y[i]);
        if((u+1)&&(v+1))//Accounts for overlap, in case segments intersect twice
        {
            if(u<v)
                swap(u,v);
            ans-=cnts[{u,v}];
            cnts[{u,v}]++;
        }
        if(u+1)
            pre[u]++;
        if(v+1)
            pre[v]++;
    }
    for(int i = 0; i<n; i++)//Accounts for more overlap, in case multiple paths begin at the same branch
        ans+=((pre[i]-pre[i]*pre[i])/2);
    dfsum(0);
    for(int i = 0; i<=m-n; i++)
        ans+=(pre[x[i]]+pre[y[i]]-2*pre[anc[i]]-(x[i]!=anc[i])-(y[i]!=anc[i])); //PIE accounting for whether x or y is the lca
    cout << ans << endl;
}
