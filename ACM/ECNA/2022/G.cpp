#include <bits/stdc++.h>

using namespace std;

int main() {
    string n, m; cin >> n >> m;
    auto nxt = [](string s) {
        vector<int> ct(10, 0);
        for(char c: s) ++ct[c - '0'];
        string res = "";
        for(int i = 0; i < 10; i++) {
            if(ct[i] > 0) {
                res += to_string(ct[i]);
                res += char('0' + i);
            }
        }
        return res;
    };
    set<string> vis;
    int ans = -1;
    for(int i = 1; ; i++) {
        if(n == m) {
            ans = i;
            break;
        }
        if(vis.count(n)) break;
        vis.insert(n);
        n = nxt(n);
    }
    if(ans == -1) {
        cout << "Does not appear\n";
    } else {
        cout << ans << '\n';
    }
}