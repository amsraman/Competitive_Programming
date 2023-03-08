template <typename T>
pair<T, vector<int>> hungarian(const vector<vector<T>> & costs) { // Matches columns to rows
    int n = costs.size() - 1, m = costs[0].size() - 1;
    vector<int> match(m + 1, 0);
    vector<T> u(n + 1, 0), v(m + 1, 0);
    for(int i = 1; i <= n; i++) {
        const T INF = numeric_limits<T>::max();
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