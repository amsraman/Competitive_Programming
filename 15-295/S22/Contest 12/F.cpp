#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mxN = 4e5;

struct TwoSat {
    int var_count, time;
    vector<int> scc, lp, assignment;
    stack<int> dfs_stack;
    vector<vector<int>> implication_graph;
    
    TwoSat(int n = 0): var_count(n), implication_graph(2 * n) {}

    int add_var() {
        implication_graph.emplace_back();
        implication_graph.emplace_back();
        return var_count++;
    }

    void add_clause(int u, int v) {
        implication_graph[u ^ 1].push_back(v);
        implication_graph[v ^ 1].push_back(u);
    }

    void either(int u, int v) {
        add_clause(u, v);
        add_clause(u ^ 1, v ^ 1);
    }

    void same(int u, int v) {
        either(u, v ^ 1);
    }

    void set(int u) {
        either(u, u);
    }

    void at_most_one(vector<int> & vars) {
        vector<int> pre, suf;
        for(int i = 0; i < vars.size(); i++) {
            pre.push_back(add_var()), suf.push_back(add_var());
            add_clause(pre[i] << 1 ^ 1, vars[i] ^ 1);
            add_clause(suf[i] << 1 ^ 1, vars[i] ^ 1);
            if(i > 0) {
                add_clause(pre[i] << 1 ^ 1, pre[i - 1] << 1);
                add_clause(suf[i - 1] << 1 ^ 1, suf[i] << 1);
                add_clause(vars[i] ^ 1, pre[i - 1] << 1);
                add_clause(vars[i - 1] ^ 1, suf[i] << 1);
            }
        }
    }

    int dfs(int u) {
        int low = lp[u] = ++time, v;
        dfs_stack.push(u);
        for(int v: implication_graph[u]) {
            if(!scc[v]) {
                low = min(low, lp[v] ?: dfs(v));
            }
        }
        ++time;
        if(low == lp[u]) {
            do {
                v = dfs_stack.top();
                dfs_stack.pop();
                scc[v] = time;
                if(assignment[v >> 1] == -1) {
                    assignment[v >> 1] = v & 1;
                }
            } while(v != u);
        }
        return lp[u] = low;
    }

    bool solvable() {
        scc.assign(var_count << 1, 0), lp.assign(var_count << 1, 0);
        assignment.assign(var_count, -1);
        time = 0;
        for(int i = 0; i < var_count << 1; i++) {
            if(!scc[i]) {
                dfs(i);
            }
        }
        for(int i = 0; i < var_count; i++) {
            if(scc[i << 1] == scc[i << 1 ^ 1]) {
                return false;
            }
        }
        return true;
    }
};

int n, q, t, in[mxN], out[mxN], par[mxN], tot[mxN];
bool bad[mxN][26], used[mxN], unfound = false;
pair<int, int> pts[mxN];
vector<int> g[mxN], ct[mxN][26];
char ans[mxN];
string s[mxN];

void dfs(int x, int p) {
    in[x] = t++, par[x] = p;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
        }
    }
    out[x] = t++;
}

bool isAnc(int x, int y) {
    return (in[x] <= in[y] && out[x] >= out[y]);
}

vector<int> get_path(int x, int y) {
    vector<int> p1, p2;
    while(!isAnc(x, y)) {
        p1.push_back(x);
        x = par[x];
    }
    while(y != x) {
        p2.push_back(y);
        y = par[y];
    }
    p1.push_back(x);
    reverse(p2.begin(), p2.end());
    for(int p: p2) {
        p1.push_back(p);
    }
    return p1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    for(int i = 0, x, y; i < q; i++) {
        cin >> x >> y >> s[i];
        int len = s[i].length();
        vector<int> path = get_path(x - 1, y - 1);
        assert(path.size() == len);
        for(int j = 0; j < len; j++) {
            used[path[j]] = true;
            if(s[i][j] != s[i][len - j - 1]) {
                ct[path[j]][s[i][j] - 'a'].push_back(i << 1);
                ct[path[j]][s[i][len - j - 1] - 'a'].push_back(i << 1 ^ 1);
                ++tot[path[j]];
            } else {
                for(int k = 0; k < 26; k++) {
                    if(k != s[i][j] - 'a') {
                        bad[path[j]][k] = true;
                    }
                }
            }
        }
        pts[i] = {x - 1, y - 1};
    }
    TwoSat ords(q);
    for(int i = 0; i < n; i++) {
        vector<int> lt;
        for(int j = 0; j < 26; j++) {
            if(ct[i][j].size() == tot[i] && !bad[i][j]) {
                lt.push_back(j);
            }
        }
        if(lt.size() == 2) {
            vector<int> vars = ct[i][lt[0]];
            for(int j = 0; j < (int) vars.size() - 1; j++) {
                ords.same(vars[j], vars[j + 1]);
            }
        } else if(lt.size() == 1) {
            for(int v: ct[i][lt[0]]) {
                ords.add_clause(v, v);
            }
        } else if(used[i]) {
            unfound = true;
        }
    }
    if(!unfound && ords.solvable()) {
        cout << "YES\n";
        for(int i = 0; i < q; i++) {
            vector<int> path = get_path(pts[i].f, pts[i].s);
            if(ords.assignment[i]) {
                reverse(path.begin(), path.end());
            }
            for(int j = 0, len = s[i].length(); j < len; j++) {
                ans[path[j]] = s[i][j];
            }
        }
        for(int i = 0; i < n; i++) {
            cout << (ans[i] == 0 ? 'a' : ans[i]);
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }
}