#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, n, k, cost[26][26];
string s;

int main() {
    freopen("consistency_chapter_2_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> s >> k;
        n = s.length();
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j++) {
                cost[i][j] = INF;
            }
            cost[i][i] = 0;
        }
        for(int i = 0; i < k; i++) {
            string rep;
            cin >> rep;
            cost[(rep[0] - 'A')][(rep[1] - 'A')] = 1;
        }
        for(int z = 0; z < 26; z++) {
            for(int x = 0; x < 26; x++) {
                for(int y = 0; y < 26; y++) {
                    cost[x][y] = min(cost[x][y], cost[x][z] + cost[z][y]);
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < 26; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                cnt = min(INF, cnt + cost[(s[j] - 'A')][i]);
            }
            ans = min(ans, cnt);
        }
        cout << "Case #" << _ << ": " << (ans == INF ? -1 : ans) << endl;
    }
}