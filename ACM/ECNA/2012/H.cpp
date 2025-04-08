#include <bits/stdc++.h>

using namespace std;

template <typename T>
pair<T, vector<int>> hungarian(const vector<vector<T>> & costs) { // Matches columns to rows
    int n = costs.size() - 1, m = costs[0].size() - 1;
    const T INF = numeric_limits<T>::max();
    vector<int> match(m + 1, 0);
    vector<T> u(n + 1, 0), v(m + 1, 0);
    for(int i = 1; i <= n; i++) {
        int cur_col = 0; match[cur_col] = i;
        vector<int> pv(m + 1, -1); vector<T> dist(m + 1, INF); vector<bool> used(m + 1, false);
        while(match[cur_col]) { // Dijkstra
            int row = match[cur_col], nxt_col; T delta = INF; used[cur_col] = true;
            for(int j = 0; j <= m; j++) {
                if(!used[j]) {
                    if(costs[row][j] - u[row] - v[j] < dist[j]) {
                        dist[j] = costs[row][j] - u[row] - v[j], pv[j] = cur_col;
                    }
                    if(dist[j] < delta) {
                        delta = dist[j], nxt_col = j;
                    }
                }
            }
            for(int j = 0; j <= m; j++) { // Augment
                if(used[j]) {
                    u[match[j]] += delta, v[j] -= delta;
                } else {
                    dist[j] -= delta;
                }
            }
            cur_col = nxt_col;
        }
        for(int nxt_col; cur_col; cur_col = nxt_col) { // Flip alternating path
            match[cur_col] = match[nxt_col = pv[cur_col]];
        }
    }
    return {-v[0], match};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<vector<int>> frame(n + 1, vector<int>(n + 1, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> frame[j + 1][i + 1];
            }
        }
        auto [frame_cost, frame_a] = hungarian(frame);
        vector<int> rframe_a(n);
        for(int i = 0; i < n; i++) {
            rframe_a[frame_a[i + 1] - 1] = i;
        }
        vector<vector<int>> up(n + 1, vector<int>(n + 1));
        vector<vector<int>> upc(n + 1, vector<int>(n + 1, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> up[j + 1][i + 1];
                upc[j + 1][i + 1] = up[j + 1][i + 1];
                int before_guy = rframe_a[j], time_ready = frame[frame_a[i + 1]][i + 1], time_done = frame[j + 1][before_guy + 1];
                upc[j + 1][i + 1] += max(time_ready, time_done);
            }
        }
        auto [up_cost, up_a] = hungarian(upc);
        cout << "Case " << _ << ":\n";
        int idle = 0;
        for(int i = 0; i < n; i++) {
            cout << "Worker " << i + 1 << ": ";
            cout << frame_a[i + 1] << " " << up_a[i + 1] << " " << upc[up_a[i + 1]][i + 1];
            idle += upc[up_a[i + 1]][i + 1] - up[up_a[i + 1]][i + 1] - frame[frame_a[i + 1]][i + 1];
            cout << '\n';
        }
        cout << "Total idle time: " << idle << '\n';
        cin >> n;
    }
}