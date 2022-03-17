#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 2e9;

int n, m, a[500002], b[500000], p[500002], dp[500002];
pair<int, int> ord[500002];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    a[0] = -INF, a[n + 1] = INF;
    for(int i = 0; i < n; i++) {
        cin >> a[i + 1];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(b, b + m);
    n += 2;
    for(int i = 0; i < n; i++) {
        ord[i] = {a[i], i};
    }
    sort(ord, ord + n);
    for(int i = 0, j = 0; i < n; i++) {
        while(j < m && b[j] <= ord[i].f) {
            ++j;
        }
        p[ord[i].s] = j;
    }
    set<pair<int, int>> bst;
    for(int i = 1; i < n; i++) {
        dp[i] = -INF;
        if(a[i] > a[i - 1]) {
            dp[i] = dp[i - 1] + 1;
        }
        auto it = bst.lower_bound({p[i] - i + 2, -1});
        if(it != bst.begin()) {
            --it;
            dp[i] = max(dp[i], it->s + 1);
        }
        pair<int, int> cur = {p[i - 1] - (i - 1), -1};
        it = bst.upper_bound(cur);
        while(it != bst.end()) {
            if(it->s > dp[i - 1]) {
                break;
            }
            bst.erase(it);
            it = bst.upper_bound(cur);
        }
        it = bst.upper_bound({p[i - 1] - i, -1});
        if(it != bst.begin()) {
            --it;
            if(it->s < dp[i - 1]) {
                bst.insert({p[i - 1] - (i - 1), dp[i - 1]});
            }
        } else {
            bst.insert({p[i - 1] - (i - 1), dp[i - 1]});
        }
    }
    dp[n - 1] = n - dp[n - 1] - 1;
    cout << (dp[n - 1] <= m ? dp[n - 1] : -1) << '\n';
}