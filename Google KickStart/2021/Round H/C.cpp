#include <bits/stdc++.h>

using namespace std;

int t, n, pv[500002], nxt[500002];
string s;

int ctoi(char c) {
    return c - '0';
}

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> s;
        int tc = 0;
        set<int> oper[10];
        for(int i = 0; i <= n; i++) {
            nxt[i] = i + 1;
            pv[i + 1] = i;
        }
        for(int i = 0; i < n - 1; i++) {
            if(ctoi(s[i + 1]) == (ctoi(s[i] + 1) % 10)) {
                oper[ctoi(s[i])].insert(i + 1);
                ++tc;
            }
        }
        int stg = 0;
        while(tc > 0) {
            while(oper[stg].empty()) {
                stg = (stg + 1) % 10;
            }
            int cur = *oper[stg].begin();
            oper[stg].erase(cur);
            --tc;
            s[cur - 1] = char('0' + (ctoi(s[cur - 1]) + 2) % 10);
            // Remove the thing after cur
            int rem = nxt[cur];
            assert(rem <= n);
            pv[nxt[rem]] = pv[rem];
            nxt[pv[rem]] = nxt[rem];
            for(int i = 0; i < 10; i++) {
                if(oper[i].count(rem)) {
                    oper[i].erase(rem);
                    --tc;
                }
            }
            // The thing before cur might as well be removed anyway, since we need to recheck if it's valid
            for(int i = 0; i < 10; i++) {
                if(oper[i].count(pv[cur])) {
                    oper[i].erase(pv[cur]);
                    --tc;
                }
            }
            if(nxt[cur] <= n && (ctoi(s[nxt[cur] - 1]) == (ctoi(s[cur - 1] + 1) % 10))) {
                oper[ctoi(s[cur - 1])].insert(cur);
                ++tc;
            }
            if(pv[cur] > 0 && (ctoi(s[cur - 1]) == ((ctoi(s[pv[cur] - 1]) + 1) % 10))) {
                oper[ctoi(s[pv[cur] - 1])].insert(pv[cur]);
                ++tc;
            }
        }
        cout << "Case #" << _ << ": ";
        int beg = nxt[0];
        while(beg <= n) {
            cout << s[beg - 1];
            beg = nxt[beg];
        }
        cout << endl;
    }
}