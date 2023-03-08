struct RollbackDSU {
    int n;
    vector<int> link, sz;
    vector<array<int, 4>> updates;
    RollbackDSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        updates.push_back({x, y, sz[x], link[y]});
        sz[x] += sz[y], link[y] = x;
    }
    void roll_back() {
        if(updates.empty()) {
            return;
        }
        array<int, 4> upd = updates.back();
        updates.pop_back();
        sz[upd[0]] = upd[2], link[upd[1]] = upd[3];
    }
}; 