struct RollbackDSU {
    int n;
    vector<int> link, sz;
    vector<array<int, 4>> updates;
 
    RollbackDSU(int n): n(n), link(n), sz(n) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            sz[i] = 1;
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : f(link[x]));
    }
 
    void unite(int x, int y) {
        x = f(x), y = f(y);
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