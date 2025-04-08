#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, d, a1, a2; cin >> n >> d >> a1 >> a2; --d;
	vector<vector<tuple<int, int, int>>> g(n);
	vector<vector<int>> ref(n, vector<int>(n, -1));
	for(int i = 0; i < n; i++) {
		int m; cin >> m;
		for(int j = 0; j < m; j++) {
			int dj, tj, aj; cin >> dj >> tj >> aj; --dj;
			ref[dj][i] = (aj + 180) % 360;
			g[i].emplace_back(dj, tj, aj);
		}
	}
	vector<vector<vector<int>>> dist(n, vector<vector<int>>(360, vector<int>(2, 1e9)));
	using state = tuple<int, int, int>;
	priority_queue<pair<int, state>, vector<pair<int, state>>, greater<pair<int, state>>> q;
	for(auto [v, t, a]: g[0]) {
		dist[v][ref[0][v]][0] = t;
		q.push({t, make_tuple(v, ref[0][v], 0)});
	}
	auto can_go = [&](int t1, int t2) {
		int ub = t1 + a1;
		int lb = t1 - a2;
		bool one = false, two = false;
		for(int i = -1; i <= 1; i++) {
			if(t2 + i * 360 >= lb && t2 + i * 360 <= t1) return true;
			if(t2 + i * 360 >= t1 && t2 + i * 360 <= ub) return true;
		}
		return false;
	};
	while(!q.empty()) {
		auto [cur_d, state] = q.top(); q.pop();
		auto [u, ang, seen] = state;
		if(cur_d > dist[u][ang][seen]) continue;
		if(u == d && seen == 0) {
			if(cur_d < dist[u][ang][1]) {
				dist[u][ang][1] = cur_d;
				q.push({dist[u][ang][1], make_tuple(u, ang, 1)});
			}
		}
		for(auto [v, t, a]: g[u]) {
			assert(ref[u][v] != -1);
			if(can_go(ang, a) && cur_d + t < dist[v][ref[u][v]][seen]) {
				dist[v][ref[u][v]][seen] = cur_d + t;
				q.push({dist[v][ref[u][v]][seen], make_tuple(v, ref[u][v], seen)});
			}
		}
	}
	int ans = 1e9;
	for(int i = 0; i < 360; i++) {
		ans = min(ans, dist[0][i][1]);
	}
	if(ans == 1e9) {
		cout << "impossible\n";
	} else {
		cout << ans << '\n';
	}
}