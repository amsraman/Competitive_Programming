#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m, s, e; cin >> n >> m >> s >> e;
	while(n > 0) {
		vector<vector<pair<int, int>>> g(n);
		vector<pair<int, int>> lights;
		for(int i = 0, g, y, r; i < n; i++) {
			cin >> g >> y >> r; g += y;
			lights.emplace_back(g, r);
		}
		for(int i = 0, l1, l2, t; i < m; i++) {
			cin >> l1 >> l2 >> t;
			g[l1].emplace_back(l2, t);
			g[l2].emplace_back(l1, t);
		}
		auto state = [](int g, int r, ll tm) -> int { // 1 if red light
			tm %= (g + r); // end of a red light is bad, end of a green light is good
			return tm >= g;
		};
		vector<vector<ll>> dist(n, vector<ll>(2, 1e18));
		dist[s][1] = 0;
		priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> q;
		q.push({0, s, 1});
		while(!q.empty()) {
			auto [d, u, p] = q.top(); q.pop();
			ll extra = 0;
			if(p == 1) {
				auto [g, r] = lights[u];
				extra = (d + g + r - 1) / (g + r) * (g + r) + 5 - d;
			}
			for(auto [v, w]: g[u]) {
				ll new_d = d + w + extra;
				auto [g, r] = lights[v];
				int new_state = state(g, r, new_d);
				if(new_d < dist[v][new_state]) {
					dist[v][new_state] = new_d;
					q.push({new_d, v, new_state});
				}
			}
		}
		ll ans = min(dist[e][0], dist[e][1]);
		cout << ans / 60 << ":" << (ans % 60) / 10 << ans % 60 % 10 << '\n';
		cin >> n >> m >> s >> e;
	}
}