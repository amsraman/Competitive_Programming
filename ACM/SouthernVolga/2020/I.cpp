#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
pair<ll, ll> frac[4];
array<ll, 4> lines[4];
ll dx1, dy1, dx2, dy2;

ll frac_ceil(pair<ll, ll> frac) {
    if(frac.s == 0) {
        return (frac.f > 0 ? 2e7 : -2e7);
    }
    if(frac.f < 0) {
        return frac.f / frac.s;
    }
    return (frac.f + frac.s - 1) / frac.s;
}

int main() {
    cin >> n >> dx1 >> dy1 >> dx2 >> dy2;
    if(abs(dx1 * dy2 - dx2 * dy1) != n) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        if(dy1 < 0) {
            dx1 *= -1, dy1 *= -1;
        }
        if(dy2 < 0) {
            dx2 *= -1, dy2 *= -1;
        }
        if(dy2 == 0) {
            swap(dx1, dx2), swap(dy1, dy2);
        }
        lines[0] = {0, 0, dx1, dy1};
        lines[1] = {0, 0, dx2, dy2};
        lines[2] = {dx1, dy1, dx2, dy2};
        lines[3] = {dx2, dy2, dx1, dy1};
        // exclusive min/max
        for(int i = 1; i < dy1 + dy2; i++) {
            // There will be four intersection points, encode them as fractions and order them
            // Our legal range will be from the ceiling of point 2 to the ceiling of point 3 - 1
            for(int j = 0; j < 4; j++) {
                frac[j] = {lines[j][0] * lines[j][3] + lines[j][2] * (i - lines[j][1]), lines[j][3]};
            }
            sort(frac, frac + 4, [](pair<ll, ll> frac1, pair<ll, ll> frac2) {
                if(frac1.s == 0) {
                    return frac1.f < 0;
                }
                if(frac2.s == 0) {
                    return frac2.f >= 0;
                }
                return (__int128_t) frac1.f * frac2.s < (__int128_t) frac2.f * frac1.s;
            });
            int lb = frac_ceil(frac[1]), ub = frac_ceil(frac[2]) - 1;
            for(int j = lb; j <= ub; j++) {
                if((j != dx1 || i != dy1) && (j != dx2 || i != dy2)) {
                    cout << j << " " << i << endl;
                }
            }
        }
        int lb = 0, ub = 1;
        if(dy1 == 0) {
            lb = min(0LL, dx1), ub = max(0LL, dx1);
        }
        for(int i = lb; i < ub; i++) {
            cout << i << " " << 0 << endl;
        }
    }
}