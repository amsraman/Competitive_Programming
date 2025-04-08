#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int k; cin >> k;
	while(k--) {
		string a, s, t; cin >> a >> s >> t;
		int n = (int) s.length(), m = (int) t.length();
		bool pos = false;
		for(int it1 = 0; it1 < 2; it1++) {
			for(int it2 = 0; it2 < 2; it2++) {
				for(int i = 0; i + m <= n; i++) {
					if(s.substr(i, m) == t) {
						pos = true;
					}
				}
				if((int) a.length() == 2 && n <= m && s.front() != s.back()) {
					string beg = s.substr(0, n - 1); sort(beg.begin(), beg.end());
					if(beg.front() == beg.back() && t.substr(m - n + 1, n - 1) == beg) {
						for(int i = 0; i < m - n + 1; i++) {
							if(t[i] == s.back()) {
								pos = true;
							}
						}
					}
				}
				reverse(s.begin(), s.end()); reverse(t.begin(), t.end());
			}
			swap(s, t); swap(n, m);			
		}
		cout << int(pos) << '\n';
	}
}
/*
- If one is a substring of the other, yes (sigma* if s == t, never if count > 1, easy to construct a dfa if count = 1)
- If |alphabet| > 2, no (pigeonhole)
- Otherwise, one can show that the smaller string needs to be of the form (abbbbbb or aaaaaab)
- Consequently, the bigger string needs to be of the form (bbbbbb(something with a) or (something with b)aaaaaa)
- Easy to construct a DFA for such cases.
*/