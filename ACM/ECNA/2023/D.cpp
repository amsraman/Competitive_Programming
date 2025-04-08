#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tot = 0;
	for(int i = 0; i < 5; i++) {
		int a, l; cin >> a >> l; tot += a * l;
	}
	tot /= 5;
	int n, kwl; cin >> n >> kwl;
	cout << (tot * n) / kwl << endl;
}