#include <bits/stdc++.h>

using namespace std;

int main() {
    int p, m, x; cin >> p >> m >> x;
    map<int, string> hsh;
    for(int a = 0; a < 26; a++) {
        for(int b = 0; b < 26; b++) {
            for(int c = 0; c < 26; c++) {
                for(int d = 0; d < 26; d++) {
                    string cur = "";
                    cur += char('a' + a); cur += char('a' + b); cur += char('a' + c); cur += char('a' + d);
                    int h = 0;
                    h = (1LL * h * p + d + 1) % m;
                    h = (1LL * h * p + c + 1) % m;
                    h = (1LL * h * p + b + 1) % m;
                    h = (1LL * h * p + a + 1) % m;
                    hsh[h] = cur;
                }
            }
        }
    }
    int cur = 0, p4 = 1;
    for(int i = 0; i < 4; i++) p4 = (1LL * p4 * p) % m;
    int base; string beg;
    bool found = false;
    for(int i = 0; i + 4 <= 1e5; i++) { // i is the number of ones so far
        int aug = (1LL * p4 * cur) % m;
        int rem = (x - aug + m) % m;
        if(hsh.count(rem)) {
            beg = hsh[rem]; base = i;
            found = true;
            break;
        }
        cur = (1LL * p * cur + 1) % m;
    }
    assert(found);
    cout << beg;
    for(int i = 0; i < base; i++) cout << 'a';
    cout << '\n';
}