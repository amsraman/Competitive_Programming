#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    vector<bool> prime(1000001, true);
    for(int i = 2; i <= 1000000; i++) {
        for(int j = 2 * i; j <= 1000000; j += i) {
            prime[j] = false;
        }
    }
    prime[0] = prime[1] = false;
    vector<bool> left(1001, false);
    int n, m, d; cin >> n >> m >> d;
    while(n > 0) {
        vector<int> cur, res; vector<vector<int>> nxt(1001);
        for(int i = n; i <= m; i++) {
            left[i] = true;
            for(int j = n; j <= m; j++) {
                if(i != j && !prime[i + j]) {
                    nxt[i].push_back(j);
                }
            }
        }
        auto gen = [&](auto rec, int lev) {
            if(lev == m - n + 1) {
                res = cur;
                return;
            } else if(lev == 0) {
                for(int i = n; i <= m; i++) {
                    cur.push_back(i);
                    left[i] = false;
                    rec(rec, lev + 1);
                    left[i] = true;
                    cur.pop_back();
                    if(!res.empty()) return;
                }
            } else {
                for(int nx: nxt[cur.back()]) {
                    if(left[nx]) {
                        left[nx] = false;
                        bool ok = true;
                        int sum = nx + cur.back();
                        for(int i = 3; i <= min(d, lev + 1); i++) {
                            sum += cur[lev - i + 1];
                            if(prime[sum]) {
                                ok = false;
                                break;
                            }
                        }
                        if(ok) {
                            cur.push_back(nx);
                            rec(rec, lev + 1);
                            cur.pop_back();
                            if(!res.empty()) return;
                        }
                        left[nx] = true;
                    }
                }
            }
        };
        gen(gen, 0);
        if(res.empty()) {
            cout << "No anti-prime sequence exists.\n";
        } else {
            cout << res[0];
            for(int i = 1; i < (int) res.size(); i++) {
                cout << "," << res[i];
            }
            cout << '\n';
        }
        cin >> n >> m >> d;
    }
}