#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int t, h, s, k, l[90000], ans[90001];
string p[300];

int main() {
    ifstream cin("grading_input.txt");
    ofstream cout("output.txt");
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> h >> s >> k;
        for(int i = 0; i < h; i++) {
            cin >> p[i];
        }
        for(int i = 0; i < k; i++) {
            cin >> l[i];
        }
        vector<vector<int>> tot(h + 1, vector<int>(2, 0));
        for(int i = 0; i < s; i++) {
            vector<pair<bool, int>> streaks;
            for(int j = 0, st = 1; j < h; j++, st++) {
                if(j == h - 1 || p[j][i] != p[j + 1][i]) {
                    streaks.push_back({p[j][i] == 'B', st});
                    st = 0;
                }
            }
            int sz = streaks.size();
            vector<vector<int>> dp1(sz + 1, vector<int>(sz + 1, INF)), dp2(sz + 1, vector<int>(sz + 1, INF));
            dp1[0][0] = dp2[0][0] = 0;
            for(int pf = 0; pf < sz; pf++) {
                dp1[pf + 1][0] = dp2[pf + 1][0] = dp1[pf][0] + streaks[pf].s;
                for(int bl = 1; bl <= pf + 1; bl++) {
                    if(streaks[pf].f) {
                        dp1[pf + 1][bl] = min(dp1[pf][bl], dp2[pf][bl - 1]); 
                        dp2[pf + 1][bl] = dp2[pf][bl] + streaks[pf].s;
                    } else {
                        dp2[pf + 1][bl] = min(dp2[pf][bl], dp1[pf][bl - 1]);
                        dp1[pf + 1][bl] = dp1[pf][bl] + streaks[pf].s;
                    }
                }
            }
            for(int i = 1; i <= sz; i++) {
                dp1[sz][i] = min({dp1[sz][i], dp1[sz][i - 1], dp2[sz][i - 1]});
                dp2[sz][i] = min({dp2[sz][i], dp1[sz][i - 1], dp2[sz][i - 1]});
            }
            for(int i = 0; i <= sz; i++) {
                tot[i][0] += dp1[sz][i];
                tot[i][1] += dp2[sz][i];
            }
        }
        for(int i = 0, j = h + 1; i <= h * s; i++) {
            while(j > 0 && min(tot[j - 1][0], tot[j - 1][1]) <= i) {
                --j;
            }
            ans[i] = j;
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < k; i++) {
            cout << ans[l[i]] << " ";
        }
        cout << endl;
    }
}