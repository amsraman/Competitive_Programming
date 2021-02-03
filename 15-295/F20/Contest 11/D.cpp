#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, m, l, link[250000], sz[250000], val[250000], par[250000][18], mn[250000][18], depth[250000];
pair<int,int> coords[500];
vector<int> g[250000];
vector<array<int,3>> edges;

int dist(int x, int y)
{
    int dx = coords[x].f-coords[y].f, dy = coords[x].s-coords[y].s;
    return dx*dx+dy*dy;
}

int conv(int x, int y)
{
    return n*x+y;
}

void addEdge(int x, int y)
{
    edges.push_back({min(val[x],val[y]),x,y});
}

int f(int x)
{
    return (x==link[x]?x:link[x]=f(link[x]));
}

void unite(int x, int y)
{
    g[x].push_back(y), g[y].push_back(x);
    x = f(x), y = f(y);
    if(sz[y]>sz[x])
        swap(x,y);
    link[y] = x, sz[x]+=sz[y];
}

void dfs(int x, int p)
{
    par[x][0] = p, mn[x][0] = val[x];
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            depth[g[x][i]] = depth[x]+1, dfs(g[x][i],x);
}

double qry(int x, int y)
{
    int ret = min(val[x],val[y]);
    if(depth[x]<depth[y])
        swap(x,y);
    for(int i = 0; i<18; i++)
        if((1<<i)&(depth[x]-depth[y]))
            ret = min(ret,mn[x][i]), x = par[x][i];
    for(int i = 17; i>=0; i--)
        if(par[x][i]!=par[y][i])
            ret = min({ret,mn[x][i],mn[y][i]}), x = par[x][i], y = par[y][i];
    ret = min({ret,val[x],val[y]});
    return sqrt((x==y?ret:min(ret,val[par[x][0]])));
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> coords[i].f >> coords[i].s;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            val[conv(i,j)] = dist(i,j);
    cin >> m;
    for(int i = 0, a, b; i<m; i++)
    {
        cin >> a >> b;
        for(int j = 0; j<n; j++)
            addEdge(conv(j,a-1),conv(j,b-1)), addEdge(conv(a-1,j),conv(b-1,j));
    }
    sort(edges.begin(),edges.end());
    for(int i = 0; i<n*n; i++)
        link[i] = i, sz[i] = 1;
    for(int i = edges.size()-1; i>=0; i--)
        if(f(edges[i][1])!=f(edges[i][2]))
            unite(edges[i][1],edges[i][2]);
    dfs(0,0);
    for(int i = 0; i<17; i++)
        for(int j = 0; j<n*n; j++)
            par[j][i+1] = par[par[j][i]][i], mn[j][i+1] = min(mn[j][i],mn[par[j][i]][i]);
    cin >> l;
    for(int i = 0, a, b; i<l; i++)
    {
        cin >> a >> b;
        cout << fixed << setprecision(11) << qry(conv(a-1,b-1),conv(b-1,a-1)) << endl;
    }
}
