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
            reps.push_back({lb, ub + pos - mid, mid - pos + 1});
        }
    }
    for(int pos = mid + 1; pos <= hi; pos++) { // case on prefixes of v, for each extend as far back and forward as possible
        int lb = mid + 1 - z3[len1 + 1 + hi - pos], ub = pos + (pos == hi ? 0 : z4[pos - mid]);
        if(lb <= mid && ub - lb + 1 >= 2 * (pos - mid)) {
            reps.push_back({lb, ub + mid - pos + 1, pos - mid});
        }
    }
}

vector<array<int, 3>> MainLorentz(const string & s) { // Requires Suffix Array
    int n = s.length();
    SuffixArray sa(s), rsa({s.rbegin(), s.rend()});
    vector<array<int, 3>> res;
    for(int p = n / 2; p >= 1; p--) {
        for(int i = 0, last = -1; i + p < n; i += p) {
            int l = i - rsa.lcp(n - i - p - 1, n - i - 1) + 1, r = i - p + sa.lcp(i, i + p);
            if(l > r || l == last) continue;
            res.push_back({last = l, r, p});
        }
        if(!res.empty()) {
            break;
        }
    }
    return res;
}