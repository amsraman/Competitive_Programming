#include <bits/stdc++.h>

using namespace std;

int main() {
	int t; cin >> t;
	while(t--) {
		string s; cin >> s;
		int num_hyph = 0, len = (int) s.length();
		vector<char> non_hyph;
		for(char c: s) {
			if(c == '-') {
				++num_hyph;
			} else {
				non_hyph.push_back(c);
			}
		}
		if(num_hyph > 3 || (num_hyph == 3 && s[len - 2] != '-') || s[0] == '-' || s[len - 1] == '-') {
			cout << "invalid\n";
			continue;
		}
		bool adj_hyph = false;
		for(int i = 0; i + 1 < len; i++) {
			if(s[i] == '-' && s[i + 1] == '-') {
				adj_hyph = true;
			}
		}
		if(adj_hyph) {
			cout << "invalid\n";
			continue;
		}
		int sz = (int) non_hyph.size(); vector<int> dig;
		bool bad_x = false;
		for(int i = 0; i < sz; i++) {
			if(non_hyph[i] == 'X') {
				if(i != sz - 1) {
					bad_x = true;
				}
			} else if(i != sz - 1) {
				dig.push_back(non_hyph[i] - '0');
			}
		}
		int sum = 0, checksum = (non_hyph.back() == 'X' ? 10 : (non_hyph.back() - '0'));
		if((int) dig.size() != 9) {
			cout << "invalid\n";
			continue;
		}
		for(int i = 0; i < 9; i++) {
			sum += (10 - i) * dig[i];
		}
		if(bad_x || ((sum + checksum) % 11 != 0)) {
			cout << "invalid\n";
			continue;
		}
		sum = 9 + 7 * 3 + 8;
		for(int i = 0; i < 9; i++) {
			int mul = (i % 2 == 0 ? 3 : 1);
			sum += mul * dig[i];
		}
		int new_checksum = (10 - sum % 10) % 10;
		string res = s; res[len - 1] = char('0' + new_checksum);
		res = "978-" + res;
		cout << res << '\n';
	}
}