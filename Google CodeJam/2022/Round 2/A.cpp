#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

pair<int, int> dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int get_num(int x, int y, int sz) {
    if(x == 0) {
        return y + 1;
    }
    if(y == sz - 1) {
        return sz + x;
    }
    if(x == sz - 1) {
        return 2 * sz - 1 + (sz - y - 1);
    }
    if(y == 0) {
        return 3 * sz - 2 + (sz - x - 1);
    }
    return 4 * (sz - 1) + get_num(x - 1, y - 1, sz - 2);
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k;
        cin >> n >> k;
        cout << "Case #" << _ << ": ";
        if(k < n - 1 || k > n * n - 1 || k % 2 == 1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            vector<pair<int, int>> jumps;
            int cx = 0, cy = 0;
            for(int s = n; s > 0; s -= 2) {
                for(int i = 0; i < 4; i++) {
                    if(k < 2 * (s - 1)) {
                        int go = s - ((2 * (s - 1) - k) / 2) - 1;
                        cx += go * dir[i].f, cy += go * dir[i].s;
                        for(int j = 0; j < 2; j++) {
                            i = (i + 1) % 4;
                            if(cx == n / 2 && cy == n / 2) {
                                break;
                            }
                            while(true) {
                                int n1 = get_num(cx, cy, n), n2 = get_num(cx + dir[i].f, cy + dir[i].s, n);
                                if(n2 != n1 + 1) {
                                    jumps.push_back({n1, n2});
                                }
                                cx += dir[i].f, cy += dir[i].s;
                                if(dir[i].f != 0 && cx == n / 2) {
                                    break;
                                }
                                if(dir[i].s != 0 && cy == n / 2) {
                                    break;
                                }
                            }
                        }
                        s = -1;
                        break;
                    } else {
                        k -= (s - 1);
                    }
                    cx += dir[i].f * (s - 1), cy += dir[i].s * (s - 1);
                }
                ++cx, ++cy;
            }
            --cx, --cy;
            assert(cx == n / 2 && cy == n / 2);
            cout << jumps.size() << endl;
            for(pair<int, int> j: jumps) {
                cout << j.f << " " << j.s << endl;
            }
        }
    }
}
