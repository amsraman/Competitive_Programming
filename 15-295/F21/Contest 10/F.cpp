#include <bits/stdc++.h>

using namespace std;

const int sq = 250;

int n, q, big_count, sub_count, big_compress[531441], general_compress[531441], num[50000][4];
vector<int> pos[531441];
int big[300][150000];
string s;

int ctoi(char c) {
    return c - 'a' + 1;
}

int conv(string str) {
    int ret = 0;
    for(char c: str) {
        ret = 27 * ret + ctoi(c);
    }
    return ret;
}

int str_len(int hsh) {
    int ret = 0;
    while(hsh > 0) {
        hsh /= 27, ++ret;
    }
    return ret;
}

int window_len(int x1, int len1, int x2, int len2) {
    return max(x1 + len1, x2 + len2) - min(x1, x2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> s >> q;
    n = s.length();
    for(int i = n - 1; i >= 0; i--) {
        num[i][0] = ctoi(s[i]);
        pos[num[i][0]].push_back(i);
        for(int j = 1; j < 4; j++) {
            if(i + j < n) {
                num[i][j] = 27 * num[i][j - 1] + num[i + j][0];
                pos[num[i][j]].push_back(i);
            }
        }
        for(int j = 0; j < 4; j++) {
            if(num[i][j] > 0 && general_compress[num[i][j]] == 0) {
                general_compress[num[i][j]] = sub_count++;
            }
        }
    }
    for(int ind = 0; ind < 27 * 27 * 27 * 27; ind++) {
        reverse(pos[ind].begin(), pos[ind].end());
        if(pos[ind].size() >= sq) {
            int sz = pos[ind].size(), len1 = str_len(ind);
            big_compress[ind] = big_count++;
            for(int len2 = 0; len2 < 4; len2++) {
                for(int i = 0, j = 0; i < sz && j < n - len2; i++) {
                    int cur_window = window_len(pos[ind][i], len1, j, len2 + 1);
                    while(i == sz - 1 || cur_window <= window_len(pos[ind][i + 1], len1, j, len2)) {
                        if(big[big_count - 1][general_compress[num[j][len2]]] == 0 || cur_window < big[big_count - 1][general_compress[num[j][len2]]]) {
                            big[big_count - 1][general_compress[num[j][len2]]] = cur_window;
                        }
                        j++;
                        if(j == n - len2) {
                            break;
                        }
                        cur_window = window_len(pos[ind][i], len1, j, len2 + 1);
                    }
                }
            }
        }
    }
    for(int i = 0; i < q; i++) {
        string a, b;
        cin >> a >> b;
        int s1 = conv(a), s2 = conv(b), len1 = a.length(), len2 = b.length();
        if(pos[s1].size() < pos[s2].size()) {
            swap(s1, s2), swap(len1, len2);
        }
        if(pos[s1].empty() || pos[s2].empty()) {
            cout << -1 << '\n';
        } else if(pos[s1].size() >= sq) {
            cout << big[big_compress[s1]][general_compress[s2]] << '\n';
        } else {
            int ans = n + 1, sz1 = pos[s1].size(), sz2 = pos[s2].size();
            for(int i = 0, j = 0; i < sz1 && j < sz2; i++) {
                int cur_window = window_len(pos[s1][i], len1, pos[s2][j], len2);
                while(i == sz1 - 1 || cur_window <= window_len(pos[s1][i + 1], len1, pos[s2][j], len2)) {
                    ans = min(ans, cur_window);
                    j++;
                    if(j == sz2) {
                        break;
                    }
                    cur_window = window_len(pos[s1][i], len1, pos[s2][j], len2);
                }
            }
            cout << ans << '\n';
        }
    }
}