#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 1e18;

int n, p[400];
ll a[400], b[400], c[400];

ll hungarian(vector<vector<int>> & costs) {
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for(int i = 0; i < n; i++) {
        p[0] = i + 1;
        int j0 = 0;
        vector<ll> minv(n + 1, INF);
        vector<bool> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1;
            ll delta = INF;
            for(int j = 1; j <= n; j++) {
                if(!used[j]) {
                    ll cur = costs[i0 - 1][j - 1] - u[i0] - v[j];
                    if(cur < minv[j]) {
                        minv[j] = cur, way[j] = j0;
                    }
                    if(minv[j] < delta) {
                        delta = minv[j], j1 = j;
                    }
                }
            }
            for(int j = 0; j <= n; j++) {
                if(used[j]) {
                    u[p[j]] += delta, v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while(j0);
    }
    return -v[0];
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> costs(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(a[k] < c[i] + b[j]) {
                    costs[i][j] -= p[k];
                }
            }
        }
    }
    cout << -hungarian(costs) << endl;
}