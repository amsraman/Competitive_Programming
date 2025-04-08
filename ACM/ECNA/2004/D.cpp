#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		map<tuple<double, ll, ll>, vector<pair<pair<double, double>, pair<double, double>>>> lines;
		for(int i = 0; i < n; i++) {
			double x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
			int nx1 = 100 * x1 + 0.5, nx2 = 100 * x2 + 0.5, ny1 = 100 * y1 + 0.5, ny2 = 100 * y2 + 0.5;
			ll b = nx2 - nx1;
			ll a = ny1 - ny2;
			ll c = a * nx1 + b * ny1;
			assert(a * nx2 + b * ny2 == c);
			ll g = __gcd(__gcd(abs(a), abs(b)), abs(c));
			a /= g, b /= g, c /= g;
			if(a < 0) a *= -1, b *= -1, c *= -1;
			if(a == 0 && b < 0) b *= -1, c *= -1;
			pair<double, double> p1 = make_pair(x1, y1);
			pair<double, double> p2 = make_pair(x2, y2);
			if(p1 > p2) swap(p1, p2);
			lines[make_tuple(a, b, c)].emplace_back(p1, p2);
		}
		int res = 0;
		for(auto [_, ranges]: lines) {
			sort(ranges.begin(), ranges.end());
			pair<double, double> pv = make_pair(-1e6, -1e6);
			for(auto [l, r]: ranges) {
				if(l > pv) {
					++res;
				}
				pv = max(pv, r);
			}
		}
		cout << res << '\n';
		cin >> n;
	}
}