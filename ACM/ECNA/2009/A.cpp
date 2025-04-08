#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<int> a(4); cin >> a[0] >> a[1] >> a[2] >> a[3];
	for(int _ = 1; a[0] > 0; _++) {
		sort(a.begin(), a.end());
		vector<int> res;
		auto gen = [&](auto rec, vector<int> left) -> void {
			int sz = (int) left.size();
			if(sz == 1) {
				res.push_back(left[0]);
				return;
			}
			for(int i = 0; i < sz - 1; i++) {
				vector<int> cp;
				cp = left;
				cp[i] = cp[i] + cp[i + 1];
				cp.erase(cp.begin() + i + 1);
				rec(rec, cp);
				cp = left;
				cp[i] = cp[i] - cp[i + 1];
				cp.erase(cp.begin() + i + 1);
				rec(rec, cp);
				cp = left;
				cp[i] = cp[i] * cp[i + 1];
				cp.erase(cp.begin() + i + 1);
				rec(rec, cp);
				cp = left;
				if(cp[i + 1] != 0 && (cp[i] % cp[i + 1] == 0)) {
					cp[i] = cp[i] / cp[i + 1];
					cp.erase(cp.begin() + i + 1);
					rec(rec, cp);
				}
			}
		};
		do {
			gen(gen, a);
		} while(next_permutation(a.begin(), a.end()));
		sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());
		pair<int, int> ans = {1, 0}, cur = {-1e9, -1e9};
		for(int r: res) {
			if(r == cur.second + 1) {
				cur = {cur.first, r};
			} else {
				cur = {r, r};
			}
			if(cur.second - cur.first > ans.second - ans.first) {
				ans = cur;
			} else if(cur.second - cur.first == ans.second - ans.first && cur.first > ans.first) {
				ans = cur;
			}
		}
		cout << "Case " << _ << ": " << ans.first << " to " << ans.second << '\n';
		cin >> a[0] >> a[1] >> a[2] >> a[3];
	}
}