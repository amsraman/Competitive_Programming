#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; _ <= n; _++) {
        int m; cin >> m;
        using state = pair<vector<ll>, vector<char>>;
        state exp;
        auto print_state = [](state e) {
            int sz = (int) e.first.size();
            for(int i = 0; i < sz; i++) {
                cout << e.first[i] << " ";
                if(i < sz - 1) cout << e.second[i] << " ";
            }
            cout << '\n';
        };
        for(int j = 0; j < m; j++) {
            int num; char op; cin >> num >> op;
            exp.first.push_back(num); exp.second.push_back(op);
        }
        int num; cin >> num;
        exp.first.push_back(num);
        auto eval = [](state e, int op) {
            vector<ll> nv; vector<char> no;
            int sz = (int) e.second.size(); nv.push_back(e.first[0]);
            assert(op < sz);
            for(int i = 0; i < sz; i++) {
                nv.push_back(e.first[i + 1]);
                no.push_back(e.second[i]);
                if(i == op) {
                    char p = no.back(); no.pop_back();
                    ll v2 = nv.back(); nv.pop_back();
                    ll v1 = nv.back(); nv.pop_back();
                    if(p == '+') {
                        nv.push_back(v1 + v2);
                    } else if(p == '-') {
                        nv.push_back(v1 - v2);
                    } else {
                        nv.push_back(v1 * v2);
                    }
                }
            }
            return make_pair(nv, no);
        };
        map<state, ll> mx;
        map<state, ll> mn;
        auto solve = [&](auto rec, state e, bool tp) -> ll {
            int sz = e.second.size();
            if(tp) {
                if(mx.count(e)) return mx[e];
                if(sz == 0) return mx[e] = e.first[0];
            }
            if(!tp) {
                if(mn.count(e)) return mn[e];
                if(sz == 0) return mn[e] = e.first[0];
            }
            ll res = (tp ? -1e18 : 1e18);
            for(int i = 0; i < sz; i++) {
                if(tp) {
                    res = max(res, rec(rec, eval(e, i), tp ^ 1));
                } else {
                    res = min(res, rec(rec, eval(e, i), tp ^ 1));
                }
            }
            if(tp) {
                return mx[e] = res;
            }
            return mn[e] = res;
        };
        ll r1 = solve(solve, exp, true);
        ll r2 = solve(solve, exp, false);
        cout << "Case " << _ << ":\n";
        cout << "Player 1 (";
        for(int i = 0; i < m; i++) {
            ll res = mn[eval(exp, i)];
            if(res == r1) {
                cout << exp.first[i] << exp.second[i] << exp.first[i + 1];
                break;
            }
        }
        cout << ") leads to " << r1 << '\n';
        cout << "Player 2 (";
        for(int i = 0; i < m; i++) {
            ll res = mx[eval(exp, i)];
            if(res == r2) {
                cout << exp.first[i] << exp.second[i] << exp.first[i + 1];
                break;
            }
        }
        cout << ") leads to " << r2 << '\n';
        if(r1 > -r2) {
            cout << "Player 1 wins\n";
        } else if(r1 < -r2) {
            cout << "Player 2 wins\n";
        } else {
            cout << "Tie\n";
        }
    }
}