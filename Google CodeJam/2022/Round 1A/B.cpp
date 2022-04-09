#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, b[100], tot;
vector<int> extra;

vector<int> get_set(ll df) {
    // Make sure df is an even number >= 2
    // Returns the *smaller* set 
    df -= 2;
    vector<int> ret;
    for(int i = 0; i < 29; i++) {
        // If this power shifted up by 1 is not in df
        if(!((df >> (i + 1)) & 1)) {
            ret.push_back(1 << i);
        }
    }
    for(int i = 0; i < 69; i++) {
        ret.push_back(extra[i]);
    }
    return ret;
}

int main() {
    for(int i = 0; i < 69; i++) {
        extra.push_back(129 + i);
        tot += (129 + i);
    }
    ++tot;
    extra.push_back(tot);
    for(int i = 0; i < 30; i++) {
        extra.push_back((1 << i));
    }
    cin >> t;
    while(t--) {
        ll sum = 0;
        cin >> n;
        for(int i: extra) {
            cout << i << " ";
            sum += i;
        }
        cout << endl;
        ll bs = 0;
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            sum += b[i];
            bs += b[i];
        }
        sort(b, b + n);
        int pf = -1;
        ll bd = 1e18, rs = 0;
        for(int i = 0; i < n; i++) {
            rs += b[i];
            if(abs(bs - 2 * rs) < abs(bd)) {
                bd = bs - 2 * rs;
                pf = i;
            }
        }
        vector<int> ans, sav = get_set(abs(bd));
        if(bd > 0) {
            for(int i = pf + 1; i < n; i++) {
                ans.push_back(b[i]);
            }
            for(int i: sav) {
                ans.push_back(i);
            }
        } else if(bd < 0) {
            for(int i = 0; i <= pf; i++) {
                ans.push_back(b[i]);
            }
            for(int i: sav) {
                ans.push_back(i);
            }
        } else {
            for(int i = 0; i <= pf; i++) {
                ans.push_back(b[i]);
            }
            for(int i = 0; i < 69; i++) {
                ans.push_back(extra[i]);
            }
            ans.push_back((1 << 29));
        }
        ll cur = 0;
        for(int i: ans) {
            cout << i << " ";
            cur += i;
        }
        cout << endl;
        assert(2 * cur == sum);
    }
}