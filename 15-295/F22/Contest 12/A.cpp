#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    int sum = 0, mn = 1e9;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] % 2 == 0) --a[i];
        sum += a[i], mn = min(mn, a[i]);
    }
    cout << (n % 2 == 1 ? sum : sum - mn) << endl;
}