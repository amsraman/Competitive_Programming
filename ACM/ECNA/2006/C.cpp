#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k; cin >> n >> k;
    for(int _ = 1; n > 0; _++) {
        vector<string> stud(n);
        for(int i = 0; i < n; i++) {
            cin >> stud[i];
        }
        sort(stud.begin(), stud.end(), [](auto x, auto y) {
            return (int) x.length() < (int) y.length();
        });
        bool res = true;
        for(int i = 0; i < n; i += k) {
            int tot = 0;
            for(int j = 0; j < k; j++) {
                tot += (int) stud[i + j].length();
            }
            for(int j = 0; j < k; j++) {
                int sz = (int) stud[i + j].length();
                if(k * sz < tot - k * 2 || k * sz > tot + k * 2) {
                    res = false;
                }
            }
        }
        cout << "Case " << _ << ": " << (res ? "yes" : "no") << '\n';
        cin >> n >> k;
    }
}