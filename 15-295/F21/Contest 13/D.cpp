#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, k, fact[200001], ifact[200001], ans;
pair<int, int> segs[200000];
vector<int> bounds, sp, ep;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int ncr(int x, int y) {
    if(x < y) {
        return 0;
    }
    return mul(fact[x], mul(ifact[x - y], ifact[y]));
}

int num_over(vector<int> & vec, int x) {
    int ind = lower_bound(vec.begin(), vec.end(), x) - vec.begin();
    return vec.size() - ind;
}

int num_containing(int x) {
    return num_over(ep, x) - num_over(sp, x + 1);
}

int main() {
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> segs[i].f >> segs[i].s;
        sp.push_back(segs[i].f);
        ep.push_back(segs[i].s);
        bounds.push_back(segs[i].f), bounds.push_back(segs[i].s);
    }
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    sort(sp.begin(), sp.end());
    sort(ep.begin(), ep.end());
    sort(bounds.begin(), bounds.end());
    for(int i = 0; i < 2 * n; i++) {
        if(i < 2 * n - 1 && bounds[i + 1] > bounds[i] + 1) {
            int pos_segs = num_containing(bounds[i] + 1);
            ans = (ans + mul(ncr(pos_segs, k), bounds[i + 1] - bounds[i] - 1)) % mod;
        }
        if(i == 2 * n - 1 || bounds[i] != bounds[i + 1]) {
            int pos_segs = num_containing(bounds[i]);
            ans = (ans + ncr(pos_segs, k)) % mod;
        }
    }
    cout << ans << endl;
}