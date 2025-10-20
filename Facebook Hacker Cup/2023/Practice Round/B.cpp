#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("dim_sum_delivery_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, c, a, b; cin >> r >> c >> a >> b;
        cout << "Case #" << _ << ": " << (r > c ? "YES" : "NO") << '\n';
    }
}