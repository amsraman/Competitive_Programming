#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> h(n);
        for(int i = 0; i < n; i++) {
            cin >> h[i];
        }
        int fro = 0, bck = 0;
        for(int i = 0; i < n - 1; i++) {
            bck += h[i] < h[i + 1];
        }
        for(int i = 0; i < n; i++) {
            cout << max(fro, bck) << " ";
            if(i < n - 1) {
                fro += h[i + 1] < h[i];
                bck -= h[i] < h[i + 1];
            }
        }
        cout << '\n';
    }
}