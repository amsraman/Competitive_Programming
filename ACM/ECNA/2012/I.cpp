#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld eps = 1e-14;

int main() {
	int t; cin >> t;
	for(int _ = 1; _ <= t; _++) {
		vector<pair<int, int>> pts;
		for(int i = 0; i < 4; i++) {
			int x, y; cin >> x >> y; pts.emplace_back(x, y);
		}
		sort(pts.begin(), pts.end());
		ld ans = -1;
		auto in_interval = [](ld lb, ld ub, ld x) {
			if(lb > ub) swap(lb, ub);
			return x > lb + eps && x + eps < ub;
		};
		do {
			auto [x1, y1] = pts[0];
			auto [x2, y2] = pts[1];
			auto [x3, y3] = pts[2];
			auto [x4, y4] = pts[3];
			ld ang = atan2l(x4 - x3 - y2 + y1, x2 - x1 - y3 + y4);
			if(x4 - x3 - y2 + y1 == 0 && x2 - x1 - y3 + y4 == 0) {
				ang = atan2l(x2 - x1, y2 - y1);
			}
			ld mn_y = sin(ang) * x1 + cos(ang) * y1, mx_y = sin(ang) * x2 + cos(ang) * y2;
			ld mn_x = cos(ang) * x3 - sin(ang) * y3, mx_x = cos(ang) * x4 - sin(ang) * y4;
			if(!in_interval(mn_y, mx_y, sin(ang) * x3 + cos(ang) * y3) || !in_interval(mn_y, mx_y, sin(ang) * x4 + cos(ang) * y4)) continue;
			if(!in_interval(mn_x, mx_x, cos(ang) * x1 - sin(ang) * y1) || !in_interval(mn_x, mx_x, cos(ang) * x2 - sin(ang) * y2)) continue;
			ans = max(ans, abs(mx_y - mn_y) + 10);
		} while(next_permutation(pts.begin(), pts.end()));
		cout << "Case " << _ << ": ";
		if(ans == -1) {
			cout << "no solution\n";
		} else {
			cout << fixed << setprecision(2) << ans << '\n';
		}
	}
}