#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[100000], ps[1000002], mx;
ll ans;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ++ps[a[i] + 1];
        mx = max(mx, a[i]);
    }
    for(int i = 1; i <= mx + 1; i++) {
        ps[i] += ps[i - 1];
    }
    for(int i = 1; i <= mx; i++) {
        vector<int> grps;
        int num_odd = 0;
        for(int j = i; j <= mx; j += i) {
            int num = ps[min(mx + 1, j + i)] - ps[j];
            grps.push_back(num);
            num_odd += num % 2;
        }
        if(num_odd == 1 && grps[0] % 2 == 1) {
            ans += grps[0];
        } else if(num_odd == 2) {
            for(int k = 1; k < grps.size(); k++) {
                if(grps[k] % 2 == 1 && grps[k - 1] % 2 == 1) {
                    ans += grps[k];
                }
            }
        }
    }
    cout << ans << endl;
}