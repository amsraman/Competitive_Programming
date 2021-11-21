#include <bits/stdc++.h>

using namespace std;

int t, n, d, c, m, dogs, ans;
string pets;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> d >> c >> m >> pets;
        ans = dogs = 0;
        for(int i = 0; i < n; i++) {
            dogs += (pets[i] == 'D');
        }
        for(int i = 0; i < n; i++) {
            if(pets[i] == 'C') {
                if(c == 0) {
                    break;
                } else {
                    --c;
                }
            } else {
                if(d == 0) {
                    break;
                } else {
                    --d, c += m;
                    ++ans;
                }
            }
        }
        cout << "Case #" << _ << ": " << (ans == dogs ? "YES" : "NO") << endl;
    }
}