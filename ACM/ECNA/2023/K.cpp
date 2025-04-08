#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	vector<string> strs;
	for(int i = 0; i < n; i++) {
		string s; cin >> s; strs.push_back(s);
	}
	int ans = 0;
	map<vector<pair<char, char>>, int> clues;
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			string s1 = strs[i], s2 = strs[j];
			if((int) s1.length() != (int) s2.length()) continue;
			int len = (int) s1.length();
			vector<pair<char, char>> cur_clue; vector<int> bad_inds;
			bool sw = false;
			for(int k = 0; k < len; k++) {
				if(s1[k] != s2[k]) {
					if(bad_inds.empty() && s1[k] > s2[k]) {
						sw = true;
					}
					if(sw) {
						cur_clue.emplace_back(s2[k], s1[k]);
					} else {
						cur_clue.emplace_back(s1[k], s2[k]);
					}
					bad_inds.push_back(k);
				} else {
					cur_clue.emplace_back('-', '-');
				}
			}
			if((int) bad_inds.size() == 2 && bad_inds[0] + 1 == bad_inds[1]) {
				++clues[cur_clue];
			}
		}
	}
	for(auto [k, v]: clues) {
		if(v == 1) ++ans;
	}
	cout << ans << '\n';
}
/*
Mistakes:
- Not reading the problem (dude just read the fucking last paragraph what are you doing lmao)
- Overcounting
- Fucking typo (why am I having a literal aneurysm rn)
*/