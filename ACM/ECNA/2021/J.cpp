#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, a[100000], lp[100000], rp[100000];
ll ans;
pair<int, int> go;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
	stack<int> ls, rs;
	for(int i = 0; i < n; i++) {
		while(!ls.empty() && a[ls.top()] >= a[i]) {
			ls.pop();
		}
		if(ls.empty()) {
			lp[i] = 0;
		} else {
			lp[i] = ls.top() + 1;
		}
		ls.push(i);
	}
	for(int i = n - 1; i >= 0; i--) {
		while(!rs.empty() && a[rs.top()] >= a[i]) {
			rs.pop();
		}
		if(rs.empty()) {
			rp[i] = n - 1;
		} else {
			rp[i] = rs.top() - 1;
		}
		rs.push(i);
	}
	for(int i = 0; i < n; i++) {
		ll cur = 1LL * (rp[i] - lp[i] + 1) * a[i];
		if(cur > ans) {
			ans = cur;
			go = {lp[i], rp[i]};
		} else if(cur == ans && lp[i] < go.f) {
			go = {lp[i], rp[i]};
		}
	}
	cout << go.f + 1 << " " << go.s + 1 << " " << ans << '\n';
}