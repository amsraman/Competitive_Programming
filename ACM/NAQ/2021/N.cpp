#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod1 = 1e9 + 7, mod2 = 998244353;
const ll big = 1e9;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<vector<int>> sts(n + 1);
    vector<vector<int>> add(n + 1, vector<int>(2000, -1)), rem(n + 1, vector<int>(2000, -1)); vector<int> out_deg(n + 1, 0);
    vector<bool> done(n + 1, false);
    vector<pair<int, int>> rng(2000, {-1, -1});
    map<string, int> id; int name_ct = 0; vector<string> names;
    vector<pair<int, int>> set_to_hash(n + 1, {0, 0}); unordered_map<ll, int> hash_to_set; hash_to_set[0] = 0;
    vector<pair<int, int>> p2(2001, {1, 1});
    for(int i = 1; i <= 2000; i++) {
        p2[i].first = (2LL * p2[i - 1].first) % mod1;
        p2[i].second = (2LL * p2[i - 1].second) % mod2;
    }
    for(int i = 0, k; i < n; i++) {
        cin >> k;
        pair<int, int> hsh = {0, 0};
        for(int j = 0; j < k; j++) {
            string name; cin >> name;
            if(!id.count(name)) {
                id[name] = name_ct++; names.push_back(name);
            }
            sts[i + 1].push_back(id[name]);
            hsh.first = (hsh.first + p2[id[name]].first) % mod1;
            hsh.second = (hsh.second + p2[id[name]].second) % mod2;
        }
        sort(sts[i + 1].begin(), sts[i + 1].end());
        set_to_hash[i + 1] = hsh, hash_to_set[big * hsh.first + hsh.second] = i + 1;
    }
    for(int i = 1; i <= n; i++) { // constructing add/rem maps
        auto hsh = set_to_hash[i];
        for(int j: sts[i]) {
            hsh.first = (hsh.first - p2[j].first + mod1) % mod1;
            hsh.second = (hsh.second - p2[j].second + mod2) % mod2;
            ll conv = big * hsh.first + hsh.second;
            if(hash_to_set.count(conv)) {
                add[hash_to_set[conv]][j] = i;
                rem[i][j] = hash_to_set[conv]; ++out_deg[hash_to_set[conv]];
            }
            hsh.first = (hsh.first + p2[j].first) % mod1;
            hsh.second = (hsh.second + p2[j].second) % mod2;
        }
    }
    int cur_set = 0, tm = 0; bool bad = false;
    queue<int> pending;
    while(true) { // greedily attempting to construct an order
        if(cur_set == 0) {
            for(int i = 0; i < name_ct; i++) {
                if(add[cur_set][i] != -1 && !done[add[cur_set][i]] && out_deg[add[cur_set][i]] <= 1) {
                    cur_set = add[cur_set][i];
                    pending.push(i); rng[i].first = tm++;
                    break;
                }
            }
            if(cur_set == 0) break;
        } else {
            bool fd = false;
            for(int i = 0; i < name_ct; i++) {
                if(add[cur_set][i] != -1 && !done[add[cur_set][i]]) {
                    cur_set = add[cur_set][i];
                    fd = true;
                    pending.push(i); rng[i].first = tm++;
                    break;
                }
            }
            if(!fd) {
                assert(!pending.empty());
                int tp = pending.front(); pending.pop(); rng[tp].second = tm++;
                auto hsh = set_to_hash[cur_set];
                cur_set = rem[cur_set][tp];
                if(cur_set == -1) {
                    hsh.first = (hsh.first - p2[tp].first + mod1) % mod1;
                    hsh.second = (hsh.second - p2[tp].second + mod2) % mod2;
                    for(int i = 0; i < name_ct; i++) { // one annoying case where endpoints should coincide
                        auto attempt = make_pair((hsh.first + p2[i].first) % mod1, (hsh.second + p2[i].second) % mod2);
                        ll conv = big * attempt.first + attempt.second;
                        if(rng[i].first == -1 && hash_to_set.count(conv) && !done[hash_to_set[conv]]) {
                            cur_set = hash_to_set[conv];
                            fd = true;
                            pending.push(i); rng[i].first = tm - 1;
                            break;
                        }
                    }
                    if(!fd) {
                        bad = true;
                        break;
                    }
                }
            }
        }
        done[cur_set] = true;
        for(int i = 0; i < name_ct; i++) {
            if(rem[cur_set][i] != -1) {
                --out_deg[rem[cur_set][i]];
            }
        }
    }
    vector<pair<int, int>> ev;
    for(int i = 0; i < name_ct; i++) {
        if(rng[i].first == -1) continue;
        ev.emplace_back(rng[i].first, i + 1);
        ev.emplace_back(rng[i].second, -i - 1);
    }
    sort(ev.begin(), ev.end()); set<pair<int, int>> seen; pair<int, int> cur_hsh = {0, 0};
    for(int i = 0; i < (int) ev.size(); i++) { // make sure the ordering we have works
        auto [x, val] = ev[i];
        if(val < 0) {
            ++val; val *= -1;
            cur_hsh.first = (cur_hsh.first - p2[val].first + mod1) % mod1;
            cur_hsh.second = (cur_hsh.second - p2[val].second + mod2) % mod2;
        } else {
            --val;
            cur_hsh.first = (cur_hsh.first + p2[val].first) % mod1;
            cur_hsh.second = (cur_hsh.second + p2[val].second) % mod2;
        }
        if(i == (int) ev.size() - 1 || x != ev[i + 1].first) {
            if(!hash_to_set.count(big * cur_hsh.first + cur_hsh.second)) {
                bad = true;
                break;
            }
            seen.insert(cur_hsh);
        }
    }
    if(seen.size() != n + 1) bad = true;
    if(!bad) {
        for(int i = 0; i < name_ct; i++) {
            cout << names[i] << " " << rng[i].first << " " << rng[i].second << '\n';
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }
}