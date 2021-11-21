#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, p[200000], pos[200000], bit[200001];
ll ans;

int qry(int k) {
    int ret = 0;
    for(k++; k > 0; k -= (k & (-k))) {
        ret += bit[k - 1];
    }
    return ret;
}

void upd(int k) {
    for(k++; k <= n; k += (k & (-k))) {
        ++bit[k - 1];
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        pos[p[i] - 1] = i;
    }
    for(int i = n - 1; i >= 0; i--) {
        ans += qry(pos[i]);
        upd(pos[i]);
    }
    cout << ans << endl;
}