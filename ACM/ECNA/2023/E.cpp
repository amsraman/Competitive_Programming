#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t ll128;

using namespace std;

const ll128 mx = (1LL << 48);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	string s; cin >> s; reverse(s.begin(), s.end());
	bool ill_formed = false;
	for(char c: s) {
		if(c != 'O' && c != 'E') {
			ill_formed = true;
		}
	}
	if(ill_formed) {
		cout << "INVALID\n";
		return 0;
	}
	ll128 p2 = 2, ans = mx;
	set<ll128> p2s; ll128 cur = 1;
	for(int i = 0; i <= 120; i++) {
		p2s.insert(cur); cur *= 2;
	}
	auto try_p2 = [&](ll128 p2) {
		for(char c: s) {
			if(c == 'E') {
				p2 *= 2;
			} else {
				if(p2 % 3 != 1) return;
				p2 = (p2 - 1) / 3;
				if(p2 % 2 != 1) return;
			}
			if(p2s.count(p2)) return;
		}
		ans = min(ans, p2);
	};
	for(int i = 0; i < 71; i++) {
		try_p2(p2);
		p2 *= 2;
	}
	if(ans == mx) {
		cout << "INVALID\n";
	} else {
		cout << (ll) ans << '\n';
	}
}
/*
Mistakes:
- Apparently the input is allowed to be ill-formed
- Overflow :(
*/