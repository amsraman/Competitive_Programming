#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

struct DSU {
    int n;
    vector<int> link, sz, mn;
 
    DSU(int n): n(n), link(n), sz(n), mn(n) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            mn[i] = i;
            sz[i] = 1;
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }

    int get_mn(int x) {
        return mn[f(x)];
    }
 
    void unite(int x, int y) {
        x = f(x), y = f(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], mn[x] = min(mn[x], mn[y]), link[y] = x;
    }
};

int d, n, nc = 1, pos[500000], ans[500000];
vector<array<int, 3>> mod_edges[500000];
map<pair<int, array<int, 3>>, int> nxt_node;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> d >> n;
    vector<DSU> trees(d, DSU(n));
    for(int i = 0; i < d; i++) {
        vector<array<int, 3>> edges(n - 1);
        for(int j = 0; j < n - 1; j++) {
            cin >> edges[j][1] >> edges[j][2] >> edges[j][0];
            --edges[j][1], --edges[j][2];
        }
        sort(edges.begin(), edges.end());
        set<int> holder;
        vector<pair<int, int>> id_holder;
        for(int j = n - 2, k = n - 2; j >= 0; j--) {
            int mn1 = trees[i].get_mn(edges[j][1]), mn2 = trees[i].get_mn(edges[j][2]);
            holder.insert(mn1);
            holder.insert(mn2);
            if(j == 0 || edges[j][0] != edges[j - 1][0]) {
                while(k >= j) {
                    trees[i].unite(edges[k][1], edges[k][2]);
                    --k;
                }
                for(int h: holder) {
                    id_holder.push_back({trees[i].f(h), h});
                }
                sort(id_holder.begin(), id_holder.end());
                for(int x = 0; x < id_holder.size() - 1; x++) {
                    if(id_holder[x].f == id_holder[x + 1].f) {
                        mod_edges[i].push_back({edges[j][0], id_holder[x].s, id_holder[x + 1].s});
                    }
                }
                holder.clear();
                id_holder.clear();
            }
        }
        sort(mod_edges[i].begin(), mod_edges[i].end());
    }
    for(int i = 0; i < d; i++) {
        int cur = 1;
        for(array<int, 3> e: mod_edges[i]) {
            if(nxt_node[{cur, e}] == 0) {
                nxt_node[{cur, e}] = ++nc;
            }
            cur = nxt_node[{cur, e}];
        }
        if(pos[cur] == 0) {
            pos[cur] = i + 1;
        }
        ans[i] = pos[cur];
    }
    for(int i = 0; i < d; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
}