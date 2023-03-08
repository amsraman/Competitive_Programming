struct DSU {
    int n; vector<int> link, sz;
    DSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};