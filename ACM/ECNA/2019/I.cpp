#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for(int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	vector<vector<ll>> ps(n + 1, vector<ll>(m + 1, 0));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			ps[i + 1][j + 1] = grid[i][j] == '$';
			if(grid[i][j] == '#') {
				ps[i + 1][j + 1] -= 1e4;
			}
			ps[i + 1][j + 1] += ps[i + 1][j] + ps[i][j + 1] - ps[i][j];
		}
	}
	bool found = false; int ct = 0;
	vector<vector<int>> mark(n, vector<int>(m, -1));
	auto gen = [&](auto rec, int lev) -> void {
		if(lev == n * m) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(mark[i][j] == -1) {
						cout << '#';
					} else {
						char let;
						if(mark[i][j] < 26) let = char('A' + mark[i][j]);
						else let = char('a' + mark[i][j] - 26);
						cout << let;
					}
				}
				cout << '\n';
			}
			found = true;
			return;
		}
		int x = lev / m, y = lev % m;
		if(grid[x][y] == '#' || mark[x][y] != -1) {
			rec(rec, lev + 1);
			return;
		}
		int lb = 1e9, ub = -1e9;
		for(int i = 1; i <= min(n - x, m - y); i++) {
			if(mark[x][y + i - 1] != -1) break;
			if(ps[x + i][y + i] - ps[x + i][y] - ps[x][y + i] + ps[x][y] == 1) {
				lb = min(lb, i);
				ub = max(ub, i);
			}
		}
		if(lb < 1e9) {
			for(int i = 0; i < ub; i++) {
				for(int j = 0; j < ub; j++) {
					mark[x + i][y + j] = ct;
				}
			}
			ct++;
			for(int i = ub; i >= lb; i--) {
				rec(rec, lev + i);
				if(found) return;
				for(int j = 0; j < i - 1; j++) mark[x + i - 1][y + j] = mark[x + j][y + i - 1] = -1;
				mark[x + i - 1][y + i - 1] = -1;
			}
			ct--;
			for(int i = 0; i < lb - 1; i++) {
				for(int j = 0; j < lb - 1; j++) {
					mark[x + i][y + j] = -1;
				}
			}
		}
	};
	gen(gen, 0);
	if(!found) {
		cout << "elgnatcer\n";
	}
}