#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m; cin >> n >> m;
	int _ = 0;
	while(n + m > 0) {
		_++;
		vector<vector<int>> board(n, vector<int>(m, 0));
		int k; cin >> k;
		for(int i = 0, x, y; i < k; i++) {
			cin >> x >> y;
			board[x][y] = 1;
		}
		int prod = n * m, ans = 0;
		vector<vector<int>> par(n, vector<int>(m)), nxt(n, vector<int>(m));
		for(int i = 0; i < 1 << prod; i++) {
			for(int j = 0; j < prod; j++) {
				int row = j / m, col = j % m;
				par[row][col] = (i >> j) & 1;
			}
			vector<int> dirs = {-1, 0, 1};
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					int neighbor = 0;
					for(int d1: dirs) {
						for(int d2: dirs) {
						 	if(d1 != 0 || d2 != 0) {
						 		int nx = (i + d1 + n) % n, ny = (j + d2 + m) % m;
						 		neighbor += par[nx][ny];
						 	}
						}
					}
					if(neighbor < 2 || neighbor > 3) {
						nxt[i][j] = 0;
					} else if(neighbor == 2) {
						nxt[i][j] = par[i][j];
					} else {
						nxt[i][j] = 1;
					}
				}
			}
			bool good = true;
			for(int x = 0; x < n; x++) {
				for(int y = 0; y < m; y++) {
					if(nxt[x][y] != board[x][y]) {
						good = false;
					}
				}
			}
			ans += (int) good;
		}
		if(ans == 0) {
			cout << "Case " << _ << ": Garden of Eden.\n";
		} else {
			cout << "Case " << _ << ": " << ans << " possible ancestors.\n";
		}
		cin >> n >> m;
	}
}