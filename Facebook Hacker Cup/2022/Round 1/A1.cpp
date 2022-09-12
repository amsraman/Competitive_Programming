#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("consecutive_cuts_chapter_1_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _  = 1; _ <= t; _++) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n), nxt1(n), nxt2(n);
        bool same = true, cyclic_shift = true, ans;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for(int i = 0; i < n; i++) {
            same &= (a[i] == b[i]);
            nxt1[a[i] - 1] = a[(i + 1) % n] - 1;
            nxt2[b[i] - 1] = b[(i + 1) % n] - 1;
        }
        for(int i = 0; i < n; i++) {
            cyclic_shift &= (nxt1[i] == nxt2[i]);
        }
        if(n == 2) {
            if(k & 1 ^ 1) {
                ans = same;
            } else {
                ans = (!same && cyclic_shift);
            }
        } else {
            if(k == 0) {
                ans = same;
            } else if(k == 1) {
                ans = (!same && cyclic_shift);
            } else {
                ans = cyclic_shift;
            }
        }
        cout << "Case #" << _ << ": " << (ans ? "YES" : "NO") << endl;
    }
}