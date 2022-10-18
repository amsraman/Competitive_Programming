#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        cin >> n;
        vector<int> a(n + 1, 0);
        vector<ll> num(n + 2, 0);
        for(int i = 0; i < n; i++) {
            cin >> a[i + 1];
            a[i + 1] += a[i];
        }
        stack<int> st;
        st.push(n);
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }
            int sz;
            if(st.empty()) {
                sz = n - i;
            } else {
                sz = st.top() - i - 1;
            }
            num[i] -= sz, num[i + 1] += sz + 1, --num[i + sz + 1];
            st.push(i);
        }
        ll ans = 0;
        for(int i = 0; i <= n; i++) {
            if(i > 0) {
                num[i] += num[i - 1];
            }
            ans += num[i] * a[i];
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}