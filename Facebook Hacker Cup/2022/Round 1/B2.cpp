#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("watering_well_chapter_2_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, q, ans = 0;
        cin >> n;
        vector<int> tree_x_coords(n), tree_y_coords(n);
        for(int i = 0; i < n; i++) {
            cin >> tree_x_coords[i] >> tree_y_coords[i];
        }
        sort(tree_x_coords.begin(), tree_x_coords.end());
        sort(tree_y_coords.begin(), tree_y_coords.end());
        cin >> q;
        vector<int> x_res(q, 0), y_res(q, 0);
        vector<pair<int, int>> well_x_coords(q), well_y_coords(q);
        for(int i = 0; i < q; i++) {
            cin >> well_x_coords[i].f >> well_y_coords[i].f;
            well_x_coords[i].s = well_y_coords[i].s = i;
        }
        sort(well_x_coords.begin(), well_x_coords.end());
        sort(well_y_coords.begin(), well_y_coords.end());
        auto mul = [](int x, int y) {
            return (1LL * x * y) % mod;
        };
        auto sweep = [&](int sgn) {
            for(int i = 0, j = 0, x_diff = 0, x_tot = 0; i < q; i++) {
                while(j < n && tree_x_coords[j] * sgn <= well_x_coords[i].f * sgn) {
                    int dist = (j > 0 ? tree_x_coords[j] * sgn - tree_x_coords[j - 1] * sgn : 0);
                    x_tot = (x_tot + mul((x_diff + mul(j, dist + 1)) % mod, dist)) % mod;
                    x_diff = (1LL * x_diff + 2LL * mul(j, dist) + mod - 1) % mod;
                    ++j;
                }
                int dist = (j > 0 ? well_x_coords[i].f * sgn - tree_x_coords[j - 1] * sgn : 0);
                int contrib = (x_tot + mul((x_diff + mul(j, dist + 1)) % mod, dist)) % mod;
                x_res[well_x_coords[i].s] = (x_res[well_x_coords[i].s] + contrib) % mod;
            }
            for(int i = 0, j = 0, y_diff = 0, y_tot = 0; i < q; i++) {
                while(j < n && tree_y_coords[j] * sgn <= well_y_coords[i].f * sgn) {
                    int dist = (j > 0 ? tree_y_coords[j] * sgn - tree_y_coords[j - 1] * sgn : 0);
                    y_tot = (y_tot + mul((y_diff + mul(j, dist + 1)) % mod, dist)) % mod;
                    y_diff = (1LL * y_diff + 2LL * mul(j, dist) + mod - 1) % mod;
                    ++j;
                }
                int dist = (j > 0 ? well_y_coords[i].f * sgn - tree_y_coords[j - 1] * sgn : 0);
                int contrib = (y_tot + mul((y_diff + mul(j, dist + 1)) % mod, dist)) % mod;
                y_res[well_y_coords[i].s] = (y_res[well_y_coords[i].s] + contrib) % mod;
            }
        };
        sweep(1);
        reverse(tree_x_coords.begin(), tree_x_coords.end());
        reverse(tree_y_coords.begin(), tree_y_coords.end());
        reverse(well_x_coords.begin(), well_x_coords.end());
        reverse(well_y_coords.begin(), well_y_coords.end());
        sweep(-1);
        for(int i = 0; i < q; i++) {
            ans = (1LL * ans + x_res[i] + y_res[i]) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}