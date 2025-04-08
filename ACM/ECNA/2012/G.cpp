#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	for(int _ = 1; n > 0; _++) {
		map<string, int> curr; int cc = 0;
		vector<vector<tuple<ll, ll, int>>> g;
		vector<vector<pair<ll, ll>>> adj;
		vector<string> ref;
		for(int i = 0; i < n; i++) {
			int val1, val2;
			string curr1, curr2, eq;
			cin >> val1 >> curr1 >> eq >> val2 >> curr2;
			if(!curr.count(curr1)) curr[curr1] = cc++, ref.push_back(curr1), g.emplace_back();
			if(!curr.count(curr2)) curr[curr2] = cc++, ref.push_back(curr2), g.emplace_back();
			g[curr[curr1]].emplace_back(val1, val2, curr[curr2]);
			g[curr[curr2]].emplace_back(val2, val1, curr[curr1]);
		}
		adj.resize(cc);
		for(int i = 0; i < cc; i++) {
			adj[i].resize(cc, {-1, -1});
			for(auto [val1, val2, targ]: g[i]) {
				adj[i][targ] = make_pair(val1, val2);
			}
		}
		for(int k = 0; k < cc; k++) {
			for(int i = 0; i < cc; i++) {
				for(int j = 0; j < cc; j++) {
					if(adj[i][k].first != -1 && adj[k][j].first != -1 && adj[i][j].first == -1) {
						adj[i][j] = make_pair(adj[i][k].first * adj[k][j].first, adj[i][k].second * adj[k][j].second);
						ll g = __gcd(adj[i][j].first, adj[i][j].second);
						adj[i][j].first /= g, adj[i][j].second /= g;
					}
				}
			}
		}
		int amt_want; string curr_want; cin >> amt_want >> curr_want;
		ll amt_give; string curr_give; double mn_delta = 1e9;
		for(int i = 0, cw = curr[curr_want]; i < cc; i++) {
			if(i != cw && adj[cw][i].first != -1) {
				auto [x, y] = adj[cw][i];
				ll cur_give = (amt_want * y + x - 1) / x;
				long double delta = (long double) cur_give / y * x - amt_want;
				if(delta < mn_delta && cur_give <= 100000) {
					mn_delta = delta;
					amt_give = cur_give;
					curr_give = ref[i];
				}
			}
		}
		cout << "Case " << _ << ": " << amt_give << " " << curr_give << '\n';
		cin >> n;
	}
}