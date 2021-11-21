#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, d, n, k;
array<int, 3> att[300000];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> d >> n >> k;
        vector<array<int, 4>> ev;
        for(int i = 0; i < n; i++) {
            cin >> att[i][0] >> att[i][1] >> att[i][2];
            ev.push_back({att[i][1] - 1, att[i][0], 1, i});
            ev.push_back({att[i][2], att[i][0], -1, i});
        }
        sort(ev.begin(), ev.end());
        set<pair<int, int>> bst, bck;
        ll cur = 0, ans = 0;
        for(int i = 0, j = 0; i < d; i++) {
            while(j < ev.size() && ev[j][0] <= i) {
                if(ev[j][2] == 1) {
                    bst.insert({-ev[j][1], ev[j][3]});
                    cur += ev[j][1];
                    if(bst.size() > k) {
                        pair<int, int> lst = *(--bst.end());
                        cur += lst.f;
                        bst.erase(bst.find(lst));
                        bck.insert(lst);
                    }
                } else {
                    if(bst.count({-ev[j][1], ev[j][3]})) {
                        bst.erase(bst.find({-ev[j][1], ev[j][3]}));
                        cur -= ev[j][1];
                    } else {
                        bck.erase(bck.find({-ev[j][1], ev[j][3]}));
                    }
                    if(bst.size() < k && !bck.empty()) {
                        pair<int, int> lst = *(bck.begin());
                        bck.erase(bck.find(lst));
                        cur -= lst.f;
                        bst.insert(lst);
                    }
                }
                ++j;
            }
            ans = max(ans, cur);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}