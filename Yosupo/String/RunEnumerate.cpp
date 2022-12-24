// 280 ms
#include <bits/stdc++.h>

using namespace std;

vector<int> Z(const string & s) {
    int n = s.length();
    vector<int> z(n, 0);
    for(int i = 1, l = 0, r = 0; i < n; i++) {
        if(i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if(i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

void MainLorentz(const string & s, vector<array<int, 3>> & reps, int lo, int hi) { // Requires Z
    if(lo == hi) {
        return;
    }
    int mid = (lo + hi) / 2, len1 = mid - lo + 1, len2 = hi - mid;
    MainLorentz(s, reps, lo, mid); MainLorentz(s, reps, mid + 1, hi);
    string u = s.substr(lo, mid - lo + 1), v = s.substr(mid + 1, hi - mid);
    string ru(u.rbegin(), u.rend()), rv(v.rbegin(), v.rend());
    vector<int> z1 = Z(ru), z2 = Z(v + "#" + u), z3 = Z(ru + "#" + rv), z4 = Z(v);
    for(int pos = lo; pos <= mid; pos++) { // case on suffixes of u, for each extend as far back and forward as possible
        int lb = pos - (pos == lo ? 0 : z1[mid - pos + 1]), ub = mid + z2[len2 + 1 + pos - lo];
        if(ub > mid && ub - lb + 1 >= 2 * (mid - pos + 1)) {
            reps.push_back({lb, ub, mid - pos + 1});
        }
    }
    for(int pos = mid + 1; pos <= hi; pos++) { // case on prefixes of v, for each extend as far back and forward as possible
        int lb = mid + 1 - z3[len1 + 1 + hi - pos], ub = pos + (pos == hi ? 0 : z4[pos - mid]);
        if(lb <= mid && ub - lb + 1 >= 2 * (pos - mid)) {
            reps.push_back({lb, ub, pos - mid});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int n = s.length(); vector<array<int, 3>> res, ans; vector<vector<pair<int, int>>> periods(n + 1);
    MainLorentz(s, res, 0, s.length() - 1);
    for(auto [l, r, p]: res) {
        periods[p].push_back({l, r});
    }
    set<pair<int, int>> seen;
    for(int i = 1; i <= n; i++) {
        sort(periods[i].begin(), periods[i].end()); pair<int, int> pv = {-1e9, -1e9};
        for(auto [l, r]: periods[i]) {
            if(pv.second - i + 1 < l) {
                if(!seen.count(pv) && pv.second != -1e9) {
                    ans.push_back({i, pv.first, pv.second + 1}); seen.insert(pv);
                }
                pv = {l, r};
            } else {
                pv.second = max(pv.second, r);
            }
        }
        if(!seen.count(pv) && pv.second != -1e9) {
            ans.push_back({i, pv.first, pv.second + 1}); seen.insert(pv);
        }
    }
    cout << ans.size() << '\n';
    for(array<int, 3> r: ans) {
        cout << r[0] << " " << r[1] << " " << r[2] << '\n';
    }
}