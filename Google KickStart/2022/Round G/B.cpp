#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m, rs, rh, mn_red = INT_MAX, mn_yellow = INT_MAX;
        cin >> rs >> rh >> n;
        rh += rs;
        vector<pair<int, int>> red(n);
        for(int i = 0; i < n; i++) {
            cin >> red[i].f >> red[i].s;
            mn_red = min(mn_red, red[i].f * red[i].f + red[i].s * red[i].s);
        }
        cin >> m;
        vector<pair<int, int>> yellow(m);
        for(int i = 0; i < m; i++) {
            cin >> yellow[i].f >> yellow[i].s;
            mn_yellow = min(mn_yellow, yellow[i].f * yellow[i].f + yellow[i].s * yellow[i].s);
        }
        int red_score = 0, yellow_score = 0;
        for(int i = 0; i < n; i++) {
            int dist = red[i].f * red[i].f + red[i].s * red[i].s;
            if(dist <= rh * rh && dist < mn_yellow) {
                ++red_score;
            }
        }
        for(int i = 0; i < m; i++) {
            int dist = yellow[i].f * yellow[i].f + yellow[i].s * yellow[i].s;
            if(dist <= rh * rh && dist < mn_red) {
                ++yellow_score;
            }
        }
        cout << "Case #" << _ << ": " << red_score << " " << yellow_score << endl;
    }
}