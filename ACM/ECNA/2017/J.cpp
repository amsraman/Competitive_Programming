#include <bits/stdc++.h>

using namespace std;

int u[10], r[10], o[10], ans;
array<int, 3> p[10]; 

int main() {
    for(int i = 0; i < 10; i++) {
        cin >> u[i] >> r[i];
    }
    for(int i = 0; i < 10; i++) {
        cin >> p[i][0] >> p[i][1] >> p[i][2];
    }
    for(int rot = 0; rot < 3; rot++) {
        for(int i = 0; i < 10; i++) {
            if(ans < p[i][2]) {
                ans += u[i];
                p[i][2] = max(p[i][2], ans);
                ans += r[i];
            } else {
                int iter = (ans - p[i][2]) / (p[i][0] + p[i][1]), ep = (iter + 1) * (p[i][0] + p[i][1]) + p[i][2];
                if(ans >= iter * (p[i][0] + p[i][1]) + p[i][0] + p[i][2]) {
                    p[i][2] += max(0, ans + u[i] - ep);
                    ans += u[i] + r[i];
                } else {
                    int time_left = p[i][0] - (ans - iter * (p[i][0] + p[i][1]) - p[i][2]);
                    p[i][2] += max(0, ans + time_left + u[i] - ep);
                    ans += time_left + u[i] + r[i];
                }
            }
        }
    }
    cout << ans - r[9] << endl;
}