#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

const ld INF = 1e18, eps = 1e-7;

int n, circ_left;
ld rad[100], rat[100], ans;
pair<ld, ld> points[100];
bool done[100];

ld dist(pair<ld, ld> x, pair<ld, ld> y) {
    return sqrt((x.f - y.f) * (x.f - y.f) + (x.s - y.s) * (x.s - y.s));
}

void collect(int u, vector<vector<int>> & g, vector<int> & comp, vector<bool> & vis) {
    vis[u] = true;
    comp.push_back(u);
    for(int v: g[u]) {
        if(!vis[v]) {
            collect(v, g, comp, vis);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s >> rad[i] >> rat[i];
    }
    circ_left = n;
    while(circ_left > 1) {
        int ic = -1;
        ld t_min = INF;
        vector<vector<int>> g(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i != j && !done[i] && !done[j]) {
                    t_min = min(t_min, (dist(points[i], points[j]) - rad[i] - rad[j]) / (rat[i] + rat[j]));
                    if(rad[i] + rad[j] > dist(points[i], points[j]) - eps) {
                        ic = i;
                        g[i].push_back(j);
                    }
                }
            }
        }
        if(ic == -1) {
            for(int i = 0; i < n; i++) {
                if(!done[i]) {
                    rad[i] += t_min * rat[i];
                }
            }
        } else {
            vector<int> comp;
            vector<bool> vis(n, false);
            collect(ic, g, comp, vis);
            pair<ld, ld> avg = {0, 0};
            ld mx_rat = 0, area_tot = 0;
            for(int i: comp) {
                avg.f += points[i].f;
                avg.s += points[i].s;
                area_tot += rad[i] * rad[i];
                mx_rat = max(mx_rat, rat[i]);
                if(i != ic) {
                    done[i] = true;
                    --circ_left;
                }
            }
            points[ic] = {avg.f / (ld) comp.size(), avg.s / (ld) comp.size()};
            rad[ic] = sqrt(area_tot);
            rat[ic] = mx_rat;
        }
    }
    for(int i = 0; i < n; i++) {
        if(!done[i]) {
            cout << fixed << setprecision(7) << points[i].f << " " << points[i].s << '\n' << rad[i] << '\n';
        }
    }
}