#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("walk_the_line_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k; cin >> n >> k;
        vector<int> s(n);
        for(int i = 0; i < n; i++) {
            cin >> s[i];
        }
        sort(s.begin(), s.end());
        ll mn = 1LL * (2 * max(2, n) - 3) * s[0];
        cout << "Case #" << _ << ": " << (mn <= k ? "YES" : "NO") << '\n';
    }
}