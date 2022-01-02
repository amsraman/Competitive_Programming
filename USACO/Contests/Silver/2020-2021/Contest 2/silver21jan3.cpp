#include <bits/stdc++.h>

using namespace std;

int n, a[1000][1000], row_max, col_max;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
        for(int j = 0; j < n; j++) {
            if(j % 2 == 0) {
                s1 += a[i][j], s3 += a[j][i];
            } else {
                s2 += a[i][j], s4 += a[j][i];
            }
        }
        row_max += max(s1, s2), col_max += max(s3, s4);
    }
    cout << max(row_max, col_max) << endl;
}