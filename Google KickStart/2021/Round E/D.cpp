#include <bits/stdc++.h>

using namespace std;

int t;
long long n;
long double euler_mascheroni = 0.5772156649;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        cout << "Case #" << _ << ": ";
        if(n <= 1000000) {
            long double ans = 0;
            for(int i = 1; i <= n; i++) {
                ans += 1.0 / (long double) i;
            }  
            cout << fixed << setprecision(7) << ans << endl;
        } else {
            long double double_n = n;
            n += 0.5;
            cout << fixed << setprecision(7) << log(n) + euler_mascheroni << endl;
        }
    }
}