// 30 ms
#include <bits/stdc++.h>

using namespace std;

vector<int> Z(const string & s) {
    int n = s.length();
    vector<int> z(n, 0);
    for(int i = 1, l = 0, r = 0; i < n; i++) {
        if(i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if(i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    vector<int> res = Z(s); res[0] = s.length();
    for(int r: res) {
        cout << r << " ";
    }
    cout << '\n';
}