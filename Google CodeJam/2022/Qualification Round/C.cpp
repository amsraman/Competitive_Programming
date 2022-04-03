#include <bits/stdc++.h>

using namespace std;

int t, n, s[100000];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        multiset<int> st;
        for(int i = 0; i < n; i++) {
            cin >> s[i];
            st.insert(s[i]);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            while(!st.empty() && *st.begin() < i) {
                st.erase(st.begin());
            }
            if(st.empty()) {
                break;
            }
            st.erase(st.begin());
            ++ans;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}