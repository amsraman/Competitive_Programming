#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		vector<tuple<int, int, ld>> dig;
		vector<int> init;
		for(int i = 0; i < n; i++) {
			int m, l; ld p; cin >> m >> l >> p;
			dig.emplace_back(m, l, p);
			init.push_back(l);
		}
		map<pair<int, vector<int>>, ld> dp;
		vector<int> done(n, -1);
		auto gen = [&](auto rec, int lev, vector<int> state) -> ld {
			if(dp.count({lev, state})) return dp[{lev, state}];
			if(state == done) return dp[{lev, state}] = 1.0;
			ld res = 0;
			for(int i = 0; i < 1 << n; i++) { // case on what move we make
				bool viable = true;
				vector<int> mod_state = state;
				for(int j = 0; j < n; j++) {
					if(state[j] == -1) {
						if((i >> j) & 1) viable = false;
						continue;
					}
					auto [tot, _, prob] = dig[j];
					if((i >> j) & 1) { // we use a known
						if(state[j] == 0) viable = false;
						--mod_state[j];
					} else { // we use an unknown
						if(tot - lev - state[j] == 0) viable = false;
					}
				}
				if(!viable) continue;
				ld tot = 0;
				for(int j = 1; j < 1 << n; j++) { // case on which subset we get right
					// find the probability that we get this subset right
					// find the downstream probability
					ld right = 1; int progress = 0;
					vector<int> new_state = mod_state;
					for(int k = 0; k < n; k++) {
						auto [tot, known, prob] = dig[k];
						ld cur_right, tot_prob = 0; // prob / known * state[k] + (1 - prob) / (tot - known) * (tot - lev - state[k]);
						if(known > 0) {
							tot_prob += prob / known * state[k];
						}
						if(tot - known > 0) {
							tot_prob += (1.0 - prob) / (tot - known) * (tot - lev - state[k]);
						}
						if(state[k] == -1) {
							cur_right = 1;
						} else if((i >> k) & 1) {
							cur_right = prob / known / tot_prob;
						} else {
							cur_right = (1 - prob) / (tot - known) / tot_prob;
						}
						if((j >> k) & 1) { // we got it right
							right *= cur_right;
							new_state[k] = -1;
							if(state[k] != -1) ++progress;
						} else { // we got it wrong
							right *= (1.0 - cur_right);
						}
					}
					if(progress > 0 && right > 0) {
						tot += right * rec(rec, lev + 1, new_state);
					}
				}
				res = max(res, tot);
			}
			return dp[{lev, state}] = res;
		};
		ld ans = gen(gen, 0, init);
		ans = (ld) round(ans * 1000) / 1000.0;
		cout << ans << '\n';
		cin >> n;
	}
}