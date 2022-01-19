#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, str[200001];
ll ans;
string s, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s >> t;
    str[n] = n;
    char sc = 'a', tc = 'a';
    for(int i = n - 1; i >= 0; i--) {
        str[i] = str[i + 1];
        if(s[i] != t[i]) {
            str[i] = i;
            sc = s[i], tc = t[i];
        }
        if(sc < tc) {
            ans += n - str[i];
        }
    }
    cout << ans << '\n';
}