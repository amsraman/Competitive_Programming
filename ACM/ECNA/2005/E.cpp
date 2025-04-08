#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m; cin >> n >> m;
	int _ = 0;
	while(n + m > 0) {
		_++;
		vector<tuple<int, int, int>> edges;
		for(int i = 0, u, v, w; i < m; i++) {
			cin >> u >> v >> w; --u, --v;
			edges.emplace_back(u, v, w);
		}
		int num_vis = 0, tm = 0;
		bool bad = false;
		vector<vector<int>> g(n);
		vector<int> in(n, -1), low(n);
		auto dfs = [&](auto rec, int u, int p) -> void {
			++num_vis;
			in[u] = low[u] = tm++;
			for(int v: g[u]) {
				if(v == p) continue;
				if(in[v] == -1) {
					rec(rec, v, u);
				}
				low[u] = min(low[u], low[v]);
			}
			if(u > 0 && low[u] == in[u]) {
				bad = true;
			}
		};
		auto is_ok = [&](int msk) {
		 	num_vis = 0, bad = false;
		 	fill(in.begin(), in.end(), -1);
		 	fill(low.begin(), low.end(), -1);
		 	for(int i = 0; i < m; i++) {
				if((msk >> i) & 1) {
					auto [u, v, w] = edges[i];
					g[u].push_back(v);
					g[v].push_back(u);
				}
			}
			dfs(dfs, 0, 0);
		 	for(int i = 0; i < n; i++) {
		 		g[i].clear();
		 	}
		 	if(num_vis < n || bad) {
		 		return false;
		 	}
		 	return true;
		};
		ll res = -1;
		for(int i = 1; i < 1 << m; i++) {
			if(is_ok(i)) {
				ll cst = 0;
				for(int j = 0; j < m; j++) {
					if((i >> j) & 1) {
						auto [u, v, w] = edges[j];
						cst += w;
					}
				}
				if(res == -1 || cst < res) {
					res = cst;
				}
			}
		}	
		if(res == -1) {
			cout << "There is no reliable net possible for test case " << _ << ".\n";
		} else {
			cout << "The minimal cost for test case " << _ << " is " << res << ".\n";
		}
		cin >> n >> m;
	}
}