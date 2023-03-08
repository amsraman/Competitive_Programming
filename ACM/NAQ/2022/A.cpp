#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> s(n);
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }
    sort(s.begin(), s.end()); reverse(s.begin(), s.end());
    ll stable = s[0], unstable = 0;
    int ans = 1;
    for(int i = 1; i < n; i++) {
        unstable += s[i];
        if(unstable >= stable) {
            stable += unstable, unstable = 0, ans = i + 1;
        }
    }
    cout << ans << '\n';
}