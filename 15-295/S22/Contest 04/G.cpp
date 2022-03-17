#include <bits/stdc++.h>

using namespace std;

int n, a[200000];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    vector<int> v1, v2;
    for(int i = 0; i < n; i++) {
        if(i < n - 1) {
            auto it = upper_bound(v2.begin(), v2.end(), a[i + 1] + 1);
            if(it != v2.end()) {
                *it = a[i + 1] + 1;
            } else {
                v2.push_back(a[i + 1] + 1);
            }
        }
        int ind = upper_bound(v1.begin(), v1.end(), a[i]) - v1.begin();
        if(ind != v1.size()) {
            v1[ind] = a[i];
        } else {
            v1.push_back(a[i]);
        }
        if(ind == v2.size()) {
            v2.push_back(a[i]);
        } else {
            v2[ind] = min(v2[ind], a[i]);
        }
    }
    int ans = max(v1.size(), v2.size()) + 1;
    cout << n - min(n, ans) << endl;
}