#include <bits/stdc++.h>

using namespace std;

const int mx = (1 << 19);

int par[2 * mx];
vector<int> ch[2 * mx];

void proc(int lo, int hi, int lb, int ub, int ind, int id) {
    if(lo <= lb && ub <= hi) {
        ++par[ind], ch[id].push_back(ind);
        return;
    }
    int mid = (lb + ub) / 2;
    if(lo <= mid) proc(lo, hi, lb, mid, 2 * ind, id);
    if(mid < hi) proc(lo, hi, mid + 1, ub, 2 * ind + 1, id);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<array<int, 3>> qrs;
    for(int i = 1; i < mx; i++) {
        ch[i].push_back(2 * i); ch[i].push_back(2 * i + 1);
        ++par[2 * i], ++par[2 * i + 1];
    }
    for(int i = 0, l, r, ind; i < q; i++) {
        cin >> l >> r >> ind;
        qrs.push_back({l - 1, r - 1, ind - 1});
        if(ind != l) {
            proc(l - 1, ind - 2, 0, mx - 1, 1, ind + mx - 1);
        }
        if(ind != r) {
            proc(ind, r - 1, 0, mx - 1, 1, ind + mx - 1);
        }
    }
    vector<int> ans(n, -1);
    int ctr = 1;
    queue<int> qu;
    qu.push(1);
    while(!qu.empty()) {
        int u = qu.front(); qu.pop();
        if(u >= mx && u < mx + n) {
            ans[u - mx] = ctr++;
        }
        for(int c: ch[u]) {
            --par[c];
            if(par[c] == 0) {
                qu.push(c);
            }
        }
    }
    if(ctr < n + 1) {
        cout << "-1\n";
    } else {
        for(int a: ans) {
            cout << a << " ";
        }
        cout << '\n';
    }
}