#include <bits/stdc++.h>

using namespace std;

int t, n, a, b;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> a >> b;
        set<int> nums;
        for(int i = 0; i < n; i++) {
            nums.insert(i + 1);
        }
        vector<int> lhs, rhs;
        lhs.push_back(a), nums.erase(a);
        rhs.push_back(b), nums.erase(b);
        for(int i = b + 1; i <= n; i++) {
            if(nums.count(i)) {
                lhs.push_back(i);
                nums.erase(i);
            }
        }
        for(int i = 1; i < a; i++) {
            if(nums.count(i)) {
                rhs.push_back(i);
                nums.erase(i);
            }
        }
        while(lhs.size() < n / 2 && !nums.empty()) {
            lhs.push_back(*nums.begin());
            nums.erase(nums.begin());
        }
        while(!nums.empty()) {
            rhs.push_back(*nums.begin());
            nums.erase(nums.begin());
        }
        bool ok = true;
        for(int i: lhs) {
            ok &= (i >= a);
        }
        for(int i: rhs) {
            ok &= (i <= b);
        }
        if(lhs.size() == rhs.size() && ok) {
            for(int i: lhs) {
                cout << i << " ";
            }
            for(int i: rhs) {
                cout << i << " ";
            }
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}
