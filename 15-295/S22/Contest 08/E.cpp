#include <bits/stdc++.h>

using namespace std;

int n, sz[1000000], num[1000001];
vector<int> g[1000000];

void dfs(int x, int p) {
    sz[x] = 1;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
            sz[x] += sz[u];
        }
    }
    ++num[sz[x]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0, a, b; i < n - 1; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    dfs(0, 0);
    for(int i = 1; i <= n; i++) {
        for(int j = 2 * i; j <= n; j += i) {
            num[i] += num[j];
        }
    }
    vector<int> ans;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0 && num[i] == n / i) {
            ans.push_back(n / i - 1);
        }
        if(i != n / i && n % i == 0 && num[n / i] == i) {
            ans.push_back(i - 1);
        }
    }
    ans.push_back(n - 1);
    sort(ans.begin(), ans.end());
    for(int a: ans) {
        cout << a << " ";
    }
    cout << '\n';
}