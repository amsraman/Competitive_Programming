#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, t[100000], subtree_sz[100000];
ll sum_tax[100000], dist[100000], sum_dist[100000], dist_tax[100000];
vector<pair<int,ll>> g[100000];

void dfs1(int x, int p)
{
    subtree_sz[x] = 1, sum_tax[x] = t[x], sum_dist[0]+=dist[x], dist_tax[0]+=t[x]*dist[x];
    for(pair<int,ll> i: g[x])
        if(i.f!=p)
            dist[i.f] = dist[x]+i.s, dfs1(i.f,x), subtree_sz[x]+=subtree_sz[i.f], sum_tax[x]+=sum_tax[i.f];
}

void dfs2(int x, int p)
{
    for(pair<int,ll> i: g[x])
        if(i.f!=p)
        {
            sum_dist[i.f] = sum_dist[x]+(n-2*subtree_sz[i.f])*i.s;
            dist_tax[i.f] = dist_tax[x]+(sum_tax[0]-2*sum_tax[i.f])*i.s;
            dfs2(i.f,x);
        }
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> t[i];
    for(int i = 0, u, v, w; i<n-1; i++)
    {
        cin >> u >> v >> w;
        g[u-1].push_back({v-1,w});
        g[v-1].push_back({u-1,w});
    }
    dfs1(0,0), dfs2(0,0);
    for(int i = 0; i<n; i++)
        cout << t[i]*sum_dist[i]+dist_tax[i] << endl;
}