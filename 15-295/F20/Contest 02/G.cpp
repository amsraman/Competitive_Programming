#include <bits/stdc++.h>

using namespace std;

template<class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;

    size_t n;
    vector<T_q> seg;
    vector<T_u> lazy;

    LazySegTree(size_t n): n(n), seg(2 * n, B::e_q), lazy(2 * n, B::e_u) {};

    void push(int ind, int lo, int hi) {
        seg[ind] = B::upd(seg[ind], lazy[ind], lo, hi);
        if(lo != hi) {
            lazy[2 * ind + 1] = B::comb_upd(lazy[2 * ind + 1], lazy[ind]);
            lazy[2 * ind + 2] = B::comb_upd(lazy[2 * ind + 2], lazy[ind]);
        }
        lazy[ind] = B::e_u;
    }

    T_q qry(int lo, int hi, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return B::e_q;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            return seg[ind];
        }
        int mid = (lo_ind + hi_ind) / 2;
        return B::comb(qry(lo, hi, lo_ind, mid, 2 * ind + 1), qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2));
    }

    T_q qry(int lo, int hi) {
        return (lo <= hi ? qry(lo, hi, 0, n - 1, 0) : B::e_q);
    }

    void upd(int lo, int hi, T_u delta, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            lazy[ind] = delta;
            push(ind, lo_ind, hi_ind);
            return;
        }
        int mid = (lo_ind + hi_ind) / 2;
        upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
        upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void upd(int lo, int hi, T_u delta) {
        return upd(lo, hi, delta, 0, n - 1, 0);
    }
};

struct SegInfo {
    using T_q = int;
    const T_q e_q = 0;

    using T_u = int;
    const T_u e_u = 0;

    T_q comb(T_q a, T_q b) {
        return a + b;
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        return (b ? (r - l + 1) - a : a);
    }

    T_u comb_upd(T_u a, T_u b) {
        return a ^ b;
    }
};

int n, m, sz[100000], nxt[100000], in[100000], out[100000], par[100000], ct, root[100000], ind[100000];
vector<int> g[100000], cur, ring;
bool vis[100000], in_ring[100000];
LazySegTree<SegInfo> tree_st((1 << 18)), ring_st((1 << 18));

void dfs_ring(int v, int p) {
    cur.push_back(v);
    vis[v] = true;
    for(int u: g[v]) {
        if(vis[u]) {
            if(ring.empty() && u != p) {
                for(int i = cur.size() - 1; i >= 0; i--) {
                    ring.push_back(cur[i]);
                    in_ring[cur[i]] = true;
                    if(cur[i] == u) {
                        break;
                    }
                }
            }
            continue;
        }
        dfs_ring(u, v);
    }
    cur.pop_back();
}

void dfs_sz(int v, int rt)  {
    sz[v] = 1, root[v] = rt;
    for(int &u: g[v]) {
        if(u == par[v] || in_ring[u]) {
            continue;
        }
        par[u] = v, dfs_sz(u, rt), sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]]) {
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v) {
    in[v] = ct++;
    for(int u: g[v]) {
        if(u != par[v] && !in_ring[u]) {
            nxt[u] = (u == g[v][0] ? nxt[v] : u);
            dfs_hld(u);
        }
    }
    out[v] = ct;
}

void path_upd(int u, int v) {
    while(nxt[u] != nxt[v]) {
        if(in[u] < in[v]) {
            swap(u, v);
        }
        tree_st.upd(in[nxt[u]], in[u], 1);
        u = par[nxt[u]];
    }
    if(in[u] > in[v]) {
        swap(u, v);
    }
    tree_st.upd(in[u] + 1, in[v], 1);
}

int main() {
    cin >> n >> m;
    for(int i = 0, u, v; i < n; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs_ring(0, 0);
    for(int i = 0; i < ring.size(); i++) {
        ind[ring[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        if(in_ring[i] && sz[i] == 0) {
            par[i] = i;
            dfs_sz(i, i);
        }
    }
    memset(nxt, -1, sizeof(nxt));
    for(int i = 0; i < n; i++) {
        if(in_ring[i] && nxt[i] == -1) {
            nxt[i] = i;
            dfs_hld(i), ct++;
        }
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        if(root[u - 1] == root[v - 1]) {
            path_upd(u - 1, v - 1);
        } else {
            path_upd(root[u - 1], u - 1);
            path_upd(root[v - 1], v - 1);
            // Find the path between root[u - 1] and root[v - 1]
            int ind1 = ind[root[u - 1]], ind2 = ind[root[v - 1]];
            int dist = abs(ind1 - ind2);
            int pv = ring[(ind1 + ring.size() - 1) % ring.size()];
            int nxt = ring[(ind1 + 1) % ring.size()];
            if(2 * dist < ring.size() || (2 * dist == ring.size() && ((ind1 < ind2) ^ (nxt > pv)))) {
                if(ind[root[u - 1]] > ind[root[v - 1]]) {
                    swap(u, v);
                }
                ring_st.upd(ind[root[u - 1]], ind[root[v - 1]] - 1, 1);
            } else {
                if(ind[root[u - 1]] > ind[root[v - 1]]) {
                    swap(u, v);
                }
                ring_st.upd(0, ind[root[u - 1]] - 1, 1);
                ring_st.upd(ind[root[v - 1]], ring.size() - 1, 1);
            }
        }
        cout << n - tree_st.qry(0, 2 * n) - min((int) ring.size() - 1, ring_st.qry(0, ring.size() - 1)) << endl;
    }
}