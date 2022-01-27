#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

string n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    set<int> dig;
    for(int i = 0; i < 10; i++) {
        dig.insert(i);
    }
    for(char c: n) {
        if(dig.count(c - '0')) {
            dig.erase(dig.find(c - '0'));
        }
    }
    if(dig.empty()) {
        cout << "Impossible\n";
    } else {
        int lo = *dig.begin(), hi = *(--dig.end()), lc = lo, rc = hi, beg = n[0] - '0', len = n.length();
        for(int d: dig) {
            if(d < beg) {
                lc = d;
            } else {
                rc = min(rc, d);
            }
        }
        string ls = "", hs = "";
        if(lc < beg) {
            ls += char('0' + lc);
        }
        if(rc > beg) {
            hs += char('0' + rc);
        } else if(lo > 0) {
            hs += char('0' + lo);
            hs += char('0' + lo);
        } else {
            if(dig.size() > 0) {
                hs += char('0' + *(++dig.begin()));
            }
            hs += char('0');
        }
        for(int i = 1; i < len; i++) {
            ls += char('0' + hi);
            hs += char('0' + lo);
        }
        ll il = atol(ls.c_str()), ih = atol(hs.c_str()), in = atol(n.c_str());
        if(abs(in - il) < abs(in - ih)) {
            cout << il << '\n';
        } else if(abs(in - il) > abs(in - ih)) {
            cout << ih << '\n';
        } else if(il == ih) {
            cout << il << '\n';
        } else {
            cout << il << " " << ih << '\n';
        }
    }
}