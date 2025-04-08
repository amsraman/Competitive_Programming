#include <bits/stdc++.h>

using namespace std;

int main() {
    string s; cin >> s;
    for(int _ = 1; s != "0"; _++) {
        int n, dig; cin >> n;
        vector<string> dict(n);
        for(int i = 0; i < n; i++) {
            cin >> dict[i];
        }
        int len = (int) s.length();
        string res = "", lst = "";
        for(int i = 0; i < len; i += dig) {
            dig = 0;
            for(int tp = max(1, n + (i > 0) - 1); tp > 0; tp /= 10) ++dig;
            int tp = atoi(s.substr(i, dig).c_str());
            if(i > 0) {
                dict.push_back(lst + (tp == n ? lst[0] : dict[tp][0])), ++n;
            }
            res += lst = dict[tp];
        }
        cout << "Case " << _ << ": " << res << '\n';
        cin >> s;
    }
}