int discrete_log(int x, int y, int m) { // find the smallest k st x^k = y mod m, -1 if none exist
    x %= m, y %= m;
    int g, st = 1, add = 0;
    while((g = __gcd(x, m)) > 1) {
        if(y == st) return add;
        if(y % g != 0) return -1;
        y /= g, m /= g, ++add, st = (1LL * st * x / g) % m;
    }
    int sq = sqrt(m), jump = 1;
    unordered_map<int, int> small;
    for(int i = 1, cur = (1LL * y * x) % m; i <= sq; i++, cur = (1LL * cur * x) % m) {
        small[cur] = i, jump = (1LL * jump * x) % m;
    }
    for(int i = 1, cur = (1LL * st * jump) % m; i <= m / sq + 1; i++, cur = (1LL * cur * jump) % m) {
        if(small.count(cur)) {
            return i * sq - small[cur] + add;
        }
    }
    return -1;
}