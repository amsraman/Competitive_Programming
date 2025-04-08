#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		vector<string> ranks(n);
		vector<vector<int>> pl(n, vector<int>(5));
		for(int i = 0; i < n; i++) {
			cin >> ranks[i];
			for(int j = 0; j < 5; j++) {
				pl[i][ranks[i][j] - 'A'] = j;
			}
		}
		pair<int, string> res = {1e9, ""};
		string cur = "ABCDE";
		do {
			int score = 0;
			vector<int> cur_pl(5);
			for(int i = 0; i < 5; i++) {
				cur_pl[cur[i] - 'A'] = i;
			}
			for(int i = 0; i < n; i++) {
				for(int a = 0; a < 5; a++) {
					for(int b = a + 1; b < 5; b++) {
						if((cur_pl[a] < cur_pl[b]) != (pl[i][a] < pl[i][b])) {
							++score;
						}
					}
				}
			}
			res = min(res, make_pair(score, cur));
		} while(next_permutation(cur.begin(), cur.end()));
		cout << res.second << " is the median ranking with value " << res.first << ".\n";
		cin >> n;
	}
}