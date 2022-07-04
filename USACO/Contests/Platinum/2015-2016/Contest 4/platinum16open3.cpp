#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("landscape.in");
    ofstream cout("landscape.out");
    int n, x, y, z;
    ll ladd = 0, radd = 0, ans = 0;
    cin >> n >> x >> y >> z;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    deque<ll> neg, pos;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i]; j++) {
            if(neg.empty()) {
                neg.push_front(-y - ladd);
            }
            ll tp = max(1LL * -y, min(1LL * x, neg.back() + ladd)); neg.pop_back();
            ans -= tp, pos.push_front(tp - radd);
        }
        for(int j = 0; j < b[i]; j++) {
            if(pos.empty()) {
                pos.push_back(x - radd);
            }
            ll tp = max(1LL * -y, min(1LL * x, pos.front() + radd)); pos.pop_front();
            ans += tp, neg.push_back(tp - ladd);
        }
        ladd -= z, radd += z;
    }
    cout << ans << endl;
}