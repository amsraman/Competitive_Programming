#include <bits/stdc++.h> // goofy problem

using namespace std;

int main() {
    ifstream cin("line_of_delivery_part_2_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, g; cin >> n >> g;
        vector<int> e(n);
        for(int i = 0; i < n; i++) {
            cin >> e[i];
        }
        vector<int> coords;
        for(int i = 0; i < n; i++) {
            coords.push_back(e[i] - 1 - (n - i - 1));
        }
        sort(coords.begin(), coords.end());
        for(int i = 0; i < n; i++) {
            coords[i] += i + 1;
        }
        int ans1 = n - 1, ans2 = 1e9;
        for(int i = 0; i < n; i++) ans2 = min(ans2, abs(coords[i] - g));
        while(abs(coords[ans1] - g) != ans2) --ans1;
        cout << "Case #" << _ << ": " << n - ans1 << " " << ans2 << '\n';
    }
}
/*
9 5 7

9 -> 9
5 -> 5

4 8 9
*/