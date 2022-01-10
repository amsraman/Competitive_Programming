#include <bits/stdc++.h>

using namespace std;

int n, p, q, s, classical[200000], creative[200000];

bool works(int x, int y, int rad) {
    return (abs(x - y) <= rad && x + y <= s);
}

bool ok(int x) {
    int tot = 0;
    multiset<int> ms;
    for(int i = 0; i < q; i++) {
        ms.insert(creative[i]);
    }
    for(int i = p - 1; i >= 0; i--) {
        int targ = min(s - classical[i], classical[i] + x);
        auto it = ms.upper_bound(targ);
        if(it != ms.begin()) {
            --it;
            if(works(classical[i], *it, x)) {
                ms.erase(it);
                ++tot;
                if(tot == n) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> p >> q >> s;
    for(int i = 0; i < p; i++) {
        cin >> classical[i];
    }
    for(int i = 0; i < q; i++) {
        cin >> creative[i];
    }
    sort(classical, classical + p);
    int lb = 0, ub = 1e9;
    while(lb < ub) {
        int mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << (ok(ub) ? ub : -1) << endl;
}