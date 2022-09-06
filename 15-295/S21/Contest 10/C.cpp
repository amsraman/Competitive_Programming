#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[1000000], nimber;
map<pair<int, ll>, int> grundy;

int solve_grundy(int num, ll msk) {
    if(grundy.count({num, msk})) {
        return grundy[{num, msk}];
    }
    set<int> nxt;
    for(ll i = 1; i <= num; i++) {
        if(!((msk >> (i - 1)) & 1)) {
            ll new_msk = msk ^ (2 * i <= num ? (1LL << (i - 1)) : 0);
            nxt.insert(solve_grundy(num - i, new_msk));
        }
    }
    int ans = 0;
    while(nxt.count(ans)) {
        ++ans;
    }
    return grundy[{num, msk}] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    grundy[{0, 0}] = 0;
    for(int i = 1; i <= 60; i++) {
        solve_grundy(i, 0);
    }
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        nimber ^= grundy[{a[i], 0}];
    }
    cout << (nimber == 0 ? "YES\n" : "NO\n");
}