#include <bits/stdc++.h>

using namespace std;

int n, a[100];

int main() {
    cin >> n;
    int np = 0, nn = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] > 0) {
            ++np;
        } else if(a[i] < 0) {
            ++nn;
        }
    }
    if(2 * np >= n) {
        cout << 1 << endl;
    } else if(2 * nn >= n) {
        cout << -1 << endl;
    } else {
        cout << 0 << endl;
    }
}