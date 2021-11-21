#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, dp[40][40][40][40], ans;
pair<int, int> points[40];

int cross(pair<int, int> p1, pair<int, int> p2) {
    return p1.f * p2.s - p1.s * p2.f;
}

int side(pair<int, int> p1, pair<int, int> p2, pair<int, int> q) {
    return cross({q.f - p1.f, q.s - p1.s}, {p2.f - q.f, p2.s - q.s});
}

bool in_triangle(int p1, int p2, int p3, int p4) {
    bool sd1 = side(points[p1], points[p2], points[p4]) > 0;
    bool sd2 = side(points[p1], points[p2], points[p3]) > 0;
    if(sd1 ^ sd2) {
        return false;
    }
    sd1 = side(points[p2], points[p3], points[p4]) > 0;
    sd2 = side(points[p2], points[p3], points[p1]) > 0;
    if(sd1 ^ sd2) {
        return false;
    }
    sd1 = side(points[p1], points[p3], points[p4]) > 0;
    sd2 = side(points[p1], points[p3], points[p2]) > 0;
    if(sd1 ^ sd2) {
        return false;
    }
    return true;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                dp[2][i][j][k] = 6;
            }
        }
    }
    for(int i = 2; i < n - 1; i++) {
        for(int p1 = 0; p1 < n; p1++) {
            for(int p2 = p1 + 1; p2 < n; p2++) {
                for(int p3 = p2 + 1; p3 < n; p3++) {
                    int in_points = 0;
                    for(int p4 = 0; p4 < n; p4++) {
                        if(p4 != p1 && p4 != p2 && p4 != p3) {
                            if(in_triangle(p1, p2, p3, p4)) {
                                ++in_points;
                            } else if(in_triangle(p1, p2, p4, p3)) {
                                array<int, 3> ord = {p1, p2, p4};
                                sort(ord.begin(), ord.end());
                                dp[i + 1][ord[0]][ord[1]][ord[2]] = (dp[i + 1][ord[0]][ord[1]][ord[2]] + dp[i][p1][p2][p3]) % mod;
                            } else if(in_triangle(p1, p3, p4, p2)) {
                                array<int, 3> ord = {p1, p3, p4};
                                sort(ord.begin(), ord.end());
                                dp[i + 1][ord[0]][ord[1]][ord[2]] = (dp[i + 1][ord[0]][ord[1]][ord[2]] + dp[i][p1][p2][p3]) % mod;
                            } else if(in_triangle(p2, p3, p4, p1)) {
                                array<int, 3> ord = {p2, p3, p4};
                                sort(ord.begin(), ord.end());
                                dp[i + 1][ord[0]][ord[1]][ord[2]] = (dp[i + 1][ord[0]][ord[1]][ord[2]] + dp[i][p1][p2][p3]) % mod;
                            }
                        }
                    }
                    dp[i + 1][p1][p2][p3] = (dp[i + 1][p1][p2][p3] + (1LL * (in_points - i + 2) * dp[i][p1][p2][p3]) % mod) % mod;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                ans = (ans + dp[n - 1][i][j][k]) % mod;
            }
        }
    }
    cout << ans << endl;
}