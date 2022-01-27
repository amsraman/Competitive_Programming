#include <bits/stdc++.h>

using namespace std;

int n, m, x, a[2000], b[2000];
vector<pair<int, int>> l1, l2;

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }
    cin >> x;
    for(int i = 0; i < n; i++) {
        int cur = 0;
        for(int j = i; j < n; j++) {
            cur += a[j];
            l1.push_back({cur, j - i + 1});
        }
    }
    for(int i = 0; i < m; i++) {
        int cur = 0;
        for(int j = i; j < m; j++) {
            cur += b[j];
            l2.push_back({cur, j - i + 1});
        }
    }
    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());
    for(int i = 1; i < l2.size(); i++) {
        l2[i].second = max(l2[i].second, l2[i - 1].second);
    }
    int ans = 0;
    for(int i = 0, j = l2.size() - 1; i < l1.size(); i++) {
        while(1LL * l1[i].first * l2[j].first > x) {
            --j;
        }
        if(1LL * l1[i].first * l2[j].first <= x) {
            ans = max(ans, l1[i].second * l2[j].second);
        }
    }
    cout << ans << '\n';
}