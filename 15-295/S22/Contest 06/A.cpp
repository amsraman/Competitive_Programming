#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld INF = 2.0;

int n, m;
ld dist[100][100];

int main() {
    cin >> n;
    while(n != 0) {
        cin >> m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    dist[i][j] = 1e14;
                }
            }
        }
        for(int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            dist[u - 1][v - 1] = dist[v - 1][u - 1] = log(100.0) - log((ld) w);
        }
        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        cout << fixed << setprecision(6) << exp(log(100.0) - dist[0][n - 1]) << endl;
        cin >> n;
    }
}