#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int ub = 50 * 20 * 20;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		vector<vector<int>> dice(n);
		int lb = 0;
		for(int i = 0, f; i < n; i++) {
			cin >> f; dice[i].resize(f);
			for(int j = 0; j < f; j++) {
				cin >> dice[i][j];
			}
			sort(dice[i].begin(), dice[i].end());
			lb += dice[i][0];
		}
		vector<ll> dp(ub + 1, 0); dp[0] = 1;
		for(vector<int> faces: dice) {
			for(int i = ub; i >= 0; i--) {
				dp[i] = 0;
				for(int f: faces) {
					if(i >= f) {
						dp[i] += dp[i - f];
					}
				}
			}
		}
		int r; cin >> r;
		vector<pair<int, int>> sums;
		int m; cin >> m;
		int mxv = 0;
		for(int i = 0; i < m; i++) {
			int v, c; cin >> v >> c;
			sums.emplace_back(v, c);
			mxv = max(mxv, v);
		}
		sort(sums.begin(), sums.end());
		vector<int> cur(r), res;
		int ct = 0;
		auto gen = [&m, &r, &cur, &res, &sums, &dp, &mxv](auto rec, int lev, int lb) -> void {
			if(lev == r) { // check if valid
				bool bad = false;
				for(int i = m - 1; i >= 0; i--) {
					auto [v, c] = sums[i];
					ll tot = 0;
					for(int f: cur) {
						if(v >= f) {
							tot += dp[v - f];
						}
					}
					if(tot != c) {
						bad = true;
						break;
					}
				}
				if(!bad) {
					res = cur;
				}
				return;
			}
			for(int i = lb; i <= min(50, mxv); i++) {
				cur[lev] = i;
				rec(rec, lev + 1, i);
				if(!res.empty()) return;
			}
		};
		vector<pair<int, int>> real_sum;
		int mnv = 1e9;
		for(auto [v, c]: sums) {
			if(v < lb + 1 && c == 0) {
				continue;
			}
			real_sum.emplace_back(v, c);
			mnv = min(mnv, v);
		}
		sums = real_sum;
		m = (int)sums.size();
		if(mnv >= lb + 1 && mxv <= ub + 50) {
			gen(gen, 0, 1);
		}
		if(res.empty()) {
			cout << "Impossible\n";
		} else {
			cout << "Final die face values are";
			for(int r: res) {
				cout << " " << r;
			}
			cout << '\n';
		}
		cin >> n;
	}
}