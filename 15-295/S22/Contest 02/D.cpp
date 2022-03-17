#include <bits/stdc++.h>

using namespace std;

int n, m, d[(1 << 16)], s[(1 << 16)];
vector<int> g[(1 << 16)];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        cin >> d[i] >> s[i];
        m += d[i];
        if(d[i] == 1) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        if(d[x] == 0) {
            continue;
        }
        g[x].push_back(s[x]);
        g[s[x]].push_back(x);
        s[s[x]] ^= x;
        --d[s[x]];
        if(d[s[x]] == 1) {
            q.push(s[x]);
        }
    }
    m /= 2;
    cout << m << '\n';
    for(int i = 0; i < n; i++) {
        for(int j: g[i]) {
            if(j > i) {
                cout << i << " " << j << '\n';
            }
        }
    }
}