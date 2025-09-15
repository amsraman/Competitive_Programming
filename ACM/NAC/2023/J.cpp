#include <bits/stdc++.h>

using namespace std;

vector<int> kmp_function(const string & s) {
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int n = s.length(), nc = 1; long long ans = 0;
    vector<vector<int>> id(n, vector<int>(n)), left_check(n), left_insert(n), right_check(n), right_insert(n);
    vector<array<int, 26>> main_trie(1);
    for(int i = 0; i < n; i++) {
        int cur = 0;
        for(int j = i; j < n; j++) {
            if(!main_trie[cur][s[j] - 'a']) {
                main_trie.emplace_back();
                main_trie.back().fill(0);
                main_trie[cur][s[j] - 'a'] = nc++;
            }
            id[i][j] = cur = main_trie[cur][s[j] - 'a'];
            left_insert[j].push_back(id[i][j]);
            right_insert[i].push_back(id[i][j]);
        }
    }
    for(int i = 0; i < n; i++) {
        auto kmp = kmp_function(s.substr(i, n - i));
        for(int j = 0; j < n - i; j++) {
            for(int k = kmp[j]; k > 0; k = kmp[k - 1]) {
                if(2 * k < j + 1) {
                    left_check[i].push_back(id[i + k][i + j - k]);
                    right_check[i + j].push_back(id[i + k][i + j - k]);
                }
                ans += 2 * k <= j + 1; // equal parts
            }
        }
    }
    vector<int> cnt(nc, 0);
    for(int i = 0; i < n; i++) {
        for(int j: left_check[i]) ans += cnt[j];
        for(int j: left_insert[i]) ++cnt[j];
    }
    fill(cnt.begin(), cnt.end(), 0);
    for(int i = n - 1; i >= 0; i--) {
        for(int j: right_check[i]) ans += cnt[j];
        for(int j: right_insert[i]) ++cnt[j];
    }
    cout << ans << '\n';
}