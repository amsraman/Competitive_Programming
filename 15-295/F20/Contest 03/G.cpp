#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, mn_y, mx_y, px[100001], pn[100001], sx[100001], sn[100001], pabs[100001], sabs[100001];
pair<int, int> points[100000];

ll norm(int x, int y) {
    return 1LL * x * x + 1LL * y * y;
}

bool ok(ll dm) {
    if((1LL * (points[n - 1].f - points[0].f) * (points[n - 1].f - points[0].f)) <= dm) {
        return true;
    }
    if(1LL * (mx_y - mn_y) * (mx_y - mn_y) <= dm) {
        return true;
    }
    for(int i = 0; i < n; i++) {
        if(points[i].f < 0) {
            int lb = 0, ub = n;
            while(lb < ub) {
                int mid = (lb + ub) / 2;
                if(points[mid].f > -points[i].f || (points[mid].f > points[i].f && norm(points[mid].f - points[i].f, 0) > dm)) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            int ly = pabs[i], uy = sabs[ub], y_dist = max(px[i], sx[ub]) - min(pn[i], sn[ub]);
            if(norm(-points[i].f, max(ly, uy)) <= dm && 1LL * y_dist * y_dist <= dm) {
                return true;
            }
        } else {
            int lb = 0, ub = n;
            while(lb < ub) {
                int mid = (lb + ub + 1) / 2;
                if(points[mid - 1].f < -points[i].f || (points[mid - 1].f < points[i].f && norm(points[mid - 1].f - points[i].f, 0) > dm)) {
                    lb = mid;
                } else {
                    ub = mid - 1;
                }
            }
            int ly = pabs[ub], uy = sabs[i + 1], y_dist = max(px[ub], sx[i + 1]) - min(pn[ub], sn[i + 1]);
            if(norm(points[i].f, max(ly, uy)) <= dm && 1LL * y_dist * y_dist <= dm) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> n;
    mn_y = 1e9, mx_y = -1e9;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
        mn_y = min(mn_y, points[i].s);
        mx_y = max(mx_y, points[i].s);
    }
    sort(points, points + n);
    px[0] = sx[n] = -1e9, pn[0] = sn[n] = 1e9;
    for(int i = 0; i < n; i++) {
        px[i + 1] = max(px[i], points[i].s);
        pn[i + 1] = min(pn[i], points[i].s);
        pabs[i + 1] = max(pabs[i], abs(points[i].s));
    }
    for(int i = n - 1; i >= 0; i--) {
        sx[i] = max(sx[i + 1], points[i].s);
        sn[i] = min(sn[i + 1], points[i].s);
        sabs[i] = max(sabs[i + 1], abs(points[i].s));
    }
    ll lb = 0, ub = 1e17;
    while(lb < ub) {
        ll mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << ub << endl;
}