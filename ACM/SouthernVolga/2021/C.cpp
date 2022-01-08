#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, k, x, y, f[200000];
char tp[200000];

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> k >> x >> y;
        int tot_a = 0, tot_b = 0;
        vector<ll> av, bv;
        av.push_back(-1e18), bv.push_back(-1e18);
        for(int i = 0; i < n; i++) {
            cin >> tp[i] >> f[i];
            if(tp[i] == 'A') {
                ++tot_a;
                av.push_back(f[i]);
            } else {
                ++tot_b;
                bv.push_back(f[i]);
            }
        }
        sort(av.begin(), av.end());
        sort(bv.begin(), bv.end());
        av[0] = bv[0] = 0;
        for(int i = 1; i <= tot_a; i++) {
            av[i] += av[i - 1];
        }
        for(int i = 1; i <= tot_b; i++) {
            bv[i] += bv[i - 1];
        }
        ll ans = -1e14;
        for(int i = 0, j = 2 * k; i <= 2 * k; i++, j--) {
            if(i <= tot_a && j <= tot_b) {
                ll cur = av[tot_a] + bv[tot_b] - av[tot_a - i] - bv[tot_b - j];
                cur -= max(0LL, (ll) j - k) * y;
                cur -= max(0LL, (ll) i - k) * x;
                ans = max(ans, cur);
            }
        }
        cout << ans << endl;
    }
}
