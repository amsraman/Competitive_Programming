#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("consecutive_cuts_chapter_2_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k;
        cin >> n >> k;
        vector<int> a(2 * n), b(n), kmp(n, 0);
        bool same = true, cyclic_shift = false, ans;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            a[i + n] = a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            same &= (a[i] == b[i]);
        }
        for(int i = 1; i < n; i++) {
            kmp[i] = kmp[i - 1];
            while(kmp[i] > 0 && b[i] != b[kmp[i]]) {
                kmp[i] = kmp[kmp[i] - 1];
            }
            kmp[i] += (b[i] == b[kmp[i]]);
        }
        for(int i = 1, j = 0; i < 2 * n; i++) {
            if(a[i] == b[j]) {
                ++j;
            } else if(j > 0) {
                j = kmp[j - 1], --i;
            }
            if(j == n) {
                cyclic_shift = (i != 2 * n - 1);
                break;
            }
        }
        if(n == 2) {
            if(k & 1 ^ 1) {
                ans = same;
            } else {
                ans = cyclic_shift;
            }
        } else {
            if(k == 0) {
                ans = same;
            } else if(k == 1) {
                ans = cyclic_shift;
            } else {
                ans = (same || cyclic_shift);
            }
        }
        cout << "Case #" << _ << ": " << (ans ? "YES" : "NO") << endl;
    }
}