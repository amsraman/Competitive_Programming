#include <bits/stdc++.h>

using namespace std;

int main() {
	int t; cin >> t;
	for(int _ = 1; _ <= t; _++) {
		int n, d; cin >> n >> d;
		int ct = 0;
		map<string, int> ind;
		vector<string> r_ind;
		vector<vector<int>> g;
		for(int i = 0; i < n; i++) {
			string name; cin >> name;
			if(!ind.count(name)) {
				ind[name] = ct++;
				r_ind.push_back(name);
				g.emplace_back();
			}
			int m; cin >> m;
			for(int j = 0; j < m; j++) {
				string dname; cin >> dname;
				if(!ind.count(dname)) {
					ind[dname] = ct++;
					r_ind.push_back(dname);
					g.emplace_back();
				}
				g[ind[name]].push_back(ind[dname]);
			}
		}
		vector<vector<int>> ch(ct, vector<int>(d + 1, 0));
		vector<bool> can_be_root(ct, true);
		for(int i = 0; i < ct; i++) {
			for(int j: g[i]) {
				can_be_root[j] = false;
			}
		}
		int root = -1;
		for(int i = 0; i < ct; i++) {
			if(can_be_root[i]) {
				root = i;
			}
		}
		assert(root != -1);
		auto dfs = [&](auto rec, int u) -> void {
			ch[u][0] = 1;
			for(int v: g[u]) {
				rec(rec, v);
				for(int i = 0; i < d; i++) {
					ch[u][i + 1] += ch[v][i];
				}
			}
		};
		dfs(dfs, root);
		vector<pair<int, string>> res;
		for(int i = 0; i < ct; i++) {
			res.emplace_back(-ch[i][d], r_ind[i]);
		}
		sort(res.begin(), res.end());
		cout << "Tree " << _ << ":\n";
		for(int i = 0; i < (int) res.size(); i++) {
			if(res[i].first > res[2].first || res[i].first == 0) break;
			cout << res[i].second << " " << -res[i].first << '\n';
		}
		cout << '\n';
	}
}