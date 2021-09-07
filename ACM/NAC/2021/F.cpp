#include <bits/stdc++.h>

using namespace std;

int n, x[1000000], ans = 1;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for(int i = 1; i < n - 1; i++) {
        if(x[i] > x[i - 1] && x[i] > x[i + 1]) {
            int l = i, r = i;
            while(l > 0 && r < n - 1 && x[l - 1] == x[r + 1] && x[l - 1] < x[l]) {
                --l, ++r;
            }
            ans = max(ans, r - l + 1);
        }
    }
    cout << (ans == 1 ? -1 : ans) << endl;
}