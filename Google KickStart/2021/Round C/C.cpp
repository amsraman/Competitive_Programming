#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int t, x, w, e;
ld dp[62][62][62];

int main()
{
    cin >> t >> x;
    for(int _ = 1; _<=t; _++)
    {
        cin >> w >> e;
        for(int r = 60; r>=0; r--) {
            for(int p = 60-r; p>=0; p--) {
                for(int s = 60-r-p; s>=0; s--) {
                    ld p_r = 1.0/3, p_p = 1.0/3, p_s = 1.0/3;
                    dp[r][p][s] = 0;
                    if(r+p+s>0) {
                        p_r = (ld)s/(r+p+s), p_p = (ld)r/(r+p+s), p_s = (ld)p/(r+p+s);
                    }
                    dp[r][p][s] = max(dp[r][p][s],dp[r+1][p][s]+p_s*w+p_r*e);
                    dp[r][p][s] = max(dp[r][p][s],dp[r][p+1][s]+p_r*w+p_p*e);
                    dp[r][p][s] = max(dp[r][p][s],dp[r][p][s+1]+p_p*w+p_s*e);
                }
            }
        }
        cout << "Case #" << _ << ": ";
        int r = 0, p = 0, s = 0;
        for(int i = 0; i<60; i++) {
            ld p_r = 1.0/3, p_p = 1.0/3, p_s = 1.0/3;
            if(r+p+s>0) {
                p_r = (ld)s/(r+p+s), p_p = (ld)r/(r+p+s), p_s = (ld)p/(r+p+s);
            }
            if(dp[r][p][s]==dp[r+1][p][s]+p_s*w+p_r*e) {
                cout << 'R';
                ++r;
            } else if(dp[r][p][s]==dp[r][p+1][s]+p_r*w+p_p*e) {
                cout << 'P';
                ++p;
            } else {
                cout << 'S';
                ++s;
            }
        }
        cout << endl;
    }
}