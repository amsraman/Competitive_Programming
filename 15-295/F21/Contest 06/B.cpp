#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 1e15;

int n, a[500][500], x[500];
ll dist[500][500], ans[500];
bool in[500];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        cin >> x[i];
        --x[i];
    }
    reverse(x, x + n);
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][x[k]] + dist[x[k]][j]);
            }
        }
        for(int i = 0; i <= k; i++) {
            for(int j = 0; j <= k; j++) {
                if(dist[x[i]][x[j]] != INF) {
                    ans[k] += dist[x[i]][x[j]];
                }
            }
        }
    }
    reverse(ans, ans + n);
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}