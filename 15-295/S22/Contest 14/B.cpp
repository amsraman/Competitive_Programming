#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cn(5, 0), cm(5, 0);
    for(int i = 0; i < 5; i++) {
        cn[i] = (n + i) / 5, cm[i] = (m + i) / 5;
    }
    ll ans = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if((i + j) % 5 == 0) {
                ans += 1LL * cn[i] * cm[j];
            }
        }
    }
    cout << ans << endl;
}