#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int m, n, t, elev[250000], st[250000], link[250000], sz[250000];
ll ans;
vector<pair<int,pair<int,int> > > edges;

int conv(int i, int j)
{
    return n*i+j;
}

int f(int x)
{
    while(x!=link[x])
        x = link[x];
    return x;
}

void unite(int a, int b)
{
    a = f(a), b = f(b);
    if(sz[a]<sz[b])
        swap(a,b);
    link[b] = a, sz[a]+=sz[b], st[a]+=st[b];
}

int main()
{
    freopen("skilevel.in","r",stdin);
    freopen("skilevel.out","w",stdout);
    cin >> m >> n >> t;
    for(int i = 0; i<m; i++)
        for(int j = 0; j<n; j++)
            cin >> elev[conv(i,j)];
    for(int i = 0; i<m; i++)
        for(int j = 0; j<n; j++)
            cin >> st[conv(i,j)];
    for(int i = 0; i<m-1; i++)
        for(int j = 0; j<n; j++)
            edges.push_back({abs(elev[conv(i,j)]-elev[conv(i+1,j)]),{conv(i,j),conv(i+1,j)}});
    for(int i = 0; i<m; i++)
        for(int j = 0; j<n-1; j++)
            edges.push_back({abs(elev[conv(i,j)]-elev[conv(i,j+1)]),{conv(i,j),conv(i,j+1)}});
    sort(edges.begin(),edges.end());
    for(int i = 0; i<m*n; i++)
        link[i] = i, sz[i] = 1;
    for(int i = 0; i<edges.size(); i++)
        if(f(edges[i].s.f)!=f(edges[i].s.s))
        {
            unite(edges[i].s.f,edges[i].s.s);
            if(sz[f(edges[i].s.f)]>=t)
                ans+=(ll(st[f(edges[i].s.f)])*ll(edges[i].f)), st[f(edges[i].s.f)] = 0;
        }
    cout << ans << endl;
}
