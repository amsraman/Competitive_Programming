#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    cin >> n;
    long long cur = 1, ans = 0;
    for(int i = 0; i < n; i++) {
        cur *= 2;
        ans += cur;
    }
    cout << ans << endl;
}