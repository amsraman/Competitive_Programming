#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<string> grid(n + 2);
	for(int i = 1; i <= n; i++) {
		cin >> grid[i];
		grid[i] = "." + grid[i] + ".";
	}
	for(int i = 0; i <= m + 1; i++) {
		grid[0] += ".";
		grid[n + 1] += ".";
	}
	queue<pair<int, int>> q;
	vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	auto ok = [&](int x, int y) {
		return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1;
	};
	vector<vector<int>> ring(n + 2, vector<int>(m + 2, -1));
	for(int i = 0; i <= n + 1; i++) {
		for(int j = 0; j <= m + 1; j++) {
			if(grid[i][j] == '.') {
				q.push({i, j});
				ring[i][j] = 0;
			}
		}
	}
	int mx = 0;
	while(!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		mx = max(mx, ring[x][y]);
		for(auto [dx, dy]: dir) {
			if(ok(x + dx, y + dy) && ring[x + dx][y + dy] == -1) {
				ring[x + dx][y + dy] = ring[x][y] + 1;
				q.push({x + dx, y + dy});
			}
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cout << '.';
			if(mx >= 10 && ring[i + 1][j + 1] < 10) cout << '.';
			if(ring[i + 1][j + 1] == 0) cout << '.';
			else cout << ring[i + 1][j + 1];
		}
		cout << '\n';
	}
}