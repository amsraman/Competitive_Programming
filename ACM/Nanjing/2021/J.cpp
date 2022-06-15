#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

vector<int> primes;
map<pair<int, int>, int> dp;

int solve(int a, int b) {
    if(a == 1 || a - b == 1) {
        return 0;
    }
    if(dp.count({a, b})) {
        return dp[{a, b}];
    }
    int ans = a - b - 1;
    for(int p: primes) {
        if(b % p == 0) {
            int up = (a + p - 1) / p * p, down = a / p * p;
            if(up - a < a - down) {
                ans = min(ans, up - a + 1 + solve(up / p, b / p));
            } else if(up - a > a - down) {
                ans = min(ans, a - down + 1 + solve(down / p, b / p));
            } else {
                ans = min({ans, up - a + 1 + solve(up / p, b / p), a - down + 1 + solve(down / p, b / p)});
            }
        }
    }
    return dp[{a, b}] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;
        if(a < b) {
            swap(a, b);
        }
        int del = a - b;
        for(int i = 2; i * i <= del; i++) {
            if(del % i == 0) {
                primes.push_back(i);
            }
            while(del % i == 0) {
                del /= i;
            }
        }
        if(del > 1) {
            primes.push_back(del);
        }
        cout << solve(a, a - b) << '\n';
        primes.clear();
    }
}