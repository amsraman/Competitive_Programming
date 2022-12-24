vector<int> KMP(const string & s) {
    int n = s.length();
    vector<int> kmp(n, 0);
    for(int i = 1, j = 0; i < n; i++) {
        while(j > 0 && s[i] != s[j]) {
            j = kmp[j - 1];
        }
        j += s[i] == s[j], kmp[i] = j;
    }
    return kmp;
}

vector<int> MatchKMP(const string & s, const string & t) { // returns starting indices
    int n = s.length(), m = t.length();
    vector<int> kmp = KMP(t), res;
    for(int i = 0, j = 0; i < n; i++) {
        while(j > 0 && s[i] != t[j]) {
            j = kmp[j - 1];
        }
        j += s[i] == t[j];
        if(j == m) {
            res.push_back(i - m + 1);
        }
    }
    return res;
}