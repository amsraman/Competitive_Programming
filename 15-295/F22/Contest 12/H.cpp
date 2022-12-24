#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k, m; cin >> n >> k >> m; --k;
    vector<int> pts(n);
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    for(int i = 0, a, pa, b, pb; i < m; i++) {
        cin >> a >> pa >> b >> pb;
        pts[a - 1] += pa, pts[b - 1] += pb;
        vis[a - 1][b - 1] = vis[b - 1][a - 1] = true;
    }
    vector<pair<int, int>> matches;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(!vis[i][j]) {
                if(i == k) {
                    pts[i] += 3;
                } else if(j == k) {
                    pts[j] += 3;
                } else {
                    matches.push_back({i, j});
                }
            }
        }
    }
    int pw3 = 1;
    for(int i = 0; i < matches.size(); i++) pw3 *= 3;
    bool ans = false;
    for(int i = 0; i < pw3; i++) {
        int tp = i;
        for(auto [x, y]: matches) {
            if(tp % 3 == 0) {
                pts[x] += 3;
            } else if(tp % 3 == 1) {
                pts[x] += 1, pts[y] += 1;
            } else {
                pts[y] += 3;
            }
            tp /= 3;
        }
        bool good = true;
        for(int i = 0; i < n; i++) {
            if(i != k && pts[i] >= pts[k]) good = false;
        }
        ans |= good, tp = i;
        for(auto [x, y]: matches) {
            if(tp % 3 == 0) {
                pts[x] -= 3;
            } else if(tp % 3 == 1) {
                pts[x] -= 1, pts[y] -= 1;
            } else {
                pts[y] -= 3;
            }
            tp /= 3;
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
}