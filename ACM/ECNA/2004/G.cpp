#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		string s; cin >> s;
		int m = (int) s.length() / n;
		vector<vector<char>> ar(m, vector<char>(n));
		assert((int) s.length() == n * m);
		for(int i = 0; i < n * m; i++) {
			int row = i / n, col = i % n;
			ar[row][col] = s[i];
		}
		for(int i = 1; i < m; i += 2) {
			reverse(ar[i].begin(), ar[i].end());
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				cout << ar[j][i];
			}
		}
		cout << '\n';
		cin >> n;
	}
}