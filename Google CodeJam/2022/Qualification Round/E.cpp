#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, k;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin >> t;
    while(t--) {
        cin >> n >> k;
        set<int> vv;
        set<pair<int, int>> vs;
        int i1, i2;
        cin >> i1 >> i2;
        vs.insert({i1, i2});
        long double tot1 = 0;
        for(int i = 0; i < k / 200; i++) {
            int cur = uniform_int_distribution<int>(0, n - 1)(rng);
            while(vv.count(cur + 1)) {
                cur = uniform_int_distribution<int>(0, n - 1)(rng);
            }
            vv.insert(cur + 1);
            assert(cur + 1 >= 1 && cur + 1 <= n);
            cout << "T " << cur + 1 << endl;
            int r1, r2;
            cin >> r1 >> r2;
            vs.insert({r1, r2});
            tot1 += r2;
            for(int j = 0; j < 199; j++) {
                cout << "W" << endl;
                cin >> r1 >> r2;
                vv.insert(r1);
                vs.insert({r1, r2});
            }
        }
        long long tot = 0;
        for(pair<int, int> v: vs) {
            tot += v.s;
        }
        long double ans = (tot + (tot1 / (long double) (k / 200)) * (n - vs.size()));
        cout << "E " << (long long) (ans / 2) << endl;
    }
}