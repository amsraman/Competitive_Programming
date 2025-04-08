#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int n, m; cin >> n >> m;
	for(int _ = 1; n > 0; _++) {
		vector<vector<int>> h(n, vector<int>(m));
		vector<vector<bool>> dead(n + 2, vector<bool>(m + 2, false)), vis(n + 2, vector<bool>(m + 2, false));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				cin >> h[i][j];
			}
		}
		int ans = 0; bool bad = false;
		for(; ans <= 1001; ans++) {
			for(int i = 0; i <= n + 1; i++) {
				for(int j = 0; j <= m + 1; j++) {
					if(i == 0 || i == n + 1 || j == 0 || j == m + 1) {
						dead[i][j] = true;
					} else {
						dead[i][j] = h[i - 1][j - 1] == 0;
					}
				}
			}
			auto ok = [&](int x, int y) {
				return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1;
			};
			auto dfs = [&](auto rec, int x, int y) -> void {
				vis[x][y] = true;
				for(auto [dx, dy]: dir) {
					if(ok(x + dx, y + dy) && dead[x + dx][y + dy] == dead[x][y] && !vis[x + dx][y + dy]) {
						rec(rec, x + dx, y + dy);
					}
				}
			};
			dfs(dfs, 0, 0);
			for(int i = 0; i <= n; i++) {
				for(int j = 0; j <= m; j++) {
					dead[i][j] = vis[i][j];
				}
			}
			int cc = 0;
			for(int i = 0; i <= n + 1; i++) {
				for(int j = 0; j <= m + 1; j++) {
					if(!vis[i][j] && !dead[i][j]) {
						dfs(dfs, i, j);
						++cc;
					}
				}
			}
			if(cc >= 2) {
				break;
			}
			for(int i = 0; i <= n + 1; i++) {
				for(int j = 0; j <= m + 1; j++) {
					vis[i][j] = false;
				}
			}
			bool all_dead = true;
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(h[i][j] > 0) {
						all_dead = false;
						--h[i][j];
					}
				}
			}
			if(all_dead) {
				bad = true;
				break;
			}
		}
		cout << "Case " << _ << ": ";
		if(bad) {
			cout << "Island never splits.\n";
		} else {
			cout << "Island splits when ocean rises " << ans << " feet.\n";
		}
		cin >> n >> m;
	}
}