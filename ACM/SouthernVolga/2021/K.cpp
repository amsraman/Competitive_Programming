#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int sq = 300;

int n, a[200000], k[200000], nxt[200000];
ll sum[200000], ps[200001], ans;
pair<int, int> ord[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ord[i] = {-a[i], i};
        ps[i + 1] = a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> k[i];
    }
    for(int i = 1; i <= n; i++) {
        ps[i] += ps[i - 1];
    }
    for(int i = n - 1; i >= 0; i--) {
        nxt[i] = min(n, i / sq * sq + sq);
        sum[i] = ps[nxt[i]] - ps[i];
    }
    ans = ps[n];
    sort(ord, ord + n);
    for(int i = 0; i < n; i++) {
        int sb = ord[i].s / sq * sq, eb = min(n, sb + sq);
        for(int j = ord[i].s; j >= sb; j--) {
            int step = (a[j] < -ord[i].f ? 1 : k[j]), ns = min(n, j + step);
            if(ns < eb) {
                nxt[j] = nxt[ns];
                sum[j] = 1LL * a[j] * step + sum[ns];
            } else {
                nxt[j] = ns;
                sum[j] = 1LL * a[j] * step;
            }
        }
        if(i == n - 1 || ord[i].f != ord[i + 1].f) {
            ll cur = 0;
            for(int j = 0; j < n;) {
                cur += sum[j];
                j = nxt[j];
            }
            ans = max(ans, cur);
        }
    }
    cout << ans << '\n';
}