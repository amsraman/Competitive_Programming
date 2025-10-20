#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("cheeseburger_corollary_1_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int s, d, k; cin >> s >> d >> k;
        bool res = (2 * (s + d) >= k + 1) && (s + 2 * d >= k);
        cout << "Case #" << _ << ": " << (res ? "YES" : "NO") << '\n';
    }
}