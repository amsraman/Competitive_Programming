#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        cin >> n;
        vector<int> p(n);
        for(int i = 0; i < n; i++) {
            cin >> p[i];
            --p[i];
        }
        vector<int> cycs;
        vector<bool> vis(n, false);
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                int len = 0, cur = i;
                while(!vis[cur]) {
                    ++len, vis[cur] = true, cur = p[cur];
                }
                cycs.push_back(len);
            }
        }
        sort(cycs.begin(), cycs.end());
        vector<pair<int, int>> cond;
        for(int i = 0, j = 0; i < cycs.size(); i++) {
            ++j;
            if(i == cycs.size() - 1 || cycs[i + 1] != cycs[i]) {
                cond.push_back({cycs[i], j});
                j = 0;
            }
        }
        vector<int> best(n + 1, 0x3f3f3f3f);
        best[0] = 0;
        for(pair<int, int> cyc: cond) {
            int len = cyc.first, num = cyc.second;
            vector<deque<pair<int, int>>> st(len);
            st[0].push_back({0, 0});
            for(int i = 1; i <= n; i++) {
                int md = i % len;
                if(!st[md].empty() && st[md].front().first < (i / len) - num) {
                    st[md].pop_front();
                }
                while(!st[md].empty() && best[i] < st[md].back().second + (i / len) - st[md].back().first) {
                    st[md].pop_back();
                }
                st[md].push_back({i / len, best[i]});
                best[i] = min(best[i], st[md].front().second + (i / len) - st[md].front().first);
            }
        }
        vector<int> ans(n);
        int mx = cycs.back();
        for(int i = 1, j = cycs.size(), cur = 0; i <= n; i++) {
            while(cur < i) {
                --j, cur += cycs[j];
            }
            ans[i - 1] = cycs.size() - j;
        } // greedy, want to counter with best case exact set
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < n; i++) {
            cout << min(ans[i], best[i + 1] - 1) << " ";
        }
        cout << endl;
    }
}