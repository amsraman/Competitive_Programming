#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, a[100000], pre[100001][2];
vector<pair<int, int>> ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1][a[i] - 1] = 1;
    }
    for(int i = 0; i < n; i++) {
        pre[i + 1][0] += pre[i][0];
        pre[i + 1][1] += pre[i][1];
    }
    for(int i = 1; i <= n; i++) {
        int wins[2] = {0, 0}, cur = 0;
        while(cur < n) {
            if(pre[n][0] < pre[cur][0] + i && pre[n][1] < pre[cur][1] + i) {
                break;
            }
            int lb1 = cur + 1, ub1 = n, lb2 = cur + 1, ub2 = n;
            while(lb1 < ub1) {
                int mid = (lb1 + ub1) / 2;
                if(pre[mid][0] >= pre[cur][0] + i) {
                    ub1 = mid;
                } else {
                    lb1 = mid + 1;
                }
            }
            while(lb2 < ub2) {
                int mid = (lb2 + ub2) / 2;
                if(pre[mid][1] >= pre[cur][1] + i) {
                    ub2 = mid;
                } else {
                    lb2 = mid + 1;
                }
            }
            if(ub1 <= ub2 && pre[ub1][0] == pre[cur][0] + i) {
                ++wins[0];
            } else {
                ++wins[1];
            }
            cur = min(ub1, ub2);
        }
        int lst = a[n - 1] - 1;
        if(cur == n && wins[lst] > wins[lst ^ 1]) {
            ans.push_back({wins[lst], i});
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(pair<int, int> a: ans) {
        cout << a.f << " " << a.s << '\n';
    }
}