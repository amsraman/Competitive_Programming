#include <bits/stdc++.h>

using namespace std;

int n, m, nc = 1, nxt[200001][26], t, in[200001], out[200001], pio[200001];
vector<int> vals[200001], ord;
string s[200000];

void dfs(int x) {
    in[x] = t;
    for(int i: vals[x]) {
        ord.push_back(i);
        pio[i] = t++;
    }
    for(int i = 0; i < 26; i++) {
        if(nxt[x][i] != 0) {
            dfs(nxt[x][i]);
        }
    }
    out[x] = t - 1;
}

const int mxN = 2e5;

int root[200000], lc[mxN * 200], rc[mxN * 200], val[mxN * 200], tot;

int seg_qry(int &ind, int lb, int ub, int lo, int hi) {
    if(ind == 0) {
        return 0;
    }
    if(lb <= lo && hi <= ub) {
        return val[ind];
    }
    int mid = (lo + hi) / 2, ret = 0;
    if(lb <= mid) {
        ret += seg_qry(lc[ind], lb, ub, lo, mid);
    }
    if(ub > mid) {
        ret += seg_qry(rc[ind], lb, ub, mid + 1, hi);
    }
    return ret;
}

void seg_upd(int &ind, int pos, int lo, int hi, int delta) {
    if(ind == 0) {
        ind = ++tot;
    }
    val[ind] += delta;
    if(lo == hi) {
        return;
    }
    int mid = (lo + hi) / 2;
    if(pos <= mid) {
        seg_upd(lc[ind], pos, lo, mid, delta);
    } else {
        seg_upd(rc[ind], pos, mid + 1, hi, delta);
    }
}

int qry(int lb, int ub, int k) {
    int ret = 0;
    for(k++; k > 0; k -= (k & -k)) {
        ret += seg_qry(root[k - 1], lb, ub, 0, n - 1);
    }
    return ret;
}

int qry(int lb, int ub, int lo, int hi) {
    return qry(lb, ub, hi) - qry(lb, ub, lo - 1);
}

void upd(int k, int pos, int delta) {
    for(k++; k <= n; k += (k & -k)) {
        seg_upd(root[k - 1], pos, 0, n - 1, delta);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        int cur = 0;
        for(char c: s[i]) {
            if(nxt[cur][c - 'a'] == 0) {
                nxt[cur][c - 'a'] = ++nc;
            }
            cur = nxt[cur][c - 'a'];
        }
        vals[cur].push_back(i + 1);
    }
    dfs(0);
    for(int i = 0; i < n; i++) {
        upd(i, ord[i] - 1, 1);
    }
    for(int i = 0; i < m; i++) {
        int opt;
        cin >> opt;
        if(opt == 1) {
            int ind1, ind2;
            cin >> ind1 >> ind2;
            if(ind1 == ind2) {
                continue;
            }
            upd(pio[ind1], ind1 - 1, -1);
            upd(pio[ind2], ind2 - 1, -1);
            upd(pio[ind1], ind2 - 1, 1);
            upd(pio[ind2], ind1 - 1, 1);
            swap(pio[ind1], pio[ind2]);
            // swap things somehow
        } else {
            string q;
            cin >> q;
            int k, l, r;
            cin >> k >> l >> r;
            int cur = 0;
            for(int j = 0; j < k; j++) {
                if(nxt[cur][q[j] - 'a'] == 0) {
                    cur = -1;
                    break;
                }
                cur = nxt[cur][q[j] - 'a'];
            }
            if(cur == -1) {
                cout << 0 << '\n';
            } else {
                // output number of things in the subtree of cur that are between l and r
                cout << qry(l - 1, r - 1, in[cur], out[cur]) << '\n';
            }
        }
    }
}