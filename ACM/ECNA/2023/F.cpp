#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

int main() {
	ll x = 1;
	map<ll, int> logs; vector<ll> p2s;
	for(int i = 0; i <= 110; i++) {
		logs[x] = i; p2s.push_back(x);
		x *= 2;
	}
	auto conv = [](string s) -> ll {
		ll res = 0;
		for(char c: s) {
			res = 10 * res + c - '0';
		}
		return res;
	};
	auto print128 = [](ll x) {
		if(x == 0) {
			cout << "0\n";
			return;
		}
		vector<int> dig;
		while(x > 0) {
			dig.push_back(x % 10); x /= 10;
		}
		reverse(dig.begin(), dig.end());
		for(int d: dig) cout << d;
		cout << '\n';
	};
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
		string s; cin >> s;
		a[i] = logs[conv(s)];
	}
	vector<vector<int>> dp(n, vector<int>(150, -1));
	// dp[i][j] = latest endpoint k st k .. i can make 2^j (or -1 if one doesn't exist)
	dp[0][a[0]] = 0;
	for(int i = 1; i < n; i++) {
		dp[i][a[i]] = i; // have it
		for(int j = 0; j < 150; j++) {
			dp[i][j] = max(dp[i][j], dp[i - 1][j]); // take it
			if(j > 0 && dp[i][j - 1] > 0) { // make it
				dp[i][j] = max(dp[i][j], dp[dp[i][j - 1] - 1][j - 1]);
			}
		}
	}
	int res = 0;
	for(int i = 0; i < 150; i++) {
		if(dp[n - 1][i] != -1) res = i;
	}
	print128(p2s[res]);
}