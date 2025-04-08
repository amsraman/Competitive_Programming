#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<bool> pr(n, false), pl(n, false);
	int mx = -1e9;
	for(int i = 0; i < n; i++) {
		if(a[i] > mx) pl[i] = true;
		mx = max(mx, a[i]);
	}
	int mn = 1e9;
	for(int i = n - 1; i >= 0; i--) {
		if(a[i] < mn) pr[i] = true;
		mn = min(mn, a[i]);
	}
	vector<int> res;
	for(int i = 0; i < n; i++) {
		if(pl[i] && pr[i]) res.push_back(i);
	}
	cout << res.size() << " ";
	for(int i = 0; i < min((int) res.size(), 100); i++) {
		cout << a[res[i]] << " ";
	}
	cout << "\n";
}