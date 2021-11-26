#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll n, m, x, y, vx, vy;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll res = egcd(b, a % b, y, x);
    y -= (a / b) * x;
    return res;
}

int main() {
    cin >> n >> m >> x >> y >> vx >> vy;
    if(vx * vy == 0) {
        if(vx == 0 && (x == 0 || x == n)) {
            if(vy == -1) {
                cout << x << " " << 0 << endl;
            } else {
                cout << x << " " << n << endl;
            }
        } else if(vy == 0 && (y == 0 || y == m)) {
            if(vx == -1) {
                cout << 0 << " " << y << endl;
            } else {
                cout << m << " " << y << endl;
            }
        } else {
            cout << -1 << endl;
        }
    } else {
        if(vx < 0) {
            x = n - x;
        }
        if(vy < 0) {
            y = m - y;
        }
        if((y - x) % __gcd(n, m) != 0) {
            cout << -1 << endl;
        } else {
            ll k1, k2, step1 = m / __gcd(n, m), step2 = n / __gcd(n, m), lcm = n * m / __gcd(n, m);
            ll g = egcd(-n, m, k1, k2);
            k1 *= (y - x) / g;
            k2 *= (y - x) / g;
            ll num = (k1 - k1 % step1) / step1;
            k1 -= step1 * num, k2 -= step2 * num;
            if((__int128_t) k1 * n < x) {
                ll num = (x - k1 * n + lcm - 1) / lcm;
                k1 += step1 * num, k2 += step2 * num;
            }
            int par1 = abs(k1 % 2) ^ (vx < 0), par2 = abs(k2 % 2) ^ (vy < 0);
            cout << (par1 ? n : 0) << " " << (par2 ? m : 0) << endl;
        }
    } 
}