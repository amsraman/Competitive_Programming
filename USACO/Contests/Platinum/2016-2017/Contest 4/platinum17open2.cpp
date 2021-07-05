#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, k, q, col[200000], par[200000], wt[200000];
vector<pair<int,int>> g[200000];
vector<array<int,3>> edges;
multiset<int> edge_set;
multiset<pair<int,int>> incident_edges[200000];

struct DSU {
    int link[200000], sz[200000];
    void init() {
        for(int i = 0; i<n; i++)
            link[i] = i, sz[i] = 1;
    }
    int trace(int x) {
        return (x == link[x] ? x : link[x] = trace(link[x]));
    }
    void unite(int x, int y) {
        if((x = trace(x)) == (y = trace(y)))
            return;
        if(sz[x]<sz[y])
            swap(x,y);
        link[y] = x, sz[x]+=sz[y];
    }
} mst;

void add_edge_set(int ind, int clr) {
    auto it = incident_edges[ind].lower_bound({clr,0});
    if(it != incident_edges[ind].end() && it->f == clr)
        edge_set.insert(it->s);
}

void rem_edge_set(int ind, int clr) {
    auto it = incident_edges[ind].lower_bound({clr,0});
    if(it != incident_edges[ind].end() && it->f == clr)
        edge_set.erase(edge_set.find(it->s));
}

void dfs(int x, int p = 0) {
    for(pair<int,int> i: g[x]) {
        if(i.s!=p) {
            incident_edges[x].insert({col[i.s],i.f});
            dfs(i.s,x), par[i.s] = x, wt[i.s] = i.f;
        }
    }
    int rec = -1;
    for(pair<int,int> i: incident_edges[x]) {
        if(i.f != rec && i.f != col[x]) {
            edge_set.insert(i.s);
            rec = i.f;
        }
    }
}

int main() {
    ifstream cin("grass.in");
    ofstream cout("grass.out");
    cin >> n >> m >> k >> q;
    for(int i = 0, a, b, l; i<m; i++) {
        cin >> a >> b >> l;
        edges.push_back({l,a-1,b-1});
    }
    for(int i = 0; i<n; i++)
        cin >> col[i];
    sort(edges.begin(),edges.end()), mst.init();
    for(array<int,3> e: edges)
        if(mst.trace(e[1])!=mst.trace(e[2]))
            mst.unite(e[1],e[2]), g[e[1]].push_back({e[0],e[2]}), g[e[2]].push_back({e[0],e[1]});
    dfs(0,0);
    for(int i = 0, a, b; i<q; i++) {
        cin >> a >> b;
        --a;
        if(a != 0) {
            if(col[a] != col[par[a]])
                rem_edge_set(par[a],col[a]);
            if(col[par[a]] != b)
                rem_edge_set(par[a],b);
            incident_edges[par[a]].erase(incident_edges[par[a]].find({col[a],wt[a]}));
            incident_edges[par[a]].insert({b,wt[a]});
            if(col[a] != col[par[a]])
                add_edge_set(par[a],col[a]);
            if(col[par[a]] != b)
                add_edge_set(par[a],b);
        }
        rem_edge_set(a,b), add_edge_set(a,col[a]), col[a] = b;
        cout << *edge_set.begin() << '\n';
    }
}