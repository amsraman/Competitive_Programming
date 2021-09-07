#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, msk[200000], ans;
ll k;
string resp[200000];

int conv(string s) {
    int ret = 0;
    for(int i = 0; i < m; i++) {
        ret = 2 * ret + (s[i] == 'B');
    }
    return ret;
}

void fwht(vector<ll> & a, bool inv) {
    int sz = a.size();
    for(int i = 1, j = 0; i < sz; i++) {
        int bit = sz >> 1;
        for(; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 1; len < sz; len <<= 1) {
        for(int i = 0; i < sz; i += 2 * len) {
            for(int j = i; j < i + len; j++) {
                ll x = a[j], y = a[j + len];
                a[j] = x + y;
                a[j + len] = x - y;
            }
        }
    }
    if(inv) {
        for(int i = 0; i < sz; i++) {
            a[i] /= (1 << m);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    vector<ll> p1((1 << m), 0), p2((1 << m), 0), fin((1 << m), 0), dif((1 << m), 0);
    for(int i = 0; i < n; i++) {
        cin >> resp[i];
        msk[i] = conv(resp[i]);
        ++p1[msk[i]], ++p2[msk[i]];
    }
    fwht(p1, false);
    fwht(p2, false);
    for(int i = 0; i < (1 << m); i++) {
        p1[i] *= p2[i];
    }
    fwht(p1, true);
    ll tot = 0;
    for(int i = 0; i < (1 << m); i++) {
        p1[i] /= 2;
        tot += p1[i];
        dif[i] = p1[i];
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < (1 << m); j++) {
            if(j & (1 << i)) {
                dif[j] += dif[(j ^ (1 << i))];
            }
        }
    }
    for(int i = 1; i < (1 << m); i++) {
        fin[i] = tot - dif[(((1 << m) - 1) ^ i)];
        if(fin[i] >= k) {
            ++ans;
        }
    }
    cout << ans << '\n';
}