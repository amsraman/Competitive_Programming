#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("here_comes_santa_claus_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<int> x(n);
        for(int i = 0; i < n; i++) {
            cin >> x[i];
        }
        sort(x.begin(), x.end());
        double ans = (x[n - 2] + x[n - 1]) / 2.0 - (x[1] + x[0]) / 2.0;
        if(n == 5) {
            double pos1 = (x[3] + x[4]) / 2.0 - (x[2] + x[0]) / 2.0;
            double pos2 = (x[2] + x[4]) / 2.0 - (x[1] + x[0]) / 2.0;
            ans = max(pos1, pos2);
        }
        cout << "Case #" << _ << ": " << fixed << setprecision(9) << ans << '\n';
    }
}