#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m, s, t; cin >> n >> m >> s >> t;
	vector<vector<int>> g(n);
	for(int i = 0, u, v; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<long long> sq(n, 0); sq[s] = 1;
	for(int i = 0; i < t; i++) {
		vector<long long> sq1(n, 0);
		for(int u = 0; u < n; u++) {
			for(int v: g[u]) {
				sq1[v] += sq[u];
			}
		}
		sq = sq1;
	}
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		ans += sq[i];
	}
	cout << ans << '\n';
}