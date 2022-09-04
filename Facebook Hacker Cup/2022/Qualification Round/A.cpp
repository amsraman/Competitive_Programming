#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("second_hands_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k;
        cin >> n >> k;
        vector<int> stl(n), stc(101, 0);
        bool ans = (2 * k >= n);
        for(int i = 0; i < n; i++) {
            cin >> stl[i];
            ++stc[stl[i]];
            if(stc[stl[i]] > 2) {
                ans = false;
            }
        }
        cout << "Case #" << _ << ": " << (ans ? "YES" : "NO") << endl;
    }
}