#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, q;
map<pair<int, int>, int> dist;
set<pair<int, int>> power;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0, a, b; i < q; i++) {
        cin >> a >> b;
        power.insert({a, b});
    }
    priority_queue<pair<int, pair<int, int>>> q;
    q.push({0, {1, 1}});
    dist[{1, 1}] = 0;
    int curd = -1, curm;
    while(!q.empty()) {
        pair<int, int> tp = q.top().s;
        if(-q.top().f != curd) {
            curd = -q.top().f;
            curm = 0;
        }
        q.pop();
        if(tp.s < curm) {
            continue;
        }
        curm = max(curm, tp.s);
        int d = dist[tp];
        if(power.count(tp)) {
            for(int i = min(m, tp.f + tp.s + 1); i <= min(m, tp.f + tp.s + 1); i++) {
                if(!dist.count({tp.f, i})) {
                    q.push({-d - 1, {tp.f, i}});
                    dist[{tp.f, i}] = d + 1;
                }
            }
            for(int i = min(n, tp.f + tp.s + 1); i <= min(n, tp.f + tp.s + 1); i++) {
                if(!dist.count({i, tp.s})) {
                    q.push({-d - 1, {i, tp.s}});
                    dist[{i, tp.s}] = d + 1;
                }
            }
        } else {
            for(int i = min(m, tp.f + tp.s); i <= min(m, tp.f + tp.s); i++) {
                if(!dist.count({tp.f, i})) {
                    q.push({-d - 1, {tp.f, i}});
                    dist[{tp.f, i}] = d + 1;
                }
            }
            for(int i = min(n, tp.f + tp.s); i <= min(n, tp.f + tp.s); i++) {
                if(!dist.count({i, tp.s})) {
                    q.push({-d - 1, {i, tp.s}});
                    dist[{i, tp.s}] = d + 1;
                }
            }
        }
    }
    cout << dist[{n, m}] << '\n';
}
