#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int main() {
	int n, m, p; cin >> n >> m >> p;
	vector<pair<int, int>> judge, repo, feather;
	for(int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		judge.emplace_back(x, y);
	}
	for(int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		repo.emplace_back(x, y);
	}
	for(int i = 0; i < p; i++) {
		int x, y; cin >> x >> y;
		feather.emplace_back(x, y);
	}
	ld res = 0;
	vector<vector<pair<double, int>>> p1(n), p2(n);
	vector<int> pt1(n, 0), pt2(n, 0);
	auto dist = [](pair<int, int> x, pair<int, int> y) {
		long long dx = y.first - x.first;
		long long dy = y.second - x.second;
		return sqrt(dx * dx + dy * dy);
	};
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			p1[i].emplace_back(dist(judge[i], repo[j]), j);
		}
		for(int j = 0; j < p; j++) {
			p2[i].emplace_back(dist(judge[i], feather[j]), j);
		}
		sort(p1[i].begin(), p1[i].end());
		sort(p2[i].begin(), p2[i].end());
	}
	vector<bool> d1(n, false), d2(m, false), d3(p, false);
	for(int i = 0; i < n; i++) {
		ld best_dist = 1e18; int guy = -1;
		for(int j = 0; j < n; j++) {
			if(d1[j]) continue;
			while(d2[p1[j][pt1[j]].second]) ++pt1[j];
			if(p1[j][pt1[j]].first < best_dist) {
				best_dist = p1[j][pt1[j]].first;
				guy = j;
			}
		}
		d1[guy] = true;
		d2[p1[guy][pt1[guy]].second] = true;
		res += best_dist;
	}
	fill(d1.begin(), d1.end(), false);
	for(int i = 0; i < n; i++) {
		ld best_dist = 1e18; int guy = -1;
		for(int j = 0; j < n; j++) {
			if(d1[j]) continue;
			while(d3[p2[j][pt2[j]].second]) ++pt2[j];
			if(p2[j][pt2[j]].first < best_dist) {
				best_dist = p2[j][pt2[j]].first;
				guy = j;
			}
		}
		d1[guy] = true;
		d3[p2[guy][pt2[guy]].second] = true;
		res += best_dist;
	}
	cout << fixed << setprecision(6) << res << '\n';
}