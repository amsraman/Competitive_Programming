#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        cin >> n;
        vector<int> r(n);
        multiset<int> best;
        for(int i = 0; i < n; i++) {
            cin >> r[i];
            best.insert(r[i]);
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < n; i++) {
            best.erase(best.find(r[i]));
            auto it = best.lower_bound(2 * r[i] + 1);
            // lower bound is the first element that is not less than
            if(it == best.begin()) {
                cout << "-1 ";
            } else {
                cout << *(--it) << " ";
            }
            best.insert(r[i]);
        }
        cout << endl;
    }
}