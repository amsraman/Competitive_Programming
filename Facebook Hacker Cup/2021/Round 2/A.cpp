#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, m, s[1000000], ans;
vector<int> p[1000000];

int main() {
    freopen("runway_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            cin >> s[i];
        }
        for(int i = 0; i < n; i++) {
            p[i].resize(m);
            for(int j = 0; j < m; j++) {
                cin >> p[i][j];
            }
        }
        vector<pair<int, int>> mdls;
        for(int i = 0; i < m; i++) {
            mdls.push_back({s[i], 0});
        }
        sort(mdls.begin(), mdls.end());
        for(int i = 0; i < n; i++) {
            vector<bool> done(m, false);
            vector<pair<int, int>> nxt;
            set<int> cur;
            map<int, int> num;
            for(int j = 0; j < m; j++) {
                cur.insert(p[i][j]);
                ++num[p[i][j]];
            }
            for(int j = m - 1; j >= 0; j--) {
                if(num[mdls[j].f] > 0) {
                    done[j] = true;
                    nxt.push_back(mdls[j]);
                    --num[mdls[j].f];
                    if(num[mdls[j].f] == 0) {
                        cur.erase(cur.find(mdls[j].f));
                    }
                }
            }
            for(int j = 0; j < m; j++) {
                if(!done[j]) {
                    ans += (mdls[j].s == 0 ? 0 : 1);
                    nxt.push_back({*cur.begin(), mdls[j].s + 1});
                    --num[*cur.begin()];
                    if(num[*cur.begin()] == 0) {
                        cur.erase(cur.begin());
                    }
                }
            }
            mdls.clear();
            for(int j = 0; j < m; j++) {
                mdls.push_back(nxt[j]);
            }
            sort(mdls.begin(), mdls.end());
        }
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            p[i].clear();
        }
        ans = 0;
    }
}