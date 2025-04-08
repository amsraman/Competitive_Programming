#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m; cin >> n >> m;
	for(int _ = 1; n + m > 0; _++) {
		vector<vector<int>> blocked(n, vector<int>(m, 0));
		vector<vector<int>> safe(n, vector<int>(m, 1));
		vector<pair<int, int>> queens;
		int k; cin >> k;
		for(int i = 0, x, y; i < k; i++) { // queen
			cin >> x >> y; --x, --y;
			queens.emplace_back(x, y);
			safe[x][y] = 0, blocked[x][y] = 1;
		}
		cin >> k;
		for(int i = 0, x, y; i < k; i++) { // knight
			cin >> x >> y; --x, --y;
			vector<pair<int, int>> knight_moves = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
			for(auto [dx, dy]: knight_moves) {
				if(x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
					safe[x + dx][y + dy] = 0;
				}
			}
			safe[x][y] = 0, blocked[x][y] = 1;
		}
		cin >> k;
		for(int i = 0, x, y; i < k; i++) { // pawn
			cin >> x >> y; --x, --y;
			safe[x][y] = 0, blocked[x][y] = 1;
		}
		for(auto [x, y]: queens) {
			vector<pair<int, int>> queen_moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
			for(auto [dx, dy]: queen_moves) {
				int cx = x + dx, cy = y + dy;
				while(cx >= 0 && cx < n && cy >= 0 && cy < m && !blocked[cx][cy]) {
					safe[cx][cy] = 0;
					cx += dx, cy += dy;
				}
			}
		}
		int res = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				res += safe[i][j];
			}
		}
		cout << "Board " << _ << " has " << res << " safe squares.\n";
		cin >> n >> m;
	}
}