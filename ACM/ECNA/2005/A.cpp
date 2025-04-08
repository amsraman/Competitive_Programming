#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		set<string> bad;
		for(int i = 0; i < n; i++) {
			string s; cin >> s;
			bad.insert(s);
		}
		string abbr; cin >> abbr;
		while(abbr != "LAST") {
			cin.ignore();
			string phr;
			getline(cin, phr);
			vector<string> tokens;
			vector<int> spaces;
			int len = (int) phr.length();
			for(int i = 0; i < len; i++) {
				if(phr[i] == ' ') {
					spaces.push_back(i);
				}
			}
			int lst = -1;
			for(int i = 0; i < (int) spaces.size(); i++) {
				tokens.push_back(phr.substr(lst + 1, spaces[i] - lst - 1));
				lst = spaces[i];
			}
			tokens.push_back(phr.substr(lst + 1, len - lst - 1));
			string tot = "";
			for(int i = 0; i < (int) tokens.size(); i++) {
				if(bad.count(tokens[i])) continue;
				if(!tot.empty()) tot += '|';
				tot += tokens[i];
			}
			int len1 = (int) tot.length(), len2 = (int) abbr.length();
			vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
			dp[0][0] = 1;
			for(int i = 1; i <= len1; i++) {
				for(int j = 1; j <= len2; j++) {
					if(tot[i - 1] != tolower(abbr[j - 1])) continue;
					int bad_ct = 0;
					for(int k = i - 1; k >= 0; k--) {
						if(k == 0 || tot[k - 1] == '|') ++bad_ct;
						if(bad_ct == 2) break;
						dp[i][j] += dp[k][j - 1];
					}
				}
			}
			int res = 0;
			for(int i = len1; i > 0; i--) {
				if(i > 0 && tot[i - 1] == '|') break;
				res += dp[i][len2];
			}
			if(res == 0) {
				cout << abbr << " is not a valid abbreviation\n";
			} else {
				cout << abbr << " can be formed in " << res << " ways\n";
			}
			cin >> abbr;
		}
		cin >> abbr >> n;
	}
}