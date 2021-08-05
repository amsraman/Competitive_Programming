#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int block_size = 200;

int n, t = -1, par[70000], depth[70000], deg[70000], nearest_leaf[70000], diff[70000], val[400][140001], counter[400], cur_ans, ans[70000];
pair<int,int> range[70000];
vector<int> g[70000], inord;

void upd_val(int ind, bool down) {
    val[ind/block_size][diff[inord[ind]]+n] -= (2-deg[inord[ind]]);
    diff[inord[ind]] += (down ? 2 : -2);
    val[ind/block_size][diff[inord[ind]]+n] += (2-deg[inord[ind]]);
}

void upd_range(int l, int r, bool down) {
    for(; l%block_size != 0 && l<=r; ++l) {
        if(diff[inord[l]]<=counter[l/block_size]) {
            cur_ans -= (2-deg[inord[l]]);
        }
        upd_val(l,down);
        if(diff[inord[l]]<=counter[l/block_size]) {
            cur_ans += (2-deg[inord[l]]);
        }
    }
    for(; (r+1)%block_size != 0 && l<=r; --r) {
        if(diff[inord[r]]<=counter[r/block_size]) {
            cur_ans -= (2-deg[inord[r]]);
        }
        upd_val(r,down);
        if(diff[inord[r]]<=counter[r/block_size]) {
            cur_ans += (2-deg[inord[r]]);
        }
    }
    for(; l<r; l+=block_size) {
        if(down) {
            cur_ans -= (val[l/block_size][n+counter[l/block_size]]+val[l/block_size][n+counter[l/block_size]-1]);
            counter[l/block_size] -= 2;
        } else {
            cur_ans += (val[l/block_size][n+counter[l/block_size]+1]+val[l/block_size][n+counter[l/block_size]+2]);
            counter[l/block_size] += 2;
        }
    }
}

int init_dfs(int x, int p = 0, int d = 0) {
    par[x] = p, depth[x] = d, nearest_leaf[x] = (g[x].size()==1 ? 0 : n+1);
    inord.push_back(x), range[x].f = ++t;
    for(int i: g[x]) {
        if(i!=p) {
            nearest_leaf[x] = min(nearest_leaf[x],1+init_dfs(i,x,d+1));
        }
    }
    range[x].s = t;
    return nearest_leaf[x];
}

void dfs(int x, int p = 0) {
    ans[x] = cur_ans-(g[x].size()==1);
    for(int i: g[x]) {
        if(i!=p) {
            for(int j = 0; j<=(n-1)/block_size; j++)
                cur_ans += val[j][n+(++counter[j])];
            upd_range(range[i].f,range[i].s,true);
            dfs(i,x);
            upd_range(range[i].f,range[i].s,false);
            for(int j = 0; j<=(n-1)/block_size; j++)
                cur_ans -= val[j][n+(counter[j]--)];
        }
    }
}

int main() {
    ifstream cin("atlarge.in");
    ofstream cout("atlarge.out");
    cin >> n;
    for(int i, u, v; i<n-1; i++) {
        cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    init_dfs(0);
    for(int i = 0; i<n; i++) {
        nearest_leaf[inord[i]] = min(nearest_leaf[inord[i]],nearest_leaf[par[inord[i]]]+1);
        diff[inord[i]] = nearest_leaf[inord[i]]-depth[inord[i]], deg[inord[i]] = g[inord[i]].size();
        if(diff[inord[i]]<=0)
            cur_ans += (2-deg[inord[i]]);
        val[i/block_size][diff[inord[i]]+n] += 2-deg[inord[i]];
    }
    dfs(0);
    for(int i = 0; i<n; i++) {
        cout << ans[i] << '\n';
    }
}