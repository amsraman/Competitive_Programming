#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld eps = 1e-9;

template <typename T>
struct LinearProgram { // Maximize c^T x s.t. Ax <= b, x >= 0
    enum solution {SOLVED, INFEASIBLE, UNBOUNDED};
    int n, m; T opt;
    vector<vector<T>> a;
    vector<T> b, c, var, sol;
    LinearProgram(const vector<vector<T>> & a, const vector<T> & b, const vector<T> & c): a(a), b(b), c(c), n(c.size()), m(b.size()), var(n + m), sol(n) {
        assert(a.size() == m);
        for(int i = 0; i < m; i++) assert(a[i].size() == n);
        iota(var.begin(), var.end(), 0);
    }
    int cmp(T x, T y) {
        if(x + eps < y) return 0;
        if(y + eps < x) return 2;
        return 1;
    }
    void pivot(int x, int y) { // Increase the xth variable until the yth constraint becomes tight, then adjust basis
        for(int i = 0; i < n; i++) {
            if(i != x) a[y][i] /= a[y][x];
        }
        b[y] /= a[y][x], a[y][x] = 1 / a[y][x];
        for(int i = 0; i < m; i++) {
            if(i == y) continue;
            for(int j = 0; j < n; j++) {
                if(j != x) a[i][j] -= a[y][j] * a[i][x];
            }
            b[i] -= b[y] * a[i][x], a[i][x] *= -a[y][x];
        }
        for(int i = 0; i < n; i++) {
            if(i != x) c[i] -= c[x] * a[y][i];
        }
        opt += c[x] * b[y], c[x] *= -a[y][x];
        swap(var[x], var[n + y]);
    }
    solution solve() { // Simplex
        fill(sol.begin(), sol.end(), 0); opt = 0;
        while(true) { // Find feasible point
            int x = -1, y = -1;
            for(int i = 0; i < m; i++) {
                if(cmp(b[i], 0) == 0 && (y == -1 || cmp(b[i], b[y]) == 0)) y = i;
            }
            if(y == -1) break;
            for(int i = 0; i < n; i++) {
                if(cmp(a[i][y], 0) == 0 && (x == -1 || cmp(a[i][y], a[x][y]) == 0)) x = i;
            }
            if(x == -1) return INFEASIBLE;
            pivot(x, y);
        }
        while(true) { // Find optimal vertex
            int x = -1, y = -1;
            for(int i = 0; i < n; i++) {
                if(cmp(c[i], 0) == 2 && (x == -1 || cmp(c[i], c[x]) == 2)) x = i;
            }
            if(x == -1) break;
            for(int i = 0; i < m; i++) {
                if(cmp(0, a[i][x]) == 0 && (y == -1 || cmp(b[i] / a[i][x], b[y] / a[y][x]) == 0)) y = i;
            }
            if(y == -1) return UNBOUNDED;
            pivot(x, y);
        }
        for(int i = 0; i < n; i++) {
            if(var[i] < n) sol[var[i]] = b[i];
        }
        return SOLVED;
    }
};

using fl = long double;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<fl>> a(n, vector<fl>(m));
    vector<fl> b(n), c(m);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[j][i]; a[j][i] /= 100;
        }
        cin >> c[i];
    }
    LinearProgram<fl> lp(a, b, c);
    assert(lp.solve() == LinearProgram<fl>::SOLVED);
    cout << fixed << setprecision(2) << lp.opt << '\n';
}