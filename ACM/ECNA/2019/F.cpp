#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> k(n);
    for(int i = 0; i < n; i++) {
        cin >> k[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    for(int i = 0, cur; i < n - 1; i++) {
        cur = (cur + k[ord[cur]] - 1) % (n - i);
        ord.erase(ord.begin() + cur);
        if(cur == n - i - 1) cur = 0;
    }
    cout << ord[0] + 1 << '\n';
}