#include <bits/stdc++.h>

using namespace std;

int n;
string s;

bool ok(int x) {
    vector<int> pv(n);
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for(int i = 0, j = -1; i < n; i++) {
        pv[i] = j;
        if(s[i] == 'P') {
            j = i;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(s[i - 1] == '.') {
            dp[i] = dp[i - 1];
        } else if(s[i - 1] == 'P') {
            if(pv[i - 1] == -1 || pv[i - 1] < i - x - 1) {
                dp[i] = dp[max(0, i - x - 1)];
            } else {
                dp[i] = dp[pv[i - 1] + 1];
            }
        } else {
            if(pv[i - 1] == -1 || pv[i - 1] < i - x - 1) {
                dp[i] = false;
            } else if(dp[pv[i - 1]]) {
                dp[i] = true;
            } else if(pv[pv[i - 1]] == -1 || pv[pv[i - 1]] < i - x - 1) {
                dp[i] = false;
            } else if(dp[max(0, pv[i - 1] - x)]) {
                dp[i] = true;
            } else if(pv[pv[pv[i - 1]]] != -1 && pv[i - 1] - pv[pv[pv[i - 1]]] <= x + 1 && dp[pv[pv[pv[i - 1]]] + 1]) {
                dp[i] = true;
            } else {
                dp[i] = false;
            }
        }
    }
    return dp[n];
}

int main() {
    cin >> n >> s;
    int packmen = 0, stars = 0;
    for(char c: s) {
        packmen += c == 'P', stars += c == '*';
    }
    if(packmen == 1) {
        int n1 = 0, m1 = 0, n2 = 0, m2 = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'P') {
                for(int j = i - 1; j >= 0; j--) {
                    if(s[j] == '*') {
                        ++n1, m1 = max(m1, i - j);
                    }
                }
                for(int j = i + 1; j < n; j++) {
                    if(s[j] == '*') {
                        ++n2, m2 = max(m2, j - i);
                    }
                }
            }
        }
        if(n1 > n2) {
            cout << n1 << " " << m1 << '\n';
        } else if(n2 > n1) {
            cout << n2 << " " << m2 << '\n';
        } else {
            cout << n1 << " " << min(m1, m2) << '\n';
        }
    } else {
        cout << stars << " ";
        int lb = 0, ub = n - 1;
        while(lb < ub) {
            int mid = (lb + ub) >> 1;
            if(ok(mid)) {
                ub = mid;
            } else {
                lb = mid + 1;
            }
        }
        cout << ub << '\n';
    }
}