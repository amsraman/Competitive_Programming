#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, state[200010];
bool assignment[200010], bad, done[200010], cyc;
vector<pair<int, int>> places[200010], g[200010];
vector<pair<int, int>> stk;

void dfs(int x) {
    done[x] = true;
    for(pair<int, int> e: g[x]) {
        if(!done[e.f]) {
            int var = abs(e.s);
            assignment[var] = (e.s < 0 ? 1 : 0);
            dfs(e.f);
        }
    }
}

void dfs2(int x, int pv) {
    state[x] = 1;
    for(pair<int, int> e: g[x]) {
        if(!done[e.f] && state[e.f] == 0) {
            if(!cyc) {
                stk.push_back(e);
            }
            dfs2(e.f, e.s);
            if(!cyc) {
                stk.pop_back();
            }
        } else if(state[e.f] == 1 && e.s != -pv && !cyc) {
            stk.push_back(e);
            cyc = true;
        }
    }
    state[x] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int k_i;
        cin >> k_i;
        for(int j = 0, var; j < k_i; j++) {
            cin >> var;
            places[abs(var)].push_back({i, var});
        }
    }
    for(int i = 1; i <= m; i++) {
        if(places[i].size() == 2 && places[i][0].s + places[i][1].s == 0) {
            g[places[i][0].f].push_back({places[i][1].f, places[i][0].s});
            g[places[i][1].f].push_back({places[i][0].f, places[i][1].s});
        }
    }
    for(int i = 1; i <= m; i++) {
        if(places[i].size() == 1) {
            assignment[i] = (places[i][0].s > 0 ? 1 : 0);
            if(!done[places[i][0].f]) {
                dfs(places[i][0].f);
            }
        } else if(places[i].size() == 2 && places[i][0].s == places[i][1].s) {
            assignment[i] = (places[i][0].s > 0 ? 1 : 0);
            if(!done[places[i][0].f]) {
                dfs(places[i][0].f);
            }
            if(!done[places[i][1].f]) {
                dfs(places[i][1].f);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(!done[i] && state[i] == 0) {
            stk.push_back({i, 0});
            dfs2(i, 0x3f3f3f3f);
            if(cyc) {
                int lst = stk.back().f, seen = 0;
                vector<int> vertices;
                while(true) {
                    pair<int, int> ed = stk.back();
                    stk.pop_back();
                    if(ed.f == lst) {
                        ++seen;
                    }
                    if(seen == 2) {
                        break;
                    }
                    assignment[abs(ed.s)] = (ed.s < 0 ? 1 : 0);
                    done[ed.f] = true;
                    vertices.push_back(ed.f);
                }
                for(int v: vertices) {
                    dfs(v);
                }
                stk.clear();
                cyc = false;
            } else {
                bad = true;
                break;
            }
        }
    }
    if(!bad) {
        cout << "YES\n";
        for(int i = 1; i <= m; i++) {
            cout << assignment[i];
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }
}