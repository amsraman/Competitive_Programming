#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
	int m, n, k, s; cin >> m >> n >> k >> s;
	vector<fl> x(m + n); n += m;
	for(int i = 0; i < n; i++) {
		cin >> x[i];
	}
	sort(x.begin(), x.end());
	vector<vector<fl>> cst(n, vector<fl>(n));
	for(int i = 0; i < n; i++) { // find costs
		fl a = 0, b = 0, c = 0;
		for(int j = i; j < n; j++) {
			++a, b -= 2 * x[j], c += x[j] * x[j];
			cst[i][j] = c - b * b / (4 * a);
		}
	}
	vector<vector<fl>> dp(n, vector<fl>(k, 1e18));
	for(int i = 0; i < n; i++) {
		dp[i][0] = cst[0][i];
	}
	auto solve = [&](auto rec, int lo, int hi, int lb, int ub, int lev) -> void {
		if(lo > hi) return;
		int mid = (lo + hi) / 2, opt = lb;
		for(int i = lb; i <= ub; i++) {
			if(i < mid && (dp[i][lev] + cst[i + 1][mid] < dp[mid][lev + 1])) {
				dp[mid][lev + 1] = dp[i][lev] + cst[i + 1][mid], opt = i;
			}
		}
		if(lo == hi) return;
		rec(rec, lo, mid - 1, lb, opt, lev);
		rec(rec, mid + 1, hi, opt, ub, lev);
	};
	for(int i = 0; i < k - 1; i++) { // transition from i to i + 1
		solve(solve, 0, n - 1, i, n - 1, i);
	}
	fl ht = fl(s) / 2;
	cout << fixed << setprecision(6) << dp[n - 1][k - 1] + n * ht * ht << '\n';
}