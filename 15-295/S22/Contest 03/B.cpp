#include <bits/stdc++.h>

using namespace std;

int n, q, x[100000], m[100000];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    sort(x, x + n);
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> m[i];
        int lb = 0, ub = n - 1;
        while(lb < ub) {
            int mid = (lb + ub) / 2;
            if(x[mid] > m[i]) {
                ub = mid;
            } else {
                lb = mid + 1;
            }
        }
        if(x[ub] <= m[i]) {
            ++ub;
        }
        cout << ub << endl;
    }
}