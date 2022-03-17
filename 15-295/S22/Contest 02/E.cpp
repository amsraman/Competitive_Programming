#include <bits/stdc++.h>

using namespace std;

int n, q, a[1000000], k[1000000];

bool ok(int x) {
    array<int, 2> num = {0, 0};
    for(int i = 0; i < n; i++) {
        if(a[i] <= x) {
            ++num[0];
        } else {
            ++num[1];
        }
    }
    for(int i = 0; i < q; i++) {
        if(k[i] >= 1) {
            if(k[i] <= x) {
                ++num[0];
            } else {
                ++num[1];
            }
        } else {
            if(-k[i] <= num[0]) {
                --num[0];
            } else {
                --num[1];
            }
        }
    }
    return (num[0] > 0 || num[1] == 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < q; i++) {
        cin >> k[i];
    }
    int lb = 0, ub = n;
    while(lb < ub) {
        int mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << ub << '\n';
}